#include "qextid.h"

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

struct QEXTIdCache : public QHash<QEXTStringHolder, int>
{
    // dont allow static leaks
    ~QEXTIdCache()
    {
        for (QEXTIdCache::iterator it = begin(); it != end(); ++it) {
            delete[](const_cast<char *>(it.key().str));
        }
    }
};

static int firstUnusedId = 0;

static QHash<int, QEXTStringHolder> stringFromId;
static QEXTIdCache idFromString;

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


QEXTId::QEXTId()
{
    m_id = 0;
}

QEXTId::QEXTId(int id)
{
    m_id = id;
}

QEXTId::QEXTId(const char *name)
{
    m_id = theId(name, 0);
}

QEXTId::QEXTId(const QString &name)
{
    m_id = theId(name.toLatin1().data(), 0);
}

QByteArray QEXTId::name() const
{
    return stringFromId.value(m_id).str;
}

QString QEXTId::toString() const
{
    return QString::fromUtf8(stringFromId.value(m_id).str);
}

QEXTId QEXTId::fromString(const QString &string)
{
    return QEXTId(theId(string.toUtf8()));
}

QEXTId QEXTId::fromName(const QByteArray &byteArray)
{
    return QEXTId(theId(byteArray));
}

QVariant QEXTId::toVariant() const
{
    return QVariant(QString::fromUtf8(stringFromId.value(m_id).str));
}

QEXTId QEXTId::fromVariant(const QVariant &variant)
{
    const QByteArray ba = variant.toString().toUtf8();
    if (ba.isEmpty()) {
        return QEXTId();
    }
    return QEXTId(theId(ba));
}

QEXTId QEXTId::withSuffix(int suffix) const
{
    const QByteArray byteArray = name() + QByteArray::number(suffix);
    return QEXTId(byteArray.constData());
}

QEXTId QEXTId::withSuffix(const char *suffix) const
{
    const QByteArray ba = name() + suffix;
    return QEXTId(ba.constData());
}

QEXTId QEXTId::withSuffix(const QString &suffix) const
{
    const QByteArray ba = name() + suffix.toUtf8();
    return QEXTId(ba.constData());
}

QEXTId QEXTId::withPrefix(const char *prefix) const
{
    const QByteArray ba = prefix + name();
    return QEXTId(ba.constData());
}

void QEXTId::registerId(int id, const char *name)
{
    QEXTStringHolder sh(name, 0);
    idFromString[sh] = id;
    stringFromId[id] = sh;
}

bool QEXTId::operator==(const char *name) const
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

bool QEXTId::alphabeticallyBefore(QEXTId other) const
{
    return toString().compare(other.toString(), Qt::CaseInsensitive) < 0;
}

QString QEXTId::suffixAfter(QEXTId baseId) const
{
    const QByteArray b = baseId.name();
    const QByteArray n = name();
    return n.startsWith(b) ? QString::fromUtf8(n.mid(b.size())) : QString();
}



QDataStream &operator<<(QDataStream &ds, const QEXTId &id)
{
    return ds << id.name();
}

QDataStream &operator>>(QDataStream &ds, QEXTId &id)
{
    QByteArray ba;
    ds >> ba;
    id = QEXTId::fromName(ba);
    return ds;
}
