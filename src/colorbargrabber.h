#ifndef COLORBARGRABBER_H
#define COLORBARGRABBER_H

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/mouseGrabber.h>


#include "colorbarobject.h"

class ColorBarGrabber : public qglviewer::MouseGrabber, public ColorBarObject {
public :
  ColorBarGrabber();
  ~ColorBarGrabber();
  
  ColorBarObject colorbar();

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
