/*
 * ComputerMonitorMainWindowSend.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOWSEND_HPP_
#define COMPUTERMONITORMAINWINDOWSEND_HPP_

#include "ComputerMonitorMainWindowBase.hpp"
#include "ui_ComputerMonitorMainWindowSend.h"
#include <QTreeWidgetItem>
#include <QTcpServer>
#include "ComputerInfo.hpp"
#include <QSystemTrayIcon>

class ComputerMonitorMainWindowSend: public ComputerMonitorMainWindowBase, Ui::ComputerMonitorMainWindowSendUi
{
    Q_OBJECT

  public:
    ComputerMonitorMainWindowSend(QWidget* parent = nullptr): ComputerMonitorMainWindowBase(parent) { init(); }
    void closeEvent(QCloseEvent* closeEventArgs) override;

  protected:
    void changeEvent(QEvent* event) override;

  private slots:
    void on_serverButton_clicked();
    void onConnected();
    void onDisconnected();
    void initSocket();
    void sendData();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason);
  private:
    void init();
    void startServer();
    void stopServer();
    void initSystemTrayIcon();
    QTcpServer* m_tcpServer;
    ComputerInfo m_compInfo;
    QSystemTrayIcon* m_trayIcon;
};

#endif /* COMPUTERMONITORMAINWINDOWSEND_HPP_ */
