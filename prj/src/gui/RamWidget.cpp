/*
 * RamWidget.cpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#include "RamWidget.hpp"

void RamWidget::init()
{
  setupUi(this);
}

void RamWidget::computerInfoData(
    ComputerInfoDataContainerWrapper* computerInfoData)
{
  m_compInfo = computerInfoData;
  connect(computerInfoData, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));
}

void RamWidget::drawPlot()
{
  QVector<double> y0, x;
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue));

  y0 = QVector<double>::fromList(
      QList<double>::fromStdList(
          m_compInfo->dataContainer()->totalRamUsage().list()));
  for (int i = 0; i < y0.size(); i++)
    x.push_back(m_compInfo->dataContainer()->time()[i]);
  customPlot->yAxis->setLabel("Ram Usage [%]");
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
}

void RamWidget::updatePlot()
{
  if (m_compInfo == nullptr)
    return;

  if (customPlot->graphCount() <= 0)
    drawPlot();
  else
  {
    double x = m_compInfo->dataContainer()->time().back(), y =
      m_compInfo->dataContainer()->totalRamUsage().back();
    addToPlot(customPlot, x, y);
    customPlot->graph(0)->rescaleAxes();
  }
  customPlot->replot();
}

void RamWidget::clear()
{
  customPlot->clearGraphs();
  customPlot->clearPlottables();
  customPlot->replot();
}
