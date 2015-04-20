/*
 * SensorsWidget.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef SENSORSWIDGET_HPP_
#define SENSORSWIDGET_HPP_

#include <QWidget>
#include "ui_SensorsWidget.h"
#include "AllSensorsModel.hpp"

class SensorsWidget: public QWidget, Ui::UiSensorsWidget
{
  public:
    SensorsWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
      setupUi(this);
      auto model = new AllSensorsModel();
      model->computerInfo(new ComputerInfo());
      tableView->setModel(model);
    }
};

#endif /* SENSORSWIDGET_HPP_ */
