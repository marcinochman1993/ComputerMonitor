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

class ComputerMonitorMainWindowSend: public ComputerMonitorMainWindowBase, Ui::ComputerMonitorMainWindowSendUi
{
    Q_OBJECT

  public:
    ComputerMonitorMainWindowSend(QWidget* parent = nullptr): ComputerMonitorMainWindowBase(parent) { init(); }
    void closeEvent(QCloseEvent* closeEventArgs) override;

  private:
    void init();
};

#endif /* COMPUTERMONITORMAINWINDOWSEND_HPP_ */
