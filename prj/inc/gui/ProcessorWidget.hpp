/*
 * ProcessorWidget.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef PROCESSORWIDGET_HPP_
#define PROCESSORWIDGET_HPP_

#include <QWidget>
#include "ui_ProcessorWidget.h"
#include "ComputerInfoDataContainerWrapper.hpp"


class ProcessorWidget: public QWidget, Ui::UiProcessorWidget
{
    Q_OBJECT
  public:
    ProcessorWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }
    void computerInfoData(ComputerInfoDataContainerWrapper* computerInfoData);

    private slots:
      void onSelectionRowChanged(const QItemSelection &, const QItemSelection &);
      void updatePlot();
      void on_dataTypeCombo_currentIndexChanged(int index);

    private:
      void drawPlot(unsigned index);
      void init();
      void addDataTypeToCombo();
      const ComputerInfoDataContainerWrapper* m_compInfo;
      int m_currentRow;
};


#endif /* PROCESSORWIDGET_HPP_ */
