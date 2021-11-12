#ifndef _QEXTOVENTIMER_H
#define _QEXTOVENTIMER_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QDateTime>

class QTimer;
class QEXT_WIDGETS_API QEXTOvenTimer : public QWidget
{
    Q_OBJECT
public:
    QEXTOvenTimer(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTOvenTimer();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

    void draw(QPainter *painter);

private:
    int duration;
    QDateTime finishTime;

    QTimer *updateTimer;
    QTimer *finishTimer;

public:
    int getDuration()               const;
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setDuration(int secs);

Q_SIGNALS:
    void timeout();
};

#endif // _QEXTOVENTIMER_H
