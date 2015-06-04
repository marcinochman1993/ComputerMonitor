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
    const T& operator[](unsigned int index) const;
    unsigned size() const
    {
      return m_data.size();
    }

    void push_back(const T& element);
  private:
    std::list<T> m_data;
};

template<typename T>
const T& DataBuffer<T>::operator[](unsigned int index) const
{
  if (index >= size())
    throw "Index out of bound";
  return *std::advance(m_data.begin(), index);
}

void push_back(const T& element)
{

}

#endif /* DATABUFFER_HPP_ */
