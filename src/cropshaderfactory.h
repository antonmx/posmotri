#ifndef CROPSHADERFACTORY_H
#define CROPSHADERFACTORY_H

#include "cropobject.h"

class CropShaderFactory {
 public :
  static QString generateCropping(QList<CropObject>);

 private :
  static QString applyTubeCropping (
    bool, bool, bool,
    qglviewer::Vec, qglviewer::Vec, float,
    qglviewer::Vec, qglviewer::Vec,
    float, float, float, float,
    int, int,
    int
  );
  static QString applyEllipsoidCropping(
    bool, bool, bool,
    qglviewer::Vec, float,
    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
    float, float,
    int, int,
    int
  );
  static QString applyBoxCropping(
    bool, bool, bool,
    qglviewer::Vec, float,
    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
    float, float,
    float, float,
    int, int,
    int
  );
};

#endif
