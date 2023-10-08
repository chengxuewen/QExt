#ifndef _QEXTOVENTIMER_H
#define _QEXTOVENTIMER_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QDateTime>

class QTimer;
class QEXTOvenTimerPrivate;
class QEXT_WIDGETS_API QEXTOvenTimer : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int duration READ duration WRITE setDuration)

public:
    QEXTOvenTimer(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTOvenTimer();

    int duration() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

Q_SIGNALS:
    void timeout();

public Q_SLOTS:
    void setDuration(int secs);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

    void draw(QPainter *painter);

    QScopedPointer<QEXTOvenTimerPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTOvenTimer)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTOvenTimer)
};

#endif // _QEXTOVENTIMER_H
