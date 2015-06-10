/*
 * ProcessesWidget.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "ProcessesWidget.hpp"
#include "UsageDelegate.hpp"

using namespace std;

void ProcessesWidget::init()
{
  setupUi(this);
  addDataTypeToCombo();
  allProcessesTable->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
}

void ProcessesWidget::addDataTypeToCombo()
{
  vector<QString> dataTypesString = { tr("CpuUsage [%]") };
  for (int i = 0; i < 1; i++)
    dataTypeCombo->addItem(dataTypesString[i]);
}

void ProcessesWidget::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  if (compInfo == nullptr)
    return;

  m_model = new AllProcessesModel(this);
  m_model->computerInfoData(compInfo);
  allProcessesTable->setModel(m_model);
  auto delegate = new UsageDelegate(this);
  delegate->addColumnUsage(2);
  allProcessesTable->setItemDelegate(delegate);
  QItemSelectionModel *selectionModel = allProcessesTable->selectionModel();
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
  if (customPlot->graphCount() <= 0)
    customPlot->addGraph();

  m_currentRow = selected.indexes()[0].row();
  QVector<double> y0 = QVector<double>::fromList(
      QList<double>::fromStdList(
          m_compInfo->dataContainer()->cpuUsage(
              m_model->processIdByIndex(m_currentRow)).list())), x;
  for (int i = 0; i < y0.size(); i++)
    x.push_back(m_compInfo->dataContainer()->time()[i]);
  customPlot->yAxis->setLabel(
      tr("Cpu Usage of %1 [%]").arg(
          QString::fromStdString(
              m_model->processNameById(
                  m_model->processIdByIndex(m_currentRow)))));
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}

void ProcessesWidget::updatePlot()
{
  if (customPlot->graphCount() == 0 || m_currentRow == -1)
    return;
  unsigned processId = m_model->processIdByIndex(m_currentRow);
  double y = m_compInfo->dataContainer()->cpuUsage(processId).back(), x =
    m_compInfo->dataContainer()->time().back();
  addToPlot(customPlot, x, y);
  customPlot->graph(0)->rescaleAxes();
  customPlot->replot();
}
