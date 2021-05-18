#ifndef QEXTSTYLEOPTION_H
#define QEXTSTYLEOPTION_H

#include <qextwidgetsglobal.h>
#include <QObject>
//#include <qextpalette.h>

#include <QStyleOption>

class QGuiApplication;

enum ItemDataRole {
    MarginsRole = Qt::UserRole + 1,
    LeftActionListRole,
    TopActionListRole,
    RightActionListRole,
    BottomActionListRole,
    TextActionListRole,
    ViewItemFontLevelRole,
    ViewItemBackgroundRole,
    ViewItemForegroundRole,
    UserRole = Qt::UserRole << 2
};

class QEXT_WIDGETS_API QEXTStyleOption
{
public:
    enum OptionType {
        SO_HighlightButton = QStyleOption::SO_CustomBase + 1,
        SO_CustomBase = QStyleOption::SO_CustomBase << 2
    };

    virtual void init(QWidget *widget);
    virtual void init(const QWidget *widget);

//    QEXTPalette extPalette;
};


class QEXT_WIDGETS_API QEXTStyleOptionButton : public QStyleOptionButton, public QEXTStyleOption
{
public:
    enum ButtonFeature {
        SuggestButton = (CommandLinkButton << 1),
        WarningButton = (SuggestButton << 1),
        FloatingButton = (WarningButton << 1),
        TitleBarButton = (FloatingButton << 1)
    };

    void init(const QWidget *widget) QEXT_OVERRIDE;
};

class QEXT_WIDGETS_API QEXTStyleOptionButtonBoxButton : public QEXTStyleOptionButton
{
public:
    enum ButtonPosition {
        Invalid,
        Beginning,
        Middle,
        End,
        OnlyOne
    };

    Qt::Orientation orientation;
    ButtonPosition position;
};

class QEXT_WIDGETS_API QEXTStyleOptionLineEdit : public QEXTStyleOption
{
public:
    enum LineEditFeature {
        None        = 0x0,
        Alert       = 0x1,
        IconButton  = 0x2
    };
    Q_DECLARE_FLAGS(LineEditFeatures, LineEditFeature)

    QEXTStyleOptionLineEdit() {
        features = None;
    }

    void init(const QWidget *widget) QEXT_OVERRIDE;

    LineEditFeatures features;
    QRect iconButtonRect;
};

class QEXT_WIDGETS_API QEXTStyleOptionBackgroundGroup : public QStyleOption, public QEXTStyleOption
{
public:
    enum ItemBackgroundPosition {
        Invalid,
        Beginning,
        Middle,
        End,
        OnlyOne
    };

    //    using QEXTStyleOption::QEXTStyleOption;
    //    using QStyleOption::QStyleOption;
    void init(const QWidget *widget) QEXT_OVERRIDE;

    Qt::Orientations directions;
    ItemBackgroundPosition position;
};

class QEXT_WIDGETS_API QEXTStyleOptionIcon : public QStyleOption, public QEXTStyleOption
{
public:
    QIcon icon;
};

class QEXT_WIDGETS_API QEXTStyleOptionViewItem : public QStyleOptionViewItem, public QEXTStyleOption
{
public:
    enum ViewItemFeature {

    };
};

class QEXT_WIDGETS_API QEXTStyleOptionFloatingWidget : public QStyleOption, public QEXTStyleOption
{
public:
    //    using QEXTStyleOption::init;
    QEXTStyleOptionFloatingWidget() {
        frameRadius = -1;
    }

    bool noBackground;
    int frameRadius;
};

class QEXTFontSizeManagerPrivate;
class QEXT_WIDGETS_API QEXTFontSizeManager
{
public:
    enum SizeType {
        T1,
        T2,
        T3,
        T4,
        T5,
        T6,
        T7,
        T8,
        T9,
        T10,
        NSizeTypes
    };

    static QEXTFontSizeManager *instance();
    void bind(QWidget *widget, SizeType type);
    void bind(QWidget *widget, SizeType type, int weight);
    void unbind(QWidget *widget);

    quint16 fontPixelSize(SizeType type) const;
    void setFontPixelSize(SizeType type, quint16 size);
    void setFontGenericPixelSize(quint16 size);
    const QFont get(SizeType type, const QFont &base = QFont()) const;
    const QFont get(SizeType type, int weight, const QFont &base = QFont()) const;

    inline const QFont t1(const QFont &base = QFont()) const
    { return get(T1, base); }
    inline const QFont t2(const QFont &base = QFont()) const
    { return get(T2, base); }
    inline const QFont t3(const QFont &base = QFont()) const
    { return get(T3, base); }
    inline const QFont t4(const QFont &base = QFont()) const
    { return get(T4, base); }
    inline const QFont t5(const QFont &base = QFont()) const
    { return get(T5, base); }
    inline const QFont t6(const QFont &base = QFont()) const
    { return get(T6, base); }
    inline const QFont t7(const QFont &base = QFont()) const
    { return get(T7, base); }
    inline const QFont t8(const QFont &base = QFont()) const
    { return get(T8, base); }
    inline const QFont t9(const QFont &base = QFont()) const
    { return get(T9, base); }
    inline const QFont t10(const QFont &base = QFont()) const
    { return get(T10, base); }

    static int fontPixelSize(const QFont &font);

private:
    QEXTFontSizeManager();

    QScopedPointer<QEXTFontSizeManagerPrivate> d;
};

#endif // QEXTSTYLEOPTION_H
