#ifndef _QEXTICONSRESOURCE_H
#define _QEXTICONSRESOURCE_H

#include <qextIconsGlobal.h>
#include <qextOnceFlag.h>

#include <QObject>
#include <QMetaEnum>

class QEXT_ICONS_API QExtIconsResource : public QObject
{
    Q_OBJECT
public:
    typedef QString (*iconNameTrimFunc)(const QString &);
    
    explicit QExtIconsResource(QObject *parent = QEXT_NULLPTR) : QObject{parent} {}

    virtual const char *iconStyle() const = 0;
    virtual QMetaEnum iconMetaEnum() const = 0;
    virtual QStringList iconNameList() const
    {
        if (m_iconsNameListOnceFlag.enter())
        {
            QMetaEnum metaEnum = this->iconMetaEnum();
            for (int i = 0; i < metaEnum.keyCount(); ++i)
            {
                QString iconName = metaEnum.valueToKey(metaEnum.value(i));
                m_iconsNameList.append(this->trimIconName(iconName));
            }
            m_iconsNameListOnceFlag.leave();
        }
        return m_iconsNameList;
    }
    virtual QString trimIconName(const QString &iconsName) const
    {
        const int index = iconsName.indexOf("_");
        return index >= 0 ? iconsName.mid(index + 1) : iconsName;
    };

    QString iconResource(const QString &iconName, bool isUrl = false) const
    {
        return QExtIconsResource::resource(this->iconStyle(), iconName, isUrl);
    }
    static inline QString resource(const QString &style, const QString &iconName, bool isUrl = false)
    {
        qextIconsInitResource();
        return QString("%1:/QExtIcons/%2/%3.svg").arg(isUrl ? "qrc" : "").arg(style).arg(iconName);
    }

    static inline void qextIconsInitResource();

private:
    mutable QStringList m_iconsNameList;
    mutable QExtOnceFlag m_iconsNameListOnceFlag;
};

#endif // _QEXTICONSRESOURCE_H
