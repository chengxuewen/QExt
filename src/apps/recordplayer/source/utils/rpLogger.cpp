#include <rpLogger.h>
#include <rpCommonUtils.h>

#include <QMutex>
#include <QMutexLocker>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTimer>
#include <QThread>
#include <QTextStream>
#include <QApplication>
#include <QAtomicPointer>
#include <QStandardPaths>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>

#include <qextDateTimeUtils.h>

#include <mutex>

#define RP_LOGGER_VAR(name)         name##Logger
#define RP_LOGGER_ONCE_VAR(name)    name##OnceFlag
#define RP_CATEGORY_NAME_VAR(name)  sg_##name##CategoryName

#define RP_LOGGING_CATEGORY_LOGGER(thread, category, level) \
    static const char *RP_CATEGORY_NAME_VAR(category) = #category; \
    Q_LOGGING_CATEGORY(category, RP_CATEGORY_NAME_VAR(category), level) \
    static RPLogger::SharedPtr category##_Logger() { \
    static RPLogger::SharedPtr RP_LOGGER_VAR(category); \
    static std::once_flag RP_LOGGER_ONCE_VAR(category); \
    std::call_once(RP_LOGGER_ONCE_VAR(category), [&](){ \
    RP_LOGGER_VAR(category).reset(new RPLogger(RP_CATEGORY_NAME_VAR(category))); \
    RP_LOGGER_VAR(category)->moveToThread(thread); \
    QObject::connect(qApp, &QApplication::destroyed, RP_LOGGER_VAR(category).data(), &RPLogger::deleteLater); \
    }); \
    return RP_LOGGER_VAR(category); \
    }

static QThread *sg_loggerThread = nullptr;
RP_LOGGING_CATEGORY_LOGGER(sg_loggerThread, RP_DEV, QtDebugMsg)
RP_LOGGING_CATEGORY_LOGGER(sg_loggerThread, RP_USER, QtDebugMsg)
RP_LOGGING_CATEGORY_LOGGER(sg_loggerThread, RP_IODEV, QtDebugMsg)
RP_LOGGING_CATEGORY_LOGGER(sg_loggerThread, RP_IOUSR, QtDebugMsg)
RP_LOGGING_CATEGORY_LOGGER(sg_loggerThread, RP_CONFIGURE, QtDebugMsg)

class RPLoggerPrivate
{
public:
    RPLoggerPrivate(RPLogger *q, const char *categoryName);
    virtual ~RPLoggerPrivate();

    void openLogFile();

    RPLogger *const q_ptr;

    mutable QMutex m_mutex;
    QFile m_logFile;
    QString m_logFilePath;
    QTextStream m_logFileStream;
    QAtomicInt m_outputEnable[RPLogger::OutputNum];
    QAtomicInt m_formatEnable[RPLogger::FormatNum];
    const char *m_categoryName;

private:
    Q_DISABLE_COPY(RPLoggerPrivate)
    Q_DECLARE_PUBLIC(RPLogger)
};

RPLoggerPrivate::RPLoggerPrivate(RPLogger *q, const char *categoryName)
    : q_ptr(q)
    , m_logFilePath(RPCommonUtils::appDataLocation() + QString("/%1.log").arg(categoryName))
    , m_logFileStream(&m_logFile)
    , m_categoryName(categoryName)
{
    m_outputEnable[RPLogger::Output_Console] = false;
    m_outputEnable[RPLogger::Output_File] = true;

    m_formatEnable[RPLogger::Format_Category] = false;
    m_formatEnable[RPLogger::Format_File] = true;
    m_formatEnable[RPLogger::Format_Level] = true;
    m_formatEnable[RPLogger::Format_Line] = false;
}

RPLoggerPrivate::~RPLoggerPrivate()
{
    if (m_logFile.isOpen())
    {
        m_logFile.close();
    }
}

void RPLoggerPrivate::openLogFile()
{
    if (!m_logFile.exists() && m_logFile.isOpen())
    {
        fprintf(stderr, "logFile-close:%s\n", m_logFile.fileName().toLatin1().data());
        fflush(stderr);
        m_logFile.close();
    }
    if (!m_logFile.isOpen())
    {
        m_logFile.setFileName(m_logFilePath);
        bool ret = m_logFile.open(QIODevice::ReadWrite | QIODevice::Append);
        if (!ret)
        {
            qFatal("%s log file open failed %s", m_logFilePath.toLatin1().data(),
                   m_logFile.errorString().toLatin1().data());
        }
        if (!m_logFile.exists())
        {
            qFatal("%s log file not exist", m_logFilePath.toLatin1().data());
        }
        m_logFileStream.reset();
    }
}

RPLogger::RPLogger(const char *categoryName, QObject *parent)
    : QObject(parent), dd_ptr(new RPLoggerPrivate(this, categoryName))
{
    qRegisterMetaType<QtMsgType>("QtMsgType");
    connect(this, &RPLogger::addLog, this, &RPLogger::outputLog);
}

#ifdef Q_OS_WIN
#   define RP_DIR_SPLIT "\\"
#else
#   define RP_DIR_SPLIT "/"
#endif
void RPLogger::outputLog(QtMsgType type, int line, const char *filePath, const char *function, const char *category,
                         const QString &msg, qint64 epochSinceMSecs)
{
    QString fileName = filePath;
    QString formatedMsg = QExtDateTimeUtils::localTimeStringFromMSecsSinceEpoch(epochSinceMSecs);
    if (dd_ptr->m_formatEnable[Format_Category].loadAcquire())
    {
        formatedMsg.append(QString(" <%1>").arg(category ? category : "Default"));
    }
    if (dd_ptr->m_formatEnable[Format_Level].loadAcquire())
    {
        formatedMsg.append(QString(" [%1]").arg(RPLogger::msgTypeString(type, true)));
    }
    if (dd_ptr->m_formatEnable[Format_File].loadAcquire())
    {
        formatedMsg.append(QString(" [%1]").arg(fileName.mid(fileName.lastIndexOf(RP_DIR_SPLIT) + 1)));
    }
    if (dd_ptr->m_formatEnable[Format_Line].loadAcquire())
    {
        formatedMsg.append(QString(" [%1]").arg(line));
    }
    formatedMsg.append(QString(" MSG:%1").arg(msg));

    if (dd_ptr->m_outputEnable[Output_Console].loadAcquire())
    {
        fprintf(stdout, "%s\n", formatedMsg.toLatin1().data());
        fflush(stdout);
    }

    if (dd_ptr->m_outputEnable[Output_File].loadAcquire())
    {
        dd_ptr->openLogFile();
        static constexpr int maxSize = 10000 * 1024;
        if (dd_ptr->m_logFile.size() >= maxSize)
        {
            dd_ptr->m_logFileStream.seek(dd_ptr->m_logFile.size() / 5);
            dd_ptr->m_logFileStream.readLine();
            auto string = dd_ptr->m_logFileStream.readAll();
            dd_ptr->m_logFile.resize(0);
            dd_ptr->m_logFileStream.reset();
            dd_ptr->m_logFileStream << string;
            dd_ptr->m_logFileStream.flush();
        }
        dd_ptr->m_logFileStream << formatedMsg << "\r\n";
        dd_ptr->m_logFileStream.flush();
    }

    emit this->newMessage(type, msg);
    emit this->newFormatedMessage(type, formatedMsg);
}

RPLogger::~RPLogger()
{
}

bool RPLogger::outputEnable(Output output) const
{
    Q_D(const RPLogger);
    return d->m_outputEnable[output].loadAcquire();
}

void RPLogger::setOutputEnable(Output output, bool enable)
{
    Q_D(RPLogger);
    d->m_outputEnable[output].storeRelease(enable);
}

bool RPLogger::formatEnable(Format format) const
{
    Q_D(const RPLogger);
    return d->m_formatEnable[format].loadAcquire();
}

void RPLogger::setFormatEnable(Format format, bool enable)
{
    Q_D(RPLogger);
    d->m_formatEnable[format].storeRelease(enable);
}

void RPLogger::setAllFormatsEnable(bool enable)
{
    Q_D(RPLogger);
    for (int i = 0; i < RPLogger::FormatNum; ++i)
    {
        d->m_formatEnable[i].storeRelease(enable);
    }
}

RPLogger::SharedPtr RPLogger::instance(const char *categoryName)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
        sg_loggerThread = new QThread(qApp);
        sg_loggerThread->start();
    });

    if (categoryName == RP_USER().categoryName())
    {
        return RP_USER_Logger();
    }
    else if (categoryName == RP_IODEV().categoryName())
    {
        return RP_IODEV_Logger();
    }
    else if (categoryName == RP_IOUSR().categoryName())
    {
        return RP_IOUSR_Logger();
    }
    else if (categoryName == RP_CONFIGURE().categoryName())
    {
        return RP_CONFIGURE_Logger();
    }
    else
    {
        return RP_DEV_Logger();
    }
}

void RPLogger::clearLogFile()
{
    QTimer::singleShot(0, this, [=]()
    {
        Q_D(RPLogger);
        d->openLogFile();
        d->m_logFile.resize(0);
        d->m_logFileStream.reset();
        emit this->logFileText("");
    });
}

void RPLogger::readLogFile()
{
    QTimer::singleShot(0, this, [=]()
    {
        Q_D(RPLogger);
        d->openLogFile();
        d->m_logFileStream.seek(0);
        QString data = d->m_logFileStream.readAll();
        d->m_logFileStream.reset();
        emit this->logFileText(data);
    });
}

void RPLogger::exportLogFile()
{
    QTimer::singleShot(0, this, [=]()
    {
        Q_D(RPLogger);
        d->openLogFile();
        d->m_logFileStream.seek(0);
        QString data = d->m_logFileStream.readAll();
        d->m_logFileStream.reset();
        emit this->exportLogFileText(data);
    });
}

QString RPLogger::logFilePath() const
{
    Q_D(const RPLogger);
    return d->m_logFilePath;
}

QString RPLogger::msgTypeString(int type, bool isEng)
{
    switch (type)
    {
        case QtInfoMsg:
            return isEng ? "Info" : tr("Info");
        case QtDebugMsg:
            return isEng ? "Debug" : tr("Debug");
        case QtWarningMsg:
            return isEng ? "Warning" : tr("Warning");
        case QtCriticalMsg:
            return isEng ? "Critical" : tr("Critical");
        case QtFatalMsg:
            return isEng ? "Fatal" : tr("Fatal");
        default:
            return "???";
    }
}

const char *RPLogger::categoryName() const
{
    Q_D(const RPLogger);
    return d->m_categoryName;
}

void RPLogger::quitThread()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&]()
    {
        if (sg_loggerThread && sg_loggerThread->isRunning())
        {
            sg_loggerThread->quit();
            sg_loggerThread->wait();
            sg_loggerThread->deleteLater();
            sg_loggerThread = nullptr;
        }
    });
}

void RPLogger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto logger = RPLogger::instance(context.category);
    if (!logger.isNull())
    {
        emit logger->addLog(type,
                            context.line,
                            context.file,
                            context.function,
                            context.category,
                            msg,
                            QExtDateTimeUtils::msecsTimeSinceEpoch());
    }
    else
    {
        const auto timestamp = QExtDateTimeUtils::localTimeStringFromMSecsSinceEpoch();
        fprintf(stderr, "%s <%s>[%s] MSG:%s\n", timestamp.toLatin1().data(),
                RPLogger::msgTypeString(type).toLatin1().data(), context.category, msg.toLatin1().data());
    }
}
