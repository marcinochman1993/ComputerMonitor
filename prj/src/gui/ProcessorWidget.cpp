/*
 * ProcessorWidget.cpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#include "ProcessorWidget.hpp"
#include "ProcessorModel.hpp"

using namespace std;

void ProcessorWidget::init()
{
  setupUi(this);
  addDataTypeToCombo();
  coresTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ProcessorWidget::addDataTypeToCombo()
{
  vector<QString> dataTypesString = { tr("Frequency [MHz]"), tr("Usage [%]") };
  for (unsigned i = 0; i < dataTypesString.size(); i++)
    dataTypeCombo->addItem(dataTypesString[i]);
}

void ProcessorWidget::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  if (compInfo == nullptr)
    return;

  auto model = new ProcessorModel(this);
  model->computerInfoData(compInfo);
  coresTable->setModel(model);
  QItemSelectionModel *selectionModel = coresTable->selectionModel();
  m_compInfo = compInfo;
  connect(selectionModel,
      SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
      this,
      SLOT(
          onSelectionRowChanged(const QItemSelection &, const QItemSelection &)));
  connect(compInfo, SIGNAL(dataUpdated()), this, SLOT(dataUpdated()));
}

void ProcessorWidget::onSelectionRowChanged(const QItemSelection & selected,
    const QItemSelection &)
{
  m_currentRow = selected.indexes()[0].row();
  drawPlot();
}

void ProcessorWidget::dataUpdated()
{
  if (customPlot->graphCount() == 0 || m_currentRow < 0)
    return;
  double x, y;
  switch (dataTypeCombo->currentIndex())
  {
    case 0:
      y = m_compInfo->dataContainer()->frequency(m_currentRow).back();
      x = m_compInfo->dataContainer()->frequency(m_currentRow).size();
      break;
    case 1:
      y = m_compInfo->dataContainer()->coreUsage(m_currentRow).back();
      x = m_compInfo->dataContainer()->coreUsage(m_currentRow).size();
      break;
  }
  customPlot->graph(0)->addData(x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();

  cpuTotalUsageRadialIndicatorWidget->setValuePercent(
      m_compInfo->dataContainer()->computerInfo().processor().totalUsage());

}

void ProcessorWidget::on_dataTypeCombo_currentIndexChanged(int index)
{
  if (m_currentRow >= 0 && m_compInfo != nullptr)
    drawPlot();
}

void ProcessorWidget::drawPlot()
{
  if (m_compInfo == nullptr)
    return;
  customPlot->clearGraphs();
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->addGraph();

  QVector<double> y0, x;
  switch (dataTypeCombo->currentIndex())
  {
    case 0:
      y0 = QVector<double>::fromStdVector(
          m_compInfo->dataContainer()->frequency(m_currentRow));
      break;
    case 1:
      y0 = QVector<double>::fromStdVector(
          m_compInfo->dataContainer()->coreUsage(m_currentRow));
      break;
  }

  for (int i = 0; i < y0.size(); i++)
    x.push_back(i);
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}
