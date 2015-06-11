/*
 * RadialIndicator.hpp
 *
 *  Created on: May 19, 2015
 *      Author: mochman
 */

#ifndef RADIALINDICATOR_HPP_
#define RADIALINDICATOR_HPP_

#include <QWidget>
#include <QPropertyAnimation>


class RadialIndicator: public QWidget
{
    Q_OBJECT

  public:
    RadialIndicator(QWidget* parent = nullptr): QWidget(parent), m_angle(-45.0) { init(); }
    void paintEvent(QPaintEvent * event) override;

    void setValuePercent(double newValue);
    double valuePercent() const { return m_valuePercent; }

  private:

    int getAngle() const { return m_angle; }
    void setAngle(int newAngle ) { m_angle = newAngle; repaint(); }

    void init();
    double m_valuePercent;
    int m_angle;
    QPropertyAnimation* m_propertyAnimation;

    Q_PROPERTY(int angle  READ getAngle WRITE setAngle)
};

#endif /* RADIALINDICATOR_HPP_ */
