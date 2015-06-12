/*
 * ComputerMonitorWidgetBase.cpp
 *
 *  Created on: Jun 7, 2015
 *      Author: mochman
 */

#include "ComputerMonitorWidgetBase.hpp"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <iostream>

void ComputerMonitorWidgetBase::savePlot(QCustomPlot* plot)
{
  if (plot == nullptr)
    QMessageBox::information(this, "No plot to export",
        "There's no plot selected", QMessageBox::Ok);
  else
  {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"),
        "/home/", tr("Supported formats (*.png *.pdf *.bmp)"));
    if (!fileName.isEmpty())
    {
      QFileInfo fileInfo(fileName);
      plot->savePng(fileName);
      QString extension = fileInfo.suffix();

      if (extension == "png")
        plot->savePng(fileName);

      if (extension == "pdf")
        plot->savePdf(fileName);

      if (extension == "bmp")
        plot->saveBmp(fileName);
    }
  }
}

void ComputerMonitorWidgetBase::addToPlot(QCustomPlot* plot, double x, double y)
{
  if (plot == nullptr)
    return;
  if (plot->graph(0) == nullptr)
    return;

  auto graphPlot = plot->graph(0);

  if (static_cast<unsigned>(graphPlot->data()->size()) > maxPlotSize())
    graphPlot->removeData(graphPlot->data()->firstKey());

  graphPlot->addData(x, y);
}
