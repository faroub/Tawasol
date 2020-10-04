#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include "LoadConfig.h"

gui::LoadConfig::LoadConfig(QWidget *ap_parent, utils::ConfigData *ap_ConfigData) :
                                    QDialog(ap_parent),
                                    mp_configFileList(new QListWidget(this))
{
    mp_configData = ap_ConfigData;
    QPushButton *lp_okButton = new QPushButton(tr("OK"));
    QPushButton *lp_cancelButton = new QPushButton(tr("Cancel"));
    QHBoxLayout *lp_hLayout = new QHBoxLayout();
    lp_hLayout->addWidget(lp_okButton);
    lp_hLayout->addWidget(lp_cancelButton);
    QGridLayout *lp_mainGridLayout = new QGridLayout();

    lp_mainGridLayout->addWidget(mp_configFileList,0,0,4,2);
    lp_mainGridLayout->addLayout(lp_hLayout,4,1,1,1);

    setLayout(lp_mainGridLayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowTitle(tr("Load Configuration"));

    fillConfigFileList();


}

gui::LoadConfig::~LoadConfig()
{

}


void gui::LoadConfig::open()
{
    qInfo("Open load configuration widget");
    QDialog::open();

}

void gui::LoadConfig::close()
{
    qInfo("Close load configuration widget");
    QDialog::close();

}

void gui::LoadConfig::fillConfigFileList()
{
    //QStringList myStringList = QStringList() << "foo" << "bar" << "baz";
    mp_configFileList->addItem("farid");
    mp_configFileList->addItem("farid");
    mp_configFileList->addItem("farid");

}
