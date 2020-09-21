#ifndef FORMAT_H
#define FORMAT_H
#include <QDialog>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE
namespace gui
{
class Console;
}
namespace gui
{

class TextFormat : public QDialog
{
    Q_OBJECT


public slots:

    void open();
    void close();
    void update();
    void setFontColor();
    void setFont();
    void setBackgroundColor();



public:

    TextFormat(QWidget *ap_parent = nullptr, gui::Console *ap_console = nullptr);

    ~TextFormat();
private:

    QPushButton *mp_fontButton = nullptr;

    QPushButton *mp_fontColorButton = nullptr;

    QPushButton *mp_backgroundColorButton = nullptr;

    gui::Console *mp_console = nullptr;

};




}



#endif // CONSOLE_FORMAT_H
