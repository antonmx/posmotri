#include "gilightobjectinfo.h"

using namespace qglviewer;

GiLightObjectInfo::GiLightObjectInfo() { clear(); }
GiLightObjectInfo::~GiLightObjectInfo() { clear(); }

void
GiLightObjectInfo::clear()
{
  points.clear();
  allowInterpolation = false;
  show = true;
  doShadows = true;
  lightType = 0; // point type
  rad = 5;
  decay = 1.0;
  angle = 60.0;
  color = Vec(1,1,1);
  opacity = 1.0;
  segments = 1;
  lod = 1;
  smooth = 1;
}

GiLightObjectInfo&
GiLightObjectInfo::operator=(const GiLightObjectInfo& gi)
{
  points = gi.points;
  allowInterpolation = gi.allowInterpolation;
  show = gi.show;
  doShadows = gi.doShadows;
  lightType = gi.lightType;
  rad = gi.rad;
  decay = gi.decay;
  angle = gi.angle;
  color = gi.color;
  opacity = gi.opacity;
  segments = gi.segments;
  lod = gi.lod;
  smooth = gi.smooth;
  return *this;
}

GiLightObjectInfo
GiLightObjectInfo::interpolate(GiLightObjectInfo gi1,
			       GiLightObjectInfo gi2,
			       float frc)
{
  GiLightObjectInfo gi;

  gi.lod = gi1.lod;
  gi.smooth = gi1.smooth;
  gi.points = gi1.points;
  gi.allowInterpolation = gi1.allowInterpolation;
  gi.show = gi1.show;
  gi.doShadows = gi1.doShadows;
  gi.lightType = gi1.lightType;
  gi.rad = (1.0-frc)*gi1.rad + frc*gi2.rad;
  gi.decay = (1.0-frc)*gi1.decay + frc*gi2.decay;
  gi.angle = (1.0-frc)*gi1.angle + frc*gi2.angle;
  gi.color = (1.0-frc)*gi1.color + frc*gi2.color;  
  gi.opacity = (1.0-frc)*gi1.opacity + frc*gi2.opacity;  
  gi.segments = (1.0-frc)*gi1.segments + frc*gi2.segments;  

  if (gi1.allowInterpolation)
    {  
      QList<Vec> po1;
      QList<Vec> po2;
      po1 = gi1.points;
      po2 = gi2.points;

      Vec pi;
      QList<Vec> po;
      for(int i=0; i<po1.count(); i++)
	{
	  if (i < po2.count())
	    pi = (1-frc)*po1[i] + frc*po2[i];
	  else
	    pi = po1[i];
	  po.append(pi);
	}
      gi.points = po;
    }

  return gi;
}

QList<GiLightObjectInfo>
GiLightObjectInfo::interpolate(QList<GiLightObjectInfo> po1,
			       QList<GiLightObjectInfo> po2,
			       float frc)
{
  QList<GiLightObjectInfo> po;
  for(int i=0; i<po1.count(); i++)
    {
      GiLightObjectInfo pi;
      if (i < po2.count())
	{
	  pi = interpolate(po1[i], po2[i], frc);
	  po.append(pi);
	}
      else
	{
	  pi = po1[i];
	  po.append(pi);
	}
    }

  return po;
}

void GiLightObjectInfo::save(QConfigMe & cfg) const {
  cfg.beginGroup("GLOinfo");
  cfg.setArrayValue("Points", points);
  cfg.setValue("allowinterpolation", allowInterpolation);
  cfg.setValue("doshadows", doShadows);
  cfg.setValue("show", show);
  cfg.setValue("lighttype", lightType);
  cfg.setValue("rad", rad);
  cfg.setValue("decay", decay);
  cfg.setValue("angle", angle);
  cfg.setValue("color", color);
  cfg.setValue("opacity", opacity);
  cfg.setValue("segments", segments);
  cfg.setValue("lod", lod);
  cfg.setValue("smooth", smooth);
  cfg.endGroup();
}

void GiLightObjectInfo::load(const QConfigMe & cfg) {
  lod = 1;
  smooth = 1;
  points.clear();
  cfg.beginGroup("GLOinfo");
  cfg.getArrayValue("Points", points);
  cfg.getValue("allowinterpolation", allowInterpolation);
  cfg.getValue("doshadows", doShadows);
  cfg.getValue("show", show);
  cfg.getValue("lighttype", lightType);
  cfg.getValue("rad", rad);
  cfg.getValue("decay", decay);
  cfg.getValue("angle", angle);
  cfg.getValue("color", color);
  cfg.getValue("opacity", opacity);
  cfg.getValue("segments", segments);
  cfg.getValue("lod", lod);
  cfg.getValue("smooth", smooth);
  cfg.endGroup();  
}
