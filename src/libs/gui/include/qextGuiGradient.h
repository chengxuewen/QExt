#ifndef _QEXTGUIGRADIENT_H
#define _QEXTGUIGRADIENT_H

#include <qextGuiGlobal.h>
#include <qextGuiList.h>
#include <qextGuiGradient.h>

#include <QObject>
#include <QGradient>

class QEXT_GUI_API QEXTGuiGradientStop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal position READ position WRITE setPosition)
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    QEXTGuiGradientStop(QObject *parent = QEXT_DECL_NULLPTR) : QObject(parent) {}
    ~QEXTGuiGradientStop() {}

    qreal position() const { return m_position; }
    void setPosition(qreal position) { m_position = position; updateGradient(); }

    QColor color() const { return m_color; }
    void setColor(const QColor &color) { m_color = color; updateGradient(); }

private:
    void updateGradient();

private:
    qreal m_position;
    QColor m_color;
};

class QEXT_GUI_API QEXTGuiGradient : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QEXTGuiListProperty<QEXTGuiGradientStop> stops READ stops)
    Q_CLASSINFO("DefaultProperty", "stops")

public:
    QEXTGuiGradient(QObject *parent = QEXT_DECL_NULLPTR) : QObject(parent), m_gradient(QEXT_DECL_NULLPTR) {}
    ~QEXTGuiGradient() { delete m_gradient; }

    QEXTGuiListProperty<QEXTGuiGradientStop> stops() { return QEXTGuiListProperty<QEXTGuiGradientStop>(this, m_stops); }

    const QGradient *gradient() const;

Q_SIGNALS:
    void updated();

private:
    void doUpdate();

private:
    QList<QEXTGuiGradientStop *> m_stops;
    mutable QGradient *m_gradient;
    friend class QEXTGuiGradientStop;
};

#endif // _QEXTGUIGRADIENT_H
