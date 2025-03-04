#include <qextTagId.h>

#include <QHash>
#include <QDebug>
#include <QVariant>
#include <QAtomicInt>
#include <QByteArray>
#include <QDataStream>
#include <QGlobalStatic>

#include <string.h>

class QExtTagIdStringHolder
{
public:
    QExtTagIdStringHolder() : n(0), str(QEXT_NULLPTR) {}

    QExtTagIdStringHolder(const char *s, int length) : n(length), str(s)
    {
        if (!n)
        {
            length = n = static_cast<int>(strlen(s));
        }
        h = 0;
        while (length--)
        {
            h = (h << 4) + *s++;
            h ^= (h & 0xf0000000) >> 23;
            h &= 0x0fffffff;
        }
    }
    int n;
    uint h;
    const char *str;
};

static bool operator==(const QExtTagIdStringHolder &sh1, const QExtTagIdStringHolder &sh2)
{
    return sh1.h == sh2.h && sh1.str && sh2.str && strcmp(sh1.str, sh2.str) == 0;
}


static uint qHash(const QExtTagIdStringHolder &sh)
{
    return sh.h;
}

struct QExtTagIdCache : public QHash<QExtTagIdStringHolder, int>
{
    // dont allow static leaks
    ~QExtTagIdCache()
    {
        for (QExtTagIdCache::iterator it = begin(); it != end(); ++it)
        {
            delete[](const_cast<char *>(it.key().str));
        }
    }
};

namespace internal
{
typedef QHash<int, QExtTagIdStringHolder> IdStringHolderHash;
static inline QAtomicInt &firstUnusedId()
{
    static QAtomicInt id = 0;
    return id;
}
static inline IdStringHolderHash &stringFromId()
{
    static IdStringHolderHash hash;
    return hash;
}
static inline QExtTagIdCache &idFromString()
{
    static QExtTagIdCache cache;
    return cache;
}
static int theId(const char *str, int n = 0)
{
    if (QEXT_NULLPTR == str || !*str)
    {
        qCritical() << "theId():parameter str error!";
        return 0;
    }
    QExtTagIdStringHolder sh(str, n);
    int res = idFromString().value(sh, -1);
    if (-1 == res)
    {
        res = firstUnusedId().fetchAndAddOrdered(1);
        sh.str = qstrdup(sh.str);
        idFromString()[sh] = res;
        stringFromId()[res] = sh;
    }
    return res;
}
static int theId(const QByteArray &ba)
{
    return theId(ba.constData(), ba.size());
}
}


QExtTagId::QExtTagId()
{
    m_id = 0;
}

QExtTagId::QExtTagId(int id)
{
    m_id = id;
}

QExtTagId::QExtTagId(const char *name)
{
    m_id = internal::theId(name, 0);
}

QExtTagId::QExtTagId(const QString &name)
{
    m_id = internal::theId(name.toLatin1().data(), 0);
}

QByteArray QExtTagId::name() const
{
    return internal::stringFromId().value(m_id).str;
}

QString QExtTagId::toString() const
{
    return QString::fromUtf8(internal::stringFromId().value(m_id).str);
}

QExtTagId QExtTagId::fromString(const QString &string)
{
    return QExtTagId(internal::theId(string.toUtf8()));
}

QExtTagId QExtTagId::fromName(const QByteArray &byteArray)
{
    return QExtTagId(internal::theId(byteArray));
}

QVariant QExtTagId::toVariant() const
{
    return QVariant(QString::fromUtf8(internal::stringFromId().value(m_id).str));
}

QExtTagId QExtTagId::fromVariant(const QVariant &variant)
{
    const QByteArray ba = variant.toString().toUtf8();
    if (ba.isEmpty())
    {
        return QExtTagId();
    }
    return QExtTagId(internal::theId(ba));
}

QExtTagId QExtTagId::withSuffix(int suffix) const
{
    const QByteArray byteArray = name() + QByteArray::number(suffix);
    return QExtTagId(byteArray.constData());
}

QExtTagId QExtTagId::withSuffix(const char *suffix) const
{
    const QByteArray ba = name() + suffix;
    return QExtTagId(ba.constData());
}

QExtTagId QExtTagId::withSuffix(const QString &suffix) const
{
    const QByteArray ba = name() + suffix.toUtf8();
    return QExtTagId(ba.constData());
}

QExtTagId QExtTagId::withPrefix(const char *prefix) const
{
    const QByteArray ba = prefix + name();
    return QExtTagId(ba.constData());
}

void QExtTagId::registerId(int id, const char *name)
{
    QExtTagIdStringHolder sh(name, 0);
    internal::idFromString()[sh] = id;
    internal::stringFromId()[id] = sh;
}

bool QExtTagId::operator==(const char *name) const
{
    const char *string = internal::stringFromId().value(m_id).str;
    if (string && name)
    {
        return strcmp(string, name) == 0;
    }
    else
    {
        return false;
    }
}

const char *nameForId(int id)
{
    return internal::stringFromId().value(id).str;
}

bool QExtTagId::alphabeticallyBefore(QExtTagId other) const
{
    return toString().compare(other.toString(), Qt::CaseInsensitive) < 0;
}

QString QExtTagId::suffixAfter(QExtTagId baseId) const
{
    const QByteArray b = baseId.name();
    const QByteArray n = name();
    return n.startsWith(b) ? QString::fromUtf8(n.mid(b.size())) : QString();
}

QDataStream &operator<<(QDataStream &ds, const QExtTagId &tag)
{
    return ds << tag.name();
}

QDataStream &operator>>(QDataStream &ds, QExtTagId &tag)
{
    QByteArray ba;
    ds >> ba;
    tag = QExtTagId::fromName(ba);
    return ds;
}
