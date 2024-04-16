#ifndef _QEXTJSON_P_H
#define _QEXTJSON_P_H

#include <qextJson.h>

#if QEXT_FEATURE_USE_CJSON_BACKEND
#   include <cjson/cJSON.h>
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#   include <QJsonValue>
#   include <QJsonArray>
#   include <QJsonObject>
#   include <QJsonDocument>
#endif

#undef QEXT_FEATURE_USE_CJSON_BACKEND
#define QEXT_FEATURE_USE_CJSON_BACKEND 0

class QExtJsonValuePrivate
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
    QEXT_DECL_PUBLIC(QExtJsonValue)
    QEXT_DISABLE_COPY_MOVE(QExtJsonValuePrivate)
};

class QExtJsonObjectPrivate
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
    QEXT_DECL_PUBLIC(QExtJsonObject)
    QEXT_DISABLE_COPY_MOVE(QExtJsonObjectPrivate)
};

class QExtJsonArrayPrivate
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
    QEXT_DECL_PUBLIC(QExtJsonArray)
    QEXT_DISABLE_COPY_MOVE(QExtJsonArrayPrivate)
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
    QEXT_DECL_PUBLIC(QExtJsonDocument)
    QEXT_DISABLE_COPY_MOVE(QExtJsonDocumentPrivate)
};

#endif // _QEXTJSON_P_H
