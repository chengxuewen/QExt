#ifndef _QEXTFRAMELESSHELPER_H
#define _QEXTFRAMELESSHELPER_H

#include <qextFramelessHelperGlobal.h>

#include <QWidget>

class QEXTFramelessHelperPrivate;
class QEXT_FRAMELESSHELPER_API QEXTFramelessHelper : public QObject
{
    Q_OBJECT
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTFramelessHelper)

public:
    explicit QEXTFramelessHelper(QWidget *parent = QEXT_DECL_NULLPTR);
    virtual ~QEXTFramelessHelper();

    void setDraggableMargins(int left, int top, int right, int bottom);
    void setMaximizedMargins(int left, int top, int right, int bottom);

    void setDraggableMargins(const QMargins &margins);
    void setMaximizedMargins(const QMargins &margins);

    QMargins draggableMargins() const;
    QMargins maximizedMargins() const;

    void addIncludeItem(QWidget *item);
    void removeIncludeItem(QWidget *item);

    void addExcludeItem(QWidget *item);
    void removeExcludeItem(QWidget *item);

    int titleBarHeight() const;
    bool isMaximized() const;

    qreal scaleFactor() const;

signals:
    void titleBarHeightChanged(int newValue);
    void scaleFactorChanged(qreal factor);
    void maximizedChanged(bool maximized);

public slots:
    void triggerMinimizeButtonAction();
    void triggerMaximizeButtonAction();
    void triggerCloseButtonAction();
    void setTitleBarHeight(int value);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

    QScopedPointer<QEXTFramelessHelperPrivate> dd_ptr;
};

#endif // _QEXTFRAMELESSHELPER_H
