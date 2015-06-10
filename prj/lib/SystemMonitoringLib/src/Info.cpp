/*
 * Info.cpp
 *
 *  Created on: Jun 7, 2015
 *      Author: mochman
 */

#include "Info.hpp"
#include <sstream>
#include <iostream>
using namespace std;

std::string Info::toString(unsigned flags) const
{
  ostringstream oss;

  oss << "Data updated:" << chrono::system_clock::to_time_t(m_lastUpdated)
      << ";";

  return oss.str();
}

bool Info::update(const std::string& strFromNet)
{

  istringstream iss(strFromNet);
  string keyName, value;

  getline(iss, keyName, ':');
  getline(iss, value, ';');

  std::time_t lastDataUpdated;

  std::cout << value << std::endl;

  if (keyName == "Data updated")
  {
    char* pEnd = nullptr;
    lastDataUpdated = strtol(value.c_str(), &pEnd, 10);
    if (!*pEnd)
      m_lastUpdated = std::chrono::system_clock::from_time_t(lastDataUpdated);
    else
      return false;
  }
  else
    return false;

  return iss;
}

bool Info::updateTime(const std::string& time)
{
  char* pEnd = nullptr;
  long numTime = strtol(time.c_str(), &pEnd, 10);
  if (!*pEnd)
    m_lastUpdated = std::chrono::system_clock::from_time_t(
        static_cast<std::time_t>(numTime));

}
