/*
 * ProcessesWidget.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "ProcessesWidget.hpp"

void ProcessesWidget::init()
{
  m_ui.setupUi(this);
}

void ProcessesWidget::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  if (compInfo == nullptr)
    return;

  m_model = new AllProcessesModel(this);
  m_model->computerInfoData(compInfo);
  m_ui.allProcessesTable->setModel(m_model);
  QItemSelectionModel *selectionModel =
    m_ui.allProcessesTable->selectionModel();
  connect(selectionModel,
      SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
      this,
      SLOT(
          onSelectionRowChanged(const QItemSelection &, const QItemSelection &)));
  m_compInfo = compInfo;
  connect(compInfo, SIGNAL(dataUpdated()), this, SLOT(updatePlot()));
}

void ProcessesWidget::onSelectionRowChanged(const QItemSelection & selected,
    const QItemSelection &)
{
  auto customPlot = customPlotWidget();
  if (customPlot->graphCount() <= 0)
    customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->addGraph();

  m_currentRow = selected.indexes()[0].row();
  std::cout << m_currentRow << std::endl;
  QVector<double> y0 = QVector<double>::fromStdVector(
      m_compInfo->dataContainer()->ramUsage(
          m_model->processIdByIndex(m_currentRow))), x;
  for (int i = 0; i < y0.size(); i++)
    x.push_back(i);
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}

void ProcessesWidget::updatePlot()
{
  auto customPlot = customPlotWidget();
  if (customPlot->graphCount() == 0 || m_currentRow == -1)
    return;
  customPlot->graph(0)->addData(
      m_compInfo->dataContainer()->ramUsage(m_currentRow).size(),
      m_compInfo->dataContainer()->ramUsage(m_currentRow).back());
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}
