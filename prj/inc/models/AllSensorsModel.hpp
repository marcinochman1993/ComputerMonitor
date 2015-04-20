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
    int columnCount(const QModelIndex &parent = QModelIndex()) const override { return 2;}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void computerInfo(ComputerInfo* compInfo) { m_computerInfo=compInfo; }
  private:
    ComputerInfo* m_computerInfo;
};

#endif /* PRJ_INC_MODELS_ALLSENSORSMODEL_HPP_ */
