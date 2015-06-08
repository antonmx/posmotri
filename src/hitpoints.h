#ifndef HITPOINTS_H
#define HITPOINTS_H

#include "hitpointgrabber.h"

class HitPoints : public QObject
{
 Q_OBJECT

 public :
  HitPoints();
  ~HitPoints();

  bool grabsMouse();

  void addInMouseGrabberPool();
  void addInMouseGrabberPool(int i);

  void removeFromMouseGrabberPool();
  void removeFromMouseGrabberPool(int i);

  QList<qglviewer::Vec> points();
  QList<qglviewer::Vec> activePoints();

  QList<qglviewer::Vec> barePoints();

  void ignore(bool);

  int count();
  int bareCount();
  int activeCount();
  bool point(int, qglviewer::Vec&);
  bool activePoint(int, qglviewer::Vec&);

  void clear();
  void removeActive();
  void resetActive();

  void draw(QGLViewer*, bool);
  void postdraw(QGLViewer*);

  bool keyPressEvent(QKeyEvent*);

  int pointSize();
  qglviewer::Vec pointColor();

  QList<qglviewer::Vec> renewValues();
  void setRawTagValues(QList<QVariant>, QList<QVariant>);

  HitPointGrabber* checkIfGrabsMouse(int, int, qglviewer::Camera*);
  void mousePressEvent(QMouseEvent*, qglviewer::Camera*);
  void mouseMoveEvent(QMouseEvent*, qglviewer::Camera*);
  void mouseReleaseEvent(QMouseEvent*, qglviewer::Camera*);

 signals :
  void sculpt(int, QList<qglviewer::Vec>, float, float, int);

 public slots :
  void add(qglviewer::Vec);
  void setPoints(QList<qglviewer::Vec>);
  void setBarePoints(const QList<qglviewer::Vec> &);
  void addPoints(QString);
  void addBarePoints(QString);
  void savePoints(QString);
  void removeBarePoints();
  void setPointSize(int);
  void setPointColor(qglviewer::Vec);
  void setMouseGrab(bool);
  void toggleMouseGrab();

 private slots :
  void updatePoint();

 private :
  bool m_ignore;
  QList<HitPointGrabber*> m_points;
  QList<QVariant> m_rawValues;
  QList<QVariant> m_tagValues;
  bool m_showPoints;
  bool m_showRawValues;
  bool m_showTagValues;
  bool m_showCoordinates;

  qglviewer::Vec m_pointColor;
  int m_pointSize;

  bool m_grab;

  QList<qglviewer::Vec> m_barePoints;

  void drawArrows(qglviewer::Vec, int);

  void updatePointDialog();
  void makePointConnections();
  void processCommand(int, QString);
};

#endif
