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
     * \brief Domyślny konstruktor klasy SensorsVector
     */
    SensorsVector() {}

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

    /*!
     * \brief Metoda aktualizuje informacje o zbiorze czujników na podstawie łańcucha znaków.
     *
     * \param strFromNet - łańcuch znaków, na podstawie którego zostaną zaktualizowane dane, format taki sam jak generuje metoda toString
     * \return true jeśli aktualizacja się powiedzie, w.p.p false
     */
    bool update(const std::string& strFromNet) override;

    /*!
     * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący zbiór czujników.
     *
     * Format dla informacji: |typ wielkości:wartość; ...|
     *
     * \param flags - określa, które elementy opisujące procesor zostaną uwzględnione w łąńuchu znaków
     * \return Zwracany jest łańcuch znaków opisujący proces.
     */
    std::string toString(unsigned flags = 0) const override;

    /*!
     * \brief Metoda inicjuje wektor czujników wyszukując je wszystkie w systemie
     */
    void initWithAllSensors();
};


#endif /* SENSORSVECTOR_HPP_ */
