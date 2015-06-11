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

class DataSendWidget: public QWidget, Ui::DataSendWidgetUi
{
  Q_OBJECT
  public:
    DataSendWidget(QWidget* parent = nullptr)
        : QWidget(parent) { init(); }

  public slots:
    void connectionEstablished();
    void connectionLost();
    void startedServer();
    void stoppedServer();
  protected slots:
    void on_dataSendTree_itemChanged(QTreeWidgetItem * item, int column);

  private:
    void init();
    void initValidation();
};

#endif /* DATASENDWIDGET_HPP_ */
