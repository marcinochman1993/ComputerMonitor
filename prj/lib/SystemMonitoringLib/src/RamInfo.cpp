/*
 * RamInfo.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "RamInfo.hpp"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include <sstream>

using namespace std;

bool RamInfo::update()
{
  struct sysinfo memInfo;
  sysinfo(&memInfo);

  long physMemUsed = memInfo.totalram - memInfo.freeram;
  m_totalRamUsage = static_cast<double>(physMemUsed) / memInfo.totalram * 100.0;

  return HardwareInfo::update();
}

bool RamInfo::update(const std::string& strFromNet)
{
  istringstream iss(strFromNet);
  string keyName, value;

  while (iss)
  {
    getline(iss, keyName, ':');
    getline(iss, value, ';');

    if (keyName == "Component Type" && value != "RAM")
      return false;

    if (keyName == "Total usage")
    {
      double numValue;
      char* pEnd = nullptr;
      numValue = strtod(value.c_str(), &pEnd);
      if (!*pEnd)
        m_totalRamUsage = numValue;
    }

    if (keyName == "Data updated")
      if (!updateTime(value))
        return false;
  }

  return true;
}

std::string RamInfo::toString(unsigned flags) const
{
  ostringstream oss;

  if (flags == 0)
    flags = ALL;

  oss << "Component Type:RAM;";

  if (flags & TOTAL_USAGE)
    oss << "Total usage:" << totalUsage() << ";";

  oss << Info::toString();

  return oss.str();
}
