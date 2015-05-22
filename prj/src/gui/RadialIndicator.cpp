/*
 * RadialIndicator.cpp
 *
 *  Created on: May 19, 2015
 *      Author: mochman
 */

#include "RadialIndicator.hpp"
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <cmath>

#include <iostream>

void RadialIndicator::init()
{
  setAutoFillBackground(true);
  m_propertyAnimation = new QPropertyAnimation(this, "angle");
}

void RadialIndicator::setValuePercent(double newValue)
{
  int startFrame = -45 + 300 * m_valuePercent / 100.0, stopFrame = -45
    + 300 * newValue / 100.0;
  m_propertyAnimation->setDuration(500);
  m_propertyAnimation->setStartValue(startFrame);
  m_propertyAnimation->setEndValue(stopFrame);
  m_propertyAnimation->start();
  m_valuePercent = newValue;
  m_angle = stopFrame;
}

void RadialIndicator::paintEvent(QPaintEvent * pEvent)
{
  QPainter painter(this);
  int areaWidth = pEvent->rect().width(), areaHeight = pEvent->rect().height(),
      radiusBig = areaWidth < areaHeight ? areaWidth / 2 : areaHeight / 2,
      centerX = areaWidth / 2, centerY = areaHeight / 2, radiusSmall = 0.8
        * radiusBig;

  QPixmap speedometerImg(":/images/images/speedometer.png");
  QPixmap speedometerIndicatorImg(":/images/images/speedometerIndicator.png");
  if (areaWidth > areaHeight)
    speedometerImg = speedometerImg.scaledToWidth(areaHeight,
        Qt::SmoothTransformation);
  else
    speedometerImg = speedometerImg.scaledToHeight(areaWidth,
        Qt::SmoothTransformation);
  QPalette palette = this->palette();

  setPalette(palette);
  double angle = m_angle;
  QImage image = QImage(areaWidth, areaHeight, QImage::Format_ARGB32);
  image.fill(Qt::transparent);
  QPainter bitmapPainter(&image);
  bitmapPainter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  painter.setRenderHints(
      QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  bitmapPainter.translate(QPoint(centerX, centerY));
  bitmapPainter.rotate(-angle);
  bitmapPainter.drawPixmap(-speedometerImg.width() / 2,
      -speedometerImg.height() / 2, speedometerImg);
  speedometerIndicatorImg = speedometerIndicatorImg.scaledToWidth(
      speedometerImg.height());
  bitmapPainter.rotate(angle);
  bitmapPainter.drawPixmap(-speedometerIndicatorImg.width() / 2,
      -speedometerIndicatorImg.height() / 2, speedometerIndicatorImg);
  painter.translate(centerX, centerY);
  painter.rotate(angle);
  painter.drawImage(-centerX, -centerY, image);

  QWidget::paintEvent(pEvent);
}
