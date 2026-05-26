#!/bin/bash
#
# ControlBlockService2 installer
#
# Quick install (downloads to a file first so the password prompt stays visible):
#   curl -fsSL https://raw.githubusercontent.com/petrockblog/ControlBlockService2/master/install.sh -o install.sh && sudo bash install.sh
#
# Or, if you prefer a single pipe:
#   curl -fsSL https://raw.githubusercontent.com/petrockblog/ControlBlockService2/master/install.sh | sudo bash
#
# The script installs system packages, builds the driver, installs it as a
# systemd service, and updates the Raspberry Pi boot configuration.

set -uo pipefail

REPO_URL="https://github.com/petrockblog/ControlBlockService2"
REBOOT_REQUIRED=0
STEP=0
TOTAL_STEPS=6

# ---------------------------------------------------------------------------
# Output helpers (colour only when writing to an interactive terminal)
# ---------------------------------------------------------------------------
if [[ -t 1 ]]; then
    C_RESET=$'\033[0m'; C_BOLD=$'\033[1m'
    C_GREEN=$'\033[32m'; C_YELLOW=$'\033[33m'; C_RED=$'\033[31m'; C_BLUE=$'\033[34m'
else
    C_RESET=""; C_BOLD=""; C_GREEN=""; C_YELLOW=""; C_RED=""; C_BLUE=""
fi

step()    { STEP=$((STEP + 1)); echo; echo "${C_BOLD}${C_BLUE}[${STEP}/${TOTAL_STEPS}] $*${C_RESET}"; }
info()    { echo "    $*"; }
success() { echo "${C_GREEN}[SUCCESS]${C_RESET} $*"; }
warn()    { echo "${C_YELLOW}[WARNING]${C_RESET} $*"; }
fail()    { echo "${C_RED}[ERROR]${C_RESET} $*" >&2; }
die()     { fail "$*"; exit 1; }

# ---------------------------------------------------------------------------
# Privilege handling
#
# The whole installer needs root. If we are not root yet, we explain why and
# re-run ourselves through sudo so the password prompt appears with context.
# (When invoked as "... | sudo bash" we are already root and skip this.)
# ---------------------------------------------------------------------------
ensure_root() {
    if [[ $EUID -eq 0 ]]; then
        return 0
    fi

    echo "${C_BOLD}ControlBlock installer${C_RESET}"
    echo
    echo "This installer needs administrator (root) privileges to:"
    echo "  - install required system packages"
    echo "  - install the ControlBlock binary and systemd service"
    echo "  - update the Raspberry Pi boot configuration"
    echo
    echo "${C_YELLOW}You may now be prompted for your password.${C_RESET}"
    echo

    if [[ -f "${BASH_SOURCE[0]:-}" ]]; then
        exec sudo -- bash "${BASH_SOURCE[0]}" "$@"
    fi

    # We were piped in via stdin, so there is no file to re-exec.
    die "Please re-run this installer as root, e.g.: sudo bash install.sh"
}

# ---------------------------------------------------------------------------
# Installation steps
# ---------------------------------------------------------------------------

install_packages() {
    step "Installing system packages"
    export DEBIAN_FRONTEND=noninteractive

    info "Refreshing package lists (apt-get update)..."
    if ! apt-get update; then
        warn "Could not refresh package lists; trying to install with the cached lists."
    fi

    info "Installing build and runtime dependencies..."
    apt-get install -y git cmake g++ doxygen libc6 libc6-dev libgpiod-dev gpiod \
        || die "Installation of APT packages failed."
}

prepare_source() {
    step "Preparing source code"

    # Already inside a valid checkout?
    if [[ "${PWD##*/}" == "ControlBlockService2" && -d .git ]]; then
        info "Using the current ControlBlockService2 checkout."
        return 0
    fi

    # A checkout already exists next to us -> reuse and update it.
    if [[ -d ControlBlockService2/.git ]]; then
        info "Reusing existing ControlBlockService2 checkout."
        cd ControlBlockService2 || die "Cannot enter existing ControlBlockService2 directory."
        if ! git pull --ff-only; then
            warn "Could not fast-forward the existing checkout; continuing with its current state."
        fi
        return 0
    fi

    # Something is in the way that is not a git checkout.
    if [[ -e ControlBlockService2 ]]; then
        die "A 'ControlBlockService2' entry exists but is not a git checkout. Please remove or rename it and re-run."
    fi

    info "Cloning ControlBlockService2..."
    git clone --recursive "$REPO_URL" || die "git clone failed (check your network connection)."
    cd ControlBlockService2 || die "Cannot enter the freshly cloned directory."
}

update_submodules() {
    step "Fetching submodules"
    git submodule update --init --recursive || die "Could not initialise git submodules."
}

build_driver() {
    step "Building the driver"

    rm -rf build
    mkdir build || die "Could not create the build folder."

    local jobs
    jobs="$(nproc 2>/dev/null || echo 1)"

    (
        cd build || exit 1
        cmake .. || exit 1
        info "Compiling with ${jobs} parallel job(s)..."
        make -j"${jobs}" || exit 1
    ) || die "Build failed. See the output above for details."
}

install_driver() {
    step "Installing binary and service"
    (
        cd build || exit 1
        make install || exit 1
        make installservice || exit 1
    ) || die "Installation failed. See the output above for details."

    # Give systemd a moment to start the freshly installed service.
    sleep 3
}

update_boot_config() {
    step "Updating Raspberry Pi boot configuration"

    local file
    if [[ -f /boot/firmware/config.txt ]]; then
        file="/boot/firmware/config.txt"          # Raspberry Pi OS Bookworm and RPi 5
    elif [[ -f /boot/config.txt ]]; then
        file="/boot/config.txt"                    # older Raspberry Pi OS
    else
        warn "No Raspberry Pi boot config found; skipping the USB current setting."
        return 0
    fi

    if grep -Eq '^[[:space:]]*usb_max_current_enable=1' "$file"; then
        info "$file already enables high USB current; no change needed."
    elif grep -Eq '^[[:space:]]*usb_max_current_enable=0' "$file"; then
        sed -i 's/^[[:space:]]*usb_max_current_enable=0/usb_max_current_enable=1/' "$file"
        info "Enabled high USB current in $file."
        REBOOT_REQUIRED=1
    else
        # Append under an explicit [all] header so the setting is not swallowed
        # by a preceding conditional filter section (e.g. [pi4], [cm4]).
        printf '\n[all]\nusb_max_current_enable=1\n' >> "$file"
        info "Added high USB current setting to $file."
        REBOOT_REQUIRED=1
    fi
}

perform_sanity_checks() {
    step "Verifying the installation"
    local errors=0

    if [[ -x /usr/bin/controlblock ]]; then
        success "The ControlBlock driver binary is installed."
    else
        fail "The ControlBlock driver binary is not installed."
        errors=$((errors + 1))
    fi

    if systemctl is-active --quiet controlblock 2>/dev/null; then
        success "The ControlBlock service is running."
    else
        warn "The ControlBlock service is not running yet."
        warn "This is often normal before the first reboot (SPI may not be active yet)."
        warn "Check it after rebooting with: systemctl status controlblock"
    fi

    return "$errors"
}

print_summary() {
    echo
    echo "${C_BOLD}=====================================================${C_RESET}"
    if [[ $1 -eq 0 ]]; then
        echo "${C_GREEN}${C_BOLD} ControlBlock installation complete.${C_RESET}"
    else
        echo "${C_RED}${C_BOLD} ControlBlock installation finished with errors.${C_RESET}"
    fi
    echo "${C_BOLD}=====================================================${C_RESET}"
    echo
    echo "Configuration file: ${C_BOLD}/etc/controlblockconfig.cfg${C_RESET}"
    echo "Shutdown script:    ${C_BOLD}/etc/controlblockswitchoff.sh${C_RESET}"
    echo
    echo "Useful commands:"
    echo "  systemctl status controlblock     # service status"
    echo "  journalctl -u controlblock -f     # live logs"
    echo "  jstest /dev/input/js0             # test player 1"
    echo

    if [[ $REBOOT_REQUIRED -eq 1 ]]; then
        echo "${C_YELLOW}${C_BOLD}A reboot is required to apply the boot configuration / SPI changes:${C_RESET}"
        echo "  sudo reboot"
        echo
    fi
}

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------
main() {
    ensure_root "$@"
    install_packages
    prepare_source
    update_submodules
    build_driver
    install_driver
    update_boot_config

    local result=0
    perform_sanity_checks || result=$?
    print_summary "$result"

    [[ $result -eq 0 ]]
}

main "$@"
