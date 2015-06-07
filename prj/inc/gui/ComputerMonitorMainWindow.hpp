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
            m_modeActionGroup(nullptr) { init(mode); }

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

  private slots:
    void on_actionVisualisation_triggered() { changeModeToVisualisation(); }
    void on_actionMixed_triggered() { changeModeToMixed(); }
  private:
    void init(PROGRAM_MODE mode);
    void initModeMenu();
    static const int CONNECTION_TAB_INDEX = 4;
    ComputerInfoDataContainerWrapper* m_dataWrapper;
    std::unique_ptr<ComputerInfo> m_computerInfo;
    ComputerInfoDataContainer m_dataContainer;
    QTimer* m_timer;
    QActionGroup* m_modeActionGroup;
};

#endif /* COMPUTERMONITORMAINWINDOW_HPP_ */
