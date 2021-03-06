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
  if (m_computerInfoData == nullptr)
    return 0;
  return compInfo().allSensors().size();
}

QVariant AllSensorsModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || m_computerInfoData == nullptr)
    return QVariant();

  unsigned row = index.row();
  unsigned column = index.column();

  switch (role)
  {
    case Qt::DisplayRole:
      if (row < compInfo().allSensors().size())
        return getData(row, column);
  }

  return QVariant();
}

QVariant AllSensorsModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
  const vector<QString> HEADER_TITLES = { tr("Sensor name"), tr("Value"), tr(
      "Unit") };

  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      return HEADER_TITLES[section];
    }
  }

  return QVariant();
}

void AllSensorsModel::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfoData)
{
  beginResetModel();
  m_computerInfoData = compInfoData;
  connect(m_computerInfoData, SIGNAL(dataUpdated()), this, SLOT(dataUpdated()));
  endResetModel();
}

QVariant AllSensorsModel::getData(int row, int column) const
{
  QVariant result;
  switch (column)
  {
    case 0:
      result = QString(compInfo().allSensors()[row].name().c_str());
      break;
    case 1:
      result = compInfo().allSensors()[row].value();
      break;
    case 2:
      result = compInfo().allSensors()[row].unit().c_str();
      break;
  }

  return result;
}

void AllSensorsModel::dataUpdated()
{
  int deltaNumSensors = static_cast<int>(compInfo().allSensors().size())
    - m_lastNumSensors;
  if (deltaNumSensors != 0)
  {
    beginResetModel();
    m_lastNumSensors = compInfo().allSensors().size();
    endResetModel();
  }
  else
    emit dataChanged(index(0, 0),
        index(compInfo().allSensors().size(), COLUMNS_NUM));
}

void AllSensorsModel::clear()
{
  if (m_computerInfoData == nullptr)
    return;
  beginResetModel();
  m_computerInfoData->clear();
  m_lastNumSensors = 0;
  endResetModel();
}
