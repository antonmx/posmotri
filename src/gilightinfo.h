#ifndef GILIGHTINFO_H
#define GILIGHTINFO_H

#include <QSettings>
#include <QGLViewer/qglviewer.h>
#include "gilightobjectinfo.h"

class GiLightInfo {

public :

  GiLightInfo();
  ~GiLightInfo();

  void clear();

  GiLightInfo &operator=(const GiLightInfo &);
  static GiLightInfo interpolate(const GiLightInfo &, const GiLightInfo &, float);

  void load(QSettings &);
  void save(QSettings &) const;

  QList<GiLightObjectInfo> gloInfo;

  bool basicLight;
  bool applyClip;
  bool applyCrop;
  bool onlyAOLight;
  int lightLod;
  int lightDiffuse;

  qglviewer::Vec aoLightColor;
  int aoRad, aoTimes;
  float aoFrac, aoDensity1, aoDensity2;

  int emisTF;
  float emisDecay;
  float emisBoost;
  int emisTimes;

};

#endif
