/*
 * ComputerInfo.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "ComputerInfo.hpp"
#include <sstream>

using namespace std;

bool ComputerInfo::update()
{
  if (!m_initialized)
    m_sensors.initWithAllSensors();
  if (!m_sensors.update())
    return false;
  if (!m_allProcesses.update())
    return false;
  if (!m_processor.update())
    return false;
  if (!m_ram.update())
    return false;

  m_initialized = true;

  return Info::update();
}

bool ComputerInfo::update(const std::string& strFromNet)
{
  istringstream iss(strFromNet);
  string componentString;

  while (iss)
  {
    getline(iss, componentString);

    if (componentString.find("Component Type:Processor;") == 0)
      if (!m_processor.update(componentString))
      {
        std::cout << "processor" << std::endl;
        return false;
      }

    if (componentString.find("|Component Type:Process;") == 0)
      if (!m_allProcesses.update(componentString))
      {
        std::cout << "process" << std::endl;
        return false;
      }

    if (componentString.find("|Component Type:Sensor;") == 0)
      if (!m_sensors.update(componentString))
      {
        std::cout << "sensor" << std::endl;
        return false;
      }

    if (componentString.find("Component Type:RAM;") == 0)
      if (!m_ram.update(componentString))
      {
        std::cout << "ram" << std::endl;
        return false;
      }

    if (componentString.find("Data updated:") == 0)
    {
      string keyName, value;
      istringstream issValue(componentString);

      getline(issValue, keyName, ':');
      getline(issValue, value, ';');

      if (!updateTime(value))
        return false;
    }
  }

  return true;
}

std::string ComputerInfo::toString(unsigned flags) const
{
  std::ostringstream oss;

  oss << processor().toString() << std::endl;
  oss << ram().toString() << std::endl;
  oss << allProcesses().toString() << std::endl;
  oss << allSensors().toString() << std::endl;

  oss << "Data updated:" << chrono::system_clock::to_time_t(lastUpdated())
      << ";" << std::endl;
  return oss.str();
}

void ComputerInfo::clear()
{
  m_processor.clear();
  m_ram.clear();
  m_allProcesses.clear();
  m_sensors.clear();
  m_initialized = false;
}
