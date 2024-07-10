#ifndef _QEXTBPSTYLECOLLECTION_H
#define _QEXTBPSTYLECOLLECTION_H

#include <qextBlueprintGlobal.h>
#include <qextBPGraphicsViewStyle.h>
#include <qextBPConnectionStyle.h>
#include <qextBPNodeStyle.h>

class QEXT_BLUEPRINT_API QExtBPStyleCollection
{
public:
    static QExtBPNodeStyle const &nodeStyle();

    static QExtBPConnectionStyle const &connectionStyle();

    static QExtBPGraphicsViewStyle const &flowViewStyle();

public:
    static void setNodeStyle(QExtBPNodeStyle);

    static void setConnectionStyle(QExtBPConnectionStyle);

    static void setGraphicsViewStyle(QExtBPGraphicsViewStyle);

private:
    QExtBPStyleCollection() = default;

    QExtBPStyleCollection(QExtBPStyleCollection const &) = delete;

    QExtBPStyleCollection &operator=(QExtBPStyleCollection const &) = delete;

    static QExtBPStyleCollection &instance();

private:
    QExtBPNodeStyle _nodeStyle;

    QExtBPConnectionStyle _connectionStyle;

    QExtBPGraphicsViewStyle _flowViewStyle;
};

#endif // _QEXTBPSTYLECOLLECTION_H
