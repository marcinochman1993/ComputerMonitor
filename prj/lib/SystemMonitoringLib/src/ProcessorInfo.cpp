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
#include <iostream> // todo usunąć
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
  while (statFile && toRead)
  {
    string line;
    getline(statFile, line);
    istringstream is(line);
    unsigned user, nice, system, idle;
    string type;
    is >> type;
    if (type.find("cpu") == 0 && type != "cpu") // wykryto wpis o cpu
    {
      is >> user >> nice >> system >> idle;
      unsigned totalTime = user + nice + system + idle, busyTime = user + nice
        + system;
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
      m_usage[coreId] = usagePercent;
      coreId++;
      if (coreId >= coresNumber())
        toRead = false;
    }
  }
  return true;
}

