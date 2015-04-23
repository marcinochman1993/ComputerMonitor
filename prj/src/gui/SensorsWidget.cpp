/*
 * SensorsWidget.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "SensorsWidget.hpp"

void SensorsWidget::computerInfoData(ComputerInfoDataContainerWrapper* compInfo)
{
  auto model = new AllSensorsModel();
  model->computerInfoData(compInfo);
  tableView->setModel(model);
  tableView->resizeColumnsToContents();
  QItemSelectionModel *selectionModel = tableView->selectionModel();
  m_compInfo = compInfo;

  connect(selectionModel,
      SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
      this,
      SLOT(
          onSelectionRowChanged(const QItemSelection &, const QItemSelection &)));
  connect(compInfo, SIGNAL(dataUpdated()), tableView, SLOT(repaint()));
  connect(compInfo, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));
}

void SensorsWidget::onSelectionRowChanged(const QItemSelection & selected,
    const QItemSelection &)
{
  static int mult = 0;
  auto customPlot = customPlotWidget();
  if (customPlot->graphCount() <= 0)
    customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->addGraph();

  m_currentRow = selected.indexes()[0].row();
  QVector<double> y0 = QVector<double>::fromStdVector(
      m_compInfo->dataContainer()->sensorsData(m_currentRow)), x;
  for (int i = 0; i < y0.size(); i++)
    x.push_back(i);
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2,
      SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2,
      SLOT(setRange(QCPRange)));
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->setInteractions(
      QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->replot();
  mult++;
}

void SensorsWidget::updatePlot()
{
  if (customPlot->graphCount() == 0 || m_currentRow == -1)
    return;
  std::cout << m_currentRow << std::endl;
  customPlot->graph(0)->addData(
      m_compInfo->dataContainer()->sensorsData(m_currentRow).size(),
      m_compInfo->dataContainer()->sensorsData(m_currentRow).back());
  customPlot->replot();

  customPlot->graph(0)->rescaleAxes();
}

void SensorsWidget::init()
{
  setupUi(this);

}
