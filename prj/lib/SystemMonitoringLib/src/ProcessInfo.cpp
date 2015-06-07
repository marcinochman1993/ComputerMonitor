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
#include <iomanip>

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
  statusFile >> temp; // id

  statusFile >> m_name;
  if (m_name.length() > 2)
    m_name = m_name.substr(1, m_name.length() - 2);

  for (int i = 1; i < 12; i++)
    statusFile >> temp;

  statusFile >> uTime >> sTime;
  uptimeFile >> upTime;
  double cpuUsage = 0.0;

  if (m_lastUpTime > 0 && upTime - m_lastUpTime > 0)
    cpuUsage = (uTime + sTime - m_lastSUTime) / TICKS_PER_SEC
        / (upTime - m_lastUpTime) * 100.0;

  m_lastSUTime = uTime + sTime;
  m_lastUpTime = upTime;
  m_cpuUsage = cpuUsage;

  return Info::update();
}

std::string ProcessInfo::toString(unsigned flags) const
{
  ostringstream oss;

  if (flags == 0)
    flags = ALL;
  if (flags & NAME)
    oss << "Process name: " << name() << "; ";
  if (flags & ID)
    oss << "Id: " << id() << "; ";
  if (flags & CPU_USAGE)
    oss << "CPU_USAGE: " << setprecision(2) << cpuUsage() << "; ";

  return oss.str();
}
