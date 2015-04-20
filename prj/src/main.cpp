/*
 * main.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#include <iostream>
#include <QApplication>
#include "ComputerMonitorMainWindow.hpp"
#include <sensors/sensors.h>
#include "SensorInfo.hpp"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  ComputerMonitorMainWindow mainWindow;
  mainWindow.show();
  return app.exec();
  for(const auto& i:SensorInfo::allSensors())
    std::cout<<i<<std::endl;
}
