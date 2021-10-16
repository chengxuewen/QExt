#ifndef _QEXTWAVECHART_H
#define _QEXTWAVECHART_H

#include <qextWidgetGlobal.h>
#include <qextObject.h>

/**
 * 曲线图表控件 作者:feiyangqingyun(QQ:517216493) 2016-10-23
 * 1:可设置间隔
 * 2:可设置标题
 * 3:可设置是否显示横线及坐标点
 * 4:可设置背景色文字颜色
 * 5:可设置范围值及x轴y轴步长
 * 6:暂时不支持最小值小于0的数据
 */

#include <QWidget>

#ifndef Q_WS_QWS
    #if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
        #include <QtDesigner/QDesignerExportWidget>
    #else
        #include <QtUiPlugin/QDesignerExportWidget>
    #endif
#endif


class QEXTWaveChartPrivate;
class QEXT_WIDGET_API QEXTWaveChart : public QWidget, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double xAxisStep READ xAxisStep WRITE setXAxisStep)
    Q_PROPERTY(double yAxisStep READ yAxisStep WRITE setYAxisStep)

    Q_PROPERTY(double space READ space WRITE setSpace)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool smoothEnable READ smoothEnable WRITE setSmoothEnable)
    Q_PROPERTY(bool hLineVisiable READ hLineVisiable WRITE setHLineVisiable)
    Q_PROPERTY(bool vLineVisiable READ vLineVisiable WRITE setVLineVisiable)
    Q_PROPERTY(bool pointVisiable READ pointVisiable WRITE setPointVisiable)
    Q_PROPERTY(bool pointBackgroundVisiable READ pointBackgroundVisiable WRITE setPointBackgroundVisiable)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor)

public:
    explicit QEXTWaveChart(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTWaveChart();

    double minValue() const;
    double maxValue() const;
    double xAxisStep() const;
    double yAxisStep() const;
    double hLineStep() const;
    double vLineStep() const;

    double space() const;
    QString title() const;
    bool smoothEnable() const;
    bool titleVisiable() const;
    bool hLineVisiable() const;
    bool vLineVisiable() const;
    bool pointVisiable() const;
    bool pointBackgroundVisiable() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;
    QColor textColor() const;
    QColor pointColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void addData(double data);
    void setData(const QVector<double> &data);
    void clearData();

    void setMinValue(double value);
    void setMaxValue(double value);
    void setXAxisStep(double step);
    void setYAxisStep(double step);
    void setHLineStep(double step);
    void setVLineStep(double step);

    void setSpace(double space);
    void setTitle(const QString &title);
    void setSmoothEnable(bool enable);
    void setTitleVisiable(bool visiable);
    void setHLineVisiable(bool visiable);
    void setVLineVisiable(bool visiable);
    void setPointVisiable(bool visiable);
    void setPointBackgroundVisiable(bool visiable);

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setPointColor(const QColor &color);


protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawBox(QPainter *painter);
    void drawText(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawPoint(QPainter *painter);

private slots:
    void updateData();

private:
    QEXT_DECL_PRIVATE(QEXTWaveChart)
    QEXT_DISABLE_COPY_MOVE(QEXTWaveChart)
};


#endif // _QEXTWAVECHART_H
