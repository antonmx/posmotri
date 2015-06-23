#ifndef KEYFRAMEINFORMATION_H
#define KEYFRAMEINFORMATION_H


#include <QObject>
#include <QByteArray>
#include <QGLViewer/qglviewer.h>

#include "camerapathnode.h"
#include "clipinformation.h"
#include "lightinginformation.h"
#include "gilightinfo.h"
#include "brickinformation.h"
#include "splineinformation.h"
#include "captionobject.h"
#include "colorbarobject.h"
#include "scalebarobject.h"
#include "pathobject.h"
#include "gridobject.h"
#include "cropobject.h"
#include "pathgroupobject.h"
#include "trisetinformation.h"
#include "networkinformation.h"

class KeyFrameInformation
{
 public :
  KeyFrameInformation();
  KeyFrameInformation(const KeyFrameInformation&);
  ~KeyFrameInformation();

  KeyFrameInformation& operator=(const KeyFrameInformation&);

  void clear();

  void load( const QConfigMe & cfg);
  void save( QConfigMe & cfg ) const;

  void setDrawBox(bool);
  void setDrawAxis(bool);
  void setBackgroundColor(qglviewer::Vec);
  void setBackgroundImageFile(QString);
  void setFrameNumber(int);
  void setFocusDistance(float, float);
  void setVolumeInterpolation(float);
  void setVolumeNumber(int);
  void setVolumeNumber2(int);
  void setVolumeNumber3(int);
  void setVolumeNumber4(int);
  void setPosition(qglviewer::Vec);
  void setOrientation(qglviewer::Quaternion);
  void setLut(uchar*);
  void setLightInfo(LightingInformation);
  void setGiLightInfo(GiLightInfo);
  void setClipInfo(ClipInformation);
  void setBrickInfo(QList<BrickInformation>);
  void setVolumeBounds(qglviewer::Vec, qglviewer::Vec);
  void setImage(QImage);
  void setTick(int, int, QString, QString, QString);
  void setMix(int, bool, bool, bool);
  void setSplineInfo(QList<SplineInformation>);
  void setMorphTF(bool);
  void setCaptions(QList<CaptionObject>);
  void setColorBars(QList<ColorBarObject>);
  void setScaleBars(QList<ScaleBarObject>);
  void setPoints(QList<qglviewer::Vec>, QList<qglviewer::Vec>, int, qglviewer::Vec);
  void setPaths(QList<PathObject>);
  void setGrids(QList<GridObject>);
  void setCrops(QList<CropObject>);
  void setPathGroups(QList<PathGroupObject>);
  void setTrisets(QList<TrisetInformation>);
  void setNetworks(QList<NetworkInformation>);
  void setTagColors(uchar*);
  void setPruneBuffer(QByteArray);
  void setPruneBlend(bool);

  bool hasCaption(QStringList);
  bool drawBox();
  bool drawAxis();
  QString backgroundImageFile();
  int frameNumber();
  float focusDistance();
  float eyeSeparation();
  int volumeNumber();
  int volumeNumber2();
  int volumeNumber3();
  int volumeNumber4();

  qglviewer::Vec backgroundColor();
  qglviewer::Vec position();
  qglviewer::Quaternion orientation();
  uchar* lut();
  LightingInformation lightInfo();
  GiLightInfo giLightInfo();
  ClipInformation clipInfo();
  QList<BrickInformation> brickInfo();
  void volumeBounds(qglviewer::Vec&, qglviewer::Vec&);
  QImage image();
  void getTick(int&, int&, QString&, QString&, QString&);
  void getMix(int&, bool&, bool&, bool&);
  QList<SplineInformation> splineInfo();
  bool morphTF();
  QList<CaptionObject> captions();
  QList<ColorBarObject> colorbars();
  QList<ScaleBarObject> scalebars();
  QList<qglviewer::Vec> points();
  QList<qglviewer::Vec> barepoints();
  int pointSize();
  qglviewer::Vec pointColor();
  QList<PathObject> paths();
  QList<GridObject> grids();
  QList<CropObject> crops();
  QList<PathGroupObject> pathgroups();
  QList<TrisetInformation> trisets();
  QList<NetworkInformation> networks();
  uchar* tagColors();
  QByteArray pruneBuffer();
  bool pruneBlend();

  // -- keyframe interpolation parameters
  void setInterpBGColor(int);
  void setInterpCaptions(int);
  void setInterpFocus(int);
  void setInterpTagColors(int);
  void setInterpTickInfo(int);
  void setInterpVolumeBounds(int);
  void setInterpCameraPosition(int);
  void setInterpCameraOrientation(int);
  void setInterpBrickInfo(int);
  void setInterpClipInfo(int);
  void setInterpLightInfo(int);
  void setInterpGiLightInfo(int);
  void setInterpTF(int);
  void setInterpCrop(int);
  void setInterpMop(int);

  int interpBGColor();
  int interpCaptions();
  int interpFocus();
  int interpTagColors();
  int interpTickInfo();
  int interpVolumeBounds();
  int interpCameraPosition();
  int interpCameraOrientation();
  int interpBrickInfo();
  int interpClipInfo();
  int interpLightInfo();
  int interpGiLightInfo();
  int interpTF();
  int interpCrop();
  int interpMop();

 private :
  int m_frameNumber;
  float m_focusDistance;
  float m_eyeSeparation;
  int m_volumeNumber;
  int m_volumeNumber2;
  int m_volumeNumber3;
  int m_volumeNumber4;
  qglviewer::Vec m_position;
  qglviewer::Quaternion m_rotation;
  QByteArray m_lut;
  LightingInformation m_lightInfo;
  GiLightInfo m_giLightInfo;
  ClipInformation m_clipInfo;
  QList<BrickInformation> m_brickInfo;
  qglviewer::Vec m_volMin, m_volMax;
  QImage m_image;
  qglviewer::Vec m_backgroundColor;
  QString m_backgroundImageFile;
  bool m_drawBox, m_drawAxis;
  int m_tickSize, m_tickStep;
  QString m_labelX, m_labelY, m_labelZ;
  int m_mixvol;
  bool m_mixColor, m_mixOpacity, m_mixTag;
  QList<SplineInformation> m_splineInfo;
  bool m_morphTF;
  QList<CaptionObject> m_captions;
  QList<ColorBarObject> m_colorbars;
  QList<ScaleBarObject> m_scalebars;
  QList<qglviewer::Vec> m_points;
  QList<qglviewer::Vec> m_barepoints;
  int m_pointSize;
  qglviewer::Vec m_pointColor;
  QList<PathObject> m_paths;
  QList<GridObject> m_grids;
  QList<CropObject> m_crops;
  QList<PathGroupObject> m_pathgroups;
  QList<TrisetInformation> m_trisets;
  QList<NetworkInformation> m_networks;
  QByteArray m_tagColors;
  QByteArray m_pruneBuffer;
  bool m_pruneBlend;

  //-- keyframe interpolation parameters
  int m_interpBGColor;
  int m_interpCaptions;
  int m_interpFocus;
  int m_interpTagColors;
  int m_interpTickInfo;
  int m_interpVolumeBounds;
  int m_interpCameraPosition;
  int m_interpCameraOrientation;
  int m_interpBrickInfo;
  int m_interpClipInfo;
  int m_interpLightInfo;
  int m_interpGiLightInfo;
  int m_interpTF;
  int m_interpCrop;
  int m_interpMop;
};

#endif
