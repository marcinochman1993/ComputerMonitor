/*
 * SensorsVector.hpp
 *
 *  Created on: Apr 20, 2015
 *      Author: mochman
 */

#ifndef SENSORSVECTOR_HPP_
#define SENSORSVECTOR_HPP_

#include <vector>
#include "SensorInfo.hpp"

/*!
 * \brief Klasa przechowująca czujniki
 *
 * Umożliwia aktualizację odczytów czujników
 */
class SensorsVector: public std::vector<SensorInfo>, public Info
{
  public:
    /*!
     * \brief Konstruktor klasy dodający czujniki
     *
     * \param sensors -wektor czujników, które mają być monitorowane
     */
    SensorsVector(const std::vector<SensorInfo>& sensors):std::vector<SensorInfo>(sensors) { }
    /*!
     * \brief Metoda aktualizuje odczyty z sensorów
     *
     * \return Jeśli wszystkie odczyty powiodą się to zwracana jest wartość true, w.p.p. false
     */
    bool update() override;

    std::string toString(unsigned flags = 0) const override;
};


#endif /* SENSORSVECTOR_HPP_ */
