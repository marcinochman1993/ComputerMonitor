/*
 * DataSendWidget.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: mochman
 */

#include "DataSendWidget.hpp"
#include <iostream>

void DataSendWidget::init()
{
  setupUi(this);
  initValidation();
}

void DataSendWidget::initValidation()
{
  QString ipSegment = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
  QRegExp ipRegex(
      "^" + ipSegment + "\\." + ipSegment + "\\." + ipSegment + "\\."
        + ipSegment + "$");
  QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

  ipAddressLineEdit->setValidator(ipValidator);

  QIntValidator* portValidator = new QIntValidator();
  portValidator->setBottom(0);

  portLineEdit->setValidator(portValidator);
}

void DataSendWidget::on_dataSendTree_itemChanged(QTreeWidgetItem * item,
    int column)
{
  QTreeWidgetItem* parent = item->parent();

  if (parent == nullptr)
    return;

  QString parentText = parent->text(column), itemText = item->text(column);
  std::cout << parentText.toStdString() << " " << itemText.toStdString()
      << std::endl;
}

void DataSendWidget::connectionEstablished()
{
  connectionStatusLabel->setText(tr("Connected"));
}

void DataSendWidget::connectionLost()
{
  connectionStatusLabel->setText(tr("Disconnected"));
}

void DataSendWidget::startedServer()
{
  serverStatusLabel->setText(tr("Running"));
  serverButton->setText(tr("Stop"));
}

void DataSendWidget::stoppedServer()
{
  serverStatusLabel->setText(tr("Stopped"));
  serverButton->setText(tr("Start"));
}
