#pragma once

#include <string>
#include <fstream>

namespace ABT
{

  class Logger
  {
  public:
    ~Logger();
    static Logger* GetInstance();
    void Log(std::string message);

  private:
    Logger();
    static Logger m_logger;
    std::ofstream m_logFile;
  };

}
