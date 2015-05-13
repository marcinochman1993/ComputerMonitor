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
    Q_OBJECT

  public:
    SensorsWidget(QWidget* parent = nullptr)
    : QWidget(parent), m_currentRow(-1) { init(); }
    void computerInfoData(ComputerInfoDataContainerWrapper* computerInfoData);

  private slots:
    void onSelectionRowChanged(const QItemSelection &, const QItemSelection &);
    void updatePlot();

  private:
    void init();
    QCustomPlot* customPlotWidget() { return customPlot; }
    const ComputerInfoDataContainerWrapper* m_compInfo;
    int m_currentRow;
};

#endif /* SENSORSWIDGET_HPP_ */
