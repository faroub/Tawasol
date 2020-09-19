#ifndef FORMAT_H
#define FORMAT_H
#include <QDialog>


namespace gui
{

class TextFormat : public QDialog
{
    Q_OBJECT


public slots:

    void open();



public:

    TextFormat(QWidget *ap_parent = nullptr);

    ~TextFormat();

};




}



#endif // CONSOLE_FORMAT_H
