#include <qextQmlThemeJsonFileParser.h>
#include <qextQmlThemeConfig.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSharedPointer>

namespace internal
{
void retrievalProperty(QExtQmlThemeBinder *binder, QMap<QString, QVariant> &namePropertyMap, QString parentName = QString())
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
    QString dotString;
    QMap<QString, QVariant> bindingPropertyMap = binder->themeBindingPropertyMap();
    if (!bindingPropertyMap.isEmpty() && !parentName.isEmpty())
    {
        dotString = ".";
    }

    QMapIterator<QString, QVariant> mapIter(bindingPropertyMap);
    while (mapIter.hasNext())
    {
        mapIter.next();
        QString key = parentName + dotString + mapIter.key();
        QVariant value = mapIter.value();
        namePropertyMap.insert(key, value);
    }

    foreach (QExtQmlThemeBinder *pChild, binder->themeBinderChilds())
    {
        retrievalProperty(pChild, namePropertyMap, parentName);
    }

    return;
}

void writeBinderData(QExtQmlThemeBinder *binder, QJsonObject &jsonObject)
{
    //    qDebug() << "writeBinderData()-------------------------";
    if (nullptr == binder->themeBinderParent())
    {
        QJsonObject binderJsonObject;
        QString binderKey = QExtQmlThemeBinder::generateFieldKey(binder->className(), binder->groupName(), binder->stateName());
        if (jsonObject.contains(binderKey) && jsonObject[binderKey].isObject())
        {
            binderJsonObject = jsonObject[binderKey].toObject();
        }

        // get Low priority theme json obj
        QStringList allFieldKeys = QExtQmlThemeBinder::generateFieldKeyList(binder->className(), binder->groupName(), binder->stateName());
        QList<QJsonObject> listLowPriorityBinderJsonObject;
        for (int i = allFieldKeys.size() - 1; i > 0; --i)
        {
            QString key = allFieldKeys.at(i);
            if (key != binderKey)
            {
                if (jsonObject.contains(key))
                {
                    if (jsonObject[key].isObject())
                    {
                        listLowPriorityBinderJsonObject.append(jsonObject[key].toObject());
                    }
                }
            }
            else
            {
                break;
            }
        }

        // add property
        QMap<QString, QVariant> namePropertyMap;
        retrievalProperty(binder, namePropertyMap);
        if (!namePropertyMap.isEmpty())
        {
            QMapIterator<QString, QVariant> mapIter(namePropertyMap);
            while (mapIter.hasNext())
            {
                mapIter.next();
                QString key = mapIter.key();
                QVariant value = mapIter.value();
                if (key.contains(QExtQmlThemeConstant::kProperty))
                {
                    binderJsonObject[key] = QJsonValue(value.toString());
                }
                else
                {
                    binderJsonObject[key] = value.toJsonValue();
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
                    if ((*iter).contains(key))
                    {
                        if ((*iter).value(key) == value)
                        {
                            binderJsonObject.remove(key);
                            break;
                        }
                    }
                }
            }

            // add binder item
            jsonObject[binderKey] = binderJsonObject;
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
    if (themeJsonObject.contains(QExtQmlThemeConstant::kInfo) &&
        themeJsonObject[QExtQmlThemeConstant::kInfo].isObject())
    {
        QJsonObject jsonObjectInfo = themeJsonObject[QExtQmlThemeConstant::kInfo].toObject();
        QString version = jsonObjectInfo[QExtQmlThemeConstant::kInfoVersion].toString();
        QString about = jsonObjectInfo[QExtQmlThemeConstant::kInfoAbout].toString();
        QString name = jsonObjectInfo[QExtQmlThemeConstant::kInfoName].toString();
        QString author = jsonObjectInfo[QExtQmlThemeConstant::kInfoAuthor].toString();
        QVariantMap themeInfoMap;
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::kInfoVersion), version);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::kInfoAbout), about);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::kInfoName), name);
        themeInfoMap.insert(QLatin1String(QExtQmlThemeConstant::kInfoAuthor), author);
        themeDataMap.insert(QExtQmlThemeConstant::kInfo, themeInfoMap);

        QString nowVersion = QString("%1.%2").
                             arg(QExtQmlThemeConstant::kVersionMajor).
                             arg(QExtQmlThemeConstant::kVersionMinor);
        if (nowVersion != version)
        {
            error = QString("Theme file %1 version number %2 mismatch, valid version number is %3!")
            .arg(path).arg(version).arg(nowVersion);
        }
    }
    else
    {
        error = QString("Theme file %1 Format error, INFO not found!").arg(path);
        return false;
    }

    // parse ITEM data
    if (themeJsonObject.contains(QExtQmlThemeConstant::kTheme) &&
        themeJsonObject[QExtQmlThemeConstant::kTheme].isObject())
    {
        QJsonObject jsonObjectClass = themeJsonObject[QExtQmlThemeConstant::kTheme].toObject();
        QStringList listThemeFieldKey = jsonObjectClass.keys();
        QListIterator<QString> iter(listThemeFieldKey);
        while (iter.hasNext())
        {
            QString fieldKey = iter.next();
            QVariantMap mapField = themeDataMap.value(fieldKey);
            QJsonObject jsonObjectBinder = jsonObjectClass.value(fieldKey).toObject();
            QStringList propertyKeys = jsonObjectBinder.keys();
            foreach (QString key, propertyKeys)
            {
                mapField.insert(key, jsonObjectBinder.value(key).toVariant());
            }
            themeDataMap.insert(fieldKey, mapField);
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
    QJsonObject newThemeJsonObject = oldJsonObject[QExtQmlThemeConstant::kInfo].toObject();
    newInfoJsonObject[QExtQmlThemeConstant::kInfoVersion] = QString("%1.%2").
                                                            arg(QExtQmlThemeConstant::kVersionMajor).
                                                            arg(QExtQmlThemeConstant::kVersionMinor);
    newInfoJsonObject[QExtQmlThemeConstant::kInfoAbout] = QLatin1String("QExtQml theme template file");
    newInfoJsonObject[QExtQmlThemeConstant::kInfoName] = QLatin1String("Template");
    newInfoJsonObject[QExtQmlThemeConstant::kInfoAuthor] = QLatin1String("QExt");
    newJsonObject[QExtQmlThemeConstant::kInfo] = newInfoJsonObject;
    
    if (nullptr != binder)
    {
        internal::writeBinderData(binder, newThemeJsonObject);
    }
    else
    {
        foreach (QExtQmlThemeBinder *item, QExtQmlThemeBinder::allThemeBinders())
        {
            if (nullptr != item && nullptr == item->themeBinderParent() && item->isEnabled())
            {
                if (!item->className().isEmpty())
                {
                    if (item->childName().isEmpty())
                    {
                        internal::writeBinderData(item, newThemeJsonObject);
                    }
                }
            }
        }
    }
    newJsonObject[QExtQmlThemeConstant::kTheme] = newThemeJsonObject;

    QJsonDocument jsonSaveDoc(newJsonObject);
    file.resize(0);
    file.write(jsonSaveDoc.toJson());
    file.close();
    return true;
}
