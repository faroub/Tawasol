#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "SaveConfig.h"

gui::SaveConfig::SaveConfig(QWidget *ap_parent, utils::ConfigData *ap_ConfigData) :
                                    QDialog(ap_parent),
                                    mp_configFileName(new QLineEdit(this))

{
    mp_configData = ap_ConfigData;
    QPushButton *lp_okButton = new QPushButton(tr("OK"));
    QPushButton *lp_cancelButton = new QPushButton(tr("Cancel"));
    QLabel *lp_configFileNameLabel = new QLabel(tr("Configuration name:"));
    lp_configFileNameLabel->setAlignment(Qt::AlignRight);


    QHBoxLayout *lp_hLayout = new QHBoxLayout();
    lp_hLayout->addWidget(lp_okButton);
    lp_hLayout->addWidget(lp_cancelButton);
    QGridLayout *lp_mainGridLayout = new QGridLayout();

    lp_mainGridLayout->addWidget(lp_configFileNameLabel,0,0,1,2);
    lp_mainGridLayout->addWidget(mp_configFileName,0,2,1,2);
    lp_mainGridLayout->addLayout(lp_hLayout,1,2,1,2);


    setLayout(lp_mainGridLayout);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(sizeHint().width(),sizeHint().height());
    setWindowTitle(tr("Save Configuration"));

}

gui::SaveConfig::~SaveConfig()
{

}


void gui::SaveConfig::open()
{
    qInfo("Open save configuration widget");
    QDialog::open();

}

void gui::SaveConfig::close()
{
    qInfo("Close save configuration widget");
    QDialog::close();

}
