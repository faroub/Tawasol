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



gui::TextFormat::TextFormat(QWidget *ap_parent, Console *ap_console) :
    QDialog(ap_parent)
{
    mp_console = ap_console;
    Q_CHECK_PTR(mp_console);

    m_consoleFont = mp_console->font();


    QPushButton *lp_okButton = new QPushButton(tr("OK"));
    QPushButton *lp_cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *lp_hLayout = new QHBoxLayout();
    lp_hLayout->addWidget(lp_okButton);
    lp_hLayout->addWidget(lp_cancelButton);

    QLabel *lp_fontLabel = new QLabel(tr("Font:"));
    lp_fontLabel->setAlignment(Qt::AlignRight);

    mp_fontButton = new QPushButton();
    mp_fontButton->setText(m_consoleFont.family()+" | "+QString::number(m_consoleFont.pointSize()));


    QLabel *lp_fontColorLabel = new QLabel(tr("Font color:"));
    lp_fontColorLabel->setAlignment(Qt::AlignRight);

    mp_fontColorButton = new QPushButton();
    QPalette l_palette = mp_fontColorButton->palette();
    l_palette.setColor(QPalette::Button,mp_console->palette().color(QPalette::Text));
    mp_fontColorButton->setPalette(l_palette);


    QLabel *lp_backgroundColorLabel = new QLabel(tr("Background color:"));
    lp_backgroundColorLabel->setAlignment(Qt::AlignRight);

    mp_backgroundColorButton = new QPushButton();
    l_palette = mp_backgroundColorButton->palette();
    l_palette.setColor(QPalette::Button,mp_console->palette().color(QPalette::Base));
    mp_backgroundColorButton->setPalette(l_palette);



    QGridLayout *lp_textFormatGridLayout = new QGridLayout();

    lp_textFormatGridLayout->addWidget(lp_fontLabel,0,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_fontButton,0,1,1,4);
    lp_textFormatGridLayout->addWidget(lp_fontColorLabel,2,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_fontColorButton,2,1,1,1);
    lp_textFormatGridLayout->addWidget(lp_backgroundColorLabel,3,0,1,1);
    lp_textFormatGridLayout->addWidget(mp_backgroundColorButton,3,1,1,1);


    QGridLayout *lp_mainGridLayout = new QGridLayout();

    lp_mainGridLayout->addLayout(lp_textFormatGridLayout,0,0,1,6);
    lp_mainGridLayout->addLayout(lp_hLayout,1,4,1,2);


    connect(lp_okButton, &QPushButton::clicked, this, &TextFormat::update);

    connect(lp_cancelButton, &QPushButton::clicked, this, &TextFormat::close);

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
    qInfo("Close text format widget");
    cancelTextFormat();
    QDialog::close();

}

void gui::TextFormat::update()
{
    qInfo("Update text format and close text format widget");
    updateTextFormat();
    QDialog::close();

}

void gui::TextFormat::updateTextFormat()
{
    mp_console->setFont(m_consoleFont);

    QPalette l_consolePalette = mp_console->palette();

    l_consolePalette.setColor(QPalette::Text, mp_fontColorButton->palette().color(QPalette::Button));
    mp_console->setPalette(l_consolePalette);

    l_consolePalette.setColor(QPalette::Base, mp_backgroundColorButton->palette().color(QPalette::Button));
    mp_console->setPalette(l_consolePalette);

}

void gui::TextFormat::cancelTextFormat()
{
    mp_fontButton->setText(mp_console->font().family()+" | "+QString::number(mp_console->font().pointSize()));

    QPalette l_palette = mp_fontColorButton->palette();    
    l_palette.setColor(QPalette::Button,mp_console->palette().color(QPalette::Text));
    mp_fontColorButton->setPalette(l_palette);

    l_palette = mp_backgroundColorButton->palette();
    l_palette.setColor(QPalette::Button,mp_console->palette().color(QPalette::Base));
    mp_backgroundColorButton->setPalette(l_palette);

}

void gui::TextFormat::setFontColor()
{
    const QColor l_color = QColorDialog::getColor(Qt::green, this, "Select Color");

    if (l_color.isValid()) {

        QPalette l_palette= mp_fontColorButton->palette();
        l_palette.setColor(QPalette::Button,l_color);
        mp_fontColorButton->setPalette(l_palette);

        
    }
}

void gui::TextFormat::setFont()
{
    bool l_ok;
    m_consoleFont = QFontDialog::getFont(&l_ok, this);

    if (l_ok) {
        mp_fontButton->setText(m_consoleFont.family()+" | "+QString::number(m_consoleFont.pointSize()));

    }
}

void gui::TextFormat::setBackgroundColor()
{
    const QColor l_color = QColorDialog::getColor(Qt::green, this, "Select Color");

    if (l_color.isValid()) {

        QPalette l_palette= mp_backgroundColorButton->palette();
        l_palette.setColor(QPalette::Button,l_color);
        mp_backgroundColorButton->setPalette(l_palette);

    }
}
