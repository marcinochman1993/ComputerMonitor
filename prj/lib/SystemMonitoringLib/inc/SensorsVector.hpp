/*
 * SensorsList.hpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#ifndef SENSORSLIST_HPP_
#define SENSORSLIST_HPP_

#include <vector>
#include "SensorInfo.hpp"

class SensorsVector: public std::vector<SensorInfo>, public Info
{
  public:
    bool update() override;
};


#endif /* PRJ_LIB_SYSTEMMONITORINGLIB_INC_SENSORSLIST_HPP_ */
