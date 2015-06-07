/*
 * ComputerMonitorMainWindowSend.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindowSend.hpp"
#include <QCloseEvent>
#include <QMessageBox>

void ComputerMonitorMainWindowSend::init()
{
  setupUi(this);
  initThemeActions(menuOptions);
}

void ComputerMonitorMainWindowSend::closeEvent(QCloseEvent* closeEventArgs)
{
  QMessageBox::StandardButtons chosenButton = QMessageBox::question(this,
      tr("Closing application"), tr("Do you really want to quit application"),
      QMessageBox::Yes | QMessageBox::No);

  if (chosenButton == QMessageBox::No)
    closeEventArgs->ignore();
}


