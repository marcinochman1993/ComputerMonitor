/*
 * SensorsVector.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "SensorsVector.hpp"

bool SensorsVector::update()
{
  for (auto& sensor : *this)
    if (!sensor.update())
      return false;

  return true;

}

