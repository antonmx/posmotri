#include "colorbarobject.h"
#include <string.h>

ColorBarObject::ColorBarObject() { clear(); }
ColorBarObject::~ColorBarObject() { clear(); }

void
ColorBarObject::clear()
{
  m_pos = QPointF(0,0);
  m_type = 1;
  m_tfset = 1;
  m_height = 500;
  m_width = 100;
  m_onlyColor = true;
}

void
ColorBarObject::setColorBar(ColorBarObject co)
{
  m_pos = co.position();
  m_type = co.type();
  m_tfset = co.tfset();
  m_height = co.height();
  m_width = co.width();
  m_onlyColor = co.onlyColor();
}

void
ColorBarObject::set(QPointF pos, int type, float tfset,
		    int wd, int ht, bool oc)
{
  m_pos = pos;
  m_type = type;
  m_tfset = tfset;
  m_width = wd;
  m_height = ht;
  m_onlyColor = oc;
}

void ColorBarObject::setOnlyColor(bool oc) { m_onlyColor = oc; }
void ColorBarObject::setWidth(int wd) { m_width = wd; }
void ColorBarObject::setHeight(int ht) { m_height = ht; }
void ColorBarObject::setPosition(QPointF pos) { m_pos = pos; }
void ColorBarObject::setTFset(float tfset) { m_tfset = tfset; }
void ColorBarObject::setType(int type)
{
  if (m_type != type)
    { // flip height and width
      int t = m_height;
      m_height = m_width;
      m_width = t;
    }

  m_type = type;
}

QPointF ColorBarObject::position() { return m_pos; }
int ColorBarObject::height() { return m_height; }
int ColorBarObject::width() { return m_width; }
int ColorBarObject::type() { return m_type; }
float ColorBarObject::tfset() { return m_tfset; }
bool ColorBarObject::onlyColor() { return m_onlyColor; }

void ColorBarObject::scale(int dx, int dy) {
  if (m_width + dx > 10)
    m_width += dx;
  if (m_height + dy > 10)
    m_height += dy;
}

void ColorBarObject::load ( const QConfigMe & cfg ) {
  clear();
  cfg.beginGroup("ColorBarObject");
  cfg.getValue("position", m_pos);
  cfg.getValue("type", m_type);
  cfg.getValue("tfset", m_tfset);
  cfg.getValue("width", m_width);
  cfg.getValue("height", m_height);
  cfg.getValue("onlycolor", m_onlyColor);
  cfg.endGroup();
}

void ColorBarObject::save(QConfigMe & cfg) const {  
  cfg.beginGroup("ColorBarObject");
  cfg.setValue("position", m_pos);
  cfg.setValue("type", m_type);
  cfg.setValue("tfset", m_tfset);
  cfg.setValue("width", m_width);
  cfg.setValue("height", m_height);
  cfg.setValue("onlycolor", m_onlyColor);
  cfg.endGroup();
}

