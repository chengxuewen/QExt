#ifndef _QEXTTAGID_H
#define _QEXTTAGID_H

#include <qextGlobal.h>

#include <QMetaType>
#include <QString>

class QEXT_CORE_API QExtTagId
{
public:
    QExtTagId();
    QExtTagId(int id);
    QExtTagId(const char *name);
    QExtTagId(const QString &name);

    QExtTagId withSuffix(int suffix) const;
    QExtTagId withSuffix(const char *suffix) const;
    QExtTagId withSuffix(const QString &suffix) const;
    QExtTagId withPrefix(const char *prefix) const;

    QByteArray name() const;
    QString toString() const;
    QVariant toVariant() const;
    QString suffixAfter(QExtTagId baseId) const;

    int id() const { return m_id; }
    bool isValid() const { return m_id; }

    bool operator==(const char *name) const;

    bool operator==(QExtTagId tag) const { return m_id == tag.m_id; }

    bool operator!=(QExtTagId tag) const { return m_id != tag.m_id; }

    bool operator!=(const char *name) const { return !operator==(name); }

    bool operator<(QExtTagId tag) const { return m_id < tag.m_id; }

    bool operator>(QExtTagId tag) const { return m_id > tag.m_id; }

    bool alphabeticallyBefore(QExtTagId other) const;

    static QExtTagId fromString(const QString &string);
    static QExtTagId fromVariant(const QVariant &variant);
    static QExtTagId fromName(const QByteArray &byteArray);
    static QExtTagId fromId(int id) { return QExtTagId(id); }
    static void registerId(int id, const char *name);

private:
    QExtTagId(const QLatin1String &);
    int m_id;
};

inline uint qHash(const QExtTagId &tag) { return tag.id(); }

QDataStream &operator<<(QDataStream &ds, const QExtTagId &tag);
QDataStream &operator>>(QDataStream &ds, QExtTagId &tag);

Q_DECLARE_METATYPE(QExtTagId)
Q_DECLARE_METATYPE(QList<QExtTagId>)

#endif // _QEXTTAGID_H
