#include "global.h"
#include "keyframeeditor.h"
#include "propertyeditor.h"
#include "ui_keyframeeditor.h"
#include <QDebug>
#include <QMenu>

#include <algorithm>
using namespace std;

// ---------- class for sorting -----------
class tag {
public :
  int id;
  float loc;
  bool operator<(const tag& a) const {
    return (loc < a.loc);
  }

  tag& operator=(const tag& a) {
    id = a.id;
    loc = a.loc;
    return *this;
  }
};
//-----------------------------------------




KeyFrameEditor::KeyFrameEditor(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::KeyFrameEditor)
  , copy(new QAction("Copy frame", this))
  , paste(new QAction("Paste frame", this))
  , save(new QAction("Save frame", this))
  , remove(new QAction("Remove frame", this))
  , addnew(new QAction("Add new frame", this))
  , interpolate(new QAction("Change interpolation", this))
  , deselect(new QAction("Clear selection", this))
  , m_tickHeight(10)
  , m_tickStep(50)
  , m_imgSpacer(35)
  , m_imgSize(100)
  , m_minFrame(1)
  , m_frameStep(10)
  , m_currFrame(1)
  , m_selected(-1)
  , m_playFrames(false)
  , m_hiresMode(false)
  , m_copyFno(-1)
{

  ui->setupUi(this);
  ui->zoomP->setAutoRepeat(true);
  ui->zoomM->setAutoRepeat(true);

  m_lineHeight = ui->buttons->geometry().bottom();
  m_p0 = QPoint(60, m_lineHeight);
  m_p1 = QPoint(100, m_lineHeight);
  m_editorHeight = m_lineHeight + m_tickHeight + m_imgSpacer + m_imgSize + 10;

  calcMaxFrame();
  clear();

  connect(copy, SIGNAL(triggered()), SLOT(copyFrame()));
  connect(paste, SIGNAL(triggered()), SLOT(pasteFrame()));
  connect(interpolate, SIGNAL(triggered()), SLOT(editFrameInterpolation()));
  connect(save, SIGNAL(triggered()), SLOT(saveKeyFrame()));
  connect(remove, SIGNAL(triggered()), SLOT(removeKeyFrame()));
  connect(addnew, SIGNAL(triggered()), SLOT(setKeyFrame()));
  connect(deselect, SIGNAL(triggered()), SLOT(clearRegion()));

  connect(ui->zoomP, SIGNAL(pressed()), SLOT(decreaseFrameStep()));
  connect(ui->zoomM, SIGNAL(pressed()), SLOT(increaseFrameStep()));
  connect(ui->playpause, SIGNAL(pressed()), SLOT(playPressed()));
  connect(ui->rewind, SIGNAL(pressed()),SLOT(resetCurrentFrame()));
  connect(ui->goTo, SIGNAL(editingFinished()), SLOT(moveTo()));
  connect(this, SIGNAL(startPlay()), SLOT(playKeyFrames()));

}


void KeyFrameEditor::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this);
  menu.addAction(cutAct);
  menu.addAction(copyAct);
  menu.addAction(pasteAct);
  menu.exec(event->globalPos());
}


int KeyFrameEditor::startFrame() {
  return (m_fno.count() > 0) ? m_fno[0] : 1;
}


int KeyFrameEditor::endFrame() {
  return (m_fno.count() > 0) ?  m_fno[m_fno.count()-1] : 1;
}


int KeyFrameEditor::currentFrame() {
  return m_currFrame;
}



void KeyFrameEditor::setHiresMode(bool flag) {
  m_hiresMode = flag;
  setPlayFrames(false);
}


void KeyFrameEditor::resetCurrentFrame() {
  m_currFrame = startFrame();
  m_minFrame = qMax(1, m_currFrame);
  calcMaxFrame();
  setPlayFrames(false);
}


void KeyFrameEditor::playPressed() {
  if ( ! m_hiresMode ) {
    emit showMessage("Play available only in Hires Mode. Press F2 to switch to Hires mode", true);
    return;
  }
  setPlayFrames(!m_playFrames);
}


void KeyFrameEditor::setPlayFrames(bool flag) {
  m_playFrames = flag;
  ui->playpause->setText( m_playFrames ? "||" : ">");
  update();
  if (m_playFrames)
    emit startPlay();
  else
    emit endPlay();
  qApp->processEvents();
}

void KeyFrameEditor::playKeyFrames(int start, int end, int step) {

  if ( m_fno.count() <= 1  || start > m_fno[m_fno.count()-1] ) {
    setPlayFrames(false);
    emit showMessage("Nothing to play.", true);
    qApp->processEvents();
    return;
  }

  ui->playpause->setText("||");
  m_playFrames = true;

  for (m_currFrame=start; m_currFrame<=end; m_currFrame+=step)  {

    if (m_currFrame > m_maxFrame) {
      m_minFrame = qMax(1, m_currFrame-1);
      calcMaxFrame();
    }
    update();
    emit playFrameNumber(m_currFrame);
    qApp->processEvents();
  }

  setPlayFrames(false);
  emit showMessage("Done", false);
  qApp->processEvents();

  if (Global::batchMode())
    qApp->quit();

}


void KeyFrameEditor::playKeyFrames() {

  if (!m_playFrames)
    return;

  if (m_currFrame < m_fno[0])
    m_currFrame = m_fno[0];

  int startFrame = m_currFrame;
  int endFrame = m_fno[m_fno.count()-1];
  if (m_selectRegion.valid &&
      m_selectRegion.frame1 > m_selectRegion.frame0)  {
    startFrame = qMax(m_selectRegion.frame0, m_fno[0]);
    endFrame = qMin(m_selectRegion.frame1, m_fno[m_fno.count()-1]);
  }

  playKeyFrames(startFrame, endFrame, 1);

}


void KeyFrameEditor::clear() {
  m_copyFno = -1;
  m_playFrames = false;
  m_draggingCurrFrame = false;
  m_reordered = false;
  m_selectRegion.valid = false;
  m_minFrame = 1;
  m_frameStep = 10;
  calcMaxFrame();
  m_fno.clear();
  m_fRect.clear();
  m_fImage.clear();
  update();
}


void KeyFrameEditor::calcRect() {
  for(int i=0; i<m_fno.count(); i++) {
    const int fno = m_fno[i];
    if (fno >= m_minFrame && fno <= m_maxFrame)  {
      int tick = m_p0.x() + (fno-m_minFrame)*m_tickStep/(m_frameStep);
      m_fRect[i] = QRect(tick-m_imgSize/2,
                         m_lineHeight+m_tickHeight+m_imgSpacer,
                         m_imgSize, m_imgSize);
    }  else
      m_fRect[i] = QRect(-10,-10,1,1);
  }
}


void KeyFrameEditor::calcMaxFrame() {
  m_maxFrame = m_minFrame + m_frameStep*(m_p1.x()-m_p0.x())/(float)m_tickStep;
  calcRect();
}


void KeyFrameEditor::paintEvent(QPaintEvent *event) {

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  // draw selected region

  if ( m_selectRegion.valid
       && m_selectRegion.frame1 >= m_minFrame
       && m_selectRegion.frame0 <= m_maxFrame) {

    const int f0 = (m_selectRegion.frame0 < m_minFrame) ?  m_minFrame : m_selectRegion.frame0;
    const int f1 = (m_selectRegion.frame1 > m_maxFrame) ?  m_maxFrame : m_selectRegion.frame1;
    const int tick0 = m_p0.x() + (f0-m_minFrame)*m_tickStep/m_frameStep;
    const int tick1 = m_p0.x() + (f1-m_minFrame)*m_tickStep/m_frameStep;

    p.setBrush(QColor(250, 150, 100));
    p.setPen(Qt::transparent);
    p.drawRect(tick0, m_lineHeight - m_tickHeight, tick1 - tick0,  m_tickHeight);

  }

    // draw visible range

  const int bg = 50;
  const int sz = size().width()-100;

  p.setBrush(Qt::transparent);
  p.setPen( QPen(QColor(50, 50, 50), 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin) );
  p.drawLine(QPoint(5,5), QPoint(bg-10, 5));
  p.drawLine(QPoint(bg+sz+10,5), QPoint(bg+sz+45, 5));

  p.setPen(QPen(QColor(150, 150, 150), 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p.drawLine(QPoint(bg,5), QPoint(bg+sz, 5));

  if (m_fno.count() >= 2) {

    const float nframes = (m_fno[m_fno.count()-1]-m_fno[0]);

    // --- draw for selection range ----
    if (m_selectRegion.valid) {

      int f0 = sz * ( m_selectRegion.frame0 - m_fno[0]) / nframes;
      if (f0 < 0) f0 = -bg+10;
      if (f0 > sz) f0 = sz+10;
      f0 += bg;

      int f1 = sz * ( m_selectRegion.frame1 - m_fno[0]) / nframes;
      if (f1 < 0) f1 = -bg+40;
      if (f1 > sz) f1 = sz+40;
      f1 += bg;

      p.setPen(QPen(QColor(250, 150, 100), 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      p.drawLine(QPoint(f0,5), QPoint(f1, 5));

    }

    for(int i=0; i<m_fno.count(); i++)  {

      int v0 = sz*(m_fno[i]-m_fno[0])/nframes;
      if (v0 < 0) v0 = -bg+10;
      if (v0 > sz) v0 = sz+10;
      v0 += bg;

      p.setPen(QPen(Qt::black, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      p.drawPoint(v0,5);
      p.setPen(QPen(Qt::lightGray, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      p.drawPoint(v0,5);

    }

    int bg0 = sz*(m_minFrame-m_fno[0])/nframes;
    if (bg0 < 0) bg0 = -bg+10;
    if (bg0 > sz) bg0 = sz+10;
    bg0 += bg;

    int bg1 = sz*(m_maxFrame-m_fno[0])/nframes;
    if (bg1 < 0) bg1 = -bg+40;
    if (bg1 > sz) bg1 = sz+40;
    bg1 += bg;

    p.setPen(QPen(QColor(255, 255, 255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawLine(QPoint(bg0,5), QPoint(bg1, 5));

  }

  // draw ticks

  if (m_playFrames || m_draggingCurrFrame)  {
    p.setBrush(QColor(70, 50, 20, 50));
    p.setPen(Qt::transparent);
    p.drawRect(m_p0.x()-5, m_lineHeight-m_tickHeight-15, m_p1.x()-m_p0.x()+10, 2*m_tickHeight+25);
  }

  p.setBrush(Qt::transparent);
  p.setPen(Qt::darkGray);
  p.drawLine(m_p0, m_p1);

  const int nticks = (m_p1.x() - m_p0.x())/m_tickStep;
  int prevtick = 0;
  for(int t=0; t<=nticks; t++) {

    int frameNumber = m_minFrame + t*m_frameStep;
    int tick = m_p0.x() + t*m_tickStep;
    int sticks = 10;

    p.drawLine(tick, m_lineHeight-m_tickHeight, tick, m_lineHeight+m_tickHeight);

    int tk = tick;
    if (frameNumber < 10)
      tk = tick-2;
    else if (frameNumber < 100)
      tk = tick-7;
    else if (frameNumber < 1000)
      tk = tick-10;
    else
      tk = tick-15;

    p.drawText(tk, m_lineHeight-m_tickHeight-2, QString("%1").arg(frameNumber));

    // draw inbetween smaller ticks
    if (m_frameStep > 1 && t > 0 && sticks > 0)	{
      int tkstep = (tick-prevtick)/sticks;
      for(int s=1; s<sticks; s++)  {
        int stk = prevtick + s*tkstep;
        p.drawLine(stk, m_lineHeight, stk, m_lineHeight-m_tickHeight/2);
      }
    }

    prevtick = tick;

  }

  // draw current frame

  if (m_currFrame >= m_minFrame  &&  m_currFrame <= m_maxFrame) {

    p.setFont(QFont("Helvetica", 10));
    p.setPen(QPen(QColor(30, 100, 60),2));
    const int tick = m_p0.x() + (m_currFrame-m_minFrame)*m_tickStep/(m_frameStep);
    p.drawLine(tick, m_lineHeight-m_tickHeight-5, tick, m_lineHeight+m_tickHeight+5);

    int tk = tick-10;
    if (m_currFrame < 10)
      tk = tick-15;
    else if (m_currFrame < 100)
      tk = tick-20;
    else if (m_currFrame < 1000)
      tk = tick-25;
    else
      tk = tick-30;
    p.drawText(tk, m_lineHeight+m_tickHeight+5, QString("%1").arg(m_currFrame));

  }

  // draw keyframes

  p.setFont(QFont("Helvetica", 12));

  for(int i=0; i<m_fno.count(); i++) {

    if (m_fno[i] >= m_minFrame && m_fno[i] <= m_maxFrame) {

      QRect rect = m_fRect[i];
      const QColor penColor = (m_selected == i) ? QColor(50, 30, 10) : QColor(100, 100, 100);
      const QColor brushColor = (m_selected == i) ? QColor(250, 150, 100) :
             ( m_selectRegion.valid &&  m_selectRegion.keyframe0 > -1
               && i >= m_selectRegion.keyframe0 &&  i <= m_selectRegion.keyframe1)
                                                    ?  QColor(250, 200, 150) : QColor(170, 170, 170);

      const int tick = m_p0.x() + (m_fno[i]-m_minFrame)*m_tickStep/m_frameStep;

      p.setPen(penColor);
      p.drawLine(tick, m_lineHeight, tick, m_lineHeight+m_tickHeight+m_imgSpacer);
      p.drawText(tick+2, rect.y()-2, QString::number(m_fno[i]));

      QRect prect = rect.adjusted(2, 2, -2, -2);
      p.drawImage(prect, m_fImage[i], QRect(0, 0, 100, 100));

      p.setBrush(Qt::transparent);
      p.setPen(QPen(penColor, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      p.drawRoundRect(rect);
      p.setPen(QPen(brushColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      p.drawRoundRect(rect);
    }

    if (Global::morphTF()) {
      p.setFont(QFont("Helvetica", 8));
      p.setPen(QPen(QColor(130, 100, 60),2));
      p.drawText(230, 30, "Transfer function morphing enabled");
    }

  }

}

void KeyFrameEditor::resizeEvent(QResizeEvent *event) {
  m_lineHeight = 30 + ui->spacer->geometry().top();
  m_p0 = QPoint(60, m_lineHeight);
  m_p1 = QPoint(size().width()-60, m_lineHeight);
  m_editorHeight = m_lineHeight + m_tickHeight + m_imgSpacer + m_imgSize + 10;
  setMaximumHeight(m_editorHeight);
  setMinimumHeight(m_editorHeight);
  calcMaxFrame();
}


static inline int frameStep2tickStep(int frameStep) {
  if (frameStep > 100)
    return 200;
  if (frameStep > 10)
    return 100;
  if (frameStep > 1)
    return 50;
  return 20;
}

void KeyFrameEditor::increaseFrameStep() {
  if (m_frameStep == 1)
    m_frameStep = 10;
  else if (m_frameStep == 10)
    m_frameStep = 100;
  else if (m_frameStep < 10000-100)
    m_frameStep += 100;
  m_tickStep = frameStep2tickStep(m_frameStep);
  ui->zoomP->setEnabled(m_frameStep < 10000);
  calcMaxFrame();
  update();
}

void KeyFrameEditor::decreaseFrameStep() {
  if (m_frameStep > 100)
    m_frameStep -= 100;
  else if (m_frameStep > 10)
    m_frameStep = 10;
  else
    m_frameStep = 1;
  m_tickStep = frameStep2tickStep(m_frameStep);
  ui->zoomP->setEnabled(m_frameStep > 1);
  calcMaxFrame();
  update();
}


int KeyFrameEditor::frameUnderPoint(QPoint pos) {
  if (pos.x() <= m_p0.x())
    return m_minFrame;
  if (pos.x() >= m_p1.x())
    return m_maxFrame;
  return m_minFrame + (m_maxFrame-m_minFrame)*(pos.x()-m_p0.x())/(float)(m_p1.x()-m_p0.x());
}


void KeyFrameEditor::moveCurrentFrame(QPoint pos) {
  m_currFrame = frameUnderPoint(pos);
  update();
  emit playFrameNumber(m_currFrame);
  qApp->processEvents();
}


// NEVER USED !
/*
void KeyFrameEditor::applyMove(int pfrm, int nfrm) {
  int startKF = 0;
  int endKF = m_fno.count()-1;

  if (m_selectRegion.valid &&
      m_selected >= m_selectRegion.keyframe0 &&
      m_selected <= m_selectRegion.keyframe1)
    {
      startKF = m_selectRegion.keyframe0;
      endKF = m_selectRegion.keyframe1;
    }

  if (m_selected < startKF ||
      m_selected > endKF)
    return;


  int diff = nfrm - pfrm;
  bool ok = true;

  int frame0 = m_fno[startKF];
  int frame1 = m_fno[endKF];
  int zeroframe = 0;
  if (startKF > 0) zeroframe = m_fno[startKF-1];

  if (frame0 + diff <= zeroframe)
    {
      diff = zeroframe - frame0;
      diff++;
    }
  if (endKF < m_fno.count()-1)
    {
      if (frame1 + diff >= m_fno[endKF+1])
  {
    diff = m_fno[endKF+1] - frame1;
    diff--;
  }
    }

  for(int fi=startKF; fi<=endKF; fi++)
    m_fno[fi] += diff;

  emit setKeyFrameNumbers(m_fno);
}
*/


void KeyFrameEditor::updateSelectRegion() {

  if ( ! m_selectRegion.valid  || ! m_fno.count() )
    return;

  int sf, ef;
  sf = m_selectRegion.frame0;
  ef = m_selectRegion.frame1;
  if (sf > ef) {
    ef = m_selectRegion.frame0;
    sf = m_selectRegion.frame1;
  }

  m_selectRegion.keyframe0 = -1;
  m_selectRegion.keyframe1 = -1;

  for(int i=0; i<m_fno.count(); i++) {
    if (m_fno[i] >= sf) {
      m_selectRegion.keyframe0 = i;
      break;
    }
  }
  for(int i=m_fno.count()-1; i>=0; i--) {
    if (m_fno[i] <= ef) {
      m_selectRegion.keyframe1 = i;
      break;
    }
  }

}


void KeyFrameEditor::copyFrame() {
  if (m_selected<0) {
    emit showMessage("No frame selected for copying", true);
    return;
  }
  m_copyFno = m_fno[m_selected];
  m_copyImage = m_fImage[m_selected];
  emit copyFrame(m_selected);
  emit showMessage(QString("frame at %1 copied").arg(m_copyFno), false);
}

void KeyFrameEditor::pasteFrame() {

  if (m_copyFno < 0)  {
    emit showMessage("No frame selected for pasting", true);
    return;
  }

  if (m_selectRegion.valid)  {
    int startKF = m_selectRegion.keyframe0;
    int endKF = m_selectRegion.keyframe1;
    emit pasteFrameOnTop(startKF, endKF);
  } else {
    if (m_selected > -1)  {
      if (m_selected < m_fno.count())
        emit pasteFrameOnTop(m_selected);
      else
        QMessageBox::information
            (0, "", QString("Selected keyframe %1 does not exist").arg(m_selected));
    } else {

      int onTop = -1;
      for(int f=0; f<m_fno.count(); f++) {
        if (m_currFrame == m_fno[f]) {
          onTop = f;
          break;
        }
      }

      if (onTop > -1)
        emit pasteFrameOnTop(onTop);
      else {
        emit pasteFrame(m_currFrame);
        m_fno.append(m_currFrame);
        m_fRect.append(QRect(-10,-10,1,1));
        m_fImage.append(m_copyImage);
        calcRect();
        reorder();
        update();
      }

    }
  }

}


void KeyFrameEditor::keyPressEvent(QKeyEvent *event) {

  if ( event->key() != Qt::Key_Left  &&  event->key() != Qt::Key_Right ) {
    QWidget::keyPressEvent(event);
    return;
  }

  if   (event->key() == Qt::Key_Left)
    m_currFrame = qMax(m_currFrame-1, 1);
  else
    m_currFrame--;

  m_selected = -1;
  for(int f=0; f<m_fno.count(); f++) {
    if (m_currFrame == m_fno[f]) {
      m_selected = f;
      break;
    }
  }

  update();
  emit playFrameNumber(m_currFrame);
  qApp->processEvents();

}


void KeyFrameEditor::mouseMoveEvent(QMouseEvent *event) {

  QPoint clickPos = event->pos();

  if (m_draggingCurrFrame)

    moveCurrentFrame(clickPos);

  else if (m_selected < 0) {

    if (m_modifiers & Qt::ShiftModifier) {
      if (m_selectRegion.valid) {
        m_selectRegion.frame1 = frameUnderPoint(clickPos);
        updateSelectRegion();
        update();
      }
    } else { // move grid
      m_minFrame = qMax(1, m_pressedMinFrame + m_frameStep*(m_prevX-clickPos.x())/m_tickStep);
      calcMaxFrame();
      update();
    }

  } else { // dragging keyframe

    int pfrm = m_fno[m_selected];

    if (event->buttons() & Qt::MidButton) {

      int nfrm;
      if (clickPos.x() <= m_p0.x())
        nfrm = m_minFrame;
      else if (clickPos.x() >= m_p1.x())
        nfrm = m_maxFrame;
      else {
        float frc = (float)(clickPos.x()-m_p0.x())/(float)(m_p1.x()-m_p0.x());
        nfrm = m_minFrame + frc * (m_maxFrame-m_minFrame);
      }

      // apply move

      int startKF = 0;
      int endKF = m_fno.count()-1;
      if (m_selectRegion.valid &&
          m_selected >= m_selectRegion.keyframe0 &&
          m_selected <= m_selectRegion.keyframe1)  {
        startKF = m_selectRegion.keyframe0;
        endKF = m_selectRegion.keyframe1;
      }

      if (m_selected >= startKF && m_selected <= endKF) {

        const int frame0 = m_fno[startKF];
        const int frame1 = m_fno[endKF];
        const int zeroframe = (startKF > 0) ? m_fno[startKF-1] : 0;

        int diff = nfrm - pfrm;
        if (frame0 + diff <= zeroframe)
          diff = zeroframe - frame0 + 1;
        if ( endKF < m_fno.count()-1  &&  frame1 + diff >= m_fno[endKF+1] )
          diff = m_fno[endKF+1] - frame1 -1;

        for(int fi=startKF; fi<=endKF; fi++)
          m_fno[fi] += diff;

        emit setKeyFrameNumbers(m_fno);

      }

      calcRect();

    } else {

      if (clickPos.x() <= m_p0.x())
        m_fno[m_selected] = m_minFrame;
      else if (clickPos.x() >= m_p1.x())
        m_fno[m_selected] = m_maxFrame;
      else
        m_fno[m_selected] = m_minFrame
            + (m_maxFrame-m_minFrame)*(clickPos.x()-m_p0.x())/(float)(m_p1.x()-m_p0.x());

      if (m_selectRegion.valid &&
          m_selected >= m_selectRegion.keyframe0 &&
          m_selected <= m_selectRegion.keyframe1) { // apply shift

        int startKF = 0;
        int endKF = m_fno.count()-1;
        if (m_selectRegion.frame1 > m_selectRegion.frame0)  {
          startKF = m_selectRegion.keyframe0;
          endKF = m_selectRegion.keyframe1;
        }

        if (m_selected >= startKF && m_selected <= endKF) {

          int firstFrame = m_fno[startKF];
          int len = qMax(0, m_fno[m_selected] - m_fno[startKF]);
          for(int fi=startKF; fi<m_selected; fi++)
            m_fno[fi] = firstFrame + m_ratioBefore[fi-startKF]*len;
          for(int fi=startKF; fi<m_selected; fi++)  {
            if (m_fno[fi] >= m_fno[fi+1])
              m_fno[fi+1] = m_fno[fi]+1;
          }
          for(int fi=m_selected; fi>0; fi--)  {
            if (m_fno[fi] <= m_fno[fi-1])
              m_fno[fi-1] = m_fno[fi] - 1;
          }
          m_fno[0] = qMax(1, m_fno[0]);

          int lastFrame = m_fno[endKF];
          len = qMin(0, m_fno[m_selected] - lastFrame);
          for(int fi=m_selected+1; fi<=endKF; fi++)
            m_fno[fi] = lastFrame + m_ratioAfter[fi-m_selected-1]*len;
          for(int fi=endKF; fi>m_selected; fi--) {
            if (m_fno[fi] <= m_fno[fi-1])
              m_fno[fi-1] = m_fno[fi]-1;
          }
          for(int fi=1; fi<m_fno.count(); fi++) {
            if (m_fno[fi] <= m_fno[fi-1])
              m_fno[fi] = m_fno[fi-1] + 1;
          }

        }

        emit setKeyFrameNumbers(m_fno);
        calcRect();

      } else {
        if (m_selectRegion.valid &&
            m_selectRegion.frame1 > m_selectRegion.frame0) {
          if (pfrm < m_selectRegion.frame0 &&
              m_fno[m_selected] >= m_selectRegion.frame0)  {
            m_fno[m_selected] = m_selectRegion.frame0 - 1;
            emit showMessage("Cannot move keyframe into select region. Deselect region to move keyframe into that space. Right click to deselect region", true);
          } else if (pfrm > m_selectRegion.frame1 &&
                      m_fno[m_selected] <= m_selectRegion.frame1) {
            m_fno[m_selected] = m_selectRegion.frame1 + 1;
            emit showMessage("Cannot move keyframe into select region. Deselect region to move keyframe into that space. Right click to deselect region", true);
          }
        }

        emit setKeyFrameNumber(m_selected, m_fno[m_selected]);

        calcRect();
        reorder();

      }

    }

    m_currFrame = m_fno[m_selected];

    update();

  }

}


void KeyFrameEditor::mouseReleaseEvent(QMouseEvent *event) {

  m_modifiers = 0;
  m_draggingCurrFrame = false;

  if (m_reordered) {
    m_reordered = false;
    emit updateGL();
  }
  if (m_selectRegion.valid &&
      m_selectRegion.frame0 > m_selectRegion.frame1) {
    int tframe = m_selectRegion.frame0;
    m_selectRegion.frame0 = m_selectRegion.frame1;
    m_selectRegion.frame1 = tframe;
  }
  updateSelectRegion();
  update();
}


void KeyFrameEditor::mousePressEvent(QMouseEvent *event) {

  QPoint clickPos = event->pos();
  const int pressed_but = event->button();
  m_pressedMinFrame = m_minFrame;
  m_draggingCurrFrame = false;
  m_modifiers = event->modifiers();

  if (pressed_but == Qt::RightButton)
    m_selectRegion.valid = false;

  m_selected = -1;
  for(int i=m_fno.count()-1; i>=0; i--)  {
    if (m_fRect[i].contains(clickPos)) {
      m_selected = i;
      m_currFrame = m_fno[m_selected];

      if (m_selectRegion.valid) { // pre shift

        m_ratioBefore.clear();
        m_ratioAfter.clear();

        int startKF = 0;
        int endKF = m_fno.count()-1;
        if ( m_selectRegion.frame1 > m_selectRegion.frame0 )  {
          startKF = m_selectRegion.keyframe0;
          endKF = m_selectRegion.keyframe1;
        }

        if (m_selected >= startKF && m_selected <= endKF) {
          for(int fi=startKF; fi<m_selected; fi++)
            m_ratioBefore.append((m_fno[fi]-m_fno[startKF])/(float)(m_currFrame - m_fno[startKF]));
          for(int fi=m_selected+1; fi<=endKF; fi++)
            m_ratioAfter.append((m_fno[fi]-m_fno[endKF])/(float)(m_currFrame - m_fno[endKF]));
        }

      }

      // pause if currently playing frames
      if (m_playFrames)
        setPlayFrames(false);

      update();
      emit playFrameNumber(m_currFrame);
      return;
    }
  }

  if (pressed_but == Qt::LeftButton && m_modifiers & Qt::ShiftModifier)
    clearRegion();
  else if (clickPos.y() >= m_lineHeight - m_tickHeight - 5 &&
           clickPos.y() <= m_lineHeight + m_tickHeight + 5) {
    m_draggingCurrFrame = true;
    if (m_playFrames)
      setPlayFrames(false);
    moveCurrentFrame(clickPos);
  }

  m_prevX = clickPos.x();

  update();

}


void KeyFrameEditor::setImage(int fno, QImage img) {
  if (fno >= m_fImage.size()) {
    emit showMessage(QString("Cannot setImage : %1 %2").arg(fno).arg(m_fImage.size()), true);
    qApp->processEvents();
    return;
  }
  m_fImage[fno] = img;
  reorder();
  updateSelectRegion();
  update();
}


void KeyFrameEditor::addKeyFrameNumbers(QList<int> fnos) {
  for(int i=0; i<fnos.count(); i++) {
    m_fno.append(fnos[i]);
    m_fRect.append(QRect(-10,-10,1,1));
    QImage img(100,100, QImage::Format_RGB32);
    m_fImage.append(img);
  }
  m_minFrame = qMax(1, m_fno[m_fno.count()-1]-3*m_frameStep);
  calcMaxFrame();
  calcRect();
  update();
}


void KeyFrameEditor::setKeyFrame() {
  if (!m_hiresMode) {
    emit showMessage("Set Keyframe available only in Hires Mode. Press F2 to switch to Hires mode", true);
    qApp->processEvents();
    return;
  }
  m_fno.append(m_currFrame);
  m_fRect.append(QRect(-10,-10,1,1));
  QImage img(100,100, QImage::Format_RGB32);
  m_fImage.append(img);
  m_minFrame = qMax(1, m_fno[m_fno.count()-1]-3*m_frameStep);
  calcMaxFrame();
  calcRect();
  update();
  emit setKeyFrame(m_currFrame);
}


void KeyFrameEditor::removeKeyFrame() {

  if (!m_hiresMode) {
    emit showMessage("Remove Keyframe available only in Hires Mode. Press F2 to switch to Hires mode", true);
    qApp->processEvents();
    return;
  }

  if (m_selectRegion.valid)  {
    for(int i=m_selectRegion.keyframe0; i<=m_selectRegion.keyframe1; i++)  {
      m_fno.removeAt(m_selectRegion.keyframe0);
      m_fRect.removeAt(m_selectRegion.keyframe0);
      m_fImage.removeAt(m_selectRegion.keyframe0);
    }
    emit removeKeyFrames(m_selectRegion.keyframe0, m_selectRegion.keyframe1);
    m_selected = -1;
    m_selectRegion.valid = false;
    update();
    return;
  }

  if (m_selected < 0)  {
    emit showMessage("No keyframe selected for removal", true);
    qApp->processEvents();
    return;
  }

  QList<int>::iterator itfno=m_fno.begin()+m_selected;
  m_fno.erase(itfno);
  QList<QRect>::iterator itfRect=m_fRect.begin()+m_selected;
  m_fRect.erase(itfRect);
  QList<QImage>::iterator itfImage=m_fImage.begin()+m_selected;
  m_fImage.erase(itfImage);

  emit removeKeyFrame(m_selected);
  m_selected = -1;
  update();

}

void KeyFrameEditor::reorder() {

  m_reordered = true;

  tag *fnoTags;
  fnoTags = new tag[m_fno.count()];

  for(int i=0; i<m_fno.count(); i++) {
    fnoTags[i].id = i;
    fnoTags[i].loc = m_fno[i];
  }

  sort(fnoTags, fnoTags+m_fno.count());

  QList<int> dfno(m_fno);
  QList<QRect> dRect(m_fRect);
  QList<QImage> dImg(m_fImage);

  for(int i=0; i<m_fno.count(); i++)  {
    int id = fnoTags[i].id;
    m_fno[i] = dfno[id];
    m_fRect[i] = dRect[id];
    m_fImage[i] = dImg[id];
  }

  if (m_selected >= 0)
    m_selected = fnoTags[m_selected].id;

  QList<int>sortedId;
  for(int i=0; i<m_fno.count(); i++)
    sortedId << fnoTags[i].id;

  emit reorder(sortedId);

  delete [] fnoTags;

}

void KeyFrameEditor::loadKeyframes(QList<int> framenumbers, QList<QImage> images) {
  clear();
  m_fno += framenumbers;
  m_fImage += images;
  for(int i=0; i<framenumbers.size(); i++)
    m_fRect.append(QRect(-10,-10,1,1));
  m_currFrame = 1;
  calcMaxFrame();
  reorder();
  update();
}

void KeyFrameEditor::moveTo(int fno) {
  if (!fno)
    fno = ui->goTo->value();
  if (m_currFrame==fno)
    return;
  m_currFrame = fno;
  if (m_currFrame < m_minFrame)
    m_minFrame = m_currFrame;
  if (m_currFrame > m_maxFrame)
    m_minFrame = qMax(1, m_currFrame-1);
  calcMaxFrame();
  update();
  emit playFrameNumber(m_currFrame);
  qApp->processEvents();
}


void KeyFrameEditor::clearRegion() {
  m_selectRegion.frame0 = frameUnderPoint(clickPos);
  m_selectRegion.frame1 = m_selectRegion.frame0;
  m_selectRegion.valid = true;
}

void KeyFrameEditor::editFrameInterpolation() {
  emit editFrameInterpolation(frameUnderPoint(mapTo(window(), clickPos)));
}




void
KeyFrameEditor::showHelp()
{
  PropertyEditor propertyEditor;
  QMap<QString, QVariantList> plist;
  QVariantList vlist;

  vlist.clear();
  QFile helpFile(":/keyframeeditor.help");
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

  propertyEditor.set("Keyframe Editor Help", plist, keys);
  propertyEditor.exec();
}
