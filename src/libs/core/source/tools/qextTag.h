#ifndef _QEXTTAG_H
#define _QEXTTAG_H

#include <qextGlobal.h>

#include <QMetaType>
#include <QString>

class QEXT_CORE_API QExtTag
{
public:
    QExtTag();
    QExtTag(int id);
    QExtTag(const char *name);
    QExtTag(const QString &name);

    QExtTag withSuffix(int suffix) const;
    QExtTag withSuffix(const char *suffix) const;
    QExtTag withSuffix(const QString &suffix) const;
    QExtTag withPrefix(const char *prefix) const;

    QByteArray name() const;
    QString toString() const;
    QVariant toVariant() const;
    QString suffixAfter(QExtTag baseId) const;

    bool isValid() const { return m_id; }

    bool operator==(QExtTag id) const { return m_id == id.m_id; }

    bool operator==(const char *name) const;

    bool operator!=(QExtTag id) const { return m_id != id.m_id; }

    bool operator!=(const char *name) const { return !operator==(name); }

    bool operator<(QExtTag id) const { return m_id < id.m_id; }

    bool operator>(QExtTag id) const { return m_id > id.m_id; }

    bool alphabeticallyBefore(QExtTag other) const;

    int uniqueIdentifier() const { return m_id; }

    static QExtTag fromUniqueIdentifier(int id) { return QExtTag(id); }

    static QExtTag fromString(const QString &string);
    static QExtTag fromName(const QByteArray &byteArray);
    static QExtTag fromVariant(const QVariant &variant);
    static void registerId(int id, const char *name);

private:
    QExtTag(const QLatin1String &);
    int m_id;
};

inline uint qHash(const QExtTag &id) { return id.uniqueIdentifier(); }

QDataStream &operator<<(QDataStream &ds, const QExtTag &id);
QDataStream &operator>>(QDataStream &ds, QExtTag &id);

Q_DECLARE_METATYPE(QExtTag)
Q_DECLARE_METATYPE(QList<QExtTag>)

#endif // _QEXTTAG_H
