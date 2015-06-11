/*
 * DataSendWidget.hpp
 *
 *  Created on: Jun 6, 2015
 *      Author: mochman
 */

#ifndef DATASENDWIDGET_HPP_
#define DATASENDWIDGET_HPP_

#include <QWidget>
#include "ui_DataSendWidget.h"
#include "ComputerInfo.hpp"

class DataSendWidget: public QWidget, Ui::DataSendWidgetUi
{
  Q_OBJECT
  public:
    DataSendWidget(QWidget* parent = nullptr)
        : QWidget(parent) { init(); }

    QString ipAddress() const { return ipAddressLineEdit->text(); }
    unsigned port() const;

    ComputerInfo::ToStringStruct toStringStruct() const { return m_toStringStruct; }

  public slots:
    void connectionEstablished();
    void connectionLost();
    void startedServer();
    void stoppedServer();
  protected slots:
    void on_dataSendTree_itemChanged(QTreeWidgetItem * item, int column);
    void on_ipAddressLineEdit_textChanged(const QString & text) { changeServerButtonStatus(); }
    void on_portLineEdit_textChanged(const QString & text) { changeServerButtonStatus(); }
  private:
    void init();
    void initValidation();
    void initToStringStruct();
    void changeServerButtonStatus();
    void processProcessorDataSendOptions(const QString& itemText, bool checked);
    void processProcessesDataSendOptions(const QString& itemText, bool checked);
    void processRamDataSendOptions(const QString& itemText, bool checked);
    void processSensorsDataSendOptions(const QString& itemText, bool checked);
    void processParentDataSendOptions(QTreeWidgetItem * parentItem);
    ComputerInfo::ToStringStruct m_toStringStruct;
};

#endif /* DATASENDWIDGET_HPP_ */
