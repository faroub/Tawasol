#ifndef LOG_H
#define LOG_H
#include <QtGlobal>

#define kBytesToBytes 1024

QT_BEGIN_NAMESPACE
class QString;
class QFile;
QT_END_NAMESPACE




// use a gui to decide to log in file or not
// decide with levels should logged

namespace utils
{

class Log
{

public:

    static void init();

    static void createLogsFolder(const QString &ar_logsFolderName);

    static void setLogFileSize(const int &ar_logFileSize);

    static void setLogFileNumber(const int &ar_logFileNumber);

    static int getLogFileSize();

    static int getLogFileNumber();

    static void setLogsFolderName(const QString &ar_logsFolderName);

    static QString getLogsFolderName();

protected:

private:

    static void createNewLogFile(const QString &ar_logsFolderName);

    static bool openLogFile();

    static void closeLogFile();

    static void deleteOldLogFile(const QString &ar_logsFolderName);

    static void logMessageHandler(QtMsgType a_type, const QMessageLogContext &ar_context, const QString &ar_message);

    static bool writeLogMessage(const QString &ar_logMessage);

    static QString m_logsFolderName;

    static bool m_isLogFileOpen;

    static QFile m_logFile;

    static int m_logFileSize;

    static int m_logFileNumber;

};





}

#endif // LOG_H
