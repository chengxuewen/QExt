#include <qextQmlVLCVideoNode.h>

QEXTQmlVLCVideoNode::QEXTQmlVLCVideoNode()
    : m_geometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4)
{
    this->setGeometry(&m_geometry);
    this->setMaterial(&m_material);
}

void QEXTQmlVLCVideoNode::setFrame(const QSharedPointer<const QEXTVLCYUVVideoFrame> &frame)
{
    m_material.setFrame(frame);
    markDirty(QSGNode::DirtyMaterial);
}

void QEXTQmlVLCVideoNode::setRect(const QRectF &rect, const QRectF &sourceRect)
{
    QSGGeometry::updateTexturedRectGeometry(&m_geometry, rect, sourceRect);
    markDirty(QSGNode::DirtyGeometry);
}
