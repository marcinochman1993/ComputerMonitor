/*
 * ComputerInfoDataContainer.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainer.hpp"

using namespace std;
using namespace std::chrono;

bool ComputerInfoDataContainer::update()
{
  if (!m_computerInfo->update())
    return false;

  m_time.push_back(m_computerInfo->lastUpdatedTimeT());
  if (m_sensorsValues.empty())
    init();

  saveUpdatedSensorsValueInVec();
  saveUpdatedProcessesValuesInVec();
  saveUpdatedProcessorValues();
  m_totalRamUsage.push_back(m_computerInfo->ram().totalUsage());
  return Info::update();
}

bool ComputerInfoDataContainer::update(const std::string& strFromNet)
{
  if (!m_computerInfo->update(strFromNet))
    return false;

  saveUpdatedSensorsValueInVec();
  saveUpdatedProcessesValuesInVec();
  saveUpdatedProcessorValues();
  m_totalRamUsage.push_back(m_computerInfo->ram().totalUsage());
  m_time.push_back(m_computerInfo->lastUpdatedTimeT());
  return true;
}

void ComputerInfoDataContainer::saveUpdatedSensorsValueInVec()
{
  int i = 0;
  auto allSensors = computerInfo().allSensors();
  if (m_sensorsValues.size() == allSensors.size())
    for (auto& sensor : m_sensorsValues)
    {
      sensor.second.push_back(allSensors[i].value());
      i++;
    }
  else
  {
    m_sensorsValues.clear();
    for (auto& sensor : allSensors)
    {
      DataBuffer<double> buff;
      buff.push_back(sensor.value());
      m_sensorsValues.insert(make_pair(i, move(buff)));
      i++;
    }
  }
}

void ComputerInfoDataContainer::saveUpdatedProcessesValuesInVec()
{
  for (const auto& procPair : computerInfo().allProcesses().processesMap())
  {
    auto it = m_processes.find(procPair.first);
    if (it == m_processes.end())
    {
      vector<DataBuffer<double>> vectorOfValues;
      vectorOfValues.resize(MONITORED_VALUES_NUM);
      vectorOfValues[CPU_INDEX].push_back(procPair.second.cpuUsage());
      DataBuffer<std::time_t> vectorOfTime;
      vectorOfTime.push_back(computerInfo().lastUpdatedTimeT());

      auto innerPair = make_pair(move(vectorOfValues), move(vectorOfTime));

      auto outerPair = make_pair(procPair.first, move(innerPair));

      m_processes.insert(outerPair);
    }
    else
      it->second.first[CPU_INDEX].push_back(procPair.second.cpuUsage());
  }
}

void ComputerInfoDataContainer::saveUpdatedProcessorValues()
{
  const ProcessorInfo& processor = m_computerInfo->processor();
  for (unsigned i = 0; i < m_computerInfo->processor().coresNumber(); i++)
  {
    auto it = m_processorValues.find(i);
    if (it != m_processorValues.end())
    {
      it->second[PROCESSOR_FREQ_INDEX].push_back(processor.frequency(i));
      it->second[PROCESSOR_COREUSAGE_INDEX].push_back(processor.usage(i));
    }
    else
    {
      std::vector<DataBuffer<double>> vectorOfValues;
      vectorOfValues.resize(PROCESSOR_MONITORED_VALUES_NUM);
      vectorOfValues[PROCESSOR_COREUSAGE_INDEX].push_back(processor.usage(i));
      vectorOfValues[PROCESSOR_FREQ_INDEX].push_back(processor.frequency(i));
      m_processorValues.insert(make_pair(i, move(vectorOfValues)));
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
      m_sensorsValues.insert(std::make_pair(i, DataBuffer<double>()));
  }
}

const DataBuffer<double>& ComputerInfoDataContainer::sensorsData(
    unsigned sensorNum) const
{
  std::cout << "size of m_sensorsValues: " << m_sensorsValues.size()
      << std::endl;
  if (sensorNum >= m_sensorsValues.size())
    throw "There's no sensor with that index";

  auto it = m_sensorsValues.find(sensorNum);

  if (it == m_sensorsValues.end())
    throw "There's no sensor with that index";

  return it->second;
}

const DataBuffer<double>& ComputerInfoDataContainer::cpuUsage(
    unsigned processId) const
{
  auto it = m_processes.find(processId);
  if (it != m_processes.end())
    return it->second.first[CPU_INDEX];

  throw "There's no process with that id";
}

const DataBuffer<double>& ComputerInfoDataContainer::coreUsage(
    unsigned coreId) const
{
  auto it = m_processorValues.find(coreId);
  if (it != m_processorValues.end())
    return it->second[PROCESSOR_COREUSAGE_INDEX];

  throw "There's no core with that id";
}

const DataBuffer<double>& ComputerInfoDataContainer::frequency(
    unsigned coreId) const
{
  auto it = m_processorValues.find(coreId);
  if (it != m_processorValues.end())
  {
    return it->second[PROCESSOR_FREQ_INDEX];
  }

  throw "There's no core with that id";
}

void ComputerInfoDataContainer::clearData()
{
  m_frequency.clear();
  m_sensorsValues.clear();
  m_processes.clear();
  m_processorValues.clear();
  m_totalRamUsage.clear();
  m_time.clear();
  m_computerInfo->clear();
}
