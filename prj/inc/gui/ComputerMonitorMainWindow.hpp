/*
 * ComputerMonitorMainWindow.hpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOW_HPP_
#define COMPUTERMONITORMAINWINDOW_HPP_

#include <QMainWindow>
#include "ui_ComputerMonitorMainWindowUi.h"

class ComputerMonitorMainWindow: public QMainWindow
{
  Q_OBJECT

  public:
    ComputerMonitorMainWindow(QWidget* parent = 0): QMainWindow(parent) { m_ui.setupUi(this); }
  private:
    Ui::ComputerMonitorMainWindowUi m_ui;
};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
