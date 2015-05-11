/*
 * ComputerInfoDataContainerWrapper.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainerWrapper.hpp"

bool ComputerInfoDataContainerWrapper::update()
{
  if (m_dataContainer->update() && Info::update())
  {
    emit dataUpdated();
    return true;
  }
  return false;
}

