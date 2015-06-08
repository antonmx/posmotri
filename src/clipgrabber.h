#ifndef CLIPGRABBER_H
#define CLIPGRABBER_H

#include "clipobject.h"
//#include <QtGui>
#include <QGLViewer/mouseGrabber.h>


class ClipGrabber : public QObject, public qglviewer::MouseGrabber, public ClipObject
{
 Q_OBJECT

 public :
  ClipGrabber();
  ~ClipGrabber();

  int pointPressed();

  void mousePosition(int&, int&);
  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);

  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);

  void wheelEvent(QWheelEvent* const, qglviewer::Camera* const);

 signals :
  void selectForEditing();
  void deselectForEditing();

 private :
  int m_lastX, m_lastY;
  int m_pointPressed;
  bool m_pressed;
  QPoint m_prevPos;

  bool xActive(const qglviewer::Camera* const, qglviewer::Vec, qglviewer::Vec, bool&);
  bool yActive(const qglviewer::Camera* const, qglviewer::Vec, qglviewer::Vec, bool&);
  bool zActive(const qglviewer::Camera* const, qglviewer::Vec, qglviewer::Vec);
};

#endif
