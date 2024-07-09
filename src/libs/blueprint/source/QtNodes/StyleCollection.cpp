#include "StyleCollection.hpp"

//using QtNodes::QExtBPConnectionStyle;
//using QtNodes::QExtBPGraphicsViewStyle;
//using QtNodes::QExtBPNodeStyle;
//using QtNodes::QExtBPStyleCollection;

QExtBPNodeStyle const &QExtBPStyleCollection::nodeStyle()
{
    return instance()._nodeStyle;
}

QExtBPConnectionStyle const &QExtBPStyleCollection::connectionStyle()
{
    return instance()._connectionStyle;
}

QExtBPGraphicsViewStyle const &QExtBPStyleCollection::flowViewStyle()
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
