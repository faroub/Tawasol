#ifndef LOAD_CONFIGURATION_H
#define LOAD_CONFIGURATION_H
#include <QDialog>

QT_BEGIN_NAMESPACE
class QPushButton;
class QListWidget;
QT_END_NAMESPACE

namespace utils
{
class ConfigData;
}

namespace gui
{

class LoadConfig : public QDialog
{
    Q_OBJECT

public slots:

    void open();
    void close();

public:

    LoadConfig(QWidget *ap_parent = nullptr, utils::ConfigData *ap_ConfigData = nullptr);

    ~LoadConfig();

private:

    void fillConfigFileList();

    QListWidget *mp_configFileList = nullptr;

    utils::ConfigData *mp_configData = nullptr;

};

}
#endif // LOADCONFIGURATION_H
