/*
 * Info.hpp
 *
 *  Created on: Apr 18, 2015
 *      Author: mochman
 */

#ifndef INFO_HPP_
#define INFO_HPP_

#include <chrono>
#include <string>
/*!
 * \brief Klasa, która reprezentuje możliwą do aktualizacji informację
 */
class Info
{
  public:
    /*!
     * \brief Metoda służy do uaktualnienia przechowywanej informacji
     *
     * Zapisuje, kiedy ostatnio została wykonana aktualizacja.
     *
     * \return Metoda zwraca zawsze true.
     */
    virtual bool update() {  m_lastUpdated = std::chrono::system_clock::now(); return true; };

    /*!
     * \brief Metoda aktualizuje informacje  na podstawie łańcucha znaków.
     *
     * \param strFromNet - łańcuch znaków, na podstawie którego zostaną zaktualizowane dane, format taki jak generuje metoda toString.
     * \return true jeśli aktualizacja się powiedzie, w.p.p false
     */
    virtual bool update(const std::string& strFromNet);

    /*!
     * \brief Metoda pozwala określić, kiedy ostatni raz zaktualizowo dane
     *
     * Pozwala pobrać punkt czasowy, który określa miejsce w czasie, kiedy nastąpiła ostatnia
     * aktualizacja informacji.
     *
     * \return Metoda zwraca punkt w czasie, kiedy ostatni raz zostały zaktualizowane informacje.
     */
    virtual const std::chrono::system_clock::time_point & lastUpdated() const { return m_lastUpdated; };

    /*!
     * \brief Metoda pozwala określić, kiedy ostatni raz zaktualizowo dane
     *
     * Pozwala pobrać punkt czasowy, który określa miejsce w czasie, kiedy nastąpiła ostatnia
     * aktualizacja informacji.
     *
     * \return Metoda zwraca punkt w czasie, kiedy ostatni raz zostały zaktualizowane informacje.
     */
    virtual const std::time_t lastUpdatedTimeT() const { return std::chrono::system_clock::to_time_t(m_lastUpdated); }

    /*!
     * \brief Wirtualna metoda umożliwiająca konwersję danych na łańcuch znaków
     * \param flags - parametr ignorowany
     * \return Zwracany jest łańcuch znaków opisujący dany obiekt.
     */
    virtual std::string toString(unsigned flags = 0) const;

    /*!
     * \brief Domyślny destruktor
     */
    virtual ~Info() { }
  protected:
    /*!
     * \brief Pozwala zaktalizować czas ostatniej aktualizacji na podstawie łańcucha znaków
     * \param time - łańcuch znaków określający ilość sekund od roku 1970.
     * \return true jeśli aktualizacja się powiedzie, w.p.p false
     */
    bool updateTime(const std::string& time);
  private:

    /*!
     * \brief Pole przechowujące punkt w czasie, kiedy ostatni raz zostały zaktualizowane informacje.
     */
    std::chrono::system_clock::time_point m_lastUpdated;
};

#endif /* INFO_HPP_ */
