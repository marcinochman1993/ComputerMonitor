/*
 * SensorInfo.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#include <cstring>
#include "SensorInfo.hpp"

using namespace std;

vector<SensorInfo> SensorInfo::s_sensorsVector;

const vector<SensorInfo>& SensorInfo::allSensors()
{
  static bool initialized = false;

  if (!initialized)
  {
    if (initAllSensors())
      initialized = true;
  }

  return s_sensorsVector;
}

bool SensorInfo::update()
{
  return sensors_get_value(m_chipName, m_subfeature->number, &m_value) >= 0;
}

bool SensorInfo::initAllSensors()
{
  if (sensors_init(nullptr) != 0)
    return false;
  const sensors_chip_name* chipName;
  int chipNum = 0;
  while ((chipName = sensors_get_detected_chips(0, &chipNum)) != 0)
  {
    const sensors_feature* feature;
    int featureNum = 0;

    while ((feature = sensors_get_features(chipName, &featureNum)) != 0)
    {
      sensors_subfeature const *subfeature;
      int subfeatureNum = 0;

      while ((subfeature = sensors_get_all_subfeatures(chipName, feature,
          &subfeatureNum)) != 0)
      {
        double value;
        if ((subfeature->flags & SENSORS_MODE_R)
            && (subfeature->type == SENSORS_SUBFEATURE_TEMP_INPUT)) // sprawdzenie czy wartość można odczytać
        {

          if (sensors_get_value(chipName, subfeature->number, &value) < 0)
            s_sensorsVector.push_back(SensorInfo(chipName, subfeature));
          else
            s_sensorsVector.push_back(SensorInfo(chipName, subfeature, value));

        }
      }
    }
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, const SensorInfo& sensor)
{
  os<<sensor.name()<<":"<<sensor.value();
  return os;
}
