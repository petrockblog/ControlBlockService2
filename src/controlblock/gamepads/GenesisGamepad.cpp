#include "GenesisGamepad.h"

const IDigitalOut::DO_Channel_e GenesisGamepad::CHN_SELECT[] = {IDigitalOut::DO_CHANNEL_GENESIS_P1_SELECT,
                                                                IDigitalOut::DO_CHANNEL_GENESIS_P2_SELECT};  //!< Controller DB9 Pin 7 Mapping

/**
 * Controller DB9 Pin to Button Flag Mappings
 * First column is the controller index, second column
 * is the input pin that the controller's DB9 pin is
 * attached to, remaing columns are the button flags
 */
const GenesisGamepad::Input GenesisGamepad::inputMap[] = {
        {0, IDigitalIn::DI_CHANNEL_P1_RIGHT, UP, UP, Z}, // P0 DB9 Pin 1
        {0, IDigitalIn::DI_CHANNEL_P1_LEFT, DOWN, DOWN, Y}, // P0 DB9 Pin 2
        {0, IDigitalIn::DI_CHANNEL_P1_UP, ON, LEFT, X}, // P0 DB9 Pin 3
        {0, IDigitalIn::DI_CHANNEL_P1_DOWN, ON, RIGHT, MODE}, // P0 DB9 Pin 4
        {0, IDigitalIn::DI_CHANNEL_P1_SW2, A, B, 0}, // P0 DB9 Pin 6
        {0, IDigitalIn::DI_CHANNEL_P1_SW5, START, C, 0}, // P0 DB9 Pin 9
        {1, IDigitalIn::DI_CHANNEL_P2_RIGHT, UP, UP, Z}, // P0 DB9 Pin 1
        {1, IDigitalIn::DI_CHANNEL_P2_LEFT, DOWN, DOWN, Y}, // P0 DB9 Pin 2
        {1, IDigitalIn::DI_CHANNEL_P2_UP, ON, LEFT, X}, // P0 DB9 Pin 3
        {1, IDigitalIn::DI_CHANNEL_P2_DOWN, ON, RIGHT, MODE}, // P0 DB9 Pin 4
        {1, IDigitalIn::DI_CHANNEL_P2_SW2, A, B, 0}, // P0 DB9 Pin 6
        {1, IDigitalIn::DI_CHANNEL_P2_SW5, START, C, 0}, // P0 DB9 Pin 9
};

GenesisGamepad::GenesisGamepad(IUInputFactory& uiFactory, IDigitalIn& digitalInRef, IDigitalOut& digitalOutRef)
        :
        channel(InputDevice::CHANNEL_UNDEFINED),
        digitalIn(digitalInRef),
        digitalOut(digitalOutRef),
        isInSixButtonMode(false),
        currentState(0u),
        lastState(0xFFFF)
{
    gamepad = uiFactory.getUInputDevice(IUInputDevice::TYPE_GAMEPAD_GENESIS);
}

void GenesisGamepad::initialize(InputDevice::Channel_e channel)
{
    IDigitalOut::BoardNumber_e boardOut = IDigitalOut::BOARD_0;
    if ((channel==InputDevice::CHANNEL_1) || (channel==InputDevice::CHANNEL_2)) {
        boardOut = IDigitalOut::BOARD_0;
    }
    else {
        boardOut = IDigitalOut::BOARD_1;
    }

    digitalIn.configureDevice(IDigitalIn::DI_DEVICE_GENESIS);
    digitalOut.configureDevice(IDigitalOut::DO_DEVICE_GENESIS);

    this->channel = channel;
}

void GenesisGamepad::update()
{
    readButtons();
    sendStates();
}

void GenesisGamepad::readButtons()
{
    for (int i = 0; i<NUM_PLAYERS; i++) {
        resetState(i);
        if (isInSixButtonMode) {
            read6buttons(i);
        }
        else {
            read3buttons(i);
        }
    }
}

void GenesisGamepad::resetState(int player)
{
    currentState = 0u;
}

void GenesisGamepad::read3buttons(int player)
{
    // Set SELECT LOW and read lowFlag
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_LOW);

    for (int i = 0; i<sizeof(inputMap)/sizeof(Input); i++) {
        if ((inputMap[i].player==player) && (digitalIn.getLevel(inputMap[i].inputChannel)==IDigitalIn::DI_LEVEL_LOW)) {
            currentState |= inputMap[i].lowFlag;
        }
    }

    // Set SELECT HIGH and read highFlag
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_HIGH);

    for (int i = 0; i<sizeof(inputMap)/sizeof(Input); i++) {
        if ((inputMap[i].player==player) && (digitalIn.getLevel(inputMap[i].inputChannel)==IDigitalIn::DI_LEVEL_LOW)) {
            currentState |= inputMap[i].highFlag;
        }
    }

    // When a six-button first connects, it'll spam UP and DOWN,
    // which signals the game to switch to 6-button polling
    if (currentState==(ON | UP | DOWN)) {
        isInSixButtonMode = true;
    }
        // When a controller disconnects, revert to three-button polling
    else if ((currentState & ON)==0) {
        isInSixButtonMode = false;
    }
}

void GenesisGamepad::read6buttons(int player)
{
    // Poll for three-button states twice
    read3buttons(player);
    read3buttons(player);

    // After two three-button polls, pulse the SELECT line
    // so the six-button reports the higher button states
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_LOW);
    digitalOut.setLevel(CHN_SELECT[player], IDigitalOut::DO_LEVEL_HIGH);

    for (int i = 0; i<sizeof(inputMap)/sizeof(Input); i++) {
        if ((inputMap[i].player==player) && (digitalIn.getLevel(inputMap[i].inputChannel)==IDigitalIn::DI_LEVEL_LOW)) {
            currentState |= inputMap[i].pulse3Flag;
        }
    }
}

void GenesisGamepad::sendStates()
{
    // Only report controller states if at least one has changed
    bool hasChanged = false;

    if (currentState!=lastState) {
        hasChanged = true;
    }

    if (hasChanged) {
        // left-right axis
        if ((currentState & LEFT) == LEFT)
        {
            gamepad->setKeyState(ABS_X, 0, EV_ABS);
        }
        else if ((currentState & RIGHT) == RIGHT)
        {
            gamepad->setKeyState(ABS_X, 4, EV_ABS);
        }
        else
        {
            gamepad->setKeyState(ABS_X, 2, EV_ABS);
        }

        // up-down axis
        if ((currentState & UP) == UP)
        {
            gamepad->setKeyState(ABS_Y, 0, EV_ABS);
        }
        else if ((currentState & DOWN) == DOWN)
        {
            gamepad->setKeyState(ABS_Y, 4, EV_ABS);
        }
        else
        {
            gamepad->setKeyState(ABS_Y, 2, EV_ABS);
        }

        // buttons
        gamepad->setKeyState(BTN_A, (currentState & A) == A ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_B, (currentState & B) == B ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_C, (currentState & C) == C ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_X, (currentState & X) == X ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Y, (currentState & Y) == Y ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_Z, (currentState & Z) == Z ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_START, (currentState & START) == START ? 1 : 0, EV_KEY);
        gamepad->setKeyState(BTN_MODE, (currentState & MODE) == MODE ? 1 : 0, EV_KEY);

        lastState = currentState;
    }
}