/*
 * ComputerMonitorMainWindowSend.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOWSEND_HPP_
#define COMPUTERMONITORMAINWINDOWSEND_HPP_

#include <QMainWindow>
#include "ui_ComputerMonitorMainWindowSend.h"

class ComputerMonitorMainWindowSend: public QMainWindow, Ui::ComputerMonitorMainWindowSendUi
{
    Q_OBJECT

  public:
    ComputerMonitorMainWindowSend(QWidget* parent = nullptr): QMainWindow(parent) { init(); }
    void closeEvent(QCloseEvent* closeEventArgs) override;
  private:
    void init();
    void initValidation();
};


#endif /* COMPUTERMONITORMAINWINDOWSEND_HPP_ */
