/*
 * SensorInfo.cpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#include <cstring>
#include "SensorInfo.hpp"
#include <sstream>

using namespace std;

vector<SensorInfo> SensorInfo::s_sensorsVector;

std::string convertTypeToString(const SensorType& sensorType)
{
  int i = static_cast<int>(sensorType);
  std::string texts[] = { "V", "deg C" };

  return texts[i];
}

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

bool SensorInfo::update(const string& strFromNet)
{
  istringstream iss(strFromNet);
  string keyName, value;

  while (iss)
  {
    getline(iss, keyName, ':');
    getline(iss, value, ';');

    if (keyName == "Component Type" && value != "Sensor")
      return false;

    if (keyName == "Sensor name")
      m_nameFromNet = value;

    if (keyName == "Value")
    {
      char * pEnd = nullptr;
      double numValue = 0;
      numValue = strtod(value.c_str(), &pEnd);
      if (!*pEnd)
        m_value = numValue;
      else
        return false;
    }

    if (keyName == "Type")
    {
      char * pEnd = nullptr;
      long typeValue = 0;

      typeValue = strtol(value.c_str(), &pEnd, 10);
      if (!*pEnd)
      {
        if (typeValue < 2)
          m_type = static_cast<SensorType>(typeValue);
      }
      else
        return false;
    }

    if (keyName == "Data updated")
      if (!updateTime(value))
        return false;
  }

  return Info::update(iss.str()) && !iss.fail();
}

string SensorInfo::name() const
{
  return
      m_nameFromNet == "" ?
          ((m_chipName == nullptr || m_subfeature == nullptr) ?
              "" :
              std::string(m_chipName->prefix) + "_"
                + std::string(m_subfeature->name)) :
          m_nameFromNet;
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
        if ((subfeature->flags & SENSORS_MODE_R)
          && (((subfeature->type == SENSORS_SUBFEATURE_TEMP_INPUT)
            || (subfeature->type == SENSORS_SUBFEATURE_IN_INPUT))
            || (subfeature->type == SENSORS_SUBFEATURE_POWER_INPUT)
            || (subfeature->type == SENSORS_SUBFEATURE_FAN_INPUT))) // sprawdzenie czy wartość można odczytać
        {
          SensorType sensorType;
          switch (subfeature->type)
          {
            case SENSORS_SUBFEATURE_TEMP_INPUT:
              sensorType = SensorType::TEMP;
              break;
            case SENSORS_SUBFEATURE_IN_INPUT:
              sensorType = SensorType::VOLTAGE;
              break;
            default:
              break;
          }
          s_sensorsVector.push_back(
              SensorInfo(chipName, subfeature, sensorType));
        }
      }
    }
  }

  return true;
}

std::string SensorInfo::toString(unsigned flags) const
{
  std::ostringstream oss;

  oss << "Component Type: " << "Sensor;";

  if (flags == 0)
    flags = ALL;
  if (flags & NAME)
    oss << "Sensor name:" << name() << ";";
  if (flags & VALUE)
    oss << "Value:" << value() << ";";
  if (flags & TYPE)
    oss << "Type:" << static_cast<int>(m_type) << ";";

  oss << HardwareInfo::toString();

  return oss.str();
}

std::ostream& operator<<(std::ostream& os, const SensorInfo& sensor)
{
  os << sensor.name() << ":" << sensor.value();
  return os;
}
