#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QListWidget>
#include "DeleteConfig.h"

gui::DeleteConfig::DeleteConfig(QWidget *ap_parent, utils::ConfigData *ap_ConfigData) :
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

    QStringList myStringList = QStringList() << "foo" << "bar" << "baz";
    mp_configFileList->addItems(myStringList);
    lp_mainGridLayout->addWidget(mp_configFileList,0,0,4,2);
    lp_mainGridLayout->addLayout(lp_hLayout,4,1,1,1);

    setLayout(lp_mainGridLayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowTitle(tr("Delete Configuration"));

}

gui::DeleteConfig::~DeleteConfig()
{

}

void gui::DeleteConfig::open()
{
    qInfo("Open delete configuration widget");
    QDialog::open();

}

void gui::DeleteConfig::close()
{
    qInfo("Close delete configuration widget");
    QDialog::close();

}

void gui::DeleteConfig::fillConfigFileList()
{
    //QStringList myStringList = QStringList() << "foo" << "bar" << "baz";
    mp_configFileList->addItem("farid");
    mp_configFileList->addItem("farid");
    mp_configFileList->addItem("farid");

}
