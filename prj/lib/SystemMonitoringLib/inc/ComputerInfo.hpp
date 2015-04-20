/*
 * ComputerInfo.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFO_HPP_
#define COMPUTERINFO_HPP_

#include "Info.hpp"
#include "SensorInfo.hpp"

class ComputerInfo: public Info
{
  public:
    //bool update() override;
    static const std::vector<SensorInfo>& allSensors() { return SensorInfo::allSensors(); }
};


#endif /* COMPUTERINFO_HPP_ */
