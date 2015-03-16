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
#include <QPropertyAnimation>
#include <QPushButton>
//#include <QQuickView>


int main(int argc, char* argv[])
{
	//QQuickView view;

	QApplication app(argc, argv);
	QPushButton button("Animated Button");
	button.show();

	QPropertyAnimation animation(&button, "geometry");
	animation.setDuration(10000);

	animation.setKeyValueAt(0, QRect(0, 0, 100, 30));
	animation.setKeyValueAt(0.8, QRect(250, 250, 100, 30));
	animation.setKeyValueAt(1, QRect(0, 0, 100, 30));

	animation.start();
	return app.exec();
}

