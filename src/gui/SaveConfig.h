#ifndef SAVE_CONFIGURATION_H
#define SAVE_CONFIGURATION_H
#include <QDialog>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE

namespace utils
{
class ConfigData;
}

namespace gui
{

class SaveConfig : public QDialog
{
    Q_OBJECT

public slots:

    void open();
    void close();

public:

    SaveConfig(QWidget *ap_parent = nullptr,
               utils::ConfigData *ap_ConfigData = nullptr);

    ~SaveConfig();

private:

    QLineEdit *mp_configFileName = nullptr;

    utils::ConfigData *mp_configData = nullptr;



};

}
#endif // SAVEC_ONFIGURATION_H
