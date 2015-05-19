/*
 * ProcessorWidget.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef PROCESSORWIDGET_HPP_
#define PROCESSORWIDGET_HPP_

#include <QWidget>
#include "ui_ProcessorWidget.h"
#include "ComputerInfoDataContainerWrapper.hpp"

/*!
 * \brief Klasa prezentująca informacje o procesorze komputera
 *
 * W przystępny sposób pokazuje informacje o procesorze - zarówno w tabeli oraz na wykresie
 */
class ProcessorWidget: public QWidget, Ui::UiProcessorWidget
{
    Q_OBJECT
  public:
    /*!
     * \brief Konstruktor inicjujący klasę ProcessorWidget
     *
     * Ustawia wygląd kontrolki
     *
     * @param parent - rodzic kontrolki, domyślnie nullptr
     */
    ProcessorWidget(QWidget* parent = nullptr): QWidget(parent), m_compInfo(nullptr), m_currentRow(-1) { init(); }

    /*!
     * \brief Metoda ustawia wskaźnik na obiekt informacji o komputerze
     *
     * Metoda jednocześnie ustawia wszystkie sygnały oraz sloty aby
     * aktualizacja informacji była automatyczna
     *
     * \param computerInfoData - wskaźnik na obiekt informacji, który ma zostać ustawiony
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* computerInfoData);

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
    /*!
     * \brief Slot obsługi zmiany elementu na liście rozwijalnej
     *
     * \param index - indeks wybranego elementu w liście rozwijalnej
     */
    void on_dataTypeCombo_currentIndexChanged(int index);

    private:

    /*!
     * \brief Metoda rysuje wykres na podstawie zaznaczonych informacji
     *
     * Zaznaczone informacje oznaczają numer rdzenia oraz rodzaj rysowanej wielkości
     */
     void drawPlot();

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
};


#endif /* PROCESSORWIDGET_HPP_ */
