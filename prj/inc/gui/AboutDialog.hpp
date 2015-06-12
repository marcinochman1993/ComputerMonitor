/*
 * AboutDialog.hpp
 *
 *  Created on: Jun 9, 2015
 *      Author: mochman
 */

#ifndef ABOUTDIALOG_HPP_
#define ABOUTDIALOG_HPP_

#include <QDialog>
#include "ui_AboutDialog.h"

/*!
 * \brief Okno dialogowe prezetujące informacje o programie.
 */
class AboutDialog: public QDialog, Ui::AboutDialog
{
    Q_OBJECT
  public:
    /*!
     * \brief Kontruktor klasy AboutDialog
     * \param parent - rodzic okna
     */
    AboutDialog(QWidget* parent = nullptr): QDialog(parent) { setupUi(this); }

    /*!
     * \brief Metoda pozwala pobrać autora programu
     * return Zwracany jest autor programu
     */
    QString author() const;

    /*!
     * \brief Metoda pozwala pobrać nazwę programu
     * return Zwracana jest nazwa programu
     */
    QString programName() const;

    /*!
     * \brief Metoda pozwala pobrać wersję programu
     * return Zwracana jest wersja programu
     */
    QString version() const;
  public slots:

  /*!
   * \brief Metoda pozwala ustawić autora programu
   * \param newAuthor - nowy autor programu
   */
    void author(const QString& newAuthor);

    /*!
     * \brief Metoda pozwala ustawić autora programu
     * \param newProgramName - nowa nazwa programu
     */
    void programName(const QString& newProgramName);

    /*!
     * \brief Metoda pozwala ustawić wersję programu
     * \param newVersion - nowa wersja programu
     */
    void version(const QString& newVersion);
};


#endif /* ABOUTDIALOG_HPP_ */
