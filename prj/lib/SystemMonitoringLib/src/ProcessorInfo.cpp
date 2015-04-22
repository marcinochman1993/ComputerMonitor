/*
 * ProcessorInfo.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#include <sstream>
#include "ProcessorInfo.hpp"
#include <set>
using namespace std;

double ProcessorInfo::frequency(unsigned int coreNum) const
{
  if (coreNum >= coresNumber())
    throw "Processor hasn't got so many cores";

  return m_freq[coreNum];
}

unsigned int ProcessorInfo::coresNumber() const
{
  return 4; //todo zaimplementować
}

bool ProcessorInfo::update()
{
  ifstream procInfoFile("/proc/cpuinfo");
  if (!procInfoFile)
    return false;
  std::set<int> repeatedCores;
  while (procInfoFile)
  {
    string line;
    getline(procInfoFile, line);
    int coreId = -1;
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
          repeatedCores.insert(coreId);
      }
      getline(procInfoFile, line);
    }

    if (m_freq.size() < coreId)
      m_freq.push_back(frequency);
  }

  return HardwareInfo::update();
}

bool ProcessorInfo::parseCoreInfo(ifstream& procInfoFile)
{
  return true;
}
