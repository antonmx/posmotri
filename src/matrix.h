#ifndef MATRIX_H
#define MATRIX_H


#include <QGLViewer/qglviewer.h>


class Matrix
{
 public :
  static void identity(double*);
  static void matmult(double*, double*, double*);
  static void matrixFromAxisAngle(double*, qglviewer::Vec, float);
  static void createTransformationMatrix(double*, qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, float);
  static qglviewer::Vec xformVec(double*, qglviewer::Vec);
  static qglviewer::Vec rotateVec(double*, qglviewer::Vec);
  static void inverse(double*, double*);
};

#endif
