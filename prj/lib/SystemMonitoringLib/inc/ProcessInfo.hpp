/*
 * ProcessInfo.hpp
 *
 *  Created on: May 3, 2015
 *      Author: mochman
 */

#ifndef PROCESSINFO_HPP_
#define PROCESSINFO_HPP_

#include "Info.hpp"
#include <limits>

/*!
 * \brief Klasa reprezentująca informacje o procesie
 */
class ProcessInfo: public Info
{
  public:

    enum Flags
    {
      NAME = 0x01,
      ID = 0x02,
      CPU_USAGE = 0x04,
      ALL = 0x07,
    };

    /*!
     * \brief Konstruktor klasy ProcessInfo
     *
     * Inicjuje informacje o procesie o podanym id
     *
     * \param id - numer identyfikacyjny procesu
     */
    ProcessInfo(unsigned id = 1)
      :m_id(id), m_cpuUsage(0) ,m_lastSUTime(0), m_lastUpTime(0) { update(); }
    //todo zaimplementować double ramUsage() const { return m_ramUsage; }
    /*!
     * \brief Metoda pozwala pobrać procentowe zużycie procesora przez proces
     *
     * Wartość ta jest obliczana na podstawie pomiaru obecnego oraz wcześniejszego na podstawie
     * czasów wykonywania i spoczynku procesu.
     *
     * @return Zwraca chwilowe procentowe zużycie procesora przez proces
     */
    double cpuUsage() const { return m_cpuUsage; }

    /*!
     * \brief Metoda pozwala odczytać id monitorowanego procesu
     *
     * \return Zwracany jest numer identyfikacyjny procesu
     */
    unsigned id() const { return m_id; }

    /*!
     * \brief Metoda aktualizuje informacje o procesie
     *
     * Odczytuje pliki w katalogu /proc/id aby uzyskać porządane informacje
     *
     * \return true jeśli odczyty się powiodą, w.p.p. false
     */
    bool update() override;

    bool update(const std::string& strFromNet) override;

    const std::string& name() const { return m_name; }

    std::string toString(unsigned flags = 0) const override;
  private:
    /*!
     * \brief Pole przechowujące id procesu
     */
    unsigned m_id;

    //unsigned m_ramUsage; //todo do zaimplementowania

    /*!
     * \brief Pole przechowujące procentowe zużycie procesora przez proces
     */
    double m_cpuUsage;

    /*!
     * \brief Pole przechowujące sumę sTime oraz uTime w tikach
     */
    unsigned m_lastSUTime;

    /*!
     * \brief Pole przechowujące ostatnio pobrany całkowity czas działania systemu
     */
    double m_lastUpTime;

    std::string m_name;
};

#endif /* PROCESSINFO_HPP_ */
