//
// Created by Florian Müller on 08.01.17.
//

#ifndef CONTROLBLOCKSERVICE2_IDIGITALIN_H
#define CONTROLBLOCKSERVICE2_IDIGITALIN_H

class IDigitalIn {
public:
    /**
 * Digital input channel identifiers
 */
    enum DI_Channel_e
    {
      DI_CHANNEL_FROMPOWERSWITCH = 0,
      DI_CHANNEL_P1_RIGHT,
      DI_CHANNEL_P1_LEFT,
      DI_CHANNEL_P1_UP,
      DI_CHANNEL_P1_DOWN,
      DI_CHANNEL_P1_SW1,
      DI_CHANNEL_P1_SW2,
      DI_CHANNEL_P1_SW3,
      DI_CHANNEL_P1_SW4,
      DI_CHANNEL_P1_SW5,
      DI_CHANNEL_P1_SW6,
      DI_CHANNEL_P1_SW7,
      DI_CHANNEL_P1_SW8,
      DI_CHANNEL_P1_START,
      DI_CHANNEL_P1_COIN,
      DI_CHANNEL_P1_A,
      DI_CHANNEL_P1_B,
      DI_CHANNEL_P2_RIGHT,
      DI_CHANNEL_P2_LEFT,
      DI_CHANNEL_P2_UP,
      DI_CHANNEL_P2_DOWN,
      DI_CHANNEL_P2_SW1,
      DI_CHANNEL_P2_SW2,
      DI_CHANNEL_P2_SW3,
      DI_CHANNEL_P2_SW4,
      DI_CHANNEL_P2_SW5,
      DI_CHANNEL_P2_SW6,
      DI_CHANNEL_P2_SW7,
      DI_CHANNEL_P2_SW8,
      DI_CHANNEL_P2_START,
      DI_CHANNEL_P2_COIN,
      DI_CHANNEL_P2_A,
      DI_CHANNEL_P2_B,
      DI_CHANNEL_P1_DATA,
      DI_CHANNEL_P2_DATA,
      DI_CHANNEL_SNES_RESET
    };

    /**
     * Board identifiers in case of several stacked ControlBLocks
     */
    enum BoardNumber_e
    {
      BOARD_0 = 0,//!< BOARD_0
      BOARD_1     //!< BOARD_1
    };

    /**
     * Logical input level identifiers
     */
    enum DI_Level_e
    {
      DI_LEVEL_LOW = 0,
      DI_LEVEL_HIGH
    };

    /**
     * Logical device identifiers for default configurations
     */
    enum DI_Device
    {
      DI_DEVICE_ALLIN = 0,   //!< Device with all ports set as input ports
      DI_DEVICE_POWERSWITCH, //!< Powerswitch device
      DI_DEVICE_SNES         //!< SNES controller device
    };

    virtual void configureDevice(DI_Device mode) = 0;

    virtual DI_Level_e getLevel(DI_Channel_e channel, BoardNumber_e board = BOARD_0) = 0;
};
#endif //CONTROLBLOCKSERVICE2_IDIGITALIN_H
