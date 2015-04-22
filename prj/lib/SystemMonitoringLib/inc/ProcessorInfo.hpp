/*
 * ProcessorInfo.hpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#ifndef PROCESSORINFO_HPP_
#define PROCESSORINFO_HPP_

#include <vector>
#include <fstream>
#include "HardwareInfo.hpp"


class ProcessorInfo: public HardwareInfo
{
	public:
		double frequency(unsigned int coreNum) const;
		std::string name() const override { return m_name; }
		double usage(unsigned int coreNum) const;
		unsigned int coresNumber() const;
		bool update() override;
	private:
		bool parseCoreInfo(std::ifstream& procInfoFile);
		std::string m_name;
		std::vector<double> m_usage;
		std::vector<double> m_freq;
};

#endif /* PROCESSORINFO_HPP_ */
