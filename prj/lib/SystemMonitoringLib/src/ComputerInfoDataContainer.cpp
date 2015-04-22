/*
 * ComputerInfoDataContainer.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainer.hpp"


bool ComputerInfoDataContainer::update()
{
  m_computerInfo->update();
  return Info::update();
}
