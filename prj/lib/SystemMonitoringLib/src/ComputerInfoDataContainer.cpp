/*
 * ComputerInfoDataContainer.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainer.hpp"

bool ComputerInfoDataContainer::update()
{
  if (!m_computerInfo->update())
    return false;

  m_time.push_back(m_computerInfo->lastUpdated());
  if (m_sensorsValues.empty())
    init();

  saveUpdatedSensorsValueInVec();
  saveUpdatedProcessesValuesInVec();

  return Info::update();
}

void ComputerInfoDataContainer::saveUpdatedSensorsValueInVec()
{
  int i = 0;
  for (auto& sensor : m_sensorsValues)
  {
    sensor.second.push_back(computerInfo().allSensors()[i].value());
    i++;
  }
}

void ComputerInfoDataContainer::saveUpdatedProcessesValuesInVec()
{
  for (const auto& procPair : computerInfo().allProcesses().processesMap())
  {
    auto it = m_ramUsage.find(procPair.first);
    if (it == m_ramUsage.end())
    {
    }
    else
    {

    }
  }
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
    unsigned sensorNum) const
{
  if (sensorNum >= m_sensorsValues.size())
    throw "There's no sensor with that index";

  auto it = m_sensorsValues.find(sensorNum);

  if (it == m_sensorsValues.end())
    throw "There's no sensor with that index";

  return it->second;
}

const std::vector<double>& ComputerInfoDataContainer::ramUsage(
    unsigned processId) const
{

  auto it = m_ramUsage.find(processId);
  if (it != m_ramUsage.end())
    return it->second.first[RAM_INDEX];

  throw "There's no process with that id";
}
