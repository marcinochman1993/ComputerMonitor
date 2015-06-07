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

bool RamInfo::update()
{
  struct sysinfo memInfo;
  sysinfo(&memInfo);

  long physMemUsed = memInfo.totalram - memInfo.freeram;
  m_totalRamUsage = static_cast<double>(physMemUsed) / memInfo.totalram * 100.0;

  return HardwareInfo::update();
}

std::string RamInfo::toString(unsigned flags) const
{
  std::ostringstream oss;

  if(flags == 0)
    flags = ALL;

  oss << "Component Type: RAM; ";

  if (flags & TOTAL_USAGE)
    oss << "Total usage: " << totalUsage() << "; ";

  return oss.str();
}
