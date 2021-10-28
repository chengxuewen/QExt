#include <qextConnection.h>
#include <qextSignal.h>

#include <QtTest>
#include <QObject>

#include <iostream>
#include <string>
#include <sstream>

class QEXTConnectionTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void testDisconnectDuringEmit();
};

static std::string sg_string = "";

QEXTConnection connection;
class HandlerClass : public QObject
{
public:
    void handler()
    {
        sg_string = "handler called";
        connection.disconnect();
    }
};

void QEXTConnectionTest::testDisconnectDuringEmit()
{
    HandlerClass instance;

    sg_string = "";
    QEXTSignal<void> signal_test;
    connection = signal_test.connect(instance, &HandlerClass::handler);
    signal_test.send();
    QVERIFY("handler called" == sg_string);
}

QTEST_APPLESS_MAIN(QEXTConnectionTest)

#include <tst_qextConnection.moc>
