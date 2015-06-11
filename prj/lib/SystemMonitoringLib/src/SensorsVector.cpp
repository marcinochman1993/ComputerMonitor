/*
 * SensorsVector.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#include "SensorsVector.hpp"
#include <sstream>

using namespace std;

bool SensorsVector::update()
{
  for (auto& sensor : *this)
    if (!sensor.update())
      return false;

  return true;

}

bool SensorsVector::update(const std::string& strFromNet)
{
  istringstream iss(strFromNet);
  std::string processInfoStr;

  clear();
  while (iss)
  {
    char c = iss.get();
    if (iss.eof())
      return true;

    if (c != '|')
      return false;

    getline(iss, processInfoStr, '|');
    SensorInfo sensorInfo;

    if (!sensorInfo.update(processInfoStr))
      return false;

    push_back(sensorInfo);

  }
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

void SensorsVector::initWithAllSensors()
{
  *this = SensorInfo::allSensors();
}
