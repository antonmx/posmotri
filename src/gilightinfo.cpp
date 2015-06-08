#include "gilightinfo.h"
#include "PromotedWidgets.h"

using namespace qglviewer;

GiLightInfo::GiLightInfo() {
  clear();
}

GiLightInfo::~GiLightInfo() {
  clear();
}

void GiLightInfo::clear() {
  gloInfo.clear();

  basicLight = false;
  applyClip = false;
  applyCrop = false;
  onlyAOLight = false;
  lightLod = 2;
  lightDiffuse = 1;

  aoLightColor = Vec(1,1,1);
  aoRad = 2;
  aoTimes = 5;
  aoFrac = 0.7;
  aoDensity1 = 0.3;
  aoDensity2 = 1.0;

  emisTF = -1;
  emisDecay = 1.0;
  emisBoost = 1;
  emisTimes = 1;
}

GiLightInfo& GiLightInfo::operator=(const GiLightInfo& gi) {

  gloInfo = gi.gloInfo;

  basicLight = gi.basicLight;
  applyClip = gi.applyClip;
  applyCrop = gi.applyCrop;
  onlyAOLight = gi.onlyAOLight;
  lightLod = gi.lightLod;
  lightDiffuse = gi.lightDiffuse;

  aoLightColor = gi.aoLightColor;
  aoRad = gi.aoRad;
  aoTimes = gi.aoTimes;
  aoFrac = gi.aoFrac;
  aoDensity1 = gi.aoDensity1;
  aoDensity2 = gi.aoDensity2;

  emisTF = gi.emisTF;
  emisDecay = gi.emisDecay;
  emisBoost = gi.emisBoost;
  emisTimes = gi.emisTimes;

  return *this;

}

GiLightInfo GiLightInfo::interpolate(const GiLightInfo & gi1, const GiLightInfo & gi2, float frc) {

  GiLightInfo gi;

  gi.gloInfo = GiLightObjectInfo::interpolate(gi1.gloInfo, gi2.gloInfo, frc);

  gi.basicLight = gi1.basicLight;
  gi.applyClip = gi1.applyClip;
  gi.applyCrop = gi1.applyCrop;
  gi.onlyAOLight = gi1.onlyAOLight;

  gi.lightLod = (1.0-frc)*gi1.lightLod + frc*gi2.lightLod;
  gi.lightDiffuse = (1.0-frc)*gi1.lightDiffuse + frc*gi2.lightDiffuse;

  gi.aoLightColor = (1.0-frc)*gi1.aoLightColor + frc*gi2.aoLightColor;
  gi.aoRad = (1.0-frc)*gi1.aoRad + frc*gi2.aoRad;
  gi.aoTimes = (1.0-frc)*gi1.aoTimes + frc*gi2.aoTimes;
  gi.aoFrac = (1.0-frc)*gi1.aoFrac + frc*gi2.aoFrac;
  gi.aoDensity1 = (1.0-frc)*gi1.aoDensity1 + frc*gi2.aoDensity1;
  gi.aoDensity2 = (1.0-frc)*gi1.aoDensity2 + frc*gi2.aoDensity2;

  gi.emisTF = gi1.emisTF;
  gi.emisDecay = (1.0-frc)*gi1.emisDecay + frc*gi2.emisDecay;
  gi.emisBoost = (1.0-frc)*gi1.emisBoost + frc*gi2.emisBoost;
  gi.emisTimes = (1.0-frc)*gi1.emisTimes + frc*gi2.emisTimes;

  return gi;

}


void GiLightInfo::load(const QConfigMe & cfg) {
  gloInfo.clear();
  cfg.beginGroup("GiLightInfo");
  cfg.getValue("basiclight", basicLight);
  cfg.getValue("applyclip", applyClip);
  cfg.getValue("applycrop", applyCrop);
  cfg.getValue("onlyaolight", onlyAOLight);
  cfg.getValue("lightlod", lightLod);
  cfg.getValue("lightdiffuse", lightDiffuse);
  cfg.getValue("aolightcolor", aoLightColor);
  cfg.getValue("aorad", aoRad);
  cfg.getValue("aotimes", aoTimes);
  cfg.getValue("aofrac", aoFrac);
  cfg.getValue("aodensity1", aoDensity1);
  cfg.getValue("aodensity2", aoDensity2);
  cfg.getValue("emistf", emisTF);
  cfg.getValue("emisdecay", emisDecay);
  cfg.getValue("emisboost", emisBoost);
  cfg.getValue("emistimes", emisTimes);
  cfg.getClassArray("GlowInfo", gloInfo);
  cfg.endGroup();
}





void GiLightInfo::save(QConfigMe & cfg) const {
  cfg.beginGroup("GiLightInfo");
  cfg.setValue("basiclight", basicLight);
  cfg.setValue("applyclip", applyClip);
  cfg.setValue("applycrop", applyCrop);
  cfg.setValue("onlyaolight", onlyAOLight);
  cfg.setValue("lightlod", lightLod);
  cfg.setValue("lightdiffuse", lightDiffuse);
  cfg.setValue("aolightcolor", aoLightColor);
  cfg.setValue("aorad", aoRad);
  cfg.setValue("aotimes", aoTimes);
  cfg.setValue("aofrac", aoFrac);
  cfg.setValue("aodensity1", aoDensity1);
  cfg.setValue("aodensity2", aoDensity2);
  cfg.setValue("emistf", emisTF);
  cfg.setValue("emisdecay", emisDecay);
  cfg.setValue("emisboost", emisBoost);
  cfg.setValue("emistimes", emisTimes);
  cfg.setClassArray("GlowInfo", gloInfo);
  cfg.endGroup();
}
