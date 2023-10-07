/**
 * @file main.cpp
 * \brief Main file.
 * @author Micha? Policht
 */
//! [0]
#include <qextSerialEnumerator.h>
//! [0]
#include <QtCore/QList>
#include <QtCore/QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
#include <QLoggingCategory>
#endif

int main()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 2, 0))
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
#endif
    //! [1]
    QList<QEXTPortInfo> ports = QEXTSerialEnumerator::portInfoList();
    //! [1]
    qDebug() << "List of ports:";
    //! [2]
    foreach (QEXTPortInfo info, ports) {
        qDebug() << "port name:"       << info.portName;
        qDebug() << "friendly name:"   << info.friendName;
        qDebug() << "physical name:"   << info.physName;
        qDebug() << "enumerator name:" << info.enumName;
        qDebug() << "vendor ID:"       << info.vendorID;
        qDebug() << "product ID:"      << info.productID;

        qDebug() << "===================================";
    }
    //! [2]
    return 0;
}

