/*
 * Info.cpp
 *
 *  Created on: Jun 7, 2015
 *      Author: mochman
 */

#include "Info.hpp"
#include <sstream>

using namespace std;

std::string Info::toString(unsigned flags) const
{
  ostringstream oss;

  oss << "Data updated: " << chrono::system_clock::to_time_t(m_lastUpdated)<< "; ";

  return oss.str();
}

bool Info::update(const std::string& strFromNet)
{

  istringstream iss;


//  iss>>

  return iss;
}

