#ifndef SPLINEINFORMATION_H
#define SPLINEINFORMATION_H

#include <QDomDocument>
# include "PromotedWidgets.h"

class SplineInformation {
public :
  SplineInformation();
  SplineInformation& operator=(const SplineInformation&);

  void load(const QConfigMe &);
  void save(QConfigMe &) const;
  
  static SplineInformation interpolate(SplineInformation&, SplineInformation&, float);
  static QList<SplineInformation> interpolate(QList<SplineInformation>, QList<SplineInformation>, float);

  static QGradientStops interpolateGradientStops(QGradientStops, QGradientStops, float);

  void setName(QString);
  void setOn(QList<bool>);
  void setPoints(QPolygonF);
  void setNormalWidths(QPolygonF);
  void setNormalRotations(const QList<float> &);
  void setGradientStops(QGradientStops);
  void setGradLimits(int, int);
  void setOpmod(float, float);

  QString name();
  QList<bool> on();
  QPolygonF points();
  QPolygonF normalWidths();
  const QList<float> & normalRotations();
  QGradientStops gradientStops();
  void gradLimits(int&, int&);
  void opMod(float&, float&);

 private :
  QString m_name;
  QList<bool> m_on;
  QPolygonF m_points;
  QPolygonF m_normalWidths;
  QList<float> m_normalRotations;
  QGradientStops m_gradientStops;
  int m_gbot, m_gtop;
  float m_gbotop, m_gtopop;
};

#endif
