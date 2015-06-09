#include "lightinginformation.h"
#include "staticfunctions.h"
#include "PromotedWidgets.h"
using namespace qglviewer;

Highlights::Highlights(float _ambient, float _diffuse, float _specular,  int _specularCoefficient)
  : ambient(_ambient)
  , diffuse(_diffuse)
  , specular(_specular)
  , specularCoefficient(_specularCoefficient)
{}

Highlights Highlights::interpolate(const Highlights highlights1, const Highlights highlights2, float frc) {
  Highlights highlights;
  highlights.ambient = highlights1.ambient + frc*(highlights2.ambient-highlights1.ambient);
  highlights.diffuse = highlights1.diffuse + frc*(highlights2.diffuse-highlights1.diffuse);
  highlights.specular = highlights1.specular + frc*(highlights2.specular-highlights1.specular);
  highlights.specularCoefficient = highlights1.specularCoefficient + frc*(highlights2.specularCoefficient-highlights1.specularCoefficient);
  return highlights;
}


LightingInformation::LightingInformation()
{
  applyEmissive = false;
  applyLighting = true;
  applyShadows = true;
  applyColoredShadows = false;
  applyBackplane = false;
  colorAttenuation = Vec(1,1,1);
  userLightVector = Vec(0,0,1);
  shadowBlur = 1.9f;
  shadowScale = 0.7f;
  shadowIntensity = 0.5f;
  shadowFovOffset = 0.0f;
  lightDistanceOffset = 1.0f;
  backplaneShadowScale = 1.0f;
  backplaneIntensity = 1.0f;

  peel = false;
  peelType = 0;
  peelMin = 0.3f;
  peelMax = -0.3f;
  peelMix = 0.0;
}

void
LightingInformation::clear()
{
  applyEmissive = false;
  applyLighting = true;
  applyShadows = true;
  applyColoredShadows = false;
  applyBackplane = false;
  colorAttenuation = Vec(1,1,1);
  userLightVector = Vec(0,0,1);
  shadowBlur = 1.9f;
  shadowScale = 0.7f;
  shadowIntensity = 0.5f;
  shadowFovOffset = 0.0f;
  lightDistanceOffset = 0.0f;
  backplaneShadowScale = 1.0f;
  backplaneIntensity = 1.0f;

  peel = false;
  peelType = 0;
  peelMin = -0.3f;
  peelMax = 0.3f;
  peelMix = 0.0;
}

LightingInformation::LightingInformation(const LightingInformation& li)
{
  applyEmissive = li.applyEmissive;
  applyLighting = li.applyLighting;
  applyShadows = li.applyShadows;
  applyColoredShadows = li.applyColoredShadows;
  applyBackplane = li.applyBackplane;
  colorAttenuation = li.colorAttenuation;
  userLightVector = li.userLightVector;
  shadowBlur = li.shadowBlur;
  shadowScale = li.shadowScale;
  shadowIntensity = li.shadowIntensity;
  shadowFovOffset = li.shadowFovOffset;
  lightDistanceOffset = li.lightDistanceOffset;
  backplaneShadowScale = li.backplaneShadowScale;
  backplaneIntensity = li.backplaneIntensity;
  highlights = li.highlights;

  peel = li.peel;
  peelType = li.peelType;
  peelMin = li.peelMin;
  peelMax = li.peelMax;
  peelMix = li.peelMix;
}
LightingInformation&
LightingInformation::operator=(const LightingInformation& li)
{
  applyEmissive = li.applyEmissive;
  applyLighting = li.applyLighting;
  applyShadows = li.applyShadows;
  applyColoredShadows = li.applyColoredShadows;
  applyBackplane = li.applyBackplane;
  colorAttenuation = li.colorAttenuation;
  userLightVector = li.userLightVector;
  shadowBlur = li.shadowBlur;
  shadowScale = li.shadowScale;
  shadowIntensity = li.shadowIntensity;
  shadowFovOffset = li.shadowFovOffset;
  lightDistanceOffset = li.lightDistanceOffset;
  backplaneShadowScale = li.backplaneShadowScale;
  backplaneIntensity = li.backplaneIntensity;
  highlights = li.highlights;

  peel = li.peel;
  peelType = li.peelType;
  peelMin = li.peelMin;
  peelMax = li.peelMax;
  peelMix = li.peelMix;

  return *this;
}

LightingInformation
LightingInformation::interpolate(const LightingInformation lightInfo1,
				 const LightingInformation lightInfo2,
				 float frc)
{
  LightingInformation lightInfo;

  if (frc <= 0.5)
    {
      lightInfo.applyEmissive = lightInfo1.applyEmissive;
      lightInfo.applyLighting = lightInfo1.applyLighting;
      lightInfo.applyShadows = lightInfo1.applyShadows;
      lightInfo.applyColoredShadows = lightInfo1.applyColoredShadows;
      lightInfo.applyBackplane = lightInfo1.applyBackplane;
      lightInfo.peel = lightInfo1.peel;
      lightInfo.peelType = lightInfo1.peelType;
    }
  else
    {
      lightInfo.applyEmissive = lightInfo2.applyEmissive;
      lightInfo.applyLighting = lightInfo2.applyLighting;
      lightInfo.applyShadows = lightInfo2.applyShadows;
      lightInfo.applyColoredShadows = lightInfo2.applyColoredShadows;
      lightInfo.applyBackplane = lightInfo2.applyBackplane;
      lightInfo.peel = lightInfo2.peel;
      lightInfo.peelType = lightInfo2.peelType;
    }

  lightInfo.colorAttenuation = lightInfo1.colorAttenuation + frc*(lightInfo2.colorAttenuation -
								  lightInfo1.colorAttenuation);

  lightInfo.shadowBlur = lightInfo1.shadowBlur + frc*(lightInfo2.shadowBlur -
						      lightInfo1.shadowBlur);

  lightInfo.shadowScale = lightInfo1.shadowScale + frc*(lightInfo2.shadowScale -
							lightInfo1.shadowScale);

  lightInfo.shadowIntensity = lightInfo1.shadowIntensity + frc*(lightInfo2.shadowIntensity -
								lightInfo1.shadowIntensity);

  lightInfo.shadowFovOffset = lightInfo1.shadowFovOffset + frc*(lightInfo2.shadowFovOffset -
								lightInfo1.shadowFovOffset);

  lightInfo.peelMin = lightInfo1.peelMin + frc*(lightInfo2.peelMin - lightInfo1.peelMin);
  lightInfo.peelMax = lightInfo1.peelMax + frc*(lightInfo2.peelMax - lightInfo1.peelMax);
  lightInfo.peelMix = lightInfo1.peelMix + frc*(lightInfo2.peelMix - lightInfo1.peelMix);

  if ((lightInfo1.userLightVector-
       lightInfo2.userLightVector).squaredNorm() > 0.001)
    {
      Vec axis;
      float angle;
      StaticFunctions::getRotationBetweenVectors(lightInfo1.userLightVector,
						 lightInfo2.userLightVector,
						 axis, angle);
      Quaternion q(axis, angle*frc);
      lightInfo.userLightVector = q.rotate(lightInfo1.userLightVector);
    }
  else
    lightInfo.userLightVector = lightInfo1.userLightVector;


  lightInfo.lightDistanceOffset = lightInfo1.lightDistanceOffset +
    frc*(lightInfo2.lightDistanceOffset - lightInfo1.lightDistanceOffset);

  lightInfo.backplaneShadowScale = lightInfo1.backplaneShadowScale +
    frc*(lightInfo2.backplaneShadowScale - lightInfo1.backplaneShadowScale);

  lightInfo.backplaneIntensity = lightInfo1.backplaneIntensity +
    frc*(lightInfo2.backplaneIntensity - lightInfo1.backplaneIntensity);

  lightInfo.highlights = Highlights::interpolate(lightInfo1.highlights,
						 lightInfo2.highlights,
						 frc);

  return lightInfo;
}








void LightingInformation::save(QConfigMe  & cfg) const {
  cfg.beginGroup("LightingInformation");
  cfg.setValue("applyemissive", applyEmissive);
  cfg.setValue("applylighting", applyLighting);
  cfg.setValue("applyshadows", applyShadows);
  cfg.setValue("applycoloredshadows", applyColoredShadows);
  cfg.setValue("applybackplane", applyBackplane);
  cfg.setValue("colorattenuation", colorAttenuation);
  cfg.setValue("userlightvector",  userLightVector);
  cfg.setValue("shadowblur", shadowBlur);
  cfg.setValue("shadowscale", shadowScale);
  cfg.setValue("shadowintensity", shadowIntensity);
  cfg.setValue("shadowfovoffset", shadowFovOffset);
  cfg.setValue("lightdistanceoffset", lightDistanceOffset);
  cfg.setValue("backplaneshadowscale", backplaneShadowScale);
  cfg.setValue("backplaneintensity", backplaneIntensity);
  cfg.setValue("ambient", highlights.ambient);
  cfg.setValue("diffuse", highlights.diffuse);
  cfg.setValue("specular", highlights.specular);
  cfg.setValue("specularcoefficient", highlights.specularCoefficient);
  cfg.setValue("peel", peel);
  cfg.setValue("peeltype", peelType);
  cfg.setValue("peelmin", peelMin);
  cfg.setValue("peelmax", peelMax);
  cfg.setValue("peelmix", peelMix);
  cfg.endGroup();
}



void LightingInformation::load(const QConfigMe  & cfg) {
  cfg.beginGroup("LightingInformation");
  cfg.getValue("applyemissive", applyEmissive);
  cfg.getValue("applylighting", applyLighting);
  cfg.getValue("applyshadows", applyShadows);
  cfg.getValue("applycoloredshadows", applyColoredShadows);
  cfg.getValue("applybackplane", applyBackplane);
  cfg.getValue("colorattenuation", colorAttenuation);
  cfg.getValue("userlightvector",  userLightVector);
  cfg.getValue("shadowblur", shadowBlur);
  cfg.getValue("shadowscale", shadowScale);
  cfg.getValue("shadowintensity", shadowIntensity);
  cfg.getValue("shadowfovoffset", shadowFovOffset);
  cfg.getValue("lightdistanceoffset", lightDistanceOffset);
  cfg.getValue("backplaneshadowscale", backplaneShadowScale);
  cfg.getValue("backplaneintensity", backplaneIntensity);
  cfg.getValue("ambient", highlights.ambient);
  cfg.getValue("diffuse", highlights.diffuse);
  cfg.getValue("specular", highlights.specular);
  cfg.getValue("specularcoefficient", highlights.specularCoefficient);
  cfg.getValue("peel", peel);
  cfg.getValue("peeltype", peelType);
  cfg.getValue("peelmin", peelMin);
  cfg.getValue("peelmax", peelMax);
  cfg.getValue("peelmix", peelMix);
  cfg.endGroup();
}

