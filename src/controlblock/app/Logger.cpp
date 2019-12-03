//
// Created by Florian Müller on 03.12.19.
//

#include <plog/Log.h>

#include "Logger.h"


Logger::Logger() = default;

Logger::~Logger() = default;

void Logger::init() {
  plog::init(plog::debug, "/tmp/controlblock.log");
}
void Logger::logMessage(const std::string& message) {
  PLOGD << message;
}
