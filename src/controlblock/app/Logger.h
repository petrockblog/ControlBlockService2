//
// Created by Florian Müller on 03.12.19.
//

#ifndef CONTROLBLOCKSERVICE2_SRC_CONTROLBLOCK_APP_LOGGER_H_
#define CONTROLBLOCKSERVICE2_SRC_CONTROLBLOCK_APP_LOGGER_H_

#include <string>

class Logger {
 public:
  Logger();
  ~Logger();

  static void init();
  static void logMessage(std::string message);

};

#endif //CONTROLBLOCKSERVICE2_SRC_CONTROLBLOCK_APP_LOGGER_H_
