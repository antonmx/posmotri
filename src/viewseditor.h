#ifndef VIEWSEDITOR_H
#define VIEWSEDITOR_H

#include "glewinitialisation.h"
#include "viewinformation.h"
#include "PromotedWidgets.h"
#include "ui_viewseditor.h"


class ViewsEditor : public QWidget {
  Q_OBJECT;

 public :
  ViewsEditor(QWidget *parent=0);

  void paintEvent(QPaintEvent*);
  void resizeEvent(QResizeEvent*);
  void mousePressEvent(QMouseEvent*);

  void load(const QConfigMe &);
  void save(QConfigMe &) const;

 signals :
  void showMessage(QString, bool);
  void currentView();
  void updateVolInfo(int);
  void updateVolInfo(int, int);
  void updateVolumeBounds(int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, int, qglviewer::Vec, qglviewer::Vec);
  void updateVolumeBounds(int, int, int, int, qglviewer::Vec, qglviewer::Vec);
  void updateLookFrom(qglviewer::Vec, qglviewer::Quaternion, float);
  void updateLightInfo(LightingInformation);
  void updateBrickInfo(QList<BrickInformation>);
  void updateTransferFunctionManager(QList<SplineInformation>);
  void updateParameters(float, float,
			int,
			bool, bool, qglviewer::Vec,
			QString,
			int, int, QString, QString, QString);
  void updateTagColors();
  void updateGL();

 public slots :
  void clear();
  void setHiresMode(bool);
  void addView(float,
	       float,
	       bool, bool,
	       qglviewer::Vec,
	       qglviewer::Vec, qglviewer::Quaternion,
	       float,
	       QImage,
	       int,
	       LightingInformation,
	       QList<BrickInformation>,
	       qglviewer::Vec, qglviewer::Vec,
	       QList<SplineInformation>,
	       int, int, QString, QString, QString);
  
 private slots :
  void on_add_pressed();
  void on_remove_pressed();
  void on_restore_pressed();
  void on_up_pressed();
  void on_down_pressed();
  void updateTransition();

 private :
  Ui::ViewsEditorWidget * ui;

  int m_leftMargin, m_topMargin;
  int m_row, m_maxRows;
  int m_imgSize;

  int m_selected;
  QList<QRect> m_Rect;
  QList<ViewInformation*> m_viewInfo;

  bool m_hiresMode;

  bool m_inTransition;
  int m_fade;

  void calcRect();
  void drawView(QPainter*, QColor, QColor, int, QRect, QImage);
};


#endif
