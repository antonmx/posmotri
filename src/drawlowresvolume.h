#ifndef DRAWLOWRESVOLUME_H
#define DRAWLOWRESVOLUME_H

#include <QGLViewer/qglviewer.h>
#include "boundingbox.h"
#include "PromotedWidgets.h"

class Viewer;
class Volume;

class DrawLowresVolume : public QObject
{
  Q_OBJECT

 public :
  DrawLowresVolume(Viewer*, Volume*);
  ~DrawLowresVolume();

  bool raised();
  void raise();
  void lower();
  void activateBounds();
  void init();
  void load3dTexture();
  void loadVolume();
  QImage histogramImage1D();
  QImage histogramImage2D();
  int* histogram2D();

  qglviewer::Vec volumeSize();
  qglviewer::Vec volumeMin();
  qglviewer::Vec volumeMax();

  void subvolumeBounds(qglviewer::Vec&, qglviewer::Vec&);

  bool keyPressEvent(QKeyEvent*);
  
  void load(const QConfigMe &);
  void save(QConfigMe &) const;
  void load(const QString &);
  void save(const QString &) const;

  void setCurrentVolume(int vnum=0);

 public slots :
  void setSubvolumeBounds(qglviewer::Vec, qglviewer::Vec);

  void createShaders();

  void updateScaling();

  void draw(float, int, int);

  void generateHistogramImage();

  void switchInterpolation();


 private :
  bool showing;

  int m_currentVolume;

  Viewer *m_Viewer;
  Volume *m_Volume;

  unsigned char *m_histImageData1D;
  unsigned char *m_histImageData2D;
  QImage m_histogramImage1D;
  QImage m_histogramImage2D;

  qglviewer::Vec m_dataMin, m_dataMax;
  qglviewer::Vec m_virtualTextureSize;
  qglviewer::Vec m_virtualTextureMin;
  qglviewer::Vec m_virtualTextureMax;

  GLuint m_dataTex;
  GLhandleARB m_fragObj, m_progObj;
  GLint m_parm[20];

  BoundingBox m_boundingBox;

  int drawpoly(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec*, qglviewer::Vec, qglviewer::Vec);
  void drawSlices(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, int, float);

  void enableTextureUnits();
  void disableTextureUnits();
};

#endif
