#ifndef QEXTCONNECTIONTEST_H
#define QEXTCONNECTIONTEST_H

#include <qextConnection.h>
#include <qextSignal.h>

#include <iostream>
#include <string>
#include <sstream>

#include <CppUTest/TestHarness.h>

QEXT_USE_NAMESPACE

namespace qextConnectionTest
{

    static std::string sg_string = "";

    QEXTConnection connection;
    class HandlerClass : public QEXTObject
    {
    public:
        void handler()
        {
            sg_string = "handler called";
            connection.disconnect();
        }
    };


    TEST_GROUP(qextConnectionTest)
    {
    };

    TEST(qextConnectionTest, testDisconnectDuringEmit)
    {
        HandlerClass instance;

        sg_string = "";
        QEXTSignal<void> signal_test;
        connection = signal_test.connect(instance, &HandlerClass::handler);
        signal_test.send();
        CHECK("handler called" == sg_string);
    }

} // namespace qextConnectionTest

#endif // QEXTCONNECTIONTEST_H
