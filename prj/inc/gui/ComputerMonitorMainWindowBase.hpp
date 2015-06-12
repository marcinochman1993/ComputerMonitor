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


/*!
 * \brief Klasa bazowa dla okien aplikacji ComputerMonitor
 */
class ComputerMonitorMainWindowBase: public QMainWindow
{
  Q_OBJECT

  public:

  /*!
   * Konstruktor klasy ComputerMonitorMainWindowBase
   * \param parent - rodzic okna
   */
    ComputerMonitorMainWindowBase(QWidget* parent = nullptr)
        : QMainWindow(parent), m_darkThemeAction(nullptr),
          m_defaultThemeAction(nullptr), m_themeActionGroup(nullptr),
          m_themeMenu(nullptr)
    { init(); }

    /*!
     * \brief Metoda ustawiająca domyślną paletę barw aplikacji
     * \param palette - nowa domyślna paleta
     */
    static void defaultPalette(const QPalette& palette) { s_defaultPalette = palette; }
  protected:

    /*!
     * \brief Metoda inicjuje menu wyboru kolorów aplikacji
     * \param optionsMenu - wskaźnik do menu opcji
     */
    void initThemeActions(QMenu* optionsMenu);

    /*!
     * \brief Pole przechowujące wskaźnik do akcji wyboru ciemnej palety kolorów
     */
    QAction* m_darkThemeAction;

    /*!
     * \brief Pole przechowujące wskaźnik do akcji wyboru domyślnej palety kolorów
     */
    QAction* m_defaultThemeAction;

    /*!
     * \brief Pole przechowujące wskaźnik do grupy akcji wyboru palety kolorów
     */
    QActionGroup* m_themeActionGroup;

    /*!
     * \brief Pole przechowujące wskaźnik do menu wyboru palety kolorów
     */
    QMenu* m_themeMenu;

    /*!
     * \brief Pole przechowujące wskaźnik do timera
     */
    QTimer* m_timer;

    /*!
     * \brief Pole wskazujące na gniazdko
     */
    QTcpSocket* m_tcpSocket;

    /*!
     * \brief Pole statyczne przechowujące domyślną paletę kolorów
     */
    static QPalette s_defaultPalette;
  protected slots:
  /*!
   * \brief Slot wyboru ciemnej palety kolorów
   */
    void selectDarkTheme();
    /*!
     * \brief Slot wyboru jasnej(domyślnej) palety kolorów
     */
    void selectBrightTheme();

    /*!
     * \brief Slot pokazujący okno dialogowe "O programie"
     */
    void showAboutDialog();

    /*!
     * \brief Slot pozwalający na zapisywanie ustawień aplikacji
     */
    virtual void saveSettings();

    /*!
     * \brief Slot pozwalający na ładowanie ustawień aplikacji
     */
    virtual void loadSettings();

    /*!
     * \brief Metoda pozwalająca wybrać paletę kolorów na podstawie nazwy
     * \param themeName -nazwa palety kolorów
     */
    void selectTheme(QString themeName);
  private:
    /*!
     * \brief Metoda inicjuje wszystkie podstawowe elementy głównego okna aplikacji
     */
    void init();

    /*!
     * \brief Pole przechowujące informacje o wybranej palecie kolorów
     */
    QString m_paletteSelected;
};

#endif /* COMPUTERMONITORMAINWINDOWBASE_HPP_ */
