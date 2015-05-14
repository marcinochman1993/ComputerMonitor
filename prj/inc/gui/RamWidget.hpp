/*
 * RamWidget.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef RAMWIDGET_HPP_
#define RAMWIDGET_HPP_

#include <QWidget>
#include "ui_RamWidget.h"

class RamWidget: public QWidget, Ui::UiRamWidget
{
  public:
    RamWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }
  private:
    void init();
};


#endif /* RAMWIDGET_HPP_ */
