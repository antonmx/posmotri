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

#include <QDebug>
#include <QString>
#include <math.h>

using namespace qglviewer;




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

int QSpinSlide::minimum() const {
  return slide->minimum();
}

int QSpinSlide::maximum() const {
  return slide->maximum();
}

void QSpinSlide::setValue(int val) {
  if (sender() != slide)
    slide->setValue(val);
  if (sender() != sbox)
    sbox->setValue(val);
  if ( sender() != sbox  &&  sender() != slide  &&  val != oldvalue )
    emit valueChanged(oldvalue=val);
}

void QSpinSlide::setRange(int minimum, int maximum) {
  sbox->setRange(minimum, maximum);
  slide->setRange(minimum, maximum);
}

void QSpinSlide::retranslateNewValue() {
  int val=sbox->value();
  if (val != oldvalue)
    emit valueChanged(oldvalue=val);
}







QDoubleSpinSlide::QDoubleSpinSlide (QSlider * _slide, QDoubleSpinBox * _box,  QObject * parent)
  : QObject (parent)
  , slide(_slide)
  , sbox(_box)
  , oldvalue(_box->value())
  , coefa(1.0)
  , coefb(0.0)
{
  setRange(sbox->minimum(), sbox->maximum());
  setValue();
  connect(sbox, SIGNAL(valueChanged(double)), SLOT(setValue()));
  connect(slide, SIGNAL(valueChanged(int)), SLOT(setValue()));
  connect(sbox, SIGNAL(editingFinished()), SLOT(retranslateNewValue()));
  connect(slide, SIGNAL(sliderReleased()), SLOT(retranslateNewValue()));
}

double QDoubleSpinSlide::value() const {
  return sbox->value();
}

double QDoubleSpinSlide::minimum() const {
  return sbox->minimum();
}

double QDoubleSpinSlide::maximum() const {
  return sbox->maximum();
}


void QDoubleSpinSlide::setValue(double val) {
  sbox->setValue(val);
  retranslateNewValue();
}

void QDoubleSpinSlide::setValue() {
  if (sender() == sbox) {
    slide->blockSignals(true);
    slide->setValue( (int) rint((sbox->value()-coefb)/coefa) );
    slide->blockSignals(false);
  } else { /*slider or constructor*/
    sbox->blockSignals(true);
    sbox->setValue(coefa * slide->sliderPosition() + coefb);
    sbox->blockSignals(false);
  }
}

void QDoubleSpinSlide::setRange(double minimum, double maximum) {
  sbox->setRange(minimum, maximum);
  int irange = slide->maximum() - slide->minimum();
  if ( ! irange )
    qDebug() <<  "QDoubleSpinSlide: 0-range of the slider. Should never happen. Report to developper.";
  else {
    coefa = ( sbox->maximum() - sbox->minimum() ) / irange ;
    coefb = ( slide->maximum() * sbox->minimum() - slide->minimum() * sbox->maximum()  ) / irange ;
  }
  sbox->setSingleStep(coefa);
}

void QDoubleSpinSlide::retranslateNewValue() {
  double val = sbox->value();
  if (val != oldvalue) {
    emit valueChanged(oldvalue=val);
    emit valueChanged((float)val);
  }
}





QValidator::State QVecValidtor::validate(QString & input, int & pos) const {
  QStringList list = input.split(" ", QString::SkipEmptyParts);
  if (list.count() != 3)
    return QValidator::Intermediate;
  foreach (QString str, list) {
    bool ok;
    str.toDouble(&ok);
    if (!ok)
      return QValidator::Intermediate;
  }
  return QValidator::Acceptable;
}




QVecEdit::QVecEdit(QWidget * parent)
  : QLineEdit(parent) 
  , oldVec(0,0,0)
{
  setValidator(new QVecValidtor(this));
  setValue(oldVec);
  connect(this, SIGNAL(editingFinished()), SLOT(retranslateNewValue()));
}
 
 
Vec QVecEdit::value() const {
  if ( ! hasAcceptableInput() )
    return oldVec;
  QStringList list = text().split(" ", QString::SkipEmptyParts);
  return Vec(list[0].toDouble(), list[1].toDouble(), list[2].toDouble());
}

void QVecEdit::setValue(const Vec & vec) {
  setText( QString("%1 %2 %3").arg(vec.x).arg(vec.y).arg(vec.z) );
}

void QVecEdit::retranslateNewValue() {
  if ( ! hasAcceptableInput() )
    return;
  const Vec newVec = value();
  if (newVec != oldVec)
    emit valueChanged(oldVec=newVec);
}

void QVecEdit::focusOutEvent ( QFocusEvent * e ) {
  if ( ! hasAcceptableInput() )
    setValue(oldVec);
  QLineEdit::focusOutEvent(e);
}




