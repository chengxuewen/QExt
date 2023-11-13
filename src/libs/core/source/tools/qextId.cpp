#include "qextId.h"

#include <QByteArray>
#include <QDataStream>
#include <QHash>
#include <QDebug>
#include <QVariant>

#include <string.h>

class QEXTStringHolder
{
public:
    QEXTStringHolder() : n(0), str(0) {}

    QEXTStringHolder(const char *s, int length) : n(length), str(s)
    {
        if (!n) {
            length = n = static_cast<int>(strlen(s));
        }
        h = 0;
        while (length--) {
            h = (h << 4) + *s++;
            h ^= (h & 0xf0000000) >> 23;
            h &= 0x0fffffff;
        }
    }
    int n;
    const char *str;
    uint h;
};

static bool operator==(const QEXTStringHolder &sh1, const QEXTStringHolder &sh2)
{
    return sh1.h == sh2.h && sh1.str && sh2.str && strcmp(sh1.str, sh2.str) == 0;
}


static uint qHash(const QEXTStringHolder &sh)
{
    return sh.h;
}

struct QExtIdCache : public QHash<QEXTStringHolder, int>
{
    // dont allow static leaks
    ~QExtIdCache()
    {
        for (QExtIdCache::iterator it = begin(); it != end(); ++it) {
            delete[](const_cast<char *>(it.key().str));
        }
    }
};

static int firstUnusedId = 0;

static QHash<int, QEXTStringHolder> stringFromId;
static QExtIdCache idFromString;

static int theId(const char *str, int n = 0)
{
    if (QEXT_DECL_NULLPTR == str || !*str) {
        qCritical() << "theId():parameter str error!";
        return 0;
    }
    QEXTStringHolder sh(str, n);
    int res = idFromString.value(sh, -1);
    if (-1 == res) {
        res = firstUnusedId++;
        sh.str = qstrdup(sh.str);
        idFromString[sh] = res;
        stringFromId[res] = sh;
    }
    return res;
}

static int theId(const QByteArray &ba)
{
    return theId(ba.constData(), ba.size());
}


QExtId::QExtId()
{
    m_id = 0;
}

QExtId::QExtId(int id)
{
    m_id = id;
}

QExtId::QExtId(const char *name)
{
    m_id = theId(name, 0);
}

QExtId::QExtId(const QString &name)
{
    m_id = theId(name.toLatin1().data(), 0);
}

QByteArray QExtId::name() const
{
    return stringFromId.value(m_id).str;
}

QString QExtId::toString() const
{
    return QString::fromUtf8(stringFromId.value(m_id).str);
}

QExtId QExtId::fromString(const QString &string)
{
    return QExtId(theId(string.toUtf8()));
}

QExtId QExtId::fromName(const QByteArray &byteArray)
{
    return QExtId(theId(byteArray));
}

QVariant QExtId::toVariant() const
{
    return QVariant(QString::fromUtf8(stringFromId.value(m_id).str));
}

QExtId QExtId::fromVariant(const QVariant &variant)
{
    const QByteArray ba = variant.toString().toUtf8();
    if (ba.isEmpty()) {
        return QExtId();
    }
    return QExtId(theId(ba));
}

QExtId QExtId::withSuffix(int suffix) const
{
    const QByteArray byteArray = name() + QByteArray::number(suffix);
    return QExtId(byteArray.constData());
}

QExtId QExtId::withSuffix(const char *suffix) const
{
    const QByteArray ba = name() + suffix;
    return QExtId(ba.constData());
}

QExtId QExtId::withSuffix(const QString &suffix) const
{
    const QByteArray ba = name() + suffix.toUtf8();
    return QExtId(ba.constData());
}

QExtId QExtId::withPrefix(const char *prefix) const
{
    const QByteArray ba = prefix + name();
    return QExtId(ba.constData());
}

void QExtId::registerId(int id, const char *name)
{
    QEXTStringHolder sh(name, 0);
    idFromString[sh] = id;
    stringFromId[id] = sh;
}

bool QExtId::operator==(const char *name) const
{
    const char *string = stringFromId.value(m_id).str;
    if (string && name) {
        return strcmp(string, name) == 0;
    } else {
        return false;
    }
}

const char *nameForId(int id)
{
    return stringFromId.value(id).str;
}

bool QExtId::alphabeticallyBefore(QExtId other) const
{
    return toString().compare(other.toString(), Qt::CaseInsensitive) < 0;
}

QString QExtId::suffixAfter(QExtId baseId) const
{
    const QByteArray b = baseId.name();
    const QByteArray n = name();
    return n.startsWith(b) ? QString::fromUtf8(n.mid(b.size())) : QString();
}



QDataStream &operator<<(QDataStream &ds, const QExtId &id)
{
    return ds << id.name();
}

QDataStream &operator>>(QDataStream &ds, QExtId &id)
{
    QByteArray ba;
    ds >> ba;
    id = QExtId::fromName(ba);
    return ds;
}
