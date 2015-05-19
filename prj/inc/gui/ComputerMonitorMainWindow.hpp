/*
 * ComputerMonitorMainWindow.hpp
 *
 *  Created on: Mar 13, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORMAINWINDOW_HPP_
#define COMPUTERMONITORMAINWINDOW_HPP_

#include <QMainWindow>
#include "ui_ComputerMonitorMainWindowUi.h"
#include "ComputerInfoDataContainerWrapper.hpp"

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
    ComputerMonitorMainWindow(QWidget* parent = 0): QMainWindow(parent) { setupUi(this); }

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

};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
