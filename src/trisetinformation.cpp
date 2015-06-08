#include "trisetinformation.h"

using namespace qglviewer;

TrisetInformation::TrisetInformation() { clear(); }

void
TrisetInformation::clear()
{
  filename.clear();
  position = Vec(0,0,0);
  scale = Vec(1,1,1);
  color = Vec(1,1,1);
  cropcolor = Vec(0,0,0);
  opacity = 1;
  ambient = 0;
  diffuse = 1;
  specular = 1;
  pointMode = true;
  pointSize = 10;
  pointStep = 1;
  blendMode = false;
  shadows = false;
  screenDoor = false;
  flipNormals = false;
}

TrisetInformation&
TrisetInformation::operator=(const TrisetInformation& ti)
{
  filename = ti.filename;
  position = ti.position;
  scale = ti.scale;
  color = ti.color;
  cropcolor = ti.cropcolor;
  opacity = ti.opacity;
  ambient = ti.ambient;
  diffuse = ti.diffuse;
  specular = ti.specular;
  pointMode = ti.pointMode;
  pointStep = ti.pointStep;
  pointSize = ti.pointSize;
  blendMode = ti.blendMode;
  shadows = ti.shadows;
  screenDoor = ti.screenDoor;
  flipNormals = ti.flipNormals;

  return *this;
}

TrisetInformation
TrisetInformation::interpolate(const TrisetInformation & tinfo1,
                               const TrisetInformation & tinfo2,
                               float frc)
{
  TrisetInformation tinfo;
  tinfo.filename = tinfo1.filename;
  tinfo.opacity = (1-frc)*tinfo1.opacity + frc*tinfo2.opacity;
  tinfo.position = (1-frc)*tinfo1.position + frc*tinfo2.position;
  tinfo.scale = (1-frc)*tinfo1.scale + frc*tinfo2.scale;
  tinfo.color = (1-frc)*tinfo1.color + frc*tinfo2.color;
  tinfo.cropcolor = (1-frc)*tinfo1.cropcolor + frc*tinfo2.cropcolor;
  tinfo.ambient = (1-frc)*tinfo1.ambient + frc*tinfo2.ambient;
  tinfo.diffuse = (1-frc)*tinfo1.diffuse + frc*tinfo2.diffuse;
  tinfo.specular = (1-frc)*tinfo1.specular + frc*tinfo2.specular;
  tinfo.pointMode = tinfo1.pointMode;
  tinfo.pointStep = (1-frc)*tinfo1.pointStep + frc*tinfo2.pointStep;
  tinfo.pointSize = (1-frc)*tinfo1.pointSize + frc*tinfo2.pointSize;
  tinfo.blendMode = tinfo1.blendMode;
  tinfo.shadows = tinfo1.shadows;
  tinfo.screenDoor = tinfo1.screenDoor;
  tinfo.flipNormals = tinfo1.flipNormals;

  return tinfo;
}

QList<TrisetInformation>
TrisetInformation::interpolate(const QList<TrisetInformation> & tinfo1,
                               const QList<TrisetInformation> & tinfo2,
                               float frc)
{
  QVector<int> present;
  present.resize(tinfo1.count());
  for(int i=0; i<tinfo1.count(); i++)
    {
      present[i] = -1;
      for(int j=0; j<tinfo2.count(); j++)
	{
	  if (tinfo1[i].filename == tinfo2[j].filename)
	    {
	      present[i] = j;
	      break;
	    }
	}
    }

  QList<TrisetInformation> tinfo;
  for(int i=0; i<tinfo1.count(); i++)
    {
      if (present[i] >= 0)
	{
	  TrisetInformation ti;
	  ti = interpolate(tinfo1[i], tinfo2[present[i]], frc);
	  tinfo.append(ti);
	}
      else
	tinfo.append(tinfo1[i]);
    }

  return tinfo;
}

void TrisetInformation::save ( QConfigMe & cfg ) const {
  cfg.beginGroup("TrisetInformation");
  cfg.setValue("filename", filename);
  cfg.setValue("position", position);
  cfg.setValue("scale", scale);
  cfg.setValue("opacity", opacity);  
  cfg.setValue("color", color);
  cfg.setValue("cropcolor", cropcolor);
  cfg.setValue("ambient", ambient);
  cfg.setValue("diffuse", diffuse);
  cfg.setValue("specular", specular);
  cfg.setValue("pointmode", pointMode);
  cfg.setValue("pointstep", pointStep);
  cfg.setValue("pointsize", pointSize);
  cfg.setValue("blendmode", blendMode);
  cfg.setValue("shadows", shadows);
  cfg.setValue("screendoor", screenDoor);
  cfg.setValue("flipnormals", flipNormals);
  cfg.endGroup();
}

void TrisetInformation::load ( const QConfigMe & cfg ) {
  clear();
  cfg.beginGroup("TrisetInformation");
  cfg.getValue("filename", filename);
  cfg.getValue("position", position);
  cfg.getValue("scale", scale);
  cfg.getValue("opacity", opacity);  
  cfg.getValue("color", color);
  cfg.getValue("cropcolor", cropcolor);
  cfg.getValue("ambient", ambient);
  cfg.getValue("diffuse", diffuse);
  cfg.getValue("specular", specular);
  cfg.getValue("pointmode", pointMode);
  cfg.getValue("pointstep", pointStep);
  cfg.getValue("pointsize", pointSize);
  cfg.getValue("blendmode", blendMode);
  cfg.getValue("shadows", shadows);
  cfg.getValue("screendoor", screenDoor);
  cfg.getValue("flipnormals", flipNormals);
  cfg.endGroup();
}
