/*
 * AllSensorsModel.hpp
 *
 *  Created on: Apr 19, 2015
 *      Author: mochman
 */

#ifndef ALLSENSORSMODEL_HPP_
#define ALLSENSORSMODEL_HPP_

#include <QAbstractTableModel>
#include "ComputerInfo.hpp"


class AllSensorsModel: public QAbstractTableModel
{
  public:
    AllSensorsModel(QObject* parent = nullptr):QAbstractTableModel(parent),m_computerInfo(nullptr) { }
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return COLUMNS_NUM;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void computerInfo(ComputerInfo* compInfo);
  private:
    QVariant getData(int row, int column) const;
    ComputerInfo* m_computerInfo;
    static const int COLUMNS_NUM = 2;
};

#endif /* PRJ_INC_MODELS_ALLSENSORSMODEL_HPP_ */
