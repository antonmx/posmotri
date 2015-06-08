#ifndef BLENDSHADERFACTORY_H
#define BLENDSHADERFACTORY_H

#include "cropobject.h"

class BlendShaderFactory
{
 public :
  static QString generateBlend(QList<CropObject>, int nvol = 1);

 private :
  static QString applyBlend(qglviewer::Vec, float,
			    qglviewer::Vec, qglviewer::Vec, qglviewer::Vec,
			    float, float,
			    float, float,
			    int, float,
			    int, int);
};

#endif
