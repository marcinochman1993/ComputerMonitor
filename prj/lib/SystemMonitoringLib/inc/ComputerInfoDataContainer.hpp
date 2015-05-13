/*
 * ComputerInfoDataContainer.hpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFODATACONTAINER_HPP_
#define COMPUTERINFODATACONTAINER_HPP_

#include <map>
#include <chrono>
#include "ComputerInfo.hpp"

/*!
 * \brief Klasa zbierająca informacje o pracy komputera
 *
 * Pozwala zapisywać wszystkie monitorowane wielkości do wektorów
 * Pobieranie wielkości odbywa się za pomocą klasy ComputerInfo
 */
class ComputerInfoDataContainer: public Info
{
  public:
    /*!
     * \brief Konstruktor pozwalający ustawić obiekt do monitorowania zasobów komputera
     *
     * \param computerInfo - wskaźnik na obiekt do monitorowania systemu, domyślnie jest ustawiony na nullptr
     */
    ComputerInfoDataContainer(ComputerInfo* computerInfo = nullptr):m_computerInfo(computerInfo) { }

    /*!
     *
     * \param sensorNum - numer czujnika
     * \return Zwraca wektor danych związanych z czujnikiem o numerze sensorNum
     */
    const std::vector<double>& sensorsData(unsigned sensorNum=0) const;
    /*!
     * \brief Metoda pozwala pobrać wektor czasów rejestracji danych
     * \return Zwracany jest wektor czasów, kiedy został stworzony
     */
    const std::vector<std::chrono::system_clock::time_point>& time() const { return m_time; }

    const std::vector<double>& cpuUsage(unsigned processId) const;

    const std::vector<std::chrono::system_clock::time_point>& ramTime(unsigned processId) const;

    void clear(); //todo do zaimplementowania


    /*!
     * \brief Metoda aktualizująca wpisy w kontenerach danych
     *
     * Metoda odczytuje wartości z monitorowanych wielkości oraz zapisuje je do kontenerów
     *
     * \return Zwraca true jeśli aktualizacja się powiodła, w.p.p. zwraca false
     */
    bool update() override;

    /*!
     * \brief Metoda pozwala pobrać aktualny obiekt monitorujący komputer
     *
     * \return Stała referencja do obiektu monitorującego komputer
     */
    const ComputerInfo& computerInfo() const { return *m_computerInfo; }
  private:
    /*!
     * \brief Metoda inicjuje zasoby potrzebne do zbierania monitorowanych danych
     *
     * Metoda przygotowuje kontener asocjacyjny dla sensorów.
     */
    void init();

    void saveUpdatedSensorsValueInVec();
    void saveUpdatedProcessesValuesInVec();


    /*!
     * \brief Kontener przechowujący częstotliwości poszczególnych rdzeni
     *
     * Kluczem jest numer rdzenia, a wartość to zbiór zapisanych odczytów
     */
    std::map<unsigned, std::vector<double>> m_frequency;

    /*!
     * \brief Kontener przechowujący odczyty z poszczególnych czujników
     *
     * Kluczem jest numer czujnika, a wartość to zbiór zapisanych odczytów
     */
    std::map<unsigned, std::vector<double>> m_sensorsValues;


    /*!
     * \brief Kontener przechowujący zużycie pamięci przez proces
     *
     * Ze względu na to, że procesy mogą być dodawane dynamicznie, należy
     * przechowywać dla nich osobno wektory czasów pomiaru.
     *
     * Kluczem jest id procesu, a wartość to para wektorów przechowujących wartości oraz czasy
     */
    std::map<unsigned, std::pair<std::vector<std::vector<double>>,
        std::vector<std::chrono::system_clock::time_point>>> m_processes;

    /*!
     * \brief Pole przechowujące czasy, kiedy zostały dokonane pomiary
     */
    std::vector<std::chrono::system_clock::time_point> m_time;

    /*!
     * \brief Pole przechowujące wskaźnik do obiektu monitorującego komputer
     *
     */
    ComputerInfo* m_computerInfo;

    static const unsigned CPU_INDEX = 0;
    static const unsigned MONITORED_VALUES_NUM = 1;
};

#endif /* COMPUTERINFODATACONTAINER_HPP_ */
