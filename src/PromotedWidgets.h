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

#ifndef PROMOTEDWIDGETS_H
#define PROMOTEDWIDGETS_H

#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QValidator>
#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>
# include <QDebug>
#include <QBrush>


class QSpinSlide : public QObject {
  Q_OBJECT;
private:
  QSpinBox * sbox;
  QSlider  * slide;
  int oldvalue;
public:
  explicit QSpinSlide (QSlider  * _slide, QSpinBox * _box,  QObject * parent=0);
  int value() const;
  int minimum() const;
  int maximum() const;
public slots:
  void setValue(int);
  void setRange(int, int);
signals:
  void valueChanged(int);
private slots:
  void retranslateNewValue();
};


class QDoubleSpinSlide : public QObject {
  Q_OBJECT;
private:
  QDoubleSpinBox * const sbox;
  QSlider  * const slide;
  double oldvalue;
  double coefa;
  double coefb;
public:
  explicit QDoubleSpinSlide (QSlider * _slide, QDoubleSpinBox * _box,  QObject * parent=0);
  double value() const;
  double minimum() const;
  double maximum() const;
public slots:
  void setValue(double val);
  void setRange(double, double);
signals:
  void valueChanged(double);
  void valueChanged(float);
private slots:
  void retranslateNewValue();
  void setValue();
};






class QVecValidtor  :  public QValidator {
  Q_OBJECT;
public:
  QVecValidtor(QObject *parent = 0) : QValidator(parent) {}
  QValidator::State validate(QString & input, int & pos) const ;
};


class QVecEdit : public QLineEdit {
  Q_OBJECT;

private:
  qglviewer::Vec _min;
  qglviewer::Vec _max;
  qglviewer::Vec oldVec;

public:
  QVecEdit(QWidget * parent = 0);
  qglviewer::Vec value() const ;
  const qglviewer::Vec & minimum() const {return _min;}
  const qglviewer::Vec & maximum() const {return _max;}
  static QString toString(const qglviewer::Vec & );
  static qglviewer::Vec toVec(const QString & , bool * ok=0);

public slots:
  void setValue(const qglviewer::Vec & );
  void setRange(const qglviewer::Vec & , const qglviewer::Vec & );

signals:
  void valueChanged(const qglviewer::Vec & );

private slots:
  void retranslateNewValue();

protected:
  virtual void 	focusOutEvent(QFocusEvent * e);

};





QDataStream &operator<<(QDataStream &, const qglviewer::Vec &);
QDataStream &operator>>(QDataStream &, qglviewer::Vec &);
QDataStream &operator<<(QDataStream &, const qglviewer::Quaternion &);
QDataStream &operator>>(QDataStream &, qglviewer::Quaternion &);




class QConfigMe {
  
private:  
  
  static QString modifyKey(const QString &skey);
  
  QMap <QString, QByteArray> store;
  mutable QString cpath;
  mutable QList<int> idxelement;
  mutable int lastelement;
  
  void levelUp() const;  
  int updateLastelement() const;
  

public:
  
  QConfigMe() {};

  void read(const QString & fileName);  
  bool write(const QString & fileName) const ;
  
  
  int beginArray(const QString & key) const;  
  int advanceArray() const;  
  void endArray() const;  
  int beginGroup(const QString & key) const;  
  void endGroup() const;
  
  bool contains(const QString & key) const;
  
  template <class Ecl> void setValue(const QString & key, const Ecl & val) {
    QByteArray bval;
    QDataStream sval(&bval, QIODevice::WriteOnly);
    sval << val;
    store[cpath + "/" + modifyKey(key)] = bval;
  }
  
  template <class Ecl> bool getValue(const QString & key, Ecl & val) const {
    const QString skey = cpath + "/" + modifyKey(key);
    if ( ! store.contains(skey) )
      return false;
    QDataStream sval(store[skey]);
    sval >> val;
    return true;
  }
  
  template <class Ecl> Ecl getValue(const QString & key) const {
    Ecl el;
    if ( ! getValue<Ecl>(key, el) )
      qDebug() << "QConfigMe detected error when reading value ok key" << key;
    return el;
  }

  template <class Vcl> void setArrayValue(const QString & key, const Vcl & valarr) {
    QByteArray bval;
    beginArray(key);
    for (int i=0; i<valarr.size() ; i++ ) {
      bval.clear();
      QDataStream sval(&bval, QIODevice::WriteOnly);
      sval << valarr.at(i);
      store[cpath] = bval;
      advanceArray();
    }
    endArray();
  }
  
  template <class Ecl> int getArrayValue(const QString & key, QList<Ecl> & valarr) const {
    const int sz = beginArray(key);
    QByteArray bval;
    for (int i=0; i<sz ; i++ ) {
      if ( store.contains(cpath) ) {
        QDataStream sval(store[cpath]);
        Ecl val;
        sval >> val;
        valarr.append(val);
      }
      advanceArray();
    }
    endArray();
  }
  
  template <class Ecl>
  void setClassArray(const QString & key, const QList<Ecl> & list) {
    beginArray(key);
    foreach (const Ecl & element,  list) {
      element.save(*this);
      advanceArray();
    }
    endArray();
  }
  
  template <class Ecl>
  void getClassArray(const QString & key, QList<Ecl> & list) const {
    const int size = beginArray(key);
    for (int el=0; el<size; el++) {
      Ecl element;
      element.load(*this);
      list.append(element);
      advanceArray();
    }
    endArray();
  }
  
  template <class Ecl>
  void setClassArray(const QString & key, const QList<Ecl*> & list) {
    beginArray(key);
    foreach (const Ecl * element,  list) {
      element->save(*this);
      advanceArray();
    }
    endArray();
  }
  
  template <class Ecl>
  void getClassArray(const QString & key, QList<Ecl*> & list) const {
    const int size = beginArray(key);
    for (int el=0; el<size; el++) {
      Ecl * element = new Ecl();
      element->load(*this);
      list.append(element);
      advanceArray();
    }
    endArray();
  }
  
};





#endif // PROMOTEDWIDGETS_H
