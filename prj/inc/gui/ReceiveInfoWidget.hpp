/*
 * ReceiveInfoWidget.hpp
 *
 *  Created on: Jun 10, 2015
 *      Author: mochman
 */

#ifndef RECEIVEDATAWIDGET_HPP_
#define RECEIVEDATAWIDGET_HPP_

#include <QWidget>
#include "ui_ReceiveInfoWidget.h"

class ReceiveInfoWidget: public QWidget, Ui::ReceiveInfoWidget
{
    Q_OBJECT

  public:
    ReceiveInfoWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }

  public slots:
    void connectionEstablished();
    void connectionLost();

  private:
    void init();
    void initValidators();
};

#endif /* RECEIVEINFOWIDGET_HPP_ */
