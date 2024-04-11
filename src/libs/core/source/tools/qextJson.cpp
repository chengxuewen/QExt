#include <private/qextJson_p.h>

QExtJsonDocumentPrivate::QExtJsonDocumentPrivate(QExtJsonDocument *q)
    : q_ptr(q)
{

}

QExtJsonDocumentPrivate::~QExtJsonDocumentPrivate()
{

}


QExtJsonDocument::QExtJsonDocument()
    : dd_ptr(new QExtJsonDocumentPrivate(this))
{

}

QExtJsonDocument::~QExtJsonDocument()
{

}

