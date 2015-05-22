/*
 * UsageDelegate.hpp
 *
 *  Created on: May 22, 2015
 *      Author: mochman
 */

#ifndef USAGEDELEGATE_HPP_
#define USAGEDELEGATE_HPP_

#include <QStyledItemDelegate>
#include <set>

class UsageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    UsageDelegate(QWidget *parent = 0):QStyledItemDelegate(parent) { }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    void addColumnUsage(int column) { m_columnsUsage.insert(column); }

private:
    QLinearGradient prepareGradient(double usagePercent, const QRect& rect) const;
    std::set<int> m_columnsUsage;

};
#endif /* USAGEDELEGATE_HPP_ */
