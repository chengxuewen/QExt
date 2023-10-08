#ifndef _QEXTFRAMELESSMAINWINDOW_P_H
#define _QEXTFRAMELESSMAINWINDOW_P_H

#include <qextFramelessMainwindow.h>

#include <QWidget>
#include <QPointer>

class QEXTFramelessMainWindow;
class QEXT_WIDGETS_API QEXTFramelessMainWindowPrivate
{
public:
    explicit QEXTFramelessMainWindowPrivate(QEXTFramelessMainWindow *q);
    virtual ~QEXTFramelessMainWindowPrivate();

    QEXTFramelessMainWindow * const q_ptr;

    int m_padding;
    bool m_moveEnable;
    bool m_resizeEnable;

    QPointer<QWidget> m_titleBar;

    bool m_mousePressed;
    QPoint m_mousePoint;
    QRect m_mouseRect;

    //Whether to hold down a region + Size of the region to hold down
    //Left + right + upper side + lower side + left upper side + right upper side + left lower side + right lower side
    QList<bool> m_pressedArea;
    QList<QRect> m_pressedRect;

    //Whether records are minimized
    bool m_isMin;
    //Stores the default properties of the form
    Qt::WindowFlags m_flags;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTFramelessMainWindowPrivate)
    QEXT_DECL_PUBLIC(QEXTFramelessMainWindow)
};

#endif // _QEXTFRAMELESSMAINWINDOW_P_H
