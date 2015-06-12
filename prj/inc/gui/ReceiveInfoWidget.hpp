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
     * \brief
     * \param parent - rodzic kontrolki
     */
    ReceiveInfoWidget(QWidget* parent = nullptr): QWidget(parent) { init(); }

    QString ipAddress() const { return ipLineEdit->text(); }
    unsigned port();

  public slots:
    void connectionEstablished();
    void connectionLost();

  private slots:
    void on_ipLineEdit_textChanged(const QString & text) { changeConnectButtonStatus(); }
    void on_portLineEdit_textChanged(const QString & text) { changeConnectButtonStatus(); }

  private:
    void init();
    void initValidators();
    void changeConnectButtonStatus();
};

#endif /* RECEIVEINFOWIDGET_HPP_ */
