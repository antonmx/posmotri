#ifndef GILIGHTOBJECTINFO_H
#define GILIGHTOBJECTINFO_H

#include "PromotedWidgets.h"
#include <QGLViewer/qglviewer.h>

class GiLightObjectInfo {
public :
  GiLightObjectInfo();
  ~GiLightObjectInfo();

  void clear();

  GiLightObjectInfo& operator=(const GiLightObjectInfo&);

  static QList<GiLightObjectInfo> interpolate(
    QList<GiLightObjectInfo>, QList<GiLightObjectInfo>, float);

  void load(const QConfigMe &);
  void save(QConfigMe &) const;

  QList<qglviewer::Vec> points;
  bool allowInterpolation;
  bool doShadows;
  bool show;
  int lightType;
  int rad;
  float decay;
  float angle;
  qglviewer::Vec color;
  float opacity;
  int segments;
  int lod;
  int smooth;

 private :
  static GiLightObjectInfo interpolate(GiLightObjectInfo,
				       GiLightObjectInfo,
				       float);
};

#endif
