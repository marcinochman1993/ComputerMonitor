/*
 * ModeSelectionDialog.hpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#ifndef MODESELECTIONDIALOG_HPP_
#define MODESELECTIONDIALOG_HPP_

#include <QDialog>
#include "ui_ModeSelectionDialog.h"

class ModeSelectionDialog: public QDialog, Ui::UiModeSelectionDialog
{
    Q_OBJECT

  public:
    ModeSelectionDialog(QWidget* parent = nullptr):QDialog(parent) { init(); }
  private:
    void init();
};


#endif /* MODESELECTIONDIALOG_HPP_ */
