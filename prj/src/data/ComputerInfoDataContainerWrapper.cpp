/*
 * ComputerInfoDataContainerWrapper.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainerWrapper.hpp"


bool ComputerInfoDataContainerWrapper::update()
{
  m_dataContainer->update();
  emit dataUpdated();
  return Info::update();
}


