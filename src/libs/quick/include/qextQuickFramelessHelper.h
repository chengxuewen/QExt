#ifndef _QEXTQUICKFRAMELESSHELPER_H
#define _QEXTQUICKFRAMELESSHELPER_H

#include <qextQuickGlobal.h>

#include <QQuickItem>
#include <QQmlParserStatus>

class QEXTQuickFramelessHelperPrivate;
class QEXT_QUICK_API QEXTQuickFramelessHelper : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQuickFramelessHelper)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQuickFramelessHelper)

    Q_PROPERTY(int topDraggableMargin READ topDraggableMargin WRITE setTopDraggableMargin NOTIFY topDraggableMarginChanged)
    Q_PROPERTY(int leftDraggableMargin READ leftDraggableMargin WRITE setLeftDraggableMargin NOTIFY leftDraggableMarginChanged)
    Q_PROPERTY(int rightDraggableMargin READ rightDraggableMargin WRITE setRightDraggableMargin NOTIFY rightDraggableMarginChanged)
    Q_PROPERTY(int bottomDraggableMargin READ bottomDraggableMargin WRITE setBottomDraggableMargin NOTIFY bottomDraggableMarginChanged)

    Q_PROPERTY(int topMaximizedMargin READ topMaximizedMargin WRITE setTopMaximizedMargin NOTIFY topMaximizedMarginChanged)
    Q_PROPERTY(int leftMaximizedMargin READ leftMaximizedMargin WRITE setLeftMaximizedMargin NOTIFY leftMaximizedMarginChanged)
    Q_PROPERTY(int rightMaximizedMargin READ rightMaximizedMargin WRITE setRightMaximizedMargin NOTIFY rightMaximizedMarginChanged)
    Q_PROPERTY(int bottomMaximizedMargin READ bottomMaximizedMargin WRITE setBottomMaximizedMargin NOTIFY bottomMaximizedMarginChanged)

    Q_PROPERTY(int titleBarHeight READ titleBarHeight WRITE setTitleBarHeight NOTIFY titleBarHeightChanged)

    Q_PROPERTY(qreal scaleFactor READ scaleFactor NOTIFY scaleFactorChanged)

    Q_INTERFACES(QQmlParserStatus)

public:
    explicit QEXTQuickFramelessHelper(QObject *parent = nullptr);
    virtual ~QEXTQuickFramelessHelper();

    void classBegin() final;
    void componentComplete() final;

    int topDraggableMargin() const;
    void setTopDraggableMargin(int dm);

    int leftDraggableMargin() const;
    void setLeftDraggableMargin(int dm);

    int rightDraggableMargin() const;
    void setRightDraggableMargin(int dm);

    int bottomDraggableMargin() const;
    void setBottomDraggableMargin(int dm);

    int topMaximizedMargin() const;
    void setTopMaximizedMargin(int dm);

    int leftMaximizedMargin() const;
    void setLeftMaximizedMargin(int dm);

    int rightMaximizedMargin() const;
    void setRightMaximizedMargin(int dm);

    int bottomMaximizedMargin() const;
    void setBottomMaximizedMargin(int dm);

    int titleBarHeight() const;
    qreal scaleFactor() const;

Q_SIGNALS:
    void topDraggableMarginChanged();
    void leftDraggableMarginChanged();
    void rightDraggableMarginChanged();
    void bottomDraggableMarginChanged();

    void topMaximizedMarginChanged();
    void leftMaximizedMarginChanged();
    void rightMaximizedMarginChanged();
    void bottomMaximizedMarginChanged();

    void titleBarHeightChanged();
    void scaleFactorChanged();


public Q_SLOTS:
    void addIncludeItem(QQuickItem *item);
    void addExcludeItem(QQuickItem *item);
    void removeIncludeItem(QQuickItem *item);
    void removeExcludeItem(QQuickItem *item);

    void setTitleBarHeight(int value);

    void triggerMinimizeButtonAction();
    void triggerMaximizeButtonAction();
    void triggerCloseButtonAction();

protected:
    QScopedPointer<QEXTQuickFramelessHelperPrivate> dd_ptr;
};

#endif // _QEXTQUICKFRAMELESSHELPER_H
