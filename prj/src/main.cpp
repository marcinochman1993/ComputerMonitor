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

int main(int argc, char* argv[])
{
	QApplication app(argc,argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:qml/ComputerMonitorMainWindow.qml"));
    QObject* topObject=engine.rootObjects().value(0);
    QQuickWindow* wnd = qobject_cast<QQuickWindow*>(topObject);
    wnd->show();

	return app.exec();
}

