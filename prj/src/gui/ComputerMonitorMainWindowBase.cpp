/*
 * ComputerMonitorMainWindowBase.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#include <QApplication>
#include <QSettings>
#include "ComputerMonitorMainWindowBase.hpp"
#include "AboutDialog.hpp"
#include <iostream>

QPalette ComputerMonitorMainWindowBase::s_defaultPalette;

void ComputerMonitorMainWindowBase::selectDarkTheme()
{
  QPalette palette;
  palette.setColor(QPalette::Window, QColor(80, 80, 80));
  palette.setColor(QPalette::WindowText, Qt::white);
  palette.setColor(QPalette::Base, QColor(110, 110, 110));
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
  m_paletteSelected = "Dark";
}

void ComputerMonitorMainWindowBase::selectBrightTheme()
{
  qApp->setPalette(s_defaultPalette);
  m_paletteSelected = "Default";
}

void ComputerMonitorMainWindowBase::initThemeActions(QMenu* optionsMenu)
{
  if (optionsMenu == nullptr)
    return;

  m_themeMenu = new QMenu(tr("Theme"), this);

  m_themeActionGroup = new QActionGroup(this);
  m_themeActionGroup->setExclusive(true);

  m_darkThemeAction = new QAction(tr("Dark theme"), this);
  m_darkThemeAction->setCheckable(true);

  m_defaultThemeAction = new QAction(tr("Bright theme"), this);
  m_defaultThemeAction->setCheckable(true);
  m_defaultThemeAction->setChecked(true);

  m_themeActionGroup->addAction(m_darkThemeAction);
  m_themeActionGroup->addAction(m_defaultThemeAction);

  m_themeMenu->addAction(m_darkThemeAction);
  m_themeMenu->addAction(m_defaultThemeAction);

  optionsMenu->addMenu(m_themeMenu);

  connect(m_defaultThemeAction, SIGNAL(triggered()), this,
      SLOT(selectBrightTheme()));
  connect(m_darkThemeAction, SIGNAL(triggered()), this,
      SLOT(selectDarkTheme()));
}

void ComputerMonitorMainWindowBase::init()
{
  setAttribute(Qt::WA_DeleteOnClose);
  loadSettings();
  selectTheme(m_paletteSelected);
}

void ComputerMonitorMainWindowBase::showAboutDialog()
{
  AboutDialog dialog(this);

  dialog.author("<h2>Marcin Ochman</h2>");
  dialog.version("<h3>0.1.0</h3>");
  dialog.programName("<h1>Computer Monitor</h1>");
  dialog.exec();
}

void ComputerMonitorMainWindowBase::saveSettings()
{
  QSettings settings;
  settings.beginGroup("Theme");

  settings.setValue("Palette", m_paletteSelected);

  settings.endGroup();
}

void ComputerMonitorMainWindowBase::loadSettings()
{
  QSettings settings;
  settings.beginGroup("Theme");

  m_paletteSelected = settings.value("Palette", "Default").toString();

  settings.endGroup();
}

void ComputerMonitorMainWindowBase::selectTheme(QString themeName)
{
  if (themeName == "Dark")
    selectDarkTheme();
  if (themeName == "Default")
    selectBrightTheme();
}
