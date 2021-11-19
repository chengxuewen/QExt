#ifndef _QEXTMVVMEXTERNALPROPERTY_H
#define _QEXTMVVMEXTERNALPROPERTY_H

#include <qextMvvmGlobal.h>

#include <QScopedPointer>
#include <QMetaType>
#include <QString>
#include <QColor>

//! Property to carry text, color and identifier.
//! Can be used to link items with each other.
class QEXTMvvmExternalPropertyPrivate;
class QEXT_MVVM_API QEXTMvvmExternalProperty
{
public:
    QEXTMvvmExternalProperty();
    QEXTMvvmExternalProperty(const QEXTMvvmExternalProperty &other);
    QEXTMvvmExternalProperty(const QString &text, const QColor &color, const QString &id = QString());
    virtual ~QEXTMvvmExternalProperty();

    bool isValid() const;

    QString text() const;
    QColor color() const;
    QString identifier() const;

    QEXTMvvmExternalProperty &operator=(const QEXTMvvmExternalProperty &other);
    bool operator==(const QEXTMvvmExternalProperty &other) const;
    bool operator!=(const QEXTMvvmExternalProperty &other) const;
    bool operator<(const QEXTMvvmExternalProperty &other) const;

    static QEXTMvvmExternalProperty undefined();

protected:
    QScopedPointer<QEXTMvvmExternalPropertyPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QEXTMvvmExternalProperty)
};

Q_DECLARE_METATYPE(QEXTMvvmExternalProperty)

#endif // _QEXTMVVMEXTERNALPROPERTY_H
