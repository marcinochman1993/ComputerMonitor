/*
 * AboutDialog.hpp
 *
 *  Created on: Jun 9, 2015
 *      Author: mochman
 */

#ifndef ABOUTDIALOG_HPP_
#define ABOUTDIALOG_HPP_

#include <QDialog>
#include "ui_AboutDialog.h"

class AboutDialog: public QDialog, Ui::AboutDialog
{
    Q_OBJECT
  public:
    AboutDialog(QWidget* parent = nullptr): QDialog(parent) { setupUi(this); }
    QString author() const;
    QString programName() const;
    QString version() const;
  public slots:
    void author(const QString& newAuthor);
    void programName(const QString& newProgramName);
    void version(const QString& newVersion);
};


#endif /* ABOUTDIALOG_HPP_ */
