#ifndef DIRECTIONVECTORWIDGET_H
#define DIRECTIONVECTORWIDGET_H

#include <QGLViewer/vec.h>


class LightDisc : public QWidget {
  Q_OBJECT;
  
private :
  QPointF m_direction;
  bool m_backlit;
  
public :
  
  LightDisc(QWidget *parent = NULL);
  inline QPointF direction() const {return m_direction;}  

public slots:
  
  void setDirection(const QPointF & pos);
  void setBacklit(bool); 

signals :
  void directionChanged(const QPointF &);
  
private:
  void onMouseSet(const QPointF & pos);
  
private slots:
  
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void paintEvent(QPaintEvent*);
  
};



#include "ui_directionvectorwidget.h"


class DirectionVectorWidget : public QWidget {
 Q_OBJECT;
 
private :
  Ui::DirectionVectorWidget ui;

public :
  
  DirectionVectorWidget(QWidget *parent=NULL);

  void setVector(qglviewer::Vec);
  qglviewer::Vec vector();

signals :
  void directionChanged(qglviewer::Vec);
  
private slots :
  void updateDirection(QPointF);
  void onDirectionChange();
  void onLenChange();
  
};


#endif
