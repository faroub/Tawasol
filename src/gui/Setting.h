/**
 * @file Setting.h
 * @brief Header file of the Setting class
 *
 * Setting GUI allows to define the communication port settings
 * @author Farid Oubbati (https://github.com/faroub)
 * @date March 2020
*/
#ifndef SETTING_H
#define SETTING_H
#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QComboBox;
class QGridLayout;
class QLabel;
class QIntValidator;
QT_END_NAMESPACE

namespace utils
{
class ConfigData;
}


namespace gui
{

class Setting : public QDialog
{
    Q_OBJECT



public slots:
    void open();

private slots:

    void showPortInfo(int idx);
    void checkCustomBaudRate(int idx);
    void checkCustomPortPath(int idx);
    void update();
    void refresh();
    void close();



public:

    struct portSettings {
        QString m_name;
        QSerialPort::OpenModeFlag m_operationMode;
        QString m_operationModeString;
        qint32 m_baudRate;
        QString m_baudRateString;
        QSerialPort::DataBits m_frameSize;
        QString m_frameSizeString;
        QSerialPort::Parity m_parityMode;
        QString m_parityModeString;
        QSerialPort::StopBits m_stopBits;
        QString m_stopBitsString;
        QSerialPort::FlowControl m_flowControl;
        QString m_flowControlString;
    };

    Setting(QWidget *ap_parent = nullptr, utils::ConfigData *ap_ConfigData = nullptr);

    ~Setting();

    portSettings* getPortSettings();

protected:


private:

    void updatePortParameters();

    void updatePortsInfo();

    void fillPortParameters();

    utils::ConfigData *mp_configData = nullptr;

    portSettings *mp_portSettings;

    QComboBox *mp_portComboBox = nullptr;

    QLabel *mp_descriptionLabel = nullptr;

    QLabel *mp_manufacturerLabel = nullptr;

    QLabel *mp_serialNumberLabel = nullptr;

    QLabel *mp_locationLabel = nullptr;

    QLabel *mp_vendorIDLabel = nullptr;

    QLabel *mp_productIDLabel = nullptr;

    QComboBox *mp_operationModeComboBox = nullptr;

    QComboBox *mp_baudRateComboBox = nullptr;

    QIntValidator *mp_baudRateValidator = nullptr;

    QComboBox *mp_frameSizeComboBox = nullptr;

    QComboBox *mp_parityModeComboBox = nullptr;

    QComboBox *mp_stopBitsComboBox = nullptr;

    QComboBox *mp_flowControlComboBox = nullptr;








};



}




#endif
