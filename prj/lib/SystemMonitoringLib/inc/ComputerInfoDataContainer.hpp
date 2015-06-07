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
#include "DataBuffer.hpp"


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
    const DataBuffer<double>& sensorsData(unsigned sensorNum=0) const;
    /*!
     * \brief Metoda pozwala pobrać wektor czasów rejestracji danych
     * \return Zwracany jest wektor czasów, kiedy został stworzony
     */
    const DataBuffer<std::time_t>& time() const { return m_time; }

    /*!
     * \brief Metoda pozwala pobrać wektor zarejestrowanych wartości zużycia procesora
     *
     * Metoda pobiera zużycia procesora odpowiedniego procesu. Jeżeli nie znajdzie informacji
     * dla podanego procesu zostanie zgłoszony wyjątek typu const char*
     *
     * \param processId - numer identyfikacyjny procesu, dla którego mają zostać pobrane dane
     * \return Zwraca wektor zarejestrowanych wartości zużycia procesora dla podanego procesu
     */
    const DataBuffer<double>& cpuUsage(unsigned processId) const;

    /*!
     * \brief Metoda pozwala pobrać wektor zarejestrowanych wartości zużycia rdzenia
     *
     * Metoda pobiera zużycia rdzenia. Jeżeli nie znajdzie informacji
     * dla podanego rdzenia zostanie zgłoszony wyjątek typu const char*
     *
     * \param coreId - numer identyfikacyjny procesu, dla którego mają zostać pobrane dane
     * \return Zwraca wektor zarejestrowanych wartości zużycia rdzenia
     */
    const DataBuffer<double>& coreUsage(unsigned coreId) const;

    /*!
     * \brief Metoda pozwala pobrać wektor zarejestrowane wartości częstotliwości
     * Metoda pobiera częstotliwości dla odpowiedniego rdzenia. Jeżeli nie znajdzie informacji
     * dla podanego procesu zostanie zgłoszony wyjątek typu const char*
     *
     * \param coreId - numer identyfikacyjny procesu, dla którego mają zostać pobrane dane
     * \return Zwraca wektor zarejestrowanych wartości częstotliwości dla podanego rdzenia
     */
    const DataBuffer<double>& frequency(unsigned coreId) const;

/*!
 * \brief Metoda pozwala pobrać wektor zarejestrowanym danych dotyczących zużycia pamięci RAM
 */
    const DataBuffer<double>& totalRamUsage() const { return m_totalRamUsage; }

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

    /*!
     * \brief Metoda do zapamiętywania informacji o czujnikach
     */
    void saveUpdatedSensorsValueInVec();

    /*!
     * \brief Metoda do zapamiętywania informacji o procesach
     */
    void saveUpdatedProcessesValuesInVec();

    /*!
     * \brief Metoda do zapamiętywania informacji o procesorze
     */
    void saveUpdatedProcessorValues();

    /*!
     * \brief Kontener przechowujący częstotliwości poszczególnych rdzeni
     *
     * Kluczem jest numer rdzenia, a wartość to zbiór zapisanych odczytów
     */
    std::map<unsigned, DataBuffer<double>> m_frequency;

    /*!
     * \brief Kontener przechowujący odczyty z poszczególnych czujników
     *
     * Kluczem jest numer czujnika, a wartość to zbiór zapisanych odczytów
     */
    std::map<unsigned, DataBuffer<double>> m_sensorsValues;


    /*!
     * \brief Kontener przechowujący zużycie pamięci przez proces
     *
     * Ze względu na to, że procesy mogą być dodawane dynamicznie, należy
     * przechowywać dla nich osobno wektory czasów pomiaru.
     *
     * Kluczem jest id procesu, a wartość to para wektorów przechowujących wartości oraz czasy
     */
    std::map<unsigned, std::pair<std::vector<DataBuffer<double>>,
    DataBuffer<std::time_t>>> m_processes;

    /*!
     * \brief Kontener asocjacyjny monitorujący informacje o procesorze
     *
     *  Kluczem jest nr rdzenia, a wartościa wektor wektorów danych.
     *  Rodzaj danych przechowywanych w poszczególnych wektorach jest
     *  zależny od indeksu. Patrz \see PROCESSOR_FREQ_INDEX oraz PROCESSOR_COREUSAGE_INDEX
     */
    std::map<unsigned, std::vector<DataBuffer<double>>> m_processorValues;

    /*!
     * \brief Wektor  przechowujący dane o całkowitym zużyciu pamięci
     */
    DataBuffer<double> m_totalRamUsage;

    /*!
     * \brief Pole przechowujące czasy, kiedy zostały dokonane pomiary
     */
    DataBuffer<std::time_t> m_time;

    /*!
     * \brief Pole przechowujące wskaźnik do obiektu monitorującego komputer
     *
     */
    ComputerInfo* m_computerInfo;

    /*!
     * \brief Indeks wektora zużycia procesora przez proces
     */
    static const unsigned CPU_INDEX = 0;

    /*!
     * \brief Indeks wektora częstotliwości procesora
     */
    static const unsigned PROCESSOR_FREQ_INDEX = 0;

    /*!
     * \brief Indeks wektora zużycia procesora
     */
    static const unsigned PROCESSOR_COREUSAGE_INDEX = 1;

    /*!
     * \brief Ilość monitorowanych wartości związanych z procesorem
     */
    static const unsigned PROCESSOR_MONITORED_VALUES_NUM = 2;

    /*!
     * \brief Ilość monitorowanych wartości związanych z procesami
     */
    static const unsigned MONITORED_VALUES_NUM = 1;
};

#endif /* COMPUTERINFODATACONTAINER_HPP_ */
