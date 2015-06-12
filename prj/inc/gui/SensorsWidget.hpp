/*
 * SensorsWidget.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef SENSORSWIDGET_HPP_
#define SENSORSWIDGET_HPP_

#include <QWidget>
#include "ui_SensorsWidget.h"
#include "AllSensorsModel.hpp"
#include "ComputerMonitorWidgetBase.hpp"

/*!
 * \brief Kontrolka odpowiedzalna za prezentację informacji o czujnikach
 *
 * Pokazuje w tabeli wszystkie dostępne czujniki wraz
 * z aktualnymi odczytami oraz prezentuje odczyty na wykresie
 */
class SensorsWidget: public ComputerMonitorWidgetBase, Ui::UiSensorsWidget
{
    Q_OBJECT

  public:
    /*!
     * Konstuktor klasy SensorsWidget
     *
     * Inicjuje wygląd kontrolki oraz ustawia jej rodzica
     *
     * \param parent - rodzica kontrolki, domyślnie nullptr
     */
    SensorsWidget(QWidget* parent = nullptr)
    : ComputerMonitorWidgetBase(parent), m_currentRow(-1),m_sensorsModel(nullptr) { init(); }

    /*!
     * \brief Metoda ustawia wskaźnik na obiekt informacji o komputerze
     *
     * Metoda jednocześnie ustawia wszystkie sygnały oraz sloty aby
     * aktualizacja informacji była automatyczna
     *
     * \param computerInfoData - wskaźnik na obiekt informacji, który ma zostać ustawiony
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* computerInfoData);

    /*!
     * \brief Usuwa wszystkie informacje prezentowane przez kontrolkę
     */
    void clear();

  public slots:
  /*!
   * \brief Metoda pozwala zapisać wykres do pliku
   */
    void savePlot() override { ComputerMonitorWidgetBase::savePlot(customPlot); }

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

  private:
    /*!
     * \brief Metoda inicjująca wygląd kontrolki
     *
     * Inicjalizuje i ustawia wygląd wszystkich komponentów kontrolki
     */
    void init();

    /*!
     * \brief Pole przechowujące wskaźnik na obiekt odpowiedzialny za informacje o komputerze
     */
    const ComputerInfoDataContainerWrapper* m_compInfo;

    /*!
     * \brief Pole przechowujące index aktualnie zaznaczonego wiersza w tabeli czujników
     */
    int m_currentRow;

    /*!
     * \brief Pole przechowujące wskaźnik do modelu wszystkich czujników
     */
    AllSensorsModel* m_sensorsModel;
};

#endif /* SENSORSWIDGET_HPP_ */
