/*
 * ComputerInfo.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef COMPUTERINFO_HPP_
#define COMPUTERINFO_HPP_

#include "Info.hpp"
#include "SensorsVector.hpp"
#include "RamInfo.hpp"
#include "ProcessorInfo.hpp"
#include "AllProcessesInfo.hpp"
#include "ProcessorInfo.hpp"
#include "RamInfo.hpp"

/*!
 * \brief Klasa reprezentująca informacje o komputerze
 *
 * Klasa przechowuje informacje o komputerze
 */
class ComputerInfo: public Info
{
  public:
    /*!
     * \brief Domyślny konstruktor klasy ComputerInfo
     *
     * Inicjuje podstawowe struktury przechowujące informacje o stanie komputera.
     */
    ComputerInfo(): m_sensors(SensorInfo::allSensors()) { }

    /*!
     * \brief Pozwala na aktualizacje informacji o komputerze
     *
     * Aktualizuje wszystkie informacje o komputerze
     *
     * \return Zwraca true, jeśli wszystko się powiedzie. Jeśli pojawi się błąd zwróci false.
     */
    bool update() override;

    bool update(const std::string& strFromNet);

    /*!
     * \brief Pozwala dostać się do zbioru wszystkich czujników
     *
     * \return Zwraca wektor czujników dostępnych na komputerze.
     */
    const SensorsVector& allSensors() const { return m_sensors; }

    /*!
     * \brief Pozwala dostać się do zbioru wszystkich procesów
     *
     * \return Zwraca zbiór procesów dostępnych na komputerze.
     */
    const AllProcessesInfo& allProcesses() const { return m_allProcesses; }

  /*!
   * \brief Metoda pozwalająca pobrać informacje o procesorze
   *
   * \return Zwracany jest obiekt przechowujący informacje o procesorze
   */
    const ProcessorInfo& processor() const { return m_processor; }

    /*!
     * \brief Metoda pozwalająca pobrać informacje o pamięci ram
     *
     * \return Zwracany jest obiekt przechowujący informacje o procesorze
     */
    const RamInfo& ram() const { return m_ram; }

    std::string toString(unsigned flags = 0) const override;
  private:
    /*!
     * \brief Pole przechowujące czujniki
     */
    SensorsVector m_sensors;

    /*!
     * \brief Pole przechowujące czujniki
     */
    AllProcessesInfo m_allProcesses;

    /*!
     * \brief Pole przechowujące informacje o procesorze
     */
    ProcessorInfo m_processor;

    /*!
     * \brief Pole przechowujące informacje o pamięci RAM
     */
    RamInfo m_ram;
};


#endif /* COMPUTERINFO_HPP_ */
