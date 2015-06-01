#include "brickswidget.h"
#include "global.h"
#include "geometryobjects.h"
#include "staticfunctions.h"
#include "propertyeditor.h"

#include <QDebug>

BricksWidget::BricksWidget(QWidget *parent, Bricks *bricks)
  : QWidget(parent)
  , ui(new Ui::BricksWidget)
{
  m_bricks = bricks;
  ui->setupUi(this);
  
  connect(ui->m_brickMinEdit, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_brickMaxEdit, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  //connect(ui->m_brickSizeEdit, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_translation_, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_pivot_, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_axis_, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_angle_, SIGNAL(editingFinished()), SLOT(updateBrickInformation()));
  connect(ui->m_scalepivot_, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  connect(ui->m_scale_, SIGNAL(valueChanged(qglviewer::Vec)), SLOT(updateBrickInformation()));
  
  ui->m_axis_->setRange(Vec(-1,-1,-1), Vec(1,1,1));
  ui->m_scale_->setRange(Vec(0.001,0.001,0.001), Vec(1000,1000,1000));

  ui->m_brickList->addItem("Brick 0");

  m_selected = -1;
  ui->m_brickList->setCurrentRow(m_selected);
  fillInformation(m_selected);
  m_bricks->setSelected(m_selected);

  ui->m_linkBrick->clear();
  ui->m_linkBrick->addItem("Brick 0");

  connect(ui->m_clipTable, SIGNAL(cellClicked(int, int)), SLOT(cellClicked(int, int)));

}

void BricksWidget::setTFSets(int ntfSets) {
  ui->m_tfSet->clear();

  QStringList items;
  for(int i=0; i<ntfSets; i++)
      items << QString("Set %1").arg(i);
  items << "None";

  ui->m_tfSet->addItems(items);
}

void BricksWidget::cellClicked(int row, int col) {
  QTableWidgetItem *wi = ui->m_clipTable->item(row, col);
  BrickInformation binfo = m_bricks->brickInformation(m_selected);

  if (wi->checkState() == Qt::Checked)
    binfo.clippers[col] = true;
  else
    binfo.clippers[col] = false;
  
  m_bricks->setBrick(m_selected, binfo);
  emit updateGL();
}

void BricksWidget::addClipper() {
  m_bricks->addClipper();
  updateClipTable(m_selected);
}

void BricksWidget::removeClipper(int ci) {
  m_bricks->removeClipper(ci);
  updateClipTable(m_selected);
}

void BricksWidget::updateClipTable(int bno) {
  // clear all information from the table
  while(ui->m_clipTable->rowCount() > 0)
    ui->m_clipTable->removeRow(0);

  if (bno < 0)
    return;
  
  BrickInformation binfo = m_bricks->brickInformation(bno);
  QList<bool> clippers = binfo.clippers;
  
  if (clippers.size() <= 0)
    return;
  
  ui->m_clipTable->setColumnCount(clippers.size());
  ui->m_clipTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->m_clipTable->verticalHeader()->hide();
  
  QStringList item;
  for (int i=0; i<clippers.size(); i++)
    item << QString("%1").arg(i);
  ui->m_clipTable->setHorizontalHeaderLabels(item);
  
  for (int i=0; i<clippers.size(); i++)
    ui->m_clipTable->setColumnWidth(i, 25);
  
  ui->m_clipTable->insertRow(0);
  for(int ci=0;ci<clippers.size();ci++) {
    QTableWidgetItem *wi = new QTableWidgetItem("");
    if (clippers[ci])
      wi->setCheckState(Qt::Checked);
    else
      wi->setCheckState(Qt::Unchecked);
    
    wi->setFlags(wi->flags() & ~Qt::ItemIsEditable);
    ui->m_clipTable->setItem(0, ci, wi);
  }
  
  update();
  
}

void BricksWidget::refresh() {
  int nitems = m_bricks->bricks().size();

  ui->m_brickList->clear();
  for(int i=0; i<nitems; i++)
    ui->m_brickList->addItem(QString("Brick %1").arg(i));
  
  ui->m_linkBrick->clear();
  for(int i=0; i<nitems; i++)
    ui->m_linkBrick->addItem(QString("Brick %1").arg(i));
  
  m_selected = qBound(0, m_selected, nitems-1);
  
  m_bricks->setSelected(m_selected);
  ui->m_brickList->setCurrentRow(m_selected);
  fillInformation(m_selected);
}

void BricksWidget::on_m_linkBrick_activated(int index) {
  if (m_selected < 0 || m_selected >= ui->m_brickList->count())
    return;

  if (ui->m_linkBrick->currentIndex() != m_selected)  {
    QList<int> links;
    for(int i=0; i<ui->m_brickList->count(); i++) {
      BrickInformation binfo = m_bricks->brickInformation(i);
      links.append(binfo.linkBrick);
    }
    links[m_selected] = index;

    // check for cycles
    bool done = false;
    int linkBrick = m_selected;
    int plinkBrick;
    while(!done) {
      if (links[linkBrick] == linkBrick || links[linkBrick] == 0)  {
        done = true;
      } else {
        plinkBrick = linkBrick;
        linkBrick = links[linkBrick];

        if (m_selected == linkBrick) {
          emit showMessage(QString("Link to brick %1 would create cycle")
                                   .arg(ui->m_linkBrick->currentIndex())
                           +  QString(" - not allowed\nReverting to brick 0")
                           , true);
          ui->m_linkBrick->setCurrentIndex(0);
          done = true;
        }
      }
    }
  }
  updateBrickInformation();
}

void BricksWidget::on_m_tfSet_activated(int index) {
  if (m_selected < 0 || m_selected >= ui->m_brickList->count())
    return;
  updateBrickInformation();
}

void BricksWidget::on_m_new_pressed() {
  int nitems = ui->m_brickList->count();
  ui->m_brickList->clear();
  ui->m_linkBrick->clear();
  for(int i=0; i<nitems+1; i++) {
    ui->m_brickList->addItem(QString("Brick %1").arg(i));
    ui->m_linkBrick->addItem(QString("Brick %1").arg(i));
  }

  m_bricks->addBrick();

  m_selected = nitems;
  m_bricks->setSelected(m_selected);
  ui->m_brickList->setCurrentRow(m_selected);
  fillInformation(m_selected);

  refresh();
  
  emit showMessage(QString("Added a new brick %1. Hover and move brick faces to change size. ").arg(m_selected),
                   false);
  emit updateGL();
  qApp->processEvents();
  
}

void BricksWidget::on_m_remove_pressed() {
  if (m_selected < 0)  {
    emit showMessage("Select brick for removal", true);
    return;
  }
  if (m_selected == 0)   {
    emit showMessage("Cannot remove toplevel brick 0", true);
    return;
  }

  m_bricks->removeBrick(m_selected);

  int nitems = ui->m_brickList->count();
  ui->m_brickList->clear();
  ui->m_linkBrick->clear();
  for(int i=0; i<nitems-1; i++) {
    ui->m_brickList->addItem(QString("Brick %1").arg(i));
    ui->m_linkBrick->addItem(QString("Brick %1").arg(i));
  }

  int deletedBrick = m_selected;

  m_selected = 0;
  m_bricks->setSelected(m_selected);
  ui->m_brickList->setCurrentRow(m_selected);
  fillInformation(m_selected);

  refresh();

  emit showMessage(QString("Removed brick %1").arg(deletedBrick), false);
  emit updateGL();
  qApp->processEvents();
}

void BricksWidget::on_m_selectAll_pressed() {
  
  if (m_selected < 0 || m_selected >= ui->m_brickList->count())
    return;

  BrickInformation binfo = m_bricks->brickInformation(m_selected);
  
  for(int ci=0;ci<binfo.clippers.size();ci++)  {
    QTableWidgetItem *wi;
    wi = ui->m_clipTable->item(0, ci);
    wi->setCheckState(Qt::Checked);
    binfo.clippers[ci] = true;
  }
  m_bricks->setBrick(m_selected, binfo);
  emit updateGL();
}

void BricksWidget::on_m_deselectAll_pressed() {
  if (m_selected < 0 || m_selected >= ui->m_brickList->count())
    return;
  
  BrickInformation binfo = m_bricks->brickInformation(m_selected);

  for(int ci=0;ci<binfo.clippers.size();ci++) {
    QTableWidgetItem *wi;
    wi = ui->m_clipTable->item(0, ci);
    wi->setCheckState(Qt::Unchecked);
    binfo.clippers[ci] = false;
  }
  m_bricks->setBrick(m_selected, binfo);
  emit updateGL();
}

void BricksWidget::fillInformation(int bno) {
  
  ui->m_brickMaxEdit->setEnabled(bno>0);
  ui->m_brickMinEdit->setEnabled(bno>0);
  //ui->m_brickSizeEdit->setEnabled(bno>0);
  ui->m_linkBrick->setEnabled(bno>0);
  ui->m_tfSet->setEnabled(bno>=0);
  ui->m_translation_->setEnabled(bno>=0);
  ui->m_pivot_->setEnabled(bno>=0);
  ui->m_axis_->setEnabled(bno>=0);
  ui->m_angle_->setEnabled(bno>=0);
  ui->m_clipTable->setEnabled(bno>=0);
  ui->m_scalepivot_->setEnabled(bno>=0);
  ui->m_scale_->setEnabled(bno>=0);
  
  if (bno < 0)
    return;

  BrickInformation binfo = m_bricks->brickInformation(bno);

  Vec dataMin, dataMax, dataSize;
  Global::bounds(dataMin, dataMax);
  dataSize = dataMax - dataMin;
  Vec bmin, bmax, bsz;
  bmin = dataMin + vMv(binfo.brickMin,dataSize);
  bmax = dataMin + vMv(binfo.brickMax,dataSize);
  bsz = bmax-bmin+Vec(1,1,1);
  
  ui->m_brickMinEdit->setRange(dataMin, dataMax);
  ui->m_brickMinEdit->setValue(bmin);
  ui->m_brickMaxEdit->setRange(dataMin, dataMax);
  ui->m_brickMaxEdit->setValue(bmax);
  ui->m_brickSizeEdit->setRange( Vec(1,1,1), dataSize+Vec(1,1,1));
  ui->m_brickSizeEdit->setValue( ui->m_brickMaxEdit->value() - ui->m_brickMinEdit->value() + Vec(1,1,1) );
    
  ui->m_tfSet->setCurrentIndex(binfo.tfSet);
  ui->m_linkBrick->setCurrentIndex(binfo.linkBrick);
  ui->m_translation_->setValue(binfo.position);
  ui->m_pivot_->setValue(binfo.pivot);
  ui->m_axis_->setValue(binfo.axis);
  ui->m_angle_->setValue(binfo.angle);
  ui->m_scalepivot_->setValue(binfo.scalepivot);
  ui->m_scale_->setValue(binfo.scale);
  
  updateClipTable(bno);
  
}

void BricksWidget::on_m_brickList_itemClicked(QListWidgetItem *item) {
  m_selected = ui->m_brickList->row(item);
  m_bricks->setSelected(m_selected);
  fillInformation(m_selected);
  emit updateGL();
}

void BricksWidget::on_m_showAxis_stateChanged(int state) {
  m_bricks->setShowAxis(state == Qt::Checked);
  emit updateGL();
}



void BricksWidget::updateBrickInformation() {
  
  if (m_selected < 0 || m_selected >= ui->m_brickList->count())
    return;
  
  BrickInformation binfo = m_bricks->brickInformation(m_selected);
  binfo.linkBrick = m_selected ? ui->m_linkBrick->currentIndex() : 0;
  
  Vec min = ui->m_brickMinEdit->value();
  Vec max = ui->m_brickMaxEdit->value();
  if ( sender() == ui->m_brickMinEdit ) {
    ui->m_brickMaxEdit->setValue( Vec(qMax(min.x+1,max.x), qMax(min.y+1,max.y), qMax(min.z+1,max.z)) );
    max = ui->m_brickMaxEdit->value();
  } else if ( sender() == ui->m_brickMaxEdit ) {
    ui->m_brickMinEdit->setValue( Vec(qMin(min.x,max.x-1), qMin(min.y,max.y-1), qMin(min.z,max.z-1)) );
    Vec min = ui->m_brickMinEdit->value();
  } /* else if ( sender() == ui->m_brickSizeEdit )
    ui->m_brickMaxEdit->setValue( min + ui->m_brickSizeEdit->value() - Vec(1,1,1) );
  */
  ui->m_brickSizeEdit->setValue( max - min + Vec(1,1,1) );
  
  Vec dataMin, dataMax;
  Global::bounds(dataMin, dataMax);
  const Vec dataSize = dataMax - dataMin;
  binfo.brickMin = vDv( min - dataMin, dataSize ) ;
  binfo.brickMax = vDv( max - dataMin, dataSize ) ;  

  binfo.tfSet = ui->m_tfSet->currentIndex();
  binfo.position = ui->m_translation_->value();
  binfo.pivot = ui->m_pivot_->value();
  binfo.axis = ui->m_axis_->value();
  binfo.angle = ui->m_angle_->value();
  binfo.scalepivot = ui->m_scalepivot_->value();
  binfo.scale = ui->m_scale_->value();

  m_bricks->setBrick(m_selected, binfo);

  emit updateGL();
  
}



bool BricksWidget::getHitpoint(Vec& hitpt) {
  
  QList<Vec> pts = GeometryObjects::hitpoints()->activeCount()
                   ? GeometryObjects::hitpoints()->activePoints()
                   : GeometryObjects::hitpoints()->points();

  if ( ! pts.count() ) {
    emit showMessage("No active hitpoint found. Use shift key and left mouse button to add a point on the volume. Click a point to make it active", true);
    return false;
  }

  Vec dataMin, dataMax, dataSize;
  Global::bounds(dataMin, dataMax);
  dataSize = dataMax-dataMin;
  BrickInformation binfo = m_bricks->brickInformation(m_selected);
  Vec bmin = dataMin + vMv(binfo.brickMin, dataSize);
  Vec bmax = dataMin + vMv(binfo.brickMax, dataSize);
  
  // take the last active hitpoint
  Vec p = pts[pts.count()-1];
  p -= bmin;
  Vec d = bmax-bmin;
  hitpt = vDv(p, d);
  return true;
  
}


void BricksWidget::on_m_pivotFromHitpoint_pressed() {
  Vec p;
  if ( ! getHitpoint(p) )
    return;
  ui->m_pivot_->setValue(p);
  update();
  updateBrickInformation();
}


void BricksWidget::on_m_axisFromHitpoint_pressed() {
  
  Vec p1;
  if ( ! getHitpoint(p1) )
    return;

  Vec p0 = ui->m_pivot_->value();

  //----- get the original coordinates back to find the rotation axis
  Vec dataMin, dataMax, dataSize;
  Global::bounds(dataMin, dataMax);
  BrickInformation binfo = m_bricks->brickInformation(m_selected);
  const Vec d = vMv( binfo.brickMax - binfo.brickMin, dataMax-dataMin );
  
  ui->m_axis_->setValue( vMv(p1-p0,d).unit());

  update();
  updateBrickInformation();
}


void BricksWidget::on_m_scalepivotFromHitpoint_pressed() {
  Vec p;
  if ( ! getHitpoint(p) )
    return;
  ui->m_scalepivot_->setValue(p);
  update();
  updateBrickInformation();
}


void BricksWidget::setBrickZeroRotation(int axisType, float angle) {
  m_selected = 0;
  m_bricks->setSelected(m_selected);
  ui->m_brickList->setCurrentRow(m_selected);
  fillInformation(m_selected);

  const Vec axis(axisType==0, axisType==1, axisType==2);
  ui->m_axis_->setValue(axis);
  ui->m_angle_->setValue(angle);

  BrickInformation binfo = m_bricks->brickInformation(m_selected);
  binfo.axis = axis;
  binfo.angle = angle;
  m_bricks->setBrick(m_selected, binfo);
  emit updateGL();
}


void
BricksWidget::showHelp()
{
  PropertyEditor propertyEditor;
  QMap<QString, QVariantList> plist;
  QVariantList vlist;

  vlist.clear();
  QFile helpFile(":/brick.help");
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

  propertyEditor.set("Bricks Editor Help", plist, keys);
  propertyEditor.exec();
}
