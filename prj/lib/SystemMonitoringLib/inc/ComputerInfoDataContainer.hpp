/*
 * ComputerInfoDataContainer.hpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFODATACONTAINER_HPP_
#define COMPUTERINFODATACONTAINER_HPP_

#include <map>
#include <chrono>
#include "ComputerInfo.hpp"

class ComputerInfoDataContainer: public Info
{
  public:
    ComputerInfoDataContainer(ComputerInfo* computerInfo = nullptr):m_computerInfo(computerInfo) { }
//    const std::vector<double>& frequencyData(int coreNum = 0) const;
    const std::vector<double>& sensorsData(int sensorNum=0) const;
    const std::vector<std::chrono::system_clock::time_point>& time() const { return m_time; }
    bool update() override;
    const ComputerInfo& computerInfo() const { return *m_computerInfo; }
  private:
    void init();

    std::map<unsigned, std::vector<double>> m_frequency;
    std::map<unsigned, std::vector<double>> m_sensorsValues;
    std::vector<std::chrono::system_clock::time_point> m_time;
    ComputerInfo* m_computerInfo;
};

#endif /* COMPUTERINFODATACONTAINER_HPP_ */
