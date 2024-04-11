#include <qextTag.h>

#include <QHash>
#include <QDebug>
#include <QVariant>
#include <QByteArray>
#include <QDataStream>
#include <QGlobalStatic>

#include <string.h>

class QExtTagStringHolder
{
public:
    QExtTagStringHolder() : n(0), str(QEXT_NULLPTR) {}

    QExtTagStringHolder(const char *s, int length) : n(length), str(s)
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

static bool operator==(const QExtTagStringHolder &sh1, const QExtTagStringHolder &sh2)
{
    return sh1.h == sh2.h && sh1.str && sh2.str && strcmp(sh1.str, sh2.str) == 0;
}


static uint qHash(const QExtTagStringHolder &sh)
{
    return sh.h;
}

struct QExtTagCache : public QHash<QExtTagStringHolder, int>
{
    // dont allow static leaks
    ~QExtTagCache()
    {
        for (QExtTagCache::iterator it = begin(); it != end(); ++it)
        {
            delete[](const_cast<char *>(it.key().str));
        }
    }
};

typedef QHash<int, QExtTagStringHolder> IdStringHolderHash;
Q_GLOBAL_STATIC(IdStringHolderHash, stringFromId)
Q_GLOBAL_STATIC(QExtTagCache, idFromString)
static int firstUnusedId = 0;

static int theId(const char *str, int n = 0)
{
    if (QEXT_NULLPTR == str || !*str)
    {
        qCritical() << "theId():parameter str error!";
        return 0;
    }
    QExtTagStringHolder sh(str, n);
    int res = idFromString()->value(sh, -1);
    if (-1 == res)
    {
        res = firstUnusedId++;
        sh.str = qstrdup(sh.str);
        (*idFromString())[sh] = res;
        (*stringFromId())[res] = sh;
    }
    return res;
}

static int theId(const QByteArray &ba)
{
    return theId(ba.constData(), ba.size());
}


QExtTag::QExtTag()
{
    m_id = 0;
}

QExtTag::QExtTag(int id)
{
    m_id = id;
}

QExtTag::QExtTag(const char *name)
{
    m_id = theId(name, 0);
}

QExtTag::QExtTag(const QString &name)
{
    m_id = theId(name.toLatin1().data(), 0);
}

QByteArray QExtTag::name() const
{
    return stringFromId()->value(m_id).str;
}

QString QExtTag::toString() const
{
    return QString::fromUtf8(stringFromId()->value(m_id).str);
}

QExtTag QExtTag::fromString(const QString &string)
{
    return QExtTag(theId(string.toUtf8()));
}

QExtTag QExtTag::fromName(const QByteArray &byteArray)
{
    return QExtTag(theId(byteArray));
}

QVariant QExtTag::toVariant() const
{
    return QVariant(QString::fromUtf8(stringFromId()->value(m_id).str));
}

QExtTag QExtTag::fromVariant(const QVariant &variant)
{
    const QByteArray ba = variant.toString().toUtf8();
    if (ba.isEmpty())
    {
        return QExtTag();
    }
    return QExtTag(theId(ba));
}

QExtTag QExtTag::withSuffix(int suffix) const
{
    const QByteArray byteArray = name() + QByteArray::number(suffix);
    return QExtTag(byteArray.constData());
}

QExtTag QExtTag::withSuffix(const char *suffix) const
{
    const QByteArray ba = name() + suffix;
    return QExtTag(ba.constData());
}

QExtTag QExtTag::withSuffix(const QString &suffix) const
{
    const QByteArray ba = name() + suffix.toUtf8();
    return QExtTag(ba.constData());
}

QExtTag QExtTag::withPrefix(const char *prefix) const
{
    const QByteArray ba = prefix + name();
    return QExtTag(ba.constData());
}

void QExtTag::registerId(int id, const char *name)
{
    QExtTagStringHolder sh(name, 0);
    (*idFromString())[sh] = id;
    (*stringFromId())[id] = sh;
}

bool QExtTag::operator==(const char *name) const
{
    const char *string = stringFromId()->value(m_id).str;
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
    return stringFromId()->value(id).str;
}

bool QExtTag::alphabeticallyBefore(QExtTag other) const
{
    return toString().compare(other.toString(), Qt::CaseInsensitive) < 0;
}

QString QExtTag::suffixAfter(QExtTag baseId) const
{
    const QByteArray b = baseId.name();
    const QByteArray n = name();
    return n.startsWith(b) ? QString::fromUtf8(n.mid(b.size())) : QString();
}

QDataStream &operator<<(QDataStream &ds, const QExtTag &tag)
{
    return ds << tag.name();
}

QDataStream &operator>>(QDataStream &ds, QExtTag &tag)
{
    QByteArray ba;
    ds >> ba;
    tag = QExtTag::fromName(ba);
    return ds;
}
