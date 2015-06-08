#ifndef CROPOBJECT_H
#define CROPOBJECT_H

#include <QGLViewer/qglviewer.h>
#include "PromotedWidgets.h"

class CropObjectUndo
{
 public :
  CropObjectUndo();
  ~CropObjectUndo();
  
  void clear();
  void append(QList<qglviewer::Vec>, QList<float>, QList<float>);

  void undo();
  void redo();

  QList<qglviewer::Vec> points();
  QList<float> pointRadX();
  QList<float> pointRadY();

 private :
  int m_index;
  QList< QList<qglviewer::Vec> > m_points;
  QList< QList<float> > m_pointRadX;
  QList< QList<float> > m_pointRadY;

  void clearTop();
};

class CropObject {
public :
  
  enum CropType  {
    Crop_Tube = 0,
    Crop_Box,
    Crop_Ellipsoid,
    Tear_Tear,
    Tear_Hole,
    Tear_Wedge,
    Tear_Curl,
    Displace_Displace,
    View_Tear,
    View_Tube,
    View_Ball,
    View_Block,
    Glow_Ball,
    Glow_Block,
    Glow_Tube
  };

  CropObject();
  ~CropObject();
  
  void undo();
  void redo();
  void updateUndo();

  bool show() { return m_show; }
  void setShow(bool s) { m_show = s; }

  void load(const QConfigMe &);
  void save(QConfigMe &) const;

  void set(const CropObject&);  
  CropObject get();

  CropObject& operator=(const CropObject&);

  static CropObject interpolate(const CropObject,
				const CropObject,
				float);

  static QList<CropObject> interpolate(const QList<CropObject>,
				       const QList<CropObject>,
				       float);
  void flipPoints();

  bool clearView();
  float magnify();
  bool showPoints();
  bool halfSection();
  bool keepInside();
  bool keepEnds();
  int cropType();
  bool tube();
  qglviewer::Vec color();
  float opacity();
  int tfset();
  float viewMix();
  bool unionBlend();
  qglviewer::Vec dtranslate();
  qglviewer::Vec dpivot();
  qglviewer::Vec drotaxis();
  float drotangle();
  QList<qglviewer::Vec> points();
  QList<float> radX();
  QList<float> radY();
  QList<int> lift();
  float angle();
  qglviewer::Vec m_tang, m_xaxis, m_yaxis;
  float length();
  bool hatch();
  void hatchParameters(bool&, int&, int&, int&, int&, int&, int&);

  void shiftPoints(float);

  void translate(qglviewer::Vec);
  void translate(bool, bool);

  qglviewer::Vec getPoint(int);
  void setPoint(int, qglviewer::Vec);

  float getRadX(int);
  void setRadX(int, float, bool);

  float getRadY(int);
  void setRadY(int, float, bool);

  int getLift(int);
  void setLift(int, int, bool);

  float getAngle();
  void setAngle(float);
  void rotate(qglviewer::Vec, float);

  void setSameForAll(bool);

  void setClearView(bool);
  void setMagnify(float);
  void setShowPoints(bool);
  void setHalfSection(bool);
  void setKeepInside(bool);
  void setKeepEnds(bool);
  void setCropType(int);
  void setTube(bool);
  void setColor(qglviewer::Vec);
  void setOpacity(float);
  void setTFset(int);
  void setViewMix(float);
  void setUnionBlend(bool);
  void setDtranslate(qglviewer::Vec);
  void setDpivot(qglviewer::Vec);
  void setDrotaxis(qglviewer::Vec);
  void setDrotangle(float);
  void normalize();
  void setPoints(QList<qglviewer::Vec>);
  void setRadX(QList<float>);
  void setRadY(QList<float>);
  void setLift(QList<int>);
  void setHatch(bool);
  void setHatchParameters(bool, int, int, int, int, int, int);

  void computeCropLength();

  QList<qglviewer::Vec> getPointCrop();

  void setPointPressed(int);
  int getPointPressed();

  void draw(QGLViewer*, bool, bool);
  void postdraw(QGLViewer*, int, int, bool);
  
  friend bool operator != (const CropObject&,
			   const CropObject&);

  friend bool operator == (const CropObject&,
			   const CropObject&);


  enum MoveAxis
  {
    MoveX0,
    MoveX1,
    MoveY0,
    MoveY1,
    MoveZ,
    MoveAll
  };

  int moveAxis();
  void setMoveAxis(int);

  bool checkCropped(qglviewer::Vec);
  float checkBlend(qglviewer::Vec);
  float checkTear(qglviewer::Vec, qglviewer::Vec&);

 private :
  CropObjectUndo m_undo;

  int m_moveAxis;
  bool m_show;
  int m_cropType;
  bool m_keepInside;
  bool m_keepEnds;
  bool m_clearView;
  float m_magnify;
  bool m_showPoints;
  bool m_halfSection;
  bool m_tube;
  qglviewer::Vec m_color;
  float m_opacity;
  int m_tfset;
  float m_viewMix;
  bool m_unionBlend;
  qglviewer::Vec m_dtranslate;
  qglviewer::Vec m_dpivot;
  qglviewer::Vec m_drotaxis;
  float m_drotangle;
  QList<qglviewer::Vec> m_points;
  QList<float> m_pointRadX;
  QList<float> m_pointRadY;
  float m_pointAngle;
  float m_length;
  qglviewer::Vec m_oxaxis;
  bool m_hatch, m_hatchGrid;
  int m_hxn, m_hxd, m_hyn, m_hyd, m_hzn, m_hzd;

  int m_pointPressed;

  bool m_updateFlag;
  QList<qglviewer::Vec> m_tgP;
  QList<qglviewer::Vec> m_crop;
  QList<float> m_radX;
  QList<float> m_radY;
  QList<int> m_lift;
  
  void computeCrop(QList<qglviewer::Vec>);
  void computeLength(QList<qglviewer::Vec>);
  void computeTangents();
  qglviewer::Vec interpolate(int, int, float);
  void generateTube(float);

  void drawTube(QGLViewer*, bool);
  void drawLines(QGLViewer*, bool, bool);

  QList<qglviewer::Vec> getCrossSection(float,
			     float, float,
			     qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
			     int sections = 20);
  QList<qglviewer::Vec> getNormals(QList<qglviewer::Vec>, qglviewer::Vec);

  bool hatched(float, float, float,
	       bool, bool,
	       int, int, int, int, int, int);
};

#endif
