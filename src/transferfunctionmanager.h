#ifndef TRANSFERFUNCTIONMANAGER_H
#define TRANSFERFUNCTIONMANAGER_H

//#include <QtGui>
# include <QGroupBox>
# include <QCheckBox>
# include <QTableWidget>


#include "transferfunctioncontainer.h"

class TransferFunctionManager : public QFrame
{
  Q_OBJECT

 public :
  TransferFunctionManager(QWidget *parent=0);

  void registerContainer(TransferFunctionContainer*);
  
  void save(const QString &) const;
  void load(const QList<SplineInformation> &);
  void append(const QList<SplineInformation> &);
  void load(const QString &);
  void append(const QString &);  
  void loadDefaultTF();

 public slots :
  void clearManager();
  void updateMorph(bool);
  void updateReplace(bool);
  void applyUndo(bool);
  void transferFunctionUpdated();
  void keyPressEvent(QKeyEvent*);

 signals :
  void changeTransferFunctionDisplay(int, QList<bool>);
  void checkStateChanged(int, int, bool);

 protected slots :
  void headerClicked(int);
  void cellClicked(int, int);
  void cellChanged(int, int);
  void addNewTransferFunction();
  void refreshTransferFunction();
  void removeTransferFunction();
  void replaceChanged(int);
  void morphChanged(int);
  bool eventFilter(QObject*, QEvent*);

 private :
  TransferFunctionContainer *m_tfContainer;
  QGroupBox *m_buttonGroup;
  QTableWidget *m_tableWidget;
  QCheckBox *m_replaceTF;
  QCheckBox *m_morphTF;

  void refreshManager(int tfno=0);
  void modifyTableWidget();
  void showHelp();
};

#endif
