/*
 * ProcessesWidget.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "ProcessesWidget.hpp"

using namespace std;

void ProcessesWidget::init()
{
  m_ui.setupUi(this);
  addDataTypeToCombo();
  m_ui.allProcessesTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
}

void ProcessesWidget::addDataTypeToCombo()
{
  vector<QString> dataTypesString = { tr("CpuUsage [%]") };
  for (int i = 0; i < 1; i++)
    m_ui.dataTypeCombo->addItem(dataTypesString[i]);
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
  QVector<double> y0 = QVector<double>::fromStdVector(
      m_compInfo->dataContainer()->cpuUsage(
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
  unsigned processId = m_model->processIdByIndex(m_currentRow);
  customPlot->graph(0)->addData(
      m_compInfo->dataContainer()->cpuUsage(processId).size(),
      m_compInfo->dataContainer()->cpuUsage(processId).back());

  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}
