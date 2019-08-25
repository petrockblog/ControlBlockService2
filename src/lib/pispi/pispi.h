#pragma once
#ifndef __PiSPI_H_
#define __PiSPI_H_

// Includes
#include <mutex>
#include <cstdint>
#include <linux/spi/spidev.h>

//Namespace STD to avoid std::
using namespace std;

//PiSPI class
//Class for low level SPI communicationn
class PiSPI {
 public:
  static std::mutex mutexSPI[2];

  //Constructor - Sets up the SPI Port and opens it. Singleton due to HW.
  PiSPI(uint8_t channel, int speed, int mode, uint8_t bitsperword = 8);
  ~PiSPI();

  bool SetMode(int mode);
  int GetMode();

  bool SetBitsPerWord(uint8_t bpw);
  uint8_t GetBitsPerWord();

  bool SetSpeed(int speed);
  int GetSpeed();

  bool Write(uint8_t reg, uint8_t *pData, size_t length);
  bool Read(uint8_t reg, uint8_t *pData, size_t length);
  bool SyncReadWrite(uint8_t *pData, size_t length);

 private:
  uint8_t _u8Channel;
  int _iSpeed;
  uint8_t _iBitsPerWord;
  int _iMode;
  int _iFD;

};

#endif //__PiSPI_H_