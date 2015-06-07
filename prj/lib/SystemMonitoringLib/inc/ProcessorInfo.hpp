/*
 * ProcessorInfo.hpp
 *
 *  Created on: Mar 30, 2015
 *      Author: mochman
 */

#ifndef PROCESSORINFO_HPP_
#define PROCESSORINFO_HPP_

#include <vector>
#include <fstream>
#include "HardwareInfo.hpp"

/*!
 * \brief Klasa przechowująca informacje o procesorze
 *
 * Przetwarzając pliki systemowe w /proc potrafi odczytywać
 * informacje o procesorze
 */
class ProcessorInfo: public HardwareInfo
{
  public:

    enum ToStringFlags
    {
      NAME = 0x01,
      CORES_NUM = 0x02,
      TOTAL_USAGE = 0x04,
      CORE_FREQ = 0x08,
      CORE_USAGE = 0x10,
      ALL =  0x1F
    };

    /*!
     * \brief Domyślny konstruktor klasy ProcessorInfo
     *
     * Inicjalizując obiekt jednocześnie aktualizuje informacje
     * o procesorze komputera
     */
    ProcessorInfo():m_totalCpuUsage(0.0), m_lastTotalCpuBusyTime(0.0), m_lastTotalCpuTime(0.0) { update(); }
    /*!
     *\brief Metoda pozwala odczytać częstotliwość odpowiedniego rdzenia
     *
     * \param coreNum - rdzeń procesora - numeracja od 0
     * \return Zwraca częstotliwość rdzenia
     */
    double frequency(unsigned int coreNum) const;

    /*!
     * \brief Metoda pozwala pobrać nazwę procesora
     *
     * \return Zwraca nazwę procesora
     */
    std::string name() const override { return m_name; }

    /*!
     * \brief Metoda pozwala pobrać procentowe zużycie rdzenia procesora
     *
     * Metoda jedynie uwzględnia procesory fizyczne. Nie uwzględnia procesorów logicznych.
     *
     * \param coreNum - numer rdzenia procesora
     * \return Zwracane jest procentowe zużycie zasobów odpowiedniego rdzenia
     */
    double usage(unsigned int coreNum) const;



    double totalUsage() const { return m_totalCpuUsage; }
    /*!
     * \brief Metoda pozwala określić ilość rdzeni procesora
     *
     * \return Zwraca ilość rdzeni procesora
     */
    unsigned int coresNumber() const { return m_coresNum; }
    /*!
     * \brief Metoda aktualizuje informacje o procesorze
     *
     * Odczytując informacje zawarte w folderze /proc
     * aktualizuje informacje o procesorze
     *
     * \return true jeśli odczyty z plików powiodą się, w.p.p. false.
     */
    bool update() override;

    std::string toString(unsigned flags = 0) const override;
  private:
    /*!
     * \brief Metoda parsuje plik /proc/cpuinfo
     *
     * Metoda uzyskuje informacje o częstotliwościach rdzeni.
     *
     * \return true jeśli odczyt pliku się powiedzie, w.p.p. false
     */
    bool parseCpuInfoFile();

    /*!
     * \brief Metoda parsuje plik /proc/stat
     *
     * Metoda uzyskuje informacje o zużyciu procesora.
     *
     * \return true jeśli odczyt pliku się powiedzie, w.p.p. false
     */
    bool parseCpuStatFile();

    /*!
     * \brief Pole przechowujące nazwę procesora
     */
    std::string m_name;
    /*!
     * \brief Pole przechowujące częstotliwości poszczególnych rdzeni
     */
    std::vector<double> m_freq;

    /*!
     * \brief Pole przechowujące ostatni całkowity czas zajęcia procesora
     */
    std::vector<unsigned> m_lastBusyTime;

    /*!
     * \brief Pole przechowujące ostatni całkowity czas pracy procesora
     */
    std::vector<unsigned> m_lastTotalTime;

    /*!
     * \brief Pole przechowujące zużycie procentowe poszczególnych rdzeni
     */
    std::vector<double> m_usage;

    double m_totalCpuUsage;

    double m_lastTotalCpuBusyTime;

    double m_lastTotalCpuTime;

    /*!
     * \brief Pole przechowujące ilość rdzeni procesora
     */
    unsigned int m_coresNum;
};

#endif /* PROCESSORINFO_HPP_ */
