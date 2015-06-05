#include "global.h"
#include "glewinitialisation.h"
#include "viewinformation.h"
#include <QBuffer>
#include <QDebug>
#include "PromotedWidgets.h"

void ViewInformation::setVolumeNumber(int vn) { m_volumeNumber = vn; }
void ViewInformation::setVolumeNumber2(int vn) { m_volumeNumber2 = vn; }
void ViewInformation::setVolumeNumber3(int vn) { m_volumeNumber3 = vn; }
void ViewInformation::setVolumeNumber4(int vn) { m_volumeNumber4 = vn; }
void ViewInformation::setStepsizeStill(float ss) { m_stepsizeStill = ss; }
void ViewInformation::setStepsizeDrag(float sd) { m_stepsizeDrag = sd; }
void ViewInformation::setDrawBox(bool db) { m_drawBox = db; }
void ViewInformation::setDrawAxis(bool db) { m_drawAxis = db; }
void ViewInformation::setBackgroundColor(Vec col) { m_backgroundColor = col; }
void ViewInformation::setBackgroundImageFile(QString fl) { m_backgroundImageFile = fl; }
void ViewInformation::setPosition(Vec pos) { m_position = pos; }
void ViewInformation::setOrientation(Quaternion rot) { m_rotation = rot; }
void ViewInformation::setFocusDistance(float fd) { m_focusDistance = fd; }
void ViewInformation::setImage(QImage pix) { m_image = pix; }
void ViewInformation::setRenderQuality(int rq) { m_renderQuality = rq; }
void ViewInformation::setLightInfo(LightingInformation li) { m_lightInfo = li; }
void ViewInformation::setClipInfo(ClipInformation ci) { m_clipInfo = ci; }
void ViewInformation::setBrickInfo(QList<BrickInformation> bi) { m_brickInfo = bi; }
void ViewInformation::setVolumeBounds(Vec bmin, Vec bmax) { m_volMin = bmin; m_volMax = bmax; }
void ViewInformation::setSplineInfo(QList<SplineInformation> si) { m_splineInfo = si; }
void ViewInformation::setTick(int sz, int st,
			       QString xl, QString yl, QString zl)
{
  m_tickSize = sz;
  m_tickStep = st;
  m_labelX = xl;
  m_labelY = yl;
  m_labelZ = zl;
}
void ViewInformation::setCaptions(QList<CaptionObject> co) { m_captions = co; }
void ViewInformation::setPoints(QList<Vec> pts) { m_points = pts; }
void ViewInformation::setPaths(QList<PathObject> paths) { m_paths = paths; }
void ViewInformation::setPathGroups(QList<PathGroupObject> paths) { m_pathgroups = paths; }
void ViewInformation::setTrisets(QList<TrisetInformation> tinfo) { m_trisets = tinfo; }
void ViewInformation::setNetworks(QList<NetworkInformation> ninfo) { m_networks = ninfo; }
void ViewInformation::setTagColors(uchar* tc) { memcpy(m_tagColors, tc, 1024); }

int ViewInformation::volumeNumber() { return m_volumeNumber; }
int ViewInformation::volumeNumber2() { return m_volumeNumber2; }
int ViewInformation::volumeNumber3() { return m_volumeNumber3; }
int ViewInformation::volumeNumber4() { return m_volumeNumber4; }
float ViewInformation::stepsizeStill() { return m_stepsizeStill; }
float ViewInformation::stepsizeDrag() { return m_stepsizeDrag; }
bool ViewInformation::drawBox()  { return m_drawBox; }
bool ViewInformation::drawAxis()  { return m_drawAxis; }
Vec ViewInformation::backgroundColor() { return m_backgroundColor; }
QString ViewInformation::backgroundImageFile() { return m_backgroundImageFile; }
Vec ViewInformation::position() { return m_position; }
Quaternion ViewInformation::orientation() { return m_rotation; }
float ViewInformation::focusDistance() { return m_focusDistance; }
QImage ViewInformation::image() { return m_image; }
int ViewInformation::renderQuality() { return m_renderQuality; }
LightingInformation ViewInformation::lightInfo() { return m_lightInfo; }
ClipInformation ViewInformation::clipInfo() { return m_clipInfo; }
QList<BrickInformation> ViewInformation::brickInfo() { return m_brickInfo; }
void ViewInformation::volumeBounds(Vec &bmin, Vec &bmax) { bmin = m_volMin; bmax = m_volMax; }
QList<SplineInformation> ViewInformation::splineInfo() { return m_splineInfo; }
void ViewInformation::getTick(int &sz, int &st,
			       QString &xl, QString &yl, QString &zl)
{
  sz = m_tickSize;
  st = m_tickStep;
  xl = m_labelX;
  yl = m_labelY;
  zl = m_labelZ;
}
QList<CaptionObject> ViewInformation::captions() { return m_captions; }
QList<Vec> ViewInformation::points() { return m_points; }
QList<PathObject> ViewInformation::paths() { return m_paths; }
QList<PathGroupObject> ViewInformation::pathgroups() { return m_pathgroups; }
QList<TrisetInformation> ViewInformation::trisets() { return m_trisets; }
QList<NetworkInformation> ViewInformation::networks() { return m_networks; }
uchar* ViewInformation::tagColors() { return m_tagColors; }


ViewInformation::ViewInformation()
{
  m_drawBox = false;
  m_drawAxis = false;
  m_backgroundColor = Vec(0,0,0);
  m_backgroundImageFile.clear();
  m_position = Vec(0,0,0);
  m_rotation = Quaternion(Vec(1,0,0), 0);
  m_focusDistance = 0;
  m_volumeNumber = 0;
  m_volumeNumber2 = 0;
  m_volumeNumber3 = 0;
  m_volumeNumber4 = 0;
  m_volMin = m_volMax = Vec(0,0,0);
  m_image = QImage(100, 100, QImage::Format_RGB32);
  m_clipInfo.clear();
  m_brickInfo.clear();
  m_splineInfo.clear();
  m_tickSize = 6;
  m_tickStep = 10;
  m_labelX = "X";
  m_labelY = "Y";
  m_labelZ = "Z";
  m_captions.clear();
  m_points.clear();
  m_paths.clear();
  m_pathgroups.clear();
  m_trisets.clear();
  m_networks.clear();
  m_tagColors = new uchar[1024];
}

ViewInformation::~ViewInformation()
{
  m_backgroundImageFile.clear();
  m_clipInfo.clear();
  m_brickInfo.clear();
  m_splineInfo.clear();
  m_labelX.clear();
  m_labelY.clear();
  m_labelZ.clear();
  m_captions.clear();
  m_points.clear();
  m_paths.clear();
  m_pathgroups.clear();
  m_trisets.clear();
  m_networks.clear();
  if (m_tagColors) delete [] m_tagColors;
}

ViewInformation::ViewInformation(const ViewInformation& viewInfo)
{
  m_volumeNumber = viewInfo.m_volumeNumber;
  m_volumeNumber2 = viewInfo.m_volumeNumber2;
  m_volumeNumber3 = viewInfo.m_volumeNumber3;
  m_volumeNumber4 = viewInfo.m_volumeNumber4;
  m_stepsizeStill = viewInfo.m_stepsizeStill;
  m_stepsizeDrag = viewInfo.m_stepsizeDrag;
  m_drawBox = viewInfo.m_drawBox;
  m_drawAxis = viewInfo.m_drawAxis;
  m_backgroundColor = viewInfo.m_backgroundColor;
  m_backgroundImageFile = viewInfo.m_backgroundImageFile;
  m_position = viewInfo.m_position;
  m_rotation = viewInfo.m_rotation;
  m_focusDistance = viewInfo.m_focusDistance;
  m_image = viewInfo.m_image;
  m_renderQuality = viewInfo.m_renderQuality;
  m_lightInfo = viewInfo.m_lightInfo;
  m_clipInfo = viewInfo.m_clipInfo;
  m_brickInfo = viewInfo.m_brickInfo;
  m_volMin = viewInfo.m_volMin;
  m_volMax = viewInfo.m_volMax;
  m_splineInfo = viewInfo.m_splineInfo;
  m_tickSize = viewInfo.m_tickSize;
  m_tickStep = viewInfo.m_tickStep;
  m_labelX = viewInfo.m_labelX;
  m_labelY = viewInfo.m_labelY;
  m_labelZ = viewInfo.m_labelZ;
  m_captions = viewInfo.m_captions;
  m_points = viewInfo.m_points;
  m_paths = viewInfo.m_paths;
  m_pathgroups = viewInfo.m_pathgroups;
  m_trisets = viewInfo.m_trisets;
  m_networks = viewInfo.m_networks;

  m_tagColors = new uchar[1024];
  memcpy(m_tagColors, viewInfo.m_tagColors, 1024);
}


ViewInformation&
ViewInformation::operator=(const ViewInformation& viewInfo)
{
  m_volumeNumber = viewInfo.m_volumeNumber;
  m_volumeNumber2 = viewInfo.m_volumeNumber2;
  m_volumeNumber3 = viewInfo.m_volumeNumber3;
  m_volumeNumber4 = viewInfo.m_volumeNumber4;
  m_stepsizeStill = viewInfo.m_stepsizeStill;
  m_stepsizeDrag = viewInfo.m_stepsizeDrag;
  m_drawBox = viewInfo.m_drawBox;
  m_drawAxis = viewInfo.m_drawAxis;
  m_backgroundColor = viewInfo.m_backgroundColor;
  m_backgroundImageFile = viewInfo.m_backgroundImageFile;
  m_position = viewInfo.m_position;
  m_rotation = viewInfo.m_rotation;
  m_focusDistance = viewInfo.m_focusDistance;
  m_image = viewInfo.m_image;
  m_renderQuality = viewInfo.m_renderQuality;
  m_lightInfo = viewInfo.m_lightInfo;
  m_clipInfo = viewInfo.m_clipInfo;
  m_brickInfo = viewInfo.m_brickInfo;
  m_volMin = viewInfo.m_volMin;
  m_volMax = viewInfo.m_volMax;
  m_splineInfo = viewInfo.m_splineInfo;
  m_tickSize = viewInfo.m_tickSize;
  m_tickStep = viewInfo.m_tickStep;
  m_labelX = viewInfo.m_labelX;
  m_labelY = viewInfo.m_labelY;
  m_labelZ = viewInfo.m_labelZ;
  m_captions = viewInfo.m_captions;
  m_points = viewInfo.m_points;
  m_paths = viewInfo.m_paths;
  m_pathgroups = viewInfo.m_pathgroups;
  m_trisets = viewInfo.m_trisets;
  m_networks = viewInfo.m_networks;
  memcpy(m_tagColors, viewInfo.m_tagColors, 1024);

  return *this;
}

//--------------------------------
//---- load and save -------------
//--------------------------------


void ViewInformation::load(QSettings &cfg) {

  m_brickInfo.clear();
  m_splineInfo.clear();

  cfg.beginGroup("ViewInformation");

  m_volumeNumber = getQSettingsValue(cfg, "volumenumber", m_volumeNumber );
  m_volumeNumber2 = getQSettingsValue(cfg, "volumenumber2", m_volumeNumber2 );
  m_volumeNumber3 = getQSettingsValue(cfg, "volumenumber3", m_volumeNumber3 );
  m_volumeNumber4 = getQSettingsValue(cfg, "volumenumber4", m_volumeNumber4 );
  m_stepsizeStill = getQSettingsValue(cfg, "stepsizestill", m_stepsizeStill );
  m_stepsizeDrag = getQSettingsValue(cfg, "stepsizedrag", m_stepsizeDrag );
  m_drawBox = getQSettingsValue(cfg, "drawbox", m_drawBox );
  m_drawAxis = getQSettingsValue(cfg, "drawaxis", m_drawAxis );
  m_backgroundColor = QVecEdit::toVec( getQSettingsValue(cfg, "backgroundcolor", m_backgroundColor ) );
  m_backgroundImageFile = getQSettingsValue(cfg, "backgroundimage", m_backgroundImageFile );
  m_position = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "position") );
  m_rotation.setAxisAngle( QVecEdit::toVec( getQSettingsValue<QString>(cfg, "rotation_axis") ),
                           getQSettingsValue<qreal>(cfg, "rotation_angle"));
  m_focusDistance = getQSettingsValue(cfg, "focusdistance", m_focusDistance );
  m_image = getQSettingsValue(cfg, "image", m_image );
  m_renderQuality = getQSettingsValue(cfg, "renderquality", m_renderQuality );
  m_volMin = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "volmin ") );
  m_volMax = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "volmax ") );
  m_tickSize = getQSettingsValue(cfg, "tickstep", m_tickSize );
  m_tickStep = getQSettingsValue(cfg, "tickstep", m_tickStep );
  m_labelX = getQSettingsValue(cfg, "labelX", m_labelX );
  m_labelY = getQSettingsValue(cfg, "labelY", m_labelY );
  m_labelZ = getQSettingsValue(cfg, "labelZ", m_labelZ );
  m_tagColors = getQSettingsValue(cfg, "tagcolors",  m_tagColors, 1024);

  m_lightInfo.load(cfg);
  m_clipInfo.load(cfg);

  QSettingsGetValArray(cfg, "Points",  m_points);
  QSettingsLoadArray(cfg, "BrickInformation", m_brickInfo);
  QSettingsLoadArray(cfg, "SplineInformation", m_splineInfo);
  QSettingsLoadArray(cfg, "CaptionObject",  m_captions);
  QSettingsLoadArray(cfg, "PathObject", m_paths);
  QSettingsLoadArray(cfg, "PathGroupObject", m_pathgroups);
  QSettingsLoadArray(cfg, "TrisetInformation", m_trisets);
  QSettingsLoadArray(cfg, "NetworkInformation", m_networks);

  cfg.endGroup();

}





void ViewInformation::save(QSettings &cfg) const {

  cfg.beginGroup("ViewInformation");

  cfg.setValue("volumenumber", m_volumeNumber);
  cfg.setValue("volumenumber2", m_volumeNumber2);
  cfg.setValue("volumenumber3", m_volumeNumber3);
  cfg.setValue("volumenumber4", m_volumeNumber4);
  cfg.setValue("stepsizestill", m_stepsizeStill);
  cfg.setValue("stepsizedrag", m_stepsizeDrag);
  cfg.setValue("drawbox", m_drawBox);
  cfg.setValue("drawaxis", m_drawAxis);
  cfg.setValue("backgroundcolor", QVecEdit::toString(m_backgroundColor));
  cfg.setValue("backgroundimage", m_backgroundImageFile);
  cfg.setValue("position",  QVecEdit::toString(m_position) );
  cfg.setValue("rotation_axis",  QVecEdit::toString(m_rotation.axis()));
  cfg.setValue("rotation_angle",  m_rotation.angle());
  cfg.setValue("focusdistance", m_focusDistance);
  cfg.setValue("image", m_image);
  cfg.setValue("renderquality",  m_renderQuality);
  cfg.setValue("volmin ", QVecEdit::toString(m_volMin));
  cfg.setValue("volmax ", QVecEdit::toString(m_volMax));
  cfg.setValue("ticksize", m_tickSize);
  cfg.setValue("tickstep", m_tickStep);
  cfg.setValue("labelX", m_labelX);
  cfg.setValue("labelY", m_labelY);
  cfg.setValue("labelZ", m_labelZ);
  cfg.setValue("tagcolors", QByteArray(m_tagColors, 1024));

  m_lightInfo.save(cfg);
  m_clipInfo.save(cfg);


  QSettingsSetValArray(cfg, "Points",  m_points);
  QSettingsSaveArray(cfg, "BrickInformation", m_brickInfo);
  QSettingsSaveArray(cfg, "SplineInformation", m_splineInfo);
  QSettingsSaveArray(cfg, "CaptionObject",  m_captions);
  QSettingsSaveArray(cfg, "PathObject", m_paths);
  QSettingsSaveArray(cfg, "PathGroupObject", m_pathgroups);
  QSettingsSaveArray(cfg, "TrisetInformation", m_trisets);
  QSettingsSaveArray(cfg, "NetworkInformation", m_networks);

  cfg.endGroup();

}
