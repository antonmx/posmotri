#ifndef PATHS_H
#define PATHS_H

//#include <QtGui>
#include "pathgrabber.h"

class Paths : public QObject
{
 Q_OBJECT

 public :
  Paths();
  ~Paths();

  bool isInMouseGrabberPool(int);
  void addInMouseGrabberPool();
  void addInMouseGrabberPool(int);
  void removeFromMouseGrabberPool();
  void removeFromMouseGrabberPool(int);

  bool grabsMouse();

  void clear();

  QList<PathObject> paths();
  void setPaths(QList<PathObject>);

  int count();
  void addPath(QList<qglviewer::Vec>);
  void addPath(PathObject);
  void addPath(QString);

  void draw(QGLViewer*, bool, qglviewer::Vec);
  void postdraw(QGLViewer*);

  void postdrawInViewport(QGLViewer*,
			  QVector4D, qglviewer::Vec, qglviewer::Vec, int);

  bool keyPressEvent(QKeyEvent*);

  void updateScaling();

  PathGrabber* checkIfGrabsMouse(int, int, qglviewer::Camera*);
  void mousePressEvent(QMouseEvent*, qglviewer::Camera*);
  void mouseMoveEvent(QMouseEvent*, qglviewer::Camera*);
  void mouseReleaseEvent(QMouseEvent*, qglviewer::Camera*);

  bool continuousAdd();
  void addPoint(qglviewer::Vec);

  int inViewport(int, int, int, int);
  bool viewportsVisible();
  int viewportGrabbed();
  void resetViewportGrabbed();
  void setViewportGrabbed(int, bool);
  void drawViewportBorders(QGLViewer*);
  bool viewportKeypressEvent(int, QKeyEvent*,
			     QPoint, qglviewer::Vec, int, int);
  void modThickness(bool,
		    int, int,
		    QPoint, qglviewer::Vec, int, int);
  void translate(int, int, int,
		 QPoint, qglviewer::Vec, int, int);
  void rotate(int, int,
		 QPoint, qglviewer::Vec, int, int);

 signals :
  void showMessage(QString, bool);
  void updateGL();

  void showProfile(int, int, QList<qglviewer::Vec>);
  void showThicknessProfile(int, int, QList< QPair<qglviewer::Vec, qglviewer::Vec> >);

  void extractPath(int, bool, int, int);

  void sculpt(int, QList<qglviewer::Vec>, float, float, int);
  void fillPathPatch(QList<qglviewer::Vec>, int, int);
  void paintPathPatch(QList<qglviewer::Vec>, int, int);

  void addToCameraPath(QList<qglviewer::Vec>,QList<qglviewer::Vec>,QList<qglviewer::Vec>,QList<qglviewer::Vec>);

 private slots :
  void selectForEditing(int, int);
  void deselectForEditing();

 private :
  QList<PathGrabber*> m_paths;
  bool m_sameForAll;

  void makePathConnections();
  void processCommand(int, QString);

  void addIndexedPath(QString);

  void loadCaption(int);

  bool openPropertyEditor(int);

  void getRequiredParameters(int,
			     qglviewer::Vec,
			     int, int,
			     int&, int&, int&, int&,
			     int&, int&,
			     int&, float&);
  int getPointPressed(int, qglviewer::Vec,
		      QList<qglviewer::Vec>,
		      QPoint,
		      int, int, int, float);

};


#endif
