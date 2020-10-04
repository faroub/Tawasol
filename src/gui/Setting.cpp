#include <QDebug>
#include "Setting.h"
#include "SerialPort.h"
#include "Log.h"
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>





gui::Setting::Setting(QWidget *ap_parent, utils::ConfigData *ap_ConfigData)
             : QDialog(ap_parent),
               mp_configData(ap_ConfigData),
               mp_portSettings(new portSettings()),
               mp_portComboBox(new QComboBox()),
               mp_descriptionLabel(new QLabel()),
               mp_manufacturerLabel(new QLabel()),
               mp_serialNumberLabel(new QLabel()),
               mp_locationLabel(new QLabel()),
               mp_vendorIDLabel(new QLabel()),
               mp_productIDLabel(new QLabel()),
               mp_operationModeComboBox(new QComboBox()),
               mp_baudRateComboBox(new QComboBox()),
               mp_baudRateValidator(new QIntValidator(0, 4000000, mp_baudRateComboBox)),
               mp_frameSizeComboBox(new QComboBox()),
               mp_parityModeComboBox(new QComboBox()),
               mp_stopBitsComboBox(new QComboBox()),
               mp_flowControlComboBox(new QComboBox())
{



    QGridLayout *lp_settingGridLayout = new QGridLayout();

    QGroupBox *lp_selectPortGroupBox = new QGroupBox(tr("Select Port"));
    QGridLayout *lp_selectPortGridLayout = new QGridLayout(lp_selectPortGroupBox);

    QGroupBox *lp_selectPortParametersGroupBox = new QGroupBox(tr("Select Port Parameters"));
    QGridLayout *lp_selectPortParametersGridLayout = new QGridLayout(lp_selectPortParametersGroupBox);

    QPushButton *lp_refreshButton = new QPushButton(tr("Refresh"));

    lp_selectPortGridLayout->addWidget(mp_portComboBox,0,0);
    lp_selectPortGridLayout->addWidget(lp_refreshButton,0,1);

    lp_selectPortGridLayout->addWidget(mp_descriptionLabel,1,0);
    lp_selectPortGridLayout->addWidget(mp_manufacturerLabel,2,0);
    lp_selectPortGridLayout->addWidget(mp_serialNumberLabel,3,0);
    lp_selectPortGridLayout->addWidget(mp_locationLabel,4,0);
    lp_selectPortGridLayout->addWidget(mp_vendorIDLabel,5,0);
    lp_selectPortGridLayout->addWidget(mp_productIDLabel,6,0);



    QLabel *lp_operationModeLabel = new QLabel(tr("Mode:"));
    lp_operationModeLabel->setAlignment(Qt::AlignRight);




    QLabel *lp_baudRateLabel = new QLabel(tr("Baud rate:"));
    lp_baudRateLabel->setAlignment(Qt::AlignRight);



    QLabel *lp_frameSizeLabel = new QLabel(tr("Frame size:"));
    lp_frameSizeLabel->setAlignment(Qt::AlignRight);



    QLabel *lp_parityModeLabel = new QLabel(tr("Parity mode:"));
    lp_parityModeLabel->setAlignment(Qt::AlignRight);



    QLabel *lp_stopBitsLabel = new QLabel(tr("Stop bits:"));
    lp_stopBitsLabel->setAlignment(Qt::AlignRight);


    QLabel *lp_flowControlLabel = new QLabel(tr("Flow control:"));
    lp_flowControlLabel->setAlignment(Qt::AlignRight);


    lp_selectPortParametersGridLayout->addWidget(lp_operationModeLabel,0,0);
    lp_selectPortParametersGridLayout->addWidget(mp_operationModeComboBox,0,1);
    lp_selectPortParametersGridLayout->addWidget(lp_baudRateLabel,1,0);
    lp_selectPortParametersGridLayout->addWidget(mp_baudRateComboBox,1,1);
    lp_selectPortParametersGridLayout->addWidget(lp_frameSizeLabel,2,0);
    lp_selectPortParametersGridLayout->addWidget(mp_frameSizeComboBox,2,1);
    lp_selectPortParametersGridLayout->addWidget(lp_parityModeLabel,3,0);
    lp_selectPortParametersGridLayout->addWidget(mp_parityModeComboBox,3,1);
    lp_selectPortParametersGridLayout->addWidget(lp_stopBitsLabel,4,0);
    lp_selectPortParametersGridLayout->addWidget(mp_stopBitsComboBox,4,1);
    lp_selectPortParametersGridLayout->addWidget(lp_flowControlLabel,5,0);
    lp_selectPortParametersGridLayout->addWidget(mp_flowControlComboBox,5,1);

    QHBoxLayout *lp_hLayout = new QHBoxLayout();
    QPushButton *lp_okButton = new QPushButton(tr("OK"));
    QPushButton *lp_cancelButton = new QPushButton(tr("Cancel"));

    lp_hLayout->addWidget(lp_okButton);
    lp_hLayout->addWidget(lp_cancelButton);

    lp_settingGridLayout->addWidget(lp_selectPortGroupBox,0,0,1,3);
    lp_settingGridLayout->addWidget(lp_selectPortParametersGroupBox,0,3,1,3);
    lp_settingGridLayout->addLayout(lp_hLayout,1,4,1,2);

    mp_baudRateComboBox->setInsertPolicy(QComboBox::NoInsert);


    connect(lp_okButton, SIGNAL(clicked()), this, SLOT(update()));
    connect(lp_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(lp_refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
    connect(mp_portComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Setting::showPortInfo);
    connect(mp_baudRateComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Setting::checkCustomBaudRate);
    connect(mp_portComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Setting::checkCustomPortPath);

    setModal(true);

    setLayout(lp_settingGridLayout);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(sizeHint().width(),sizeHint().height());

    setWindowTitle(tr("Port Settings"));

    fillPortParameters();
    updatePortsInfo();
    updatePortParameters();

}


gui::Setting::~Setting()
{
    qDebug("Distructor setting widget");

}

void gui::Setting::open()
{
    qInfo("Open setting widget");
    updatePortsInfo();
    QDialog::open();
}
void gui::Setting::refresh()
{
    updatePortsInfo();

}

void gui::Setting::update()
{
    updatePortParameters();
    close();

}

void gui::Setting::updatePortParameters()
{
    mp_portSettings->m_name =  mp_portComboBox->currentText();

    mp_portSettings->m_operationMode = static_cast<QSerialPort::OpenModeFlag>(
                mp_operationModeComboBox->itemData(mp_operationModeComboBox->currentIndex()).toInt());
    mp_portSettings->m_operationModeString = mp_operationModeComboBox->currentText();

    if (mp_baudRateComboBox->currentIndex() == 8) {
        mp_portSettings->m_baudRate = mp_baudRateComboBox->currentText().toInt();
    } else
    {
        mp_portSettings->m_baudRate = static_cast<QSerialPort::BaudRate>(
                    mp_baudRateComboBox->itemData(mp_baudRateComboBox->currentIndex()).toInt());
    }
    mp_portSettings->m_baudRateString = QString::number(mp_portSettings->m_baudRate);

    mp_portSettings->m_frameSize = static_cast<QSerialPort::DataBits>(
                mp_frameSizeComboBox->itemData(mp_frameSizeComboBox->currentIndex()).toInt());
    mp_portSettings->m_frameSizeString = mp_frameSizeComboBox->currentText();

    mp_portSettings->m_parityMode = static_cast<QSerialPort::Parity>(
                mp_parityModeComboBox->itemData(mp_parityModeComboBox->currentIndex()).toInt());
    mp_portSettings->m_parityModeString = mp_parityModeComboBox->currentText();

    mp_portSettings->m_stopBits = static_cast<QSerialPort::StopBits>(
                mp_stopBitsComboBox->itemData(mp_stopBitsComboBox->currentIndex()).toInt());
    mp_portSettings->m_stopBitsString = mp_stopBitsComboBox->currentText();

    mp_portSettings->m_flowControl = static_cast<QSerialPort::FlowControl>(
                mp_flowControlComboBox->itemData(mp_flowControlComboBox->currentIndex()).toInt());
    mp_portSettings->m_flowControlString = mp_flowControlComboBox->currentText();


    qInfo("Update port %s: %s, %s, %s, %s, %s",
          qUtf8Printable(mp_portSettings->m_name),
          qUtf8Printable(mp_portSettings->m_baudRateString),
          qUtf8Printable(mp_portSettings->m_frameSizeString),
          qUtf8Printable(mp_portSettings->m_parityModeString),
          qUtf8Printable(mp_portSettings->m_stopBitsString),
          qUtf8Printable(mp_portSettings->m_flowControlString));

}

void gui::Setting::checkCustomPortPath(int a_idx)
{
    mp_portComboBox->setEditable(false);

    if (!mp_portComboBox->itemData(a_idx).isValid())
    {
        mp_portComboBox->setEditable(true);
        mp_portComboBox->clearEditText();
    }
}

void gui::Setting::checkCustomBaudRate(int a_idx)
{
    mp_baudRateComboBox->setEditable(false);

    if (!mp_baudRateComboBox->itemData(a_idx).isValid())
    {
        mp_baudRateComboBox->setEditable(true);
        mp_baudRateComboBox->clearEditText();
        mp_baudRateComboBox->lineEdit()->setValidator(mp_baudRateValidator);
    }

}

void gui::Setting::showPortInfo(int a_idx)
{
    if (a_idx == -1)
    {
        return;
    }

    const QStringList list = mp_portComboBox->itemData(a_idx).toStringList();
    mp_descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr("N/A")));
    mp_manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr("N/A")));
    mp_serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr("N/A")));
    mp_locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr("N/A")));
    mp_vendorIDLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr("N/A")));
    mp_productIDLabel->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr("N/A")));


}
void gui::Setting::updatePortsInfo()
{
    qInfo("Update ports information:");
    mp_portComboBox->clear();
    QList<QSerialPortInfo> l_portsInfoLists = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &l_portInfoList : l_portsInfoLists)
    {
        QStringList l_portList;
        l_portList  << l_portInfoList.portName()
                    << (l_portInfoList.description().isEmpty() ? tr("N/A") : l_portInfoList.description())
                    << (l_portInfoList.manufacturer().isEmpty() ? tr("N/A") : l_portInfoList.manufacturer())
                    << (l_portInfoList.serialNumber().isEmpty() ? tr("N/A") : l_portInfoList.serialNumber())
                    << (l_portInfoList.systemLocation().isEmpty() ? tr("N/A") : l_portInfoList.systemLocation())
                    << (l_portInfoList.vendorIdentifier() ? QString::number(l_portInfoList.vendorIdentifier(), 16) : tr("N/A") )
                    << (l_portInfoList.productIdentifier() ? QString::number(l_portInfoList.productIdentifier(), 16) : tr("N/A"));
             mp_portComboBox->addItem(l_portList.first(), l_portList);
             qInfo("-> Port %s: %s, %s, %s, %s, %s, %s ",
                   qUtf8Printable(l_portList.at(0)),
                   qUtf8Printable(l_portList.at(1)),
                   qUtf8Printable(l_portList.at(2)),
                   qUtf8Printable(l_portList.at(3)),
                   qUtf8Printable(l_portList.at(4)),
                   qUtf8Printable(l_portList.at(5)),
                   qUtf8Printable(l_portList.at(6)));

    }

    mp_portComboBox->addItem(tr("Custom"));




}

void gui::Setting::fillPortParameters()
{
    mp_operationModeComboBox->addItem(tr("ReadWrite"),QSerialPort::ReadWrite);
    mp_operationModeComboBox->addItem(tr("ReadOnly"),QSerialPort::ReadOnly);
    mp_operationModeComboBox->addItem(tr("WriteOnly"),QSerialPort::WriteOnly);
    mp_operationModeComboBox->setCurrentIndex(0);
    //mp_operationModeComboBox->setCurrentText("ReadWrite");


    mp_baudRateComboBox->addItem("1200",QSerialPort::Baud1200);
    mp_baudRateComboBox->addItem("2400",QSerialPort::Baud2400);
    mp_baudRateComboBox->addItem("4800",QSerialPort::Baud4800);
    mp_baudRateComboBox->addItem("9600",QSerialPort::Baud9600);
    mp_baudRateComboBox->addItem("19200",QSerialPort::Baud19200);
    mp_baudRateComboBox->addItem("38400",QSerialPort::Baud38400);
    mp_baudRateComboBox->addItem("57600",QSerialPort::Baud57600);
    mp_baudRateComboBox->addItem("115200",QSerialPort::Baud115200);
    mp_baudRateComboBox->addItem(tr("Custom"));
    mp_baudRateComboBox->setCurrentIndex(3);

    mp_frameSizeComboBox->addItem("5",QSerialPort::Data5);
    mp_frameSizeComboBox->addItem("6",QSerialPort::Data6);
    mp_frameSizeComboBox->addItem("7",QSerialPort::Data7);
    mp_frameSizeComboBox->addItem("8",QSerialPort::Data8);
    mp_frameSizeComboBox->setCurrentIndex(3);

    mp_parityModeComboBox->addItem(tr("None"),QSerialPort::NoParity);
    mp_parityModeComboBox->addItem(tr("Even"),QSerialPort::EvenParity);
    mp_parityModeComboBox->addItem(tr("Odd"),QSerialPort::OddParity);
    mp_parityModeComboBox->addItem(tr("Mark"),QSerialPort::MarkParity);
    mp_parityModeComboBox->addItem(tr("Space"),QSerialPort::SpaceParity);
    mp_parityModeComboBox->setCurrentIndex(0);

    mp_stopBitsComboBox->addItem("1",QSerialPort::OneStop);
#ifdef Q_OS_WIN
    mp_stopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    mp_stopBitsComboBox->addItem("2",QSerialPort::TwoStop);
    mp_stopBitsComboBox->setCurrentIndex(0);


    mp_flowControlComboBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    mp_flowControlComboBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    mp_flowControlComboBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
    mp_flowControlComboBox->setCurrentIndex(0);



}

gui::Setting::portSettings *gui::Setting::getPortSettings()
{
    return mp_portSettings;
}

void gui::Setting::close()
{
    qInfo("Close setting widget");
    QDialog::close();

}
