#include <qextMemory.h>

#include <QtTest>
#include <QtEndian>
#include <QByteArray>
#include <QDebug>

#include <iostream>

class QExtMemoryTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void constructor();
};

class ArgsTest
{
public:
    ArgsTest() {}
    ArgsTest(int a1) {}
    ArgsTest(int a1, int a2) {}
    ArgsTest(int a1, int a2, int a3) {}
};


void QExtMemoryTest::constructor()
{
    {
        QExtSharedPointer<int> x{new int(1)};

        auto a1 = qextMakeShared<int>(1);
        auto t0 = qextMakeShared<ArgsTest>();
        auto t1 = qextMakeShared<ArgsTest>(1);
        auto t2 = qextMakeShared<ArgsTest>(2);
        auto t3 = qextMakeShared<ArgsTest>(3);
    }

    {
        QExtUniquePointer<int> x(new int(1));
        QExtUniquePointer<int[]> y(new int[4]{1,2,3,4});
        QExtUniquePointer<int[]> z(new int[100]{1,2,3,4});

        auto a = qextMakeUnique<int>(1);
        auto b = qextMakeUnique<int[]>(1,2,3,4);
        auto c = qextMakeUnique<int[100]>(1,2,3,4);
        auto d = qextMakeUnique<int[100]>();
        //auto e = std::make_unique<int[1]>(1,2,3,4); // static_assert

        c[90] = 9;
        d[90] = 9;

        std::cout << *a << std::endl;
        std::cout << b[0] << " " << b[1] << std::endl;
        std::cout << c[0] << " " << c[80] << " " << c[90] << std::endl;
        std::cout << d[0] << " " << d[80] << " " << d[90] << std::endl;
    }
}

QTEST_APPLESS_MAIN(QExtMemoryTest)

#include <tst_qextMemory.moc>
