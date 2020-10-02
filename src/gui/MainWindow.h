/**
 * @file MainWindow.h
 * @brief Header file of the MainWindow class
 *
 * MainWindow GUI holds all PC <-> MCU communication modules
 * @author Farid Oubbati (https://github.com/faroub)
 * @date March 2020
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>


QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace gui
{
class Setting;
class Console;
class LogFile;
class TextFormat;
}
namespace io
{
class SerialPort;
}
namespace gui
{

// TODO: void Window::contextMenu(const QPoint &pos)
class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void about();
    void close();


public:
    /** Constructor. Builds the MainWindow GUI
         *
         *  @param ap_applicationGUI defines pointer to application GUI
         */
    MainWindow();
    /** Destructor.
        */
    ~MainWindow();

    void enableConnectionAction(bool a_enable);

    void enableDisconnectionAction(bool a_enable);

    void enableSetSettingAction(bool a_enable);

    void showStatusMessage(const QString &ar_message);

    void showErrorMessage(const QString &ar_message, const QString &a_error);




protected:
    /** The event handler that receives the Main Window close event
        */
    void closeEvent(QCloseEvent *event) override;

#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

private:

    /** user input condition for the Main Window close event
        */
    bool closeWindow();

    void setupActions();

    void setupMenuBar();

    void setupToolBar();


    Setting *mp_setting = nullptr;

    Console *mp_console = nullptr;

    LogFile *mp_logFile = nullptr;

    TextFormat *mp_textFormat = nullptr;

    io::SerialPort *mp_serialPort = nullptr;

    QLabel *mp_statusMessage = nullptr;

    QAction *mp_connectAction = nullptr;

    QAction *mp_disconnectAction = nullptr;

    QAction *mp_setSettingAction = nullptr;

    QAction *mp_setLocalEchoAction = nullptr;
    
    QAction *mp_clearAction = nullptr;

#ifndef QT_NO_CLIPBOARD

    QAction *mp_copyAction = nullptr;

    QAction *mp_pastAction = nullptr;
#endif

    QAction *mp_selectAllAction = nullptr;

    QAction *mp_exitAction = nullptr;

    QAction *mp_logFileAction = nullptr;

    QAction *mp_textFormatAction = nullptr;

    QAction *mp_asciiAction = nullptr;

    QAction *mp_hexAction = nullptr;






};
}

#endif
