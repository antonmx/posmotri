
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
  
  peelminLink = new QSpinSlide(ui.peelmin_, ui.peelmin_SB, this);
  peelmaxLink = new QSpinSlide(ui.peelmax_, ui.peelmax_SB, this);
  peelmixLink = new QSpinSlide(ui.peelmix_, ui.peelmix_SB, this);
  ambientLink = new QSpinSlide(ui.ambient_, ui.ambient_SB, this);
  diffuseLink = new QSpinSlide(ui.diffuse_, ui.diffuse_SB, this);
  specularLink = new QSpinSlide(ui.specular_, ui.specular_SB, this);
  specularcoeffLink = new QSpinSlide(ui.specularcoeff_, ui.specularcoeff_SB, this);
  shadowblurLink = new QSpinSlide(ui.shadowblur_, ui.shadowblur_SB, this);
  shadowscaleLink = new QSpinSlide(ui.shadowscale_, ui.shadowscale_SB, this);
  shadowcontrastLink = new QSpinSlide(ui.shadowcontrast_, ui.shadowcontrast_SB, this);
  shadowfovLink = new QSpinSlide(ui.shadowfov_, ui.shadowfov_SB, this);
  redLink = new QSpinSlide(ui.red_, ui.red_SB, this);
  greenLink = new QSpinSlide(ui.green_, ui.green_SB, this);
  blueLink = new QSpinSlide(ui.blue_, ui.blue_SB, this);
  backplaneshadowscaleLink = new QSpinSlide(ui.backplaneshadowscale_, ui.backplaneshadowscale_SB, this);
  backplanecontrastLink = new QSpinSlide(ui.backplanecontrast_, ui.backplanecontrast_SB, this);

  connect( redLink, SIGNAL(valueChanged(int)), SLOT(shadowColor()));
  connect( blueLink, SIGNAL(valueChanged(int)), SLOT(shadowColor()));
  connect( greenLink, SIGNAL(valueChanged(int)), SLOT(shadowColor()));
  
  
  connect(ui.lightpositionW, SIGNAL(directionChanged(qglviewer::Vec)), SLOT(lightDirectionChanged(qglviewer::Vec)));

}


void
LightingWidget::setLightInfo(LightingInformation lightInfo)
{
  ui.applylighting->setChecked(lightInfo.applyLighting);
  ambientLink->setValue(lightInfo.highlights.ambient*10);
  diffuseLink->setValue(lightInfo.highlights.diffuse*10);
  specularLink->setValue(lightInfo.highlights.specular*10);
  specularcoeffLink->setValue(ui.specularcoeff_->maximum() - lightInfo.highlights.specularCoefficient);

  ui.peel->setChecked(lightInfo.peel);
  peelminLink->setValue(lightInfo.peelMin*100);
  peelmaxLink->setValue(lightInfo.peelMax*100);
  peelmixLink->setValue(lightInfo.peelMix*100);
  ui.peeltype->setCurrentIndex(lightInfo.peelType);

  ui.applyshadow->setChecked(lightInfo.applyShadows);
  shadowblurLink->setValue(lightInfo.shadowBlur);
  shadowscaleLink->setValue((lightInfo.shadowScale-0.2)*10);
  shadowcontrastLink->setValue(lightInfo.shadowIntensity*10);
  shadowfovLink->setValue(lightInfo.shadowFovOffset*25+5);

  ui.applycoloredshadow->setChecked(lightInfo.applyColoredShadows);
  redLink->setValue(lightInfo.colorAttenuation.x*50);
  greenLink->setValue(lightInfo.colorAttenuation.y*50);
  blueLink->setValue(lightInfo.colorAttenuation.z*50);

  ui.applybackplane->setChecked(lightInfo.applyBackplane);
  backplaneshadowscaleLink->setValue(lightInfo.backplaneShadowScale*5);
  backplanecontrastLink->setValue(lightInfo.backplaneIntensity*10);

  ui.lightpositionW->setVector( lightInfo.lightDistanceOffset * lightInfo.userLightVector);

}

void LightingWidget::lightDirectionChanged(Vec v) {
  emit directionChanged(v);
  emit lightDistanceOffset(v.norm());
}

void LightingWidget::on_peel_clicked(bool flag) {
  emit peel(flag);
}
void LightingWidget::on_peelmin_sliderReleased() { peelSliderReleased(); }
void LightingWidget::on_peelmax_sliderReleased() { peelSliderReleased(); }
void LightingWidget::on_peelmix_sliderReleased() { peelSliderReleased(); }
void LightingWidget::on_peeltype_currentIndexChanged(int idx) { peelSliderReleased(); }
void LightingWidget::peelSliderReleased()
{
  int pidx = ui.peeltype->currentIndex();
  float emin = (float)peelminLink->value()*0.01;
  float emax = (float)peelmaxLink->value()*0.01;
  float emix = (float)peelmixLink->value()*0.01;
  emit peelInfo(pidx, emin, emax, emix);
}

void LightingWidget::on_applylighting_clicked(bool flag) {
  emit applyLighting(flag);
}
void LightingWidget::on_ambient_sliderReleased() { highlightsChanged(); }
void LightingWidget::on_diffuse_sliderReleased() { highlightsChanged(); }
void LightingWidget::on_specular_sliderReleased() { highlightsChanged(); }
void LightingWidget::on_specularcoeff_sliderReleased() { highlightsChanged(); }
void LightingWidget::highlightsChanged()
{
  Highlights hl;

  hl.ambient  = (float)ambientLink->value()*0.1;
  hl.diffuse  = (float)diffuseLink->value()*0.1;
  hl.specular = (float)specularLink->value()*0.1;
  hl.specularCoefficient = ui.specularcoeff_->maximum()-specularcoeffLink->value();

  emit highlights(hl);
}


void LightingWidget::on_applyshadow_clicked(bool flag) {
  emit applyShadow(flag);
}
void LightingWidget::on_shadowblur_sliderReleased()
{
  float v = (float)shadowblurLink->value();
  emit shadowBlur(v);
}
void LightingWidget::on_shadowscale_sliderReleased()
{
  float v = (float)shadowscaleLink->value()*0.1 + 0.2;
  emit shadowScale(v);
}
void LightingWidget::on_shadowcontrast_sliderReleased()
{
  float v = (float)shadowcontrastLink->value()*0.1;
  emit shadowIntensity(v);
}
void LightingWidget::on_shadowfov_sliderReleased()
{
  float v = (float)(shadowfovLink->value()-5)*0.04;
  emit shadowFOV(v);
}


void LightingWidget::on_applycoloredshadow_clicked(bool flag) {
  emit applyColoredShadow(flag);
}


void LightingWidget::on_linkcolors_clicked(bool flag) {
  if ( ui.linkcolors->isChecked() ) {
    blueLink->setValue(redLink->value());
    greenLink->setValue(redLink->value());
    connect( redLink, SIGNAL(valueChanged(int)), blueLink, SLOT(setValue(int)));
    connect( redLink, SIGNAL(valueChanged(int)), greenLink, SLOT(setValue(int)));
    connect( blueLink, SIGNAL(valueChanged(int)), redLink, SLOT(setValue(int)));
    connect( blueLink, SIGNAL(valueChanged(int)), greenLink, SLOT(setValue(int)));
    connect( greenLink, SIGNAL(valueChanged(int)), blueLink, SLOT(setValue(int)));
    connect( greenLink, SIGNAL(valueChanged(int)), redLink, SLOT(setValue(int)));
  } else {
    disconnect( redLink, SIGNAL(valueChanged(int)), blueLink, SLOT(setValue(int)));
    disconnect( redLink, SIGNAL(valueChanged(int)), greenLink, SLOT(setValue(int)));
    disconnect( blueLink, SIGNAL(valueChanged(int)), redLink, SLOT(setValue(int)));
    disconnect( blueLink, SIGNAL(valueChanged(int)), greenLink, SLOT(setValue(int)));
    disconnect( greenLink, SIGNAL(valueChanged(int)), blueLink, SLOT(setValue(int)));
    disconnect( greenLink, SIGNAL(valueChanged(int)), redLink, SLOT(setValue(int)));
  }
}

void LightingWidget::shadowColor() {
  QCoreApplication::processEvents(); // to allow linked colors to update.
  float r = 0.02*redLink->value();
  float g = 0.02*greenLink->value();
  float b = 0.02*blueLink->value();
  emit shadowColorAttenuation(r,g,b);
}


void LightingWidget::on_applybackplane_clicked(bool flag) {
  emit applyBackplane(flag);
}
void LightingWidget::on_backplaneshadowscale_sliderReleased()
{
  float v = (float)backplaneshadowscaleLink->value()*0.2;
  emit backplaneShadowScale(v);
}
void LightingWidget::on_backplanecontrast_sliderReleased()
{
  float v = (float)backplanecontrastLink->value()*0.1;
  emit backplaneIntensity(v);
}

void LightingWidget::on_applyemissive_clicked(bool flag)
{
  emit applyEmissive(flag);
}


void
LightingWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_H &&
      (event->modifiers() & Qt::ControlModifier ||
       event->modifiers() & Qt::MetaModifier) )
    showHelp();
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
