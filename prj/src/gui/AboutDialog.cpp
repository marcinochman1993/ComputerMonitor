/*
 * AboutDialog.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: mochman
 */

#include "AboutDialog.hpp"

void AboutDialog::author(const QString& newAuthor)
{
  authorLabel->setText(newAuthor);
}

QString AboutDialog::author() const
{
  return authorLabel->text();
}

void AboutDialog::programName(const QString& newProgramName)
{
  programNameLabel->setText(newProgramName);
}

QString AboutDialog::programName() const
{
  return programNameLabel->text();
}

void AboutDialog::version(const QString& newVersion)
{
  versionLabel->setText(newVersion);
}

QString AboutDialog::version() const
{
  return versionLabel->text();
}

