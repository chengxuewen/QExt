#ifndef QEXTMVVMTAGINFO_H
#define QEXTMVVMTAGINFO_H

#include <qextmvvmglobal.h>

#include <QList>
#include <QString>



class QEXT_MVVM_API QEXTMvvmTagInfo
{
public:
    QEXTMvvmTagInfo();
    QEXTMvvmTagInfo(const QString &name, int min, int max, const QList<QString> &modelTypes);

    //! Constructs universal tag intended for unlimited amount of various items.
    static QEXTMvvmTagInfo universalTag(const QString &name, const QList<QString> &modelTypes = {});
    //! Constructs tag intended for single property.
    static QEXTMvvmTagInfo propertyTag(const QString &name, const QString &modelType);

    QString name() const;

    int min() const;
    int max() const;

    QList<QString> modelTypes() const;

    bool isValidChild(const QString &child) const;
    bool isSinglePropertyTag() const;

    bool operator==(const QEXTMvvmTagInfo &other) const;
    bool operator!=(const QEXTMvvmTagInfo &other) const;

private:
    QString m_name;
    int m_min;
    int m_max;
    QList<QString> m_modelTypes;
};



#endif // QEXTMVVMTAGINFO_H
