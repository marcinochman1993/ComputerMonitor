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

/*!
 * \brief Klasa prezentująca informacje o pamięci RAM
 */
class RamWidget: public QWidget, Ui::UiRamWidget
{
  public:
    /*!
     * \brief Konstruktor klasy RamWidget
     *
     *  Inicjalizuje wygląd kontrolki
     *
     * @param parent - rodzic kontrolki, domyślnie nullptr
     */
    RamWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }
  private:

    /*!
     * \brief Metoda inicjująca wygląd kontrolki
     *
     * Jest wywoływana w konstruktorze
     */
    void init();
};


#endif /* RAMWIDGET_HPP_ */
