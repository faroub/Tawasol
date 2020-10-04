#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QIcon>
#include <QtWidgets>
#include "MainWindow.h"
#include "Setting.h"
#include "Console.h"
#include "SerialPort.h"
#include "LogFile.h"
#include "TextFormat.h"
#include "LoadConfig.h"
#include "SaveConfig.h"
#include "DeleteConfig.h"
#include "ConfigData.h"






gui::MainWindow::MainWindow()
                : mp_configData(new utils::ConfigData()),
                  mp_setting(new Setting(this,mp_configData)),
                  mp_console(new Console(this,mp_configData)),
                  mp_logFile(new LogFile(this)),
                  mp_textFormat(new TextFormat(this,mp_console)),
                  mp_loadConfig(new LoadConfig(this)),
                  mp_saveConfig(new SaveConfig(this)),
                  mp_deleteConfig(new DeleteConfig(this)),
                  mp_serialPort(new io::SerialPort(this,mp_setting, mp_console)),
                  mp_statusMessage(new QLabel("Disconnected ...",this))

{




    setupActions();
    setupMenuBar();
    setupToolBar();
    statusBar()->addWidget(mp_statusMessage);

    enableDisconnectionAction(false);
    enableConnectionAction(true);

    setCentralWidget(mp_console);
    setWindowTitle("TAWASOL");


    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    resize(screenGeometry.width() / 3, screenGeometry.height() / 2);
    qInfo("Start application");


}

gui::MainWindow::~MainWindow()
{
    qDebug("Distructor main widget");
}

void gui::MainWindow::enableConnectionAction(bool a_enable)
{
    if (a_enable)
    {
        mp_connectAction->setEnabled(true);

    } else {
        mp_connectAction->setEnabled(false);
    }
}

void gui::MainWindow::enableSetSettingAction(bool a_enable)
{
    if (a_enable)
    {
        mp_setSettingAction->setEnabled(true);

    } else {
        mp_setSettingAction->setEnabled(false);
    }
}

void gui::MainWindow::enableDisconnectionAction(bool a_enable)
{
    if (a_enable)
    {
        mp_disconnectAction->setEnabled(true);

    } else {
        mp_disconnectAction->setEnabled(false);
    }
}

void gui::MainWindow::showStatusMessage(const QString &ar_message)
{
    mp_statusMessage->setText(ar_message);

}
void gui::MainWindow::about()
{
    qInfo("Check about dialog");
    QMessageBox::about(this, tr("About"),tr("TAWASOL is a Simple Qt Application which allows you to communicate"
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
    QMenu *lp_menuFile = menuBar()->addMenu(tr("&File"));

    lp_menuFile->addAction(mp_exitAction);


    QMenu *lp_menuEdit = menuBar()->addMenu(tr("&Edit"));
#ifndef QT_NO_CLIPBOARD
    lp_menuEdit->addAction(mp_copyAction);
    lp_menuEdit->addAction(mp_pastAction);
#endif
    lp_menuEdit->addAction(mp_selectAllAction);
    lp_menuEdit->addSeparator();
    lp_menuEdit->addAction(mp_clearAction);

    QMenu *lp_menuIODevice = menuBar()->addMenu(tr("IO&Device"));

    lp_menuIODevice->addAction(mp_connectAction);
    lp_menuIODevice->addAction(mp_disconnectAction);
    lp_menuIODevice->addSeparator();

    QMenu *lp_menuSetting = menuBar()->addMenu(tr("&Port"));

    lp_menuSetting->addAction(mp_setSettingAction);
    lp_menuSetting->addAction(mp_setLocalEchoAction);
    lp_menuSetting->addAction(mp_loadConfigAction);
    lp_menuSetting->addAction(mp_saveConfigAction);
    lp_menuSetting->addAction(mp_deleteConfigAction);

    QMenu *lp_menuView = menuBar()->addMenu(tr("&View"));

    lp_menuView->addAction(mp_asciiAction);
    lp_menuView->addAction(mp_hexAction);
    lp_menuView->addAction(mp_textFormatAction);


    QMenu *lp_menuLog = menuBar()->addMenu(tr("&Log"));

    lp_menuLog->addAction(mp_logFileAction);



    QMenu *lp_menuHelp = menuBar()->addMenu(tr("&Help"));
    lp_menuHelp->addAction(tr("&About"), this, &MainWindow::about);



}

void gui::MainWindow::setupActions()
{
    mp_connectAction = new QAction(QIcon(":/connect.png"),tr("C&onnect"), this);
    connect(mp_connectAction, SIGNAL(triggered()), mp_serialPort, SLOT(openSerialPort()));
    mp_connectAction->setShortcut(Qt::CTRL + Qt::Key_O);

    mp_disconnectAction = new QAction(QIcon(":/disconnect.png"),tr( "&Disconnect"), this);
    connect(mp_disconnectAction, SIGNAL(triggered()), mp_serialPort, SLOT(closeSerialPort()));
    mp_disconnectAction->setShortcut(Qt::CTRL + Qt::Key_D);

    mp_setSettingAction = new QAction(QIcon(":/settings.png"),tr("&Setting"), this);
    connect(mp_setSettingAction, SIGNAL(triggered()), mp_setting, SLOT(open()));
    mp_setSettingAction->setShortcut(Qt::CTRL + Qt::Key_S);

    mp_setLocalEchoAction = new QAction(tr("Local ec&ho"), this);
    mp_setLocalEchoAction->setCheckable(true);
    connect(mp_setLocalEchoAction, SIGNAL(toggled(bool)), mp_console, SLOT(enableLocalEcho(const bool)));
    mp_setLocalEchoAction->setShortcut(Qt::CTRL + Qt::Key_H);

    mp_clearAction = new QAction(QIcon(":/clear.png"),tr("C&lear"), this);
    connect(mp_clearAction, SIGNAL(triggered()), mp_console, SLOT(clear()));
    mp_clearAction->setShortcut(Qt::CTRL + Qt::Key_L);

    mp_selectAllAction = new QAction(QIcon(":/select_all.png"),tr("Select &All"), this);
    connect(mp_selectAllAction, SIGNAL(triggered()), mp_console, SLOT(selectAll()));
    mp_selectAllAction->setShortcuts(QKeySequence::SelectAll);
#ifndef QT_NO_CLIPBOARD

    mp_copyAction = new QAction(QIcon(":/copy.png"),tr("&Copy"), this);
    connect(mp_copyAction, SIGNAL(triggered()), mp_console, SLOT(copy()));
    mp_copyAction->setShortcuts(QKeySequence::Copy);

    mp_pastAction = new QAction(QIcon(":/paste.png"),tr("&Past"), this);
    connect(mp_pastAction, SIGNAL(triggered()), mp_console, SLOT(past()));
    mp_pastAction->setShortcuts(QKeySequence::Paste);

#endif // !QT_NO_CLIPBOARD

    mp_exitAction = new QAction(QIcon(":/exit.png"),tr("&Exit"), this);
    connect(mp_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    mp_exitAction->setShortcut(Qt::CTRL + Qt::Key_E);

#ifndef QT_NO_CLIPBOARD
    mp_copyAction->setEnabled(false);
    mp_pastAction->setEnabled(false);
    connect(mp_console, &QPlainTextEdit::copyAvailable, mp_copyAction, &QAction::setEnabled);
    connect(mp_console, &QPlainTextEdit::copyAvailable, mp_pastAction, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD

    mp_logFileAction = new QAction(QIcon(":/log_file.png"),tr("Log &Files"), this);
    connect(mp_logFileAction, SIGNAL(triggered()), mp_logFile, SLOT(open()));
    mp_logFileAction->setShortcut(Qt::CTRL + Qt::Key_F);

    mp_textFormatAction = new QAction(QIcon(":/text_format.png"),tr("Text Fo&rmat"), this);
    connect(mp_textFormatAction, SIGNAL(triggered()), mp_textFormat, SLOT(open()));
    mp_textFormatAction->setShortcut(Qt::CTRL + Qt::Key_R);

    QActionGroup *lp_actionGroup = new QActionGroup(this);

    mp_asciiAction = new QAction(QIcon(":/ascii.png"),tr("&ASCII"), this);
    connect(mp_asciiAction, SIGNAL(triggered()), mp_textFormat, SLOT(open()));
    mp_asciiAction->setShortcut(Qt::CTRL + Qt::Key_A);
    mp_asciiAction->setCheckable(true);
    lp_actionGroup->addAction(mp_asciiAction);

    mp_hexAction = new QAction(QIcon(":/hex.png"),tr("HE&X"), this);
    connect(mp_hexAction, SIGNAL(triggered()), mp_textFormat, SLOT(open()));
    mp_hexAction->setShortcut(Qt::CTRL + Qt::Key_X);
    mp_hexAction->setCheckable(true);
    lp_actionGroup->addAction(mp_hexAction);
    mp_asciiAction->setChecked(true);

    mp_loadConfigAction = new QAction(QIcon(":/settings_file.png"),tr("Load Confi&guration"), this);
    connect(mp_loadConfigAction, SIGNAL(triggered()), mp_loadConfig, SLOT(open()));
    mp_loadConfigAction->setShortcut(Qt::CTRL + Qt::Key_G);

    mp_saveConfigAction = new QAction(QIcon(":/settings_file.png"),tr("Sa&ve Configuration"), this);
    connect(mp_saveConfigAction, SIGNAL(triggered()), mp_saveConfig, SLOT(open()));
    mp_saveConfigAction->setShortcut(Qt::CTRL + Qt::Key_V);

    mp_deleteConfigAction = new QAction(QIcon(":/settings_file.png"),tr("Dele&te Configuration"), this);
    connect(mp_deleteConfigAction, SIGNAL(triggered()), mp_deleteConfig, SLOT(open()));
    mp_deleteConfigAction->setShortcut(Qt::CTRL + Qt::Key_T);
}

void gui::MainWindow::setupToolBar()
{
#ifdef Q_OS_MACOS
    setUnifiedTitleAndToolBarOnMac(true);
#endif
    QToolBar *lp_fileToolBar = addToolBar(tr("IODevice"));

    lp_fileToolBar->addAction(mp_connectAction);
    lp_fileToolBar->addAction(mp_disconnectAction);
    QToolBar *lp_portToolBar = addToolBar(tr("Port"));
    lp_portToolBar->addAction(mp_setSettingAction);
#ifndef QT_NO_CLIPBOARD
    QToolBar *lp_editToolBar = addToolBar(tr("Edit"));
    lp_editToolBar->addAction(mp_copyAction);
    lp_editToolBar->addAction(mp_pastAction);
#endif
    lp_editToolBar->addAction(mp_selectAllAction);
    lp_editToolBar->addAction(mp_clearAction);

    addToolBar(lp_fileToolBar);
    addToolBar(lp_portToolBar);
    addToolBar(lp_editToolBar);


}

void gui::MainWindow::closeEvent(QCloseEvent *event)
{
    if (closeWindow()) {
        mp_serialPort->closeSerialPort();
        qInfo("Exit application");
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

void gui::MainWindow::close()
{
    QMainWindow::close();

}

#ifndef QT_NO_CONTEXTMENU
void gui::MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu l_contextMenu(this);
#ifndef QT_NO_CLIPBOARD
    l_contextMenu.addAction(mp_copyAction);
    l_contextMenu.addAction(mp_pastAction);
#endif // !QT_NO_CLIPBOARD
    l_contextMenu.addAction(mp_selectAllAction);
    l_contextMenu.addSeparator();
    l_contextMenu.addAction(mp_clearAction);
    l_contextMenu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
