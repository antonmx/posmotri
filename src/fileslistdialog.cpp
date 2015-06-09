#include "fileslistdialog.h"
FilesListDialog::FilesListDialog(QList<QString> files, QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::FilesListDialog)
{
  ui->setupUi(this);
  ui->listWidget->addItems(files);
}
