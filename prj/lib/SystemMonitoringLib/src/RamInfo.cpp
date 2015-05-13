/*
 * RamInfo.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "RamInfo.hpp"
#include "sys/types.h"
#include "sys/sysinfo.h"

bool RamInfo::update()
{
  struct sysinfo memInfo;
  sysinfo(&memInfo);

  long physMemUsed = memInfo.totalram - memInfo.freeram;
  m_totalRamUsage = static_cast<double>(physMemUsed) / memInfo.totalram * 100.0;

  return HardwareInfo::update();
}
