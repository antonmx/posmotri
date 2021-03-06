#ifndef MYMANIPULATEDFRAME_H
#define MYMANIPULATEDFRAME_H

#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedFrame.h>


class MyManipulatedFrame : public qglviewer::ManipulatedFrame {
  Q_OBJECT
  public :
    MyManipulatedFrame();

    void setThreshold(int);
    int threshold();

    void setOnlyRotate(bool);
    bool onlyRotate();

    void setOnlyTranslate(bool);
    bool onlyTranslate();

    void mousePosition(int&, int&);

    virtual void checkIfGrabsMouse(int, int, const qglviewer::Camera* const);
 protected :
    virtual void mousePressEvent(QMouseEvent* const, qglviewer::Camera* const);
    virtual void mouseMoveEvent(QMouseEvent* const, qglviewer::Camera* const);
    virtual void mouseReleaseEvent(QMouseEvent* const, qglviewer::Camera* const);
  private :
    int m_threshold;
    bool m_keepsGrabbingMouse;
    bool m_onlyRotate;
    bool m_onlyTranslate;
    int m_lastX, m_lastY;
};

#endif
