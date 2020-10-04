#ifndef DELETE_CONFIGURATION_H
#define DELETE_CONFIGURATION_H
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

class DeleteConfig : public QDialog
{
    Q_OBJECT

public slots:

    void open();
    void close();

public:

    DeleteConfig(QWidget *ap_parent = nullptr, utils::ConfigData *ap_ConfigData = nullptr);

    ~DeleteConfig();

private:

    void fillConfigFileList();

    QListWidget *mp_configFileList = nullptr;

    utils::ConfigData *mp_configData = nullptr;

};

}
#endif // DELETE_CONFIGURATION_H
