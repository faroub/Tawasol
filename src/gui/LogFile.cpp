#include "LogFile.h"


gui::LogFile::LogFile(QWidget *ap_parent) :
    QDialog(ap_parent)
{

}


gui::LogFile::~LogFile()
{
    qDebug("Distructor logfile widget");

}

void gui::LogFile::open()
{
    qInfo("Open logfile widget");
    QDialog::open();

}
