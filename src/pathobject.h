#ifndef PATHOBJECT_H
#define PATHOBJECT_H

#include <QVector4D>
#include <QGLViewer/qglviewer.h>
#include "PromotedWidgets.h"

class PathObjectUndo {
public :
  PathObjectUndo();
  ~PathObjectUndo();
  
  void clear();
  void append(QList<qglviewer::Vec>, QList<float>, QList<float>, QList<float>);

  void undo();
  void redo();

  QList<qglviewer::Vec> points();
  QList<float> pointRadX();
  QList<float> pointRadY();
  QList<float> pointAngle();

private :
  int m_index;
  QList< QList<qglviewer::Vec> > m_points;
  QList< QList<float> > m_pointRadX;
  QList< QList<float> > m_pointRadY;
  QList< QList<float> > m_pointAngle;

  void clearTop();
};

class PathObject {
public :
  PathObject();
  ~PathObject();
  
  void load(const QConfigMe &);
  void save(QConfigMe &) const;

  void set(const PathObject&);  
  PathObject get();

  PathObject& operator=(const PathObject&);

  friend bool operator != (const PathObject&, const PathObject&);

  friend bool operator == (const PathObject&, const PathObject&);

  static PathObject interpolate(PathObject, PathObject, float);
  static QList<PathObject> interpolate(QList<PathObject>, QList<PathObject>, float);

  void undo();
  void redo();
  void updateUndo();

  bool hasCaption(QStringList);

  QString captionText();
  QFont captionFont();
  QColor captionColor();
  QColor captionHaloColor();

  bool captionGrabbed();
  void setCaptionGrabbed(bool);
  void setCaptionLabel(bool);
  bool captionLabel();
  bool captionPresent();

  void imageSize(int&, int&);

  void resetCaption();
  void setCaption(QString, QFont, QColor, QColor);

  QString imageName();
  void setImage(QString);

  void resetImage();
  void loadImage();

  int useType();
  void setUseType(int);
  bool crop();
  bool keepInside();
  void setKeepInside(bool);
  bool keepEnds();
  void setKeepEnds(bool);
  bool blend();
  int blendTF();
  void setBlendTF(int);

  bool showPointNumbers();
  bool showPoints();
  bool showLength();
  bool showAngle();
  int capType();
  bool arrowDirection();
  bool arrowForAll();
  bool halfSection();
  bool tube();
  bool closed();
  qglviewer::Vec color();
  qglviewer::Vec lengthColor();
  float opacity();
  float arrowHeadLength();
  int lengthTextDistance();
  QList<qglviewer::Vec> points();
  QList<qglviewer::Vec> tangents();
  QList<qglviewer::Vec> saxis();
  QList<qglviewer::Vec> taxis();
  QList<float> radX();
  QList<float> radY();
  QList<float> angle();
  QList<qglviewer::Vec> pathPoints();
  QList<qglviewer::Vec> pathT();
  QList<qglviewer::Vec> pathX();
  QList<qglviewer::Vec> pathY();
  QList<float> pathradX();
  QList<float> pathradY();
  QList<float> pathAngles();
  int segments();
  int sections();
  float length();

  void translate(bool, bool);
  void translate(int, int, float);

  void rotate(int, float);

  qglviewer::Vec getPoint(int);
  void setPoint(int, qglviewer::Vec);

  float getRadX(int);
  void setRadX(int, float, bool);

  float getRadY(int);
  void setRadY(int, float, bool);

  float getAngle(int);
  void setAngle(int, float, bool);

  bool allowInterpolate();
  void setAllowInterpolate(bool);

  void setSameForAll(bool);

  void setShowPointNumbers(bool);
  void setShowPoints(bool);
  void setShowLength(bool);
  void setShowAngle(bool);
  void setCapType(int);
  void setArrowDirection(bool);
  void setArrowForAll(bool);
  void setHalfSection(bool);
  void setTube(bool);
  void setClosed(bool);
  void setColor(qglviewer::Vec);
  void setLengthColor(qglviewer::Vec);
  void setOpacity(float);
  void setArrowHeadLength(float);
  void setLengthTextDistance(int);
  void normalize();
  void makePlanar(int, int, int);
  void makePlanar();
  void makeCircle();
  void setPoints(QList<qglviewer::Vec>);
  void setRadX(QList<float>);
  void setRadY(QList<float>);
  void setAngle(QList<float>);
  void setSegments(int);
  void setSections(int);
  void flip();

  void replace(QList<qglviewer::Vec>, QList<float>, QList<float>, QList<float>);

  void computePathLength();

  QList<qglviewer::Vec> getPointPath();
  QList< QPair<qglviewer::Vec, qglviewer::Vec> > getPointAndNormalPath();

  void insertPointAfter(int);
  void insertPointBefore(int);

  void removePoint(int);

  void setPointPressed(int);
  int getPointPressed();

  void draw(QGLViewer*, bool, bool, qglviewer::Vec);
  void postdraw(QGLViewer*, int, int, bool, float scale = 0.15);

  void postdrawInViewport(QGLViewer*, int, int, bool,
			  qglviewer::Vec, qglviewer::Vec, int, float);

  void drawViewportLine(float, int);
  void drawViewportLineDots(QGLViewer*, float, int);

  bool checkCropped(qglviewer::Vec);
  float checkBlend(qglviewer::Vec);

  void setAdd(bool);
  bool add();
  void addPoint(qglviewer::Vec);

  bool viewportGrabbed();
  void setViewportGrabbed(bool);

  int viewportTF();
  void setViewportTF(int);

  QVector4D viewport();
  void setViewport(QVector4D);

  void setViewportCamPos(qglviewer::Vec);
  qglviewer::Vec viewportCamPos();

  void setViewportCamRot(float);
  float viewportCamRot();

  void setViewportStyle(bool);
  bool viewportStyle();

  enum CapType
  {
    FLAT,
    ROUND,
    ARROW
  };

 private :
  PathObjectUndo m_undo;

  int m_useType;
  bool m_keepInside;
  bool m_keepEnds;
  int m_blendTF;

  bool m_add;
  bool m_allowInterpolate;
  bool m_showPointNumbers;
  bool m_showPoints;
  bool m_showLength;
  bool m_showAngle;
  int m_capType;
  bool m_arrowDirection;
  bool m_arrowForAll;
  bool m_halfSection;
  bool m_tube;
  bool m_closed;
  qglviewer::Vec m_color;
  qglviewer::Vec m_lengthColor;
  float m_opacity;
  float m_arrowHeadLength;
  int m_lengthTextDistance;
  QList<qglviewer::Vec> m_points;
  QList<float> m_pointRadX;
  QList<float> m_pointRadY;
  QList<float> m_pointAngle;
  int m_segments;
  int m_sections;
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
  QList<float> m_radX;
  QList<float> m_radY;
  QList<float> m_angle;
  GLuint m_displayList;
  GLuint m_displayListCaption;
  
  GLuint m_imageTex;
  bool m_imagePresent;
  QString m_imageName;

  QImage m_cImage;
  QImage m_image;

  bool m_captionGrabbed;
  bool m_captionPresent;
  bool m_captionLabel;
  QString m_captionText;
  QFont m_captionFont;
  QColor m_captionColor;
  QColor m_captionHaloColor;

  int m_textureHeight;
  int m_textureWidth;

  float m_glutTextScale;

  bool m_viewportStyle;
  int m_viewportTF;
  QVector4D m_viewport;
  bool m_viewportGrabbed;
  qglviewer::Vec m_viewportCamPos;
  float m_viewportCamRot;

  void loadImage(QString);

  void loadCaption(QString, QFont, QColor, QColor);

  void computePath(QList<qglviewer::Vec>);
  void computePathVectors();
  void computeLength(QList<qglviewer::Vec>);
  void computeTangents();
  qglviewer::Vec interpolate(int, int, float);
  void generateTube(float);
  void generateRibbon(float);

  void addFlatCaps(int, qglviewer::Vec, QList<qglviewer::Vec>);
  void addRoundCaps(int, qglviewer::Vec, QList<qglviewer::Vec>, QList<qglviewer::Vec>);

  void drawTube(QGLViewer*, bool, qglviewer::Vec);
  void drawLines(QGLViewer*, bool, bool);

  QList<qglviewer::Vec> getCrossSection(float,
			     float, float,
			     int,
			     qglviewer::Vec, qglviewer::Vec, qglviewer::Vec);
  QList<qglviewer::Vec> getNormals(QList<qglviewer::Vec>, qglviewer::Vec);

  void addArrowHead(int, float,
		    qglviewer::Vec,
		    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
		    float, float,
		    QList<qglviewer::Vec>,
		    QList<qglviewer::Vec>);

  void postdrawCaption(QGLViewer*);
  void postdrawPointNumbers(QGLViewer*);
  void postdrawGrab(QGLViewer*, int, int);
  void postdrawLength(QGLViewer*);
  void postdrawAngle(QGLViewer*);
};

#endif
