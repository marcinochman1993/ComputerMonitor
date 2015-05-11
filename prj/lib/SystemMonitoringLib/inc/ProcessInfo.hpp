/*
 * ProcessInfo.hpp
 *
 *  Created on: May 3, 2015
 *      Author: mochman
 */

#ifndef PROCESSINFO_HPP_
#define PROCESSINFO_HPP_

#include "Info.hpp"
#include <limits>

class ProcessInfo: public Info
{
  public:
    ProcessInfo()
      :m_id(std::numeric_limits<unsigned>::max()), m_processorUsage(0.0), m_ramUsage(0.0) { }
    double ramUsage() const { return m_ramUsage; }
    double processorUsage() const { return m_processorUsage; }
    unsigned id() const { return m_id; }
    bool update() override;
  private:
    unsigned m_id;
    unsigned m_ramUsage;
    unsigned m_processorUsage;
};


#endif /* PROCESSINFO_HPP_ */
