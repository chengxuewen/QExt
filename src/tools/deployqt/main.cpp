#include <QCoreApplication>
#include <QFileInfo>
#include <QProcess>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#   include <QLoggingCategory>
#endif

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif

    qDebug() << "QEXT_DEPLOYQT_EXECUTABLE=" << QEXT_DEPLOYQT_EXECUTABLE;
    QProcess::execute(QEXT_DEPLOYQT_EXECUTABLE);

    return 0;
}
