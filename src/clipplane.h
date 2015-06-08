#ifndef CLIPPLANES_H
#define CLIPPLANES_H

#include "clipinformation.h"
#include "clipgrabber.h"

class ClipPlanes : public QObject
{
 Q_OBJECT

 public :
  ClipPlanes();
  ~ClipPlanes();

  ClipInformation clipInfo();

  QList<int> tfset();
  QList<QVector4D> viewport();
  QList<bool> viewportType();
  QList<float> viewportScale();
  QList<int> thickness();
  QList<bool> applyClip();
  QList<qglviewer::Vec> positions();
  QList<qglviewer::Vec> normals();
  QList<qglviewer::Vec> xaxis();
  QList<qglviewer::Vec> yaxis();
  QList<bool> showSlice();
  QList<bool> showOtherSlice();

  bool viewportsVisible();
  int viewportGrabbed();
  void resetViewportGrabbed();
  void setViewportGrabbed(int, bool);
  bool viewportKeypressEvent(int, QKeyEvent*);

  void reset();
  void setBounds(qglviewer::Vec, qglviewer::Vec);

  int inViewport(int, int, int, int);

  bool show(int);
  void setShow(int, bool);
  void show();
  void hide();

  bool isInMouseGrabberPool(int);
  void addInMouseGrabberPool();
  void addInMouseGrabberPool(int);
  void removeFromMouseGrabberPool();
  void removeFromMouseGrabberPool(int);

  bool grabsMouse();

  void clear();

  int count();
  void addClip();
  void addClip(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);

  void draw(QGLViewer*, bool);
  void postdraw(QGLViewer*);

  bool keyPressEvent(QKeyEvent*);

  void updateScaling();

  void translate(int, qglviewer::Vec);
  void rotate(int, int, float);
  void modViewportScale(int, float);
  void modThickness(int, int);

  void drawViewportBorders(QGLViewer*);
  void drawOtherSlicesInViewport(QGLViewer*, int);
  void drawPoints(int, QList<qglviewer::Vec>);

 signals :
  void showMessage(QString, bool);
  void addClipper();
  void removeClipper(int);
  void updateGL();
  void mopClip(qglviewer::Vec, qglviewer::Vec);
  void reorientCameraUsingClipPlane(int);
  void saveSliceImage(int, int);
  void extractClip(int, int, int);

 public slots :
  void set(ClipInformation);

 private slots :
  void selectForEditing();
  void deselectForEditing();

 private :
  qglviewer::Vec m_dataMin, m_dataMax;

  QList<ClipGrabber*> m_clips;

  void makeClipConnections();
  void processCommand(int, QString);
  void drawViewportIntersections(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec*);
};


#endif
