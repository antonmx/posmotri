#ifndef NETWORKS_H
#define NETWORKS_H

//#include <QtGui>


#include "networkgrabber.h"

class Networks : public QObject
{
  Q_OBJECT

 public :
  Networks();
  ~Networks();

  int count() { return m_networks.count(); }

  bool show(int);
  void setShow(int, bool);
  void show();
  void hide();

  void allEnclosingBox(qglviewer::Vec&, qglviewer::Vec&);
  void allGridSize(int&, int&, int&);

  bool isInMouseGrabberPool(int);
  void addInMouseGrabberPool();
  void addInMouseGrabberPool(int);
  void removeFromMouseGrabberPool();
  void removeFromMouseGrabberPool(int);

  bool grabsMouse();

  void clear();

  void addNetwork(QString);

  void predraw(QGLViewer*,
	       double*,
	       qglviewer::Vec,
	       QList<qglviewer::Vec>, QList<qglviewer::Vec>,
	       QList<CropObject>,
	       qglviewer::Vec);
  void draw(QGLViewer*,
	    float, float,
	    bool);
  void postdraw(QGLViewer*);

  bool keyPressEvent(QKeyEvent*);

  void createSpriteShader();
  void createShadowShader(qglviewer::Vec);

  QList<NetworkInformation> get();
  void set(QList<NetworkInformation>);

  void load(const char*);
  void save(const char*);

 signals :
  void updateGL();

 private :
  QList<NetworkGrabber*> m_networks;

  GLhandleARB m_geoShadowShader;
  GLhandleARB m_geoSpriteShader;

  GLint m_spriteParm[20];
  GLint m_shadowParm[20];

  bool processCommand(int, QString);
};


#endif
