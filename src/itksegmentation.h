#ifndef ITKSEGMENTATION_H
#define ITKSEGMENTATION_H

//#include <QtGui>
#include <QGLViewer/qglviewer.h>


class ITKSegmentation
{
 public :
  static bool applyITKFilter(int, int, int, uchar*, QList<qglviewer::Vec>);
};

#endif
