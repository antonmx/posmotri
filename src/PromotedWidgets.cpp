/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "PromotedWidgets.h"

#include <QApplication>
#include <QDebug>

QSpinSlide::QSpinSlide (QSlider * _slide, QSpinBox * _box,  QObject * parent)
  : QObject (parent)
  , slide(_slide)
  , sbox(_box)
{
  setValue(slide->value());
  setRange(slide->minimum(), slide->maximum());
  connect(sbox, SIGNAL(valueChanged(int)), slide, SLOT(setValue(int)));
  connect(slide, SIGNAL(valueChanged(int)), sbox, SLOT(setValue(int)));
  connect(sbox, SIGNAL(editingFinished()), SLOT(retranslateNewValue()));
  connect(slide, SIGNAL(sliderReleased()), SLOT(retranslateNewValue()));
  connect(slide, SIGNAL(rangeChanged(int,int)), SLOT(setRange(int,int)));
}

int QSpinSlide::value() const {
  return sbox->value();
}

void QSpinSlide::setValue(int val) {
  oldvalue = val;
  sbox->setValue(val);
  slide->setValue(val);
}

void QSpinSlide::setRange(int minimum, int maximum) {
  sbox->setRange(minimum, maximum);
  slide->setRange(minimum, maximum);
}

void QSpinSlide::retranslateNewValue(QWidget * oldwdg) {
  QCoreApplication::processEvents(); // to allow connected "valueChanged" get processed.
  int val=oldvalue;
  if ( sender() == sbox || oldwdg == sbox)
    val = sbox->value();
  else if ( sender() == slide )
    val = slide->value();
  if (val != oldvalue)
    emit valueChanged(oldvalue=val);
}


