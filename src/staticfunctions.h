#ifndef STATICFUNCTIONS_H
#define STATICFUNCTIONS_H

#include <QGLViewer/qglviewer.h>


#include "classes.h"

#define DEG2RAD(angle) angle*3.1415926535897931/180.0
#define RAD2DEG(angle) angle*180.0/3.1415926535897931

inline qglviewer::Vec vMv(const qglviewer::Vec & a, const qglviewer::Vec & b) {
  return qglviewer::Vec(a.x*b.x, a.y*b.y, a.z*b.z);
}

inline qglviewer::Vec vDv(const qglviewer::Vec & a, const qglviewer::Vec & b) {
  return qglviewer::Vec( b.x==0 ? 1 : a.x/b.x, b.y==0 ? 1 : a.y/b.y, b.z==0 ? 1 :  a.z/b.z);
}

class StaticFunctions
{
 public :
  static qglviewer::Vec getVec(QString);

  static int getPowerOf2(int);

  static qglviewer::Vec interpolate(qglviewer::Vec, qglviewer::Vec, float);

  static qglviewer::Vec clampVec(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);
  static qglviewer::Vec maxVec(qglviewer::Vec, qglviewer::Vec);
  static qglviewer::Vec minVec(qglviewer::Vec, qglviewer::Vec);

  static int getSubsamplingLevel(int, int, qglviewer::Vec, qglviewer::Vec);

  static void getRotationBetweenVectors(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec&, float&);

  static QGradientStops resampleGradientStops(QGradientStops, int mapSize = 100);
  static void initQColorDialog();

  static void drawEnclosingCube(qglviewer::Vec*, qglviewer::Vec);
  static void drawEnclosingCube(qglviewer::Vec, qglviewer::Vec);
  static void drawEnclosingCubeWithTransformation(qglviewer::Vec, qglviewer::Vec,
						  double*,
						  qglviewer::Vec);

  static void drawAxis(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);

  static int intersectType1(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec&);
  static int intersectType1WithTexture(qglviewer::Vec, qglviewer::Vec,
				       qglviewer::Vec, qglviewer::Vec,
				       qglviewer::Vec, qglviewer::Vec,
				       qglviewer::Vec&, qglviewer::Vec&);

  static int intersectType2(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec&, qglviewer::Vec&);
  static int intersectType2WithTexture(qglviewer::Vec, qglviewer::Vec,
				       qglviewer::Vec&, qglviewer::Vec&,
				       qglviewer::Vec&, qglviewer::Vec&);

  static int intersectType3WithTexture(qglviewer::Vec, qglviewer::Vec,
				       qglviewer::Vec&, qglviewer::Vec&,
				       qglviewer::Vec&, qglviewer::Vec&,
				       qglviewer::Vec&, qglviewer::Vec&);

  static void getMinMaxBrickVertices(qglviewer::Camera*,
				     qglviewer::Vec, qglviewer::Vec,
				     float&,
				     qglviewer::Vec&, qglviewer::Vec&,
				     int&);
  static void getMinMaxProjectionVertices(qglviewer::Camera*,
					  qglviewer::Vec*,
					  float&, qglviewer::Vec&, qglviewer::Vec&, int&);

  static int getScaledown(int, int);

  static void pushOrthoView(float, float, float, float);
  static void popOrthoView();
  static void drawQuad(float, float, float, float, float);

  static bool checkExtension(QString, const char*);
  static bool checkURLs(QList<QUrl>, const char*);

  static float calculateAngle(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);

  static QList<qglviewer::Vec> voxelizeLine(qglviewer::Vec, qglviewer::Vec);
  static VoxelizedPath voxelizePath(QList<qglviewer::Vec>);
  static VoxelizedPath voxelizePath(QList< QPair<qglviewer::Vec, qglviewer::Vec> >);

  static void generateHistograms(float*, float*, int*, int*);

  static bool getClip(qglviewer::Vec, QList<qglviewer::Vec>, QList<qglviewer::Vec>);

  static QSize getImageSize(int, int);

  static float remapKeyframe(int, float);
  static float easeIn(float);
  static float easeOut(float);
  static float smoothstep(float);
  static float smoothstep(float, float, float);


  static QVector<qglviewer::Vec> generateUnitSphere(int);

  static bool inTriangle(qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);

  static QString replaceDirectory(QString, QString);

  static void convertFromGLImage(QImage&, int, int);

  static void savePvlHeader(QString,
			    bool, QString,
			    int, int, int,
			    int, int, int,
			    float, float, float,
			    QList<float>, QList<int>,
			    QString,
			    int);
};

#endif
