#ifndef QEXTNETWORKUTILS_H
#define QEXTNETWORKUTILS_H

#include <qextglobal.h>

#include <qextutilsglobal.h>

#include <QObject>



class QEXT_UTILS_API QEXTNetworkUtils
{
public:
    QEXTNetworkUtils();

    static QByteArray qint16HostToNet(qint16 src);
    static QByteArray quint16HostToNet(quint16 src);
    static QByteArray qint32HostToNet(qint32 src);
    static QByteArray quint32HostToNet(quint32 src);
    static QByteArray qint64HostToNet(qint64 src);
    static QByteArray quint64HostToNet(quint64 src);

    static void qint16HostToNet(qint16 src, char *des);
    static void quint16HostToNet(quint16 src, char *des);
    static void qint32HostToNet(qint32 src, char *des);
    static void quint32HostToNet(quint32 src, char *des);
    static void qint64HostToNet(qint64 src, char *des);
    static void quint64HostToNet(quint64 src, char *des);

    static qint16 qint16NetToHost(QByteArray src);
    static quint16 quint16NetToHost(QByteArray src);
    static qint32 qint32NetToHost(QByteArray src);
    static quint32 quint32NetToHost(QByteArray src);
    static qint64 qint64NetToHost(QByteArray src);
    static quint64 quint64NetToHost(QByteArray src);

    static qint16 qint16NetToHost(char *src);
    static quint16 quint16NetToHost(char *src);
    static qint32 qint32NetToHost(char *src);
    static quint32 quint32NetToHost(char *src);
    static qint64 qint64NetToHost(char *src);
    static quint64 quint64NetToHost(char *src);

    static void qint16NetToHost(const char *src, qint16 *des);
    static void quint16NetToHost(const char *src, quint16 *des);
    static void qint32NetToHost(const char *src, qint32 *des);
    static void quint32NetToHost(const char *src, quint32 *des);
    static void qint64NetToHost(const char *src, qint64 *des);
    static void quint64NetToHost(const char *src, quint64 *des);

    static void setBitValue(char *c, int bit, int value);
    static void setBit(char *c, int bit);
    static void clearBit(char *c, int bit);
    static bool testBit(char c, int bit);

    static QString charToBinaryString(char c);
    static QString qint8ToBinaryString(qint8 src);
    static QString quint8ToBinaryString(quint8 src);
    static QString qint16ToBinaryString(qint16 src);
    static QString quint16ToBinaryString(quint16 src);
    static QString qint32ToBinaryString(qint32 src);
    static QString quint32ToBinaryString(quint32 src);
    static QString qint64ToBinaryString(qint64 src);
    static QString quint64ToBinaryString(quint64 src);
    static QString byteArrayToBinaryString(QByteArray src);
};



#endif // QEXTNETWORKUTILS_H
