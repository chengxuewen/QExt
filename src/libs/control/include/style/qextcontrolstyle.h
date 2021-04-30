#ifndef QEXTCONTROLSTYLE_H
#define QEXTCONTROLSTYLE_H

#include <qextcontrolglobal.h>

#include <QObject>
#include <QRect>
#include <QApplication>
#include <QPalette>
#include <QPainter>

class QEXTControlStyle : public QObject
{
    Q_OBJECT
public:
    enum StateFlag {
        State_None =                0x00000000,
        State_Enabled =             0x00000001,
        State_Raised =              0x00000002,
        State_Sunken =              0x00000004,
        State_Off =                 0x00000008,
        State_NoChange =            0x00000010,
        State_On =                  0x00000020,
        State_DownArrow =           0x00000040,
        State_Horizontal =          0x00000080,
        State_HasFocus =            0x00000100,
        State_Top =                 0x00000200,
        State_Bottom =              0x00000400,
        State_FocusAtBorder =       0x00000800,
        State_AutoRaise =           0x00001000,
        State_MouseOver =           0x00002000,
        State_UpArrow =             0x00004000,
        State_Selected =            0x00008000,
        State_Active =              0x00010000,
        State_Window =              0x00020000,
        State_Open =                0x00040000,
        State_Children =            0x00080000,
        State_Item =                0x00100000,
        State_Sibling =             0x00200000,
        State_Editing =             0x00400000,
        State_KeyboardFocusChange = 0x00800000,
        State_HasEditFocus =        0x01000000,
        State_ReadOnly =            0x02000000,
        State_Small =               0x04000000,
        State_Mini =                0x08000000
    };
    Q_ENUMS(StateFlag)
    Q_DECLARE_FLAGS(State, StateFlag)

    explicit QEXTControlStyle(QObject *parent = QEXT_NULLPTR);
    ~QEXTControlStyle();

    virtual void polish(QWidget *widget);
    virtual void unpolish(QWidget *widget);

    virtual void polish(QApplication *application);
    virtual void unpolish(QApplication *application);

    virtual void polish(QPalette &palette);

    virtual QRect itemTextRect(const QFontMetrics &fm, const QRect &r,
                               int flags, bool enabled,
                               const QString &text) const;

    virtual QRect itemPixmapRect(const QRect &r, int flags, const QPixmap &pixmap) const;

    virtual void drawItemText(QPainter *painter, const QRect &rect,
                              int flags, const QPalette &pal, bool enabled,
                              const QString &text, QPalette::ColorRole textRole = QPalette::NoRole) const;

    virtual void drawItemPixmap(QPainter *painter, const QRect &rect,
                                int alignment, const QPixmap &pixmap) const;

    virtual QPalette standardPalette() const;
};

#endif // QEXTCONTROLSTYLE_H
