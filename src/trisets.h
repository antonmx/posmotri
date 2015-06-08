#ifndef TRISETS_H
#define TRISETS_H

//#include <QtGui>


#include "trisetgrabber.h"
#include "cropobject.h"

class Trisets : public QObject
{
  Q_OBJECT

 public :
  Trisets();
  ~Trisets();

  int count() { return m_trisets.count(); }

  void allEnclosingBox(qglviewer::Vec&, qglviewer::Vec&);
  void allGridSize(int&, int&, int&);

  bool isInMouseGrabberPool(int);
  void addInMouseGrabberPool();
  void addInMouseGrabberPool(int);
  void removeFromMouseGrabberPool();
  void removeFromMouseGrabberPool(int);

  bool grabsMouse();

  void clear();

  void addTriset(QString);
  void addPLY(QString);

  void predraw(QGLViewer*,
	       double*,
	       qglviewer::Vec,
	       bool, int, int);
  void draw(QGLViewer*, qglviewer::Vec,
	    float, float, qglviewer::Vec,
	    bool, bool, qglviewer::Vec,
	    QList<qglviewer::Vec>, QList<qglviewer::Vec>,
	    bool);
  void postdraw(QGLViewer*);

  bool keyPressEvent(QKeyEvent*);

  void createDefaultShader(QList<CropObject>);
  void createHighQualityShader(bool, float, QList<CropObject>);
  void createShadowShader(qglviewer::Vec, QList<CropObject>);

  QList<TrisetInformation> get();
  void set(QList<TrisetInformation>);

  void load(const char*);
  void save(const char*);

  void makeReadyForPainting(QGLViewer*);
  void releaseFromPainting();
  void paint(QGLViewer*, QBitArray, float*, qglviewer::Vec, float);

 signals :
  void updateGL();

 private :
  QList<TrisetGrabber*> m_trisets;

  void processCommand(int, QString);

  GLhandleARB m_geoShadowShader;
  GLhandleARB m_geoHighQualityShader;
  GLhandleARB m_geoDefaultShader;

  GLint m_highqualityParm[15];
  GLint m_defaultParm[15];
  GLint m_shadowParm[15];

  float *m_cpos;
  float *m_cnormal;
};


#endif
