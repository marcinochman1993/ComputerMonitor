/*
 * main.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#include <QMessageBox>
#include <QMainWindow>
#include <iostream>
#include <QApplication>
#include "ComputerMonitorMainWindow.hpp"
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <sensors/sensors.h>
#include "SensorInfo.hpp"

int main(int argc, char* argv[])
{
//  sensors_init(0);
//  QApplication app(argc, argv);
//
//  ComputerMonitorMainWindow mainWindow;
//  mainWindow.show();
//  return app.exec();
  for(const auto& i:SensorInfo::allSensors())
    std::cout<<i<<std::endl;
}
