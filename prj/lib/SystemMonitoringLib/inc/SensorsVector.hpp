/*
 * SensorsVector.hpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#ifndef SENSORSVECTOR_HPP_
#define SENSORSVECTOR_HPP_

#include <vector>
#include "SensorInfo.hpp"

class SensorsVector: public std::vector<SensorInfo>, public Info
{
  public:
    SensorsVector(const std::vector<SensorInfo>& sensors):std::vector<SensorInfo>(sensors) { }
    bool update() override;
};


#endif /* SENSORSVECTOR_HPP_ */
