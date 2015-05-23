
#include "directionvectorwidget.h"
#include "staticfunctions.h"

#include <QtGui>
#include <QMenu>


using namespace qglviewer;


LightDisc::LightDisc(QWidget *parent)
  : QWidget(parent)
  , m_backlit(false)
  , m_direction(0, 0)
{
  setContextMenuPolicy(Qt::CustomContextMenu);
}

void LightDisc::setDirection(const QPointF & dir) {
  m_direction = dir;
  update();
  emit directionChanged(m_direction);
}

void LightDisc::setBacklit(bool flag) { 
  m_backlit = flag;
  update();
}

void LightDisc::paintEvent(QPaintEvent *event) {
  
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  
  float m_size = qMin( width(), height() );  
  QRectF drawRect( rect().topLeft(), QSizeF(m_size,m_size) ) ;
  
  QRadialGradient radialGradient( drawRect.center(), m_size,
    drawRect.center() + m_size * QPointF( m_direction.x(), -m_direction.y() ) /2 );  
  radialGradient.setColorAt(0.0, m_backlit ? Qt::black : Qt::white );
  radialGradient.setColorAt(0.5, Qt::gray);
  radialGradient.setColorAt(1.0, m_backlit ? Qt::white : Qt::black );
  p.setBrush(QBrush(radialGradient));
  p.setPen(Qt::darkGray);
  p.drawEllipse(drawRect);

  p.setBrush(Qt::transparent);
  p.drawEllipse( drawRect.center(), m_size*cos(M_PI/8)/2, m_size*cos(M_PI/8)/2);
  p.drawEllipse( drawRect.center(), m_size*cos(M_PI/4)/2, m_size*cos(M_PI/4)/2);
  p.drawEllipse( drawRect.center(), m_size*cos(3*M_PI/8)/2, m_size*cos(3*M_PI/8)/2);
  
  p.drawLine(0, m_size/2, m_size, m_size/2);
  p.drawLine(m_size/2, 0, m_size/2, m_size);
  
}

void LightDisc::onMouseSet(const QPointF & pos) {
    const float m_size = qMin( width(), height() );  
    const QPointF ecor = pos - QPointF(m_size/2, m_size/2);
    const float len = sqrt(ecor.x()*ecor.x() + ecor.y()*ecor.y());
    if (len > m_size/2)
      return;
    setDirection(QPointF( 2*ecor.x()/m_size, -2*ecor.y()/m_size)) ; 
}

void LightDisc::mousePressEvent(QMouseEvent *event) {
  if(event->button() == Qt::RightButton ) {
    QMenu myMenu;
    myMenu.addAction("Center");
    if (myMenu.exec(mapToGlobal(event->pos())))
      setDirection(QPointF(0, 0));
  } else {
    onMouseSet(event->pos());
  }
}

void LightDisc::mouseMoveEvent(QMouseEvent *event) {
  onMouseSet(event->pos());
}




DirectionVectorWidget::DirectionVectorWidget(QWidget *parent)
 : QWidget(parent)
{	
  ui.setupUi(this);  
  connect(ui.lightDisc, SIGNAL(directionChanged(QPointF)), SLOT(updateDirection(QPointF)));
  connect(ui.zangle, SIGNAL(valueChanged(double)), SLOT(onDirectionChange()));
  connect(ui.yangle, SIGNAL(valueChanged(double)), SLOT(onDirectionChange()));
  connect(ui.len, SIGNAL(valueChanged(double)), SLOT(onLenChange()));
}

void DirectionVectorWidget::setVector(Vec vo) {
  ui.len->setValue(vo.normalize());
  ui.zangle->setValue( RAD2DEG(acos(vo.z)) );
  if (vo.y != 0.0  ||  vo.x != 0.0 )
    ui.yangle->setValue( RAD2DEG(acos(vo.y/sqrt(vo.y*vo.y+vo.x*vo.x))) );  
}

Vec DirectionVectorWidget::vector() {
  const float cosz = cos( DEG2RAD(ui.zangle->value()) );
  const float cosy = cos( DEG2RAD(ui.yangle->value()) );  
  const float z = cosz;
  const float y = cosy*sqrt(1-cosz*cosz);  
  const float x = copysign( sqrt( (1-cosz*cosz)*(1-cosy*cosy) ), ui.yangle->value() );
  return  ui.len->value() * Vec(x,y,z);
}


void DirectionVectorWidget::updateDirection(QPointF pt) {  
  float psq = pt.y()*pt.y() + pt.x()*pt.x();
  float zangle = RAD2DEG(acos( sqrt(1-psq) ));
  if (ui.zangle->value() > 90)
    zangle = 180-zangle;
  ui.zangle->setValue(zangle);
  if ( psq > 0.0 )
    ui.yangle->setValue( copysign( RAD2DEG(acos( pt.y() / sqrt(psq) )), pt.x() ) );
  emit directionChanged(vector());
}


void DirectionVectorWidget::onDirectionChange() {
  Vec vn=vector().unit();
  ui.lightDisc->setDirection( QPointF(vn.x, vn.y) );
  ui.lightDisc->setBacklit(vn.z < 0);
  emit directionChanged(vector());
}


void DirectionVectorWidget::onLenChange() {
  emit directionChanged(vector());
}


