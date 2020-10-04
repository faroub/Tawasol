#ifndef CONFIGFILE_H
#define CONFIGFILE_H
#include <QtGlobal>
#include <QFile>
#include <QString>




namespace utils
{


class ConfigData
{

public:

        struct portSetting {
            QString m_name;
            QString m_operationMode;
            qint32 m_baudRate;
            quint8 m_frameSize;
            QString m_parityMode;
            quint8 m_stopBits;
            QString m_flowControl;
        };
        struct consoleSetting {
            quint8 m_fontSize;
            QString m_fontFamily;
            QString m_fontColor;
            QString m_backgroundColor;
        };

    struct XMLData {
        portSetting m_portSetting;
        consoleSetting m_vconsoleSetting;
    };

    ConfigData();

    ~ConfigData();



    void saveConfigFile(const QString &ar_configFileName);

    void deleteConfigFile(const QString &ar_configFileName);

    void loadConfigFile(const QString &ar_configFileName);

    XMLData* getXMLData();


private:

    XMLData *mp_XMLData;

    void openConfigFile(const QString &ar_configFileName);

    void closeConfigFile(const QString &ar_configFileName);

    void readConfigFile(const QString &ar_configFileName);

    void writeConfigFile(const QString &ar_configFileName);

    QFile m_configFile;

    QString m_configFileName;



};

}
#endif // CONFIGFILE_H
