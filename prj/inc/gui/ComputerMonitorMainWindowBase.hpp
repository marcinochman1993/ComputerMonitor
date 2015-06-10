/*
 * ComputerMonitorMainWindowBase.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOWBASE_HPP_
#define COMPUTERMONITORMAINWINDOWBASE_HPP_

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QApplication>

class ComputerMonitorMainWindowBase: public QMainWindow
{
  Q_OBJECT
  public:
    ComputerMonitorMainWindowBase(QWidget* parent = nullptr)
        : QMainWindow(parent), m_darkThemeAction(nullptr),
          m_defaultThemeAction(nullptr), m_themeActionGroup(nullptr),
          m_themeMenu(nullptr)
    { init(); }

    static void defaultPalette(const QPalette& palette) { s_defaultPalette = palette; }
  protected:
    void initThemeActions(QMenu* optionsMenu);
    QAction* m_darkThemeAction;
    QAction* m_defaultThemeAction;
    QActionGroup* m_themeActionGroup;
    QMenu* m_themeMenu;
    static QPalette s_defaultPalette;
  protected slots:
    void selectDarkTheme();
    void selectBrightTheme();
    void showAboutDialog();
  private:
    void init();
};

#endif /* COMPUTERMONITORMAINWINDOWBASE_HPP_ */
