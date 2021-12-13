#include <qextQmlThemeJsonFileParser.h>
#include <qextQmlThemeConfig.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSharedPointer>

void retrievalProperty(QEXTQmlThemeBinder *pBinder, QMap<QString, QVariant> &mapNameToProperty, QString strParentName = QString())
{
    //    qDebug() << "retrievalProperty()-------------------------";
    if (pBinder->className().isEmpty())
    {
        return;
    }
    if (!pBinder->childName().isEmpty())
    {
        if (!strParentName.isEmpty())
        {
            strParentName += "." + pBinder->childName();
        }
        else
        {
            strParentName = pBinder->childName();
        }
    }
    QString strDot;
    QMap<QString, QVariant> bindingPropertyMap = pBinder->themeBindingPropertyMap();
    if (!bindingPropertyMap.isEmpty() && !strParentName.isEmpty())
    {
        strDot = ".";
    }

    QMapIterator<QString, QVariant> mapIter(bindingPropertyMap);
    while (mapIter.hasNext())
    {
        mapIter.next();
        QString strKey = strParentName + strDot + mapIter.key();
        QVariant value = mapIter.value();
        mapNameToProperty.insert(strKey, value);
    }

    foreach (QEXTQmlThemeBinder *pChild, pBinder->themeBinderChilds())
    {
        retrievalProperty(pChild, mapNameToProperty, strParentName);
    }

    return;
}

void writeBinderData(QEXTQmlThemeBinder *pBinder, QJsonObject &jsonObject)
{
    //    qDebug() << "writeBinderData()-------------------------";
    if (nullptr == pBinder->themeBinderParent())
    {
        QJsonObject binderJsonObject;
        QString strBinderKey = QEXTQmlThemeBinder::generateFieldKey(pBinder->className(), pBinder->groupName(), pBinder->stateName());
        if (jsonObject.contains(strBinderKey) && jsonObject[strBinderKey].isObject())
        {
            binderJsonObject = jsonObject[strBinderKey].toObject();
        }

        // get Low priority theme json obj
        QStringList listAllFieldKey = QEXTQmlThemeBinder::generateFieldKeyList(pBinder->className(), pBinder->groupName(), pBinder->stateName());
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
        retrievalProperty(pBinder, mapNameToProperty);
        if (!mapNameToProperty.isEmpty())
        {
            QMapIterator<QString, QVariant> mapIter(mapNameToProperty);
            while (mapIter.hasNext())
            {
                mapIter.next();
                QString strKey = mapIter.key();
                QVariant value = mapIter.value();
                if (strKey.contains(QEXTQmlThemeConstant::THEME_PROPERTY_COLOR))
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

bool QEXTQmlThemeJsonFileParser::parseThemeFile(const QString &strPath, QMap<QString, QVariantMap> &themeDataMap, QString &strError)
{
    QFile themeFile(strPath);
    if (!themeFile.exists())
    {
        strError = QString("Theme file %1 not exist!").arg(strPath);
        return false;
    }

    if (!themeFile.open(QIODevice::ReadOnly))
    {
        strError = QString("Theme file %1 open failed!").arg(strPath);
        return false;
    }

    QByteArray themeData = themeFile.readAll();
    themeFile.close();

    QJsonDocument themeJsonDoc(QJsonDocument::fromJson(themeData));
    QJsonObject themeJsonObject = themeJsonDoc.object();

    // parse INFO data
    if (themeJsonObject.contains(QEXTQmlThemeConstant::THEME_INFO_KEY) && themeJsonObject[QEXTQmlThemeConstant::THEME_INFO_KEY].isObject())
    {
        QJsonObject jsonObjectInfo = themeJsonObject[QEXTQmlThemeConstant::THEME_INFO_KEY].toObject();
        QString strVersion = jsonObjectInfo[QEXTQmlThemeConstant::THEME_INFO_VERSION_KEY].toString();
        QString strAbout = jsonObjectInfo[QEXTQmlThemeConstant::THEME_INFO_ABOUT_KEY].toString();
        QString strName = jsonObjectInfo[QEXTQmlThemeConstant::THEME_INFO_NAME_KEY].toString();
        QString strAuthor = jsonObjectInfo[QEXTQmlThemeConstant::THEME_INFO_AUTHOR_KEY].toString();
        QVariantMap themeInfoMap;
        themeInfoMap.insert(QLatin1String(QEXTQmlThemeConstant::THEME_INFO_VERSION_KEY), strVersion);
        themeInfoMap.insert(QLatin1String(QEXTQmlThemeConstant::THEME_INFO_ABOUT_KEY), strAbout);
        themeInfoMap.insert(QLatin1String(QEXTQmlThemeConstant::THEME_INFO_NAME_KEY), strName);
        themeInfoMap.insert(QLatin1String(QEXTQmlThemeConstant::THEME_INFO_AUTHOR_KEY), strAuthor);
        themeDataMap.insert(QEXTQmlThemeConstant::THEME_INFO_KEY, themeInfoMap);

        QString libVersion = QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
        if (libVersion != strVersion)
        {
            strError = QString("Theme file %1 version number %2 mismatch, valid version number is %3!")
                       .arg(strPath).arg(strVersion).arg(libVersion);
        }
    }
    else
    {
        strError = QString("Theme file %1 Format error, INFO not found!").arg(strPath);
        return false;
    }

    // parse ITEM data
    if (themeJsonObject.contains(QEXTQmlThemeConstant::THEME_THEME_KEY) && themeJsonObject[QEXTQmlThemeConstant::THEME_THEME_KEY].isObject())
    {
        QJsonObject jsonObjectClass = themeJsonObject[QEXTQmlThemeConstant::THEME_THEME_KEY].toObject();
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
        strError = QString("Theme file %1 Format error, ITEM not found!").arg(strPath);
        return false;
    }

    return true;
}

bool QEXTQmlThemeJsonFileParser::generateThemeTemplateFile(QString &strError, QEXTQmlThemeBinder *pBinder)
{
    //    qDebug() << "TThemeJsonFileParser::generateThemeTemplateFile()------------------------";
    QFile file(QStringLiteral("themeTemplate.json"));
    if (!file.open(QIODevice::ReadWrite))
    {
        strError = QString("themeTemplate.json file open failed!");
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonReadDoc(QJsonDocument::fromJson(fileData));
    QJsonObject oldJsonObject = jsonReadDoc.object();

    QJsonObject newJsonObject;
    QJsonObject newInfoJsonObject;
    QJsonObject newThemeJsonObject = oldJsonObject[QEXTQmlThemeConstant::THEME_THEME_KEY].toObject();
    newInfoJsonObject[QEXTQmlThemeConstant::THEME_INFO_VERSION_KEY] = QString("%1.%2").arg(QEXT_QML_PLUGIN_VERSION_MAJOR).arg(QEXT_QML_PLUGIN_VERSION_MINOR);
    newInfoJsonObject[QEXTQmlThemeConstant::THEME_INFO_ABOUT_KEY] = QLatin1String("TQuick theme template file");
    newInfoJsonObject[QEXTQmlThemeConstant::THEME_INFO_NAME_KEY] = QLatin1String("Template");
    newInfoJsonObject[QEXTQmlThemeConstant::THEME_INFO_AUTHOR_KEY] = QLatin1String("TQuick");
    newJsonObject[QEXTQmlThemeConstant::THEME_INFO_KEY] = newInfoJsonObject;

    if (nullptr != pBinder)
    {
        writeBinderData(pBinder, newThemeJsonObject);
    }
    else
    {
        foreach (QEXTQmlThemeBinder *pBinderItem, QEXTQmlThemeBinder::allThemeBinders())
        {
            if (nullptr != pBinderItem && nullptr == pBinderItem->themeBinderParent() && pBinderItem->isEnabled())
            {
                if (!pBinderItem->className().isEmpty())
                {
                    if (pBinderItem->childName().isEmpty())
                    {
                        writeBinderData(pBinderItem, newThemeJsonObject);
                    }
                }
            }
        }
    }
    newJsonObject[QEXTQmlThemeConstant::THEME_THEME_KEY] = newThemeJsonObject;

    QJsonDocument jsonSaveDoc(newJsonObject);
    file.resize(0);
    file.write(jsonSaveDoc.toJson());
    file.close();
    return true;
}
