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
    /*!
     * \brief Pozwala dostać się do zbioru wszystkich wektorów
     *
     * \return Zwraca wektor czujników dostępnych na komputerze.
     */
    const SensorsVector& allSensors() const { return m_sensors; }

  private:
    /*!
     * \brief Pole przechowujące czujniki
     */
    SensorsVector m_sensors;
};


#endif /* COMPUTERINFO_HPP_ */
