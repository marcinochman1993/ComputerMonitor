/*
 * RamWidget.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef RAMWIDGET_HPP_
#define RAMWIDGET_HPP_

#include <QWidget>
#include "ui_RamWidget.h"
#include "ComputerInfoDataContainerWrapper.hpp"
#include "ComputerMonitorWidgetBase.hpp"

/*!
 * \brief Klasa prezentująca informacje o pamięci RAM
 */
class RamWidget: public ComputerMonitorWidgetBase, Ui::UiRamWidget
{
    Q_OBJECT
  public:
    /*!
     * \brief Konstruktor klasy RamWidget
     *
     *  Inicjalizuje wygląd kontrolki
     *
     * \param parent - rodzic kontrolki, domyślnie nullptr
     */
    RamWidget(QWidget* parent = nullptr): ComputerMonitorWidgetBase(parent) { init(); }

    /*!
     * \brief Metoda ustawia wskaźnik na obiekt informacji o komputerze
     *
     * Metoda jednocześnie ustawia wszystkie sygnały oraz sloty aby
     * aktualizacja informacji była automatyczna
     *
     * \param computerInfoData - wskaźnik na obiekt informacji, który ma zostać ustawiony
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* computerInfoData);

    void clear();

  public slots:
    void savePlot() override { ComputerMonitorWidgetBase::savePlot(customPlot); }
  private slots:
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
     * Jest wywoływana w konstruktorze
     */
    void init();

    /*!
     * brief Metoda odpowiedzialna za rysowanie i inicjację wykresu
     */
    void drawPlot();

    /*!
     * \brief Pole przechowujące wskaźnik na obiekt odpowiedzialny za informacje o komputerze
     */
    const ComputerInfoDataContainerWrapper* m_compInfo;
};

#endif /* RAMWIDGET_HPP_ */
