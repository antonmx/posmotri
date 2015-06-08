#include <QDebug>
#include "brickinformation.h"
#include "staticfunctions.h"
#include "PromotedWidgets.h"

using namespace qglviewer;


//----------------------------------
int DrawBrickInformation::subvolSize() { return m_subvol.size(); }
Vec DrawBrickInformation::subvol(int i)
{
  if (i < m_subvol.size())
    return m_subvol[i];
  else
    return Vec(0,0,0);
}
DrawBrickInformation::DrawBrickInformation()
{
  m_numBricks = 0;
  m_tfSet.clear();
  m_subvol.clear();
  m_subcorner.clear();
  m_subdim.clear();
  m_clips.clear();
  m_scalepivot.clear();
  m_scale.clear();
  m_texture.clear();
}
DrawBrickInformation::~DrawBrickInformation()
{
  m_numBricks = 0;
  m_tfSet.clear();
  m_subvol.clear();
  m_subcorner.clear();
  m_subdim.clear();
  m_scalepivot.clear();
  m_scale.clear();
  m_texture.clear();

  if (m_clips.size() > 0)
    {
      for(int i=0; i<m_clips.size(); i++)
	m_clips[i].clear();
    }
  m_clips.clear();
}
void
DrawBrickInformation::reset()
{
  m_numBricks = 0;
  m_tfSet.clear();
  m_subvol.clear();
  m_subcorner.clear();
  m_subdim.clear();
  m_scalepivot.clear();
  m_scale.clear();
  m_texture.clear();

  if (m_clips.size() > 0)
    {
      for(int i=0; i<m_clips.size(); i++)
	m_clips[i].clear();
    }
  m_clips.clear();
}
int DrawBrickInformation::numBricks() { return m_numBricks; }
bool
DrawBrickInformation::get(int i,
			  int& tfset,
			  Vec *subvol,
			  Vec *texture,
			  Vec& subcorner, Vec& subdim,
			  QList<bool>& clips,
			  Vec& scalepivot, Vec& scale)
{
  if (i >= m_numBricks)
    return false;

  tfset = m_tfSet[i];

  for (int j=0; j<8; j++)
    subvol[j] = m_subvol[8*i+j];

  for (int j=0; j<8; j++)
    texture[j] = m_texture[8*i+j];

  subcorner = m_subcorner[i];
  subdim = m_subdim[i];

  clips = m_clips[i];

  scalepivot = m_scalepivot[i];
  scale = m_scale[i];

  return true;
}
void
DrawBrickInformation::append( int tfset,
			      Vec *subvol,
			      Vec *texture,
			      Vec subcorner, Vec subdim,
			      QList<bool> clips,
			      Vec scalepivot, Vec scale)
{
  m_tfSet.append(tfset);

  for (int j=0; j<8; j++)
    m_subvol.append(subvol[j]);

  for (int j=0; j<8; j++)
    m_texture.append(texture[j]);

  m_subcorner.append(subcorner);
  m_subdim.append(subdim);

  m_clips.append(clips);

  m_scalepivot.append(scalepivot);
  m_scale.append(scale);

  m_numBricks ++;
}
//----------------------------------


//----------------------------------
BrickBounds::BrickBounds()
{
  brickMin = Vec(0,0,0);
  brickMax = Vec(1,1,1);
}
BrickBounds::BrickBounds(Vec bmin, Vec bmax)
{
  brickMin = bmin;
  brickMax = bmax;
}
BrickBounds&
BrickBounds::operator=(const BrickBounds &bb)
{
  brickMin = bb.brickMin;
  brickMax = bb.brickMax;
  return *this;
}
//----------------------------------

Vec
BrickInformation::getCorrectedPivot()
{
  Vec sz = brickMax - brickMin;
  Vec p = brickMin + vMv(pivot, sz);
  return p;
}
Vec
BrickInformation::getCorrectedScalePivot()
{
  Vec sz = brickMax - brickMin;
  Vec p = brickMin + vMv(scalepivot, sz);
  return p;
}

void
BrickInformation::reset()
{
  tfSet = 0;
  linkBrick = 0;
  brickMin = Vec(0,0,0);
  brickMax = Vec(1,1,1);
  position = Vec(0,0,0);
  pivot = Vec(0.5,0.5,0.5);
  axis = Vec(1,0,0);
  angle = 0;
  scalepivot = Vec(0.5,0.5,0.5);
  scale = Vec(1,1,1);

  clippers.clear();
}

BrickInformation::BrickInformation()
{
  reset();
}
BrickInformation::~BrickInformation()
{
  reset();
}

BrickInformation::BrickInformation(const BrickInformation& bi)
{
  tfSet = bi.tfSet;
  linkBrick = bi.linkBrick;
  brickMin = bi.brickMin;
  brickMax = bi.brickMax;
  position = bi.position;
  pivot = bi.pivot;
  axis = bi.axis;
  angle = bi.angle;
  scalepivot = bi.scalepivot;
  scale = bi.scale;

  clippers = bi.clippers;
}

BrickInformation&
BrickInformation::operator=(const BrickInformation& bi)
{
  tfSet = bi.tfSet;
  linkBrick = bi.linkBrick;
  brickMin = bi.brickMin;
  brickMax = bi.brickMax;
  position = bi.position;
  pivot = bi.pivot;
  axis = bi.axis;
  angle = bi.angle;
  scalepivot = bi.scalepivot;
  scale = bi.scale;

  clippers = bi.clippers;

  return *this;
}

BrickInformation
BrickInformation::interpolate(const BrickInformation brickInfo1,
			      const BrickInformation brickInfo2,
			      float frc)
{
  BrickInformation brickInfo;

  brickInfo.tfSet = brickInfo1.tfSet;
  brickInfo.linkBrick = brickInfo1.linkBrick;

  brickInfo.brickMin = StaticFunctions::interpolate(brickInfo1.brickMin,
						    brickInfo2.brickMin,
						    frc);

  brickInfo.brickMax = StaticFunctions::interpolate(brickInfo1.brickMax,
						    brickInfo2.brickMax,
						    frc);

  brickInfo.position = StaticFunctions::interpolate(brickInfo1.position,
						    brickInfo2.position,
						    frc);

  brickInfo.pivot = StaticFunctions::interpolate(brickInfo1.pivot,
						    brickInfo2.pivot,
						    frc);

  brickInfo.scalepivot = StaticFunctions::interpolate(brickInfo1.scalepivot,
						      brickInfo2.scalepivot,
						      frc);

  brickInfo.scale = StaticFunctions::interpolate(brickInfo1.scale,
						 brickInfo2.scale,
						 frc);

  if ((brickInfo1.axis-brickInfo2.axis).squaredNorm() < 0.001)
    { // same axis
      brickInfo.axis = brickInfo1.axis;
      brickInfo.angle = brickInfo1.angle + frc*(brickInfo2.angle-
						brickInfo1.angle);
    }
  else
    {
      if (fabs(brickInfo1.angle) < 0.001 &&
	  fabs(brickInfo2.angle) < 0.001)
	{ // axis change for 0 angle
	  if (frc < 0.5)
	    {
	      brickInfo.axis = brickInfo1.axis;
	      brickInfo.angle = brickInfo1.angle;
	    }
	  else
	    {
	      brickInfo.axis = brickInfo2.axis;
	      brickInfo.angle = brickInfo2.angle;
	    }
	}
      else
	{
	  Quaternion q, q1, q2;
	  q1 = Quaternion(brickInfo1.axis, DEG2RAD(brickInfo1.angle));
	  q2 = Quaternion(brickInfo2.axis, DEG2RAD(brickInfo2.angle));
	  q = Quaternion::slerp(q1, q2, frc);
	  brickInfo.axis = q.axis();
	  brickInfo.angle = RAD2DEG(q.angle());
	}
    }


  if (brickInfo1.clippers.size() == brickInfo2.clippers.size())
    {
      brickInfo.clippers = brickInfo1.clippers;
    }
  else
    {
      for(int ci=0;
	  ci<qMin(brickInfo1.clippers.size(),
		  brickInfo2.clippers.size());
	  ci++)
	{
	  brickInfo.clippers.append(brickInfo1.clippers[ci]);
	}
      if (brickInfo2.clippers.size() < brickInfo1.clippers.size())
	{
	  for(int ci=brickInfo2.clippers.size();
	      ci<brickInfo1.clippers.size();
	      ci++)
	    {
	      brickInfo.clippers.append(brickInfo1.clippers[ci]);
	    }
	}
    }

  return brickInfo;
}


QList<BrickInformation>
BrickInformation::interpolate(const QList<BrickInformation> brickInfo1,
			      const QList<BrickInformation> brickInfo2,
			      float frc)
{
  int i;
  QList <BrickInformation> brickInfo;

  for(i=0; i<qMin(brickInfo1.size(), brickInfo2.size()); i++)
    brickInfo.append(interpolate(brickInfo1[i], brickInfo2[i], frc));

  if (brickInfo1.size() > brickInfo2.size())
    {
      for(i=brickInfo2.size(); i<brickInfo1.size(); i++)
	brickInfo.append(brickInfo1[i]);
    }

  return brickInfo;
}






void BrickInformation::load(const QConfigMe & cfg) {
  reset();
  cfg.beginGroup("BrickInformation");
  cfg.getValue("tfset", tfSet);
  cfg.getValue("linkbrick", linkBrick);
  cfg.getValue("brickmin", brickMin);
  cfg.getValue("brickmax", brickMax);
  cfg.getValue("position", position);
  cfg.getValue("pivot", pivot);
  cfg.getValue("axis", axis);
  cfg.getValue("angle", angle);
  cfg.getValue("scalepivot", scalepivot);
  cfg.getValue("scale", scale);
  cfg.getArrayValue("Clippers",  clippers);
  cfg.endGroup();
}



void BrickInformation::save(QConfigMe  & cfg) const {
  cfg.beginGroup("BrickInformation");
  cfg.setValue("tfset", tfSet);
  cfg.setValue("linkbrick", linkBrick);
  cfg.setValue("brickmin", brickMin);
  cfg.setValue("brickmax", brickMax);
  cfg.setValue("position", position);
  cfg.setValue("pivot", pivot);
  cfg.setValue("axis", axis);
  cfg.setValue("angle", angle);
  cfg.setValue("scalepivot", scalepivot);
  cfg.setValue("scale", scale);
  cfg.setArrayValue("Clippers",  clippers);
  cfg.endGroup();
}
