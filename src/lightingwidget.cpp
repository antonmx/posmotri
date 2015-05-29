
#include "lightingwidget.h"
#include "propertyeditor.h"
#include <QtGui>

LightingWidget::LightingWidget(QWidget *parent)
  : QWidget(parent)
{

  ui.setupUi(this);
  ui.lightpositionW->hide();
  ui.peelW->hide();
  ui.applycoloredshadowW->hide();
  ui.applybackplaneW->hide();

  connect(ui.lightpositionW, SIGNAL(directionChanged(qglviewer::Vec)), SLOT(lightDirectionChanged(qglviewer::Vec)));

  connect( ui.applyemissive,  SIGNAL(clicked(bool)),  SIGNAL(applyEmissive(bool)) );
  connect( ui.peel,  SIGNAL(clicked(bool)),  SIGNAL(peel(bool)) );
  connect( ui.peeltype,  SIGNAL(currentIndexChanged(int)),  SLOT(peelChanged()) );
  peelminLink = new QDoubleSpinSlide(ui.peelmin_, ui.peelmin_SB, this);
  connect(peelminLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );
  peelmaxLink = new QDoubleSpinSlide(ui.peelmax_, ui.peelmax_SB, this);
  connect(peelmaxLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );
  peelmixLink = new QDoubleSpinSlide(ui.peelmix_, ui.peelmix_SB, this);
  connect(peelmixLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );

  connect(ui.applylighting,  SIGNAL(clicked(bool)),  SIGNAL(applyLighting(bool)));
  ambientLink = new QDoubleSpinSlide(ui.ambient_, ui.ambient_SB, this);
  connect(ambientLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  diffuseLink = new QDoubleSpinSlide(ui.diffuse_, ui.diffuse_SB, this);
  connect(diffuseLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  specularLink = new QDoubleSpinSlide(ui.specular_, ui.specular_SB, this);
  connect(specularLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  specularcoeffLink = new QSpinSlide(ui.specularcoeff_, ui.specularcoeff_SB, this);
  connect(specularcoeffLink,  SIGNAL(valueChanged(int)),  SLOT(highlightsChanged()) );

  connect(ui.applyshadow,  SIGNAL(clicked(bool)),  SIGNAL(applyShadow(bool)));
  shadowblurLink = new QDoubleSpinSlide(ui.shadowblur_, ui.shadowblur_SB, this);
  connect(shadowblurLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowBlur(float)));
  shadowscaleLink = new QDoubleSpinSlide(ui.shadowscale_, ui.shadowscale_SB, this);
  connect(shadowscaleLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowScale(float)));
  shadowcontrastLink = new QDoubleSpinSlide(ui.shadowcontrast_, ui.shadowcontrast_SB, this);
  connect(shadowcontrastLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowIntensity(float)));
  shadowfovLink = new QDoubleSpinSlide(ui.shadowfov_, ui.shadowfov_SB, this);
  connect(shadowfovLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowFOV(float)));

  connect(ui.applycoloredshadow,  SIGNAL(clicked(bool)),  SIGNAL(applyColoredShadow(bool)));
  redLink = new QDoubleSpinSlide(ui.red_, ui.red_SB, this);
  connect(redLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  greenLink = new QDoubleSpinSlide(ui.green_, ui.green_SB, this);
  connect(greenLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  blueLink = new QDoubleSpinSlide(ui.blue_, ui.blue_SB, this);
  connect(blueLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  connect(ui.linkcolors,  SIGNAL(clicked(bool)),  SLOT(shadowColor()));

  connect(ui.applybackplane,  SIGNAL(clicked(bool)),  SIGNAL(applyBackplane(bool)));
  backplaneshadowscaleLink = new QDoubleSpinSlide(ui.backplaneshadowscale_, ui.backplaneshadowscale_SB, this);
  connect(backplaneshadowscaleLink,  SIGNAL(valueChanged(float)),  SIGNAL(backplaneShadowScale(float)));
  backplanecontrastLink = new QDoubleSpinSlide(ui.backplanecontrast_, ui.backplanecontrast_SB, this);
  connect(backplanecontrastLink,  SIGNAL(valueChanged(float)),  SIGNAL(backplaneIntensity(float)));

}


void LightingWidget::setLightInfo(LightingInformation lightInfo) {
  ui.applylighting->setChecked(lightInfo.applyLighting);
  ambientLink->setValue(lightInfo.highlights.ambient);
  diffuseLink->setValue(lightInfo.highlights.diffuse);
  specularLink->setValue(lightInfo.highlights.specular);
  specularcoeffLink->setValue(specularcoeffLink->maximum()
                              - lightInfo.highlights.specularCoefficient);

  ui.peel->setChecked(lightInfo.peel);
  peelminLink->setValue(lightInfo.peelMin);
  peelmaxLink->setValue(lightInfo.peelMax);
  peelmixLink->setValue(lightInfo.peelMix);
  ui.peeltype->setCurrentIndex(lightInfo.peelType);

  ui.applyshadow->setChecked(lightInfo.applyShadows);
  shadowblurLink->setValue(lightInfo.shadowBlur);
  shadowscaleLink->setValue(lightInfo.shadowScale);
  shadowcontrastLink->setValue(lightInfo.shadowIntensity);
  shadowfovLink->setValue(lightInfo.shadowFovOffset);

  ui.applycoloredshadow->setChecked(lightInfo.applyColoredShadows);
  redLink->setValue(lightInfo.colorAttenuation.x);
  greenLink->setValue(lightInfo.colorAttenuation.y);
  blueLink->setValue(lightInfo.colorAttenuation.z);

  ui.applybackplane->setChecked(lightInfo.applyBackplane);
  backplaneshadowscaleLink->setValue(lightInfo.backplaneShadowScale);
  backplanecontrastLink->setValue(lightInfo.backplaneIntensity);

  ui.lightpositionW->setVector( lightInfo.lightDistanceOffset * lightInfo.userLightVector);

}


void LightingWidget::lightDirectionChanged(Vec v) {
  emit directionChanged(v);
  emit lightDistanceOffset(v.norm());
}


void LightingWidget::peelChanged() {
  emit peelInfo(ui.peeltype->currentIndex(),
                peelminLink->value(), peelmaxLink->value(), peelmixLink->value());
}


void LightingWidget::highlightsChanged() {
  Highlights hl;
  hl.ambient  = ambientLink->value();
  hl.diffuse  = diffuseLink->value();
  hl.specular = specularLink->value();
  hl.specularCoefficient = specularcoeffLink->maximum()-specularcoeffLink->value();
  emit highlights(hl);
}


void LightingWidget::shadowColor() {

  if ( ui.linkcolors->isChecked() ) {

    int val = redLink->minimum() - 1;
    if (sender() == redLink)        val = redLink->value();
    else if (sender() == greenLink) val = greenLink->value();
    else if (sender() == blueLink)  val = blueLink->value();

    if (val >= redLink->minimum() ) {
      redLink->setValue(val);
      greenLink->setValue(val);
      blueLink->setValue(val);
    }

  }

  emit shadowColorAttenuation( redLink->value(), greenLink->value(), blueLink->value());

}


void
LightingWidget::showHelp()
{
  PropertyEditor propertyEditor;
  QMap<QString, QVariantList> plist;
  QVariantList vlist;

  vlist.clear();
  QFile helpFile(":/shader.help");
  if (helpFile.open(QFile::ReadOnly))
    {
      QTextStream in(&helpFile);
      QString line = in.readLine();
      while (!line.isNull())
	{
	  if (line == "#begin")
	    {
	      QString keyword = in.readLine();
	      QString helptext;
	      line = in.readLine();
	      while (!line.isNull())
		{
		  helptext += line;
		  helptext += "\n";
		  line = in.readLine();
		  if (line == "#end") break;
		}
	      vlist << keyword << helptext;
	    }
	  line = in.readLine();
	}
    }
  plist["commandhelp"] = vlist;


  QStringList keys;
  keys << "commandhelp";

  propertyEditor.set("Shader Help", plist, keys);
  propertyEditor.exec();
}
