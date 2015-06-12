/*
 * ComputerMonitorWidgetBase.hpp
 *
 *  Created on: Jun 7, 2015
 *      Author: mochman
 */

#ifndef COMPUTERMONITORWIDGETBASE_HPP_
#define COMPUTERMONITORWIDGETBASE_HPP_


#include <QWidget>
#include "qcustomplot.h"

/*!
 * \brief Klasa bazowa dla wszystkich kontrolek w aplikacji ComputerMonitor
 */
class ComputerMonitorWidgetBase: public QWidget
{
    Q_OBJECT
  public:
    /*!
     * \brief Konstruktor klasy ComputerMonitorWidgetBase
     * \param parent - rodzic kontrolki
     */
    ComputerMonitorWidgetBase(QWidget* parent = nullptr): QWidget(parent), m_maxPlotSize(60) { }

    /*!
     * \brief Metoda pozwalająca sprawdzić maksymalną ilość punktów na wykresie
     */
    unsigned maxPlotSize() const { return m_maxPlotSize; }

    /*!
     * \brief Metoda pozwalająca ustawić maksymalną ilość punktów na wykresie
     */
    void maxPlotSize(unsigned newMaxPlotSize) { m_maxPlotSize = newMaxPlotSize; }
  protected:
    /*!
     * \brief Metoda pozwalająca zapisać wykres jako PDF,PNG lub BMP
     * \param plot - wykres, który należy wyeksportować
     */
    void savePlot(QCustomPlot* plot);

    /*!
     * \brief Metoda aktualizuje wykres, dodając jeden punkt do niego
     * @param plot - wskaźnik na wykres
     * @param x - wsþółrzędna na osi odciętych
     * @param y - współrzędna na osi rzędnych
     */
    void addToPlot(QCustomPlot* plot, double x, double y);
    public slots:
        virtual void savePlot() { }
  private:
    /*!
     * \brief Pole przechowujące maksymalną ilość punktów na wykresie
     */
  unsigned m_maxPlotSize;
};


#endif /* COMPUTERMONITORWIDGETBASE_HPP_ */
