#include "stdafx.h"
#include "Logger.h"
#include "ABT.h"

ABT::Logger ABT::Logger::m_logger;

ABT::Logger::Logger()
{
  m_logFile.open("Log.txt", std::ios::out);
  assert(m_logFile.good());
}

ABT::Logger::~Logger()
{
  m_logFile.close();
}

ABT::Logger* ABT::Logger::GetInstance()
{
  return &m_logger;
}

void ABT::Logger::Log(std::string message)
{
  m_logFile << message << std::endl;
}
