#!/bin/bash
# Test compilation in a Debian Bookworm ARM64 container
# Requires: docker with buildx/qemu for ARM emulation
#
# Usage: ./test_bookworm_build.sh

set -e

echo "Building in Debian Bookworm ARM64 container..."

docker run --rm --platform linux/arm64 \
  -v "$(pwd):/src" \
  -w /src \
  debian:bookworm \
  bash -c '
    apt-get update && apt-get install -y cmake g++ libgpiod-dev
    echo "=== libgpiod version ==="
    dpkg -l | grep libgpiod
    echo "=== Checking GPIOD_API_VERSION ==="
    grep -r "GPIOD_API_VERSION" /usr/include/gpiod* || echo "GPIOD_API_VERSION not defined (v1.x)"
    echo "=== Building project ==="
    rm -rf build && mkdir build && cd build
    cmake .. && make -j$(nproc)
    echo "=== Build successful! ==="
  '
