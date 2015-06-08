#ifndef TEARSHADERFACTORY_H
#define TEARSHADERFACTORY_H

#include "cropobject.h"

class TearShaderFactory {
public :
  static QString generateTear(QList<CropObject>);

private :
  static QString applyTear(
    qglviewer::Vec, float,
    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
    float, float,
    float, float,
    int,
    int, int,
    float
  );
  static QString applyDisplace(
    qglviewer::Vec, float,
    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
    float, float,
    float, float,
    int,
    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec, float,
    int, int
  );
};

#endif
