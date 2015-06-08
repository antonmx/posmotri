#ifndef CLASSES_H
#define CLASSES_H


#include <QGLViewer/qglviewer.h>


class ViewAlignedPolygon
{
 public :
  ViewAlignedPolygon();
  ViewAlignedPolygon& operator=(const ViewAlignedPolygon&);

  void scale(float);

  int edges;
  qglviewer::Vec vertex[100];
  qglviewer::Vec texcoord[100];
  float tx[100], ty[100];
};


class VoxelizedPath
{
 public :
  VoxelizedPath();
  ~VoxelizedPath();
  VoxelizedPath& operator=(const VoxelizedPath&);

  QList<qglviewer::Vec> voxels;
  QList<qglviewer::Vec> normals;
  QList<uint> index;
};

class BatchJob
{
 public :
  BatchJob();
  BatchJob& operator=(const BatchJob&);

  bool startProject;
  bool backgroundrender;
  bool renderFrames;
  bool image;
  bool movie;
  bool imagesize;
  bool shading;
  bool skipEmptySpace;
  bool dragonly;
  bool dragonlyforshadows;
  bool depthcue;
  float stepSize;
  int startFrame, endFrame, stepFrame;
  int imgWidth, imgHeight, frameRate;
  int imageMode;
  QString projectFilename;
  QString imageFilename, movieFilename;
};

#endif
