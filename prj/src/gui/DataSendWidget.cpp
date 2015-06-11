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
  initToStringStruct();
}

void DataSendWidget::initToStringStruct()
{
  m_toStringStruct.processesFlags = ProcessInfo::ALL;
  m_toStringStruct.processorFlags = ProcessorInfo::ALL;
  m_toStringStruct.ramFlags = RamInfo::ALL;
  m_toStringStruct.sensorsFlags = SensorInfo::ALL;
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
    processParentDataSendOptions(item);
  else
  {
    QString parentText = parent->text(column), itemText = item->text(column);
    item->checkState(column);

    if (parentText == "Processes")
      processProcessesDataSendOptions(itemText,
          item->checkState(0) == Qt::Checked);

    if (parentText == "Processor")
      processProcessorDataSendOptions(itemText,
          item->checkState(0) == Qt::Checked);

    if (parentText == "RAM")
      processRamDataSendOptions(itemText, item->checkState(0) == Qt::Checked);

    if (parentText == "Sensors")
      processSensorsDataSendOptions(itemText,
          item->checkState(0) == Qt::Checked);
  }
}

void DataSendWidget::processParentDataSendOptions(QTreeWidgetItem * parentItem)
{
  QList<QTreeWidgetItem*> children = parentItem->takeChildren();

  for (auto& item : children)
  {
    if (item->checkState(0) == Qt::Checked)
      item->setCheckState(0, Qt::Unchecked);
    else
      item->setCheckState(0, Qt::Checked);
  }

  parentItem->addChildren(children);
}

void DataSendWidget::processProcessorDataSendOptions(const QString& itemText,
    bool checked)
{
  std::cout << itemText.toStdString() << std::endl;

  if (itemText == "Name")
  {
    if (checked)
      m_toStringStruct.processorFlags |= ProcessorInfo::NAME;
    else
      m_toStringStruct.processorFlags &= ~ProcessorInfo::NAME;
  }

  if (itemText == "Frequency")
  {
    if (checked)
      m_toStringStruct.processorFlags |= ProcessorInfo::CORE_FREQ;
    else
      m_toStringStruct.processorFlags &= ~ProcessorInfo::CORE_FREQ;
  }

  if (itemText == "Core Usage")
  {
    if (checked)
      m_toStringStruct.processorFlags |= ProcessorInfo::CORE_USAGE;
    else
      m_toStringStruct.processorFlags &= ~ProcessorInfo::CORE_USAGE;
  }

  if (itemText == "Total Cpu Usage")
  {
    if (checked)
      m_toStringStruct.processorFlags |= ProcessorInfo::TOTAL_USAGE;
    else
      m_toStringStruct.processorFlags &= ~ProcessorInfo::TOTAL_USAGE;
  }

}

void DataSendWidget::processProcessesDataSendOptions(const QString& itemText,
    bool checked)
{
  std::cout << itemText.toStdString() << std::endl;
  if (itemText == "Name")
  {
    if (checked)
      m_toStringStruct.processesFlags |= ProcessInfo::NAME;
    else
      m_toStringStruct.processesFlags &= ~ProcessInfo::NAME;
  }

  if (itemText == "Id")
  {
    if (checked)
      m_toStringStruct.processesFlags |= ProcessInfo::ID;
    else
      m_toStringStruct.processesFlags &= ~ProcessInfo::ID;
  }

  if (itemText == "Cpu Usage")
  {
    if (checked)
      m_toStringStruct.processesFlags |= ProcessInfo::CPU_USAGE;
    else
      m_toStringStruct.processesFlags &= ~ProcessInfo::CPU_USAGE;
  }
}

void DataSendWidget::processRamDataSendOptions(const QString& itemText,
    bool checked)
{
  std::cout << itemText.toStdString() << std::endl;
  if (itemText == "Total Memory Usage")
  {
    if (checked)
      m_toStringStruct.ramFlags |= RamInfo::TOTAL_USAGE;
    else
      m_toStringStruct.ramFlags &= ~RamInfo::TOTAL_USAGE;
  }
}

void DataSendWidget::processSensorsDataSendOptions(const QString& itemText,
    bool checked)
{
  std::cout << itemText.toStdString() << std::endl;
  if (itemText == "Name")
  {
    if (checked)
      m_toStringStruct.sensorsFlags |= SensorInfo::NAME;
    else
      m_toStringStruct.sensorsFlags &= ~SensorInfo::NAME;
  }

  if (itemText == "Value")
  {
    if (checked)
      m_toStringStruct.sensorsFlags |= SensorInfo::VALUE;
    else
      m_toStringStruct.sensorsFlags &= ~SensorInfo::VALUE;
  }
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
  dataSendTree->setEnabled(false);
}

void DataSendWidget::stoppedServer()
{
  serverStatusLabel->setText(tr("Stopped"));
  serverButton->setText(tr("Start"));
  dataSendTree->setEnabled(true);
}

void DataSendWidget::changeServerButtonStatus()
{
  QRegExp ipRegEx("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");

  if (ipRegEx.exactMatch(ipAddressLineEdit->text())
    && !portLineEdit->text().isEmpty())
    serverButton->setEnabled(true);
  else
    serverButton->setEnabled(false);
}

unsigned DataSendWidget::port() const
{
  return portLineEdit->text().toUInt();
}
