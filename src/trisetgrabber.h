#ifndef TRISETGRABBER_H
#define TRISETGRABBER_H
#include "trisetobject.h"
#include <QGLViewer/mouseGrabber.h>


class TrisetGrabber
  : public QObject
  , public qglviewer::MouseGrabber
  , public TrisetObject
{
  Q_OBJECT;

public :
  TrisetGrabber();
  ~TrisetGrabber();

  enum MoveAxis {
    MoveX,
    MoveY,
    MoveZ,
    MoveAll
  };

  int pointPressed();

  void mousePosition(int&, int&);

  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);

  int moveAxis();
  void setMoveAxis(int);

  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);

 private :
  int m_lastX, m_lastY;
  int m_pointPressed;
  int m_moveAxis;
  bool m_pressed;
  QPoint m_prevPos;
  
};

#endif
