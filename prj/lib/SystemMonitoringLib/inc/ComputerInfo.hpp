/*
 * ComputerInfo.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFO_HPP_
#define COMPUTERINFO_HPP_

#include "Info.hpp"
#include "SensorsVector.hpp"
#include "RamInfo.hpp"
#include "ProcessorInfo.hpp"

class ComputerInfo: public Info
{
  public:
    ComputerInfo(): m_sensors(SensorInfo::allSensors()) { }
    bool update() override;
    const SensorsVector& allSensors() const { return m_sensors; }

  private:
    SensorsVector m_sensors;
};


#endif /* COMPUTERINFO_HPP_ */
