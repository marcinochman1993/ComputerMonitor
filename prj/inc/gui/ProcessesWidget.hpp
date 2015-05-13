/*
 * ProcessesWidget.hpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#ifndef PROCESSESWIDGET_HPP_
#define PROCESSESWIDGET_HPP_

#include "ui_ProcessesWidget.h"
#include <QWidget>
#include "ComputerInfoDataContainerWrapper.hpp"
#include "AllProcessesModel.hpp"

class ProcessesWidget: public QWidget
{
    Q_OBJECT
  public:
    ProcessesWidget(QWidget* parent = nullptr): QWidget(parent), m_currentRow(-1) { init(); }
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);

  private:
    void init();
    QCustomPlot* customPlotWidget() { return m_ui.customPlot; }
    Ui::UiProcessesWidget m_ui;
    const ComputerInfoDataContainerWrapper* m_compInfo;
    int m_currentRow;
    AllProcessesModel* m_model;
  private slots:
    void onSelectionRowChanged(const QItemSelection &, const QItemSelection &);
    void updatePlot();
};



#endif /* PROCESSESWIDGET_HPP_ */
