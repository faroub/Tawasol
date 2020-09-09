/**
 * @file main.cpp
 * @brief test Qt application
 * @author Farid Oubbati (https://github.com/faroub)
 * @date March 2020
*/
#include <QApplication>
#include "Log.h"
#include "MainWindow.h"





int main(int argc, char *argv[]) {

    utils::Log::init();
    QApplication App(argc, argv);
    App.setApplicationName("TAWASOL");
    App.setOrganizationName("TAWASOL");
    App.setWindowIcon(QIcon(":/tawasol_logo.png"));
    // Main UI
    gui::MainWindow mainUI;   
    mainUI.show();

    return App.exec();
}




