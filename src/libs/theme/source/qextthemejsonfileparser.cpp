/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#include "qextthemejsonfileparser.h"

#include <QFile>
#include <QSharedPointer>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

void retrievalProperty(QEXTThemeBinder *binder, QMap<QString, QVariant> &namePropertyMap, QString parentName = QString())
{
    //    qDebug() << "retrievalProperty()-------------------------";
    if (binder->className().isEmpty()) {
        return;
    }
    if (!binder->childName().isEmpty()) {
        if (!parentName.isEmpty()) {
            parentName += "." + binder->childName();
        } else {
            parentName = binder->childName();
        }
    }
    QString dotString;
    QMap<QString, QVariant> bindingPropertyMap = binder->bindingPropertyMap();
    if (!bindingPropertyMap.isEmpty() && !parentName.isEmpty()) {
        dotString = ".";
    }

    QMapIterator<QString, QVariant> iter(bindingPropertyMap);
    while (iter.hasNext()) {
        iter.next();
        QString key = parentName + dotString + iter.key();
        QVariant value = iter.value();
        namePropertyMap.insert(key, value);
    }

    foreach (QEXTThemeBinder *child, binder->childsList()) {
        retrievalProperty(child, namePropertyMap, parentName);
    }

    return;
}

void writeBinderData(QEXTThemeBinder *binder, QJsonObject &jsonObject) {
    //    qDebug() << "writeBinderData()-------------------------";
    if (nullptr == binder->parent()) {
        QJsonObject binderJsonObject;
        QString binderKey = QEXTThemeBinder::generateFieldKey(binder->className(), binder->groupName(), binder->stateName());
        if (jsonObject.contains(binderKey) && jsonObject[binderKey].isObject()) {
            binderJsonObject = jsonObject[binderKey].toObject();
        }

        // get Low priority theme json obj
        QStringList allFieldKeyList = QEXTThemeBinder::generateFieldKeyList(binder->className(), binder->groupName(), binder->stateName());
        QList<QJsonObject> lowPriorityBinderJsonObjectList;
        for (int i = allFieldKeyList.size() - 1; i > 0; --i) {
            QString key = allFieldKeyList.at(i);
            if (key != binderKey) {
                if (jsonObject.contains(key)) {
                    if (jsonObject[key].isObject()) {
                        lowPriorityBinderJsonObjectList.append(jsonObject[key].toObject());
                    }
                }
            } else {
                break;
            }
        }

        // add property
        QMap<QString, QVariant> namePropertyMap;
        retrievalProperty(binder, namePropertyMap);
        if (!namePropertyMap.isEmpty()) {
            QMapIterator<QString, QVariant> iter(namePropertyMap);
            while (iter.hasNext()) {
                iter.next();
                QString key = iter.key();
                QVariant value = iter.value();
                if (key.contains(QEXTThemeConstant::THEME_PROPERTY_COLOR)) {
                    binderJsonObject[key] = QJsonValue(value.toString());
                } else {
                    binderJsonObject[key] = value.toJsonValue();
                }

                // remove data equal to low priority theme binder json obj
                foreach (QJsonObject lowBinderJsonObject, lowPriorityBinderJsonObjectList) {
                    if (lowBinderJsonObject.contains(key)) {
                        if (lowBinderJsonObject.value(key) == value) {
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

bool QEXTThemeJsonFileParser::parseThemeFile(const QString &path, QMap<QString, QVariantMap> &themeDataMap, QString &error)
{
    QFile themeFile(path);
    if (!themeFile.exists()) {
        error = QString("Theme file %1 not exist!").arg(path);
        return false;
    }

    if (!themeFile.open(QIODevice::ReadOnly)) {
        error = QString("Theme file %1 open failed!").arg(path);
        return false;
    }

    QByteArray themeData = themeFile.readAll();
    themeFile.close();

    QJsonDocument themeJsonDoc(QJsonDocument::fromJson(themeData));
    QJsonObject themeJsonObject = themeJsonDoc.object();

    // parse INFO data
    if (themeJsonObject.contains(QEXTThemeConstant::THEME_INFO_KEY) && themeJsonObject[QEXTThemeConstant::THEME_INFO_KEY].isObject()) {
        QJsonObject jsonObjectInfo = themeJsonObject[QEXTThemeConstant::THEME_INFO_KEY].toObject();
        QString themeVersion = jsonObjectInfo[QEXTThemeConstant::THEME_INFO_VERSION_KEY].toString();
        QString strAbout = jsonObjectInfo[QEXTThemeConstant::THEME_INFO_ABOUT_KEY].toString();
        QString strName = jsonObjectInfo[QEXTThemeConstant::THEME_INFO_NAME_KEY].toString();
        QString strAuthor = jsonObjectInfo[QEXTThemeConstant::THEME_INFO_AUTHOR_KEY].toString();
        QVariantMap themeInfoMap;
        themeInfoMap.insert(QLatin1String(QEXTThemeConstant::THEME_INFO_VERSION_KEY), themeVersion);
        themeInfoMap.insert(QLatin1String(QEXTThemeConstant::THEME_INFO_ABOUT_KEY), strAbout);
        themeInfoMap.insert(QLatin1String(QEXTThemeConstant::THEME_INFO_NAME_KEY), strName);
        themeInfoMap.insert(QLatin1String(QEXTThemeConstant::THEME_INFO_AUTHOR_KEY), strAuthor);
        themeDataMap.insert(QEXTThemeConstant::THEME_INFO_KEY, themeInfoMap);

        if (QLatin1String(QEXTThemeConstant::THEME_VERSION) != themeVersion) {
            error = QString("Theme file %1 version number %2 mismatch, valid version number is %3!")
                           .arg(path).arg(themeVersion).arg(QLatin1String(QEXTThemeConstant::THEME_VERSION));
        }
    } else {
        error = QString("Theme file %1 Format error, INFO not found!").arg(path);
        return false;
    }

    // parse ITEM data
    if (themeJsonObject.contains(QEXTThemeConstant::THEME_THEME_KEY) && themeJsonObject[QEXTThemeConstant::THEME_THEME_KEY].isObject()) {
        QJsonObject jsonObjectClass = themeJsonObject[QEXTThemeConstant::THEME_THEME_KEY].toObject();
        QStringList themeFieldKeyList = jsonObjectClass.keys();
        foreach (QString fieldKey, themeFieldKeyList) {
            QVariantMap fieldMap = themeDataMap.value(fieldKey);
            QJsonObject jsonObjectBinder = jsonObjectClass.value(fieldKey).toObject();
            QStringList propertyKeyList = jsonObjectBinder.keys();
            for (int i = 0; i < propertyKeyList.size(); ++i) {
                QString propertyKey = propertyKeyList.at(i);
                fieldMap.insert(propertyKey, jsonObjectBinder.value(propertyKey).toVariant());
            }
            themeDataMap.insert(fieldKey, fieldMap);
        }
    } else {
        error = QString("Theme file %1 Format error, ITEM not found!").arg(path);
        return false;
    }

    return true;
}

bool QEXTThemeJsonFileParser::generateThemeTemplateFile(QString &error, QEXTThemeBinder *binder)
{
    //    qDebug() << "QEXTThemeJsonFileParser::generateThemeTemplateFile()------------------------";
    QFile file(QStringLiteral("themeTemplate.json"));
    if (!file.open(QIODevice::ReadWrite)) {
        error = QString("themeTemplate.json file open failed!");
        return false;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument jsonReadDoc(QJsonDocument::fromJson(fileData));
    QJsonObject oldJsonObject = jsonReadDoc.object();

    QJsonObject newJsonObject;
    QJsonObject newInfoJsonObject;
    QJsonObject newThemeJsonObject = oldJsonObject[QEXTThemeConstant::THEME_THEME_KEY].toObject();
    newInfoJsonObject[QEXTThemeConstant::THEME_INFO_VERSION_KEY] = QLatin1String(QEXTThemeConstant::THEME_VERSION);
    newInfoJsonObject[QEXTThemeConstant::THEME_INFO_ABOUT_KEY] = QLatin1String("QEXT theme template file");
    newInfoJsonObject[QEXTThemeConstant::THEME_INFO_NAME_KEY] = QLatin1String("Template");
    newInfoJsonObject[QEXTThemeConstant::THEME_INFO_AUTHOR_KEY] = QLatin1String("QEXT");
    newJsonObject[QEXTThemeConstant::THEME_INFO_KEY] = newInfoJsonObject;

    if (nullptr != binder) {
        writeBinderData(binder, newThemeJsonObject);
    } else {
        foreach (QEXTThemeBinder *pBinderItem, QEXTThemeBinder::allBindersList()) {
            if (nullptr != pBinderItem && nullptr == pBinderItem->parent() && pBinderItem->isEnabled()) {
                if (!pBinderItem->className().isEmpty()) {
                    if (pBinderItem->childName().isEmpty()) {
                        writeBinderData(pBinderItem, newThemeJsonObject);
                    }
                }
            }
        }
    }
    newJsonObject[QEXTThemeConstant::THEME_THEME_KEY] = newThemeJsonObject;

    QJsonDocument jsonSaveDoc(newJsonObject);
    file.resize(0);
    file.write(jsonSaveDoc.toJson());
    file.close();
    return true;
}
