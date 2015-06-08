#ifndef PAINTBALL_H
#define PAINTBALL_H

#include "mymanipulatedframe.h"

class PaintBall : public QObject
{
 Q_OBJECT

 public :
  PaintBall();
  ~PaintBall();

  bool grabsMouse();

  void setBounds(qglviewer::Vec, qglviewer::Vec);

  void setShowPaintBall(bool);
  bool showPaintBall();
  
  void setPosition(qglviewer::Vec);
  qglviewer::Vec position();

  void setSize(qglviewer::Vec);
  qglviewer::Vec size();
  
  void draw();

  bool keyPressEvent(QKeyEvent*);

 signals :
  void updateGL();
  void tagVolume(int, bool);
  void fillVolume(int, bool);
  void dilateVolume(int, int, bool);
  void erodeVolume(int, int, bool);
  void tagSurface(int, int, bool, bool);
  
 private slots :
  void bound();

 private : 
  bool m_show;
  qglviewer::Vec m_size;

  qglviewer::Vec m_dataMin;
  qglviewer::Vec m_dataMax;

  int m_tag;
  int m_thickness;

  qglviewer::LocalConstraint *m_constraints;
  MyManipulatedFrame m_frame;

  MyManipulatedFrame m_bounds[6];

  void processCommand(QString);
  void setSizeBounds();

  qglviewer::Vec m_fpos, m_pb0, m_pb1;
};

#endif
