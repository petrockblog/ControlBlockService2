#ifndef UINPUTKEYBOARD_H
#define UINPUTKEYBOARD_H

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
    virtual ~UInputKeyboard();
};

#endif
