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




#endif // PROMOTEDWIDGETS_H
