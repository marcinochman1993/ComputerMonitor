/*
 * ComputerMonitorMainWindowBase.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOWBASE_HPP_
#define COMPUTERMONITORMAINWINDOWBASE_HPP_

#include <QMainWindow>


class ComputerMonitorMainWindowBase: public QMainWindow
{
public:
    ComputerMonitorMainWindowBase(QWidget* parent = nulltrp): QWidget(parent) { }
protected:
    void selectDarkTheme();
    void selectBrightTheme();
};


#endif /* COMPUTERMONITORMAINWINDOWBASE_HPP_ */
