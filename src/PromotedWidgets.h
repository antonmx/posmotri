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
#include <QDoubleSpinBox>


class QMSpinBox :  public QSpinBox {
  Q_OBJECT;
public:
  QMSpinBox(QWidget * parent = 0) : QSpinBox(parent) {}
public slots:
  void  setRange(int minimum, int maximum) { QSpinBox::setRange(minimum,  maximum); }
};

class QMDoubleSpinBox :  public QDoubleSpinBox {
  Q_OBJECT;
public:
  QMDoubleSpinBox(QWidget * parent = 0) : QDoubleSpinBox(parent) {}
public slots:
  void  setRange(double minimum, double maximum) { QDoubleSpinBox::setRange(minimum,  maximum); }
};

#endif // PROMOTEDWIDGETS_H
