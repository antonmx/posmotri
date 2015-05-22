#include "global.h"
#include "gilightgrabber.h"
#include "staticfunctions.h"
//#include <QtGui>
#include <QGLViewer/manipulatedCameraFrame.h>


GiLightGrabber::GiLightGrabber()
{
  m_lastX = m_lastY = -1;
  m_pressed = false;
  m_pointPressed = -1;
  m_moveAxis = MoveAll;
  m_moved = false;
}

GiLightGrabber::~GiLightGrabber() { removeFromMouseGrabberPool(); }

int GiLightGrabber::moveAxis() { return m_moveAxis; }
void GiLightGrabber::setMoveAxis(int type) { m_moveAxis = type; }

int GiLightGrabber::pointPressed() { return m_pointPressed; }

void
GiLightGrabber::mousePosition(int& x, int& y)
{
  x = m_lastX;
  y = m_lastY;
}

void
GiLightGrabber::checkIfGrabsMouse(int x, int y,
			       const Camera* const camera)
{
  if (m_pressed)
    {
      // mouse button pressed so keep grabbing
      setGrabsMouse(true);
      return;
    }

  int sz = 20;

  QList<Vec> pts = pathPoints();

  m_lastX = x;
  m_lastY = y;
  Vec v = Vec(x, y, 0);
  Vec pos0 = camera->projectedCoordinatesOf(pts[0]);
  Vec p0 = Vec(pos0.x, pos0.y, 0);
  if (pts.count() == 1)
    {
      if ((p0-v).norm() < sz)
	{
	  setGrabsMouse(true);
	  return;
	}
    }
  else
    {
      for(int i=1; i<pts.count(); i++)
	{
	  Vec pos1 = camera->projectedCoordinatesOf(pts[i]);
	  Vec p1 = Vec(pos1.x, pos1.y, 0);
	  Vec pvec = p1-p0;
	  Vec pv = v-p0;
	  pv.projectOnAxis(pvec);

	  float pvdotpvec = pv*pvec.unit();
	  if (pvdotpvec >= -sz && pvdotpvec <= pvec.norm()+sz)
	    {
	      pv += p0;
	      if ((pv-v).norm() < sz)
		{
		  setGrabsMouse(true);
		  return;
		}
	    }
	  pos0 = pos1;
	  p0 = p1;
	}
    }
  setGrabsMouse(false);
}

void
GiLightGrabber::mousePressEvent(QMouseEvent* const event,
				 Camera* const camera)
{
  m_pointPressed = -1;
  m_pressed = true;
  m_moved = false;
  m_prevPos = event->pos();

  if (event->button() == Qt::MidButton)
    {
      setPointPressed(m_pointPressed);
      return;
    }

  Vec voxelScaling = Global::voxelScaling();
  int nseg = segments();
  QList<Vec> pts = points();
  for(int i=0; i<pts.count(); i++)
    {
      Vec v = VECPRODUCT(pts[i], voxelScaling);
      Vec pos = camera->projectedCoordinatesOf(v);
      QPoint hp(pos.x, pos.y);
      if ((hp-m_prevPos).manhattanLength() < 20)
	{
	  m_pointPressed = i;
	  break;
	}
    }

  int pt0 = -1;
  if (m_pointPressed == -1)
    {
      QList<Vec> pts = pathPoints();
      for(int i=1; i<pts.count(); i++)
	{
	  Vec pos0 = camera->projectedCoordinatesOf(pts[i-1]);
	  Vec pos1 = camera->projectedCoordinatesOf(pts[i]);
	  int p0x = pos0.x;
	  int p0y = pos0.y;
	  int p1x = pos1.x;
	  int p1y = pos1.y;
	  int pvx = p1x-p0x;
	  int pvy = p1y-p0y;
	  int pmx = m_prevPos.x()-p0x;
	  int pmy = m_prevPos.y()-p0y;
	  int t = pvx*pmx + pvy*pmy;
	  int pd =  pvx*pvx+pvy*pvy;
	  int sqd = (pmx*pmx + pmy*pmy) - (float)(t*t)/pd;
	  if (sqd < 10)
	    {
	      pt0 = i;
	      break;
	    }
	}
      if (pt0 > -1)
	{
	  if (pts.count() > 2 && nseg > 1)
	    {
	      pt0 /= nseg;
	      pt0 += 1;
	    }
	  pt0 = points().count()-1-pt0;

	  m_pointPressed = pt0;
	  setPointPressed(pt0);
	}
    }
  else
    setPointPressed(m_pointPressed);

  emit selectForEditing(event->button(), pt0);
}

void
GiLightGrabber::mouseMoveEvent(QMouseEvent* const event,
			       Camera* const camera)
{
  if (!m_pressed && getPointPressed() == -1)
    return;

  QPoint delta = event->pos() - m_prevPos;
  Vec trans(delta.x(), -delta.y(), 0.0f);

  // Scale to fit the screen mouse displacement
  trans *= 2.0 * tan(camera->fieldOfView()/2.0) *
           fabs((camera->frame()->coordinatesOf(Vec(0,0,0))).z) /
           camera->screenHeight();
  // Transform to world coordinate system.
  trans = camera->frame()->orientation().rotate(trans);

  if (m_moveAxis == MoveX)
    trans = Vec(trans.x,0,0);
  else if (m_moveAxis == MoveY)
    trans = Vec(0,trans.y,0);
  else if (m_moveAxis == MoveZ)
    trans = Vec(0,0,trans.z);

  Vec voxelScaling = Global::voxelScaling();
  trans = VECDIVIDE(trans, voxelScaling);


  m_pointPressed = getPointPressed();
  if (m_pointPressed > -1)
    {
      Vec pt = getPoint(m_pointPressed);
      if (m_moveAxis == MoveX)
	pt += trans.x*saxis()[m_pointPressed];
      else if (m_moveAxis == MoveY)
	pt += trans.y*taxis()[m_pointPressed];
      else if (m_moveAxis == MoveZ)
	pt += trans.z*(tangents()[m_pointPressed]).unit();
      else
	pt += trans;

      setPoint(m_pointPressed, pt);
    }
  else
    setPoint(m_pointPressed, trans);

  m_moved = true;

  m_prevPos = event->pos();
}

void
GiLightGrabber::mouseReleaseEvent(QMouseEvent* const event,
				  Camera* const camera)
{
  if (m_moved)
    updateUndo();

  m_moved = false;
  m_pressed = false;
  m_pointPressed = -1;
  setPointPressed(m_pointPressed);
  setGrabsMouse(false);

  emit deselectForEditing();
}
