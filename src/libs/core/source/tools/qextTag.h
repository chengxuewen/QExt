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

    int id() const { return m_id; }
    bool isValid() const { return m_id; }

    bool operator==(const char *name) const;

    bool operator==(QExtTag tag) const { return m_id == tag.m_id; }

    bool operator!=(QExtTag tag) const { return m_id != tag.m_id; }

    bool operator!=(const char *name) const { return !operator==(name); }

    bool operator<(QExtTag tag) const { return m_id < tag.m_id; }

    bool operator>(QExtTag tag) const { return m_id > tag.m_id; }

    bool alphabeticallyBefore(QExtTag other) const;

    static QExtTag fromString(const QString &string);
    static QExtTag fromVariant(const QVariant &variant);
    static QExtTag fromName(const QByteArray &byteArray);
    static QExtTag fromId(int id) { return QExtTag(id); }
    static void registerId(int id, const char *name);

private:
    QExtTag(const QLatin1String &);
    int m_id;
};

inline uint qHash(const QExtTag &tag) { return tag.id(); }

QDataStream &operator<<(QDataStream &ds, const QExtTag &tag);
QDataStream &operator>>(QDataStream &ds, QExtTag &tag);

Q_DECLARE_METATYPE(QExtTag)
Q_DECLARE_METATYPE(QList<QExtTag>)

#endif // _QEXTTAG_H
