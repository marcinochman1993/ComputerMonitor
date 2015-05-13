/*
 * RamInfo.hpp
 *
 *  Created on: Apr 22, 2015
 *      Author: mochman
 */

#ifndef RAMINFO_HPP_
#define RAMINFO_HPP_

#include "HardwareInfo.hpp"

/*!
 * \brief Klasa zbierająca informacje o pamięci typu RAM komputera
 */
class RamInfo: public HardwareInfo
{
  public:
    /*!
     * \brief Domyślny konstruktor klasy RamInfo
     *
     * Przy tworzeniu obiektu odczytuje informacje o pamięci RAM
     */
    RamInfo() { update(); }

    /*!
     * \brief Metoda aktualizuje informacje o pamięci RAM
     *
     * \return true jeśli odczyty się powiodą, w.p.p. false
     */
    bool update() override;

    /*!
     *\brief Metoda pozwala na otrzymanie informacji o zużyciu pamięci RAM w komputerze
     *
     * @return Zwracana jest ilość zajętej pamięci RAM
     */
    double totalUsage() const { return m_totalRamUsage; }
  private:

    /*!
     * \brief Pole przechowujące informacje o zużyciu pamięci RAM
     */
    double m_totalRamUsage;
};

#endif /* RAMINFO_HPP_ */
