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

    Info():m_updateFromNet(false) { }

    /*!
     * \brief Metoda służy do uaktualnienia przechowywanej informacji
     *
     * Zapisuje, kiedy ostatio została wykonana aktualizacja.
     *
     * \return Metoda zwraca zawsze true.
     */
    virtual bool update() {  m_lastUpdated = std::chrono::system_clock::now(); return true; };

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

    virtual const std::time_t lastUpdatedTimeT() const { return std::chrono::system_clock::to_time_t(m_lastUpdated); }

    virtual std::string toString(unsigned flags = 0) const;

    virtual bool updateFromNet() const { return m_updateFromNet; }

    virtual void updateFromNet(bool newUpdateFromNet) { m_updateFromNet = newUpdateFromNet; }

    /*!
     * \brief Domyślny destruktor
     */
    virtual ~Info() { }
  protected:
    bool updateTime(const std::string& time);
  private:

    bool m_updateFromNet;
    /*!
     * \brief Pole przechowujące punkt w czasie, kiedy ostatni raz zostały zaktualizowane informacje.
     */
    std::chrono::system_clock::time_point m_lastUpdated;
};

#endif /* INFO_HPP_ */
