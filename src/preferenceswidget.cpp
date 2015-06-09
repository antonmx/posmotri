#include "preferenceswidget.h"
#include "tick.h"
#include "global.h"
#include "dcolordialog.h"
#include "propertyeditor.h"

#include <QFile>
#include <QTextStream>

using namespace qglviewer;

PreferencesWidget::PreferencesWidget(QWidget *parent)
  : QWidget(parent)
  , m_tagColorEditor(new TagColorEditor)
  , ui(new Ui::PreferencesWidget)
{
  ui->setupUi(this);

  ui->tabWidget->widget(3)->layout()->addWidget(m_tagColorEditor);
  connect(m_tagColorEditor, SIGNAL(tagColorChanged()), SIGNAL(tagColorChanged()));
  connect(m_tagColorEditor, SIGNAL(tagColorChanged()), SIGNAL(updateGL()));

  textureMemorySizeLink = new QSpinSlide(ui->m_textureMemorySize, ui->m_textureMemorySize_SB, this);
  stilLink = new QSpinSlide(ui->m_still, ui->m_still_SB, this);
  dragLink = new QSpinSlide(ui->m_drag, ui->m_drag_SB, this);
  connect( textureMemorySizeLink,  SIGNAL(valueChanged(int)),  SLOT(onImageQualityChanged()));
  connect( stilLink,  SIGNAL(valueChanged(int)),  SLOT( onImageQualityChanged() ));
  connect( dragLink,  SIGNAL(valueChanged(int)),  SLOT( onImageQualityChanged() ));

  connect( ui->m_tickSize,  SIGNAL(editingFinished()),  SLOT(onTickChanged()));
  connect( ui->m_tickStep,  SIGNAL(editingFinished()),  SLOT(onTickChanged()));
  connect( ui->m_labelX,  SIGNAL(editingFinished()),  SLOT(onTickChanged()));
  connect( ui->m_labelY,  SIGNAL(editingFinished()),  SLOT(onTickChanged()));
  connect( ui->m_labelZ,  SIGNAL(editingFinished()),  SLOT(onTickChanged()));
  connect( ui->m_eyeSeparation,  SIGNAL(editingFinished()),  SLOT(onStereoChanged()));
  connect( ui->m_focus,  SIGNAL(editingFinished()),  SLOT(onStereoChanged()));
  connect( ui->m_screenWidth,  SIGNAL(editingFinished()),  SLOT(onStereoChanged()));

  onTickChanged();
  updateTextureMemory();


}


void PreferencesWidget::updateTagColors() {
  m_tagColorEditor->setColors();
}


void PreferencesWidget::updateTextureMemory() {
  textureMemorySizeLink->setValue(Global::textureMemorySize());
}


void PreferencesWidget::setStereoSettings(float dist, float es, float width) {
  ui->m_focus->setRange(dist/10, 2*dist);
  ui->m_focus->setValue(dist);
  ui->m_screenWidth->setValue(width);
  ui->m_eyeSeparation->setValue(es);
}



void PreferencesWidget::onImageQualityChanged() {
  Global::setStepsizeDrag(imageQualityValue(dragLink->value()));
  Global::setStepsizeStill(imageQualityValue(stilLink->value()));
  Global::setTextureMemorySize(textureMemorySizeLink->value());
  Global::calculate3dTextureSize();
  emit updateLookupTable();
  emit updateGL();
}



int PreferencesWidget::renderQualityValue(float v) {
  if (v <= 1.0) return (1.7-v)*10;
  else return 8 - v;
}


float PreferencesWidget::imageQualityValue(int v) {
  if (v >= 7) return 1.7 - 0.1*v;
  else return 8 - v;
}


void PreferencesWidget::setRenderQualityValues(float still, float drag) {
  stilLink->setValue(renderQualityValue(still));
  dragLink->setValue(renderQualityValue(drag));
}


void PreferencesWidget::getTick(int& sz, int& st, QString& xl, QString& yl, QString& zl) const {
  sz = ui->m_tickSize->value();
  st = ui->m_tickStep->value();
  xl = ui->m_labelX->text();
  yl = ui->m_labelY->text();
  zl = ui->m_labelZ->text();
}

void PreferencesWidget::setTick(int sz, int st, const QString & xl, const QString & yl, const QString & zl) {
  ui->m_tickSize->setValue(sz);
  ui->m_tickStep->setValue(st);
  ui->m_labelX->setText(xl);
  ui->m_labelY->setText(yl);
  ui->m_labelZ->setText(zl);
}







void PreferencesWidget::on_m_newColorSet_clicked() {
  m_tagColorEditor->newColorSet(ui->m_colorSeed->value());
}

void PreferencesWidget::on_m_setOpacity_clicked() {
  m_tagColorEditor->setOpacity(ui->m_opacity->value());
}

void PreferencesWidget::onTickChanged() {
  Tick::setTickSize(ui->m_tickSize->value());
  Tick::setTickStep(ui->m_tickStep->value());
  Tick::setLabelX(ui->m_labelX->text());
  Tick::setLabelY(ui->m_labelY->text());
  Tick::setLabelZ(ui->m_labelZ->text());
  emit updateGL();
}

void PreferencesWidget::onStereoChanged() {
  emit stereoSettingsChanged(ui->m_focus->value(), ui->m_eyeSeparation->value(), ui->m_screenWidth->value() );
}

void PreferencesWidget::on_m_bgcolor_clicked() {
  const Vec bg = Global::backgroundColor();
  const QColor color = DColorDialog::getColor(QColor(255*bg.x, 255*bg.y, 255*bg.z));
  if (color.isValid()) {
    Global::setBackgroundColor(Vec(color.redF(), color.greenF(), color.blueF()));
    emit updateGL();
  }
}



void
PreferencesWidget::showHelp()
{
  PropertyEditor propertyEditor;
  QMap<QString, QVariantList> plist;
  QVariantList vlist;

  vlist.clear();
  QFile helpFile(":/preferences.help");
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

  propertyEditor.set("Preferences Help", plist, keys);
  propertyEditor.exec();

}
