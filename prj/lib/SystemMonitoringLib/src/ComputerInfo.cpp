/*
 * ComputerInfo.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "ComputerInfo.hpp"

bool ComputerInfo::update()
{
  if (!m_sensors.update())
    return false;
  if (!m_allProcesses.update())
    return false;
  if (!m_processor.update())
    return false;
  return Info::update();
}

