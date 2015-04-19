/*
 * SensorInfo.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef SENSORINFO_HPP_
#define SENSORINFO_HPP_

#include <iostream>
#include <vector>
#include <sensors/sensors.h>
#include "HardwareInfo.hpp"

class SensorInfo: public HardwareInfo
{
  public:
    static const std::vector<SensorInfo>& allSensors();
    static void cleanUp() { sensors_cleanup(); }
    SensorInfo(const sensors_chip_name* chipName = nullptr,
        const sensors_subfeature* subfeature = nullptr, double value = -1.0)
        : m_chipName(chipName), m_subfeature(subfeature), m_value(value)
    { }
    bool update() override;
    std::string name() const override { return m_subfeature->name; }
    double value() const { return m_value; }
    ~SensorInfo() { }
  private:
    static bool initAllSensors();
    const sensors_chip_name* m_chipName;
    const sensors_subfeature* m_subfeature;
    double m_value;

    static std::vector<SensorInfo> s_sensorsVector;
};

std::ostream& operator<<(std::ostream& os, const SensorInfo& sensor);

#endif /* SENSORINFO_HPP_ */
