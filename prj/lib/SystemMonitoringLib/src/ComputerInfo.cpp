/*
 * ComputerInfo.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "ComputerInfo.hpp"
#include <sstream>

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

std::string ComputerInfo::toString(unsigned flags) const
{
  std::ostringstream oss;

  oss << processor().toString() << std::endl;
  oss << ram().toString() << std::endl;
  oss << allProcesses().toString() << std::endl;
  oss << allSensors().toString() << std::endl;

  return oss.str();
}
