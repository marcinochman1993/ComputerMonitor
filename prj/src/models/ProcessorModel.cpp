/*
 * ProcessorModel.cpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#include "ProcessorModel.hpp"

using namespace std;

int ProcessorModel::rowCount(const QModelIndex &parent) const
{
  if (m_computerInfoData == nullptr)
    return 0;
  return compInfo().processor().coresNumber();
}

QVariant ProcessorModel::data(const QModelIndex &index, int role) const
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

QVariant ProcessorModel::getData(int row, int column) const
{
  QVariant result;
  switch (column)
  {
    case 0:
      result = row;
      break;
    case 1:
      result = compInfo().processor().frequency(row);
      break;
    case 2:
      result = compInfo().processor().usage(row);
      break;
  }

  return result;
}

QVariant ProcessorModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
  const vector<QString> HEADER_TITLES = { tr("Core id"), tr("Frequency [MHz]"),
      tr("Usage [%]") };

  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      return HEADER_TITLES[section];
    }
  }

  return QVariant();
}

void ProcessorModel::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  beginResetModel();
  m_computerInfoData = compInfo;
  connect(m_computerInfoData, SIGNAL(dataUpdated()), this, SLOT(dataUpdated()));
  endResetModel();
}

void ProcessorModel::dataUpdated()
{
  emit dataChanged(index(0, 0),
      index(compInfo().processor().coresNumber(), COLUMNS_NUM));
}
