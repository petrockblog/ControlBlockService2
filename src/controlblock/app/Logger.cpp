//
// Created by Florian Müller on 03.12.19.
//

#include <plog/Log.h>

#include "Logger.h"


Logger::Logger() {

}

Logger::~Logger() {

}

void Logger::init() {
  plog::init(plog::debug, "/tmp/controlblock.log");
}
void Logger::logMessage(std::string message) {
  PLOGD << message;
}
