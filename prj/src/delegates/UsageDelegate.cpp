/*
 * UsageDelegate.cpp
 *
 *  Created on: May 22, 2015
 *      Author: mochman
 */
#include <QPainter>
#include "UsageDelegate.hpp"
#include <QLinearGradient>

#include <iostream>

void UsageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
  if (m_columnsUsage.find(index.column()) != m_columnsUsage.end())
  {
    double usage = index.data().toDouble();
    QRect rect = option.rect;
    QColor textBackground;
    rect.setWidth(usage * rect.width() / 100.0);
    if (option.state & QStyle::State_Selected)
    {
      painter->setPen(option.palette.color(QPalette::HighlightedText));
      textBackground = option.palette.color(QPalette::Highlight);
    }
    else
    {
      painter->setPen(option.palette.color(QPalette::WindowText));
      textBackground = option.palette.color(QPalette::Base);
    }
    QFont font;
    QFontMetrics metrics(font);

    QString text = QString::number(usage, 'f', 2);

    int textWidth = metrics.width(text), textHeight = metrics.height(), textX =
      option.rect.width() / 2 - textWidth / 2 + option.rect.x(), textY =
      option.rect.height() / 2 + textHeight / 2 + option.rect.y();

    painter->fillRect(rect, prepareGradient(usage, rect));
    painter->fillRect(textX, textY - textHeight, textWidth, 1.1 * textHeight,
        textBackground);
    painter->drawText(textX, textY, text);
  }
  else
    QStyledItemDelegate::paint(painter, option, index);
}

QLinearGradient UsageDelegate::prepareGradient(double usagePercent,
    const QRect& rect) const
{
  QLinearGradient gradient(rect.topLeft(), rect.bottomRight());

  static std::map<int, QColor> colorMap = { { 0, QColor(0, 255, 0) }, { 10,
      QColor(0, 230, 0) }, { 20, QColor(0, 207, 0) }, { 30, QColor(184, 255,
      112) }, { 40, QColor(255, 255, 204) }, { 50, QColor(255, 255, 153) }, {
      60, QColor(255, 255, 0) }, { 70, QColor(255, 204, 0) }, { 80, QColor(255,
      153, 102) }, { 90, QColor(255, 80, 80) }, { 100, QColor(255, 0, 0) } };

  for (int i = 0; i < usagePercent; i += 10)
    gradient.setColorAt(i / 100.0, colorMap[i]);

  return gradient;
}
