/*
 * main.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#include <iostream>
#include <QApplication>
#include "ComputerMonitorMainWindow.hpp"
#include <QSplashScreen>
#include <QTimer>
#include "ModeSelectionDialog.hpp"
#include "ProcessorInfo.hpp"
#include <thread>
#include <chrono>
#include "ComputerInfoDataContainerWrapper.hpp"

int main(int argc, char* argv[])
{
  const int SPLASH_SCREEN_TIME_MS = 2500;
  QApplication app(argc, argv);

  QSplashScreen* splashScreen = new QSplashScreen();
  splashScreen->setPixmap(QPixmap(":/images/images/splash.png"));

  ComputerMonitorMainWindow mainWindow;
  ComputerInfo computerInfo;
  ComputerInfoDataContainer dataContainer(&computerInfo);
  ComputerInfoDataContainerWrapper* dataWrapper=new ComputerInfoDataContainerWrapper();
  dataWrapper->data(&dataContainer);

  mainWindow.computerInfoData(dataWrapper);
  ModeSelectionDialog dialog;
  dialog.exec();

  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, splashScreen, SLOT(close()));
  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, &mainWindow, SLOT(show()));

  std::thread updateThread([&dataWrapper]()
  {
    while(true)
    {
      dataWrapper->update();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });

  updateThread.detach();

  splashScreen->show();

  return app.exec();

}
