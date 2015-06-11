/*
 * ProcessorWidget.cpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#include "ProcessorWidget.hpp"
#include "UsageDelegate.hpp"

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

  m_processorModel = new ProcessorModel(this);
  m_processorModel->computerInfoData(compInfo);
  auto delegate = new UsageDelegate(this);
  delegate->addColumnUsage(2);
  coresTable->setItemDelegate(delegate);
  coresTable->setModel(m_processorModel);
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
  if (m_compInfo == nullptr)
    return;

  auto dataContainer = m_compInfo->dataContainer();
  auto computerInfo = dataContainer->computerInfo();
  cpuTotalUsageRadialIndicatorWidget->setValuePercent(
      m_compInfo->dataContainer()->computerInfo().processor().totalUsage());
  processorNameLabel->setText(QString(computerInfo.processor().name().c_str()));
  processorUsageLabel->setText(
      QString::number(computerInfo.processor().totalUsage(), 'f', 2) + " %");

  if (customPlot->graphCount() == 0 || m_currentRow < 0)
    return;
  double x, y;
  switch (dataTypeCombo->currentIndex())
  {
    case 0:
      y = dataContainer->frequency(m_currentRow).back();
      customPlot->yAxis->setLabel(
          QString("Frequency of core %1 [MHz]").arg(m_currentRow));
      break;
    case 1:
      y = dataContainer->coreUsage(m_currentRow).back();
      customPlot->yAxis->setLabel(
          QString("Usage of core %1 [%]").arg(m_currentRow));
      break;
  }
  x = dataContainer->time().back();
  addToPlot(customPlot, x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->xAxis->setLabel("t");
  customPlot->replot();
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
      y0 = QVector<double>::fromList(
          QList<double>::fromStdList(
              m_compInfo->dataContainer()->frequency(m_currentRow).list()));
      break;
    case 1:
      y0 = QVector<double>::fromList(
          QList<double>::fromStdList(
              m_compInfo->dataContainer()->coreUsage(m_currentRow).list()));
      break;
  }

  for (int i = 0; i < y0.size(); i++)
    x.push_back(m_compInfo->dataContainer()->time()[i]);
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}

void ProcessorWidget::clear()
{
  if (m_processorModel != nullptr)
    m_processorModel->clear();
  customPlot->clearGraphs();
  customPlot->clearPlottables();
  customPlot->replot();
  cpuTotalUsageRadialIndicatorWidget->setValuePercent(0.0);
  processorUsageLabel->setText("");
  processorNameLabel->setText("");

}
