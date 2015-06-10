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

    enum ToStringFlags
    {
      TOTAL_USAGE = 0x01,
      ALL = 0x01
    };

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


    bool update(const std::string& strFromNet) override;

    /*!
     *\brief Metoda pozwala na otrzymanie informacji o zużyciu pamięci RAM w komputerze
     *
     * \return Zwracana jest ilość zajętej pamięci RAM
     */
    double totalUsage() const { return m_totalRamUsage; }

    std::string toString(unsigned flags = 0) const override;
  private:

    /*!
     * \brief Pole przechowujące informacje o zużyciu pamięci RAM
     */
    double m_totalRamUsage;
};

#endif /* RAMINFO_HPP_ */
