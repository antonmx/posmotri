#ifndef NETWORKGRABBER_H
#define NETWORKGRABBER_H

#include "networkobject.h"
#include <QGLViewer/mouseGrabber.h>

class NetworkGrabber : public QObject, public qglviewer::MouseGrabber, public NetworkObject {
  Q_OBJECT;

public :
  NetworkGrabber();
  ~NetworkGrabber();

  int pointPressed();

  void mousePosition(int&, int&);

  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);

  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);

private :
  int m_lastX, m_lastY;
  int m_pointPressed;
  bool m_pressed;
};

#endif
