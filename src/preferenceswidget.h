#ifndef PREFERENCESWIDGET_H
#define PREFERENCESWIDGET_H

#include "ui_preferenceswidget.h"
#include "tagcoloreditor.h"
#include "PromotedWidgets.h"

class PreferencesWidget : public QWidget {
  Q_OBJECT;

public :
  PreferencesWidget(QWidget *parent=NULL);

  void getTick(int&, int&, QString&, QString&, QString&) const ;
  void setTick(int sz, int st, const QString & xl, const QString & yl, const QString & zl);

signals :
  void updateLookupTable();
  void updateGL();
  void stereoSettingsChanged(float, float, float);
  void tagColorChanged();

public slots :
  void setRenderQualityValues(float, float);
  void setStereoSettings(float, float, float);
  void updateTextureMemory();
  void updateTagColors();

private slots:
  void on_m_newColorSet_clicked();
  void on_m_setOpacity_clicked();
  void on_m_bgcolor_clicked();
  void onImageQualityChanged();
  void onTickChanged();
  void onStereoChanged();

 private :
  Ui::PreferencesWidget * ui;

  TagColorEditor *m_tagColorEditor;

  static float imageQualityValue(int);
  static int renderQualityValue(float);
  
  QSpinSlide * textureMemorySizeLink;
  QSpinSlide * stilLink;
  QSpinSlide * dragLink;

  void showHelp();
};

#endif
