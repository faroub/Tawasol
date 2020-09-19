#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDir>
#include <QFileDialog>
#include "Log.h"
#include "LogFile.h"


gui::LogFile::LogFile(QWidget *ap_parent) :
    QDialog(ap_parent)
{

    QPushButton *lp_okButton = new QPushButton(tr("OK"));

    QPushButton *lp_cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *lp_hLayout = new QHBoxLayout();

    lp_hLayout->addWidget(lp_okButton);
    lp_hLayout->addWidget(lp_cancelButton);

    QLabel *lp_logsDirectoryLabel = new QLabel(tr("Logs directory:"));

    mp_logsDirectoryComboBox = new QComboBox();
    mp_logsDirectoryComboBox->setEditable(true);
    mp_logsDirectoryComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mp_logsDirectoryComboBox->addItem(QDir::toNativeSeparators(QDir(utils::Log::getLogsFolderName()).absolutePath()));

    QPushButton *lp_browseButton = new QPushButton(tr("&Browse..."));

    QLabel *lp_logFileNumberLabel = new QLabel(tr("Log files number:"));

    mp_logFileNumberSpinBox = new QSpinBox();
    mp_logFileNumberSpinBox->setRange(0, 100);
    mp_logFileNumberSpinBox->setValue(utils::Log::getLogFileNumber());

    QLabel *lp_logFileSizeLabel = new QLabel(tr("Log file size:"));

    mp_logFileSizeField = new QLineEdit();
    mp_logFileSizeField->setValidator(new QIntValidator(0,10000,mp_logFileSizeField));
    mp_logFileSizeField->setText(QString::number(utils::Log::getLogFileSize()));

    QLabel *lp_logFileSizeUnitLabel = new QLabel(tr("kB"));


    QGroupBox *lp_selectLogDirectoryGroupBox = new QGroupBox();

    QGridLayout *lp_selectLogDirectoryGridLayout = new QGridLayout(lp_selectLogDirectoryGroupBox);

    lp_selectLogDirectoryGridLayout->addWidget(lp_logsDirectoryLabel,0,0,1,1);
    lp_selectLogDirectoryGridLayout->addWidget(mp_logsDirectoryComboBox,0,1,1,8);
    lp_selectLogDirectoryGridLayout->addWidget(lp_browseButton,0,9,1,1);

    lp_selectLogDirectoryGridLayout->addWidget(lp_logFileNumberLabel,1,0,1,1);
    lp_selectLogDirectoryGridLayout->addWidget(mp_logFileNumberSpinBox,1,1,1,2);

    lp_selectLogDirectoryGridLayout->addWidget(lp_logFileSizeLabel,2,0,1,1);
    lp_selectLogDirectoryGridLayout->addWidget(mp_logFileSizeField,2,1,1,2);
    lp_selectLogDirectoryGridLayout->addWidget(lp_logFileSizeUnitLabel,2,3,1,1);

    QGridLayout *lp_logFileGridLayout = new QGridLayout();


    lp_logFileGridLayout->addWidget(lp_selectLogDirectoryGroupBox,0,0,1,12);
    lp_logFileGridLayout->addLayout(lp_hLayout,1,10,1,2);


    connect(lp_browseButton, &QPushButton::clicked, this, &LogFile::browse);
    connect(lp_cancelButton, &QPushButton::clicked, this, &LogFile::close);
    connect(lp_okButton, &QPushButton::clicked, this, &LogFile::update);



    setLayout(lp_logFileGridLayout);

    setWindowTitle(tr("Log Files"));


}


gui::LogFile::~LogFile()
{
    qDebug("Distructor logs directory widget");

}

void gui::LogFile::open()
{
    qInfo("Open logs directory widget");
    QDialog::open();

}

void gui::LogFile::browse()
{
    qInfo("Browse logs directory");
    QString l_logsDirectory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!l_logsDirectory.isEmpty()) {
        if (mp_logsDirectoryComboBox->findText(l_logsDirectory) == -1)
            mp_logsDirectoryComboBox->addItem(l_logsDirectory);
        mp_logsDirectoryComboBox->setCurrentIndex(mp_logsDirectoryComboBox->findText(l_logsDirectory));
    }


}


void gui::LogFile::close()
{
    qInfo("Close logs directory widget");
    QDialog::close();

}

void gui::LogFile::updateLogsDirectory()
{
    utils::Log::setLogsFolderName(mp_logsDirectoryComboBox->currentText());
    qDebug("%s",qUtf8Printable(mp_logsDirectoryComboBox->currentText()));
}

void gui::LogFile::update()
{
    updateLogsDirectory();
    updateLogsParameters();
    utils::Log::init();
    close();

}

void gui::LogFile::updateLogsParameters()
{
    utils::Log::setLogFileSize(mp_logFileSizeField->text().toInt());
    utils::Log::setLogFileNumber(mp_logFileNumberSpinBox->value());


}
