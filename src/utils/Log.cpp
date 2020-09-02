#include "Log.h"

QString utils::Log::m_logFolderName = "logs";
bool utils::Log::m_isLogFileOpen = false;
QFile utils::Log::m_logFile;



void utils::Log::init(const QString &ar_folderName)
{


#ifdef LOG_TO_FILE

    // set logs folder name
    m_logFolderName = ar_folderName;
    // create folder if no one already exist
    createLogFolder(m_logFolderName);
    // create a new log file
    createNewLogFile(m_logFolderName);
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
        break;
    }

    deleteOldLogFile(m_logFolderName);

    if (m_logFile.size() > LOGFILESIZE) //check current log size
    {
        createNewLogFile(m_logFolderName);
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

void utils::Log::createLogFolder(const QString &ar_folderName)
{

    // Create folder for logfiles if not exists
    if(!QDir(ar_folderName).exists())
    {
      QDir().mkdir(ar_folderName);
    }
}

void utils::Log::createNewLogFile(const QString &ar_folderName)
{
    if (m_isLogFileOpen)
    {
        closeLogFile();
    }
    m_logFile.setFileName(QString(ar_folderName + "/Log_%1__%2.txt")
                          .arg(QDate::currentDate().toString("yyyy_MM_dd"))
                          .arg(QTime::currentTime().toString("hh_mm_ss_zzz")));

}


void utils::Log::deleteOldLogFile(const QString &ar_folderName)
{
    QDir l_dir;
    l_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    l_dir.setSorting(QDir::Time | QDir::Reversed);
    l_dir.setPath(ar_folderName);

    QFileInfoList list = l_dir.entryInfoList();

    if (list.size() <= LOGFILENUMBER)
    {

        return; //no files to delete

    } else {

        for (int i = 0; i < (list.size() - LOGFILENUMBER); i++)
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
