#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFontComboBox>
#include <QSpinBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QApplication>
#include "TextFormat.h"
#include "Console.h"



gui::TextFormat::TextFormat(QWidget *ap_parent, gui::Console *ap_console) :
    QDialog(ap_parent)
{
    mp_console = ap_console;
    Q_CHECK_PTR(mp_console);

    QPushButton *lp_closeButton = new QPushButton(tr("Close"));



    QLabel *lp_fontLabel = new QLabel(tr("Font:"));

    lp_fontLabel->setAlignment(Qt::AlignRight);

    mp_fontButton = new QPushButton();
    QFont l_font = mp_console->font();
    mp_fontButton->setText(l_font.family()+" | "+QString::number(l_font.pointSize()));




    QLabel *lp_fontColorLabel = new QLabel(tr("Font color:"));

    lp_fontColorLabel->setAlignment(Qt::AlignRight);

    mp_fontColorButton = new QPushButton();
    QPalette l_pal= mp_console->palette();
    l_pal.setColor(QPalette::Button,l_pal.color(QPalette::Text));
    mp_fontColorButton->setPalette(l_pal);


    QLabel *lp_backgroundColorLabel = new QLabel(tr("Background color:"));

    lp_backgroundColorLabel->setAlignment(Qt::AlignRight);

    mp_backgroundColorButton = new QPushButton();
    l_pal= mp_console->palette();
    l_pal.setColor(QPalette::Button,l_pal.color(QPalette::Base));
    mp_backgroundColorButton->setPalette(l_pal);


    QGroupBox *lp_textFormatGroupBox = new QGroupBox();

    QGridLayout *lp_textFormatGridLayout = new QGridLayout(lp_textFormatGroupBox);

    lp_textFormatGridLayout->addWidget(lp_fontLabel,0,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_fontButton,0,1,1,4);



    lp_textFormatGridLayout->addWidget(lp_fontColorLabel,2,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_fontColorButton,2,1,1,1);

    lp_textFormatGridLayout->addWidget(lp_backgroundColorLabel,3,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_backgroundColorButton,3,1,1,1);


    QGridLayout *lp_mainGridLayout = new QGridLayout();


    lp_mainGridLayout->addWidget(lp_textFormatGroupBox,0,0,1,3);
    lp_mainGridLayout->addWidget(lp_closeButton,1,2,1,1);


    connect(lp_closeButton, &QPushButton::clicked, this, &TextFormat::close);

    connect(mp_fontButton, &QPushButton::clicked, this, &TextFormat::setFont);

    connect(mp_fontColorButton, &QPushButton::clicked, this, &TextFormat::setFontColor);

    connect(mp_backgroundColorButton, &QPushButton::clicked, this, &TextFormat::setBackgroundColor);


    setLayout(lp_mainGridLayout);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(sizeHint().width(),sizeHint().height());


    setWindowTitle(tr("Text Format"));
}


gui::TextFormat::~TextFormat()
{
    qDebug("Distructor text format widget");

}

void gui::TextFormat::open()
{
    qInfo("Open text format widget");
    QDialog::open();

}

void gui::TextFormat::close()
{
    qInfo("Close logs directory widget");
    QDialog::close();

}

void gui::TextFormat::update()
{
    close();

}

void gui::TextFormat::setFontColor()
{
    const QColor l_color = QColorDialog::getColor(Qt::green, this, "Select Color");
    QPalette l_pal;
    if (l_color.isValid()) {

        QPalette l_pal= mp_fontColorButton->palette();
        l_pal.setColor(QPalette::Button,l_color);
        mp_fontColorButton->setPalette(l_pal);
        l_pal= mp_console->palette();
        l_pal.setColor(QPalette::Text, l_color);
        mp_console->setPalette(l_pal);
        
    }
}

void gui::TextFormat::setFont()
{
    bool l_ok;
    QFont l_font = QFontDialog::getFont(&l_ok, this);

    if (l_ok) {
        mp_fontButton->setText(l_font.family()+" | "+QString::number(l_font.pointSize()));
        mp_console->setFont(l_font);
    }
}

void gui::TextFormat::setBackgroundColor()
{
    const QColor l_color = QColorDialog::getColor(Qt::green, this, "Select Color");
    QPalette l_pal;

    if (l_color.isValid()) {

        l_pal= mp_backgroundColorButton->palette();
        l_pal.setColor(QPalette::Button,l_color);
        mp_backgroundColorButton->setPalette(l_pal);
        l_pal= mp_console->palette();
        l_pal.setColor(QPalette::Base, l_color);
        mp_console->setPalette(l_pal);
    }
}
