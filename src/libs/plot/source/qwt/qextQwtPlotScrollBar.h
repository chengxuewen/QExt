#ifndef _QEXTQWTPLOTSCROLLBAR_H
#define _QEXTQWTPLOTSCROLLBAR_H

#include <qextPlotGlobal.h>

#include <QScrollBar>

class QExtPlotScrollBarPrivate;
class QEXT_PLOT_API QExtPlotScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit QExtPlotScrollBar(QWidget *parent = QEXT_NULLPTR);
    QExtPlotScrollBar(Qt::Orientation orientation, QWidget *parent = QEXT_NULLPTR);
    QExtPlotScrollBar(double minBase, double maxBase, Qt::Orientation orientation, QWidget *parent = QEXT_NULLPTR);
    ~QExtPlotScrollBar() QEXT_OVERRIDE;

    bool isInverted() const;
    void setInverted(bool inverted);

    double minBaseValue() const;
    double maxBaseValue() const;

    double minSliderValue() const;
    double maxSliderValue() const;

    int extent() const;

    void init();
    void init(double minBase, double maxBase)
    {
        this->init();
        this->setBase(minBase, maxBase);
        this->moveSlider(minBase, maxBase);
    }

Q_SIGNALS:
    void sliderMovedWithRange(Qt::Orientation orientation, double min, double max);
    void valueChangedWithRange(Qt::Orientation orientation, double min, double max);

public Q_SLOTS:
    virtual void setBase(double min, double max);
    virtual void moveSlider(double min, double max);

private Q_SLOTS:
    void catchValueChanged(int value);
    void catchSliderMoved(int value);

protected:
    void sliderRange(int value, double &min, double &max) const;
    double mapFromTick(int) const;
    int mapToTick(double value) const;

private:
    QScopedPointer<QExtPlotScrollBarPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPlotScrollBar)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotScrollBar)
};

#endif // _QEXTQWTPLOTSCROLLBAR_H
