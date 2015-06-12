#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "keyframeinformation.h"
#include "ui_interpolation.h"

class KeyFrame : public QObject
{
  Q_OBJECT

 public :
  KeyFrame();
  ~KeyFrame();

  void clear();

  void import(const QString &);
  void load(const QConfigMe  &cfg);
  void save(QConfigMe  &cfg) const;

  void draw(float);

  KeyFrameInformation interpolate(int);

  KeyFrameInformation keyFrameInfo(int);

  int searchCaption(QStringList);

  void saveProject(qglviewer::Vec, qglviewer::Quaternion,
       float, float,
       int, int, int, int,
       unsigned char*,
       LightingInformation,
       QList<BrickInformation>,
       qglviewer::Vec, qglviewer::Vec,
       QImage,
       int, int, QString, QString, QString,
       int, bool, bool, bool,
       QByteArray);

  void setKeyFrame(qglviewer::Vec, qglviewer::Quaternion,
       float, float,
       int, unsigned char*,
       LightingInformation,
       QList<BrickInformation>,
       qglviewer::Vec, qglviewer::Vec,
       QImage,
       QList<SplineInformation>,
       int, int, QString, QString, QString,
       int, bool, bool, bool);

  void interpolateAt(int, float,
         qglviewer::Vec&, qglviewer::Quaternion&,
         KeyFrameInformation&,
         float&);

  int numberOfKeyFrames();

 public slots :
  void playFrameNumber(int);
  void updateKeyFrameInterpolator();
  void removeKeyFrame(int);
  void removeKeyFrames(int, int);
  void setKeyFrameNumber(int, int);
  void setKeyFrameNumbers(QList<int>);
  void reorder(QList<int>);
  void copyFrame(int);
  void pasteFrame(int);
  void pasteFrameOnTop(int);
  void pasteFrameOnTop(int, int);
  void editFrameInterpolation(int);
  void replaceKeyFrameImage(int, QImage);
  void playSavedKeyFrame();

 signals :
  void updateParameters(bool, bool, qglviewer::Vec, QString,
      int, int, QString, QString, QString,
      int, bool, bool, float, bool, bool);
  void loadKeyframes(QList<int>, QList<QImage>);
  void updateVolInfo(int);
  void updateVolInfo(int, int);
  void updateFocus(float, float);
  void updateLookFrom(qglviewer::Vec, qglviewer::Quaternion, float, float);
  void updateTagColors();
  void updateLookupTable(unsigned char*);
  void updateLightInfo(LightingInformation);
  void updateBrickInfo(QList<BrickInformation>);
  void updateVolumeBounds(qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, int, int, qglviewer::Vec, qglviewer::Vec);
  void updateGL();
  void setImage(int, QImage);
  void currentFrameChanged(int);
  void updateTransferFunctionManager(QList<SplineInformation>);
  void updateMorph(bool);
  void replaceKeyFrameImage(int);
  void addKeyFrameNumbers(QList<int>);

 private :
  QList<CameraPathNode*> m_cameraList;
  QList<KeyFrameInformation*> m_keyFrameInfo;

  KeyFrameInformation m_savedKeyFrame;
  KeyFrameInformation m_copyKeyFrame;

  QList<qglviewer::Vec> m_tgP;
  QList<qglviewer::Quaternion> m_tgQ;
  void computeTangents();
  qglviewer::Vec interpolatePosition(int, int, float);
  qglviewer::Quaternion interpolateOrientation(int, int, float);

  void updateCameraPath();

  QMap<QString, QPair<QVariant, bool> > copyProperties(QString);
};

#endif
