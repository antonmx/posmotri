
#include "ui_lightingwidget.h"
#include "ui_directionvectorwidget.h"

#include "lightingwidget.h"
#include "propertyeditor.h"
#include "staticfunctions.h"
#include <QtGui>
#include <QMenu>


using namespace qglviewer;


LightDisc::LightDisc(QWidget *parent)
  : QWidget(parent)
  , m_backlit(false)
  , m_direction(0, 0)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
}

void LightDisc::setDirection(const QPointF & dir) {
  m_direction = dir;
  update();
  emit directionChanged(m_direction);
}

void LightDisc::setBacklit(bool flag) { 
  m_backlit = flag;
  update();
}

void LightDisc::paintEvent(QPaintEvent *event) {
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  float m_size = qMin( width(), height() );  
  QRectF drawRect( rect().topLeft(), QSizeF(m_size,m_size) ) ;
  
  QRadialGradient radialGradient( drawRect.center(), m_size,
    drawRect.center() + m_size * QPointF( -m_direction.x(), m_direction.y() ) /2 );  
  radialGradient.setColorAt(0.0, m_backlit ? Qt::black : Qt::white );
  radialGradient.setColorAt(0.5, Qt::gray);
  radialGradient.setColorAt(1.0, m_backlit ? Qt::white : Qt::black );
  p.setBrush(QBrush(radialGradient));
  p.setPen(Qt::darkGray);  
  p.drawEllipse(drawRect);

  p.setBrush(Qt::transparent);
  p.drawEllipse( drawRect.center(), m_size*cos(M_PI/8)/2, m_size*cos(M_PI/8)/2);
  p.drawEllipse( drawRect.center(), m_size*cos(M_PI/4)/2, m_size*cos(M_PI/4)/2);
  p.drawEllipse( drawRect.center(), m_size*cos(3*M_PI/8)/2, m_size*cos(3*M_PI/8)/2);
  
  p.drawLine(0, m_size/2, m_size, m_size/2);
  p.drawLine(m_size/2, 0, m_size/2, m_size);
  
  
}

void LightDisc::onMouseSet(const QPointF & pos) {
    const float m_size = qMin( width(), height() );  
    const QPointF ecor = pos - QPointF(m_size/2, m_size/2);
    const float len = sqrt(ecor.x()*ecor.x() + ecor.y()*ecor.y());
    if (len > m_size/2)
      return;
    setDirection(QPointF( -2*ecor.x()/m_size, 2*ecor.y()/m_size)) ; 
}

void LightDisc::mousePressEvent(QMouseEvent *event) {
  if(event->button() == Qt::RightButton ) {
    QMenu myMenu;
    myMenu.addAction("Center");
    if (myMenu.exec(mapToGlobal(event->pos())))
      setDirection(QPointF(0, 0));
  } else {
    onMouseSet(event->pos());
  }
}

void LightDisc::mouseMoveEvent(QMouseEvent *event) {
  onMouseSet(event->pos());
}


void LightDisc::resizeEvent(QResizeEvent *event) {
  setMaximumSize(QWIDGETSIZE_MAX, width());
}







DirectionVectorWidget::DirectionVectorWidget(QWidget *parent)
  : QFrame(parent)
  , ui(new Ui::DirectionVectorWidget)
{	
  ui->setupUi(this);  
  connect(ui->lightDisc, SIGNAL(directionChanged(QPointF)), SLOT(updateDirection(QPointF)));
  connect(ui->zangle, SIGNAL(valueChanged(double)), SLOT(onDirectionChange()));
  connect(ui->yangle, SIGNAL(valueChanged(double)), SLOT(onDirectionChange()));
  connect(ui->len, SIGNAL(valueChanged(double)), SLOT(onLenChange()));
  setVector(Vec(0,0,1));
}

void DirectionVectorWidget::setVector(const Vec & vv) {
  const qreal norm = vv.norm();
  ui->len->setValue(norm);
  if ( norm != 0 ) {
    Vec vo = vv/norm;
    ui->zangle->setValue( RAD2DEG(acos(vo.z)) );
    ui->yangle->setValue( copysign( RAD2DEG(acos(-vo.y/sqrt(vo.y*vo.y+vo.x*vo.x))), -vo.x ) );  
  }
}

Vec DirectionVectorWidget::vector() {
  const float cosz = cos( DEG2RAD(ui->zangle->value()) );
  const float cosy = cos( DEG2RAD(ui->yangle->value()) );  
  const float z = cosz;
  const float y = -cosy*sqrt(1-cosz*cosz);  
  const float x = -copysign( sqrt( (1-cosz*cosz)*(1-cosy*cosy) ), ui->yangle->value() );
  return  ui->len->value() * Vec(x,y,z);
}


void DirectionVectorWidget::updateDirection(QPointF pt) {
  const qreal zabs = sqrt(1-pt.y()*pt.y()-pt.x()*pt.x());
  setVector( Vec(pt.x(), pt.y(), copysign( zabs, 90 - ui->zangle->value() ) ) );
  emit directionChanged(vector());
}


void DirectionVectorWidget::onDirectionChange() {
  const Vec vo=vector();
  const Vec vn = vo.norm() == 0 ? vo : vo.unit();
  ui->lightDisc->setDirection( QPointF(vn.x, vn.y) );
  ui->lightDisc->setBacklit(vn.z < 0);
  emit directionChanged(vo);
}


void DirectionVectorWidget::onLenChange() {
  emit directionChanged(vector());
}


void DirectionVectorWidget::resizeEvent(QResizeEvent *event) {
  setMaximumSize(QWIDGETSIZE_MAX,
		 width() + ui->nums->height() + layout()->minimumSize().height());
}


















LightingWidget::LightingWidget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::LightingWidget)
{

  ui->setupUi(this);
  ui->lightpositionW->hide();
  ui->peelW->hide();
  ui->applycoloredshadowW->hide();
  ui->applybackplaneW->hide();

  connect(ui->lightpositionW, SIGNAL(directionChanged(qglviewer::Vec)), SLOT(lightDirectionChanged(qglviewer::Vec)));

  connect( ui->applyemissive,  SIGNAL(clicked(bool)),  SIGNAL(applyEmissive(bool)) );
  connect( ui->peel,  SIGNAL(clicked(bool)),  SIGNAL(peel(bool)) );
  connect( ui->peeltype,  SIGNAL(currentIndexChanged(int)),  SLOT(peelChanged()) );
  peelminLink = new QDoubleSpinSlide(ui->peelmin_, ui->peelmin_SB, this);
  connect(peelminLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );
  peelmaxLink = new QDoubleSpinSlide(ui->peelmax_, ui->peelmax_SB, this);
  connect(peelmaxLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );
  peelmixLink = new QDoubleSpinSlide(ui->peelmix_, ui->peelmix_SB, this);
  connect(peelmixLink,  SIGNAL(valueChanged(double)),  SLOT(peelChanged()) );

  connect(ui->applylighting,  SIGNAL(clicked(bool)),  SIGNAL(applyLighting(bool)));
  ambientLink = new QDoubleSpinSlide(ui->ambient_, ui->ambient_SB, this);
  connect(ambientLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  diffuseLink = new QDoubleSpinSlide(ui->diffuse_, ui->diffuse_SB, this);
  connect(diffuseLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  specularLink = new QDoubleSpinSlide(ui->specular_, ui->specular_SB, this);
  connect(specularLink,  SIGNAL(valueChanged(double)),  SLOT(highlightsChanged()) );
  specularcoeffLink = new QSpinSlide(ui->specularcoeff_, ui->specularcoeff_SB, this);
  connect(specularcoeffLink,  SIGNAL(valueChanged(int)),  SLOT(highlightsChanged()) );

  connect(ui->applyshadow,  SIGNAL(clicked(bool)),  SIGNAL(applyShadow(bool)));
  shadowblurLink = new QDoubleSpinSlide(ui->shadowblur_, ui->shadowblur_SB, this);
  connect(shadowblurLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowBlur(float)));
  shadowscaleLink = new QDoubleSpinSlide(ui->shadowscale_, ui->shadowscale_SB, this);
  connect(shadowscaleLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowScale(float)));
  shadowcontrastLink = new QDoubleSpinSlide(ui->shadowcontrast_, ui->shadowcontrast_SB, this);
  connect(shadowcontrastLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowIntensity(float)));
  shadowfovLink = new QDoubleSpinSlide(ui->shadowfov_, ui->shadowfov_SB, this);
  connect(shadowfovLink,  SIGNAL(valueChanged(float)),  SIGNAL(shadowFOV(float)));

  connect(ui->applycoloredshadow,  SIGNAL(clicked(bool)),  SIGNAL(applyColoredShadow(bool)));
  redLink = new QDoubleSpinSlide(ui->red_, ui->red_SB, this);
  connect(redLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  greenLink = new QDoubleSpinSlide(ui->green_, ui->green_SB, this);
  connect(greenLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  blueLink = new QDoubleSpinSlide(ui->blue_, ui->blue_SB, this);
  connect(blueLink,  SIGNAL(valueChanged(double)),  SLOT(shadowColor()));
  connect(ui->linkcolors,  SIGNAL(clicked(bool)),  SLOT(shadowColor()));

  connect(ui->applybackplane,  SIGNAL(clicked(bool)),  SIGNAL(applyBackplane(bool)));
  backplaneshadowscaleLink = new QDoubleSpinSlide(ui->backplaneshadowscale_, ui->backplaneshadowscale_SB, this);
  connect(backplaneshadowscaleLink,  SIGNAL(valueChanged(float)),  SIGNAL(backplaneShadowScale(float)));
  backplanecontrastLink = new QDoubleSpinSlide(ui->backplanecontrast_, ui->backplanecontrast_SB, this);
  connect(backplanecontrastLink,  SIGNAL(valueChanged(float)),  SIGNAL(backplaneIntensity(float)));

}


void LightingWidget::setLightInfo(LightingInformation lightInfo) {
  ui->applylighting->setChecked(lightInfo.applyLighting);
  ambientLink->setValue(lightInfo.highlights.ambient);
  diffuseLink->setValue(lightInfo.highlights.diffuse);
  specularLink->setValue(lightInfo.highlights.specular);
  specularcoeffLink->setValue(specularcoeffLink->maximum()
                              - lightInfo.highlights.specularCoefficient);

  ui->peel->setChecked(lightInfo.peel);
  peelminLink->setValue(lightInfo.peelMin);
  peelmaxLink->setValue(lightInfo.peelMax);
  peelmixLink->setValue(lightInfo.peelMix);
  ui->peeltype->setCurrentIndex(lightInfo.peelType);

  ui->applyshadow->setChecked(lightInfo.applyShadows);
  shadowblurLink->setValue(lightInfo.shadowBlur);
  shadowscaleLink->setValue(lightInfo.shadowScale);
  shadowcontrastLink->setValue(lightInfo.shadowIntensity);
  shadowfovLink->setValue(lightInfo.shadowFovOffset);

  ui->applycoloredshadow->setChecked(lightInfo.applyColoredShadows);
  redLink->setValue(lightInfo.colorAttenuation.x);
  greenLink->setValue(lightInfo.colorAttenuation.y);
  blueLink->setValue(lightInfo.colorAttenuation.z);

  ui->applybackplane->setChecked(lightInfo.applyBackplane);
  backplaneshadowscaleLink->setValue(lightInfo.backplaneShadowScale);
  backplanecontrastLink->setValue(lightInfo.backplaneIntensity);

  ui->lightpositionW->setVector( lightInfo.lightDistanceOffset * lightInfo.userLightVector);

}


void LightingWidget::lightDirectionChanged(Vec v) {
  emit directionChanged(v);
  emit lightDistanceOffset(v.norm());
}


void LightingWidget::peelChanged() {
  emit peelInfo(ui->peeltype->currentIndex(),
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

  if ( ui->linkcolors->isChecked() ) {

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
