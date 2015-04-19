/*
 * ProcessorInfo.hpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORLIB_PROCESSORINFO_HPP_
#define COMPUTERMONITORLIB_PROCESSORINFO_HPP_

#include "HardwareInfo.hpp"


class ProcessorInfo: public HardwareInfo
{
	public:
		double frequency(unsigned int coreNum) const;
		double maxFrequency(unsigned int coreNum) const;
		std::string name() const override { return m_name; }
		double usage(unsigned int coreNum) const;
	private:
		std::string m_name;
};

#endif /* COMPUTERMONITORLIB_PROCESSORINFO_HPP_ */
