#include <QDebug>
#include <QScrollBar>
#include "Console.h"
#include "ConfigData.h"


gui::Console::Console(QWidget *ap_parent, utils::ConfigData *ap_ConfigData)
             : QPlainTextEdit(ap_parent),
               mp_configData(ap_ConfigData)
{

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::white);
    setPalette(p);
    setEnabled(false);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


}

gui::Console::~Console()
{
    qDebug("Distructor console widget");
}


void gui::Console::writeData(const QByteArray &ar_data)
{
    insertPlainText(ar_data);
    QScrollBar *lp_bar = verticalScrollBar();
    lp_bar->setValue(lp_bar->maximum());
    lp_bar = horizontalScrollBar();
    lp_bar->setValue(lp_bar->maximum());

}

void gui::Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Backspace:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            break;
        default:
        {
            if (m_localEchoEnabled)
            {
                QPlainTextEdit::keyPressEvent(e);
            }
            emit sendData(e->text().toLocal8Bit());
            break;
        }
    }

}

void gui::Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();

}

void gui::Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

}

void gui::Console::contextMenuEvent(QContextMenuEvent *e)
{
     Q_UNUSED(e)

}

void gui::Console::enableLocalEcho(const bool a_enable)
{
    qInfo("Set local echo: %d", a_enable);
    m_localEchoEnabled = a_enable;
}

void gui::Console::clear()
{
    qInfo("Clear console");
    QPlainTextEdit::clear();

}

void gui::Console::copy()
{
    qInfo("Copy text");
    QPlainTextEdit::copy();

}

void gui::Console::selectAll()
{
    qInfo("Select all text");
    QPlainTextEdit::selectAll();

}

void gui::Console::past()
{
    qInfo("Paste text");
    QPlainTextEdit::paste();

}

