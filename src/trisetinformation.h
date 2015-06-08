#ifndef TRISETINFORMATION_H
#define TRISETINFORMATION_H

#include <QGLViewer/qglviewer.h>
#include "PromotedWidgets.h"

class TrisetInformation {
public :
  TrisetInformation();
  TrisetInformation& operator=(const TrisetInformation&);

  static TrisetInformation interpolate(const TrisetInformation &, const TrisetInformation &,  float);
  static QList<TrisetInformation> interpolate(const QList<TrisetInformation> &, const QList<TrisetInformation> &, float);

  void clear();
  void load(const QConfigMe &);
  void save(QConfigMe &) const;
  
  QString filename;
  qglviewer::Vec position;
  qglviewer::Vec scale;
  qglviewer::Vec color;
  qglviewer::Vec cropcolor;
  float opacity;
  float ambient;
  float diffuse;
  float specular;
  bool pointMode;
  int pointStep;
  int pointSize;
  bool blendMode;
  bool shadows;
  bool screenDoor;
  bool flipNormals;
};

#endif
