/*
 * RadialIndicator.hpp
 *
 *  Created on: May 19, 2015
 *      Author: mochman
 */

#ifndef RADIALINDICATOR_HPP_
#define RADIALINDICATOR_HPP_

#include <QWidget>
#include <QTimeLine>


class RadialIndicator: public QWidget
{
    Q_OBJECT
  public:
    RadialIndicator(QWidget* parent = nullptr): QWidget(parent) { init(); }
    void paintEvent(QPaintEvent * event) override;

    void valuePercent(double newValue);
    double valuePercent() const { return m_valuePercent; }
  private:
    void init();
    double m_valuePercent;
    QTimeLine* m_timeLine;
    int m_angle;
};

#endif /* RADIALINDICATOR_HPP_ */
