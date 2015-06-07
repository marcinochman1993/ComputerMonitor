/*
 * ComputerMonitorWidgetBase.hpp
 *
 *  Created on: Jun 7, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORWIDGETBASE_HPP_
#define COMPUTERMONITORWIDGETBASE_HPP_


#include <QWidget>
#include "qcustomplot.h"

class ComputerMonitorWidgetBase: public QWidget
{
    Q_OBJECT
  public:
    ComputerMonitorWidgetBase(QWidget* parent = nullptr): QWidget(parent) { }
  protected:
    void savePlot(QCustomPlot* plot);
  public slots:
    virtual void savePlot() { }
};


#endif /* COMPUTERMONITORWIDGETBASE_HPP_ */
