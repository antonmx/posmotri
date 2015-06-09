#ifndef FILESLISTDIALOG_H
#define FILESLISTDIALOG_H

#include "ui_fileslistdialog.h"

class FilesListDialog : public QDialog {
  Q_OBJECT;  
private:
  Ui::FilesListDialog * ui;
public :
  FilesListDialog(QList<QString> files, QWidget *parent = 0);
};


#endif
