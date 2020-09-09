#ifndef LOGFILE_H
#define LOGFILE_H
#include <QDialog>

namespace gui
{

class LogFile : public QDialog
{
    Q_OBJECT

public slots:
    void open();


public:

    LogFile(QWidget *ap_parent = nullptr);

    ~LogFile();

private:




};


}






#endif // LOGFILE_H
