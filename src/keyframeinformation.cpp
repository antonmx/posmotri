#include "global.h"
#include "keyframeinformation.h"
#include "enums.h"
#include "PromotedWidgets.h"
#include <QBuffer>
#include <QDebug>

void KeyFrameInformation::setDrawBox(bool flag) { m_drawBox = flag; }
void KeyFrameInformation::setDrawAxis(bool flag) { m_drawAxis = flag; }
void KeyFrameInformation::setBackgroundColor(Vec col) { m_backgroundColor = col; }
void KeyFrameInformation::setBackgroundImageFile(QString fl) { m_backgroundImageFile = fl; }
void KeyFrameInformation::setFrameNumber(int fn) { m_frameNumber = fn; }
void KeyFrameInformation::setFocusDistance(float fd, float es) { m_focusDistance = fd; m_eyeSeparation = es; }
void KeyFrameInformation::setVolumeNumber(int vn) { m_volumeNumber = vn; }
void KeyFrameInformation::setVolumeNumber2(int vn) { m_volumeNumber2 = vn; }
void KeyFrameInformation::setVolumeNumber3(int vn) { m_volumeNumber3 = vn; }
void KeyFrameInformation::setVolumeNumber4(int vn) { m_volumeNumber4 = vn; }
void KeyFrameInformation::setPosition(Vec pos) { m_position = pos; }
void KeyFrameInformation::setOrientation(Quaternion rot) { m_rotation = rot; }
void KeyFrameInformation::setLut(unsigned char* lut)
{
  if (!m_lut)
    m_lut = new unsigned char[Global::lutSize()*256*256*4];
  memcpy(m_lut, lut, Global::lutSize()*256*256*4);
}
void KeyFrameInformation::setLightInfo(LightingInformation li) { m_lightInfo = li; }
void KeyFrameInformation::setGiLightInfo(GiLightInfo li) { m_giLightInfo = li; }
void KeyFrameInformation::setClipInfo(ClipInformation ci) { m_clipInfo = ci; }
void KeyFrameInformation::setVolumeBounds(Vec bmin, Vec bmax) { m_volMin = bmin; m_volMax = bmax; }
void KeyFrameInformation::setImage(QImage pix) { m_image = pix; }
void KeyFrameInformation::setSplineInfo(QList<SplineInformation> si) { m_splineInfo = si; }
void KeyFrameInformation::setTick(int sz, int st,
				  QString xl, QString yl, QString zl)
{
  m_tickSize = sz;
  m_tickStep = st;
  m_labelX = xl;
  m_labelY = yl;
  m_labelZ = zl;
}
void KeyFrameInformation::setMix(int mv, bool mc, bool mo, bool mt)
{
  m_mixvol = mv;
  m_mixColor = mc;
  m_mixOpacity = mo;
  m_mixTag = mt;
}
void KeyFrameInformation::setBrickInfo(QList<BrickInformation> bi)
{
  m_brickInfo.clear();
  m_brickInfo += bi;
}
void KeyFrameInformation::setMorphTF(bool flag) { m_morphTF = flag; }
void KeyFrameInformation::setCaptions(QList<CaptionObject> co) { m_captions = co; }
void KeyFrameInformation::setColorBars(QList<ColorBarObject> co) { m_colorbars = co; }
void KeyFrameInformation::setScaleBars(QList<ScaleBarObject> co) { m_scalebars = co; }
void KeyFrameInformation::setPoints(QList<Vec> pts, QList<Vec> bpts, int psz, Vec pcol)
{ m_points=pts; m_barepoints=bpts; m_pointSize=psz; m_pointColor=pcol;}
void KeyFrameInformation::setPaths(QList<PathObject> paths) { m_paths = paths; }
void KeyFrameInformation::setGrids(QList<GridObject> grids) { m_grids = grids; }
void KeyFrameInformation::setCrops(QList<CropObject> crops) { m_crops = crops; }
void KeyFrameInformation::setPathGroups(QList<PathGroupObject> paths) { m_pathgroups = paths; }
void KeyFrameInformation::setTrisets(QList<TrisetInformation> tinfo) { m_trisets = tinfo; }
void KeyFrameInformation::setNetworks(QList<NetworkInformation> ninfo) { m_networks = ninfo; }
void KeyFrameInformation::setTagColors(unsigned char* tc) { memcpy(m_tagColors, tc, 1024); }
void KeyFrameInformation::setPruneBuffer(QByteArray pb) { m_pruneBuffer = pb; }
void KeyFrameInformation::setPruneBlend(bool pb) { m_pruneBlend = pb; }


bool KeyFrameInformation::drawBox() { return m_drawBox; }
bool KeyFrameInformation::drawAxis() { return m_drawAxis; }
Vec KeyFrameInformation::backgroundColor() { return m_backgroundColor; }
QString KeyFrameInformation::backgroundImageFile() { return m_backgroundImageFile; }
int KeyFrameInformation::frameNumber() { return m_frameNumber; }
float KeyFrameInformation::focusDistance() { return m_focusDistance; }
float KeyFrameInformation::eyeSeparation() { return m_eyeSeparation; }
int KeyFrameInformation::volumeNumber() { return m_volumeNumber; }
int KeyFrameInformation::volumeNumber2() { return m_volumeNumber2; }
int KeyFrameInformation::volumeNumber3() { return m_volumeNumber3; }
int KeyFrameInformation::volumeNumber4() { return m_volumeNumber4; }
Vec KeyFrameInformation::position() { return m_position; }
Quaternion KeyFrameInformation::orientation() { return m_rotation; }
unsigned char* KeyFrameInformation::lut() { return m_lut; }
LightingInformation KeyFrameInformation::lightInfo() { return m_lightInfo; }
GiLightInfo KeyFrameInformation::giLightInfo() { return m_giLightInfo; }
ClipInformation KeyFrameInformation::clipInfo() { return m_clipInfo; }
void KeyFrameInformation::volumeBounds(Vec &bmin, Vec &bmax) { bmin = m_volMin; bmax = m_volMax; }
QImage KeyFrameInformation::image() { return m_image; }
QList<SplineInformation> KeyFrameInformation::splineInfo() { return m_splineInfo; }
void KeyFrameInformation::getTick(int &sz, int &st,
				  QString &xl, QString &yl, QString &zl)
{
  sz = m_tickSize;
  st = m_tickStep;
  xl = m_labelX;
  yl = m_labelY;
  zl = m_labelZ;
}
void KeyFrameInformation::getMix(int &mv, bool &mc, bool &mo, bool &mt)
{
  mv = m_mixvol;
  mc = m_mixColor;
  mo = m_mixOpacity;
  mt = m_mixTag;
}
QList<BrickInformation> KeyFrameInformation::brickInfo() { return m_brickInfo; }
bool KeyFrameInformation::morphTF() { return m_morphTF; }
QList<CaptionObject> KeyFrameInformation::captions() { return m_captions; }
QList<ColorBarObject> KeyFrameInformation::colorbars() { return m_colorbars; }
QList<ScaleBarObject> KeyFrameInformation::scalebars() { return m_scalebars; }
QList<Vec> KeyFrameInformation::points() { return m_points; }
QList<Vec> KeyFrameInformation::barepoints() { return m_barepoints; }
int KeyFrameInformation::pointSize() { return m_pointSize; }
Vec KeyFrameInformation::pointColor() { return m_pointColor; }
QList<PathObject> KeyFrameInformation::paths() { return m_paths; }
QList<GridObject> KeyFrameInformation::grids() { return m_grids; }
QList<CropObject> KeyFrameInformation::crops() { return m_crops; }
QList<PathGroupObject> KeyFrameInformation::pathgroups() { return m_pathgroups; }
QList<TrisetInformation> KeyFrameInformation::trisets() { return m_trisets; }
QList<NetworkInformation> KeyFrameInformation::networks() { return m_networks; }
unsigned char* KeyFrameInformation::tagColors() { return m_tagColors; }
QByteArray KeyFrameInformation::pruneBuffer() { return m_pruneBuffer; }
bool KeyFrameInformation::pruneBlend() { return m_pruneBlend; }


// -- keyframe interpolation parameters
void KeyFrameInformation::setInterpBGColor(int i) {m_interpBGColor = i;}
void KeyFrameInformation::setInterpCaptions(int i) {m_interpCaptions = i;}
void KeyFrameInformation::setInterpFocus(int i) {m_interpFocus = i;}
void KeyFrameInformation::setInterpTagColors(int i) {m_interpTagColors = i;}
void KeyFrameInformation::setInterpTickInfo(int i) {m_interpTickInfo = i;}
void KeyFrameInformation::setInterpVolumeBounds(int i) {m_interpVolumeBounds = i;}
void KeyFrameInformation::setInterpCameraPosition(int i) {m_interpCameraPosition = i;}
void KeyFrameInformation::setInterpCameraOrientation(int i) {m_interpCameraOrientation = i;}
void KeyFrameInformation::setInterpBrickInfo(int i) {m_interpBrickInfo = i;}
void KeyFrameInformation::setInterpClipInfo(int i) {m_interpClipInfo = i;}
void KeyFrameInformation::setInterpLightInfo(int i) {m_interpLightInfo = i;}
void KeyFrameInformation::setInterpGiLightInfo(int i) {m_interpGiLightInfo = i;}
void KeyFrameInformation::setInterpTF(int i) {m_interpTF = i;}
void KeyFrameInformation::setInterpCrop(int i) {m_interpCrop = i;}
void KeyFrameInformation::setInterpMop(int i) {m_interpMop = i;}

int KeyFrameInformation::interpBGColor() { return m_interpBGColor; }
int KeyFrameInformation::interpCaptions() { return m_interpCaptions; }
int KeyFrameInformation::interpFocus() { return m_interpFocus; }
int KeyFrameInformation::interpTagColors() { return m_interpTagColors; }
int KeyFrameInformation::interpTickInfo() { return m_interpTickInfo; }
int KeyFrameInformation::interpVolumeBounds() { return m_interpVolumeBounds; }
int KeyFrameInformation::interpCameraPosition() { return m_interpCameraPosition; }
int KeyFrameInformation::interpCameraOrientation() { return m_interpCameraOrientation; }
int KeyFrameInformation::interpBrickInfo() { return m_interpBrickInfo; }
int KeyFrameInformation::interpClipInfo() { return m_interpClipInfo; }
int KeyFrameInformation::interpLightInfo() { return m_interpLightInfo; }
int KeyFrameInformation::interpGiLightInfo() { return m_interpGiLightInfo; }
int KeyFrameInformation::interpTF() { return m_interpTF; }
int KeyFrameInformation::interpCrop() { return m_interpCrop; }
int KeyFrameInformation::interpMop() { return m_interpMop; }

bool
KeyFrameInformation::hasCaption(QStringList str)
{
  for(int i=0; i<m_captions.size(); i++)
    if (m_captions[i].hasCaption(str))
      return true;

  for(int i=0; i<m_paths.size(); i++)
    if (m_paths[i].hasCaption(str))
      return true;

  return false;
}

KeyFrameInformation::KeyFrameInformation()
{
  m_drawBox = false;
  m_drawAxis = false;
  m_backgroundColor = Vec(0,0,0);
  m_backgroundImageFile.clear();
  m_frameNumber = 0;
  m_focusDistance = 0;
  m_eyeSeparation = 0.062;
  m_volumeNumber = 0;
  m_volumeNumber2 = 0;
  m_volumeNumber3 = 0;
  m_volumeNumber4 = 0;
  m_position = Vec(0,0,0);
  m_rotation = Quaternion(Vec(1,0,0), 0);
  //m_lut = new unsigned char[Global::lutSize()*256*256*4];
  m_lut = 0;
  m_tagColors = new unsigned char[1024];
  m_pruneBuffer.clear();
  m_pruneBlend = false;
  m_volMin = m_volMax = Vec(0,0,0);
  m_image = QImage(100, 100, QImage::Format_RGB32);
  m_clipInfo.clear();
  m_tickSize = 6;
  m_tickStep = 10;
  m_labelX = "X";
  m_labelY = "Y";
  m_labelZ = "Z";
  m_mixvol = 0;
  m_mixColor = false;
  m_mixOpacity = false;
  m_mixTag = false;
  m_brickInfo.clear();
  m_splineInfo.clear();
  m_morphTF = false;
  m_captions.clear();
  m_colorbars.clear();
  m_scalebars.clear();
  m_points.clear();
  m_barepoints.clear();
  m_pointSize = 10;
  m_pointColor = Vec(0.0f, 0.5f, 1.0f);
  m_paths.clear();
  m_grids.clear();
  m_crops.clear();
  m_pathgroups.clear();
  m_trisets.clear();
  m_networks.clear();

  m_interpBGColor = Enums::KFIT_Linear;
  m_interpCaptions = Enums::KFIT_Linear;
  m_interpFocus = Enums::KFIT_Linear;
  m_interpTagColors = Enums::KFIT_Linear;
  m_interpTickInfo = Enums::KFIT_Linear;
  m_interpVolumeBounds = Enums::KFIT_Linear;
  m_interpCameraPosition = Enums::KFIT_Linear;
  m_interpCameraOrientation = Enums::KFIT_Linear;
  m_interpBrickInfo = Enums::KFIT_Linear;
  m_interpClipInfo = Enums::KFIT_Linear;
  m_interpLightInfo = Enums::KFIT_Linear;
  m_interpGiLightInfo = Enums::KFIT_None;
  m_interpTF = Enums::KFIT_Linear;
  m_interpCrop = Enums::KFIT_Linear;
  m_interpMop = Enums::KFIT_None;
}

void
KeyFrameInformation::clear()
{
  m_drawBox = false;
  m_drawAxis = false;
  m_backgroundColor = Vec(0,0,0);
  m_backgroundImageFile.clear();
  m_frameNumber = 0;
  m_focusDistance = 0;
  m_eyeSeparation = 0.062;
  m_volumeNumber = 0;
  m_volumeNumber2 = 0;
  m_volumeNumber3 = 0;
  m_volumeNumber4 = 0;
  m_position = Vec(0,0,0);
  m_rotation = Quaternion(Vec(1,0,0), 0);
  if (m_lut) delete [] m_lut;
  m_lut = 0;
  //m_lut = new unsigned char[Global::lutSize()*256*256*4];
  if (m_tagColors) delete [] m_tagColors;
  m_tagColors = new unsigned char[1024];
  m_pruneBuffer.clear();
  m_pruneBlend = false;
  m_volMin = m_volMax = Vec(0,0,0);
  m_image = QImage(100, 100, QImage::Format_RGB32);
  m_lightInfo.clear();
  m_giLightInfo.clear();
  m_clipInfo.clear();
  m_brickInfo.clear();
  m_tickSize = 6;
  m_tickStep = 10;
  m_labelX = "X";
  m_labelY = "Y";
  m_labelZ = "Z";
  m_mixvol = 0;
  m_mixColor = false;
  m_mixOpacity = false;
  m_mixTag = false;
  m_splineInfo.clear();
  m_morphTF = false;
  m_captions.clear();
  m_colorbars.clear();
  m_scalebars.clear();
  m_points.clear();
  m_barepoints.clear();
  m_pointSize = 10;
  m_pointColor = Vec(0.0f, 0.5f, 1.0f);
  m_paths.clear();
  m_grids.clear();
  m_crops.clear();
  m_pathgroups.clear();
  m_trisets.clear();
  m_networks.clear();

  m_interpBGColor = Enums::KFIT_Linear;
  m_interpCaptions = Enums::KFIT_Linear;
  m_interpFocus = Enums::KFIT_Linear;
  m_interpTagColors = Enums::KFIT_Linear;
  m_interpTickInfo = Enums::KFIT_Linear;
  m_interpVolumeBounds = Enums::KFIT_Linear;
  m_interpCameraPosition = Enums::KFIT_Linear;
  m_interpCameraOrientation = Enums::KFIT_Linear;
  m_interpBrickInfo = Enums::KFIT_Linear;
  m_interpClipInfo = Enums::KFIT_Linear;
  m_interpLightInfo = Enums::KFIT_Linear;
  m_interpGiLightInfo = Enums::KFIT_None;
  m_interpTF = Enums::KFIT_Linear;
  m_interpCrop = Enums::KFIT_Linear;
  m_interpMop = Enums::KFIT_None;
}

KeyFrameInformation::KeyFrameInformation(const KeyFrameInformation& kfi)
{
  m_drawBox = kfi.m_drawBox;
  m_drawAxis = kfi.m_drawAxis;

  m_backgroundColor = kfi.m_backgroundColor;
  m_backgroundImageFile = kfi.m_backgroundImageFile;

  m_frameNumber = kfi.m_frameNumber;
  m_focusDistance = kfi.m_focusDistance;

  m_eyeSeparation = kfi.m_eyeSeparation;

  m_volumeNumber = kfi.m_volumeNumber;
  m_volumeNumber2 = kfi.m_volumeNumber2;
  m_volumeNumber3 = kfi.m_volumeNumber3;
  m_volumeNumber4 = kfi.m_volumeNumber4;

  m_position = kfi.m_position;
  m_rotation = kfi.m_rotation;

  m_lut = new unsigned char[Global::lutSize()*256*256*4];
  memcpy(m_lut, kfi.m_lut, Global::lutSize()*256*256*4);

  m_tagColors = new unsigned char[1024];
  memcpy(m_tagColors, kfi.m_tagColors, 1024);

  m_pruneBuffer = kfi.m_pruneBuffer;
  m_pruneBlend = kfi.m_pruneBlend;

  m_lightInfo = kfi.m_lightInfo;
  m_giLightInfo = kfi.m_giLightInfo;
  m_clipInfo = kfi.m_clipInfo;

  m_volMin = kfi.m_volMin;
  m_volMax = kfi.m_volMax;

  m_image = kfi.m_image;

  m_brickInfo = kfi.m_brickInfo;

  m_tickSize = kfi.m_tickSize;
  m_tickStep = kfi.m_tickStep;
  m_labelX = kfi.m_labelX;
  m_labelY = kfi.m_labelY;
  m_labelZ = kfi.m_labelZ;

  m_mixvol = kfi.m_mixvol;
  m_mixColor = kfi.m_mixColor;
  m_mixOpacity = kfi.m_mixOpacity;
  m_mixTag = kfi.m_mixTag;

  m_splineInfo = kfi.m_splineInfo;
  m_morphTF = kfi.m_morphTF;

  m_captions = kfi.m_captions;
  m_colorbars = kfi.m_colorbars;
  m_scalebars = kfi.m_scalebars;
  m_points = kfi.m_points;
  m_barepoints = kfi.m_barepoints;
  m_pointSize = kfi.m_pointSize;
  m_pointColor = kfi.m_pointColor;
  m_paths = kfi.m_paths;
  m_grids = kfi.m_grids;
  m_crops = kfi.m_crops;
  m_pathgroups = kfi.m_pathgroups;
  m_trisets = kfi.m_trisets;
  m_networks = kfi.m_networks;

  m_interpBGColor = kfi.m_interpBGColor;
  m_interpCaptions = kfi.m_interpCaptions;
  m_interpFocus = kfi.m_interpFocus;
  m_interpTagColors = kfi.m_interpTagColors;
  m_interpTickInfo = kfi.m_interpTickInfo;
  m_interpVolumeBounds = kfi.m_interpVolumeBounds;
  m_interpCameraPosition = kfi.m_interpCameraPosition;
  m_interpCameraOrientation = kfi.m_interpCameraOrientation;
  m_interpBrickInfo = kfi.m_interpBrickInfo;
  m_interpClipInfo = kfi.m_interpClipInfo;
  m_interpLightInfo = kfi.m_interpLightInfo;
  m_interpGiLightInfo = kfi.m_interpGiLightInfo;
  m_interpTF = kfi.m_interpTF;
  m_interpCrop = kfi.m_interpCrop;
  m_interpMop = kfi.m_interpMop;
}

KeyFrameInformation::~KeyFrameInformation()
{
  if (m_lut)
    delete [] m_lut;
  if (m_tagColors)
    delete [] m_tagColors;
  m_clipInfo.clear();
  m_brickInfo.clear();
  m_labelX.clear();
  m_labelY.clear();
  m_labelZ.clear();
  m_splineInfo.clear();
  m_captions.clear();
  m_colorbars.clear();
  m_scalebars.clear();
  m_points.clear();
  m_barepoints.clear();
  m_paths.clear();
  m_grids.clear();
  m_crops.clear();
  m_pathgroups.clear();
  m_trisets.clear();
  m_networks.clear();
  m_pruneBuffer.clear();
  m_pruneBlend = false;
}

KeyFrameInformation&
KeyFrameInformation::operator=(const KeyFrameInformation& kfi)
{
  m_drawBox = kfi.m_drawBox;
  m_drawAxis = kfi.m_drawAxis;

  m_backgroundColor = kfi.m_backgroundColor;
  m_backgroundImageFile = kfi.m_backgroundImageFile;

  m_frameNumber = kfi.m_frameNumber;
  m_focusDistance = kfi.m_focusDistance;

  m_eyeSeparation = kfi.m_eyeSeparation;

  m_volumeNumber = kfi.m_volumeNumber;
  m_volumeNumber2 = kfi.m_volumeNumber2;
  m_volumeNumber3 = kfi.m_volumeNumber3;
  m_volumeNumber4 = kfi.m_volumeNumber4;

  m_position = kfi.m_position;
  m_rotation = kfi.m_rotation;

  if (!m_lut)
    m_lut = new unsigned char[Global::lutSize()*256*256*4];
  memcpy(m_lut, kfi.m_lut, Global::lutSize()*256*256*4);

  memcpy(m_tagColors, kfi.m_tagColors, 1024);

  m_pruneBuffer = kfi.m_pruneBuffer;
  m_pruneBlend = kfi.m_pruneBlend;

  m_lightInfo = kfi.m_lightInfo;
  m_giLightInfo = kfi.m_giLightInfo;
  m_clipInfo = kfi.m_clipInfo;

  m_volMin = kfi.m_volMin;
  m_volMax = kfi.m_volMax;

  m_image = kfi.m_image;

  m_brickInfo = kfi.m_brickInfo;

  m_tickSize = kfi.m_tickSize;
  m_tickStep = kfi.m_tickStep;
  m_labelX = kfi.m_labelX;
  m_labelY = kfi.m_labelY;
  m_labelZ = kfi.m_labelZ;

  m_mixvol = kfi.m_mixvol;
  m_mixColor = kfi.m_mixColor;
  m_mixOpacity = kfi.m_mixOpacity;
  m_mixTag = kfi.m_mixTag;

  m_splineInfo = kfi.m_splineInfo;
  m_morphTF = kfi.m_morphTF;

  m_captions = kfi.m_captions;
  m_colorbars = kfi.m_colorbars;
  m_scalebars = kfi.m_scalebars;
  m_points = kfi.m_points;
  m_barepoints = kfi.m_barepoints;
  m_pointSize = kfi.m_pointSize;
  m_pointColor = kfi.m_pointColor;
  m_paths = kfi.m_paths;
  m_grids = kfi.m_grids;
  m_crops = kfi.m_crops;
  m_pathgroups = kfi.m_pathgroups;
  m_trisets = kfi.m_trisets;
  m_networks = kfi.m_networks;

  m_interpBGColor = kfi.m_interpBGColor;
  m_interpCaptions = kfi.m_interpCaptions;
  m_interpFocus = kfi.m_interpFocus;
  m_interpTagColors = kfi.m_interpTagColors;
  m_interpTickInfo = kfi.m_interpTickInfo;
  m_interpVolumeBounds = kfi.m_interpVolumeBounds;
  m_interpCameraPosition = kfi.m_interpCameraPosition;
  m_interpCameraOrientation = kfi.m_interpCameraOrientation;
  m_interpBrickInfo = kfi.m_interpBrickInfo;
  m_interpClipInfo = kfi.m_interpClipInfo;
  m_interpLightInfo = kfi.m_interpLightInfo;
  m_interpGiLightInfo = kfi.m_interpGiLightInfo;
  m_interpTF = kfi.m_interpTF;
  m_interpCrop = kfi.m_interpCrop;
  m_interpMop = kfi.m_interpMop;

  return *this;
}

//--------------------------------
//---- load and save -------------
//--------------------------------



void KeyFrameInformation::save(QSettings & cfg) const {

  cfg.beginGroup("KeyFrameInformation");

  cfg.setValue("framenumber", m_frameNumber);
  cfg.setValue("drawbox", m_drawBox);
  cfg.setValue("drawaxis", m_drawAxis);
  cfg.setValue("backgroundcolor", QVecEdit::toString(m_backgroundColor));
  cfg.setValue("backgroundimage",  m_backgroundImageFile);
  cfg.setValue("morphtf", m_morphTF);
  cfg.setValue("focusdistance", m_focusDistance);
  cfg.setValue("eyeseparation", m_eyeSeparation);
  cfg.setValue("volumenumber", m_volumeNumber);
  cfg.setValue("volumenumber2", m_volumeNumber2);
  cfg.setValue("volumenumber3", m_volumeNumber3);
  cfg.setValue("volumenumber4", m_volumeNumber4);
  cfg.setValue("volmin", QVecEdit::toString(m_volMin));
  cfg.setValue("volmax", QVecEdit::toString(m_volMax));
  cfg.setValue("position",  QVecEdit::toString(m_position));
  cfg.setValue("rotation_axis",  QVecEdit::toString(m_rotation.axis()));
  cfg.setValue("rotation_angle",  m_rotation.angle());
  cfg.setValue("image", m_image);
  cfg.setValue("ticksize", m_tickSize);
  cfg.setValue("tickstep", m_tickStep);
  cfg.setValue("labelX", m_labelX);
  cfg.setValue("labelY", m_labelY);
  cfg.setValue("labelZ", m_labelZ);
  cfg.setValue("mixinfo", m_mixvol);
  cfg.setValue("mixcolor",  m_mixColor);
  cfg.setValue("mixopacity", m_mixOpacity);
  cfg.setValue("mixtag", m_mixTag);
  cfg.setValue("interpbgcolor", m_interpBGColor);
  cfg.setValue("interpcaptions", m_interpCaptions);
  cfg.setValue("interpfocus", m_interpFocus);
  cfg.setValue("interptagcolors", m_interpTagColors);
  cfg.setValue("interptickinfo", m_interpTickInfo);
  cfg.setValue("interpvolumebounds", m_interpVolumeBounds);
  cfg.setValue("interpcamerapos", m_interpCameraPosition);
  cfg.setValue("interpcamerarot", m_interpCameraOrientation);
  cfg.setValue("interpbrickinfo", m_interpBrickInfo);
  cfg.setValue("interpclipinfo", m_interpClipInfo);
  cfg.setValue("interplightinfo", m_interpLightInfo);
  cfg.setValue("interpgilightinfo", m_interpGiLightInfo);
  cfg.setValue("interptf", m_interpTF);
  cfg.setValue("interpcrop", m_interpCrop);
  cfg.setValue("interpmop", m_interpMop);
  cfg.setValue("pointsize", m_pointSize);
  cfg.setValue("pointcolor",  QVecEdit::toString(m_pointColor));
  cfg.setValue("tagcolors",  QByteArray( (const char*) m_tagColors, 1024) );
  if (m_lut)
    cfg.setValue("lookuptable",
      QByteArray( (const char*) m_lut,  Global::lutSize()*256*256*4) );

  m_lightInfo.save(cfg);
  m_giLightInfo.save(cfg);
  m_clipInfo.save(cfg);

  QSettingsSetValArray(cfg, "Points",  m_points);
  QSettingsSetValArray(cfg, "BarePoints",  m_barepoints);

  QSettingsSaveArray(cfg, "BrickInformation", m_brickInfo);
  QSettingsSaveArray(cfg, "SplineInformation", m_splineInfo);
  QSettingsSaveArray(cfg, "CaptionObject",  m_captions);
  QSettingsSaveArray(cfg, "ColorBarObject", m_colorbars);
  QSettingsSaveArray(cfg, "ScaleBarObject", m_scalebars);
  QSettingsSaveArray(cfg, "PathObject", m_paths);
  QSettingsSaveArray(cfg, "GridObject", m_grids);
  QSettingsSaveArray(cfg, "CropObject", m_crops);
  QSettingsSaveArray(cfg, "PathGroupObject", m_pathgroups);
  QSettingsSaveArray(cfg, "TrisetInformation", m_trisets);
  QSettingsSaveArray(cfg, "NetworkInformation", m_networks);

  if (!m_pruneBuffer.isEmpty()) {
    cfg.setValue("pruneblend", m_pruneBlend);
    cfg.setValue("prunebuffer", m_pruneBuffer);
  }

  cfg.endGroup();

}





void KeyFrameInformation::load(QSettings & cfg) {

  m_brickInfo.clear();
  m_pruneBuffer.clear();
  m_pruneBlend = false;

  m_interpBGColor = Enums::KFIT_Linear;
  m_interpCaptions = Enums::KFIT_Linear;
  m_interpFocus = Enums::KFIT_Linear;
  m_interpTagColors = Enums::KFIT_Linear;
  m_interpTickInfo = Enums::KFIT_Linear;
  m_interpVolumeBounds = Enums::KFIT_Linear;
  m_interpCameraPosition = Enums::KFIT_Linear;
  m_interpCameraOrientation = Enums::KFIT_Linear;
  m_interpBrickInfo = Enums::KFIT_Linear;
  m_interpClipInfo = Enums::KFIT_Linear;
  m_interpLightInfo = Enums::KFIT_Linear;
  m_interpGiLightInfo = Enums::KFIT_None;
  m_interpTF = Enums::KFIT_Linear;
  m_interpCrop = Enums::KFIT_Linear;
  m_interpMop = Enums::KFIT_None;

  cfg.beginGroup("KeyFrameInformation");

  m_frameNumber = getQSettingsValue(cfg, "framenumber", m_frameNumber );
  m_drawBox = getQSettingsValue(cfg, "drawbox", m_drawBox );
  m_drawAxis = getQSettingsValue(cfg, "drawaxis", m_drawAxis );
  m_backgroundColor = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "backgroundColor") );
  m_backgroundImageFile = getQSettingsValue(cfg, "backgroundimage", m_backgroundImageFile );
  m_morphTF = getQSettingsValue(cfg, "morphtf", m_morphTF );
  m_focusDistance = getQSettingsValue(cfg, "focusdistance", m_focusDistance );
  m_eyeSeparation = getQSettingsValue(cfg, "eyeseparation", m_eyeSeparation );
  m_volumeNumber = getQSettingsValue(cfg, "volumenumber", m_volumeNumber );
  m_volumeNumber2 = getQSettingsValue(cfg, "volumenumber2", m_volumeNumber2 );
  m_volumeNumber3 = getQSettingsValue(cfg, "volumenumber3", m_volumeNumber3 );
  m_volumeNumber4 = getQSettingsValue(cfg, "volumenumber4", m_volumeNumber4 );
  m_volMin = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "volmin") );
  m_volMax = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "volmax") );
  m_position = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "position") );
  m_rotation.setAxisAngle( QVecEdit::toVec( getQSettingsValue<QString>(cfg, "rotation_axis") ),
                           getQSettingsValue<qreal>(cfg, "rotation_angle"));
  m_image = getQSettingsValue(cfg, "image", m_image );
  m_tickSize = getQSettingsValue(cfg, "tickstep", m_tickSize );
  m_tickStep = getQSettingsValue(cfg, "tickstep", m_tickStep );
  m_labelX = getQSettingsValue(cfg, "labelX", m_labelX );
  m_labelY = getQSettingsValue(cfg, "labelY", m_labelY );
  m_labelZ = getQSettingsValue(cfg, "labelZ", m_labelZ );
  m_mixvol = getQSettingsValue(cfg, "mixinfo", m_mixvol );
  m_mixColor = getQSettingsValue(cfg, "mixcolor", m_mixColor );
  m_mixOpacity = getQSettingsValue(cfg, "mixopacity", m_mixOpacity );
  m_mixTag = getQSettingsValue(cfg, "mixtag", m_mixTag );
  m_interpBGColor = getQSettingsValue(cfg, "interpbgcolor", m_interpBGColor );
  m_interpCaptions = getQSettingsValue(cfg, "interpcaptions", m_interpCaptions );
  m_interpFocus = getQSettingsValue(cfg, "interpfocus", m_interpFocus );
  m_interpTagColors = getQSettingsValue(cfg, "interptagcolors", m_interpTagColors );
  m_interpTickInfo = getQSettingsValue(cfg, "interptickinfo", m_interpTickInfo );
  m_interpVolumeBounds = getQSettingsValue(cfg, "interpvolumebounds", m_interpVolumeBounds );
  m_interpCameraPosition = getQSettingsValue(cfg, "interpcamerapos", m_interpCameraPosition );
  m_interpCameraOrientation = getQSettingsValue(cfg, "interpcamerarot", m_interpCameraOrientation );
  m_interpBrickInfo = getQSettingsValue(cfg, "interpbrickinfo", m_interpBrickInfo );
  m_interpClipInfo = getQSettingsValue(cfg, "interpclipinfo", m_interpClipInfo );
  m_interpLightInfo = getQSettingsValue(cfg, "interplightinfo", m_interpLightInfo );
  m_interpGiLightInfo = getQSettingsValue(cfg, "interpgilightinfo", m_interpGiLightInfo );
  m_interpTF = getQSettingsValue(cfg, "interptf", m_interpTF );
  m_interpCrop = getQSettingsValue(cfg, "interpcrop", m_interpCrop );
  m_interpMop = getQSettingsValue(cfg, "interpmop", m_interpMop );
  m_pointSize = getQSettingsValue(cfg, "pointsize", m_pointSize );
  m_pointColor = QVecEdit::toVec( getQSettingsValue<QString>(cfg, "m_pointColor") );
  m_tagColors = getQSettingsValue(cfg, "tagcolors",  m_tagColors,  1024);
  if ( cfg.contains("lookuptable") ) {
    if (!m_lut)
      m_lut = new unsigned char[Global::lutSize()*256*256*4];
    m_lut = getQSettingsValue(cfg, "lookuptable",  m_lut,  Global::lutSize()*256*256*4);
  }

  m_lightInfo.load(cfg);
  m_giLightInfo.load(cfg);
  m_clipInfo.load(cfg);

  QSettingsGetValArray(cfg, "Points",  m_points);
  QSettingsGetValArray(cfg, "BarePoints",  m_barepoints);

  QSettingsLoadArray(cfg, "BrickInformation", m_brickInfo);
  QSettingsLoadArray(cfg, "SplineInformation", m_splineInfo);
  QSettingsLoadArray(cfg, "CaptionObject",  m_captions);
  QSettingsLoadArray(cfg, "ColorBarObject", m_colorbars);
  QSettingsLoadArray(cfg, "ScaleBarObject", m_scalebars);
  QSettingsLoadArray(cfg, "PathObject", m_paths);
  QSettingsLoadArray(cfg, "PathGroupObject", m_pathgroups);
  QSettingsLoadArray(cfg, "GridObject", m_grids);
  QSettingsLoadArray(cfg, "CropObject", m_crops);
  QSettingsLoadArray(cfg, "TrisetInformation", m_trisets);
  QSettingsLoadArray(cfg, "NetworkInformation", m_networks);

  if (cfg.contains("pruneblend")) {
    m_pruneBlend = getQSettingsValue(cfg, "pruneblend",  m_pruneBlend);
    m_pruneBuffer = getQSettingsValue(cfg, "prunebuffer", m_pruneBuffer);
  }

  cfg.endGroup();

}


