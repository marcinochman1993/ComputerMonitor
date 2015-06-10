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
  if (!m_sensors.update())
    return false;
  if (!m_allProcesses.update())
    return false;
  if (!m_processor.update())
    return false;
  if (!m_ram.update())
    return false;
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
        return false;

    if (componentString.find("|Component Type:Process;") == 0)
      if (!m_allProcesses.update(componentString))
      {
        std::cout << "UPS\n";
        return false;
      }

    if (componentString.find("|Component Type:Sensor;") == 0)
      if (!m_sensors.update(componentString))
        return false;

    if (componentString.find("Component Type:RAM;") == 0)
      if (!m_processor.update(componentString))
        return false;
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

  return oss.str();
}
