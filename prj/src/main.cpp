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
#include "ComputerMonitorMainWindowSend.hpp"
#include <thread>

#include <QTcpSocket>

#include "AllProcessesInfo.hpp"

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void initPalette();

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
      break;
  }

  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, splashScreen, SLOT(close()));
  QTimer::singleShot(SPLASH_SCREEN_TIME_MS, mainWindow, SLOT(show()));

  splashScreen->show();

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

  /*ComputerMonitorMainWindowSend mainWindow;

   mainWindow.show();
   */

  return app.exec();
}

void initPalette()
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(80, 80, 80));
  palette.setColor(QPalette::WindowText, Qt::white);
  palette.setColor(QPalette::Base, QColor(130, 130, 130));
  palette.setColor(QPalette::AlternateBase, QColor(80, 80, 80));
  palette.setColor(QPalette::ToolTipBase, Qt::white);
  palette.setColor(QPalette::ToolTipText, Qt::white);
  palette.setColor(QPalette::Text, Qt::white);
  palette.setColor(QPalette::Button, QColor(80, 80, 80));
  palette.setColor(QPalette::ButtonText, Qt::white);
  palette.setColor(QPalette::BrightText, Qt::red);

  palette.setColor(QPalette::Highlight, QColor(100, 100, 100));
  palette.setColor(QPalette::HighlightedText, Qt::white);

  palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
  palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
  qApp->setPalette(palette);
}
