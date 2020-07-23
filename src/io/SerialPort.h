/**
 * @file SerialPort.h
 * @brief Header file of the SerialPort class
 *
 * SerialPort class provides functions to access the serial ports
 * @author Farid Oubbati (https://github.com/faroub)
 * @date March 2020
*/
#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


namespace gui
{
class MainWindow;
class Setting;
}
namespace io
{

class SerialPort : public QObject
{
    Q_OBJECT

public slots:

    void openSerialPort();

    void closeSerialPort();

    void enableLocalEcho(const bool a_enable);

private slots:

    void handleError(QSerialPort::SerialPortError l_error);

public:
    SerialPort(gui::MainWindow *ap_mainWindow, gui::Setting *ap_setting);

    ~SerialPort();


    void sendFrame(const QByteArray &data);

    void readFrame();






protected:
private:

    QSerialPort *mp_serialPort = nullptr;


    gui::MainWindow *mp_mainWindow = nullptr;

    gui::Setting *mp_setting = nullptr;


};





}





#endif
