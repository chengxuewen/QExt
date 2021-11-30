#ifndef _QEXTICONBUTTON_H
#define _QEXTICONBUTTON_H

#include <qextWidgetGlobal.h>

#include <QPushButton>
#include <QSize>

class QEXTIconButtonPrivate;
class QEXT_WIDGETS_API QEXTIconButton : public QPushButton
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTIconButton)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTIconButton)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor iconColor READ iconColor WRITE setIconColor)

public:
    QEXTIconButton(const QIcon &icon, QWidget *parent = QEXT_DECL_NULLPTR);
    explicit QEXTIconButton(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIconButton();

    QSize sizeHint() const QEXT_DECL_OVERRIDE;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void setIconColor(const QColor &color);
    QColor iconColor() const;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

protected:
    QEXTIconButton(QEXTIconButtonPrivate &d, QWidget *parent = QEXT_DECL_NULLPTR);

    bool event(QEvent *event) QEXT_DECL_OVERRIDE;
    bool eventFilter(QObject *obj, QEvent *event) QEXT_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) QEXT_DECL_OVERRIDE;

    const QScopedPointer<QEXTIconButtonPrivate> dd_ptr;
};

#endif // _QEXTICONBUTTON_H
