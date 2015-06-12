/*
 * ReceiveInfoWidget.hpp
 *
 *  Created on: Jun 10, 2015
 *      Author: mochman
 */

#ifndef RECEIVEDATAWIDGET_HPP_
#define RECEIVEDATAWIDGET_HPP_

#include <QWidget>
#include "ui_ReceiveInfoWidget.h"

/*!
 * \brief Klasa reprezentująca kontrolkę prezentującą stan obsługi odbierania danych przez sieć
 *
 * Kontrolka implementuje jedynie interfejs graficzny, sama nie obsługuje komunikacji
 */
class ReceiveInfoWidget: public QWidget, Ui::ReceiveInfoWidget
{
    Q_OBJECT

  public:
    /*!
     * \brief Konstruktor klasy ReceiveInfoWidget
     * \param parent - rodzic kontrolki
     */
    ReceiveInfoWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }

    /*!
     * \brief Metoda pozwalająca pobrać ip wpisane przez użytkownika
     * \return Zwracane jest ip wpisane przez użytkownika
     */
    QString ipAddress() const { return ipLineEdit->text(); }

    /*!
     * \brief Metoda pozwalająca pobrać port wpisany przez użytkownika
     * \return Zwracany jest port wpisany przez użytkownika
     */
    unsigned port();

  public slots:
  /*!
   * \brief Slot ustawia odpowiednie etykiety, gdy połączeniie zostało ustanowione
   */
    void connectionEstablished();
    /*!
     * \brief Slot ustawia odpowiednie etykiety, gdy połączeniie zostało utracone
     */
    void connectionLost();

  private slots:
  /*!
   * \brief Slot reaguje na zmiany wprowadzane w polu adresu ip.
   *
   * Odpowiednio zmienia stan przycisku do połączenia z serwerem.
   *
   * \param text - wprowadzony tekst przez użytkownika
   */
    void on_ipLineEdit_textChanged(const QString & text) { changeConnectButtonStatus(); }

    /*!
     * \brief Slot reaguje na zmiany wprowadzane w polu portu.
     *
     * Odpowiednio zmienia stan przycisku do uruchamiania serwera.
     *
     * \param text - wprowadzony tekst przez użytkownika
     */
    void on_portLineEdit_textChanged(const QString & text) { changeConnectButtonStatus(); }

  private:
    /*!
     * \brief Metoda inicjująca całą kontrolkę
     *
     * Inicjuje wygląd, początkowe stany przycisków, opisy etykiet
     */
    void init();

    /*!
     * \brief Metoda inicjuje walidację dla pól adresu oraz portu
     */
    void initValidators();

    /*!
     * \brief Metoda zmienia stan przycisku uruchaminia połączenia
     *
     * W zależnośći od poprawności wprowadzonych danych w polu portu i adresu ip przycisk
     * jest aktywowany lub nie
     */
    void changeConnectButtonStatus();
};

#endif /* RECEIVEINFOWIDGET_HPP_ */
