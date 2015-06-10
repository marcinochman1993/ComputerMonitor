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
    ComputerMonitorWidgetBase(QWidget* parent = nullptr): QWidget(parent), m_maxPlotSize(60) { }
    unsigned maxPlotSize() const { return m_maxPlotSize; }
    void maxPlotSize(unsigned newMaxPlotSize) { m_maxPlotSize= newMaxPlotSize; }
  protected:
    void savePlot(QCustomPlot* plot);
    void addToPlot(QCustomPlot* plot, double x, double y);
  public slots:
    virtual void savePlot() { }
  private:
  unsigned m_maxPlotSize;
};


#endif /* COMPUTERMONITORWIDGETBASE_HPP_ */
