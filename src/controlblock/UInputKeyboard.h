#ifndef UINPUTKEYBOARD_H
#define UINPUTKEYBOARD_H

#include <stdint.h>
extern "C"
{
#include <linux/input.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
}

#include "UInputDevice.h"

class UInputKeyboard : public UInputDevice
{
public:
    /**
     * Constructor
     */
    UInputKeyboard();

    /**
     * Destructor
     */
    ~UInputKeyboard();
};

#endif
