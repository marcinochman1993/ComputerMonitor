/*
 * ComputerMonitorMainWindowBase.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#include <QApplication>
#include "ComputerMonitorMainWindowBase.hpp"
#include "AboutDialog.hpp"

QPalette ComputerMonitorMainWindowBase::s_defaultPalette;

void ComputerMonitorMainWindowBase::selectDarkTheme()
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

void ComputerMonitorMainWindowBase::selectBrightTheme()
{
  qApp->setPalette(s_defaultPalette);
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
}

void ComputerMonitorMainWindowBase::showAboutDialog()
{
  AboutDialog dialog(this);

  dialog.author("Marcin Ochman");
  dialog.version("0.1.0");
  dialog.programName("Computer Monitor");

  dialog.exec();
}
