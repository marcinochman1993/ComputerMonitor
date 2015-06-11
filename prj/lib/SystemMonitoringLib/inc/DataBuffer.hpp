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

template<typename T>
class DataBuffer
{
  public:
    explicit DataBuffer(unsigned maxSize = 60)
        : m_maxSize(maxSize)
    {
    }
    const T& operator[](unsigned int index) const;
    unsigned size() const
    {
      return m_data.size();
    }

    void push_back(const T& element);
    unsigned maxSize() const
    {
      return m_maxSize;
    }

    const T& back() const
    {
      return m_data.back();
    }

    const std::list<T> list() const
    {
      return m_data;
    }

    void clear() { m_data.clear(); }
  private:
    std::list<T> m_data;
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
