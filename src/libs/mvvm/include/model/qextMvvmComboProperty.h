#ifndef _QEXTMVVMCOMBOPROPERTY_H
#define _QEXTMVVMCOMBOPROPERTY_H

#include <qextMvvmGlobal.h>

#include <QVariant>
#include <QString>
#include <QVector>

//! Custom property to define list of string values with multiple selections.

class QEXTMvvmComboPropertyPrivate;
class QEXT_MVVM_API QEXTMvvmComboProperty
{
public:
    QEXTMvvmComboProperty();
    QEXTMvvmComboProperty(const QEXTMvvmComboProperty &other);
    virtual ~QEXTMvvmComboProperty();

    QString value() const;
    void setValue(const QString &name);

    QVector<QString> values() const;
    void setValues(const QVector<QString> &values);

    QVector<QString> toolTips() const;
    void setToolTips(const QVector<QString> &tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QEXTMvvmComboProperty &operator<<(const QString &string);
    QEXTMvvmComboProperty &operator<<(const QVector<QString> &string);
    QEXTMvvmComboProperty &operator=(const QEXTMvvmComboProperty &other);
    bool operator==(const QEXTMvvmComboProperty &other) const;
    bool operator!=(const QEXTMvvmComboProperty &other) const;
    bool operator<(const QEXTMvvmComboProperty &other) const;

    QString stringOfValues() const;
    void setStringOfValues(const QString& values);

    QVector<int> selectedIndices() const;
    QVector<QString> selectedValues() const;

    void setSelected(int index, bool value = true);
    void setSelected(const QString &name, bool value = true);

    QString stringOfSelections() const;
    void setStringOfSelections(const QString& values);

    QString label() const;

    static QEXTMvvmComboProperty createFrom(const QVector<QString> &values, const QString &currentValue = QString());

protected:
    QEXTMvvmComboProperty(QVector<QString> values);

    QScopedPointer<QEXTMvvmComboPropertyPrivate> d_ptr;

private:
    QEXT_DECL_PRIVATE(QEXTMvvmComboProperty)
};

Q_DECLARE_METATYPE(QEXTMvvmComboProperty)

#endif // _QEXTMVVMCOMBOPROPERTY_H
