#include "Log.h"

QString utils::Log::m_logsFolderName = "logs";
bool utils::Log::m_isLogFileOpen = false;
QFile utils::Log::m_logFile;
int utils::Log::m_logFileSize = 100; // kB
int utils::Log::m_logFileNumber = 5;


void utils::Log::init()
{

#ifdef LOG_TO_FILE


    // create folder if no one already exist
    createLogsFolder(m_logsFolderName);
    // create a new log file
    createNewLogFile(m_logsFolderName);
    // open log file
    m_isLogFileOpen = openLogFile();

    // install log message handler
    qInstallMessageHandler(logMessageHandler);

#else

    qSetMessagePattern("[%{time dd-MM-yyyy h:mm:ss:}] [%{appname}] [%{type}] [%{threadid}] [%{pid}] %{function}:%{line} - %{message}");


#endif


}

void utils::Log::logMessageHandler(QtMsgType a_type, const QMessageLogContext &ar_context, const QString& ar_message)
{
    qint64 l_pid = QCoreApplication::applicationPid();
    QString l_appName = QCoreApplication::applicationName();

    const char *l_function = ar_context.function ? ar_context.function : "";
    QString l_text;

    l_text += "[" + QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss:") + "] ";

    switch (a_type) {
    case QtDebugMsg:
        l_text += QString("[%1] [debug] [%2] %3:%4 - ").arg(l_appName).arg(l_pid).arg(l_function).arg(ar_context.line);
        l_text += ar_message;
        break;
    case QtInfoMsg:
        l_text += QString("[%1] [info] [%2] %3:%4 - ").arg(l_appName).arg(l_pid).arg(l_function).arg(ar_context.line);
        l_text += ar_message;
        break;
    case QtWarningMsg:
        l_text += QString("[%1] [warning] [%2] %3:%4 - ").arg(l_appName).arg(l_pid).arg(l_function).arg(ar_context.line);
        l_text += ar_message;
        break;
    case QtCriticalMsg:
        l_text += QString("[%1] [critical] [%2] %3:%4 - ").arg(l_appName).arg(l_pid).arg(l_function).arg(ar_context.line);
        l_text += ar_message;
        break;
    case QtFatalMsg:
        l_text += QString("[%1] [fatal] [%2] %3:%4 - ").arg(l_appName).arg(l_pid).arg(l_function).arg(ar_context.line);
        l_text += ar_message;
        abort();
    }

    deleteOldLogFile(m_logsFolderName);

    if (m_logFile.size() > (m_logFileSize * 1024)) //check current log size
    {
        createNewLogFile(m_logsFolderName);
        m_isLogFileOpen = openLogFile();
        if (m_isLogFileOpen)
        {
            // log message in log file
            writeLogMessage(l_text);

        } else {
            // log error message
        }

    } else {

        if (m_isLogFileOpen)
        {
            // log message in log file
            writeLogMessage(l_text);

        } else {

            // log error message
        }

    }

}

void utils::Log::createLogsFolder(const QString &ar_logsFolderName)
{

    // Create folder for logfiles if not exists
    if(!QDir(ar_logsFolderName).exists())
    {
      QDir().mkdir(ar_logsFolderName);
    }
}

void utils::Log::createNewLogFile(const QString &ar_logsFolderName)
{
    if (m_isLogFileOpen)
    {
        closeLogFile();
    }
    m_logFile.setFileName(QString(ar_logsFolderName + "/Log_%1__%2.txt")
                          .arg(QDate::currentDate().toString("yyyy_MM_dd"))
                          .arg(QTime::currentTime().toString("hh_mm_ss_zzz")));

}


void utils::Log::deleteOldLogFile(const QString &ar_logsFolderName)
{
    QDir l_dir;
    l_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    l_dir.setSorting(QDir::Time | QDir::Reversed);
    l_dir.setPath(ar_logsFolderName);

    QFileInfoList list = l_dir.entryInfoList();

    if (list.size() <= m_logFileNumber)
    {

        return; //no files to delete

    } else {

        for (int i = 0; i < (list.size() - m_logFileNumber); i++)
        {
            QFile l_file(list.at(i).absoluteFilePath());
            l_file.remove();
        }

    }

}

bool utils::Log::openLogFile()
{
    return m_logFile.open(QIODevice::WriteOnly | QIODevice::Append);
}

void utils::Log::closeLogFile()
{
    m_logFile.close();
}

bool utils::Log::writeLogMessage(const QString &ar_logMessage)
{
    return m_logFile.write(qPrintable(ar_logMessage+"\n"));
}

void utils::Log::setLogFileNumber(const int &ar_logFileNumber)
{
    m_logFileNumber = ar_logFileNumber;
}

void utils::Log::setLogFileSize(const int &ar_logFileSize)
{
    m_logFileSize = ar_logFileSize;
}

int utils::Log::getLogFileSize()
{
    return m_logFileSize;
}

int utils::Log::getLogFileNumber()
{
    return m_logFileNumber;
}

void utils::Log::setLogsFolderName(const QString &ar_logsFolderName)
{
    m_logsFolderName = ar_logsFolderName;
}


QString utils::Log::getLogsFolderName()
{
    return m_logsFolderName;
}
