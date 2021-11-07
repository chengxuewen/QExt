#ifndef _QEXTMVVMTAGINFO_H
#define _QEXTMVVMTAGINFO_H

#include <qextMvvmGlobal.h>

#include <QVector>
#include <QString>

//! Holds info about single tag for QEXTMvvmItem.
class QEXT_MVVM_API QEXTMvvmTagInfo
{
public:
    QEXTMvvmTagInfo();
    QEXTMvvmTagInfo(const QString &name, int min, int max, const QVector<QString> &modelTypes);

    //! Constructs universal tag intended for unlimited amount of various items.
    static QEXTMvvmTagInfo universalTag(const QString &name, const QVector<QString> &modelTypes = QVector<QString>());
    //! Constructs tag intended for single property.
    static QEXTMvvmTagInfo propertyTag(const QString &name, const QString &modelType);

    int min() const;

    int max() const;

    QString name() const;

    QVector<QString> modelTypes() const;

    bool maximumReached() const;

    bool isValidChild(const QString &child) const;

    bool isSinglePropertyTag() const;

    bool operator==(const QEXTMvvmTagInfo &other) const;
    bool operator!=(const QEXTMvvmTagInfo &other) const;

private:
    int m_min;
    int m_max;
    QString m_name;
    QVector<QString> m_modelTypes;
};


#endif // _QEXTMVVMTAGINFO_H
