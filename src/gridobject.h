#ifndef GRIDOBJECT_H
#define GRIDOBJECT_H

#include <QGLViewer/qglviewer.h>
#include "PromotedWidgets.h"

class GridObjectUndo {
 public :
  GridObjectUndo();
  ~GridObjectUndo();
  
  void clear();
  void append(int, int, QList<qglviewer::Vec>);

  void undo();
  void redo();

  void colrow(int&, int&);
  QList<qglviewer::Vec> points();

 private :
  int m_index;
  QList< QList<qglviewer::Vec> > m_points;
  QList<int> m_cols;
  QList<int> m_rows;

  void clearTop();
};

class GridObject {
public :
  GridObject();
  ~GridObject();
  
  void load(const QConfigMe &);
  void save(QConfigMe &) const;

  void set(const GridObject&);  
  GridObject get();

  GridObject& operator=(const GridObject&);

  void undo();
  void redo();
  void updateUndo();

  bool showPointNumbers();
  bool showPoints();
  qglviewer::Vec color();
  float opacity();
  QList<qglviewer::Vec> points();
  int columns();
  int rows();

  qglviewer::Vec getPoint(int);
  void setPoint(int, qglviewer::Vec);

  void regrid();
  QList<qglviewer::Vec> gridPoints();
  QList< QPair<qglviewer::Vec, qglviewer::Vec> > getPointsAndNormals();

  void setShowPointNumbers(bool);
  void setShowPoints(bool);
  void setColor(qglviewer::Vec);
  void setOpacity(float);
  void normalize();
  void setColRow(int, int);
  void setPoints(QList<qglviewer::Vec>);

  void setPointPressed(int);
  int getPointPressed();

  void draw(QGLViewer*, bool, bool, qglviewer::Vec);
  void postdraw(QGLViewer*, int, int, bool);

  void insertRow(int);
  void insertCol(int);
  void removeRow(int);
  void removeCol(int);

 private :
  GridObjectUndo m_undo;

  int m_cols, m_rows;
  bool m_showPointNumbers;
  bool m_showPoints;
  qglviewer::Vec m_color;
  float m_opacity;
  QList<qglviewer::Vec> m_points;
  QList<qglviewer::Vec> m_grid;
  int m_pointPressed;
  bool m_updateFlag;
  
  void drawLines(QGLViewer*, bool, bool);

  void postdrawPointNumbers(QGLViewer*);
  void postdrawGrab(QGLViewer*, int, int);
};

#endif
