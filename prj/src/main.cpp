/*
 * main.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#include <iostream>
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "ComputerMonitorMainWindow.hpp"
#include "ModeSelectionDialog.hpp"
#include "ProcessorInfo.hpp"
#include "ComputerMonitorMainWindowSend.hpp"

int main(int argc, char* argv[])
{
  const int SPLASH_SCREEN_TIME_MS = 2500;
  QApplication app(argc, argv);

  QSplashScreen* splashScreen = new QSplashScreen();
  splashScreen->setPixmap(QPixmap(":/images/images/splash.png"));

  ModeSelectionDialog dialog;
  dialog.exec();

  QMainWindow* mainWindow = nullptr;

  switch (dialog.programMode())
  {
    case ProgramMode::SENDING_DATA:
      mainWindow = new ComputerMonitorMainWindowSend;
      break;
    case ProgramMode::PRESENTING_DATA:
      mainWindow = new ComputerMonitorMainWindow;
      break;
    case ProgramMode::MIXED:
      mainWindow = new ComputerMonitorMainWindow(
          ComputerMonitorMainWindow::PROGRAM_MODE::MIXED);
      break;
  }

  ComputerMonitorMainWindowBase::defaultPalette(qApp->palette());

  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, splashScreen, SLOT(close()));
  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, mainWindow, SLOT(show()));

  splashScreen->show();

  return app.exec();

  ComputerInfo ci;

  ci.update();
  std::cout << ci.toString();
}

//#include <QTcpSocket>
/*  QTcpSocket* socket = new QTcpSocket;

 socket->connectToHost("192.168.2.1", 80);

 if (socket->waitForConnected(3000))
 {
 qDebug() << "Connected";
 }
 else
 {
 qDebug() << "Not Connected";
 socket->close();
 }

 socket->write("Hello world\r\n\r\n");
 socket->waitForBytesWritten(1000);
 socket->waitForReadyRead(3000);
 qDebug() << socket->readAll();
 socket->close();*/
