#ifndef _QEXTBPDEFAULTNODEPAINTER_H
#define _QEXTBPDEFAULTNODEPAINTER_H

#include <qextBPAbstractNodePainter.h>
#include <qextBPTypes.h>

#include <QPainter>

class QExtBPNodeState;
class QExtBPNodeGraphicsObject;
class QExtBPBasicGraphicsScene;

/// @ Lightweight class incapsulating paint code.
class QEXT_BLUEPRINT_API QExtBPDefaultNodePainter : public QExtBPAbstractNodePainter
{
public:
    void paint(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const override;

    void drawNodeRect(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;

    void drawConnectionPoints(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;

    void drawFilledConnectionPoints(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;

    void drawNodeCaption(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;

    void drawEntryLabels(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;

    void drawResizeRect(QPainter *painter, QExtBPNodeGraphicsObject &ngo) const;
};

#endif // _QEXTBPDEFAULTNODEPAINTER_H
