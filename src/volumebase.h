#ifndef VOLUMEBASE_H
#define VOLUMEBASE_H



#include <QGLViewer/vec.h>


class VolumeBase : public QObject
{
  Q_OBJECT

 public :
  VolumeBase();
  ~VolumeBase();

  int pvlVoxelType();

  bool loadDummyVolume(int, int, int);

  bool loadVolume(const char*, bool);

  qglviewer::Vec getFullVolumeSize();
  qglviewer::Vec getLowresVolumeSize();
  qglviewer::Vec getLowresTextureVolumeSize();
  int getLowresSubsamplingLevel();
  int* getLowres1dHistogram();
  int* getLowres2dHistogram();
  unsigned char* getLowresVolume();
  unsigned char* getLowresTextureVolume();

  void createLowresTextureVolume();

 protected :
  QString m_volumeFile;
  int m_pvlVoxelType;
  int m_depth, m_width, m_height;
  int *m_1dHistogram, *m_2dHistogram;
  qglviewer::Vec m_fullVolumeSize;
  qglviewer::Vec m_lowresVolumeSize;
  qglviewer::Vec m_lowresTextureVolumeSize;
  int m_subSamplingLevel;
  unsigned char *m_lowresVolume;
  unsigned char *m_lowresTextureVolume;

  void createLowresVolume(bool);
};

#endif
