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
  initValidation();
}

void ComputerMonitorMainWindowSend::initValidation()
{
  QString ipSegment = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp ipRegex(
      "^" + ipSegment + "\\." + ipSegment + "\\." + ipSegment + "\\."
        + ipSegment + "$");
  QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

  ipAddressLineEdit->setValidator(ipValidator);
}

void ComputerMonitorMainWindowSend::closeEvent(QCloseEvent* closeEventArgs)
{
  QMessageBox::StandardButtons chosenButton = QMessageBox::question(this,
      tr("Closing application"), tr("Do you really want to quit application"),
      QMessageBox::Yes | QMessageBox::No);

  if (chosenButton == QMessageBox::No)
    closeEventArgs->ignore();
}
