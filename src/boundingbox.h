#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "global.h"
#include <QKeyEvent>
#include "mymanipulatedframe.h"

class BoundingBox : public QObject {
 Q_OBJECT

 public :
  BoundingBox();
  ~BoundingBox();

  void activateBounds();
  void deactivateBounds();

  void setPositions(qglviewer::Vec, qglviewer::Vec);
  void setBounds(qglviewer::Vec, qglviewer::Vec);
  void bounds(qglviewer::Vec&, qglviewer::Vec&);
  void draw();
  bool keyPressEvent(QKeyEvent*);

 signals :
  void updated();

 private slots :
  void update();

 private :
  MyManipulatedFrame m_bounds[6];
  qglviewer::Vec m_dataMin, m_dataMax;
  qglviewer::Vec boxColor, defaultColor, selectColor;

  void drawX(float, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);
  void drawY(float, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);
  void drawZ(float, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);

  void updateMidPoints();
};

#endif
