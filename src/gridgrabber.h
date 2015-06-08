#ifndef GRIDGRABBER_H
#define GRIDGRABBER_H

//#include <QtGui>

#include "gridobject.h"
#include <QGLViewer/mouseGrabber.h>


class GridGrabber : public QObject, public qglviewer::MouseGrabber, public GridObject
{
 Q_OBJECT

 public :
  GridGrabber();
  ~GridGrabber();

  enum MoveAxis
  {
    MoveX,
    MoveY,
    MoveZ,
    MoveAll
  };

  int moveAxis();
  void setMoveAxis(int);

  int pointPressed();

  void mousePosition(int&, int&);
  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);

  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);

 signals :
  void selectForEditing(int, int);
  void deselectForEditing();

 private :
  int m_lastX, m_lastY;
  int m_pointPressed;
  int m_moveAxis;
  bool m_pressed;
  QPoint m_prevPos;
  bool m_moved;
};

#endif
