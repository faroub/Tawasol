#include <QPushButton>
#include "TextFormat.h"



gui::TextFormat::TextFormat(QWidget *ap_parent) :
    QDialog(ap_parent)
{


}


gui::TextFormat::~TextFormat()
{
    qDebug("Distructor text format widget");

}

void gui::TextFormat::open()
{
    qInfo("Open text format widget");
    QDialog::open();

}


