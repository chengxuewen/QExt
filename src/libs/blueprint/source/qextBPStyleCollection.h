#ifndef _QEXTBPSTYLECOLLECTION_H
#define _QEXTBPSTYLECOLLECTION_H

#include <qextBlueprintGlobal.h>
#include <qextBPGraphicsViewStyle.h>
#include <qextBPConnectionStyle.h>
#include <qextBPNodeStyle.h>

class QExtBPStyleCollectionPrivate;
class QEXT_BLUEPRINT_API QExtBPStyleCollection
{
public:
    virtual ~QExtBPStyleCollection();
    static QExtBPStyleCollection &instance();

    static void setNodeStyle(QExtBPNodeStyle);

    static void setConnectionStyle(QExtBPConnectionStyle);

    static void setGraphicsViewStyle(QExtBPGraphicsViewStyle);

    static const QExtBPNodeStyle &nodeStyle();

    static const QExtBPConnectionStyle &connectionStyle();

    static const QExtBPGraphicsViewStyle &flowViewStyle();

protected:
    QExtBPStyleCollection();

    QScopedPointer<QExtBPStyleCollectionPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtBPStyleCollection)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtBPStyleCollection)
};

#endif // _QEXTBPSTYLECOLLECTION_H
