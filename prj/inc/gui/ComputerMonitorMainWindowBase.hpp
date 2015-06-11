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
#include <QTcpSocket>
#include <QTimer>


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
    QTimer* m_timer;
    QTcpSocket* m_tcpSocket;
    static QPalette s_defaultPalette;
  protected slots:
    void selectDarkTheme();
    void selectBrightTheme();
    void showAboutDialog();

    virtual void saveSettings();
    virtual void loadSettings();
    void selectTheme(QString themeName);
  private:
    void init();
    QString m_paletteSelected;
};

#endif /* COMPUTERMONITORMAINWINDOWBASE_HPP_ */
