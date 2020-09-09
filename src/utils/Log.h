#ifndef LOG_H
#define LOG_H
#include <QDebug>
#include <QCoreApplication>
#include <QThread>
#include <QDate>
#include <QTime>
#include <QDir>

#define LOGFILESIZE 1024 * 100 //100kB
#define LOGFILENUMBER 5
//#define LOG_TO_FILE


// use a gui to decide to log in file or not
// decide with levels should logged

namespace utils
{

class Log
{

public:

    static void init(const QString &ar_folderName = "logs");

    static void createLogFolder(const QString &ar_folderName);


protected:

private:

    static void createNewLogFile(const QString &ar_folderName);

    static bool openLogFile();

    static void closeLogFile();

    static void deleteOldLogFile(const QString &ar_folderName);

    static void logMessageHandler(QtMsgType a_type, const QMessageLogContext &ar_context, const QString &ar_message);

    static bool writeLogMessage(const QString &ar_logMessage);

    static QString m_logFolderName;

    static bool m_isLogFileOpen;

    static QFile m_logFile;

};





}

//#ifdef QT_DEBUG
//#include <modeltest.h>
//#endif


// 	#ifdef QT_DEBUG
// new ModelTest(m_engineOptionModel, this);
// #endif
//// logging macros
/// // QT_NO_INFO_OUTPUT
/// QT_NO_DEBUG_OUTPUT
/// QT_NO_WARNING_OUTPUT
/// QT_FATAL_CRITICALS
//#ifdef QT_NO_DEBUG
//    #define DEBUG(...)
//#else
//    #define DEBUG(...)      qDebug(__VA_ARGS__)
//#endif

//#define INFO(msg)       qInfo(qPrintable(msg))
//#define WARNING(...)    qWarning(__VA_ARGS__)
//#define CRITICAL(...)   qCritical(__VA_ARGS__)
//#define FATAL(...)      qFatal(__VA_ARGS__)



#endif // LOG_H
