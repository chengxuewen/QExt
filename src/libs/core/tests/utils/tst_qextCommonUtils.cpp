#include <qextCommonUtils.h>

#include <QtTest>
#include <QDebug>
#include <QApplication>

class QExtCommonUtilsTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void application();
};

void QExtCommonUtilsTest::application()
{
    QCOMPARE(QCoreApplication::applicationFilePath(), QExtCommonUtils::executablePath());
    QCOMPARE(QCoreApplication::applicationDirPath(), QExtCommonUtils::executableDir());
}


QTEST_MAIN(QExtCommonUtilsTest)

#include <tst_qextCommonUtils.moc>
