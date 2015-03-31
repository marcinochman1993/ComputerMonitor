/*
 * ProcessorInfo.hpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORLIB_PROCESSORINFO_HPP_
#define COMPUTERMONITORLIB_PROCESSORINFO_HPP_

#include <string>

class ProcessorInfo
{
	public:
		double frequency(unsigned int coreNum) const;
		double maxFrequency(unsigned int coreNum) const;
		double voltage(unsigned int coreNum) const;
		double temperature(unsigned int coreNum) const;
		const std::string& name() const { return m_name; }
	private:
		std::string m_name;
};

#endif /* COMPUTERMONITORLIB_PROCESSORINFO_HPP_ */
