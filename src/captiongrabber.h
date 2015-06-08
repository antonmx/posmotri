#ifndef CAPTIONGRABBER_H
#define CAPTIONGRABBER_H

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/mouseGrabber.h>


#include "captionobject.h"

class CaptionGrabber : public qglviewer::MouseGrabber, public CaptionObject
{
 public :
  CaptionGrabber();
  ~CaptionGrabber();

  CaptionObject caption();

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
