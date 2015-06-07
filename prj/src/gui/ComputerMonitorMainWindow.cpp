/*
 * ComputerMonitorMainWindow.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindow.hpp"
#include <QMessageBox>

void ComputerMonitorMainWindow::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  sensorsWidget->computerInfoData(compInfo);
  processesWidget->computerInfoData(compInfo);
  processorWidget->computerInfoData(compInfo);
  ramWidget->computerInfoData(compInfo);
}

void ComputerMonitorMainWindow::closeEvent(QCloseEvent * closeEventData)
{
  QMessageBox::StandardButtons chosenButton = QMessageBox::question(this,
      tr("Closing application"), tr("Do you really want to quit application"),
      QMessageBox::Yes | QMessageBox::No);

  if (chosenButton == QMessageBox::No)
    closeEventData->ignore();
}

void ComputerMonitorMainWindow::init(PROGRAM_MODE mode)
{
  setupUi(this);
  m_dataWrapper = new ComputerInfoDataContainerWrapper();
  m_dataWrapper->data(&m_dataContainer);
  computerInfoData(m_dataWrapper);
  m_timer = new QTimer(this);
  m_timer->start(1000);
  connect(m_timer, SIGNAL(timeout()), m_dataWrapper, SLOT(update()));
  initThemeActions(menuOptions);
  initModeMenu();

  if (mode == PROGRAM_MODE::VISUALISATION)
    changeModeToVisualisation();
}

void ComputerMonitorMainWindow::changeModeToMixed()
{
  tabWidget->addTab(connectionTab, tr("Connection"));
}

void ComputerMonitorMainWindow::changeModeToVisualisation()
{
  tabWidget->removeTab(CONNECTION_TAB_INDEX);
}

void ComputerMonitorMainWindow::initModeMenu()
{
  m_modeActionGroup = new QActionGroup(this);
  m_modeActionGroup->addAction(actionVisualisation);
  m_modeActionGroup->addAction(actionMixed);
}
