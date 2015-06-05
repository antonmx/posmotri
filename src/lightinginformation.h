#ifndef LIGHTINGINFORMATION_H
#define LIGHTINGINFORMATION_H

#include <QGLViewer/vec.h>
#include <QGLViewer/quaternion.h>
#include <QSettings>


#include <fstream>
using namespace std;

class Highlights {
public :
  Highlights( float _ambient = 1.0, float _diffuse = 0.0, float _specular = 1.0,  int _specularCoefficient = 7);
  static Highlights interpolate(const Highlights, const Highlights, float);
  float ambient;
  float diffuse;
  float specular;
  int specularCoefficient;
};


class LightingInformation
{
 public :
  LightingInformation();
  LightingInformation(const LightingInformation&);

  LightingInformation& operator=(const LightingInformation&);

  static LightingInformation interpolate(const LightingInformation,
					 const LightingInformation,
					 float);

  void clear();
  void load(QSettings &);
  void save(QSettings &) const;

  bool applyEmissive;
  bool applyLighting;
  bool applyShadows;
  bool applyColoredShadows;
  bool applyBackplane;
  bool peel;
  qglviewer::Vec colorAttenuation;
  qglviewer::Vec userLightVector;
  float shadowBlur;
  float shadowScale;
  float shadowIntensity;
  float shadowFovOffset;
  float lightDistanceOffset;
  float backplaneShadowScale;
  float backplaneIntensity;
  int peelType;
  float peelMin, peelMax, peelMix;

  Highlights highlights;
};

#endif
