/*
 * ProcessesWidget.hpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#ifndef PROCESSESWIDGET_HPP_
#define PROCESSESWIDGET_HPP_

#include "ui_ProcessesWidget.h"
#include <QWidget>
#include "ComputerInfoDataContainerWrapper.hpp"
#include "AllProcessesModel.hpp"
#include "ComputerMonitorWidgetBase.hpp"

/*!
 * \brief Klasa odpowiedzialna za prezentację danych o wszystkich procesach w systemie
 *
 * Pokazuje w prosty sposób informacje o poszczególnych procesach w tabeli i na wykresie
 */
class ProcessesWidget: public ComputerMonitorWidgetBase, Ui::UiProcessesWidget
{
    Q_OBJECT
  public:
    ProcessesWidget(QWidget* parent = nullptr): ComputerMonitorWidgetBase(parent), m_currentRow(-1) { init(); }

    /*!
     * \brief Metoda ustawia wskaźnik na obiekt informacji o komputerze
     *
     * Metoda jednocześnie ustawia wszystkie sygnały oraz sloty aby
     * aktualizacja informacji była automatyczna
     *
     * \param compInfo - wskaźnik na obiekt informacji, który ma zostać ustawiony
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);

    void clear();

  public slots:
    void savePlot() override { ComputerMonitorWidgetBase::savePlot(customPlot); }

  private:
    /*!
     * \brief Metoda inicjująca wygląd kontrolki
     *
     * Inicjalizuje i ustawia wygląd wszystkich komponentów kontrolki
     */
    void init();

    /*!
     * \brief Metoda dodaje wpisy do wyboru rysowanej wielkości na wykresie
     */
    void addDataTypeToCombo();

    /*!
     * \brief Pole przechowujące wskaźnik na obiekt odpowiedzialny za informacje o komputerze
     */
    const ComputerInfoDataContainerWrapper* m_compInfo;

    /*!
     * \brief Pole przechowujące index aktualnie zaznaczonego wiersza w tabel procesów
     */
    int m_currentRow;

    /*!
     * \brief Pole przechowujące model tabeli wyświetlające wszystkie procesy
     */
    AllProcessesModel* m_model;
  private slots:

  /*!
   * \brief Slot obsługi zmiany zaznaczenia w tabeli procesów
   *
   */
    void onSelectionRowChanged(const QItemSelection &, const QItemSelection &);

    /*!
     * \brief Slot obsługi aktualizacji danych
     *
     * Aktualizuje dane na wykresie
     */
    void updatePlot();
};

#endif /* PROCESSESWIDGET_HPP_ */
