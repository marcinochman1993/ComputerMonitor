/*
 * AllProcessesInfo.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "AllProcessesInfo.hpp"
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <utility>
#include <sstream>

using namespace boost::filesystem;
using namespace std;

const ProcessInfo& AllProcessesInfo::process(unsigned int id) const
{
  auto it = m_processesMap.find(id);
  if (it != m_processesMap.end())
    return it->second;
  throw "There is no process with that id";
}

bool AllProcessesInfo::containsProcess(unsigned int id) const
{
  return m_processesMap.find(id) != m_processesMap.end();
}

bool AllProcessesInfo::removeProcess(unsigned int id)
{
  return m_processesMap.erase(id) > 0;
}

bool AllProcessesInfo::update()
{
  path procDir("/proc");
  if (!exists(procDir))
    return false;

  m_lastAddedProcesses.clear();
  m_lastDeletedProcesses.clear();
  map<unsigned, bool> processesMapDeletedStatus;
  getAllKeys(processesMapDeletedStatus);
  for (auto it = directory_iterator(procDir); it != directory_iterator(); it++)
  {
    char* errorPtr = nullptr;
    long procId = strtol(basename(it->path()).c_str(), &errorPtr, 10);
    if (!*errorPtr)
    {
      auto returnPair = m_processesMap.insert(
          make_pair(procId, ProcessInfo(procId)));
      if (returnPair.second)
        m_lastAddedProcesses.push_back(procId);
      else
        processesMapDeletedStatus[procId] = false;
    }
  }

  for (const auto& it : processesMapDeletedStatus)
    if (it.second)
    {
      m_lastDeletedProcesses.push_back(it.first);
      m_processesMap.erase(it.first);
    }

  for (auto& it : m_processesMap)
    it.second.update();

  return Info::update();
}

void AllProcessesInfo::getAllKeys(std::map<unsigned, bool>& keysVec) const
{
  keysVec.clear();
  for (const auto& processPair : m_processesMap)
    keysVec.insert(make_pair(processPair.first, true));
}

std::string AllProcessesInfo::toString(unsigned flags) const
{
  std::ostringstream oss;

  for(const auto& procPair: processesMap())
  {
    const ProcessInfo& procInfo = procPair.second;
    oss<<"|"<<procInfo.toString()<<"|";
  }

  return oss.str();
}

