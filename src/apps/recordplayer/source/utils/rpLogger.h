#ifndef _RPLOGGER_H
#define _RPLOGGER_H

#include <rpGlobal.h>
#include <rpConstants.h>

#include <QDebug>
#include <QPointer>
#include <QLoggingCategory>

class RPLoggerPrivate;
class RPLogger : public QObject
{
    Q_OBJECT
public:
    RP_DECL_PTRS(RPLogger)

    enum Output
    {
        Output_Console = 0,
        Output_File
    };
    static constexpr int OutputNum = 2;

    enum Format
    {
        Format_Category = 0,
        Format_Level,
        Format_File,
        Format_Line,
    };
    static constexpr int FormatNum = 4;

    RPLogger(const char *categoryName, QObject *parent = nullptr);
    static RPLogger::SharedPtr instance(const char *categoryName);
    ~RPLogger();

    bool outputEnable(Output output) const;
    void setOutputEnable(Output output, bool enable);

    bool formatEnable(Format format) const;
    void setFormatEnable(Format format, bool enable);
    void setAllFormatsEnable(bool enable);

    void clearLogFile();
    void readLogFile();
    void exportLogFile();
    QString logFilePath() const;
    const char *categoryName() const;

    static void quitThread();
    static QString msgTypeString(int type, bool isEng = false);
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:
    void logFileText(const QString &log);
    void exportLogFileText(const QString &log);

    void newMessage(QtMsgType type, const QString &msg);
    void newFormatedMessage(QtMsgType type, const QString &msg);
    void addLog(QtMsgType type, int line, const char *filePath, const char *function,
                const char *category, const QString &msg, qint64 epochSinceMSecs);

protected:
    void outputLog(QtMsgType type, int line, const char *file, const char *function, const char *category,
                   const QString &msg, qint64 epochSinceMSecs);

    QScopedPointer<RPLoggerPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(RPLogger)
    Q_DECLARE_PRIVATE_D(dd_ptr, RPLogger)
};

Q_DECLARE_LOGGING_CATEGORY(RP_DEV)
Q_DECLARE_LOGGING_CATEGORY(RP_USER)
Q_DECLARE_LOGGING_CATEGORY(RP_IODEV)
Q_DECLARE_LOGGING_CATEGORY(RP_IOUSR)
Q_DECLARE_LOGGING_CATEGORY(RP_CONFIGURE)

#endif //_RPLOGGER_H
