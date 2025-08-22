#include <qextBPStyleCollection.h>

class QExtBPStyleCollectionPrivate
{
public:
    explicit QExtBPStyleCollectionPrivate(QExtBPStyleCollection *q);
    virtual ~QExtBPStyleCollectionPrivate();

    QExtBPStyleCollection * const q_ptr;

    QExtBPNodeStyle m_nodeStyle;
    QExtBPConnectionStyle m_connectionStyle;
    QExtBPGraphicsViewStyle m_flowViewStyle;

private:
    QEXT_DECLARE_PUBLIC(QExtBPStyleCollection)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPStyleCollectionPrivate)
};

QExtBPStyleCollectionPrivate::QExtBPStyleCollectionPrivate(QExtBPStyleCollection *q)
    : q_ptr(q)
{
}

QExtBPStyleCollectionPrivate::~QExtBPStyleCollectionPrivate()
{
}

QExtBPStyleCollection::QExtBPStyleCollection()
    : dd_ptr(new QExtBPStyleCollectionPrivate(this))
{
}

QExtBPStyleCollection::~QExtBPStyleCollection()
{
}

const QExtBPNodeStyle &QExtBPStyleCollection::nodeStyle()
{
    return QExtBPStyleCollection::instance().dd_ptr->m_nodeStyle;
}

const QExtBPConnectionStyle &QExtBPStyleCollection::connectionStyle()
{
    return QExtBPStyleCollection::instance().dd_ptr->m_connectionStyle;
}

const QExtBPGraphicsViewStyle &QExtBPStyleCollection::flowViewStyle()
{
    return QExtBPStyleCollection::instance().dd_ptr->m_flowViewStyle;
}

void QExtBPStyleCollection::setNodeStyle(QExtBPNodeStyle nodeStyle)
{
    QExtBPStyleCollection::instance().dd_ptr->m_nodeStyle = nodeStyle;
}

void QExtBPStyleCollection::setConnectionStyle(QExtBPConnectionStyle connectionStyle)
{
    QExtBPStyleCollection::instance().dd_ptr->m_connectionStyle = connectionStyle;
}

void QExtBPStyleCollection::setGraphicsViewStyle(QExtBPGraphicsViewStyle flowViewStyle)
{
    QExtBPStyleCollection::instance().dd_ptr->m_flowViewStyle = flowViewStyle;
}

QExtBPStyleCollection &QExtBPStyleCollection::instance()
{
    static QExtBPStyleCollection collection;
    return collection;
}
