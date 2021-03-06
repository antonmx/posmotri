#ifndef PATHGROUPOBJECT_H
#define PATHGROUPOBJECT_H

#include <QGLViewer/qglviewer.h>
#include "cropobject.h"

class PathGroupObjectUndo {
public :
  PathGroupObjectUndo();
  ~PathGroupObjectUndo();
  
  void clear();
  void append(QList<int>, QList<qglviewer::Vec>, QList<float>, QList<float>, QList<float>);

  void undo();
  void redo();

  QList<int> index();
  QList<qglviewer::Vec> points();
  QList<float> pointRadX();
  QList<float> pointRadY();
  QList<float> pointAngle();

 private :
  int m_index;
  QList< QList<int> > m_pindex;
  QList< QList<qglviewer::Vec> > m_points;
  QList< QList<float> > m_pointRadX;
  QList< QList<float> > m_pointRadY;
  QList< QList<float> > m_pointAngle;

  void clearTop();
};


class PathGroupObject {
public :
  PathGroupObject();
  ~PathGroupObject();
  
  void load(const QConfigMe &);
  void save(QConfigMe &) const;
  
  void set(const PathGroupObject&);  
  PathGroupObject get();
  
  PathGroupObject& operator=(const PathGroupObject&);

  static PathGroupObject interpolate(PathGroupObject, PathGroupObject, float);
  static QList<PathGroupObject> interpolate(QList<PathGroupObject>, QList<PathGroupObject>, float);

  void undo();
  void redo();
  void updateUndo();

  bool captionGrabbed();
  void setCaptionGrabbed(bool);
  QFont captionFont();
  QColor captionColor();
  QColor captionHaloColor();
  QList<qglviewer::Vec> imageSizes();
  void loadCaption();

  bool depthcue();
  bool showPoints();
  bool showLength();
  int capType();
  bool arrowDirection();
  bool arrowForAll();
  bool tube();
  bool closed();
  QGradientStops stops();
  float opacity();
  QList<qglviewer::Vec> points();
  QList<qglviewer::Vec> pathPoints();
  QList<int> pathPointIndices();
  QVector<bool> valid();
  QList<float> radX();
  QList<float> radY();
  QList<float> angle();
  int segments();
  int sections();
  int sparseness();
  int separation();
  bool animate();
  int animateSpeed();
  float length();

  qglviewer::Vec getPoint(int);
  void setPoint(int, qglviewer::Vec);

  float getRadX(int);
  void setRadX(int, float, bool);

  float getRadY(int);
  void setRadY(int, float, bool);

  float getAngle(int);
  void setAngle(int, float, bool);

  void setSameForAll(bool);

  bool clip();
  void setClip(bool);

  bool allowEditing();
  void setAllowEditing(bool);

  bool blendMode();
  void setBlendMode(bool);

  bool allowInterpolate();
  void setAllowInterpolate(bool);

  void setDepthcue(bool);
  void setShowPoints(bool);
  void setShowLength(bool);
  void setCapType(int);
  void setArrowDirection(bool);
  void setArrowForAll(bool);
  void setTube(bool);
  void setClosed(bool);
  void setStops(const QGradientStops &);
  void setOpacity(float);
  void normalize();
  void setVectorPoints(QList<qglviewer::Vec>);
  void setPoints(QList<qglviewer::Vec>);
  void replacePoints(QList<qglviewer::Vec>);
  void addPoints(QList<qglviewer::Vec>);
  void setRadX(QList<float>);
  void setRadY(QList<float>);
  void setAngle(QList<float>);
  void setSegments(int);
  void setSparseness(int);
  void setSeparation(int);
  void setAnimate(bool);
  void setAnimateSpeed(int);
  void setSections(int);

  void pathlenMinmax(float&, float&);
  void userPathlenMinmax(float&, float&);
  void setUserPathlenMinmax(float, float);

  bool filterPathLen();
  void setFilterPathLen(bool);

  void setGrabsIndex(int);

  void computePathLength();

  void setPointPressed(int);
  int getPointPressed();

  void predraw(QGLViewer*, bool, bool,
	       QList<qglviewer::Vec>,
	       QList<qglviewer::Vec>,
	       QList<CropObject> crops);
  void draw(QGLViewer*, bool, bool, qglviewer::Vec);
  void postdraw(QGLViewer*, int, int, bool);

  void disableUndo(bool);

  void setMinScale(float);
  float minScale();

  void setMaxScale(float);
  float maxScale();

  void setScaleType(bool);
  bool scaleType();

  enum CapType  {
    FLAT,
    ROUND,
    ARROW
  };

 private :
  PathGroupObjectUndo m_undo;

  bool m_scaleType;
  float m_minScale, m_maxScale;
  int m_indexGrabbed;
  bool m_depthcue;
  bool m_filterPathLen;
  bool m_showPoints;
  bool m_showLength;
  int m_capType;
  bool m_arrowDirection;
  bool m_arrowForAll;
  bool m_tube;
  bool m_closed;
  qglviewer::Vec m_pointColor;
  QGradientStops m_stops;
  QGradientStops m_resampledStops;
  float m_opacity;
  bool m_clip;
  bool m_allowEditing;
  bool m_blendMode;
  bool m_allowInterpolate;
  QList<int> m_index;
  QList<qglviewer::Vec> m_points;
  QList<float> m_pointRadX;
  QList<float> m_pointRadY;
  QList<float> m_pointAngle;
  int m_segments;
  int m_sections;
  int m_sparseness;
  int m_separation;
  float m_length;
  bool m_animate;
  int m_animateSpeed;
  int m_astep;

  int m_pointPressed;

  bool m_updateFlag;
  QVector<bool> m_validPoint;
  QVector<bool> m_valid;
  QVector<qglviewer::Vec> m_tgP;
  QList<int> m_pathIndex;
  QList<qglviewer::Vec> m_path;
  QList<float> m_radX;
  QList<float> m_radY;
  QList<float> m_angle;
  GLuint m_displayList;

  QList<float> m_pathLength;
  float m_minPathLen, m_maxPathLen;
  float m_minUserPathLen, m_maxUserPathLen;

  bool m_captionGrabbed;
  QFont m_captionFont;
  QColor m_captionColor;
  QColor m_captionHaloColor;
  QList<QImage> m_cImage;
  
  bool m_disableUndo;

  GLuint m_spriteTexture;

  static int m_animationstep;
  float m_minDepth, m_maxDepth;

  void setCaption(QFont, QColor, QColor);
  void generateImages();
  void drawImage(QGLViewer*, int, qglviewer::Vec, qglviewer::Vec);

  float computeGrabbedPathLength();
  void computePath();
  float computeLength(QList<qglviewer::Vec>);
  void computeTangents(int, int);
  qglviewer::Vec interpolate(int, int, float);
  void generateTube(QGLViewer*, float);

  void addFlatCaps(int, qglviewer::Vec, QList<qglviewer::Vec>);
  void addRoundCaps(int, qglviewer::Vec, QList<qglviewer::Vec>, QList<qglviewer::Vec>);

  void drawPoints();
  void drawTube(QGLViewer*, bool, qglviewer::Vec);
  void drawLines(QGLViewer*, bool, bool);
  void drawSphereSprites(QGLViewer*, bool, bool);

  void generateSphereSprite();

  QList<qglviewer::Vec> getCrossSection(float,
			     float, float, float,
			     int,
			     qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
			     qglviewer::Vec, qglviewer::Vec&, qglviewer::Vec&);
  QList<qglviewer::Vec> getNormals(QList<qglviewer::Vec>, qglviewer::Vec);

  void addArrowHead(int, float,
		    qglviewer::Vec,
		    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
		    float, float, qglviewer::Vec,
		    QList<qglviewer::Vec>,
		    QList<qglviewer::Vec>);

};

#endif
