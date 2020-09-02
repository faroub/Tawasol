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
#include "tawasol_utils.h"
#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE
class QGroupBox;
class QComboBox;
class QGridLayout;
class QLabel;
class QIntValidator;
QT_END_NAMESPACE

namespace gui
{

class Setting : public QDialog
{
    Q_OBJECT

public slots:

    int exec() override;

private slots:

    void showPortInfo(int idx);
    void checkCustomBaudRate(int idx);
    void checkCustomPortPath(int idx);
    void update();
    void refresh();


public:

    struct portParameters {
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

    Setting(QWidget *ap_parent = nullptr);

    ~Setting() override;


    portParameters* getPortParameters();

protected:


private:

    void updatePortParameters();

    void updatePortsInfo();

    void fillPortParameters();

    portParameters *mp_portParameters;

    QComboBox *mp_portComboBox = nullptr;

    QComboBox *mp_operationModeComboBox = nullptr;

    QComboBox *mp_baudRateComboBox = nullptr;

    QComboBox *mp_frameSizeComboBox = nullptr;

    QComboBox *mp_parityModeComboBox = nullptr;

    QComboBox *mp_stopBitsComboBox = nullptr;

    QComboBox *mp_flowControlComboBox = nullptr;

    QLabel *mp_descriptionLabel = nullptr;

    QLabel *mp_manufacturerLabel = nullptr;

    QLabel *mp_serialNumberLabel = nullptr;

    QLabel *mp_locationLabel = nullptr;

    QLabel *mp_vendorIDLabel = nullptr;

    QLabel *mp_productIDLabel = nullptr;

    QPushButton *mp_okButton = nullptr;

    QPushButton *mp_cancelButton = nullptr;

    QPushButton *mp_refreshButton = nullptr;

    QIntValidator *mp_baudRateValidator = nullptr;





};



}




#endif
