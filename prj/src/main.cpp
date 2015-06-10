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
#include "DataBuffer.hpp"

int main(int argc, char* argv[])
{
  /*const int SPLASH_SCREEN_TIME_MS = 2500;
   QApplication app(argc, argv);

   QSplashScreen* splashScreen = new QSplashScreen();
   splashScreen->setPixmap(QPixmap(":/images/images/splash.png"));

   splashScreen->setAttribute(Qt::WA_DeleteOnClose);

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

   return app.exec();*/

//  ComputerInfo info;
//  info.update();
//
//  std::cout << info.toString() << std::endl;
  ComputerInfo ci;
  ci.update(
      "Component Type:Processor;Processor name:;Cores number:2;Total usage:0;(Core Frequency:0:782);(Core Frequency:1:1500);(Core Usage:0 :0);(Core Usage:1 :0);Data updated:1433922423;\n"
          "Component Type:RAM;Total usage:30.636;Data updated:1433922423;\n"
          "|Component Type:Process;Process name:init;Id:1;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kthreadd;Id:2;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ksoftirqd/0;Id:3;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/0:0H;Id:5;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcu_sched;Id:7;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/0;Id:8;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/1;Id:9;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/2;Id:10;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/3;Id:11;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/4;Id:12;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/5;Id:13;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/6;Id:14;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuos/7;Id:15;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcu_bh;Id:16;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/0;Id:17;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/1;Id:18;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/2;Id:19;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/3;Id:20;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/4;Id:21;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/5;Id:22;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/6;Id:23;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rcuob/7;Id:24;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:migration/0;Id:25;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:watchdog/0;Id:26;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:watchdog/1;Id:27;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:migration/1;Id:28;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ksoftirqd/1;Id:29;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/1:0H;Id:31;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:watchdog/2;Id:32;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:migration/2;Id:33;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ksoftirqd/2;Id:34;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/2:0;Id:35;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/2:0H;Id:36;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:watchdog/3;Id:37;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:migration/3;Id:38;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ksoftirqd/3;Id:39;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/3:0H;Id:41;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:khelper;Id:42;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kdevtmpfs;Id:43;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:netns;Id:44;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:writeback;Id:45;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kintegrityd;Id:46;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:bioset;Id:47;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u17:0;Id:48;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kblockd;Id:49;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ata_sff;Id:50;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:khubd;Id:51;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:md;Id:52;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:devfreq_wq;Id:53;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/1:1;Id:54;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:khungtaskd;Id:56;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kswapd0;Id:57;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ksmd;Id:58;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:khugepaged;Id:59;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:fsnotify_mark;Id:60;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ecryptfs-kthrea;Id:61;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:crypto;Id:62;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kthrotld;Id:74;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/3:1;Id:78;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:deferwq;Id:97;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:charger_manager;Id:98;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kpsmoused;Id:145;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_0;Id:146;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_1;Id:147;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_2;Id:148;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_3;Id:149;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_4;Id:150;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:scsi_eh_5;Id:151;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/2:2;Id:158;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:jbd2/sda5-8;Id:251;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ext4-rsv-conver;Id:252;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:upstart-udev-br;Id:378;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:systemd-udevd;Id:383;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cfg80211;Id:453;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:irq/45-iwlwifi;Id:475;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:hd-audio0;Id:495;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kvm-irqfd-clean;Id:504;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:iwlwifi;Id:505;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kmpathd;Id:522;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kmpath_handlerd;Id:523;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:led_workqueue;Id:545;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:smbd;Id:643;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-daemon;Id:674;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:bluetoothd;Id:753;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ModemManager;Id:772;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:krfcommd;Id:784;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:systemd-logind;Id:795;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rsyslogd;Id:799;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:NetworkManager;Id:833;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:smbd;Id:839;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:avahi-daemon;Id:849;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:avahi-daemon;Id:850;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:polkitd;Id:863;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:upstart-file-br;Id:911;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:upstart-socket-;Id:914;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:wpa_supplicant;Id:1014;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1121;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1123;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1129;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1130;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1134;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cron;Id:1185;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:mdm;Id:1234;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:irqbalance;Id:1251;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cups-browsed;Id:1296;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:mdm;Id:1302;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:mysqld;Id:1321;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:acpid;Id:1348;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:Xorg;Id:1369;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kerneloops;Id:1382;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:getty;Id:1442;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-launch;Id:1490;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-daemon;Id:1491;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kauditd;Id:1617;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gnome-keyring-d;Id:1620;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:console-kit-dae;Id:1625;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cinnamon-sessio;Id:1696;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:ssh-agent;Id:1833;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-launch;Id:1836;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-daemon;Id:1837;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:at-spi-bus-laun;Id:1909;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dbus-daemon;Id:1914;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:at-spi2-registr;Id:1917;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cinnamon-settin;Id:1928;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:pulseaudio;Id:1937;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:rtkit-daemon;Id:1939;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:upowerd;Id:1947;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfsd;Id:2017;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfsd-fuse;Id:2030;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfs-udisks2-vo;Id:2138;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:udisksd;Id:2141;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfs-gphoto2-vo;Id:2151;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfs-mtp-volume;Id:2155;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfs-afc-volume;Id:2159;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cinnamon-launch;Id:2163;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:colord;Id:2165;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:csd-printer;Id:2170;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cinnamon;Id:2175;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:nemo;Id:2182;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:nm-applet;Id:2183;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:polkit-gnome-au;Id:2187;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dropbox;Id:2196;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:dconf-service;Id:2206;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gconfd-2;Id:2218;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfsd-metadata;Id:2221;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:gvfsd-trash;Id:2227;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:accounts-daemon;Id:2261;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/3:2;Id:2265;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:konsole;Id:2313;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:bash;Id:2317;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:mintupdate-laun;Id:2417;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cinnamon-screen;Id:2418;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:sh;Id:2421;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:mintUpdate;Id:2422;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:cupsd;Id:2457;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:applet.py;Id:2469;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:eclipse;Id:2474;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:java;Id:2476;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/1:1H;Id:4296;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/2:1H;Id:4297;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/3:1H;Id:4298;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:irq/44-mei_me;Id:4299;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u16:53;Id:4339;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u16:55;Id:4341;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:hci0;Id:4359;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:hci0;Id:4360;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/1:2;Id:4569;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/0:1;Id:4915;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u17:1;Id:5051;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/0:2;Id:5404;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u17:2;Id:5649;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/0:0;Id:5676;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:kworker/u16:0;Id:5727;CPU Usage:0;Data updated:1433922423;||Component Type:Process;Process name:computer_monito;Id:5807;CPU Usage:0;Data updated:1433922423;|\n"
          "|Component Type:Sensor;Sensor name:acpitz_temp1_input;Value:49;Type:1;Data updated:1433922423;||Component Type:Sensor;Sensor name:acpitz_temp2_input;Value:29.8;Type:1;Data updated:1433922423;||Component Type:Sensor;Sensor name:coretemp_temp1_input;Value:54;Type:1;Data updated:1433922423;||Component Type:Sensor;Sensor name:coretemp_temp2_input;Value:54;Type:1;Data updated:1433922423;||Component Type:Sensor;Sensor name:coretemp_temp3_input;Value:52;Type:1;Data updated:1433922423;|\n");

  //std::cout << ci.toString();
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
