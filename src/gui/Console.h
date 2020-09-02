/**
 * @file Console.h
 * @brief Header file of the console class
 *
 * Console GUI allows to read/write data from/to the communication port
 * @author Farid Oubbati (https://github.com/faroub)
 * @date March 2020
*/
#ifndef CONSOLE_H
#define CONSOLE_H
#include "tawasol_utils.h"
#include <QPlainTextEdit>

namespace gui
{

class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:

    void sendData(const QByteArray &data);

public slots:

    void enableLocalEcho(const bool a_enable);


public:

    Console(QWidget *ap_parent = nullptr);

    ~Console() override;

    void writeData(const QByteArray &data);



protected:
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *e) override;
private:
    bool m_localEchoEnabled = false;
};


}




#endif // CONSOLE_H
