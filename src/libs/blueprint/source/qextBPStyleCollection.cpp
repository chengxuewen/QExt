#include <qextBPStyleCollection.h>

const QExtBPNodeStyle &QExtBPStyleCollection::nodeStyle()
{
    return instance()._nodeStyle;
}

const QExtBPConnectionStyle &QExtBPStyleCollection::connectionStyle()
{
    return instance()._connectionStyle;
}

const QExtBPGraphicsViewStyle &QExtBPStyleCollection::flowViewStyle()
{
    return instance()._flowViewStyle;
}

void QExtBPStyleCollection::setNodeStyle(QExtBPNodeStyle nodeStyle)
{
    instance()._nodeStyle = nodeStyle;
}

void QExtBPStyleCollection::setConnectionStyle(QExtBPConnectionStyle connectionStyle)
{
    instance()._connectionStyle = connectionStyle;
}

void QExtBPStyleCollection::setGraphicsViewStyle(QExtBPGraphicsViewStyle flowViewStyle)
{
    instance()._flowViewStyle = flowViewStyle;
}

QExtBPStyleCollection &QExtBPStyleCollection::instance()
{
    static QExtBPStyleCollection collection;

    return collection;
}
