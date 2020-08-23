#include <QDebug>
#include "SerialPort.h"
#include "MainWindow.h"
#include "Setting.h"
#include "Console.h"




io::SerialPort::SerialPort(gui::MainWindow *ap_mainWindow, gui::Setting *ap_setting, gui::Console *ap_console)
              : QObject(ap_mainWindow)
{
    mp_mainWindow = ap_mainWindow;
    mp_setting = ap_setting;
    mp_console = ap_console;
    mp_serialPort = new QSerialPort(this);



    connect(mp_serialPort, &QSerialPort::errorOccurred, this, &SerialPort::handleError);

    connect(mp_serialPort, &QSerialPort::readyRead, this, &SerialPort::receiveData);

    connect(mp_console, &gui::Console::sendData, this, &SerialPort::sendData);


}

io::SerialPort::~SerialPort()
{

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

    if (mp_serialPort->open(mp_setting->getPortParameters()->m_operationMode))
    {
        mp_console->setEnabled(true);
        mp_console->setFocus();
        mp_mainWindow->enableConnectionAction(false);
        mp_mainWindow->enableDisconnectionAction(true);
        mp_mainWindow->showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                         .arg(mp_setting->getPortParameters()->m_name).arg(mp_setting->getPortParameters()->m_baudRateString).arg(mp_setting->getPortParameters()->m_frameSizeString)
                                         .arg(mp_setting->getPortParameters()->m_parityModeString).arg(mp_setting->getPortParameters()->m_stopBitsString).arg(mp_setting->getPortParameters()->m_flowControlString));

    }
}


void io::SerialPort::closeSerialPort()
{
    if (isOpen())
    {
        mp_serialPort->close();
    }
    mp_console->setEnabled(false);
    mp_mainWindow->enableConnectionAction(true);
    mp_mainWindow->enableDisconnectionAction(false);
    mp_mainWindow->showStatusMessage(tr("Disconnected ..."));



}

void io::SerialPort::sendData(const QByteArray &data)
{
    mp_serialPort->write(data);

}

void io::SerialPort::receiveData()
{
    const QByteArray data = mp_serialPort->readAll();
    mp_console->writeData(data);
}


void io::SerialPort::handleError(QSerialPort::SerialPortError l_error)
{
    switch (l_error)
    {
        case QSerialPort::NoError :
        {

            break;
        }
        case QSerialPort::DeviceNotFoundError :
        {
            mp_mainWindow->showStatusMessage(tr("Device not found error"));
            break;
        }
        case QSerialPort::PermissionError :
        {
            mp_mainWindow->showErrorMessage(tr("Permission error"),mp_serialPort->errorString());
            break;
        }
        case QSerialPort::OpenError :
        {
            mp_mainWindow->showErrorMessage(tr("Open error"),mp_serialPort->errorString());
            break;
        }
        case QSerialPort::NotOpenError :
        {
            mp_mainWindow->showStatusMessage(tr("Not open error"));
            break;
        }
        case QSerialPort::WriteError :
        {
            mp_mainWindow->showErrorMessage(tr("Write error"),mp_serialPort->errorString());
            break;
        }
        case QSerialPort::ReadError :
        {
            mp_mainWindow->showErrorMessage(tr("Read error"),mp_serialPort->errorString());
            break;
        }
        case QSerialPort::ResourceError :
        {
            mp_mainWindow->showErrorMessage(tr("Resource error"),mp_serialPort->errorString());
            break;
        }
        case QSerialPort::UnsupportedOperationError :
        {
            mp_mainWindow->showStatusMessage(tr("Unsupported operation error"));
            break;
        }
        case QSerialPort::TimeoutError :
        {
            mp_mainWindow->showStatusMessage(tr("Timeout error"));
            break;
        }
        case QSerialPort::UnknownError :
        {
            mp_mainWindow->showStatusMessage(tr("Unknown error"));
            break;
        }
    }

}




bool io::SerialPort::isOpen() const
{
    return mp_serialPort->isOpen();
}


