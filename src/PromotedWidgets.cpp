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
#include <limits>
#include <QFile>

using namespace qglviewer;
using namespace std;




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
  bool ok;
  Vec tvec = QVecEdit::toVec(input, &ok);
  if ( ! ok )
    return QValidator::Intermediate;
  QVecEdit * vec = dynamic_cast<QVecEdit*>( parent() );
  if (vec)
    return  ( tvec.x < vec->minimum().x || tvec.x > vec->maximum().x
           || tvec.y < vec->minimum().y || tvec.y > vec->maximum().y
           || tvec.z < vec->minimum().z || tvec.z > vec->maximum().z )
         ? QValidator::Intermediate : QValidator::Acceptable;
  return QValidator::Acceptable;
}








QVecEdit::QVecEdit(QWidget * parent)
  : QLineEdit(parent)
  , oldVec(0,0,0)
{
  bool ok;
  Vec initvec = toVec(text(),&ok);
  if(!ok)
    initvec=Vec(1,1,1);
  const double rm=std::numeric_limits<double>::max();
  setRange( Vec(-rm,-rm,-rm), Vec(rm,rm,rm));
  setValue( initvec );

  setValidator(new QVecValidtor(this));

  connect(this, SIGNAL(returnPressed()), SLOT(retranslateNewValue()));
  //connect(this, SIGNAL(editingFinished()), SLOT(retranslateNewValue()));
}


Vec QVecEdit::value() const {
  return hasAcceptableInput()  ?  toVec(text())  :  oldVec;
}

void QVecEdit::setValue(const Vec & vec) {
  setText(toString(vec));
  oldVec=value();
}

void QVecEdit::retranslateNewValue() {

  if ( ! hasAcceptableInput() ) {
    setValue(oldVec);
    return;
  }
  const Vec newVec = value();
  if (newVec != oldVec)
    emit valueChanged(oldVec=newVec);
}

void QVecEdit::focusOutEvent ( QFocusEvent * e ) {
  retranslateNewValue();
  QLineEdit::focusOutEvent(e);
}

QString QVecEdit::toString ( const Vec & vec ) {
  return QString("%1 %2 %3").arg(vec.x).arg(vec.y).arg(vec.z);
}

Vec QVecEdit::toVec ( const QString & str, bool * ok) {
  if(ok) *ok = true;
  QStringList list = str.split(" ", QString::SkipEmptyParts);
  if (list.count() != 3) {
    if(ok) *ok=false;
    return Vec(0,0,0);
  }
  bool v0, v1, v2;
  Vec ret(list[0].toDouble(&v0), list[1].toDouble(&v1), list[2].toDouble(&v2));
  if (ok) *ok = v0 && v1 && v2;
  return ret;
}

void QVecEdit::setRange ( const Vec & min, const Vec & max) {
  _min = min;
  _max = max;
  setValue(value()); // to revalidate
}











QDataStream &operator<<(QDataStream & stream, const Vec & vec) {
  stream << vec.x << vec.y << vec.z;
}

QDataStream &operator>>(QDataStream & stream, Vec & vec) {
  stream >> vec.x >> vec.y >> vec.z;
}

QDataStream &operator<<(QDataStream & stream, const Quaternion & qn) {
  stream << qn.axis() << qn.angle();
}

QDataStream &operator>>(QDataStream & stream, Quaternion & qn) {
  qreal angle;
  Vec axis;
  stream >> axis >> angle;
  qn=Quaternion(axis, angle);
}




void QConfigMe::levelUp() const {
  if (cpath.isEmpty())
    return;
  int curpos = cpath.length()-1;
  int startpos=0;
  QString ret;
  while ( curpos && ! startpos ) {
    if ( cpath[curpos] == '/' ) {
      if ( cpath[curpos-1] == '\\' )
        curpos--;
      else
        startpos=curpos;
    }
    curpos--;
  }
  cpath.truncate(startpos);
}


QString QConfigMe::modifyKey(const QString &skey) {
  return skey;
  QString key(skey);
  key.replace("/", "\\/");
  key.replace(" ", "\\ ");
  key.replace("\\", "\\\\");
  return key;
}


void QConfigMe::read(const QString & fileName) {
  QFile file(fileName);
  if ( ! file.open(QIODevice::ReadOnly) ) {
    qDebug() << "Could not read configMe into file" << fileName;
    return;
  }
  QDataStream stream(&file);
  while (!stream.atEnd()) {
    QString key, tmp;
    QByteArray val;
    stream >> key >> tmp >> val >> tmp;
    store[key] = val;
  }
  file.close();
}

bool QConfigMe::write(const QString & fileName) const {
  QFile file(fileName);
  if ( ! file.open(QIODevice::WriteOnly) ) {
    qDebug() << "Could not save configMe into file" << fileName;
    return false;
  }
  QDataStream stream(&file);
  foreach ( const QString & skey, store.keys() )
    stream << skey << QString(" ") << store[skey] << QString("\n");
  file.close();
}


int QConfigMe::beginArray(const QString & key, bool toEnd) const {

  beginGroup(key);

  int counter=0;
  QString prefix = cpath+"/";
  foreach (QString path, store.keys())
    if (path.indexOf(prefix)==0){
      path.remove(0, prefix.length());
      const int tr=path.indexOf(QRegExp("[\\D]"));
      if (tr>=0)
        path.truncate(tr);
      bool ok;
      const int el = path.toInt(&ok);
      if ( ok && el>counter )
        counter = el;
    }

  idxelement.append( qMakePair( cpath.length()+1,  toEnd ? counter : 0 ) );
  advanceArray();

  return counter;

}

int QConfigMe::advanceArray() const {
  if (idxelement.empty())
    return 0;
  QPair<int,int> & idxl = idxelement.last();
  cpath.truncate(idxl.first-1);
  idxl.second++;
  beginGroup( QString::number( idxl.second ) );
  return idxl.second;
}

void QConfigMe::endArray() const {
  if (idxelement.empty())
    return;
  cpath.truncate( idxelement.takeLast().first - 1 );
  levelUp();
}

int QConfigMe::beginGroup(const QString & key) const {
  cpath += "/" + modifyKey(key);
  int cnt=0;
  foreach (const QString & path, store.keys())
    if ( path.indexOf(cpath+QString("/"))==0  ||  path == cpath )
      cnt++;
  return cnt;
}

void QConfigMe::endGroup() const {
  levelUp();
}

bool QConfigMe::contains(const QString & key) const {
  bool ret = beginGroup(key);
  endGroup();
  return ret;
}




