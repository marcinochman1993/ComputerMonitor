/*
 * SensorsVector.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "SensorsVector.hpp"
#include <sstream>

bool SensorsVector::update()
{
  for (auto& sensor : *this)
    if (!sensor.update())
      return false;

  return true;

}

std::string SensorsVector::toString(unsigned flags) const
{
  std::ostringstream oss;

  for (const auto& sensor : *this)
  {
    oss << "|" << sensor.toString() << "|";
  }

  return oss.str();
}
