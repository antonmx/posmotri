#include "networkinformation.h"

NetworkInformation::NetworkInformation() { clear(); }

void
NetworkInformation::clear()
{
  filename.clear();
  Vopacity = 1;
  Eopacity = 1;
  Vatt = 0;
  Eatt = 0;
  userVmin = userVmax = 0;
  userEmin = userEmax = 0;
  Vstops.clear();
  Estops.clear();
  scalee = scalev = 1.0;
}

NetworkInformation&
NetworkInformation::operator=(const NetworkInformation& ti)
{
  filename = ti.filename;
  Vopacity = ti.Vopacity;
  Eopacity = ti.Eopacity;
  Vatt = ti.Vatt;
  Eatt = ti.Eatt;
  userVmin = ti.userVmin;
  userVmax = ti.userVmax;
  userEmin = ti.userEmin;
  userEmax = ti.userEmax;
  Vstops = ti.Vstops;
  Estops = ti.Estops;
  scalee = ti.scalee;
  scalev = ti.scalev;
  return *this;
}

NetworkInformation
NetworkInformation::interpolate(const NetworkInformation & tinfo1,
                                const NetworkInformation & tinfo2,
                                float frc)
{
  NetworkInformation tinfo;
  tinfo.filename = tinfo1.filename;

  tinfo.Vopacity = (1-frc)*tinfo1.Vopacity + frc*tinfo2.Vopacity;
  tinfo.Eopacity = (1-frc)*tinfo1.Eopacity + frc*tinfo2.Eopacity;

  tinfo.scalee = (1-frc)*tinfo1.scalee + frc*tinfo2.scalee;
  tinfo.scalev = (1-frc)*tinfo1.scalev + frc*tinfo2.scalev;

  if (frc < 0.5)
    {
      tinfo.Vstops = tinfo1.Vstops;
      tinfo.Estops = tinfo1.Estops;
    }
  else
    {
      tinfo.Vstops = tinfo2.Vstops;
      tinfo.Estops = tinfo2.Estops;
    }

  if (tinfo1.Vatt == tinfo2.Vatt)
    {
      tinfo.Vatt = tinfo1.Vatt;
      tinfo.userVmin = (1-frc)*tinfo1.userVmin + frc*tinfo2.userVmin;
      tinfo.userVmax = (1-frc)*tinfo1.userVmax + frc*tinfo2.userVmax;
    }
  else
    {
      // modulate opacity & scale near 0.5 if the attributes are changing
      float opf = qAbs(frc - 0.5f);
      opf = qMin(opf*10, 1.0f);
      tinfo.Vopacity *= opf;
      tinfo.scalev *= opf;

      if (frc < 0.5)
	{
	  tinfo.Vatt = tinfo1.Vatt;
	  tinfo.userVmin = tinfo1.userVmin;
	  tinfo.userVmax = tinfo1.userVmax;
	}
      else
	{
	  tinfo.Vatt = tinfo2.Vatt;
	  tinfo.userVmin = tinfo2.userVmin;
	  tinfo.userVmax = tinfo2.userVmax;
	}
    }

  if (tinfo1.Eatt == tinfo2.Eatt)
    {
      tinfo.Eatt = tinfo1.Eatt;
      tinfo.userEmin = (1-frc)*tinfo1.userEmin + frc*tinfo2.userEmin;
      tinfo.userEmax = (1-frc)*tinfo1.userEmax + frc*tinfo2.userEmax;
    }
  else
    {
      // modulate opacity & scale near 0.5 if the attributes are changing
      float opf = qAbs(frc - 0.5f);
      opf = qMin(opf*10, 1.0f);
      tinfo.Eopacity *= opf;
      tinfo.scalee *= opf;

      if (frc < 0.5)
	{
	  tinfo.Eatt = tinfo1.Eatt;
	  tinfo.userEmin = tinfo1.userEmin;
	  tinfo.userEmax = tinfo1.userEmax;
	}
      else
	{
	  tinfo.Eatt = tinfo2.Eatt;
	  tinfo.userEmin = tinfo2.userEmin;
	  tinfo.userEmax = tinfo2.userEmax;
	}
    }



  return tinfo;
}

QList<NetworkInformation> NetworkInformation::interpolate(
  const QList<NetworkInformation> & tinfo1,
  const QList<NetworkInformation> & tinfo2,
  float frc)
{
  QVector<int> present;
  present.resize(tinfo1.count());
  for(int i=0; i<tinfo1.count(); i++)
    {
      present[i] = -1;
      for(int j=0; j<tinfo2.count(); j++)
	{
	  if (tinfo1[i].filename == tinfo2[j].filename)
	    {
	      present[i] = j;
	      break;
	    }
	}
    }

  QList<NetworkInformation> tinfo;
  for(int i=0; i<tinfo1.count(); i++)
    {
      if (present[i] >= 0)
	{
	  NetworkInformation ti;
	  ti = interpolate(tinfo1[i], tinfo2[present[i]], frc);
	  tinfo.append(ti);
	}
      else
	tinfo.append(tinfo1[i]);
    }

  return tinfo;
}

void NetworkInformation::save(QConfigMe & cfg) const {
  cfg.beginGroup("NetworkInformation");
  cfg.setValue("filename", filename);
  cfg.setValue("vopacity", Vopacity);  
  cfg.setValue("eopacity", Eopacity);  
  cfg.setValue("scalee", scalee);  
  cfg.setValue("scalev", scalev);
  cfg.beginArray("Vstops");
  foreach(QGradientStop st, Vstops) {
    cfg.setValue("pos", st.first);
    cfg.setValue("col", st.second);
  }
  cfg.endArray();
  cfg.beginArray("Estops");
  foreach(QGradientStop st, Estops) {
    cfg.setValue("pos", st.first);
    cfg.setValue("col", st.second);
  }
  cfg.endArray();
  cfg.setValue("vatt", Vatt);  
  cfg.setValue("uservmin", userVmin);  
  cfg.setValue("uservmax", userVmax);  
  cfg.setValue("eatt", Eatt);  
  cfg.setValue("useremin", userEmin);  
  cfg.setValue("useremax", userEmax);
  cfg.endGroup();
}

void NetworkInformation::load(const QConfigMe & cfg) {
  clear();
  cfg.beginGroup("NetworkInformation");
  cfg.getValue("filename", filename);
  cfg.getValue("vopacity", Vopacity);  
  cfg.getValue("eopacity", Eopacity);  
  cfg.getValue("scalee", scalee);  
  cfg.getValue("scalev", scalev);
  int sz = cfg.beginArray("Vstops");
  for (int i=0; i<sz; i++) {
    QGradientStop st;    
    cfg.getValue("pos", st.first);
    cfg.getValue("col", st.second);
    Vstops.append(st);
  }
  cfg.endArray();
  cfg.beginArray("Estops");
  for (int i=0; i<sz; i++) {
    QGradientStop st;    
    cfg.getValue("pos", st.first);
    cfg.getValue("col", st.second);
    Estops.append(st);
  }
  cfg.endArray();
  cfg.getValue("vatt", Vatt);  
  cfg.getValue("uservmin", userVmin);  
  cfg.getValue("uservmax", userVmax);  
  cfg.getValue("eatt", Eatt);  
  cfg.getValue("useremin", userEmin);  
  cfg.getValue("useremax", userEmax);
  cfg.endGroup();
}
