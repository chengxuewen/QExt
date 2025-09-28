#include <qextQmlThemeJsonFileParser.h>
#include <qextQmlThemeConfig.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSharedPointer>

namespace internal
{
void retrievalProperty(QExtQmlThemeBinder *binder, QMap<QString, QVariant> &mapNameToProperty, QString parentName = QString())
{
    //    qDebug() << "retrievalProperty()-------------------------";
    if (binder->className().isEmpty())
    {
        return;
    }
    if (!binder->childName().isEmpty())
    {
        if (!parentName.isEmpty())
        {
            parentName += "." + binder->childName();
        }
        else
        {
            parentName = binder->childName();
        }
    }
    QString strDot;
    QMap<QString, QVariant> bindingPropertyMap = binder->themeBindingPropertyMap();
    if (!bindingPropertyMap.isEmpty() && !parentName.isEmpty())
    {
        strDot = ".";
    }

    QMapIterator<QString, QVariant> mapIter(bindingPropertyMap);
    while (mapIter.hasNext())
    {
        mapIter.next();
        QString strKey = parentName + strDot + mapIter.key();
        QVariant value = mapIter.value();
        mapNameToProperty.insert(strKey, value);
    }

    foreach (QExtQmlThemeBinder *pChild, binder->themeBinderChilds())
    {
        retrievalProperty(pChild, mapNameToProperty, parentName);
    }

    return;
}

void writeBinderData(QExtQmlThemeBinder *binder, QJsonObject &jsonObject)
{
    //    qDebug() << "writeBinderData()-------------------------";
    if (nullptr == binder->themeBinderParent())
    {
        QJsonObject binderJsonObject;
        QString strBinderKey = QExtQmlThemeBinder::generateFieldKey(binder->className(), binder->groupName(), binder->stateName());
        if (jsonObject.contains(strBinderKey) && jsonObject[strBinderKey].isObject())
        {
            binderJsonObject = jsonObject[strBinderKey].toObject();
        }

        // get Low priority theme json obj
        QStringList listAllFieldKey = QExtQmlThemeBinder::generateFieldKeyList(binder->className(), binder->groupName(), binder->stateName());
        QList<QJsonObject> listLowPriorityBinderJsonObject;
        for (int i = listAllFieldKey.size() - 1; i > 0; --i)
        {
            QString strKey = listAllFieldKey.at(i);
            if (strKey != strBinderKey)
            {
                if (jsonObject.contains(strKey))
                {
                    if (jsonObject[strKey].isObject())
                    {
                        listLowPriorityBinderJsonObject.append(jsonObject[strKey].toObject());
                    }
                }
            }
            else
            {
                break;
            }
        }

        // add property
        QMap<QString, QVariant> mapNameToProperty;
        retrievalProperty(binder, mapNameToProperty);
        if (!mapNameToProperty.isEmpty())
        {
            QMapIterator<QString, QVariant> mapIter(mapNameToProperty);
            while (mapIter.hasNext())
            {
                mapIter.next();
                QString strKey = mapIter.key();
                QVariant value = mapIter.value();
                if (strKey.contains(QExtQmlThemeConstant::THEME_PROPERTY_COLOR))
                {
                    binderJsonObject[strKey] = QJsonValue(value.toString());
                }
                else
                {
                    binderJsonObject[strKey] = value.toJsonValue();
                }

                // remove data equal to low priority theme binder json obj
                //                QListIterator<QJsonObject> iter(listLowPriorityBinderJsonObject);
                //                while (iter.hasNext()) {
                //                    QJsonObject jsonObject = iter.next();
                //                    if (jsonObject.contains(strKey)) {
                //                        if (jsonObject.value(strKey) == value) {
                //                            binderJsonObject.remove(strKey);
                //                            break;
                //                        }
                //                    }
                //                }
                QList<QJsonObject>::iterator iter;
                for (iter = listLowPriorityBinderJsonObject.begin(); iter != listLowPriorityBinderJsonObject.end(); ++iter)
                {
                    //                    QJsonObject jsonObject = *iter;
                    if ((*iter).contains(strKey))
                    {
                        if ((*iter).value(strKey) == value)
                        {
                            binderJsonObject.remove(strKey);
                            break;
                        }
                    }
                }
            }

            // add binder item
            jsonObject[strBinderKey] = binderJsonObject;
        }
    }
}
}

bool QExtQmlThemeJsonFileParser::parseThemeFile(const QString &path, QMap<QString, QVariantMap> &themeDataMap,
                                                QString &error)
{
    QFile themeFile(path);
    if (!themeFile.exists())
    {
        error = QString("Theme file %1 not exist!").arg(path);
        return false;
    }

    if (!themeFile.open(QIODevice::ReadOnly))
    {
        error = QString("Theme file %1 open failed!").arg(path);
        return false;
    }

    QByteArray themeData = themeFile.readAll();
    themeFile.close();

    QJsonDocument themeJsonDoc(QJsonDocument::fromJson(themeData));
    QJsonObject themeJsonObject = themeJsonDoc.object();

    // parse INFO data
    if (themeJsonObject.contains(QExtQmlThemeConstant::THEME_INFO_KEY) &&
        themeJsonObject[QExtQmlThemeConstant::THEME_INFO_KEY].isObject())
    {
        QJsonObject jsonObjectInfo = themeJsonObject[QExtQmlThemeConstant::THEME_INFO_KEY].toObject();
        QString strVersion = jsonObjectInfo[QExtQmlThemeConstant::THEME_INFO_VERSION_KEY].toString();
        QString strAbout = jsonObjectInfo[QExtQmlThemeConstant::THEME_INFO_ABOUT_KEY].toString();
        QString strName = jsonObjectInfo[QExtQmlThemeConstant::THEME_INFO_NAME_KEY].toString();
        QString strAuthor = jsonObjectInfo[QExtQmlThemeConstant::THEME_INFO_AUTHOR_KEY].toString();
        QVariantMap themeInfoMap;
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::THEME_INFO_VERSION_KEY), strVersion);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::THEME_INFO_ABOUT_KEY), strAbout);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::THEME_INFO_NAME_KEY), strName);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::THEME_INFO_AUTHOR_KEY), strAuthor);
        themeDataMap.insert(QExtQmlThemeConstant::THEME_INFO_KEY, themeInfoMap);

        QString libVersion = QString("%1.%2").
                             arg(QExtQmlThemeConstant::THEME_VERSION_MAJOR).
                             arg(QExtQmlThemeConstant::THEME_VERSION_MINOR);
        if (libVersion != strVersion)
        {
            error = QString("Theme file %1 version number %2 mismatch, valid version number is %3!")
            .arg(path).arg(strVersion).arg(libVersion);
        }
    }
    else
    {
        error = QString("Theme file %1 Format error, INFO not found!").arg(path);
        return false;
    }

    // parse ITEM data
    if (themeJsonObject.contains(QExtQmlThemeConstant::THEME_THEME_KEY) &&
        themeJsonObject[QExtQmlThemeConstant::THEME_THEME_KEY].isObject())
    {
        QJsonObject jsonObjectClass = themeJsonObject[QExtQmlThemeConstant::THEME_THEME_KEY].toObject();
        QStringList listThemeFieldKey = jsonObjectClass.keys();
        QListIterator<QString> iter(listThemeFieldKey);
        while (iter.hasNext())
        {
            QString strFieldKey = iter.next();
            QVariantMap mapField = themeDataMap.value(strFieldKey);
            QJsonObject jsonObjectBinder = jsonObjectClass.value(strFieldKey).toObject();
            QStringList listPropertyKey = jsonObjectBinder.keys();
            foreach (QString strPropertyKey, listPropertyKey)
            {
                mapField.insert(strPropertyKey, jsonObjectBinder.value(strPropertyKey).toVariant());
            }
            themeDataMap.insert(strFieldKey, mapField);
        }
    }
    else
    {
        error = QString("Theme file %1 Format error, ITEM not found!").arg(path);
        return false;
    }

    return true;
}

bool QExtQmlThemeJsonFileParser::generateThemeTemplateFile(QString &error, QExtQmlThemeBinder *binder)
{
    //    qDebug() << "TThemeJsonFileParser::generateThemeTemplateFile()------------------------";
    QFile file(QStringLiteral("themeTemplate.json"));
    if (!file.open(QIODevice::ReadWrite))
    {
        error = QString("themeTemplate.json file open failed!");
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonReadDoc(QJsonDocument::fromJson(fileData));
    QJsonObject oldJsonObject = jsonReadDoc.object();

    QJsonObject newJsonObject;
    QJsonObject newInfoJsonObject;
    QJsonObject newThemeJsonObject = oldJsonObject[QExtQmlThemeConstant::THEME_THEME_KEY].toObject();
    newInfoJsonObject[QExtQmlThemeConstant::THEME_INFO_VERSION_KEY] = QString("%1.%2").
                                                                      arg(QExtQmlThemeConstant::THEME_VERSION_MAJOR).
                                                                      arg(QExtQmlThemeConstant::THEME_VERSION_MINOR);
    newInfoJsonObject[QExtQmlThemeConstant::THEME_INFO_ABOUT_KEY] = QLatin1String("QExtQml theme template file");
    newInfoJsonObject[QExtQmlThemeConstant::THEME_INFO_NAME_KEY] = QLatin1String("Template");
    newInfoJsonObject[QExtQmlThemeConstant::THEME_INFO_AUTHOR_KEY] = QLatin1String("QExt");
    newJsonObject[QExtQmlThemeConstant::THEME_INFO_KEY] = newInfoJsonObject;
    
    if (nullptr != binder)
    {
        internal::writeBinderData(binder, newThemeJsonObject);
    }
    else
    {
        foreach (QExtQmlThemeBinder *pBinderItem, QExtQmlThemeBinder::allThemeBinders())
        {
            if (nullptr != pBinderItem && nullptr == pBinderItem->themeBinderParent() && pBinderItem->isEnabled())
            {
                if (!pBinderItem->className().isEmpty())
                {
                    if (pBinderItem->childName().isEmpty())
                    {
                        internal::writeBinderData(pBinderItem, newThemeJsonObject);
                    }
                }
            }
        }
    }
    newJsonObject[QExtQmlThemeConstant::THEME_THEME_KEY] = newThemeJsonObject;

    QJsonDocument jsonSaveDoc(newJsonObject);
    file.resize(0);
    file.write(jsonSaveDoc.toJson());
    file.close();
    return true;
}
