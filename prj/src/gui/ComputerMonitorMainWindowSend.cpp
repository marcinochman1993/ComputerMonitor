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

void ComputerMonitorMainWindowSend::init()
{
  m_tcpSocket = nullptr;
  setupUi(this);
  initThemeActions(menuOptions);
  initSystemTrayIcon();

  m_tcpServer = new QTcpServer(this);
  m_timer = new QTimer(this);
  m_timer->setInterval(1000);
  m_timer->start();

  connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(initSocket()));
  connect(m_timer, SIGNAL(timeout()), this, SLOT(sendData()));
  connect(actionAbout, SIGNAL(triggered()), this, SLOT(showAboutDialog()));

}

void ComputerMonitorMainWindowSend::initSystemTrayIcon()
{
  m_trayIcon = new QSystemTrayIcon(this);
  connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
      this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
  m_trayIcon->setIcon(QIcon(":/images/images/tray.png"));
  m_trayIcon->setToolTip(tr("Computer Monitor - stopped server"));
}

void ComputerMonitorMainWindowSend::onTrayIconActivated(
    QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
    case QSystemTrayIcon::DoubleClick:
      show();
      m_trayIcon->hide();
      break;

    default:
      break;
  }
}

void ComputerMonitorMainWindowSend::changeEvent(QEvent* event)
{
  switch (event->type())
  {
    case QEvent::WindowStateChange:
    {
      if (windowState() & Qt::WindowMinimized)
      {
        QTimer::singleShot(0, this, SLOT(hide()));
        m_trayIcon->show();
      }
      break;
    }
    default:
      break;
  }

  QMainWindow::changeEvent(event);

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
  else
    saveSettings();
}

void ComputerMonitorMainWindowSend::on_serverButton_clicked()
{
  if (m_tcpServer == nullptr || !m_tcpServer->isListening())
    startServer();
  else
    stopServer();
}

void ComputerMonitorMainWindowSend::sendData()
{
  if (m_tcpSocket == nullptr)
    return;

  m_compInfo.update();

  if (m_tcpSocket->state() == QTcpSocket::ConnectedState)
  {
    QByteArray array(
        m_compInfo.toString(dataSendWidget->toStringStruct()).c_str());
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
  m_tcpServer->listen(QHostAddress(dataSendWidget->ipAddress()),
      dataSendWidget->port());
  dataSendWidget->startedServer();
  m_trayIcon->setToolTip(tr("Computer Monitor - running server"));
}

void ComputerMonitorMainWindowSend::stopServer()
{
  m_tcpServer->close();
  dataSendWidget->stoppedServer();
  m_trayIcon->setToolTip(tr("Computer Monitor - stopped server"));
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

