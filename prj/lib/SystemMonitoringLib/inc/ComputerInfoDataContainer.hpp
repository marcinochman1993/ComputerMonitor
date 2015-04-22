/*
 * ComputerInfoDataContainer.hpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFODATACONTAINER_HPP_
#define COMPUTERINFODATACONTAINER_HPP_

#include <map>
#include "ComputerInfo.hpp"

class ComputerInfoDataContainer: public Info
{
  public:
    ComputerInfoDataContainer(ComputerInfo* computerInfo = nullptr):m_computerInfo(computerInfo) { }
//    const std::vector<double>& frequencyData(int coreNum = 0) const;
//    const std::vector<double>& sensorsData(int sensorNum=0) const;
    // time() const;
    bool update() override;
    const ComputerInfo& computerInfo() const { return *m_computerInfo; }
  private:
    std::map<unsigned, std::vector<double>> m_frequency;
    std::map<unsigned, std::vector<double>> m_sensorsValues;
    ComputerInfo* m_computerInfo;
};

#endif /* COMPUTERINFODATACONTAINER_HPP_ */
