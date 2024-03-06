#ifndef _QEXTGRAPHICSVIEW_P_H
#define _QEXTGRAPHICSVIEW_P_H

#include <qextGraphicsView.h>

class QExtGraphicsViewRuleBarPrivate
{
    QExtGraphicsViewRuleBar * const q_ptr;
public:
    explicit QExtGraphicsViewRuleBarPrivate(QExtGraphicsViewRuleBar *q);
    virtual ~QExtGraphicsViewRuleBarPrivate();

    QPoint m_lastPos;
    QColor m_faceColor;
    QGraphicsView *m_view;
    Qt::Orientation m_direction;

    double m_lower;
    double m_upper;
    double m_maxsize;

private:
    QEXT_DECL_PUBLIC(QExtGraphicsViewRuleBar)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsViewRuleBarPrivate)
};

class QExtGraphicsViewPrivate
{
    QExtGraphicsView * const q_ptr;
public:
    explicit QExtGraphicsViewPrivate(QExtGraphicsView *q);
    virtual ~QExtGraphicsViewPrivate();

    bool maybeSave();
    void loadCanvas(QXmlStreamReader *xml);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QExtGraphicsItemGroup *loadGroupFromXML( QXmlStreamReader *xml);

    QExtGraphicsViewRuleBar *m_hRulerBar;
    QExtGraphicsViewRuleBar *m_vRulerBar;
    QExtGraphicsViewCornerBox *m_cornerBox;

    bool m_modified;
    bool m_untitled;
    QString m_curFile;

private:
    QEXT_DECL_PUBLIC(QExtGraphicsView)
    QEXT_DISABLE_COPY_MOVE(QExtGraphicsViewPrivate)
};

#endif // _QEXTGRAPHICSVIEW_P_H
