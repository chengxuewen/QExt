#include <qextTSValue.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

class QExtTSValueTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();
};


void QExtTSValueTest::constructor()
{

}

QTEST_APPLESS_MAIN(QExtTSValueTest)

#include <tst_qextTSValue.moc>
