/*
 * SensorsWidget.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "SensorsWidget.hpp"

void SensorsWidget::computerInfoData(ComputerInfoDataContainerWrapper* compInfo)
{
  if (compInfo == nullptr)
    return;

  auto model = new AllSensorsModel();
  model->computerInfoData(compInfo);
  tableView->setModel(model);
  QItemSelectionModel *selectionModel = tableView->selectionModel();
  m_compInfo = compInfo;

  connect(selectionModel,
      SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
      this,
      SLOT(
          onSelectionRowChanged(const QItemSelection &, const QItemSelection &)));
  connect(compInfo, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));
}

void SensorsWidget::onSelectionRowChanged(const QItemSelection & selected,
    const QItemSelection &)
{
  if (customPlot->graphCount() <= 0)
    customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue));

  m_currentRow = selected.indexes()[0].row();
  QVector<double> y0 = QVector<double>::fromList(
      QList<double>::fromStdList(
          m_compInfo->dataContainer()->sensorsData(m_currentRow).list())), x;

  for (int i = 0; i < y0.size(); i++)
    x.push_back(m_compInfo->dataContainer()->time()[i]);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->yAxis->setLabel(
      QString("Sensor %1 [%2]").arg(m_currentRow).arg(
          m_compInfo->dataContainer()->computerInfo().allSensors()[m_currentRow].unit().c_str()));
  customPlot->replot();
}

void SensorsWidget::updatePlot()
{
  if (customPlot->graphCount() == 0 || m_currentRow == -1)
    return;
  double x = m_compInfo->dataContainer()->time().back(), y =
    m_compInfo->dataContainer()->sensorsData(m_currentRow).back();

  addToPlot(customPlot, x, y);

  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}

void SensorsWidget::init()
{
  setupUi(this);
  tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
