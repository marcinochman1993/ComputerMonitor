/*
 * ComputerMonitorMainWindowSend.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOWSEND_HPP_
#define COMPUTERMONITORMAINWINDOWSEND_HPP_

#include "ComputerMonitorMainWindowBase.hpp"
#include "ui_ComputerMonitorMainWindowSend.h"
#include <QTreeWidgetItem>
#include <QTcpServer>
#include "ComputerInfo.hpp"
#include <QSystemTrayIcon>

/*!
 * \brief Główne okno aplikacji w trybie wysyłania danych
 */
class ComputerMonitorMainWindowSend: public ComputerMonitorMainWindowBase, Ui::ComputerMonitorMainWindowSendUi
{
    Q_OBJECT

  public:
    /*!
     * \brief Konstruktor klasy ComputerMonitorMainWindowSend
     * \param parent - rodzic okna
     */
    ComputerMonitorMainWindowSend(QWidget* parent = nullptr): ComputerMonitorMainWindowBase(parent) { init(); }

    /*!
     * \brief Metoda wywoływana w momencie, kiedy następuje żądanie zamknięcia okna
     *
     * Jeśli użytkownik potwierdzi zamykanie aplikacji wtedy zostaną zapisane
     * ustawienia aplikacji
     *
     * \param closeEventData - dane o zdarzeniu
     */
    void closeEvent(QCloseEvent* closeEventData) override;

  protected:
    /*!
     * \brief Metoda obsługująca różne zdarzenia okna
     *
     * Obsługuje minimalizację okna do zasbonika systemowego
     *
     * \param event - informacje o zdarzeniu
     */
    void changeEvent(QEvent* event) override;

  private slots:
  /*!
   * \brief Slot obsługujący kliknięcie przycisku zarządzającego serwerem
   *
   * W zależności od tego czy serwer jest uruchomiony odpowiednio przerywa
   * lub wznawia jego pracę
   */
    void on_serverButton_clicked();

    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że do serwera ktoś się podłączył
     *
     * Zmieniana jest wtedy etykieta stanu połączenia serwera
     */
    void onConnected();

    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że uzyskano połączenie z serwerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia
     */
    void onDisconnected();

    /*!
     * \brief Slot obsługujący nawiązanie połączenia przez serwer z komputerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia serwera
     */
    void initSocket();

    /*!
     * \brief Slot obsługi wysyłania danych poprzez sieć
     * W zależności od wybranych komponentów, które mają zostać wysłane,
     *  dane są wysyłane poprzez sieć
     */
    void sendData();

    /*!
     * \brief Slot obsługi aktywacji ikony z zasobnika systemowego
     * \param reason - powód, dla którego ikona została aktywowana
     */
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
  private:
    /*!
     * \brief Metoda inicjująca okno aplikacji
     *
     * Inicjuje wygląd oraz podstawowe elementy aplikacji
     */
    void init();
    /*!
     * \brief Metoda uruchamia serwer wysyłania danych o komputerze
     *
     * Uruchamia serwer oraz aktualizuje odpowiednie kontrolki
     */
    void startServer();

    /*!
     * \brief Metoda zatrzymuje serwer wysyłania danych o komputerze
     *
     * Uruchamia serwer oraz aktualizuje odpowiednie kontrolki
     */
    void stopServer();

    /*!
     * \brief Metoda inicjuje ikonę znajdującą się w zasobniku systemowym
     *
     * Łączy sygnał podwójnego kliknięcia ze zniknięciem ikony
     */
    void initSystemTrayIcon();

    /*!
     * \brief Pole przechowujące wskaźnik do obiektu zarządzającego serwerem
     */
    QTcpServer* m_tcpServer;

    /*!
     * \brief Pole przechowujące obiekt odzpowiedzialny za informacje o komputerze
     */
    ComputerInfo m_compInfo;

    /*!
     * \brief Pole przchowujące wskaźnik na obiekt odpowiedizalny za zarządzenie ikoną w systemowym zasobniku
     */
    QSystemTrayIcon* m_trayIcon;
};

#endif /* COMPUTERMONITORMAINWINDOWSEND_HPP_ */
