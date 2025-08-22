#ifndef _QEXTJSON_P_H
#define _QEXTJSON_P_H

#include <qextJson.h>

#if QEXT_FEATURE_USE_CJSON_BACKEND
#   include <cjson/cJSON.h>
#endif
#if QEXT_FEATURE_USE_3rdQJSON_BACKEND
#   include <qjsonarray.h>
#   include <qjsonvalue.h>
#   include <qjsonobject.h>
#   include <qjsondocument.h>
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#   include <QJsonValue>
#   include <QJsonArray>
#   include <QJsonObject>
#   include <QJsonDocument>
#endif

class QEXT_CORE_API QExtJsonValuePrivate
{
public:
    explicit QExtJsonValuePrivate(QExtJsonValue *q);
    virtual ~QExtJsonValuePrivate();

    QExtJsonValue * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *m_cJson;
#else
    QJsonValue m_value;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonValue)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonValuePrivate)
};

class QEXT_CORE_API QExtJsonObjectPrivate
{
public:
    explicit QExtJsonObjectPrivate(QExtJsonObject *q);
    virtual ~QExtJsonObjectPrivate();

    QExtJsonObject * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *m_cJson;
#else
    QJsonObject m_object;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonObject)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonObjectPrivate)
};

class QEXT_CORE_API QExtJsonArrayPrivate
{
public:
    explicit QExtJsonArrayPrivate(QExtJsonArray *q);
    virtual ~QExtJsonArrayPrivate();

    QExtJsonArray * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *m_cJson;
#else
    QJsonArray m_array;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonArray)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonArrayPrivate)
};

class QEXT_CORE_API QExtJsonDocumentPrivate
{
public:
    explicit QExtJsonDocumentPrivate(QExtJsonDocument *q);
    virtual ~QExtJsonDocumentPrivate();

    QExtJsonDocument * const q_ptr;

#if QEXT_FEATURE_USE_CJSON_BACKEND
    cJSON *m_cJson;
#else
    QJsonDocument m_document;
#endif

private:
    QEXT_DECLARE_PUBLIC(QExtJsonDocument)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtJsonDocumentPrivate)
};

#endif // _QEXTJSON_P_H
