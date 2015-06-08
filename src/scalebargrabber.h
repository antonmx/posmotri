#ifndef SCALEBARGRABBER_H
#define SCALEBARGRABBER_H

#include "scalebarobject.h"
#include <QGLViewer/mouseGrabber.h>
#include <QGLViewer/camera.h>


class ScaleBarGrabber : public qglviewer::MouseGrabber, public ScaleBarObject {
public :
  ScaleBarGrabber();
  ~ScaleBarGrabber();
  
  ScaleBarObject scalebar();
  
  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);
  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  
private :
  bool m_dragging;
  int m_prevx, m_prevy;
  QPointF m_prevpos;
  
};


#endif
