#ifndef BRICKS_H
#define BRICKS_H

#include "brickinformation.h"
#include "boundingbox.h"

class Bricks : public QObject
{
  Q_OBJECT

 public :
  Bricks();
  ~Bricks();

  QList<BrickInformation> bricks();
  QList<BrickBounds> ghostBricks();

  BrickInformation brickInformation(int);

  void reset();

  int selected();
  void setSelected(int);
  void setShowAxis(bool);

  bool updateFlag();
  void resetUpdateFlag();

  double* getMatrix();
  double* getMatrixInv();
  qglviewer::Vec getTranslation();
  qglviewer::Vec getPivot();
  qglviewer::Vec getAxis();
  float getAngle();
  qglviewer::Vec getScalePivot();
  qglviewer::Vec getScale();

  double* getMatrix(int);
  double* getMatrixInv(int);
  qglviewer::Vec getTranslation(int);
  qglviewer::Vec getPivot(int);
  qglviewer::Vec getAxis(int);
  float getAngle(int);
  qglviewer::Vec getScalePivot(int);
  qglviewer::Vec getScale(int);

  void activateBounds(int);
  void activateBounds();
  void deactivateBounds();

  bool keyPressEvent(QKeyEvent*);

 signals :
  void refresh();

 public slots :
  void addClipper();
  void removeClipper(int);
  void removeBrick(int);
  void addBrick(BrickInformation);
  void addBrick();
  void updateScaling();
  void setBounds(qglviewer::Vec, qglviewer::Vec);
  void setBricks(QList<BrickInformation>);
  void setBrick(int, BrickInformation);
  void update();
  void draw();

 private :
  bool m_updateFlag;
  bool m_showAxis;
  int m_selected;

  qglviewer::Vec m_dataMin, m_dataMax, m_dataSize;

  QList<BrickInformation> m_bricks;
  QList<BoundingBox*> m_brickBox;

  QList<BrickBounds> m_ghostBricks;

  QList<double*> m_Xform;
  QList<double*> m_XformInv;

  void drawAxisAngle(double*, int);
  void genMatrices();
};

#endif
