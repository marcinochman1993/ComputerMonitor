/*
 * ModeSelectionDialog.hpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#ifndef MODESELECTIONDIALOG_HPP_
#define MODESELECTIONDIALOG_HPP_

#include <QDialog>
#include "ui_ModeSelectionDialog.h"

/*!
 * \brief Jest to okno wyboru trybu pracy aplikacji
 *
 * Pozwala wybrać trzy tryby: monitorowania, raportowania, monitorowania i raportowania
 */
class ModeSelectionDialog: public QDialog, Ui::UiModeSelectionDialog
{
    Q_OBJECT

  public:
    /*!
     * \brief Konstruktor klasy ModeSelectionDialog
     *
     * Inicjuje okno dialogowe oraz ustawia rodzica okna dialogowego
     * @param parent - wskaźnik na rodzica okna, jeśli nie jest podane to domyślnie wynosi nullptr
     */
    ModeSelectionDialog(QWidget* parent = nullptr):QDialog(parent) { init(); }
  private:
    /*!
     * \brief Metoda inicjująca okno dialogowe
     *
     * Inicjuje wygląd okna dialogowego
     */
    void init();
};


#endif /* MODESELECTIONDIALOG_HPP_ */
