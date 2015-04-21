/*
 * HardwareInfo.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef HARDWAREINFO_HPP_
#define HARDWAREINFO_HPP_

#include <string>
#include "Info.hpp"

class HardwareInfo: public Info
{
  public:
    virtual std::string name() const { return std::string(); }
};

#endif /* HARDWAREINFO_HPP_ */
