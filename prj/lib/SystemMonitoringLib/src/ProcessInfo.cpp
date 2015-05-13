/*
 * ProcessInfo.cpp
 *
 *  Created on: May 3, 2015
 *      Author: mochman
 */

#include "ProcessInfo.hpp"
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <iostream>

using namespace std;

bool ProcessInfo::update()
{
  const double TICKS_PER_SEC = sysconf(_SC_CLK_TCK);
  ostringstream osPathProc;
  osPathProc << "/proc/" << id() << "/stat";
  ifstream uptimeFile("/proc/uptime"), statusFile(osPathProc.str());
  unsigned uTime, sTime;
  double upTime;

  string temp;
  for (int i = 1; i < 14; i++)
    statusFile >> temp;

  statusFile >> uTime >> sTime;
  uptimeFile >> upTime;
  double cpuUsage = 0.0;

  if (m_lastUpTime > 0)
    cpuUsage = (uTime + sTime - m_lastSUTime) / TICKS_PER_SEC
      / (upTime - m_lastUpTime) * 100.0;

  m_lastSUTime = uTime+sTime;
  m_lastUpTime = upTime;
  m_cpuUsage = cpuUsage;

  return Info::update();
}
