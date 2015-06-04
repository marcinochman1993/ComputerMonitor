/*
 * ModeSelectionDialog.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: mochman
 */

#include "ModeSelectionDialog.hpp"

void ModeSelectionDialog::init()
{
  setupUi(this);
  connect(this, SIGNAL(accepted()), this, SLOT(acceptedMode()));
}

void ModeSelectionDialog::acceptedMode()
{
  if (radioMixed->isChecked())
    m_mode = ProgramMode::MIXED;
  else if (radioPresenting->isChecked())
    m_mode = ProgramMode::PRESENTING_DATA;
  else if (radioSending->isChecked())
    m_mode = ProgramMode::SENDING_DATA;
}
