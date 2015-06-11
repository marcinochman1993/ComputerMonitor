/*
 * ProcessorModel.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef PROCESSORMODEL_HPP_
#define PROCESSORMODEL_HPP_

#include <QAbstractTableModel>
#include "ComputerInfoDataContainerWrapper.hpp"

/*!
 * \brief Model informacji o procesorze
 */
class ProcessorModel: public QAbstractTableModel
{
    Q_OBJECT
  public:

    /*!
     * \brief Konstruktor klasy ProcessorModel
     *
     * Inicjuje model i pozwala ustawić rodzica modelu
     *
     * \param parent
     */
    ProcessorModel(QObject* parent = nullptr):QAbstractTableModel(parent),m_computerInfoData(nullptr), m_lastCoresNum(0) { }
    /*!
     * \brief Metoda określająca ilość wierszy tabeli, do której należy model
     *
     * Jest ona równa ilości procesorów
     *
     * \param parent - parametr ignorowany
     * \return
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /*!
     * \brief Metoda pozwalająca określić ilość
     *
     * \param parent - parametr ignorowany
     *
     * @return - Ilość kolumn tabeli, do której należy model
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}

    /*!
     * \brief Metoda pozwalająca pobrać dane z modelu o odpowiednim indeksie
     * @param index - współrzedne danych w tabeli
     * @param role - rodzaj danych
     * @return Odpowiednie dane dla tabeli
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*!
     * \brief Metoda pozwala pobrać dane o nagłówku tabeli
     *
     * @param section - numer sekcji w nagłówku
     * @param orientation - określa rodzaj nagłówka - pionowy lub poziomy
     * @param role - rodzaj danych
     * @return Zwraca odpowiedni napis dla nagłówka
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /*!
     * \brief Metoda ustawia wskaźnik na obiekt informacji o komputerze
     *
     * Metoda jednocześnie ustawia wszystkie sygnały oraz sloty aby
     * aktualizacja informacji była automatyczna
     *
     * \param compInfo - wskaźnik na obiekt informacji, który ma zostać ustawiony
     */
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);

    void clear();
  private slots:

  /*!
   * \brief Slot, który reaguje na aktualizację danych
   *
   * Wysyła sygnał do widoku, że zostały zaktualizowane dane
   */
    void dataUpdated();
  private:
    /*!
     * \brief Metoda pozwalająca pobrać obiekt reprezentujący informacje o komputerze
     * \return Zwracany jest obiekt reprezentujący informacje o komputerze
     */
    const ComputerInfo& compInfo() const { return m_computerInfoData->dataContainer()->computerInfo(); }

    /*!
     * \brief Metoda pozwalająca pobrać dane o procesorze
     * \param row - numer rdzenia
     * \param column - rodzaj danych
     * \return Zwracane są odpowiednia dane w zależności od rdzenia i rodzaju danych
     */
    QVariant getData(int row, int column) const;

    /*!
     *\brief Pole przechowujące obiekt pośredniczący do obiektu o informacji o komputerze
     */
    ComputerInfoDataContainerWrapper* m_computerInfoData;

    unsigned m_lastCoresNum;

    /*!
     * \brief Stała określająca ilość kolumn w modelu
     */
    static const int COLUMNS_NUM = 3;
};


#endif /* PROCESSORMODEL_HPP_ */
