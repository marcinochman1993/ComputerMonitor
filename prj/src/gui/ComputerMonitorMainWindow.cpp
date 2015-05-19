/*
 * ComputerMonitorMainWindow.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindow.hpp"
#include <QMessageBox>

void ComputerMonitorMainWindow::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  sensorsWidget->computerInfoData(compInfo);
  processesWidget->computerInfoData(compInfo);
  processorWidget->computerInfoData(compInfo);
  ramWidget->computerInfoData(compInfo);
}

void ComputerMonitorMainWindow::closeEvent(QCloseEvent * closeEventData)
{
  QMessageBox::StandardButtons chosenButton = QMessageBox::question(this,
      tr("Closing application"), tr("Do you really want to quit application"),
      QMessageBox::Yes | QMessageBox::No);

  if (chosenButton == QMessageBox::No)
    closeEventData->ignore();
}
