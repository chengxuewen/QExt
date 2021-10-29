#ifndef _QEXTGUIGVITEM_P_H
#define _QEXTGUIGVITEM_P_H

#include <qextGuiGlobal.h>
#include <qextGuiAnchors.h>
#include <qextGuiContents.h>
#include <qextGuiNullableValue.h>
#include <qextGuiItemChangeListener.h>
#include <qextGuiGVItem.h>

#include <QVector>

/*
    Key filters can be installed on a QDeclarativeItem, but not removed.  Currently they
    are only used by attached objects (which are only destroyed on Item
    destruction), so this isn't a problem.  If in future this becomes any form
    of public API, they will have to support removal too.
*/
class QEXT_GUI_API QEXTGuiGVItemKeyFilter
{
public:
    QEXTGuiGVItemKeyFilter(QEXTGuiGVItem * item = QEXT_DECL_NULLPTR);
    virtual ~QEXTGuiGVItemKeyFilter();

    virtual void keyPressed(QKeyEvent *event, bool post);
    virtual void keyReleased(QKeyEvent *event, bool post);
    virtual void inputMethodEvent(QInputMethodEvent *event, bool post);
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;
    virtual void componentComplete();

    bool m_processPost;

private:
    QEXTGuiGVItemKeyFilter *m_next;
};


class QEXT_GUI_API QEXTGuiGVItemPrivate
{
public:
    enum ChangeType
    {
        Geometry = 0x01,
        SiblingOrder = 0x02,
        Visibility = 0x04,
        Opacity = 0x08,
        Destroyed = 0x10
    };
    Q_DECLARE_FLAGS(ChangeTypes, ChangeType)

    struct ChangeListener
    {
        ChangeListener(QDeclarativeItemChangeListener *l, ChangeType t) : listener(l), types(t) {}
        QDeclarativeItemChangeListener *listener;
        ChangeTypes types;
        bool operator==(const ChangeListener &other) const { return listener == other.listener && types == other.types; }
    };

    explicit QEXTGuiGVItemPrivate(QEXTGuiGVItem *q);
    virtual ~QEXTGuiGVItemPrivate();

    QEXTGuiAnchors *anchors();

    qreal width() const;
    void setWidth(qreal width);
    void resetWidth();

    qreal height() const;
    void setHeight(qreal height);
    void resetHeight();

    void resolveLayoutMirror();
    void setImplicitLayoutMirror(bool mirror, bool inherit);
    void setLayoutMirror(bool mirror);

    virtual qreal implicitWidth() const;
    virtual qreal implicitHeight() const;
    virtual void implicitWidthChanged();
    virtual void implicitHeightChanged();

    virtual void focusChanged(bool flag);
    virtual void focusScopeItemChange(bool isSubFocusItem);


    QEXTGuiGVItem * const q_ptr;

//    QDeclarativeStateGroup *_states();
//    QDeclarativeStateGroup *_stateGroup;

    QVector<ChangeListener> m_changeListeners;

    QEXTGuiAnchors *m_anchors;
    QEXTGuiContents *m_contents;
    QEXTGuiNullableValue<qreal> m_baselineOffset;

    QEXTGuiGVItem::TransformOrigin m_origin:5;
    bool m_widthValid:1;
    bool m_heightValid:1;
    bool m_componentComplete:1;
    bool m_keepMouse:1;
    bool m_smooth:1;
    bool m_transformOriginDirty : 1;
    bool m_doneEventPreHandler : 1;
    bool m_inheritedLayoutMirror:1;
    bool m_effectiveLayoutMirror:1;
    bool m_isMirrorImplicit:1;
    bool m_inheritMirrorFromParent:1;
    bool m_inheritMirrorFromItem:1;
    bool m_hadFocus:1;
    bool m_hadActiveFocus:1;

    QEXTGuiGVItemKeyFilter *m_keyHandler;

    qreal m_width;
    qreal m_height;
    qreal m_implicitWidth;
    qreal m_implicitHeight;

private:
    friend class QEXTGuiGVItemPrivate;

    Q_DISABLE_COPY(QEXTGuiGVItemPrivate)
    Q_DECLARE_PUBLIC(QEXTGuiGVItem)
};

#endif // _QEXTGUIGVITEM_P_H
