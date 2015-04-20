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
#include <QSplashScreen>
#include <QTimer>
#include "SensorInfo.hpp"

int main(int argc, char* argv[])
{
  const int SPLASH_SCREEN_TIME_MS = 2500;
  QApplication app(argc, argv);

  QSplashScreen* splashScreen = new QSplashScreen();
  splashScreen->setPixmap(QPixmap(":/images/images/splash.png"));

  ComputerMonitorMainWindow mainWindow;
  splashScreen->show();

  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, splashScreen, SLOT(close()));
  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, &mainWindow, SLOT(show()));

//  mainWindow.show();
  return app.exec();
}
