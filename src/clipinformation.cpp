
#include "clipinformation.h"
#include <QVector4D>
#include "PromotedWidgets.h"

ClipInformation::ClipInformation() { clear(); }
ClipInformation::~ClipInformation() { clear(); }
int ClipInformation::size() { return pos.size(); }

ClipInformation::ClipInformation(const ClipInformation& ci)
{
  show = ci.show;
  pos = ci.pos;
  rot = ci.rot;
  color = ci.color;
  solidColor = ci.solidColor;
  applyFlip = ci.applyFlip;
  apply = ci.apply;
  imageName = ci.imageName;
  imageFrame = ci.imageFrame;
  captionText = ci.captionText;
  captionFont = ci.captionFont;
  captionColor = ci.captionColor;
  captionHaloColor = ci.captionHaloColor;
  opacity = ci.opacity;
  stereo = ci.stereo;
  scale1 = ci.scale1;
  scale2 = ci.scale2;
  tfSet = ci.tfSet;
  viewport = ci.viewport;
  viewportType = ci.viewportType;
  viewportScale = ci.viewportScale;
  thickness = ci.thickness;
  showSlice = ci.showSlice;
  showOtherSlice = ci.showOtherSlice;
  showThickness = ci.showThickness;
  gridX = ci.gridX;
  gridY = ci.gridY;
}

ClipInformation&
ClipInformation::operator=(const ClipInformation& ci)
{
  show = ci.show;
  pos = ci.pos;
  rot = ci.rot;
  color = ci.color;
  solidColor = ci.solidColor;
  applyFlip = ci.applyFlip;
  apply = ci.apply;
  imageName = ci.imageName;
  imageFrame = ci.imageFrame;
  captionText = ci.captionText;
  captionFont = ci.captionFont;
  captionColor = ci.captionColor;
  captionHaloColor = ci.captionHaloColor;
  opacity = ci.opacity;
  stereo = ci.stereo;
  scale1 = ci.scale1;
  scale2 = ci.scale2;
  tfSet = ci.tfSet;
  viewport = ci.viewport;
  viewportType = ci.viewportType;
  viewportScale = ci.viewportScale;
  thickness = ci.thickness;
  showSlice = ci.showSlice;
  showOtherSlice = ci.showOtherSlice;
  showThickness = ci.showThickness;
  gridX = ci.gridX;
  gridY = ci.gridY;

  return *this;
}

void
ClipInformation::clear()
{
  show.clear();
  pos.clear();
  rot.clear();
  color.clear();
  solidColor.clear();
  applyFlip.clear();
  apply.clear();
  imageName.clear();
  imageFrame.clear();
  captionText.clear();
  captionFont.clear();
  captionColor.clear();
  captionHaloColor.clear();
  opacity.clear();
  stereo.clear();
  scale1.clear();
  scale2.clear();
  tfSet.clear();
  viewport.clear();
  viewportType.clear();
  viewportScale.clear();
  thickness.clear();
  showSlice.clear();
  showOtherSlice.clear();
  showThickness.clear();
  gridX.clear();
  gridY.clear();
}

ClipInformation
ClipInformation::interpolate(const ClipInformation clipInfo1,
			     const ClipInformation clipInfo2,
			     float frc)
{
  ClipInformation clipInfo;


  clipInfo.show = clipInfo1.show;
  clipInfo.applyFlip = clipInfo1.applyFlip;
  clipInfo.apply = clipInfo1.apply;
  clipInfo.imageName = clipInfo1.imageName;
  clipInfo.captionText = clipInfo1.captionText;
  clipInfo.tfSet = clipInfo1.tfSet;
  clipInfo.solidColor = clipInfo1.solidColor;
  clipInfo.showSlice = clipInfo1.showSlice;
  clipInfo.showOtherSlice = clipInfo1.showOtherSlice;
  clipInfo.showThickness = clipInfo1.showThickness;
  clipInfo.viewportType = clipInfo1.viewportType;

  // interpolate the rest
  for(int ci=0;
      ci<qMin(clipInfo1.pos.size(),
	      clipInfo2.pos.size());
      ci++)
    {
      Vec pos;
      Quaternion rot;
      pos = clipInfo1.pos[ci] + frc*(clipInfo2.pos[ci]-
				     clipInfo1.pos[ci]);
      rot = Quaternion::slerp(clipInfo1.rot[ci], clipInfo2.rot[ci], frc);

      float st, op, scl1, scl2;
      st = clipInfo1.stereo[ci] + frc*(clipInfo2.stereo[ci]-
					clipInfo1.stereo[ci]);
      op = clipInfo1.opacity[ci] + frc*(clipInfo2.opacity[ci]-
					clipInfo1.opacity[ci]);
      scl1 = clipInfo1.scale1[ci] + frc*(clipInfo2.scale1[ci]-
					 clipInfo1.scale1[ci]);
      scl2 = clipInfo1.scale2[ci] + frc*(clipInfo2.scale2[ci]-
					 clipInfo1.scale2[ci]);
      int grdx = clipInfo1.gridX[ci] + frc*(clipInfo2.gridX[ci]-
					    clipInfo1.gridX[ci]);
      int grdy = clipInfo1.gridY[ci] + frc*(clipInfo2.gridY[ci]-
					    clipInfo1.gridY[ci]);

      int frm;
      frm = clipInfo1.imageFrame[ci] + frc*(clipInfo2.imageFrame[ci]-
					    clipInfo1.imageFrame[ci]);

      Vec pcolor;
      pcolor = clipInfo1.color[ci] + frc*(clipInfo2.color[ci]-
					  clipInfo1.color[ci]);

      QVector4D vp;
      vp = clipInfo1.viewport[ci] + frc*(clipInfo2.viewport[ci]-
					 clipInfo1.viewport[ci]);

      float vps;
      vps = clipInfo1.viewportScale[ci] + frc*(clipInfo2.viewportScale[ci]-
					       clipInfo1.viewportScale[ci]);

      int thick;
      thick = clipInfo1.thickness[ci] + frc*(clipInfo2.thickness[ci]-
					     clipInfo1.thickness[ci]);

      QFont cfont = clipInfo1.captionFont[ci];
      QColor ccolor = clipInfo1.captionColor[ci];
      QColor chcolor = clipInfo1.captionHaloColor[ci];
      if (clipInfo1.captionText[ci] == clipInfo2.captionText[ci])
	{
	  QFont cfont2 = clipInfo1.captionFont[ci];

	  if (cfont.family() == cfont2.family())
	    {
	      // interpolate pointsize
	      int pt1 = cfont.pointSize();
	      int pt2 = cfont2.pointSize();
	      int pt = (1-frc)*pt1 + frc*pt2;
	      cfont.setPointSize(pt);
	    }

	  // interpolate color
	  float r1 = ccolor.redF();
	  float g1 = ccolor.greenF();
	  float b1 = ccolor.blueF();
	  float a1 = ccolor.alphaF();
	  QColor c = clipInfo2.captionColor[ci];
	  float r2 = c.redF();
	  float g2 = c.greenF();
	  float b2 = c.blueF();
	  float a2 = c.alphaF();
	  float r = (1-frc)*r1 + frc*r2;
	  float g = (1-frc)*g1 + frc*g2;
	  float b = (1-frc)*b1 + frc*b2;
	  float a = (1-frc)*a1 + frc*a2;
	  ccolor = QColor(r*255, g*255, b*255, a*255);


	  r1 = chcolor.redF();
	  g1 = chcolor.greenF();
	  b1 = chcolor.blueF();
	  a1 = chcolor.alphaF();
	   c = clipInfo2.captionHaloColor[ci];
	  r2 = c.redF();
	  g2 = c.greenF();
	  b2 = c.blueF();
	  a2 = c.alphaF();
	  r = (1-frc)*r1 + frc*r2;
	  g = (1-frc)*g1 + frc*g2;
	  b = (1-frc)*b1 + frc*b2;
	  a = (1-frc)*a1 + frc*a2;
	  chcolor = QColor(r*255, g*255, b*255, a*255);
	}


      clipInfo.pos.append(pos);
      clipInfo.rot.append(rot);
      clipInfo.opacity.append(op);
      clipInfo.stereo.append(st);
      clipInfo.scale1.append(scl1);
      clipInfo.scale2.append(scl2);
      clipInfo.gridX.append(grdx);
      clipInfo.gridY.append(grdy);
      clipInfo.imageFrame.append(frm);
      clipInfo.captionFont.append(cfont);
      clipInfo.captionColor.append(ccolor);
      clipInfo.captionHaloColor.append(chcolor);
      clipInfo.color.append(pcolor);
      clipInfo.viewport.append(vp);
      clipInfo.viewportScale.append(vps);
      clipInfo.thickness.append(thick);
    }

//  if (clipInfo1.pos.size() < clipInfo2.pos.size())
//    {
//      for(int ci=clipInfo1.pos.size();
//	  ci < clipInfo2.pos.size();
//	  ci++)
//	{
//	  clipInfo.pos.append(clipInfo2.pos[ci]);
//	  clipInfo.rot.append(clipInfo2.rot[ci]);
//	}
//    }
  if (clipInfo2.pos.size() < clipInfo1.pos.size())
    {
      for(int ci=clipInfo2.pos.size();
	  ci < clipInfo1.pos.size();
	  ci++)
	{
	  clipInfo.pos.append(clipInfo1.pos[ci]);
	  clipInfo.rot.append(clipInfo1.rot[ci]);
	  clipInfo.opacity.append(clipInfo1.opacity[ci]);
	  clipInfo.stereo.append(clipInfo1.stereo[ci]);
	  clipInfo.scale1.append(clipInfo1.scale1[ci]);
	  clipInfo.scale2.append(clipInfo1.scale2[ci]);
	  clipInfo.imageFrame.append(clipInfo1.imageFrame[ci]);
	  clipInfo.captionFont.append(clipInfo1.captionFont[ci]);
	  clipInfo.captionColor.append(clipInfo1.captionColor[ci]);
	  clipInfo.captionHaloColor.append(clipInfo1.captionHaloColor[ci]);
	  clipInfo.color.append(clipInfo1.color[ci]);
	  clipInfo.viewport.append(clipInfo1.viewport[ci]);
	  clipInfo.viewportScale.append(clipInfo1.viewportScale[ci]);
	  clipInfo.thickness.append(clipInfo1.thickness[ci]);
	}
    }

  return clipInfo;
}



void ClipInformation::save(QSettings &cfg) const {
  cfg.beginGroup("ClipInformation");
  cfg.beginWriteArray("ClipInformationArray",  pos.size());
  for (int i = 0; i < pos.size(); i++) {
    cfg.setArrayIndex(i);
    cfg.setValue("position", QVecEdit::toString(pos[i]));
    cfg.setValue("rotation_axis",  QVecEdit::toString(rot[i].axis()));
    cfg.setValue("rotation_angle",  rot[i].angle());
    cfg.setValue("show", show[i]);
    cfg.setValue("flip", applyFlip[i]);
    cfg.setValue("apply", apply[i]);
    cfg.setValue("imagename",  imageName[i]);
    cfg.setValue("imageframe", imageFrame[i]);
    cfg.setValue("captiontext",  captionText[i]);
    cfg.setValue("captionfont",  captionFont[i]);
    cfg.setValue("captioncolor", captionColor[i]);
    cfg.setValue("captionhalocolor", captionHaloColor[i]);
    cfg.setValue("opacity", opacity[i]);
    cfg.setValue("solidcolor", solidColor[i]);
    cfg.setValue("color", QVecEdit::toString(color[i]));
    cfg.setValue("scale1", scale1[i]);
    cfg.setValue("scale2", scale2[i]);
    cfg.setValue("tfset", tfSet[i]);
    cfg.setValue("gridx", gridX[i]);
    cfg.setValue("gridy", gridY[i]);
    cfg.setValue("viewport",  viewport[i]);
    cfg.setValue("viewporttype", viewportType[i]);
    cfg.setValue("viewportscale", viewportScale[i]);
    cfg.setValue("thickness", thickness[i]);
    cfg.setValue("showslice", showSlice[i]);
    cfg.setValue("showotherslice", showOtherSlice[i]);
    cfg.setValue("showthickness", showThickness[i]);
    cfg.setValue("stereo", stereo[i]);
  }
  cfg.endArray();
  cfg.endGroup();
}


void ClipInformation::load(QSettings &cfg) {
  clear();
  cfg.beginGroup("ClipInformation");
  const int sz = cfg.beginReadArray("ClipInformationArray");
  for (int i = 0; i < sz; i++) {
    cfg.setArrayIndex(i);
    pos.append( QVecEdit::toVec( getQSettingsValue<QString>(cfg, "position") ) );
    rot.append( Quaternion( QVecEdit::toVec( getQSettingsValue<QString>(cfg, "rotation_axis") ),
                            getQSettingsValue<qreal>(cfg, "rotation_angle")) );
    show.append( getQSettingsValue<bool>(cfg, "show") );
    applyFlip.append( getQSettingsValue<bool>(cfg, "flip") );
    apply.append( getQSettingsValue<bool>(cfg, "apply") );
    imageName.append( getQSettingsValue<QString>(cfg, "imagename") );
    imageFrame.append( getQSettingsValue<int>(cfg, "imageframe") );
    captionText.append( getQSettingsValue<QString>(cfg, "captiontext") );
    captionFont.append( getQSettingsValue<QFont>(cfg, "captionfont") );
    captionColor.append( getQSettingsValue<QColor>(cfg, "captioncolor") );
    captionHaloColor.append( getQSettingsValue<QColor>(cfg, "captionhalocolor") );
    opacity.append( getQSettingsValue<float>(cfg, "opacity") );
    solidColor.append( getQSettingsValue<bool>(cfg, "solidcolor") );
    color.append( QVecEdit::toVec( getQSettingsValue<QString>(cfg, "color") ) );
    scale1.append( getQSettingsValue<float>(cfg, "scale1") );
    scale2.append( getQSettingsValue<float>(cfg, "scale2") );
    tfSet.append( getQSettingsValue<int>(cfg, "tfset") );
    gridX.append( getQSettingsValue<int>(cfg, "gridx") );
    gridY.append( getQSettingsValue<int>(cfg, "gridy") );
    viewport.append( getQSettingsValue<QVector4D>(cfg, "viewport") );
    viewportType.append( getQSettingsValue<bool>(cfg, "viewporttype") );
    viewportScale.append( getQSettingsValue<float>(cfg, "viewportscale") );
    thickness.append( getQSettingsValue<int>(cfg, "thickness") );
    showSlice.append( getQSettingsValue<bool>(cfg, "showslice") );
    showOtherSlice.append( getQSettingsValue<bool>(cfg, "showotherslice") );
    showThickness.append( getQSettingsValue<bool>(cfg, "showthickness") );
    stereo.append( getQSettingsValue<float>(cfg, "stereo") );
  }
  cfg.endArray();
  cfg.endGroup();
}

