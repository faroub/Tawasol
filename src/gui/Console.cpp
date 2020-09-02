#include <QDebug>
#include <QScrollBar>
#include "Console.h"


gui::Console::Console(QWidget *ap_parent)
            : QPlainTextEdit(ap_parent)
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
    m_localEchoEnabled = a_enable;
}
