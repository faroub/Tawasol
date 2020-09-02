#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QIcon>
#include "Log.h"
#include "MainWindow.h"
#include "Setting.h"
#include "Console.h"
#include "SerialPort.h"






gui::MainWindow::MainWindow()
                : mp_setting(new Setting(this)),
                  mp_console(new Console(this)),
                  mp_serialPort(new io::SerialPort(this,mp_setting, mp_console)),
                  mp_statusMessage(new QLabel("Disconnected ...",this))

{


    INFO(QString("Start Application"));

    setupActions();
    setupMenuBar();
    setupToolBar();
    statusBar()->addWidget(mp_statusMessage);

    enableDisconnectionAction(false);
    enableConnectionAction(true);


    setWindowTitle("TAWASOL");
    setMinimumSize(500, 500);
    setCentralWidget(mp_console);


}

gui::MainWindow::~MainWindow()
{
    INFO("Close Application");
}

void gui::MainWindow::enableConnectionAction(bool a_enable)
{
    if (a_enable)
    {
        INFO("Enable Connection Action");
        mp_connectAction->setEnabled(true);

    } else {
        INFO("Disable Connection Action");
        mp_connectAction->setEnabled(false);
    }
}

void gui::MainWindow::enableSetSettingAction(bool a_enable)
{
    if (a_enable)
    {
        INFO("Enable Setting Action");
        mp_setSettingAction->setEnabled(true);

    } else {
        INFO("Disable Setting Action");
        mp_setSettingAction->setEnabled(false);
    }
}

void gui::MainWindow::enableDisconnectionAction(bool a_enable)
{
    if (a_enable)
    {
        INFO("Enable Disconnection Action");
        mp_disconnectAction->setEnabled(true);

    } else {
        INFO("Disable Disconnection Action");
        mp_disconnectAction->setEnabled(false);
    }
}

void gui::MainWindow::showStatusMessage(const QString &a_message)
{
    INFO(QString("Show Status Message: %1").arg(a_message));


    mp_statusMessage->setText(a_message);

}
void gui::MainWindow::about()
{
    QMessageBox::about(this, tr("About"),tr("TAWASOL is a Simple Qt Application allows you to communicate\n"
                                            " with a device connected to the serial port."
                                            "\n"
                                            "\n"
                                            "Farid Oubbati\n"
                                            "(https://github.com/faroub)"));
}

void gui::MainWindow::showErrorMessage(const QString &a_message, const QString &a_error)
{
    QMessageBox::critical(this, a_message, a_error);

}
void gui::MainWindow::setupMenuBar()
{
    QMenu *lp_menuIODevice = menuBar()->addMenu(tr("IO&Device"));

    lp_menuIODevice->addAction(mp_connectAction);
    lp_menuIODevice->addAction(mp_disconnectAction);
    lp_menuIODevice->addSeparator();
    lp_menuIODevice->addAction(*(new QIcon(":/application-exit.png")),tr("&Quit"),this, &MainWindow::close);

    QMenu *lp_menuSetting = menuBar()->addMenu(tr("&Port"));

    lp_menuSetting->addAction(mp_setSettingAction);
    lp_menuSetting->addAction(mp_setLocalEcho);


    QMenu *lp_menuHelp = menuBar()->addMenu(tr("&Help"));
    lp_menuHelp->addAction(tr("About"), this, &MainWindow::about);



}

void gui::MainWindow::setupActions()
{
    mp_connectAction = new QAction(QIcon(":/connect.png"),tr("&Connect"), this);
    connect(mp_connectAction, SIGNAL(triggered()), mp_serialPort, SLOT(openSerialPort()));
    mp_disconnectAction = new QAction(QIcon(":/disconnect.png"),tr( "&Disconnect"), this);
    connect(mp_disconnectAction, SIGNAL(triggered()), mp_serialPort, SLOT(closeSerialPort()));
    mp_setSettingAction = new QAction(QIcon(":/settings.png"),tr("&Setting"), this);
    connect(mp_setSettingAction, SIGNAL(triggered()), mp_setting, SLOT(exec()));
    mp_setLocalEcho = new QAction(tr("Local &echo"), this);
    mp_setLocalEcho->setCheckable(true);
    connect(mp_setLocalEcho, SIGNAL(toggled(bool)), mp_console, SLOT(enableLocalEcho(const bool)));    
    mp_clearConsoleAction = new QAction(QIcon(":/clear.png"),tr("C&lear"), this);
    connect(mp_clearConsoleAction, SIGNAL(triggered()), mp_console, SLOT(clear()));



}

void gui::MainWindow::setupToolBar()
{
#ifdef Q_OS_MACOS
    setUnifiedTitleAndToolBarOnMac(true);
#endif
    QToolBar *lp_fileToolBar = addToolBar(tr("IODevice"));

    lp_fileToolBar->addAction(mp_connectAction);
    lp_fileToolBar->addAction(mp_disconnectAction);
    lp_fileToolBar->addAction(mp_setSettingAction);
    lp_fileToolBar->addAction(mp_clearConsoleAction);
    addToolBar(lp_fileToolBar);
}

void gui::MainWindow::closeEvent(QCloseEvent *event)
{
    if (closeWindow()) {
        mp_serialPort->closeSerialPort();
        event->accept();
    }
    else {
        event->ignore();
    }

}

bool gui::MainWindow::closeWindow()
{
    if (!mp_serialPort->isOpen())
    {
        return 1;

    } else {
        const QMessageBox::StandardButton answer = QMessageBox::warning(
                    this,
                    tr("Close TAWASOL"),
                    tr("A connection is still open.\n"
                    "Close anyway?"),
                    QMessageBox::Yes | QMessageBox::No);
        return answer == QMessageBox::Yes;
    }

}

