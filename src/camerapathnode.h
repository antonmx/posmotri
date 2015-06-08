#ifndef CAMERAPATHNODE_H
#define CAMERAPATHNODE_H

#include <QObject>
#include <QGLViewer/qglviewer.h>


class CameraPathNode : public QObject
{
 Q_OBJECT

 public :
  CameraPathNode(qglviewer::Vec, qglviewer::Quaternion);
  
  qglviewer::Vec position();
  void setPosition(qglviewer::Vec);

  qglviewer::Quaternion orientation();
  void setOrientation(qglviewer::Quaternion);

  void draw(float);
  int keyPressEvent(QKeyEvent*, bool&);
  bool markedForDeletion();

 public slots :
  void nodeModified();

 signals :
  void modified();

 private :
  qglviewer::ManipulatedFrame *m_mf;
  bool m_markForDelete;
  qglviewer::AxisPlaneConstraint *m_constraints;
};

#endif
