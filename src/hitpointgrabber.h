#ifndef HITPOINTGRABBER_H
#define HITPOINTGRABBER_H

//#include <QtGui>

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/mouseGrabber.h>



class HitPointGrabber : public QObject, public qglviewer::MouseGrabber
{
 Q_OBJECT

 public :
  HitPointGrabber(qglviewer::Vec);
  ~HitPointGrabber();

  enum MoveAxis
  {
    MoveX,
    MoveY,
    MoveZ,
    MoveAll
  };


  bool active();
  void resetActive();

  void setPoint(qglviewer::Vec);
  qglviewer::Vec point();

  int moveAxis();
  void setMoveAxis(int);

  void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);
  void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
  void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);

  bool isInActivePool();
  void addToActivePool();
  void removeFromActivePool();

  static void clearActivePool();
  static const QList<HitPointGrabber*> activePool();

 signals :
  void updatePoint();

 private :
  qglviewer::Vec m_point;
  bool m_active;
  int m_moveAxis;
  bool m_pressed;
  QPoint m_prevPos;


  static QList<HitPointGrabber*> activeHitPointPool_;
};

#endif
