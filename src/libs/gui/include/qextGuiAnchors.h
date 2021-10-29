#ifndef _QEXTGUIANCHORS_H
#define _QEXTGUIANCHORS_H

#include <qextGuiGlobal.h>

#include <QObject>
#include <QGraphicsObject>

struct QEXT_GUI_API QEXTGuiAnchorLine
{
    QEXTGuiAnchorLine() : item(QEXT_DECL_NULLPTR), anchorLine(AnchorLine_Invalid) {}
    enum AnchorLineType
    {
        AnchorLine_Invalid = 0x0,
        AnchorLine_Left = 0x01,
        AnchorLine_Right = 0x02,
        AnchorLine_Top = 0x04,
        AnchorLine_Bottom = 0x08,
        AnchorLine_HCenter = 0x10,
        AnchorLine_VCenter = 0x20,
        AnchorLine_Baseline = 0x40,
        AnchorLine_HorizontalMask = AnchorLine_Left | AnchorLine_Right | AnchorLine_HCenter,
        AnchorLine_VerticalMask = AnchorLine_Top | AnchorLine_Bottom | AnchorLine_VCenter | AnchorLine_Baseline
    };

    QGraphicsObject *item;
    AnchorLineType anchorLine;
};


class QEXTGuiAnchorsPrivate;
class QEXT_GUI_API QEXTGuiAnchors : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QEXTGuiAnchorLine left READ left WRITE setLeft RESET resetLeft NOTIFY leftChanged)
    Q_PROPERTY(QEXTGuiAnchorLine right READ right WRITE setRight RESET resetRight NOTIFY rightChanged)
    Q_PROPERTY(QEXTGuiAnchorLine horizontalCenter READ horizontalCenter WRITE setHorizontalCenter RESET resetHorizontalCenter NOTIFY horizontalCenterChanged)
    Q_PROPERTY(QEXTGuiAnchorLine top READ top WRITE setTop RESET resetTop NOTIFY topChanged)
    Q_PROPERTY(QEXTGuiAnchorLine bottom READ bottom WRITE setBottom RESET resetBottom NOTIFY bottomChanged)
    Q_PROPERTY(QEXTGuiAnchorLine verticalCenter READ verticalCenter WRITE setVerticalCenter RESET resetVerticalCenter NOTIFY verticalCenterChanged)
    Q_PROPERTY(QEXTGuiAnchorLine baseline READ baseline WRITE setBaseline RESET resetBaseline NOTIFY baselineChanged)
    Q_PROPERTY(qreal margins READ margins WRITE setMargins NOTIFY marginsChanged)
    Q_PROPERTY(qreal leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(qreal rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(qreal horizontalCenterOffset READ horizontalCenterOffset WRITE setHorizontalCenterOffset NOTIFY horizontalCenterOffsetChanged)
    Q_PROPERTY(qreal topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(qreal bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(qreal verticalCenterOffset READ verticalCenterOffset WRITE setVerticalCenterOffset NOTIFY verticalCenterOffsetChanged)
    Q_PROPERTY(qreal baselineOffset READ baselineOffset WRITE setBaselineOffset NOTIFY baselineOffsetChanged)
    Q_PROPERTY(QGraphicsObject *fill READ fill WRITE setFill RESET resetFill NOTIFY fillChanged)
    Q_PROPERTY(QGraphicsObject *centerIn READ centerIn WRITE setCenterIn RESET resetCenterIn NOTIFY centerInChanged)

public:
    enum AnchorType {
        Anchor_Left = 0x01,
        Anchor_Right = 0x02,
        Anchor_Top = 0x04,
        Anchor_Bottom = 0x08,
        Anchor_HCenter = 0x10,
        Anchor_VCenter = 0x20,
        Anchor_Baseline = 0x40,
        Anchor_HorizontalMask = Anchor_Left | Anchor_Right | Anchor_HCenter,
        Anchor_VerticalMask = Anchor_Top | Anchor_Bottom | Anchor_VCenter | Anchor_Baseline
    };
    Q_DECLARE_FLAGS(AnchorTypes, AnchorType)

    QEXTGuiAnchors(QObject *parent = QEXT_DECL_NULLPTR);
    QEXTGuiAnchors(QGraphicsObject *item, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiAnchors();

    QEXTGuiAnchorLine left() const;
    void setLeft(const QEXTGuiAnchorLine &edge);
    void resetLeft();

    QEXTGuiAnchorLine right() const;
    void setRight(const QEXTGuiAnchorLine &edge);
    void resetRight();

    QEXTGuiAnchorLine horizontalCenter() const;
    void setHorizontalCenter(const QEXTGuiAnchorLine &edge);
    void resetHorizontalCenter();

    QEXTGuiAnchorLine top() const;
    void setTop(const QEXTGuiAnchorLine &edge);
    void resetTop();

    QEXTGuiAnchorLine bottom() const;
    void setBottom(const QEXTGuiAnchorLine &edge);
    void resetBottom();

    QEXTGuiAnchorLine verticalCenter() const;
    void setVerticalCenter(const QEXTGuiAnchorLine &edge);
    void resetVerticalCenter();

    QEXTGuiAnchorLine baseline() const;
    void setBaseline(const QEXTGuiAnchorLine &edge);
    void resetBaseline();

    qreal leftMargin() const;
    void setLeftMargin(qreal);

    qreal rightMargin() const;
    void setRightMargin(qreal);

    qreal horizontalCenterOffset() const;
    void setHorizontalCenterOffset(qreal);

    qreal topMargin() const;
    void setTopMargin(qreal);

    qreal bottomMargin() const;
    void setBottomMargin(qreal);

    qreal margins() const;
    void setMargins(qreal);

    qreal verticalCenterOffset() const;
    void setVerticalCenterOffset(qreal);

    qreal baselineOffset() const;
    void setBaselineOffset(qreal);

    QGraphicsObject *fill() const;
    void setFill(QGraphicsObject *);
    void resetFill();

    QGraphicsObject *centerIn() const;
    void setCenterIn(QGraphicsObject *);
    void resetCenterIn();

    QEXTGuiAnchors::AnchorTypes usedAnchors() const;

    void classBegin();
    void componentComplete();

    bool mirrored();

Q_SIGNALS:
    void leftChanged();
    void rightChanged();
    void topChanged();
    void bottomChanged();
    void verticalCenterChanged();
    void horizontalCenterChanged();
    void baselineChanged();
    void fillChanged();
    void centerInChanged();
    void leftMarginChanged();
    void rightMarginChanged();
    void topMarginChanged();
    void bottomMarginChanged();
    void marginsChanged();
    void verticalCenterOffsetChanged();
    void horizontalCenterOffsetChanged();
    void baselineOffsetChanged();

protected Q_SLOTS:
    void onWidgetGeometryChanged();
    void onWidgetDestroyed(QObject *obj);

protected:
    QScopedPointer<QEXTGuiAnchorsPrivate> d_ptr;

private:
    //    friend class QEXTGuiGVItem;
    //    friend class QEXTGuiGVItemPrivate;
    //    friend class QEXTGuiGVGraphicsWidget;
    Q_DISABLE_COPY(QEXTGuiAnchors)
    Q_DECLARE_PRIVATE(QEXTGuiAnchors)
};

#endif // _QEXTGUIANCHORS_H
