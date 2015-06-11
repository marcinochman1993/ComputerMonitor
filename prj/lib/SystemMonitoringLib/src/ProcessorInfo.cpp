/*
 * ProcessorInfo.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#include <sstream>
#include "ProcessorInfo.hpp"
#include <map>
#include <set>
#include <iostream>
using namespace std;

double ProcessorInfo::frequency(unsigned int coreNum) const
{
  if (coreNum >= coresNumber())
    throw "Processor hasn't got so many cores";

  return m_freq[coreNum];
}

double ProcessorInfo::usage(unsigned int coreNum) const
{
  if (coreNum < m_usage.size())
    return m_usage[coreNum];
  throw "There's no core with that id";
}

bool ProcessorInfo::update()
{
  if (!parseCpuInfoFile())
    return false;
  if (!parseCpuStatFile())
    return false;
  return HardwareInfo::update();
}

bool ProcessorInfo::update(const std::string& strFromNet)
{
  istringstream iss(strFromNet);
  string keyName, value, coreNum;

  while (iss)
  {
    getline(iss, keyName, ':');
    if (keyName.find('(') == 0)
    {
      getline(iss, coreNum, ':');
      getline(iss, value, ')');
      iss.get(); // skip ;
    }
    else
      getline(iss, value, ';');

    if (keyName.find('(') == 0)
      parseCoreInfo(keyName.substr(1), coreNum, value);

    if (keyName == "Component Type" && value != "Processor")
      return false;

    if (keyName == "Processor name")
      m_name = value;

    if (keyName == "Cores number")
    {
      char* pEnd = nullptr;
      long numValue = strtol(value.c_str(), &pEnd, 10);
      if (!*pEnd)
      {
        m_coresNum = numValue;
        m_freq.resize(m_coresNum);
        m_usage.resize(m_coresNum);
      }
      else
        return false;
    }

    if (keyName == "Total usage")
    {
      char* pEnd = nullptr;
      double numValue = strtod(value.c_str(), &pEnd);
      if (!*pEnd)
        m_totalCpuUsage = numValue;
    }

    if (keyName == "Data updated")
      if (!updateTime(value))
        return false;
  }

  return true;
}

bool ProcessorInfo::parseCoreInfo(const std::string& componentName,
    const std::string& coreNumStr, const std::string& value)
{
  char* pEnd = nullptr;
  long coreNum = strtol(coreNumStr.c_str(), &pEnd, 10);
  if (*pEnd)
    return false;

  pEnd = nullptr;
  double numValue = strtold(value.c_str(), &pEnd);
  if (*pEnd)
    return false;

  if (componentName == "Core Frequency")
  {
    if (coreNum < coresNumber())
      m_freq[coreNum] = numValue;
    else
      return false;
  }

  if (componentName == "Core Usage")
  {
    if (coreNum < coresNumber())
      m_usage[coreNum] = numValue;
    else
      return false;
  }

  return true;
}

bool ProcessorInfo::parseCpuInfoFile()
{
  ifstream procInfoFile("/proc/cpuinfo");
  if (!procInfoFile)
    return false;
  std::map<unsigned, double> repeatedCores;
  while (procInfoFile)
  {
    string line;
    getline(procInfoFile, line);
    unsigned coreId;
    double frequency;
    while (!line.empty())
    {
      istringstream iss(line);
      string paramName;
      getline(iss, paramName, ':');

      if (paramName.find("cpu MHz") != string::npos)
        iss >> frequency;
      if (paramName.find("core id") != string::npos)
      {
        iss >> coreId;

        if (repeatedCores.find(coreId) == repeatedCores.end())
          repeatedCores.insert(make_pair(coreId, frequency));
      }
      getline(procInfoFile, line);
    }
  }
  m_coresNum = repeatedCores.size();
  m_freq.resize(coresNumber());
  for (const auto& it : repeatedCores)
    m_freq[it.first] = it.second;
  return true;
}

bool ProcessorInfo::parseCpuStatFile()
{
  ifstream statFile("/proc/stat");
  bool toRead = true;
  std::set<int> repeatedCores;
  unsigned coreId = 0;
  string line, type;
  getline(statFile, line);
  istringstream isTotalCpuInfo(line);
  unsigned user, nice, system, idle;
  isTotalCpuInfo >> type;
  isTotalCpuInfo >> user >> nice >> system >> idle;
  unsigned totalTime = user + nice + system + idle, busyTime = user + nice
    + system;
  if (m_lastTotalCpuTime == 0)
  {
    m_totalCpuUsage = 0.0;
  }
  else
  {
    if (totalTime - m_lastTotalCpuTime <= 0)
      m_totalCpuUsage = 0.0;
    else
      m_totalCpuUsage = (busyTime - m_lastTotalCpuBusyTime)
        / (totalTime - m_lastTotalCpuTime) * 100.0;
  }
  m_lastTotalCpuBusyTime = busyTime;
  m_lastTotalCpuTime = totalTime;

  while (statFile && toRead) // czyta informacje o rdzeniach
  {
    getline(statFile, line);
    istringstream is(line);
    is >> type;
    if (type.find("cpu") == 0 && type != "cpu") // wykryto wpis o cpu
    {
      is >> user >> nice >> system >> idle;
      totalTime = user + nice + system + idle, busyTime = user + nice + system;
      double usagePercent = 0;
      if (m_lastBusyTime.size() == 0)
        m_lastBusyTime.resize(coresNumber(), 0);
      if (m_lastTotalTime.size() == 0)
        m_lastTotalTime.resize(coresNumber(), 0);
      if (m_lastBusyTime[coreId] > 0.0 && m_lastTotalTime[coreId] > 0.0)
        usagePercent = (busyTime - m_lastBusyTime[coreId])
          / static_cast<double>(totalTime - m_lastTotalTime[coreId]) * 100.0;

      m_lastBusyTime[coreId] = busyTime;
      m_lastTotalTime[coreId] = totalTime;
      if (m_usage.size() == 0)
        m_usage.resize(coresNumber());
      if (usagePercent > 100.0)
        usagePercent = 100;
      m_usage[coreId] = usagePercent;
      coreId++;
      if (coreId >= coresNumber())
        toRead = false;
    }
  }
  return true;
}

std::string ProcessorInfo::toString(unsigned flags) const
{
  std::ostringstream oss;
  if (flags == 0)
    flags = ALL;

  oss << "Component Type:Processor;";

  if (flags & NAME)
    oss << "Processor name:" << name() << ";";

  if (flags & CORES_NUM)
    oss << "Cores number:" << coresNumber() << ";";

  if (flags & TOTAL_USAGE)
    oss << "Total usage:" << totalUsage() << ";";

  if (flags & CORE_FREQ)
  {
    for (unsigned i = 0; i < coresNumber(); i++)
      oss << "(Core Frequency:" << i << ":" << frequency(i) << ");";
  }

  if (flags & CORE_USAGE)
  {
    for (unsigned i = 0; i < coresNumber(); i++)
      oss << "(Core Usage:" << i << " :" << usage(i) << ");";
  }

  oss << HardwareInfo::toString();

  return oss.str();
}

void ProcessorInfo::clear()
{
  m_coresNum = 0;
  m_freq.clear();
  m_totalCpuUsage = 0.0;
  m_usage.clear();
}
