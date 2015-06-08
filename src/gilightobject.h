#ifndef GILIGHTOBJECT_H
#define GILIGHTOBJECT_H

#include <QVector4D>

#include <QGLViewer/qglviewer.h>


#include <fstream>
using namespace std;

#include "gilightobjectinfo.h"

class GiLightObjectUndo
{
 public :
  GiLightObjectUndo();
  ~GiLightObjectUndo();
  
  void clear();
  void append(QList<qglviewer::Vec>);

  void undo();
  void redo();

  QList<qglviewer::Vec> points();

 private :
  int m_index;
  QList< QList<qglviewer::Vec> > m_points;

  void clearTop();
};

class GiLightObject
{
 public :
  GiLightObject();
  ~GiLightObject();

  bool lightChanged();
  void setLightChanged(bool);

  bool checkIfNotEqual(GiLightObjectInfo);
  GiLightObjectInfo giLightObjectInfo();
  void setGiLightObjectInfo(GiLightObjectInfo);  

  void set(const GiLightObject&);  
  GiLightObject get();

  GiLightObject& operator=(const GiLightObject&);

  friend bool operator != (const GiLightObject&,
			   const GiLightObject&);

  friend bool operator == (const GiLightObject&,
			   const GiLightObject&);

  static GiLightObject interpolate(GiLightObject,
				GiLightObject,
				float);
  static QList<GiLightObject> interpolate(QList<GiLightObject>,
				       QList<GiLightObject>,
				       float);


  void undo();
  void redo();
  void updateUndo();

  bool showPointNumbers();
  bool showPoints();
  qglviewer::Vec color();
  float opacity();
  int lod();
  int smooth();
  QList<qglviewer::Vec> points();
  QList<qglviewer::Vec> tangents();
  QList<qglviewer::Vec> saxis();
  QList<qglviewer::Vec> taxis();
  QList<qglviewer::Vec> pathPoints();
  QList<qglviewer::Vec> pathT();
  QList<qglviewer::Vec> pathX();
  QList<qglviewer::Vec> pathY();
  int segments();

  void translate(bool, bool);
  void translate(int, int, float);

  qglviewer::Vec getPoint(int);
  void setPoint(int, qglviewer::Vec);

  bool allowInterpolate();
  void setAllowInterpolate(bool);

  void setDoShadows(bool);
  bool doShadows();

  void setShowPointNumbers(bool);
  void setShowPoints(bool);
  void setColor(qglviewer::Vec);
  void setOpacity(float);
  void setLod(int);
  void setSmooth(int);
  void normalize();
  void makePlanar(int, int, int);
  void makePlanar();
  void makeCircle();
  void setPoints(QList<qglviewer::Vec>);
  void setSegments(int);

  void replace(QList<qglviewer::Vec>);

  void computePathLength();

  QList<qglviewer::Vec> getPointPath();
  QList< QPair<qglviewer::Vec, qglviewer::Vec> > getPointAndNormalPath();

  void insertPointAfter(int);
  void insertPointBefore(int);

  void removePoint(int);

  void setPointPressed(int);
  int getPointPressed();

  void draw(QGLViewer*, bool, bool);
  void postdraw(QGLViewer*, int, int, bool, float scale = 0.15);

  void addPoint(qglviewer::Vec);

  void setLightType(int);
  int lightType() { return m_lightType; }

  bool show() { return m_show; }
  void setShow(bool s) { m_show = s; }

  int rad() { return m_rad; }
  float decay() { return m_decay; }
  float angle() { return m_angle; }

  void setRad(int);
  void setDecay(float);
  void setAngle(float);

 private :
  GiLightObjectUndo m_undo;

  bool m_lightChanged;  
  bool m_show;

  bool m_allowInterpolate;
  bool m_showPointNumbers;
  bool m_showPoints;
  bool m_doShadows;
  
  int m_lightType;
  int m_rad;
  float m_decay;
  float m_angle;
  qglviewer::Vec m_color;
  float m_opacity;
  int m_lod, m_smooth;
  QList<qglviewer::Vec> m_points;
  int m_segments;
  float m_length;

  int m_pointPressed;

  bool m_updateFlag;
  QList<qglviewer::Vec> m_tgP;
  QList<qglviewer::Vec> m_xaxis;
  QList<qglviewer::Vec> m_yaxis;
  QList<qglviewer::Vec> m_path;
  QList<qglviewer::Vec> m_pathT;
  QList<qglviewer::Vec> m_pathX;
  QList<qglviewer::Vec> m_pathY;
  
  void computePath(QList<qglviewer::Vec>);
  void computePathVectors();
  void computeLength(QList<qglviewer::Vec>);
  void computeTangents();
  qglviewer::Vec interpolate(int, int, float);

  void drawLines(QGLViewer*, bool, bool);

  QList<qglviewer::Vec> getCrossSection(float,
			     float, float,
			     int,
			     qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);
  QList<qglviewer::Vec> getNormals(QList<qglviewer::Vec>, qglviewer::Vec);

  void postdrawPointNumbers(QGLViewer*);
  void postdrawGrab(QGLViewer*, int, int);
};

#endif
