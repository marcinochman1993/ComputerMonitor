/*
 * HardwareInfo.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef HARDWAREINFO_HPP_
#define HARDWAREINFO_HPP_

#include <string>
#include "Info.hpp"

/*!
 * \brief Klasa opisująca urządzenie fizyczne w komputerze
 *
 * Wprowadza własności wspólne dla urządzenia. Klasa służy do dziedziczenia.
 *
 */
class HardwareInfo: public Info
{
  public:

    /*!
     * \brief Metoda określająca nazwę urządzenia
     *
     * Jest to metoda wirtualna, każde urządzenie tj. klasa pochodna powinna przeciążyc tę metodę
     *
     * \return Nazwa urządzenia
     */
    virtual std::string name() const { return std::string(); }
};

#endif /* HARDWAREINFO_HPP_ */
