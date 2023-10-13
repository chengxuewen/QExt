#include <qextConnection.h>
#include <qextSignal.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QExtConnectionTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testDisconnectDuringEmit();
};

static QString sg_string = "";

QExtConnection connection;
class HandlerClass : public QObject
{
public:
    void handler()
    {
        sg_string = "handler called";
        connection.disconnect();
    }
};

void QExtConnectionTest::testDisconnectDuringEmit()
{
    HandlerClass instance;

    sg_string = "";
    QExtSignal<void> signal_test;
    connection = signal_test.connect(instance, &HandlerClass::handler);
    signal_test.send();
    QVERIFY("handler called" == sg_string);
}

QTEST_APPLESS_MAIN(QExtConnectionTest)

#include <tst_qextConnection.moc>
