/*
 * AllProcessesModel.hpp
 *
 *  Created on: May 13, 2015
 *      Author: mochman
 */

#ifndef ALLPROCESSESMODEL_HPP_
#define ALLPROCESSESMODEL_HPP_


#include <QAbstractTableModel>
#include "ComputerInfoDataContainerWrapper.hpp"

class AllProcessesModel: public QAbstractTableModel
{
    Q_OBJECT

  public:
    AllProcessesModel(QObject* parent=nullptr): QAbstractTableModel(parent), m_computerInfoData(nullptr){ }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);
    unsigned processIdByIndex(unsigned index) const;
  private:
    static const int COLUMNS_NUM = 2;
    ComputerInfoDataContainerWrapper* m_computerInfoData;
    std::vector<unsigned> m_allProcessesId;
    const ComputerInfo& compInfo() const { return m_computerInfoData->dataContainer()->computerInfo(); }
    QVariant getData(unsigned row, unsigned column) const;
  private slots:
    void dataUpdated();
};


#endif /* ALLPROCESSESMODEL_HPP_ */
