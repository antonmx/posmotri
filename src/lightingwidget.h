#ifndef LIGHTINGWIDGET_H
#define LIGHTINGWIDGET_H

#include "lightinginformation.h"
#include "ui_lightingwidget.h"
#include "PromotedWidgets.h"

class LightingWidget : public QWidget {
 Q_OBJECT;

 public :
  LightingWidget(QWidget *parent=NULL);

 signals :
  void applyLighting(bool);
  void applyEmissive(bool);
  void highlights(Highlights);

  void applyShadow(bool);
  void shadowBlur(float);
  void shadowScale(float);
  void shadowFOV(float);
  void shadowIntensity(float);

  void applyColoredShadow(bool);
  void shadowColorAttenuation(float, float, float);

  void applyBackplane(bool);
  void backplaneShadowScale(float);
  void backplaneIntensity(float);

  void directionChanged(Vec);
  void lightDistanceOffset(float);

  void peel(bool);
  void peelInfo(int, float, float, float);

 public slots :
  void setLightInfo(LightingInformation);
  void keyPressEvent(QKeyEvent*);

 private slots :
  void lightDirectionChanged(qglviewer::Vec);

  void on_applyemissive_clicked(bool);
  void on_applylighting_clicked(bool);
  void on_applyshadow_clicked(bool);
  void on_applycoloredshadow_clicked(bool);
  void on_applybackplane_clicked(bool);

  void on_peel_clicked(bool);
  void on_peelmin_sliderReleased();
  void on_peelmax_sliderReleased();
  void on_peelmix_sliderReleased();
  void on_peeltype_currentIndexChanged(int);

  void on_ambient_sliderReleased();
  void on_diffuse_sliderReleased();
  void on_specular_sliderReleased();
  void on_specularcoeff_sliderReleased();

  void on_shadowblur_sliderReleased();
  void on_shadowscale_sliderReleased();
  void on_shadowcontrast_sliderReleased();
  void on_shadowfov_sliderReleased();

  void on_backplaneshadowscale_sliderReleased();
  void on_backplanecontrast_sliderReleased();

  void highlightsChanged();
  void shadowColor();

 private :
  Ui::LightingWidget ui;

  void peelSliderReleased();
  void showHelp();

  QSpinSlide * peelminLink;
  QSpinSlide * peelmaxLink;
  QSpinSlide * peelmixLink;
  QSpinSlide * ambientLink;
  QSpinSlide * diffuseLink;
  QSpinSlide * specularLink;
  QSpinSlide * specularcoeffLink;
  QSpinSlide * shadowblurLink;
  QSpinSlide * shadowscaleLink;
  QSpinSlide * shadowcontrastLink;
  QSpinSlide * shadowfovLink;
  QSpinSlide * redLink;
  QSpinSlide * greenLink;
  QSpinSlide * blueLink;
  QSpinSlide * backplaneshadowscaleLink;
  QSpinSlide * backplanecontrastLink;

};

#endif
