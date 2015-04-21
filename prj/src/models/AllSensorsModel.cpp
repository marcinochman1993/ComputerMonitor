/*
 * AllSensorsModel.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#include <vector>
#include "AllSensorsModel.hpp"

using namespace std;

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
  int column = index.column();

  switch (role)
  {
    case Qt::DisplayRole:
      if (row < m_computerInfo->allSensors().size())
        return getData(row, column);
  }

  return QVariant();
}

QVariant AllSensorsModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
  const vector<QString> HEADER_TITLES = { tr("Sensor name"), tr("Value") };

  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      return HEADER_TITLES[section];
    }
  }

  return QVariant();
}

void AllSensorsModel::computerInfo(ComputerInfo* compInfo)
{
  beginResetModel();
  m_computerInfo = compInfo;
  endResetModel();
}

QVariant AllSensorsModel::getData(int row, int column) const
{
  QVariant result;
  switch (column)
  {
    case 0:
      result = QString(m_computerInfo->allSensors()[row].name().c_str());
      break;
    case 1:
      result = m_computerInfo->allSensors()[row].value();
      break;
  }

  return result;
}
