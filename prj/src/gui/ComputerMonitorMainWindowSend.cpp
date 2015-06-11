/*
 * ComputerMonitorMainWindowSend.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#include "ComputerMonitorMainWindowSend.hpp"
#include <QCloseEvent>
#include <QMessageBox>
#include <QHostAddress>
#include <iostream>
void ComputerMonitorMainWindowSend::init()
{
  m_tcpSocket = nullptr;
  setupUi(this);
  initThemeActions(menuOptions);

  m_tcpServer = new QTcpServer(this);
  m_timer = new QTimer(this);
  m_timer->setInterval(1000);
  m_timer->start();

  connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(initSocket()));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(sendData()));
  connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
}

void ComputerMonitorMainWindowSend::initSocket()
{
  m_tcpSocket = m_tcpServer->nextPendingConnection();
  dataSendWidget->connectionEstablished();

  connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
  connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void ComputerMonitorMainWindowSend::closeEvent(QCloseEvent* closeEventArgs)
{
  QMessageBox::StandardButtons chosenButton = QMessageBox::question(this,
      tr("Closing application"), tr("Do you really want to quit application"),
      QMessageBox::Yes | QMessageBox::No);

  if (chosenButton == QMessageBox::No)
    closeEventArgs->ignore();
}

void ComputerMonitorMainWindowSend::on_connectButton_clicked()
{
  if (m_tcpServer == nullptr || !m_tcpServer->isListening())
    startServer();
  else
  {
    m_tcpServer->close();
    dataSendWidget->stoppedServer();
  }
}

void ComputerMonitorMainWindowSend::sendData()
{
  if (m_tcpSocket == nullptr)
    return;

  m_compInfo.update();

  if (m_tcpSocket->state() == QTcpSocket::ConnectedState)
  {
    QByteArray array(m_compInfo.toString().c_str());
    m_tcpSocket->write(array);
  }
  else
  {
    //todo
  }
}

void ComputerMonitorMainWindowSend::startServer()
{
  m_tcpServer->close();
  m_tcpServer->listen(QHostAddress::Any, 9998);
  dataSendWidget->startedServer();
}

void ComputerMonitorMainWindowSend::onConnected()
{
  dataSendWidget->connectionEstablished();
}

void ComputerMonitorMainWindowSend::onDisconnected()
{
  dataSendWidget->connectionLost();
  m_tcpSocket = nullptr;
}


