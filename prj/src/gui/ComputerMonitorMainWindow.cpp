/*
 * ComputerMonitorMainWindow.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindow.hpp"
#include <QMessageBox>

using namespace std;

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

  initThemeActions(menuOptions);
  initModeMenu();

  if (mode == PROGRAM_MODE::VISUALISATION)
    changeModeToVisualisation();
  else
    changeModeToMixed();

  m_tcpServer = new QTcpServer(this);
  m_tcpSocket = new QTcpSocket(this);

  connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(initSocket()));
  connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
  connect(m_timer, SIGNAL(timeout()), m_dataWrapper, SLOT(update()));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(sendData()));
  connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void ComputerMonitorMainWindow::changeModeToMixed()
{
  if (tabWidget->count() == 6)
  {
    tabWidget->removeTab(CONNECTION_TAB_INDEX + 1);
  }
  else
    tabWidget->removeTab(CONNECTION_TAB_INDEX);
  tabWidget->addTab(sendingConfigTab, tr("Sending config"));
  m_timer->start(1000);
}

void ComputerMonitorMainWindow::changeModeToVisualisation()
{
  clear();
  stopServer();

  if (tabWidget->count() == 6)
  {
    tabWidget->removeTab(CONNECTION_TAB_INDEX);
  }
  else
    tabWidget->removeTab(CONNECTION_TAB_INDEX);
  tabWidget->removeTab(CONNECTION_TAB_INDEX);
  tabWidget->addTab(serverConfigTab, tr("Server config"));
  m_timer->stop();
}

void ComputerMonitorMainWindow::initModeMenu()
{
  m_modeActionGroup = new QActionGroup(this);
  m_modeActionGroup->addAction(actionVisualisation);
  m_modeActionGroup->addAction(actionMixed);
}

void ComputerMonitorMainWindow::on_actionExport_Plot_triggered()
{
  std::map<int, ComputerMonitorWidgetBase*> widgetMap = { { 0, sensorsWidget },
      { 1, processorWidget }, { 2, ramWidget }, { 3, processesWidget } };

  ComputerMonitorWidgetBase* widgetToExport = widgetMap[m_selectedTabIndex];
  widgetToExport->savePlot();
}

void ComputerMonitorMainWindow::on_serverButton_clicked()
{
  if (!m_tcpServer->isListening())
    startServer();
  else
  {
    stopServer();
  }
}

void ComputerMonitorMainWindow::onConnectedServer()
{
  dataSendWidget->connectionEstablished();
}

void ComputerMonitorMainWindow::onDisconnectedServer()
{
  dataSendWidget->connectionLost();
  m_tcpSocketServer = nullptr;
}

void ComputerMonitorMainWindow::initSocket()
{
  m_tcpSocketServer = m_tcpServer->nextPendingConnection();
  dataSendWidget->connectionEstablished();

  connect(m_tcpSocketServer, SIGNAL(connected()), this,
      SLOT(onConnectedServer()));
  connect(m_tcpSocketServer, SIGNAL(disconnected()), this,
      SLOT(onDisconnectedServer()));
}

void ComputerMonitorMainWindow::startServer()
{
  m_tcpServer->close();
  if (m_tcpServer->listen(QHostAddress::Any, 9998))
    dataSendWidget->startedServer();
}

void ComputerMonitorMainWindow::stopServer()
{
  if (m_tcpSocketServer != nullptr)
  {
    m_tcpSocketServer->close();
    m_tcpSocketServer = nullptr;
  }
  if (m_tcpServer != nullptr)
    m_tcpServer->close();
  dataSendWidget->stoppedServer();
}

void ComputerMonitorMainWindow::sendData()
{
  if (m_tcpSocketServer == nullptr)
    return;

  if (m_tcpSocketServer->state() == QTcpSocket::ConnectedState)
  {
    QByteArray array(m_dataContainer.computerInfo().toString().c_str());
    m_tcpSocketServer->write(array);
  }
  else
  {
  }
}

void ComputerMonitorMainWindow::clear()
{
  processorWidget->clear();
  ramWidget->clear();
  sensorsWidget->clear();
  processesWidget->clear();
}

void ComputerMonitorMainWindow::receiveData()
{
  string strFromNet = QString(m_tcpSocket->readAll()).toStdString();
  if (m_dataWrapper != nullptr)
    m_dataWrapper->update();
}

void ComputerMonitorMainWindow::on_connectButton_clicked()
{
  if (m_tcpSocket->state() == QTcpSocket::ConnectedState)
    stopReceiving();
  else
    startReceiving();
}

void ComputerMonitorMainWindow::stopReceiving()
{
  m_tcpSocket->close();
  dataReceiveWidget->connectionLost();
}

void ComputerMonitorMainWindow::startReceiving()
{
  m_tcpSocket->connectToHost(QHostAddress("127.0.0.1"), 9998);
  if (m_tcpSocket->waitForConnected(3000))
    dataReceiveWidget->connectionEstablished();
}
