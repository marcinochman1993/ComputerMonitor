/*
 * ComputerInfoDataContainerWrapper.cpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#include "ComputerInfoDataContainerWrapper.hpp"

bool ComputerInfoDataContainerWrapper::update()
{
  if (m_dataContainer == nullptr)
    return false;
  if (m_dataContainer->update() && Info::update())
  {
    emit dataUpdated();
    return true;
  }

  return false;
}

bool ComputerInfoDataContainerWrapper::update(const std::string& strFromNet)
{
  if (m_dataContainer == nullptr)
    return false;

  if (m_dataContainer->update(strFromNet))
  {
    emit dataUpdated();
    return true;
  }

  return false;
}

void ComputerInfoDataContainerWrapper::clear()
{
  if (m_dataContainer == nullptr)
    return;

  m_dataContainer->clearData();
}
