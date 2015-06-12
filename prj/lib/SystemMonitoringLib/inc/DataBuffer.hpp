/*
 * DataBuffer.hpp
 *
 *  Created on: May 22, 2015
 *      Author: mochman
 */

#ifndef DATABUFFER_HPP_
#define DATABUFFER_HPP_

#include <list>
#include <algorithm>

/*!
 * \brief Klasa reprezentująca bufor danych.
 *
 * Jest to bufor o określonym rozmiarze. Jeśli ilość
 * danych przekroczy jego wielkość, to usuwane są dane, które
 * zostały dodane na samym początku.
 */
template<typename T>
class DataBuffer
{
  public:
    /*!
     * \brief Kontruktora klasy DataBuffer.
     *
     * \param maxSize - pozwala określić wielkość bufora
     */
    explicit DataBuffer(unsigned maxSize = 60)
        : m_maxSize(maxSize)
    {
    }
    /*!
     * \brief Operator indeksowania.
     * \param index - indeks operatora indeksowania
     * \return Jeśli indeks jest poprawny to zwracana jest stałą referencja do obiektu o podanym indeksie.
     */
    const T& operator[](unsigned int index) const;

    /*!
     * \brief Metoda pozwala określić, ile danych jest przechowywanych przez bufor.
     *
     * \return Ilość danych przechowywanych przez bufor.
     */
    unsigned size() const
    {
      return m_data.size();
    }

    /*!
     * \brief Metoda pozwalająca dodać obiekt do bufora.
     *
     * Jeśli ilość danych przekracza dozwolony rozmiar bufora,
     * to obiekt, który został dodany najwcześniej zostaje usunięty.
     *
     * \param element - obiekt, który zostanie dodany do bufora
     */
    void push_back(const T& element);

    /*!
     * \brief Metoda pozwalająca określić maksymalny rozmiar bufora
     *
     * \return Zwracany jest maksymalny rozmiar bufora
     */
    unsigned maxSize() const
    {
      return m_maxSize;
    }

    /*!
     * \brief Metoda pozwala określić ostatnio dodany element do bufora
     *
     * \return Zwracany jest ostatnio dodany element.
     */
    const T& back() const
    {
      return m_data.back();
    }

    /*!
     * \brief Metoda pozwalająca otrzymać wszystkie przechowywane obiekty jako lista
     * \return Lista wszystkich przechowywanych obiektów przez bufor
     */
    const std::list<T> list() const
    {
      return m_data;
    }

    /*!
     * \brief Metoda pozwala wyczyścić bufor.
     *
     * Rozmiar bufora po wywołaniu tej metody wynosi 0.
     */
    void clear() { m_data.clear(); }
  private:
    /*!
     * \brief Pole przechowujące dane bufora
     */
    std::list<T> m_data;

    /*!
     * \brief Pole określające maksymalny rozmiar bufora
     */
    unsigned m_maxSize;
};

template<typename T>
const T& DataBuffer<T>::operator[](unsigned int index) const
{
  if (index >= size())
    throw "Index out of bound";

  auto it = m_data.begin();
  std::advance(it, index);

  return *it;
}

template<typename T>
void DataBuffer<T>::push_back(const T& element)
{
  if (m_data.size() >= maxSize())
    m_data.pop_front();

  m_data.push_back(element);
}

#endif /* DATABUFFER_HPP_ */
