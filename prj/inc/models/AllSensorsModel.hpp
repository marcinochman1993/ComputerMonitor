/*
 * AllSensorsModel.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef ALLSENSORSMODEL_HPP_
#define ALLSENSORSMODEL_HPP_

#include <QAbstractTableModel>
#include "ComputerInfoDataContainerWrapper.hpp"


class AllSensorsModel: public QAbstractTableModel
{
    Q_OBJECT

  public:
    AllSensorsModel(QObject* parent = nullptr):QAbstractTableModel(parent),m_computerInfoData(nullptr) { }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void computerInfoData(ComputerInfoDataContainerWrapper* compInfo);
  private:
    QVariant getData(int row, int column) const;
    const ComputerInfo& compInfo() const { return m_computerInfoData->dataContainer()->computerInfo(); }
    ComputerInfoDataContainerWrapper* m_computerInfoData;
    static const int COLUMNS_NUM = 2;
  private slots:
  void dataUpdated();

};

#endif /* PRJ_INC_MODELS_ALLSENSORSMODEL_HPP_ */
