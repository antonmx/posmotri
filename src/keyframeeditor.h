#ifndef KEYFRAMEEDITOR_H
#define KEYFRAMEEDITOR_H

#include "global.h"


class SelectRegion {
public :
    bool valid;
    int frame0, frame1;
    int keyframe0, keyframe1;
};


namespace Ui {
  class KeyFrameEditor;
}

class KeyFrameEditor : public QWidget {
  Q_OBJECT;

private:
  Ui::KeyFrameEditor * ui;

public :
  KeyFrameEditor ( QWidget *parent=0 );

  void paintEvent ( QPaintEvent * );
  void resizeEvent ( QResizeEvent * );

  void mouseReleaseEvent(QMouseEvent*);
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

  int startFrame();
  int endFrame();
  int currentFrame();

signals :
  void showMessage(QString, bool);
  void setKeyFrame(int);
  void removeKeyFrame(int);
  void removeKeyFrames(int, int);
  void reorder(QList<int>);
  void setKeyFrameNumber(int, int);
  void setPlay(bool);
  void playFrameNumber(int);
  void updateGL();
  void startPlay();
  void endPlay();
  void copyFrame(int);
  void pasteFrame(int);
  void pasteFrameOnTop(int);
  void pasteFrameOnTop(int, int);
  void editFrameInterpolation(int);
  void setKeyFrameNumbers(QList<int>);

public slots :
  void setCurrentFrame(int);
  void loadKeyframes(QList<int>, QList<QImage>);
  void clear();
  void setImage(int, QImage);
  void setHiresMode(bool);
  void resetCurrentFrame();
  void setPlayFrames(bool);
  void playKeyFrames(int, int, int);
  void addKeyFrameNumbers(QList<int>);
  void moveTo(int=0);
  void setKeyFrame();

private slots :
  void increaseFrameStep();
  void decreaseFrameStep();
  void removeKeyFrame();
  void playKeyFrames();
  void playPressed();
  void copyFrame();
  void pasteFrame();
  void clearRegion();
  void editFrameInterpolation();

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private :
   QAction * copyAct;
   QAction * pasteAct;
   QAction * interpolateAct;
   QAction * removeAct;
   QAction * setAct;
   QAction * deselectAct;

  SelectRegion m_selectRegion;
  int m_lineHeight;
  const int m_tickHeight;
  int m_tickStep;
  QPoint m_p0, m_p1;
  const int m_imgSize, m_imgSpacer;
  int m_editorHeight;
  int m_minFrame, m_maxFrame, m_frameStep;
  int m_prevX;
  bool m_reordered;
  int m_currFrame;
  bool m_draggingCurrFrame;
  int m_selected;
  int m_pressedMinFrame;
  bool m_playFrames;
  bool m_hiresMode;

  int m_copyFno;
  QImage m_copyImage;

  QList<int> m_fno;
  QList<QRect> m_fRect;
  QList<QImage> m_fImage;


  int m_modifiers;
  QList<float> m_ratioBefore;
  QList<float> m_ratioAfter;

  void reorder();
  void calcRect();
  void calcMaxFrame();
  void updateSelectRegion();
  int frameUnderPoint(QPoint);
  void moveCurrentFrame(QPoint);

  void showHelp();

};





#endif
