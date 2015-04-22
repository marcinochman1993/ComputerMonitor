/*
 * ComputerInfoDataContainer.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainer.hpp"

bool ComputerInfoDataContainer::update()
{
  m_computerInfo->update();
  m_time.push_back(m_computerInfo->lastUpdated());
  if (m_sensorsValues.empty())
    init();

  int i = 0;
  for (auto& sensor : m_sensorsValues)
  {
    sensor.second.push_back(computerInfo().allSensors()[i].value());
    i++;
  }

  return Info::update();
}

void ComputerInfoDataContainer::init()
{
  const SensorsVector& allSensors = computerInfo().allSensors();
  if (m_sensorsValues.size() != allSensors.size())
  {
    m_sensorsValues.clear();
    for (unsigned i = 0; i < allSensors.size(); i++)
      m_sensorsValues.insert(std::make_pair(i, std::vector<double>()));
  }
}

const std::vector<double>& ComputerInfoDataContainer::sensorsData(
    int sensorNum) const
{
  if (sensorNum >= m_sensorsValues.size())
    throw "There's no sensor with that index";

  auto it = m_sensorsValues.find(sensorNum);

  if (it == m_sensorsValues.end())
    throw "There's no sensor with that index";

  return it->second;
}
