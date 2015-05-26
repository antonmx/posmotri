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


class QSpinSlide : public QObject {
  Q_OBJECT;
private:
  QSpinBox * sbox;
  QSlider  * slide;
  int oldvalue;
public:
  explicit QSpinSlide (QSlider  * _slide, QSpinBox * _box,  QObject * parent=0);
  int value() const;
public slots:
  void setValue(int);
  void setRange(int, int);
signals:
  void valueChanged(int);
private slots:
  void retranslateNewValue(QWidget *oldwdg=0);
};

#endif // PROMOTEDWIDGETS_H
