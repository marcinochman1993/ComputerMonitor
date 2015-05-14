/*
 * ProcessorModel.hpp
 *
 *  Created on: May 14, 2015
 *      Author: mochman
 */

#ifndef PROCESSORMODEL_HPP_
#define PROCESSORMODEL_HPP_

#include <QAbstractTableModel>
#include "ComputerInfoDataContainerWrapper.hpp"

class ProcessorModel: public QAbstractTableModel
{
    Q_OBJECT
  public:
    ProcessorModel(QObject* parent = nullptr):QAbstractTableModel(parent),m_computerInfoData(nullptr) { }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);
  private slots:
    void dataUpdated();
  private:
    const ComputerInfo& compInfo() const { return m_computerInfoData->dataContainer()->computerInfo(); }
    QVariant getData(int row, int column) const;
    ComputerInfoDataContainerWrapper* m_computerInfoData;
    static const int COLUMNS_NUM = 3;
};


#endif /* PROCESSORMODEL_HPP_ */
