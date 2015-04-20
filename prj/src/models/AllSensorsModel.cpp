/*
 * AllSensorsModel.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#include "AllSensorsModel.hpp"


int AllSensorsModel::rowCount(const QModelIndex &parent) const
{

  if (m_computerInfo == nullptr)
    return 0;
  return m_computerInfo->allSensors().size();
}

QVariant AllSensorsModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || m_computerInfo == nullptr)
    return QVariant();

  int row = index.row();
  int column=index.column();

  switch (role)
  {
    case Qt::DisplayRole:
      if (row < m_computerInfo->allSensors().size())
        return  QString(m_computerInfo->allSensors()[row].name().c_str());
  }

  return QVariant();
}
