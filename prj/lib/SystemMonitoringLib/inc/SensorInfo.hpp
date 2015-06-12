/*
 * SensorInfo.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef SENSORINFO_HPP_
#define SENSORINFO_HPP_

#include <iostream>
#include <vector>
#include <sensors/sensors.h>
#include "HardwareInfo.hpp"


/*!
 * \brief Typ wyliczeniowy określający rodzaj sensora
 */
enum class SensorType
{
  VOLTAGE = 0, //!< Napięcie
      TEMP     //!< Temperatura
};

/*!
 * \brief Metoda określa jednostkę dla podanego typu czujnika
 *
 * \param sensorType - określa typ sensora
 * \return Łańcuch znaków, określający jednostkę czujnika
 */
std::string convertTypeToString(const SensorType& sensorType);

/*!
 * \brief Klasa reprezentująca czujnik w komputerze
 *
 * Pozwala na komunikację (pobieranie) wartości z czujnika oraz
 * zdobycie informacji o samym czujniku.
 */
class SensorInfo: public HardwareInfo
{
  public:

    /*!
     * \brief
     *
     */
    enum TO_STRING_FLAGS
    {
      NAME = 0x01,  //!< NAzwa
      VALUE = 0x02, //!< Wartość
      TYPE = 0x04,  //!< Typ
      ALL = 0x07    //!< Wszystko
    };

    /*!
     * \brief Metoda zwracająca wszystkie znalezione czujniki w komputerze
     *
     * Metoda pozwala na dostęp do wszystkich czujników, które zostały
     * rozpoznane przez bibliotekę libsensors. Wartości odczytów nie są zainicjowane.
     *
     * \return Zwracany jest wektor czujników
     */
    static const std::vector<SensorInfo>& allSensors();

    /*!
     * \brief Metoda statyczna czyści wszelkie zajęte zasoby
     *
     * Usuwa wszystkie zasoby, które zostały zajęte przez bibliotekę libsensors.
     *
     */
    static void cleanUp()
    {
      sensors_cleanup();
    }

    /*!
     * \brief Konstruktor klasy SensorInfo.
     *
     * \param chipName - wskaźnik na strukture opisującą układ sensora
     * \param subfeature - wskaźnik na strukturę opisującą poszczególną cechę sensora
     * \param type - typ czujnika
     */
    SensorInfo(const sensors_chip_name* chipName = nullptr,
        const sensors_subfeature* subfeature = nullptr, const SensorType& type =
          SensorType::VOLTAGE)
        : m_chipName(chipName), m_subfeature(subfeature), m_value(-1.0), m_type(
            type), m_nameFromNet()
    {
    }

    /*!
     * \brief Metoda aktualizująca wartość z czujnika.
     *
     *Odziedziczona metoda z klasy Info, aktualizująca odczyty z czujnika.
     *
     * \return Wartość określająca czy odczyt z sensorów się powiódł
     */
    bool update() override;

    /*!
     * \brief Metoda aktualizuje informacje o czujniku na podstawie łańcucha znaków.
     *
     * \param strFromNet - łańcuch znaków, na podstawie którego zostaną zaktualizowane dane, format taki sam jak generuje metoda toString
     * \return true jeśli aktualizacja się powiedzie, w.p.p false
     */
    bool update(const std::string& strFromNet) override;

    /*!
     * \brief Metoda pozwala pobrać nazwę czujnika
     *
     * Odziedziczona metoda z klasy HardwareInfo, pozwala otrzymać nazwę urządzenia,
     * w tym wypadku czujnika.
     *
     * \return Nazwa czujnika
     */
    std::string name() const override;

    /*!
     * \brief Metoda pobierająca wartość z czujnika
     *
     * Pobrana wartość jest ostatnią wartością, która została odczytana
     * przy pomocy funkcji update().
     *
     * \return Ostatnia odczytana wartość z czujnika.
     */
    double value() const
    {
      return m_value;
    }

    /*!
     * Metoda pozwala określić rodzaj czujnika
     *
     * \return Zwraca rodzaj czujnika
     */
    const SensorType& sensorType() const
    {
      return m_type;
    }

    /*!
     * \brief
     *
     * \return Łańuch znaków określający jednostkę wielkości mierzonej przez czujnik.
     */
    std::string unit() const
    {
      return convertTypeToString(m_type);
    }

    /*!
     * \brief Metoda pozwalająca uzyskać łańcuch znaków opisujący czujnik.
     *
     * Format dla informacji: (typ wielkości:wartość)
     *
     * \param flags - określa, które elementy opisujące procesor zostaną uwzględnione w łąńuchu znaków
     * \return Zwracany jest łańcuch znaków opisujący proces.
     */
    std::string toString(unsigned flags = 0) const override;
  private:
    /*!
     * \brief Statyczna metoda pozwalająca zainicjować sensory
     *
     * Pobiera informacje o wszystkich sensorach i zapisuje je w s_sensorsVector.
     *
     * \return Zwracana wartość określa czy inicjalizacja się powiodła.
     */
    static bool initAllSensors();

    /*!
     * \brief Pole zawierające strukturę przechowującą informacje o układzie sensora.
     *
     * Jest to wskaźnik na informacje o układzie sensora. Pole służy do komunikacji
     * z biblioteką libsensors.
     */
    const sensors_chip_name* m_chipName;

    /*!
     * \brief Pole zawierające strukturę przechowującą informacje o poszczególnej cesze sensora
     *
     * Jest to wskaźnik na informacje o cesze sensora. Pole służy do komunikacji
     * z biblioteką libsensors.
     */
    const sensors_subfeature* m_subfeature;

    /*!
     * \brief Ostatnia pobrana wartość z sensora
     *
     * Pole przechowuje ostatnią zapamiętaną wartość odczytaną z czujnika. Wartość
     * ta jest aktualizowana, gdy wywoła sie metodę update().
     */
    double m_value;

    /*!
     * \brief Pole opisujące rodzaj czujnika
     */
    SensorType m_type;

    /*!
     * \brief Pole przechowujące nazwę czujnika pobranego z łańucha znakowego w metodzie update
     */
    std::string m_nameFromNet;

    /*!
     * \brief Statyczne pole przechowujące wszystkie czujniki.
     *
     * Jest to wektor wszysktkich dostępnych czujników na danym komputerze.
     */
    static std::vector<SensorInfo> s_sensorsVector;

};

/*!
 * \brief Przeciążony operator wypisywania informacji o czujniku na strumień
 *
 * Funkcja wypisuje dane w postaci nazwaSensora:wartosc
 */
std::ostream& operator<<(std::ostream& os, const SensorInfo& sensor);

#endif /* SENSORINFO_HPP_ */
