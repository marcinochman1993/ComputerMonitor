/*
 * ComputerMonitorMainWindow.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindow.hpp"

void ComputerMonitorMainWindow::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  sensorsWidget->computerInfoData(compInfo);
  processesWidget->computerInfoData(compInfo);
  processorWidget->computerInfoData(compInfo);
}

