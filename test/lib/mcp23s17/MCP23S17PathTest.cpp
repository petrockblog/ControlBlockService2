#include <stddef.h>
#include <string.h>

#include <iostream>

int mcp23s17_build_spidev_path(int bus,
                               int chip_select,
                               char *path,
                               size_t path_size);

static int expect_path(int bus, int chip_select, const char *expected)
{
    char path[32] = {0};

    if (mcp23s17_build_spidev_path(bus, chip_select, path, sizeof(path)) != 0) {
        std::cerr << "Expected valid path for bus " << bus
                  << ", chip select " << chip_select << "\n";
        return 1;
    }

    if (strcmp(path, expected) != 0) {
        std::cerr << "Expected " << expected << ", got " << path << "\n";
        return 1;
    }

    return 0;
}

static int expect_invalid(int bus, int chip_select)
{
    char path[32] = {0};

    if (mcp23s17_build_spidev_path(bus, chip_select, path, sizeof(path)) == 0) {
        std::cerr << "Expected invalid path for bus " << bus
                  << ", chip select " << chip_select << ", got " << path << "\n";
        return 1;
    }

    return 0;
}

int main()
{
    int failures = 0;

    failures += expect_path(0, 0, "/dev/spidev0.0");
    failures += expect_path(0, 1, "/dev/spidev0.1");
    failures += expect_path(10, 0, "/dev/spidev10.0");
    failures += expect_invalid(-1, 0);
    failures += expect_invalid(0, -1);
    failures += expect_invalid(0, 2);

    return failures == 0 ? 0 : 1;
}
