/*
 * AllProcessesModel.hpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#ifndef ALLPROCESSESMODEL_HPP_
#define ALLPROCESSESMODEL_HPP_


#include <QAbstractTableModel>
#include "ComputerInfoDataContainerWrapper.hpp"

/*!
 * \brief Model wszystkich procesów
 */
class AllProcessesModel: public QAbstractTableModel
{
    Q_OBJECT

  public:

    /*!
     * \brief Konstruktor klasy AllProcessesModel
     *
     * Inicjuje model i pozwala ustawić rodzica modelu
     *
     * \param parent - rodzic modelu, domyślnie nullptr
     */
    AllProcessesModel(QObject* parent=nullptr): QAbstractTableModel(parent), m_computerInfoData(nullptr){ }
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
     * \return - Ilość kolumn tabeli, do której należy model
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}

    /*!
     * \brief Metoda pozwalająca pobrać dane z modelu o odpowiednim indeksie
     * \param index - współrzedne danych w tabeli
     * \param role - rodzaj danych
     * \return Odpowiednie dane dla tabeli
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*!
     * \brief Metoda pozwala pobrać dane o nagłówku tabeli
     *
     * \param section - numer sekcji w nagłówku
     * \param orientation - określa rodzaj nagłówka - pionowy lub poziomy
     * \param role - rodzaj danych
     * \return Zwraca odpowiedni napis dla nagłówka
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

    /*!
     * \brief Metoda określająca id procesu z indeksu
     * \param index - indeks modelu - numer wiersz
     */
    unsigned processIdByIndex(unsigned index) const;
  private:
    /*!
     * \brief Stała określająca ilość kolumn w modelu
     */
    static const int COLUMNS_NUM = 3;

    /*!
     *\brief Pole przechowujące obiekt pośredniczący do obiektu o informacji o komputerze
     */
    ComputerInfoDataContainerWrapper* m_computerInfoData;

    /*!
     * \brief Pole przchowujące wszystkie procesy do wyświetlenia w tabeli
     */
    std::vector<unsigned> m_allProcessesId;

    /*!
     * \brief Metoda pozwalająca pobrać obiekt reprezentujący informacje o komputerze
     * \return Zwracany jest obiekt reprezentujący informacje o komputerze
     */
    const ComputerInfo& compInfo() const { return m_computerInfoData->dataContainer()->computerInfo(); }

    /*!
     * \brief Metoda pozwalająca pobrać dane o procesorze
     * \param row - indeks (numer wiersza) procesu
     * \param column - rodzaj danych
     * \return Zwracane są odpowiednia dane w zależności od row i column
     */
    QVariant getData(unsigned row, unsigned column) const;
  private slots:
  /*!
   * \brief Slot, który reaguje na aktualizację danych
   *
   * Wysyła sygnał do widoku, że zostały zaktualizowane dane
   */
    void dataUpdated();
};


#endif /* ALLPROCESSESMODEL_HPP_ */
