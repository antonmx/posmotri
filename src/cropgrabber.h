#ifndef CROPGRABBER_H
#define CROPGRABBER_H

#include <QGLViewer/mouseGrabber.h>
#include "cropobject.h"

class CropGrabber : public QObject, public qglviewer::MouseGrabber, public CropObject {
 Q_OBJECT;

 public :
  CropGrabber();
  ~CropGrabber();

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
  bool m_pressed;
  QPoint m_prevPos;
  bool m_moved;
};

#endif
