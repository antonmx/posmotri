#ifndef MOPPLUGININTERFACE_H
#define MOPPLUGININTERFACE_H

//#include <QtGui>
#include <QGLViewer/qglviewer.h>
using namespace qglviewer;

class MopPluginInterface
{
 public :
  virtual ~MopPluginInterface() {}

  // register plugin with the main program
  virtual QStringList registerPlugin() = 0;

  virtual void setData(int, int, int, uchar*, QList<Vec>)=0;

  virtual void init() = 0;
  virtual bool start() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(MopPluginInterface,
		    "drishti.mop.Plugin.PluginInterface/1.0");
QT_END_NAMESPACE

#endif

