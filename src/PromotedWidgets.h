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
# include <QSettings>
# include <QDebug>


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







template <class varclass> varclass & getQSettingsValue
  (QSettings & cfg,  const QString & key,  varclass & val)
{
  if ( ! cfg.contains(key) ) {
    qDebug() << "Config does not contain key" << key;
    return val;
  }
  QVariant value = cfg.value(key);
  if ( ! value.canConvert<varclass>() )
    qDebug() << "Value read from config key " << key << ": is not valid for the class.";
  else
    val = value.value<varclass>();
  return val;
}

template <class varclass> varclass getQSettingsValue
  (QSettings & cfg,  const QString & key)
{
  varclass val;
  return getQSettingsValue(cfg, key, val);
}


uchar * getQSettingsValue(QSettings & cfg,  const QString & key,  uchar * val,  size_t sz) {
  const QByteArray qbarr = getQSettingsValue<QByteArray>(cfg,  key);
  if ( qbarr.size() != sz )
    qDebug() << "Error on loading char array" << key
             <<  ": unexpected array size" << qbarr.size() << "not" <<  sz <<  ".";
  else
    memcpy(val, qbarr.data(),  1024);
  return val;
}




template <class listclass> void QSettingsSetValArray
  (QSettings & cfg, const QString & arrayName,  const QList<listclass> & list)
{
  int arridx = 0;
  cfg.beginWriteArray(arrayName+"Array",  list.size());
  foreach (const listclass & element,  list) {
    cfg.setArrayIndex(arridx++);
    cfg.setValue(arrayName,  element);
  }

  cfg.endArray();
}

void QSettingsSetValArray
  (QSettings & cfg, const QString & arrayName, const QList<qglviewer::Vec> & list)
{
  QStringList slist;
  foreach (const qglviewer::Vec & vec,  list)
    slist <<  QVecEdit::toString(vec);
  QSettingsSetValArray(cfg, arrayName,  slist);
}


template <class listclass> void QSettingsGetValArray
  (QSettings &cfg, const QString &arrayName, QList<listclass> &list)
{
  const int size = cfg.beginReadArray(arrayName + "Array");
  for (int i = 0; i < size; i++) {
    cfg.setArrayIndex(i);
    QVariant val = cfg.value(arrayName);
    if ( ! val.isValid()  )
      qDebug() << "Config could not get expected array value for " << arrayName <<  ".";
    else if  ( ! val.canConvert<listclass>() )
      qDebug() << "Config could not convert array value (" << val << ") for " << arrayName << ".";
    else
      list.append( val.value<listclass>() );
  }
  cfg.endArray();
}

void QSettingsGetValArray(QSettings & cfg, const QString & arrayName, QList<qglviewer::Vec> & list) {
  QStringList slist;
  QSettingsGetValArray(cfg,  arrayName,  slist);
  foreach (const QString & svec,  slist) {
    bool ok;
    qglviewer::Vec vec = QVecEdit::toVec(svec,  &ok);
    if (ok)
      list.append(vec);
  }
}


template <class listclass> void QSettingsSaveArray
  (QSettings & cfg, const QString & arrayName, const QList<listclass> & list)
{
  int arridx = 0;
  cfg.beginWriteArray(arrayName,  list.size());
  foreach (const listclass & element,  list) {
    cfg.setArrayIndex(arridx++);
    element.save(cfg);
  }
  cfg.endArray();
}

template <class listclass> void QSettingsLoadArray
  (QSettings & cfg, const QString & arrayName, QList<listclass> & list)
{
  int arridx = 0;
  const int size = cfg.beginReadArray(arrayName);
  for (int i = 0; i<size; i++) {
    cfg.setArrayIndex(arridx++);
    listclass inst;
    inst.load(cfg);
    list.append(inst);
  }
  cfg.endArray();
}


template <class listclass> void QSettingsLoadArray
  (QSettings & cfg, const QString & arrayName, QList<listclass*> & list)
{
  int arridx = 0;
  const int size = cfg.beginReadArray(arrayName);
  for (int i = 0; i<size; i++) {
    cfg.setArrayIndex(arridx++);
    listclass * inst = new listclass;
    inst->load(cfg);
    list.append(inst);
  }
  cfg.endArray();
}



QString nextString(std::fstream &fin,  char delim = 0);



#endif // PROMOTEDWIDGETS_H
