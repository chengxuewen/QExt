#ifndef QEXTID_H
#define QEXTID_H

#include <qextglobal.h>

#include <QMetaType>
#include <QString>



class QEXT_CORE_API QEXTId
{
public:
    QEXTId();
    QEXTId(int id);
    QEXTId(const char *name);
    QEXTId(const QString &name);

    QEXTId withSuffix(int suffix) const;
    QEXTId withSuffix(const char *suffix) const;
    QEXTId withSuffix(const QString &suffix) const;
    QEXTId withPrefix(const char *prefix) const;

    QByteArray name() const;
    QString toString() const;
    QVariant toVariant() const;
    QString suffixAfter(QEXTId baseId) const;
    bool isValid() const { return m_id; }
    bool operator==(QEXTId id) const { return m_id == id.m_id; }
    bool operator==(const char *name) const;
    bool operator!=(QEXTId id) const { return m_id != id.m_id; }
    bool operator!=(const char *name) const { return !operator==(name); }
    bool operator<(QEXTId id) const { return m_id < id.m_id; }
    bool operator>(QEXTId id) const { return m_id > id.m_id; }
    bool alphabeticallyBefore(QEXTId other) const;
    int uniqueIdentifier() const { return m_id; }
    static QEXTId fromUniqueIdentifier(int id) { return QEXTId(id); }
    static QEXTId fromString(const QString &string);
    static QEXTId fromName(const QByteArray &byteArray);
    static QEXTId fromVariant(const QVariant &variant);
    static void registerId(int id, const char *name);

private:
    QEXTId(const QLatin1String &);
    int m_id;
};

inline uint qHash(const QEXTId &id) { return id.uniqueIdentifier(); }

QDataStream &operator<<(QDataStream &ds, const QEXTId &id);
QDataStream &operator>>(QDataStream &ds, QEXTId &id);



Q_DECLARE_METATYPE(QEXTId)
Q_DECLARE_METATYPE(QList<QEXTId>)

#endif // QEXTID_H
