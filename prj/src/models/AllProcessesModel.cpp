/*
 * AllProcessesModel.cpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#include "AllProcessesModel.hpp"

using namespace std;

int AllProcessesModel::rowCount(const QModelIndex &parent) const
{
  return m_allProcessesId.size();
}

QVariant AllProcessesModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || m_computerInfoData == nullptr)
    return QVariant();

  unsigned row = index.row();
  unsigned column = index.column();

  switch (role)
  {
    case Qt::DisplayRole:
      return getData(row, column);
  }

  return QVariant();
}

QVariant AllProcessesModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
  const vector<QString> HEADER_TITLES = { tr("Name"), tr("Id"), tr(
      "Cpu Usage [%]") };

  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
      return HEADER_TITLES[section];
  }

  return QVariant();
}

void AllProcessesModel::computerInfoData(
    ComputerInfoDataContainerWrapper* compInfo)
{
  beginResetModel();
  m_computerInfoData = compInfo;
  connect(m_computerInfoData, SIGNAL(dataUpdated()), this, SLOT(dataUpdated()));
  endResetModel();
}

void AllProcessesModel::dataUpdated()
{
  const std::vector<unsigned>& lastAddedProcesses =
    compInfo().allProcesses().lastAddedProcesses();
  if (lastAddedProcesses.size() > 0)
  {
    unsigned beginIndex = m_allProcessesId.size();
    beginInsertRows(QModelIndex(), beginIndex,
        beginIndex + lastAddedProcesses.size() - 1);
    for (const int& procId : lastAddedProcesses)
      m_allProcessesId.push_back(procId);
    endInsertRows();
  }

  const std::vector<unsigned>& lastDeletedProcesses =
    compInfo().allProcesses().lastDeletedProcesses();
  if (lastDeletedProcesses.size())
  {
    for (const int& procId : lastDeletedProcesses)
    {
      auto foundIt = std::find(m_allProcessesId.begin(), m_allProcessesId.end(),
          procId);
      if (foundIt != m_allProcessesId.end())
      {
        unsigned beginIndex = std::distance(m_allProcessesId.begin(), foundIt);
        beginRemoveRows(QModelIndex(), beginIndex, beginIndex);
        m_allProcessesId.erase(foundIt);
        endRemoveRows();
      }
    }
  }

  emit dataChanged(index(0, 0), index(m_allProcessesId.size(), COLUMNS_NUM));
}

unsigned AllProcessesModel::processIdByIndex(unsigned index) const
{
  if (index < m_allProcessesId.size())
    return m_allProcessesId[index];
  throw "There's no process with that index";
}

std::string AllProcessesModel::processNameById(unsigned id) const
{
  return compInfo().allProcesses().process(id).name();
}

QVariant AllProcessesModel::getData(unsigned row, unsigned column) const
{
  if (row < m_allProcessesId.size())
  {
    unsigned procId = m_allProcessesId[row];
    if (compInfo().allProcesses().containsProcess(procId))
    {
      const ProcessInfo& proc = compInfo().allProcesses().process(procId);
      switch (column)
      {
        case 0:
          return QString(proc.name().c_str());
        case 1:
          return proc.id();
        case 2:
          return proc.cpuUsage();
      }

    }
  }

  return QVariant();
}
