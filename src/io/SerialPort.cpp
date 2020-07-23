#include <QDebug>
#include "SerialPort.h"
#include "MainWindow.h"
#include "Setting.h"




io::SerialPort::SerialPort(gui::MainWindow *ap_mainWindow, gui::Setting *ap_setting)
{
    mp_mainWindow = ap_mainWindow;
    mp_setting = ap_setting;
    mp_serialPort = new QSerialPort;

    connect(mp_serialPort, &QSerialPort::errorOccurred, this, &SerialPort::handleError);



}

io::SerialPort::~SerialPort()
{

}


void io::SerialPort::openSerialPort()
{
    mp_mainWindow->enableConnectionAction(false);
    mp_mainWindow->enableDisconnectionAction(true);
    mp_serialPort->setPortName(mp_setting->getPortParameters()->m_name);
    mp_serialPort->setBaudRate(mp_setting->getPortParameters()->m_baudRate);
    mp_serialPort->setDataBits(mp_setting->getPortParameters()->m_frameSize);
    mp_serialPort->setParity(mp_setting->getPortParameters()->m_parityMode);
    mp_serialPort->setStopBits(mp_setting->getPortParameters()->m_stopBits);
    mp_serialPort->setFlowControl(mp_setting->getPortParameters()->m_flowControl);
    if (mp_serialPort->open(mp_setting->getPortParameters()->m_operationMode))
    {
        mp_mainWindow->enableConnectionAction(false);
        mp_mainWindow->enableDisconnectionAction(true);
        mp_mainWindow->showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                         .arg(mp_setting->getPortParameters()->m_name).arg(mp_setting->getPortParameters()->m_baudRateString).arg(mp_setting->getPortParameters()->m_frameSizeString)
                                         .arg(mp_setting->getPortParameters()->m_parityModeString).arg(mp_setting->getPortParameters()->m_stopBitsString).arg(mp_setting->getPortParameters()->m_flowControlString));

    } else {


        mp_mainWindow->showStatusMessage(tr("Open error"));
        mp_mainWindow->showErrorMessage(tr("OpenError"),mp_serialPort->errorString());

    }
}


void io::SerialPort::closeSerialPort()
{
    if (mp_serialPort->isOpen())
    {
        mp_serialPort->close();
    }
    mp_mainWindow->showStatusMessage(tr("Disconnected ..."));
    mp_mainWindow->enableConnectionAction(true);
    mp_mainWindow->enableDisconnectionAction(false);


}

void io::SerialPort::sendFrame(const QByteArray &data)
{

}

void io::SerialPort::readFrame()
{

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
            mp_mainWindow->showStatusMessage(tr("Permission error"));
            break;
        }
        case QSerialPort::OpenError :
        {
            mp_mainWindow->showStatusMessage(tr("Open error"));
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


void io::SerialPort::enableLocalEcho(const bool a_enable)
{
    if (a_enable)
    {
        qDebug()<< "enable local echo";

    } else {
        qDebug()<< "disable local echo";
    }

}



