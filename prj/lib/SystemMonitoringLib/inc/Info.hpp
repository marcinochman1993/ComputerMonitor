/*
 * Info.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef INFO_HPP_
#define INFO_HPP_

#include <chrono>


class Info
{
  public:
    virtual bool update() {  m_lastUpdated=std::chrono::system_clock::now(); return true; };
    virtual const std::chrono::system_clock::time_point & lastUpdated() const { return m_lastUpdated; };
    virtual ~Info() { }
  private:
    std::chrono::system_clock::time_point m_lastUpdated;
};



#endif /* INFO_HPP_ */
