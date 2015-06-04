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
#include "ui_ComputerMonitorMainWindowUi.h"
#include "ComputerInfoDataContainerWrapper.hpp"
#include <memory>


/*!
 * \brief Jest to głowne okno aplikacji ComputerMonitor
 *
 * Reprezentuje okno z największą funkcjonalnością programu
 */
class ComputerMonitorMainWindow: public QMainWindow, Ui::ComputerMonitorMainWindowUi
{
  Q_OBJECT

  public:
  /*!
   * \brief Tworzy główne okno, ustawiając jego rodzica
   *
   * @param parent - rodzic okna, jeśli nie jest ustawiony to domyślnie jest nullptr
   */
    ComputerMonitorMainWindow(QWidget* parent = 0): QMainWindow(parent), m_computerInfo(new ComputerInfo), m_dataContainer(m_computerInfo.get()) { init(); }

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

  private:
    void init();

    ComputerInfoDataContainerWrapper* m_dataWrapper;
    std::unique_ptr<ComputerInfo> m_computerInfo;
    ComputerInfoDataContainer m_dataContainer;
    QTimer* m_timer;
};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
