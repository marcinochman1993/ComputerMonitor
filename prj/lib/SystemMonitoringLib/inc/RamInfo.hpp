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
     * \brief Typ wyliczeniowy określający flagi dla metody toString
     */
    enum ToStringFlags
    {
      TOTAL_USAGE = 0x01,//!< TOTAL_USAGE
      ALL = 0x01         //!< ALL
    };

    /*!
     * \brief Domyślny konstruktor klasy RamInfo
     *
     * Przy tworzeniu obiektu odczytuje informacje o pamięci RAM
     */
    RamInfo(): m_totalRamUsage(0) { }

    /*!
     * \brief Metoda aktualizuje informacje o pamięci RAM
     *
     * \return true jeśli odczyty się powiodą, w.p.p. false
     */
    bool update() override;

    /*!
      * \brief Metoda aktualizuje informacje o procesorze na podstawie łańcucha znaków.
      *
      * \param strFromNet - łańcuch znaków, na podstawie którego zostaną zaktualizowane dane, format taki sam jak generuje metoda toString
      * \return true jeśli aktualizacja się powiedzie, w.p.p false
      */
    bool update(const std::string& strFromNet) override;

    /*!
     *\brief Metoda pozwala na otrzymanie informacji o zużyciu pamięci RAM w komputerze
     *
     * \return Zwracana jest ilość zajętej pamięci RAM
     */
    double totalUsage() const { return m_totalRamUsage; }

    /*!
      * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący pamięć RAM.
      *
      * Format dla informacji: (typ wielkości:wartość)
      *
      * \param flags - określa, które elementy opisujące procesor zostaną uwzględnione w łąńuchu znaków
      * \return Zwracany jest łańcuch znaków opisujący proces.
      */
    std::string toString(unsigned flags = 0) const override;

    /*!
     * \brief Metoda pozwalająca usunąć wszelkie dostępne informacje o pamięci RAM.
     *
     * Po wywołaniu metody, aby kolejny raz otrzymać informacje o procesorze należy
     * wywołać jedną z metod update.
     */
    void clear() { m_totalRamUsage = 0; }
  private:

    /*!
     * \brief Pole przechowujące informacje o zużyciu pamięci RAM
     */
    double m_totalRamUsage;
};

#endif /* RAMINFO_HPP_ */
