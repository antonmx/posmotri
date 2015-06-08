#ifndef CLIPINFORMATION_H
#define CLIPINFORMATION_H



#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>
# include "PromotedWidgets.h"



#include <fstream>
using namespace std;

class ClipInformation
{
 public :
  ClipInformation();
  ~ClipInformation();
  ClipInformation(const ClipInformation&);

  ClipInformation& operator=(const ClipInformation&);

  static ClipInformation interpolate(const ClipInformation,
				     const ClipInformation,
				     float);

  void load(const QConfigMe  &cfg);
  void save(QConfigMe  &cfg) const;

  void clear();
  int size();

  QList<bool> show;
  QList<qglviewer::Vec> pos;
  QList<qglviewer::Quaternion> rot;
  QList<qglviewer::Vec> color;
  QList<bool> solidColor;
  QList<bool> apply;
  QList<bool> applyFlip;
  QList<QString> imageName;
  QList<int> imageFrame;
  QList<QString> captionText;
  QList<QFont> captionFont;
  QList<QColor> captionColor;
  QList<QColor> captionHaloColor;
  QList<float> opacity;
  QList<float> stereo;
  QList<float> scale1;
  QList<float> scale2;
  QList<int> tfSet;
  QList<QVector4D> viewport;
  QList<bool> viewportType;
  QList<float> viewportScale;
  QList<int> thickness;
  QList<bool> showSlice;
  QList<bool> showOtherSlice;
  QList<bool> showThickness;
  QList<int> gridX;
  QList<int> gridY;
};

#endif
