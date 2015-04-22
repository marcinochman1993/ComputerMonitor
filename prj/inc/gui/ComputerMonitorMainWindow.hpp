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
#include "ComputerInfoDataContainerWrapper.hpp"

class ComputerMonitorMainWindow: public QMainWindow, Ui::ComputerMonitorMainWindowUi
{
  Q_OBJECT

  public:
    ComputerMonitorMainWindow(QWidget* parent = 0): QMainWindow(parent) { setupUi(this); }
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);

};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
