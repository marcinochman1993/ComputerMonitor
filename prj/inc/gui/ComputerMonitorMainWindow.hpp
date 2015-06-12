/*
 * ComputerMonitorMainWindow.hpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOW_HPP_
#define COMPUTERMONITORMAINWINDOW_HPP_

#include <QMainWindow>
#include <QTimer>
#include <QActionGroup>
#include "ui_ComputerMonitorMainWindowUi.h"
#include "ComputerInfoDataContainerWrapper.hpp"
#include "ComputerMonitorMainWindowBase.hpp"
#include <memory>
#include <QTcpServer>

/*!
 * \brief Jest to głowne okno aplikacji ComputerMonitor
 *
 * Reprezentuje okno z największą funkcjonalnością programu
 */
class ComputerMonitorMainWindow: public ComputerMonitorMainWindowBase,
    Ui::ComputerMonitorMainWindowUi
{
  Q_OBJECT

  public:

  /*!
   * \brief Typ wyliczeniowy określający tryb pracy programu
   */
    enum class PROGRAM_MODE
    {
      VISUALISATION, //!< Tryb prezentacji
      MIXED, //!< Tryb łączony
    };

    /*!
     * \brief Tworzy główne okno, ustawiając jego rodzica
     *
     * \param mode - tryb programu
     * \param parent - rodzic okna, jeśli nie jest ustawiony to domyślnie jest nullptr
     */
    ComputerMonitorMainWindow(PROGRAM_MODE mode = PROGRAM_MODE::VISUALISATION, QWidget* parent = 0)
        : ComputerMonitorMainWindowBase(parent), m_computerInfo(
            new ComputerInfo), m_dataContainer(m_computerInfo.get()),
            m_modeActionGroup(nullptr),m_selectedTabIndex(0),
            m_tcpServer(nullptr),m_tcpSocketServer(nullptr) { init(mode); }

    /*!
     * \brief Metoda pozwala ustawić obiekt informacji o komputerze
     *
     * Metoda ustawia wszystkie sygnały i sloty tak, aby
     * aktualizacje informacji i ich prezentacja były automatyczne
     *
     * \param compInfo -wskaźnik na obiekt przechowujący i aktualizujący informacje
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);
    /*!
     * \brief Metoda wywoływana w momencie, kiedy następuje żądanie zamknięcia okna
     *
     * Jeśli użytkownik potwierdzi zamykanie aplikacji wtedy zostaną zapisane
     * ustawienia aplikacji
     *
     * \param closeEventData - dane o zdarzeniu
     */
    void closeEvent(QCloseEvent * closeEventData) override;

  protected slots:
  /*!
   * \brief Slot pozwala zmienić tryb aplikacji na łączony
   */
    void changeModeToMixed();
    /*!
     * \brief Slot pozwala zmienić tryb aplikacji na tryb prezentacji
     */
    void changeModeToVisualisation();
    /*!
     * \brief Slot obsługujący kliknięcie przycisku zarządzającego serwerem
     *
     * W zależności od tego czy serwer jest uruchomiony odpowiednio przerywa
     * lub wznawia jego pracę
     */
    void on_serverButton_clicked();

    /*!
     * \brief Slot obsługujący kliknięcie przycisku zarządzającego połączeniem z serwerem
     *
     * W zależności od tego czy połączenie jest ustanowione odpowiednio kończy lub ustanawia
     * połączenie z serwerem
     */
    void on_connectButton_clicked();
    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że do serwera ktoś się podłączył
     *
     * Zmieniana jest wtedy etykieta stanu połączenia serwera
     */
    void onConnectedServer();

    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że uzyskano połączenie z serwerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia
     */
    void onConnectedSocket() { dataReceiveWidget->connectionEstablished(); }

    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że serwer utracił połączenie z komputerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia serwera
     */
    void onDisconnectedServer();

    /*!
     * \brief Slot obsługujący zdarzenie polegające na tym, że utracono połączenie z serwerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia
     */
    void onDisconnectedSocket() { dataReceiveWidget->connectionLost(); }
    /*!
     * \brief Slot obsługujący nawiązanie połączenia przez serwer z komputerem
     *
     * Zmieniana jest wtedy etykieta stanu połączenia serwera
     */
    void initSocket();

  private slots:
  /*!
   * \brief Slot obsługi zmiany trybu aplikacji na tryb prezentacji
   *
   * Program zaczyna pracować w trybie prezentacji
   */
    void on_actionVisualisation_triggered() { changeModeToVisualisation(); }

    /*!
     * \brief Slot obsługi zmiany trybu aplikacji na tryb łączony
     *
     * Program zaczyna pracować w trybie łączonym
     */
    void on_actionMixed_triggered() { changeModeToMixed(); }

    /*!
     * \brief Slot obsługi zmiany zakładki
     * \param index - numer aktualnie wybranej zakładki
     */
    void on_tabWidget_currentChanged(int index) { m_selectedTabIndex = index; }

    /*!
     * \brief Slot obsługi eksportu wykresu do pliku
     *
     * W zależności od wybranej karty zostaje wyeksportowanny odpowiedni wykres
     */
    void on_actionExport_Plot_triggered();

    /*!
     * \brief Slot obsługi wysyłania danych poprzez sieć
     *
     */
    void sendData();

    /*!
     * \brief Slot obsługi odebrania danych poprzez sieć
     *
     * Po odebraniu danych następuje aktualizacja wszystkich kontrolek
     */
    void receiveData();

    /*!
     * \brief Metoda zamykająca połączenie z serwerem
     *
     * Zamyka połączenie z serwerem oraz aktualizuje widok kontrolek
     */
    void stopReceiving();

    /*!
     * \brief Metoda otwierająca połączenie z serwerem
     *
     * Zamyka połączenie z serwerem oraz aktualizuje widok kontrolek
     */
    void startReceiving();
  private:
    /*!
     * \brief Metoda inicjująca okno aplikacji
     *
     * W zależności od wybranego trybu wybierany jest odpowiedni wygląd aplikacji
     *
     * \param mode - tryb pracy aplikacji
     */
    void init(PROGRAM_MODE mode);

    /*!
     * \brief Metoda inicjuje menu wyboru trybu
     *
     * Dodaje menu wyboru trybu oraz łączy odpowiednie sygnały i sloty ze sobą
     */
    void initModeMenu();

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
     * \brief Metoda czyszcząca wszystkie dane z kontrolek.
     *
     * Wszystkie kontrolki nie będą prezentować żadnych danych
     */
    void clear();

    /*!
     * \brief Stała określająca ostatnią zakładkę - konfiguracja połączeń
     */
    static const int CONNECTION_TAB_INDEX = 4;

    /*!
     * \brief Pole przechowujące pośrednika pomiędzy biblioteką SystemMonitoringLib oraz Qt
     */
    ComputerInfoDataContainerWrapper* m_dataWrapper;

    /*!
     * \brief Pole przechowujące unikalny wskaźnik na obiekt przechowujący informacje o komputerze
     */
    std::unique_ptr<ComputerInfo> m_computerInfo;

    /*!
     * \brief Pole przechowujące kontener danych zebranych przez m_computerInfo
     */
    ComputerInfoDataContainer m_dataContainer;

    /*!
     * \brief Grupa akcji związanych z trybem pracy aplikacji
     */
    QActionGroup* m_modeActionGroup;

    /*!
     * \brief Pole przechowujące indeks aktualnie wybranej zakładki
     */
    int m_selectedTabIndex;

    /*!
     * \brief Pole przechowujące wskaźnik do obiektu zarządzającego serwerem
     */
    QTcpServer* m_tcpServer;

    /*!
     * \brief Pole przechowujące wskaźnik do gniazdka
     */
    QTcpSocket* m_tcpSocketServer;
};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
