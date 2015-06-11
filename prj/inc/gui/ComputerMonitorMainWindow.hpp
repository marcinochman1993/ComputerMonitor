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

    enum class PROGRAM_MODE
    {
      VISUALISATION, MIXED,
    };

    /*!
     * \brief Tworzy główne okno, ustawiając jego rodzica
     *
     * \param parent - rodzic okna, jeśli nie jest ustawiony to domyślnie jest nullptr
     */
    ComputerMonitorMainWindow(PROGRAM_MODE mode = PROGRAM_MODE::VISUALISATION, QWidget* parent = 0)
        : ComputerMonitorMainWindowBase(parent), m_computerInfo(
            new ComputerInfo), m_dataContainer(m_computerInfo.get()),
            m_modeActionGroup(nullptr),m_selectedTabIndex(0), m_updateSeconds(1),
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
    void closeEvent(QCloseEvent * closeEventData) override;

  protected slots:
    void changeModeToMixed();
    void changeModeToVisualisation();
    void on_serverButton_clicked();
    void on_connectButton_clicked();
    void onConnectedServer();
    void onConnectedSocket() { dataReceiveWidget->connectionEstablished(); }
    void onDisconnectedServer();
    void onDisconnectedSocket() { dataReceiveWidget->connectionLost(); }
    void initSocket();

  private slots:
    void on_actionVisualisation_triggered() { changeModeToVisualisation(); }
    void on_actionMixed_triggered() { changeModeToMixed(); }
    void on_tabWidget_currentChanged(int index) { m_selectedTabIndex = index; }
    void on_actionExport_Plot_triggered();
    void sendData();

    void receiveData();
    void stopReceiving();
    void startReceiving();
  private:
    void init(PROGRAM_MODE mode);
    void initModeMenu();
    void startServer();
    void stopServer();
    void clear();
    static const int CONNECTION_TAB_INDEX = 4;
    ComputerInfoDataContainerWrapper* m_dataWrapper;
    std::unique_ptr<ComputerInfo> m_computerInfo;
    ComputerInfoDataContainer m_dataContainer;
    QActionGroup* m_modeActionGroup;
    int m_selectedTabIndex;
    unsigned m_updateSeconds;
    QTcpServer* m_tcpServer;
    QTcpSocket* m_tcpSocketServer;
};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
