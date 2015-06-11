/*
 * ReceiveInfoWidget.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: mochman
 */

#include "ReceiveInfoWidget.hpp"

void ReceiveInfoWidget::init()
{
  setupUi(this);
  initValidators();

}

void ReceiveInfoWidget::initValidators()
{
  QString ipSegment = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp ipRegex(
      "^" + ipSegment + "\\." + ipSegment + "\\." + ipSegment + "\\."
        + ipSegment + "$");
  QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

  ipLineEdit->setValidator(ipValidator);

  QIntValidator* portValidator = new QIntValidator(this);
  portValidator->setBottom(0);

  portLineEdit->setValidator(portValidator);
}

void ReceiveInfoWidget::connectionEstablished()
{
  statusLabel->setText(tr("Connected"));
  connectButton->setText(tr("Disconnect"));
}

void ReceiveInfoWidget::connectionLost()
{
  statusLabel->setText(tr("Disconnected"));
  connectButton->setText(tr("Connect"));
}
