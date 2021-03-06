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

enum class ProgramMode
{
    SENDING_DATA,
    PRESENTING_DATA,
    MIXED
};


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
     * \param parent - wskaźnik na rodzica okna, jeśli nie jest podane to domyślnie wynosi nullptr
     */
    ModeSelectionDialog(QWidget* parent = nullptr):QDialog(parent), m_mode(ProgramMode::PRESENTING_DATA) { init(); }

    /*!
     * \brief Metoda pozwalająca określić rodzaj wybranego trybu pracy programu
     * \return Zwracany jest wybrany przez użytkownika tryb pracy programu
     */
    ProgramMode programMode() const { return m_mode; }
  private:
    /*!
     * \brief Metoda inicjująca okno dialogowe
     *
     * Inicjuje wygląd okna dialogowego
     */
    void init();

    /*!
     * \brief Pole przechowujące wybrany tryb pracy programu
     */
    ProgramMode m_mode;
  private slots:
  /*!
   * \brief Slot obsługi akceptacji okna dialogowego przez użytkownika
   *
   * Na podstawie ustawionego checkbox'a ustawia odpowiednią wartość m_mode
   */
    void acceptedMode();

};


#endif /* MODESELECTIONDIALOG_HPP_ */
