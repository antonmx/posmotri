#ifndef LIGHTINGWIDGET_H
#define LIGHTINGWIDGET_H

#include "lightinginformation.h"
#include "PromotedWidgets.h"

#include <QGLViewer/vec.h>
#include <QFrame>




class LightDisc : public QWidget {
  Q_OBJECT;
  
private :
  QPointF m_direction;
  bool m_backlit;
  
public :
  
  LightDisc(QWidget *parent = NULL);
  inline QPointF direction() const {return m_direction;}  

public slots:
  
  void setDirection(const QPointF & pos);
  void setBacklit(bool); 

signals :
  void directionChanged(const QPointF &);
  
private:
  void onMouseSet(const QPointF & pos);
  
private slots:
  
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void paintEvent(QPaintEvent*);
  void resizeEvent(QResizeEvent*);
  
};



namespace Ui {
    class DirectionVectorWidget;
}

class DirectionVectorWidget : public QFrame {
 Q_OBJECT;
 
private :
  Ui::DirectionVectorWidget * ui;

public :
  
  DirectionVectorWidget(QWidget *parent=NULL);

  void setVector(const qglviewer::Vec &);
  qglviewer::Vec vector();

signals :
  void directionChanged(qglviewer::Vec);
  
private slots :
  
  void updateDirection(QPointF);
  void onDirectionChange();
  void onLenChange();
  void resizeEvent(QResizeEvent*);
  
};



namespace Ui {
    class LightingWidget;
} 


class LightingWidget : public QWidget {
  Q_OBJECT;

private :
  Ui::LightingWidget * ui;

  QDoubleSpinSlide * peelminLink;
  QDoubleSpinSlide * peelmaxLink;
  QDoubleSpinSlide * peelmixLink;
  QDoubleSpinSlide * ambientLink;
  QDoubleSpinSlide * diffuseLink;
  QDoubleSpinSlide * specularLink;
  QSpinSlide       * specularcoeffLink;
  QDoubleSpinSlide * shadowblurLink;
  QDoubleSpinSlide * shadowscaleLink;
  QDoubleSpinSlide * shadowcontrastLink;
  QDoubleSpinSlide * shadowfovLink;
  QDoubleSpinSlide * redLink;
  QDoubleSpinSlide * greenLink;
  QDoubleSpinSlide * blueLink;
  QDoubleSpinSlide * backplaneshadowscaleLink;
  QDoubleSpinSlide * backplanecontrastLink;

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

private slots :
  void lightDirectionChanged(qglviewer::Vec);
  void highlightsChanged();
  void shadowColor();
  void peelChanged();

private:

  void showHelp();  //  TODO : remove after extracting useful info

};

#endif
