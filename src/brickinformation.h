#ifndef BRICKINFORMATION_H
#define BRICKINFORMATION_H

#include <QGLViewer/qglviewer.h>
#include "PromotedWidgets.h"

class DrawBrickInformation {
 public :
  DrawBrickInformation();
  ~DrawBrickInformation();

  void reset();
  int numBricks();
  int subvolSize();
  qglviewer::Vec subvol(int);

  bool get(int, int&,
	   qglviewer::Vec*, qglviewer::Vec*,
	   qglviewer::Vec&, qglviewer::Vec&,
	   QList<bool>&,
	   qglviewer::Vec&, qglviewer::Vec&);
  void append(int,
	      qglviewer::Vec*, qglviewer::Vec*,
	      qglviewer::Vec, qglviewer::Vec,
	      QList<bool>,
	      qglviewer::Vec, qglviewer::Vec);

 private :
  int m_numBricks;
  QList<int> m_tfSet;
  QList<qglviewer::Vec> m_subvol;
  QList<qglviewer::Vec> m_subcorner;
  QList<qglviewer::Vec> m_subdim;
  QList<qglviewer::Vec> m_scalepivot;
  QList<qglviewer::Vec> m_scale;
  QList<qglviewer::Vec> m_texture;

  QList< QList<bool> > m_clips;
};

class BrickBounds
{
 public :
  BrickBounds();
  BrickBounds(qglviewer::Vec, qglviewer::Vec);
  BrickBounds& operator=(const BrickBounds&);
  qglviewer::Vec brickMin, brickMax;
};

class BrickInformation
{
 public :
  BrickInformation();
  ~BrickInformation();
  BrickInformation(const BrickInformation&);
  BrickInformation& operator=(const BrickInformation&);

  qglviewer::Vec getCorrectedPivot();
  qglviewer::Vec getCorrectedScalePivot();

  static BrickInformation interpolate(const BrickInformation,
				      const BrickInformation,
				      float);

  static QList<BrickInformation> interpolate(const QList<BrickInformation>,
					     const QList<BrickInformation>,
					     float);

  void load(const QConfigMe&);
  void save(QConfigMe&) const;


  int tfSet;
  int linkBrick;
  qglviewer::Vec brickMin, brickMax;
  qglviewer::Vec position;
  qglviewer::Vec pivot;
  qglviewer::Vec axis;
  float angle;
  qglviewer::Vec scalepivot;
  qglviewer::Vec scale;
  QList<bool> clippers;

 private :
  void reset();
};

#endif
