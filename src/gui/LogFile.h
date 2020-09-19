#ifndef LOGFILE_H
#define LOGFILE_H
#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDir;
class QLineEdit;
class QSpinBox;
QT_END_NAMESPACE

namespace gui
{

class LogFile : public QDialog
{
    Q_OBJECT

public slots:

    void open();

private slots:

    void browse();
    void close();
    void update();

public:

    LogFile(QWidget *ap_parent = nullptr);

    ~LogFile();

private:

    void updateLogsDirectory();
    void updateLogsParameters();

    QComboBox *mp_logsDirectoryComboBox = nullptr;
    QLineEdit *mp_logFileSizeField = nullptr;
    QSpinBox *mp_logFileNumberSpinBox = nullptr;
    QDir *mp_currentDir = nullptr;


};


}






#endif // LOGFILE_H
