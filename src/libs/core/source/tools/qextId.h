#ifndef _QEXTID_H
#define _QEXTID_H

#include <qextGlobal.h>

#include <QMetaType>
#include <QString>

class QEXT_CORE_API QExtId
{
public:
    QExtId();
    QExtId(int id);
    QExtId(const char *name);
    QExtId(const QString &name);

    QExtId withSuffix(int suffix) const;
    QExtId withSuffix(const char *suffix) const;
    QExtId withSuffix(const QString &suffix) const;
    QExtId withPrefix(const char *prefix) const;

    QByteArray name() const;
    QString toString() const;
    QVariant toVariant() const;
    QString suffixAfter(QExtId baseId) const;

    bool isValid() const { return m_id; }

    bool operator==(QExtId id) const { return m_id == id.m_id; }

    bool operator==(const char *name) const;

    bool operator!=(QExtId id) const { return m_id != id.m_id; }

    bool operator!=(const char *name) const { return !operator==(name); }

    bool operator<(QExtId id) const { return m_id < id.m_id; }

    bool operator>(QExtId id) const { return m_id > id.m_id; }

    bool alphabeticallyBefore(QExtId other) const;

    int uniqueIdentifier() const { return m_id; }

    static QExtId fromUniqueIdentifier(int id) { return QExtId(id); }

    static QExtId fromString(const QString &string);
    static QExtId fromName(const QByteArray &byteArray);
    static QExtId fromVariant(const QVariant &variant);
    static void registerId(int id, const char *name);

private:
    QExtId(const QLatin1String &);
    int m_id;
};

inline uint qHash(const QExtId &id) { return id.uniqueIdentifier(); }

QDataStream &operator<<(QDataStream &ds, const QExtId &id);
QDataStream &operator>>(QDataStream &ds, QExtId &id);

Q_DECLARE_METATYPE(QExtId)
Q_DECLARE_METATYPE(QList<QExtId>)

#endif // _QEXTID_H
