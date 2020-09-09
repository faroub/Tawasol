#include <QDebug>
#include "SerialPort.h"
#include "MainWindow.h"
#include "Setting.h"
#include "Console.h"




io::SerialPort::SerialPort(gui::MainWindow *ap_mainWindow, gui::Setting *ap_setting, gui::Console *ap_console)
              : QObject(ap_mainWindow)
{


    mp_mainWindow = ap_mainWindow;
    Q_CHECK_PTR(mp_mainWindow);
    mp_setting = ap_setting;
    Q_CHECK_PTR(mp_setting);
    mp_console = ap_console;
    Q_CHECK_PTR(mp_console);
    mp_serialPort = new QSerialPort(this);



    connect(mp_serialPort, &QSerialPort::errorOccurred, this, &SerialPort::handleError);

    connect(mp_serialPort, &QSerialPort::readyRead, this, &SerialPort::receiveData);

    connect(mp_console, &gui::Console::sendData, this, &SerialPort::sendData);


}

io::SerialPort::~SerialPort()
{
    qDebug("Distructor serialport object");

}

void io::SerialPort::setSerialPortParameters()
{
    mp_serialPort->setPortName(mp_setting->getPortParameters()->m_name);
    mp_serialPort->setBaudRate(mp_setting->getPortParameters()->m_baudRate);
    mp_serialPort->setDataBits(mp_setting->getPortParameters()->m_frameSize);
    mp_serialPort->setParity(mp_setting->getPortParameters()->m_parityMode);
    mp_serialPort->setStopBits(mp_setting->getPortParameters()->m_stopBits);
    mp_serialPort->setFlowControl(mp_setting->getPortParameters()->m_flowControl);

}
void io::SerialPort::openSerialPort()
{

    setSerialPortParameters();

    qInfo("Open connection to %s: %s, %s, %s, %s, %s, %s",
          qUtf8Printable(mp_setting->getPortParameters()->m_name),
          qUtf8Printable(mp_setting->getPortParameters()->m_operationModeString),
          qUtf8Printable(mp_setting->getPortParameters()->m_baudRateString),
          qUtf8Printable(mp_setting->getPortParameters()->m_frameSizeString),
          qUtf8Printable(mp_setting->getPortParameters()->m_parityModeString),
          qUtf8Printable(mp_setting->getPortParameters()->m_stopBitsString),
          qUtf8Printable(mp_setting->getPortParameters()->m_flowControlString));

    if (mp_serialPort->open(mp_setting->getPortParameters()->m_operationMode))
    {

        mp_console->setEnabled(true);
        mp_console->setFocus();
        mp_mainWindow->enableConnectionAction(false);
        mp_mainWindow->enableDisconnectionAction(true);
        mp_mainWindow->showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                         .arg(mp_setting->getPortParameters()->m_name).arg(mp_setting->getPortParameters()->m_baudRateString).arg(mp_setting->getPortParameters()->m_frameSizeString)
                                         .arg(mp_setting->getPortParameters()->m_parityModeString).arg(mp_setting->getPortParameters()->m_stopBitsString).arg(mp_setting->getPortParameters()->m_flowControlString));

        qInfo("Connected to %s: %s, %s, %s, %s, %s",
              qUtf8Printable(mp_setting->getPortParameters()->m_name),
              qUtf8Printable(mp_setting->getPortParameters()->m_baudRateString),
              qUtf8Printable(mp_setting->getPortParameters()->m_frameSizeString),
              qUtf8Printable(mp_setting->getPortParameters()->m_parityModeString),
              qUtf8Printable(mp_setting->getPortParameters()->m_stopBitsString),
              qUtf8Printable(mp_setting->getPortParameters()->m_flowControlString));
    }
}


void io::SerialPort::closeSerialPort()
{

    if (isOpen())
    {
        mp_serialPort->close();
        mp_console->setEnabled(false);
        mp_mainWindow->enableConnectionAction(true);
        mp_mainWindow->enableDisconnectionAction(false);
        mp_mainWindow->showStatusMessage(tr("Disconnected ..."));
        qInfo("Close connection to %s", qUtf8Printable(mp_setting->getPortParameters()->m_name));

    }





}

void io::SerialPort::sendData(const QByteArray &ar_data)
{
    mp_serialPort->write(ar_data);


}

void io::SerialPort::receiveData()
{
    const QByteArray l_data = mp_serialPort->readAll();
    mp_console->writeData(l_data);
}


void io::SerialPort::handleError(QSerialPort::SerialPortError l_error)
{
    switch (l_error)
    {
        case QSerialPort::NoError :
        {
            qInfo("No error: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::DeviceNotFoundError :
        {
            mp_mainWindow->showErrorMessage(tr("Error: Device not found"), mp_serialPort->errorString());
            qCritical("Error: Device not found: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::PermissionError :
        {
            mp_mainWindow->showErrorMessage(tr("Error: Access permission"),mp_serialPort->errorString());
            qCritical("Error: Access permission: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::OpenError :
        {
            mp_mainWindow->showErrorMessage(tr("Error: Open device"),mp_serialPort->errorString());
            qCritical("Error: Open device: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::NotOpenError :
        {
            mp_mainWindow->showErrorMessage(tr("Error: Not open device"),mp_serialPort->errorString());
            qCritical("Error: Not open device: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::WriteError :
        {
            mp_mainWindow->showStatusMessage(tr("Error: Write data"));
            qCritical("Error: Write data: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::ReadError :
        {
            mp_mainWindow->showStatusMessage(tr("Error: Read data"));
            qCritical("Error: Read data: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::ResourceError :
        {
            mp_mainWindow->showErrorMessage(tr("Error: Resource unavailable"),mp_serialPort->errorString());
            qCritical("Error: Resource unavailable: %s", qUtf8Printable(mp_serialPort->errorString()));
            closeSerialPort();
            break;
        }
        case QSerialPort::UnsupportedOperationError :
        {
            mp_mainWindow->showStatusMessage(tr("Error: Unsupported operation"));
            qCritical("Error: Unsupported operation: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::TimeoutError :
        {
            mp_mainWindow->showStatusMessage(tr("Error: Timeout occurred"));
            qCritical("Error: Timeout occurred: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::UnknownError :
        {
            mp_mainWindow->showStatusMessage(tr("Error: Unidentified"));
            qCritical("Error: Unidentified: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::FramingError :
        {
            qCritical("Error: Data framing <obsolete>: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::BreakConditionError :
        {
            qCritical("Error: Break condition <obsolete>: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
        case QSerialPort::ParityError :
        {
            qCritical("Error: Data parity <obsolete>: %s", qUtf8Printable(mp_serialPort->errorString()));
            break;
        }
    }

}




bool io::SerialPort::isOpen() const
{
    return mp_serialPort->isOpen();
}


