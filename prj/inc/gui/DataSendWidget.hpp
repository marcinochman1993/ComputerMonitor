/*
 * DataSendWidget.hpp
 *
 *  Created on: Jun 6, 2015
 *      Author: mochman
 */

#ifndef DATASENDWIDGET_HPP_
#define DATASENDWIDGET_HPP_

#include <QWidget>
#include "ui_DataSendWidget.h"
#include "ComputerInfo.hpp"

/*!
 * \brief Klasa reprezentująca kontrolkę prezentującą stan obsługi wysyłania danych przez sieć
 *
 * Kontrolka implementuje jedynie interfejs graficzny, sama nie wykonuje komunikacji
 */
class DataSendWidget: public QWidget, Ui::DataSendWidgetUi
{
  Q_OBJECT
  public:
  /*!
   * \brief Konstruktor klasy DataSendWidget
   * \param parent - rodzic kontrolki
   */
    DataSendWidget(QWidget* parent = nullptr)
        : QWidget(parent) { init(); }

    /*!
     * \brief Metoda pozwalająca pobrać ip wpisane przez użytkownika
     * \return Zwracane jest ip wpisane przez użytkownika
     */
    QString ipAddress() const { return ipAddressLineEdit->text(); }

    /*!
     * \brief Metoda pozwalająca pobrać port wpisany przez użytkownika
     * \return Zwracany jest port wpisany przez użytkownika
     */
    unsigned port() const;

    /*!
     * \brief Metoda pozwala określić, które elementy wysyłać poprzez sieć
     * \return Zwracany jest obiekt typu ComputerInfo::ToStringStruct określający, które dane zostaną wysłane
     */
    ComputerInfo::ToStringStruct toStringStruct() const { return m_toStringStruct; }

  public slots:
  /*!
   * \brief Slot ustawia odpowiednie etykiety, gdy połączeniie zostało ustanowione
   */
    void connectionEstablished();
    /*!
     * \brief Slot ustawia odpowiednie etykiety, gdy połączeniie zostało utracone
     */
    void connectionLost();

    /*!
     * \brief Slot ustawia odpowiednie etykiety, gdy serwer rozpoczął pracę
     */
    void startedServer();

    /*!
     * \brief Slot ustawia odpowiednie etykiety, gdy serwer zakończył pracę
     */
    void stoppedServer();
  protected slots:
  /*!
   * \brief Slot reaguje na zmianę elementu na drzewku.
   */
    void on_dataSendTree_itemChanged(QTreeWidgetItem * item, int column);

    /*!
     * \brief Slot reaguje na zmiany wprowadzane w polu adresu ip.
     *
     * Odpowiednio zmienia stan przycisku do uruchamiania serwera.
     *
     * \param text - wprowadzony tekst przez użytkownika
     */
    void on_ipAddressLineEdit_textChanged(const QString & text) { changeServerButtonStatus(); }

    /*!
     * \brief Slot reaguje na zmiany wprowadzane w polu portu.
     *
     * Odpowiednio zmienia stan przycisku do uruchamiania serwera.
     *
     * \param text - wprowadzony tekst przez użytkownika
     */
    void on_portLineEdit_textChanged(const QString & text) { changeServerButtonStatus(); }
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
    void initValidation();
    /*!
     * \brief Metoda inicjuje strukturę określającą co należy wysyłać przez sieć
     */
    void initToStringStruct();
    /*!
     * \brief Metoda zmienia stan przycisku uruchaminia/zatrzymania serwera
     *
     * W zależnośći od poprawności wprowadzonych danych w polu portu i adresu ip przycisk
     * jest aktywowany lub nie
     */
    void changeServerButtonStatus();
    /*!
     * \brief Metoda pozwala zmienić, które dane procesora będą wysyłane przez sieć
     * \param itemText - nazwa elementu, który ma zostać ustawiony do wysyłania lub nie
     * \param checked - określa czy dany element jest zaznaczony czy nie
     */
    void processProcessorDataSendOptions(const QString& itemText, bool checked);

    /*!
     * \brief Metoda pozwala zmienić, które dane procesów będą wysyłane przez sieć
     * \param itemText - nazwa elementu, który ma zostać ustawiony do wysyłania lub nie
     * \param checked - określa czy dany element jest zaznaczony czy nie
     */
    void processProcessesDataSendOptions(const QString& itemText, bool checked);

    /*!
     * \brief Metoda pozwala zmienić, które dane pamięci RAM będą wysyłane przez sieć
     * \param itemText - nazwa elementu, który ma zostać ustawiony do wysyłania lub nie
     * \param checked - określa czy dany element jest zaznaczony czy nie
     */
    void processRamDataSendOptions(const QString& itemText, bool checked);

    /*!
     * \brief Metoda pozwala zmienić, które dane czujników będą wysyłane przez sieć
     * \param itemText - nazwa elementu, który ma zostać ustawiony do wysyłania lub nie
     * \param checked - określa czy dany element jest zaznaczony czy nie
     */
    void processSensorsDataSendOptions(const QString& itemText, bool checked);

    /*!
     * \brief Pole określające, co zostanie wysłane przez sieć
     */
    ComputerInfo::ToStringStruct m_toStringStruct;
};

#endif /* DATASENDWIDGET_HPP_ */
