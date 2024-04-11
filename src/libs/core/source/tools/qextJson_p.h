#ifndef _QEXTJSON_P_H
#define _QEXTJSON_P_H

#include <qextJson.h>

#if QEXT_FEATURE_USE_CJSON_BACKEND
#   include <cjson/cJSON.h>
#endif

class QEXT_CORE_API QExtJsonDocumentPrivate
{
public:
    explicit QExtJsonDocumentPrivate(QExtJsonDocument *q);
    virtual ~QExtJsonDocumentPrivate();

    QExtJsonDocument * const q_ptr;

private:
    QEXT_DECL_PUBLIC(QExtJsonDocument)
    QEXT_DISABLE_COPY_MOVE(QExtJsonDocumentPrivate)
};

#endif // _QEXTJSON_P_H
