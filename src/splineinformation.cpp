#include "global.h"
#include "splineinformation.h"
#include "staticfunctions.h"
//#include <QtGui>

void SplineInformation::setName(QString str) {m_name = str; };
void SplineInformation::setOn(QList<bool> flags) { m_on = flags; };
void SplineInformation::setPoints(QPolygonF pts) { m_points = pts; };
void SplineInformation::setNormalWidths(QPolygonF nw) { m_normalWidths = nw; };
void SplineInformation::setNormalRotations(const QList<float> & nr) { m_normalRotations = nr; };
void SplineInformation::setGradientStops(QGradientStops gs) { m_gradientStops = gs; };
void SplineInformation::setGradLimits(int bot, int top)
{
  m_gtop = top;
  m_gbot = bot;
}
void SplineInformation::setOpmod(float bot, float top)
{
  m_gbotop = bot;
  m_gtopop = top;
}



QString SplineInformation::name() { return m_name; };
QList<bool> SplineInformation::on() { return m_on; };
QPolygonF SplineInformation::points() { return m_points; };
QPolygonF SplineInformation::normalWidths() { return m_normalWidths; };
const QList<float> & SplineInformation::normalRotations() { return m_normalRotations; };
QGradientStops SplineInformation::gradientStops() { return m_gradientStops; };
void SplineInformation::gradLimits(int& bot, int& top)
{
  bot = qBound(0, m_gbot, 255);
  top = qBound(0, m_gtop, 255);
}
void SplineInformation::opMod(float& bot, float& top)
{
  bot = qBound(0.0f, m_gbotop, 1.0f);
  top = qBound(0.0f, m_gtopop, 1.0f);
}



SplineInformation::SplineInformation()
{
  m_name.clear();
  m_on.clear();
  m_points.clear();
  m_normalWidths.clear();
  m_normalRotations.clear();
  m_gradientStops.clear();
  m_gbot = 0;
  m_gtop = 255;
  m_gbotop = 1.0;
  m_gtopop = 1.0;
}
SplineInformation&
SplineInformation::operator=(const SplineInformation& splineInfo)
{
  m_name = splineInfo.m_name;
  m_on = splineInfo.m_on;
  m_points = splineInfo.m_points;
  m_normalWidths = splineInfo.m_normalWidths;
  m_normalRotations = splineInfo.m_normalRotations;
  m_gradientStops = splineInfo.m_gradientStops;
  m_gbot = splineInfo.m_gbot;
  m_gtop =splineInfo.m_gtop;
  m_gbotop = splineInfo.m_gbotop;
  m_gtopop =splineInfo.m_gtopop;
  return *this;
}

void SplineInformation::load ( const QConfigMe & cfg) {

  m_name.clear();
  m_on.clear();
  m_points.clear();
  m_normalWidths.clear();
  m_normalRotations.clear();
  m_gradientStops.clear();
  m_gbot = 0;
  m_gtop = 255;
  m_gbotop = 1.0;
  m_gtopop = 1.0;

  cfg.beginGroup("SplineInformation");
  cfg.getValue("name", m_name);
  cfg.getArrayValue("On", m_on);
  cfg.getValue("Points", m_points);
  cfg.getValue("normalwidths", m_normalWidths);
  cfg.getArrayValue("normalrotations", m_normalRotations);
  int sz = cfg.beginArray("GradientStops");
  for (int i=0; i<sz; i++) {
    QGradientStop st;
    cfg.getValue("pos", st.first);
    cfg.getValue("col", st.second);
    cfg.advanceArray();
    m_gradientStops.append(st);
  }
  cfg.endArray();
  cfg.getValue("gbot", m_gbot);
  cfg.getValue("gtop", m_gtop);
  cfg.getValue("gbotop", m_gbotop);
  cfg.getValue("gtopop", m_gtopop);
  cfg.endGroup();

}

void SplineInformation::save ( QConfigMe & cfg) const {
  cfg.beginGroup("SplineInformation");
  cfg.setValue("name", m_name);
  cfg.setArrayValue("On", m_on);
  cfg.setValue("Points", m_points);
  cfg.setValue("normalwidths", m_normalWidths);
  cfg.setArrayValue("normalrotations", m_normalRotations);
  cfg.beginArray("GradientStops");
  foreach(QGradientStop st, m_gradientStops) {
    cfg.setValue("pos", st.first);
    cfg.setValue("col", st.second);
    cfg.advanceArray();
  }
  cfg.endArray();
  cfg.setValue("gbot", m_gbot);
  cfg.setValue("gtop", m_gtop);
  cfg.setValue("gbotop", m_gbotop);
  cfg.setValue("gtopop", m_gtopop);
  cfg.endGroup();
}

SplineInformation
SplineInformation::interpolate(SplineInformation& splineInfo1,
             SplineInformation& splineInfo2,
             float frc)
{
  SplineInformation splineInfo;
  QPolygonF points, points1, points2;
  QPolygonF normalWidths, normalWidths1, normalWidths2;
  QList<float> normalRotations, normalRotations1, normalRotations2;
  QGradientStops gradStops, gradStops1, gradStops2;

  int m1, m2;

  points1 = splineInfo1.points();
  points2 = splineInfo2.points();
  m1 = points1.size();
  m2 = points2.size();
  for(int i=0; i<qMax(m1,m2); i++)
    {
      float x1, y1, x2, y2;
      if (i < m1)
  {
    x1 = points1[i].x();
    y1 = points1[i].y();
  }
      else
  {
    x1 = points1[m1-1].x();
    y1 = points1[m1-1].y();
  }
      if (i < m2)
  {
    x2 = points2[i].x();
    y2 = points2[i].y();
  }
      else
  {
    x2 = points2[m2-1].x();
    y2 = points2[m2-1].y();
  }

      float x, y;
      x = x1 + frc*(x2-x1);
      y = y1 + frc*(y2-y1);

      points << QPointF(x,y);
    }

  normalWidths1 = splineInfo1.normalWidths();
  normalWidths2 = splineInfo2.normalWidths();
  m1 = normalWidths1.size();
  m2 = normalWidths2.size();
  for(int i=0; i<qMax(m1,m2); i++)
    {
      float x1, y1, x2, y2;
      if (i < m1)
  {
    x1 = normalWidths1[i].x();
    y1 = normalWidths1[i].y();
  }
      else
  {
    x1 = normalWidths1[m1-1].x();
    y1 = normalWidths1[m1-1].y();
  }
      if (i < m2)
  {
    x2 = normalWidths2[i].x();
    y2 = normalWidths2[i].y();
  }
      else
  {
    x2 = normalWidths2[m2-1].x();
    y2 = normalWidths2[m2-1].y();
  }

      float x, y;
      x = x1 + frc*(x2-x1);
      y = y1 + frc*(y2-y1);

      normalWidths << QPointF(x,y);
    }


  normalRotations1 = splineInfo1.normalRotations();
  normalRotations2 = splineInfo2.normalRotations();
  m1 = normalRotations1.size();
  m2 = normalRotations2.size();
  for(int i=0; i<qMax(m1,m2); i++)
    {
      float r1, r2;
      if (i<m1)
       r1 = normalRotations1[i];
      else
       r1 = normalRotations1[m1-1];

      if (i<m2)
       r2 = normalRotations2[i];
      else
       r2 = normalRotations2[m2-1];

      float r = r1 + frc*(r2-r1);
      normalRotations << r;
    }


  gradStops = interpolateGradientStops(splineInfo1.gradientStops(),
               splineInfo2.gradientStops(),
               frc);


  int bot1, top1, bot2, top2;
  float botop1, topop1, botop2, topop2;
  splineInfo1.gradLimits(bot1, top1);
  splineInfo1.opMod(botop1, topop1);
  splineInfo2.gradLimits(bot2, top2);
  splineInfo2.opMod(botop2, topop2);
  int bot, top;
  float botop, topop;
  bot = bot1 + frc*(bot2-bot1);
  top = top1 + frc*(top2-top1);
  botop = botop1 + frc*(botop2-botop1);
  topop = topop1 + frc*(topop2-topop1);

  // keep same "name" and "on"
  splineInfo.setName(splineInfo1.name());
  splineInfo.setOn(splineInfo1.on());
  // interpolate the rest
  splineInfo.setPoints(points);
  splineInfo.setNormalWidths(normalWidths);
  splineInfo.setNormalRotations(normalRotations);
  splineInfo.setGradientStops(gradStops);
  splineInfo.setGradLimits(bot, top);
  splineInfo.setOpmod(botop, topop);

  return splineInfo;
}

QList<SplineInformation>
SplineInformation::interpolate(QList<SplineInformation> splineInfo1,
             QList<SplineInformation> splineInfo2,
             float frc)
{

  QList<SplineInformation> splineInfo;

  for(int i=0; i<qMin(splineInfo1.size(),
          splineInfo2.size()); i++)
    {
      splineInfo.append(interpolate(splineInfo1[i],
            splineInfo2[i],
            frc));
    }

  int st = splineInfo.size();
  for(int i=st; i<splineInfo1.size(); i++)
    {
      QGradientStops stops = splineInfo1[i].gradientStops();
      QGradientStops newStops;
      for(int j=0; j<stops.size(); j++)
  {
    float pos = stops[j].first;
    QColor col = stops[j].second;
    float r,g,b,a;
    r = col.red();
    g = col.green();
    b = col.blue();
    a = (1-frc)*col.alpha();
    col = QColor(r,g,b,a);

    newStops << QGradientStop(pos, col);
  }

      SplineInformation sinfo;
      sinfo.setName(splineInfo1[i].name());
      sinfo.setOn(splineInfo1[i].on());
      sinfo.setPoints(splineInfo1[i].points());
      sinfo.setNormalWidths(splineInfo1[i].normalWidths());
      sinfo.setNormalRotations(splineInfo1[i].normalRotations());
      sinfo.setGradientStops(newStops);

      int bot, top;
      float botop, topop;
      splineInfo1[i].gradLimits(bot, top);
      splineInfo1[i].opMod(botop, topop);
      sinfo.setGradLimits(bot, top);
      sinfo.setOpmod(botop, topop);

      splineInfo.append(sinfo);
    }

  st = splineInfo.size();
  for(int i=st; i<splineInfo2.size(); i++)
    {
      QGradientStops stops = splineInfo2[i].gradientStops();
      QGradientStops newStops;
      for(int j=0; j<stops.size(); j++)
  {
    float pos = stops[j].first;
    QColor col = stops[j].second;
    float r,g,b,a;
    r = col.red();
    g = col.green();
    b = col.blue();
    a = frc*col.alpha();
    col = QColor(r,g,b,a);

    newStops << QGradientStop(pos, col);
  }

      SplineInformation sinfo;
      sinfo.setName(splineInfo2[i].name());
      sinfo.setOn(splineInfo2[i].on());
      sinfo.setPoints(splineInfo2[i].points());
      sinfo.setNormalWidths(splineInfo2[i].normalWidths());
      sinfo.setNormalRotations(splineInfo2[i].normalRotations());
      sinfo.setGradientStops(newStops);

      int bot, top;
      float botop, topop;
      splineInfo2[i].gradLimits(bot, top);
      splineInfo2[i].opMod(botop, topop);
      sinfo.setGradLimits(bot, top);
      sinfo.setOpmod(botop, topop);

      splineInfo.append(sinfo);
    }


  return splineInfo;
}

QGradientStops
SplineInformation::interpolateGradientStops(QGradientStops stops1,
              QGradientStops stops2,
              float frc)
{
  QVector<float> pos;

  for(int i=0; i<stops1.size(); i++)
    pos.append(stops1[i].first);

  for(int i=0; i<stops2.size(); i++)
    {
      float pos2 = stops2[i].first;
      bool flag = true;
      for(int j=0; j<stops1.size(); j++)
  {
    if (fabs(pos[j] - pos2) < 0.0001)
      {
        flag = false;
        break;
      }
  }
      if (flag)
  pos.append(pos2);
    }

  qSort(pos.begin(), pos.end());

  QGradientStops gradStops1 = StaticFunctions::resampleGradientStops(stops1);
  QGradientStops gradStops2 = StaticFunctions::resampleGradientStops(stops2);

  QGradientStops gradStops;
  int gsize = gradStops1.size()-1;
  for(int i=0; i<pos.size(); i++)
    {
      int idx = pos[i]*gsize;
      QColor color1 = gradStops1[idx].second;
      QColor color2 = gradStops2[idx].second;

      // linear interpolation of colors
      float rb,gb,bb,ab, re,ge,be,ae;
      rb = color1.red();
      gb = color1.green();
      bb = color1.blue();
      ab = color1.alpha();
      re = color2.red();
      ge = color2.green();
      be = color2.blue();
      ae = color2.alpha();

      float r,g,b,a;
      r = rb + frc*(re-rb);
      g = gb + frc*(ge-gb);
      b = bb + frc*(be-bb);
      a = ab + frc*(ae-ab);


      QColor color = QColor(r,g,b,a);
      gradStops << QGradientStop(pos[i], color);
    }

  return gradStops;
}
