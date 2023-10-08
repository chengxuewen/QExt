#include <private/qextWaveChart_p.h>

#include <QPainter>
#include <QDebug>

QPainterPath QEXTSmoothCurveCreator::createSmoothCurve(const QVector<QPointF> &points)
{
    QPainterPath path;
    int len = points.size();
    if (len < 2) {
        return path;
    }

    QVector<QPointF> firstControlPoints;
    QVector<QPointF> secondControlPoints;
    calculateControlPoints(points, &firstControlPoints, &secondControlPoints);
    path.moveTo(points[0].x(), points[0].y());

    for (int i = 0; i < len - 1; ++i) {
        path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i + 1]);
    }

    return path;
}

void QEXTSmoothCurveCreator::calculateFirstControlPoints(double *&result, const double *rhs, int n)
{
    result = new double[n];
    double *tmp = new double[n];
    double b = 2.0;
    result[0] = rhs[0] / b;

    for (int i = 1; i < n; i++) {
        tmp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < n; i++) {
        result[n - i - 1] -= tmp[n - i] * result[n - i];
    }

    delete[] tmp;
}

void QEXTSmoothCurveCreator::calculateControlPoints(const QVector<QPointF> &knots, QVector<QPointF> *firstControlPoints, QVector<QPointF> *secondControlPoints)
{
    int n = knots.size() - 1;
    for (int i = 0; i < n; ++i) {
        firstControlPoints->append(QPointF());
        secondControlPoints->append(QPointF());
    }

    if (n == 1) {
        (*firstControlPoints)[0].rx() = (2 * knots[0].x() + knots[1].x()) / 3;
        (*firstControlPoints)[0].ry() = (2 * knots[0].y() + knots[1].y()) / 3;
        (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - knots[0].x();
        (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - knots[0].y();
        return;
    }

    double *xs = 0;
    double *ys = 0;
    double *rhsx = new double[n];
    double *rhsy = new double[n];

    for (int i = 1; i < n - 1; ++i) {
        rhsx[i] = 4 * knots[i].x() + 2 * knots[i + 1].x();
        rhsy[i] = 4 * knots[i].y() + 2 * knots[i + 1].y();
    }

    rhsx[0] = knots[0].x() + 2 * knots[1].x();
    rhsx[n - 1] = (8 * knots[n - 1].x() + knots[n].x()) / 2.0;
    rhsy[0] = knots[0].y() + 2 * knots[1].y();
    rhsy[n - 1] = (8 * knots[n - 1].y() + knots[n].y()) / 2.0;

    calculateFirstControlPoints(xs, rhsx, n);
    calculateFirstControlPoints(ys, rhsy, n);

    for (int i = 0; i < n; ++i) {
        (*firstControlPoints)[i].rx() = xs[i];
        (*firstControlPoints)[i].ry() = ys[i];

        if (i < n - 1) {
            (*secondControlPoints)[i].rx() = 2 * knots[i + 1].x() - xs[i + 1];
            (*secondControlPoints)[i].ry() = 2 * knots[i + 1].y() - ys[i + 1];
        } else {
            (*secondControlPoints)[i].rx() = (knots[n].x() + xs[n - 1]) / 2;
            (*secondControlPoints)[i].ry() = (knots[n].y() + ys[n - 1]) / 2;
        }
    }

    delete xs;
    delete ys;
    delete [] rhsx;
    delete [] rhsy;
}



QEXTWaveChartPrivate::QEXTWaveChartPrivate(QEXTWaveChart *q)
    : q_ptr(q)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_yAxisStep = 10;
    m_xAxisStep = 10;
    m_hLineStep = 10;
    m_vLineStep = 10;

    m_space = 40;
    m_title = "WaveChart";
    m_smooth = false;
    m_hLineVisible = true;
    m_vLineVisible = true;
    m_pointVisible = true;
    m_pointBackgroundVisible = true;
    m_titleVisible = true;

    m_backgroundStartColor = QColor(79, 79, 79);
    m_backgroundEndColor = QColor(51, 51, 51);
    m_textColor = QColor(250, 250, 250);
    m_pointColor = QColor(38, 114, 179);
}

QEXTWaveChartPrivate::~QEXTWaveChartPrivate()
{

}



QEXTWaveChart::QEXTWaveChart(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTWaveChartPrivate(this))
{

}

QEXTWaveChart::~QEXTWaveChart()
{

}

void QEXTWaveChart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    this->drawBackground(&painter);

    this->drawBox(&painter);

    this->drawText(&painter);

    this->drawTitle(&painter);

    this->drawPoint(&painter);
}

void QEXTWaveChart::drawBackground(QPainter *painter)
{
    Q_D(QEXTWaveChart);
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient topGradient(rect().topLeft(), rect().bottomLeft());
    topGradient.setColorAt(0.0, d->m_backgroundStartColor);
    topGradient.setColorAt(1.0, d->m_backgroundEndColor);
    painter->setBrush(topGradient);
    painter->drawRect(rect());
    painter->restore();
}

void QEXTWaveChart::drawBox(QPainter *painter)
{
    Q_D(QEXTWaveChart);
    painter->save();

    QPointF topLeftPoint(d->m_space, d->m_space);
    QPointF bottomRightPoint(this->width() - d->m_space / 2, this->height() - d->m_space / 2);
    painter->setPen(d->m_textColor);
    painter->setBrush(Qt::NoBrush);

    d->m_plotAreaRect = QRectF(topLeftPoint, bottomRightPoint);
    painter->drawRect(d->m_plotAreaRect);

    if (d->m_hLineVisible) {
        QPen pen(d->m_textColor, 1, Qt::DotLine);
        painter->setPen(pen);

        int step = (d->m_maxValue - d->m_minValue) / d->m_hLineStep;
        double increment = (double)d->m_plotAreaRect.height() / step;
        double startY = d->m_plotAreaRect.topLeft().y();

        for (int i = 0; i < step - 1; i++) {
            startY += increment;
            QPointF leftPoint(d->m_plotAreaRect.topLeft().x(), startY);
            QPointF rightPoint(d->m_plotAreaRect.topRight().x(), startY);
            painter->drawLine(leftPoint, rightPoint);
        }
    }
    if (d->m_vLineVisible) {
        QPen pen(d->m_textColor, 1, Qt::DotLine);
        painter->setPen(pen);

        int step = d->m_plotAreaRect.width() / d->m_vLineStep;
        double increment = (double)d->m_plotAreaRect.width() / step;
        double startX = d->m_plotAreaRect.bottomLeft().x();

        for (int i = 0; i < step - 1; i++) {
            startX += increment;
            QPointF topPoint(startX, d->m_plotAreaRect.topLeft().y());
            QPointF bottomPoint(startX, d->m_plotAreaRect.bottomLeft().y());
            painter->drawLine(topPoint, bottomPoint);
        }
    }

    painter->restore();
}

void QEXTWaveChart::drawText(QPainter *painter)
{
    Q_D(QEXTWaveChart);
    painter->save();

    painter->setPen(d->m_textColor);
    painter->setBrush(Qt::NoBrush);

    int step = (d->m_maxValue - d->m_minValue) / d->m_yAxisStep;
    int value = d->m_maxValue;
    double increment = (double)d->m_plotAreaRect.height() / step;
    double startY = d->m_plotAreaRect.topLeft().y();
    QString strValue;

    for (int i = 0; i <= step; i++) {
        strValue = QString("%1").arg(value);
        QRect strRect = this->fontMetrics().boundingRect(strValue);
        double textWidth = strRect.width();
        double textHeight = strRect.height();
        QPointF textPot(d->m_plotAreaRect.topLeft().x() - 5 - textWidth, startY + textHeight / 2);
        painter->drawText(textPot, strValue);
        value -= d->m_yAxisStep;
        startY += increment;
    }

    painter->restore();
}

void QEXTWaveChart::drawTitle(QPainter *painter)
{
    Q_D(QEXTWaveChart);
    if (!d->m_titleVisible)
    {
        return;
    }

    painter->save();

    painter->setPen(d->m_textColor);
    painter->setBrush(Qt::NoBrush);

    double titleX = (double)width() / 2;
    double titleY = d->m_space;
    QRect textRect = this->fontMetrics().boundingRect(d->m_title);
    double textWidth = textRect.width();
    double textHeight = textRect.height();

    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPixelSize(13);
    painter->setFont(titleFont);

    QPointF textPot(titleX - textWidth / 2, titleY / 2 + textHeight / 2);
    painter->drawText(textPot, d->m_title);

    painter->restore();
}

void QEXTWaveChart::drawPoint(QPainter *painter)
{
    Q_D(QEXTWaveChart);
    painter->save();

    double startX = d->m_plotAreaRect.topRight().x();
    QVector<QPointF> points;

    if (d->m_pointBackgroundVisible) {
        points.push_back(QPointF(startX, d->m_plotAreaRect.bottomRight().y()));
    }

    for (int i = 0; i < d->m_dataList.count(); i++) {
        QPointF dataPot(startX, d->m_plotAreaRect.bottomRight().y() - (double)d->m_dataList.at(i) * (d->m_plotAreaRect.height() / (d->m_maxValue - d->m_minValue)));
        points.push_back(dataPot);
        startX -= d->m_xAxisStep;
    }

    if (d->m_pointBackgroundVisible) {
        points.push_back(QPointF(startX, d->m_plotAreaRect.bottomRight().y()));
    }

    if (d->m_pointBackgroundVisible && points.count() <= 2) {
        painter->restore();
        return;
    }

    painter->setPen(d->m_pointColor);

    if (d->m_pointBackgroundVisible) {
        painter->setBrush(QColor(d->m_pointColor.red(), d->m_pointColor.green(), d->m_pointColor.blue(), 150));
        if (!d->m_smooth) {
            painter->drawPolygon(QPolygonF(points));
        }
    } else {
        painter->setBrush(Qt::NoBrush);
        if (!d->m_smooth) {
            painter->drawPolyline(QPolygonF(points));
        }
    }

    if (d->m_smooth) {
        QPainterPath path = QEXTSmoothCurveCreator::createSmoothCurve(points);
        painter->drawPath(path);
    }

    if (d->m_pointVisible) {
        for (int i = 0; i < points.count(); i++) {
            QPointF dataPot = points.at(i);
            painter->setBrush(d->m_pointColor);
            painter->drawEllipse(dataPot, 3, 3);
        }
    }

    painter->restore();
}

void QEXTWaveChart::updateData()
{
    Q_D(QEXTWaveChart);
    int count = d->m_plotAreaRect.width() / d->m_xAxisStep;
    int i = d->m_dataList.count() - count;

    if (i > 0) {
        d->m_dataList.remove(count, i);
    }

    update();
}

double QEXTWaveChart::minValue() const
{
    Q_D(const QEXTWaveChart);
    return d->m_minValue;
}

double QEXTWaveChart::maxValue() const
{
    Q_D(const QEXTWaveChart);
    return d->m_maxValue;
}

double QEXTWaveChart::xAxisStep() const
{
    Q_D(const QEXTWaveChart);
    return d->m_xAxisStep;
}

double QEXTWaveChart::yAxisStep() const
{
    Q_D(const QEXTWaveChart);
    return d->m_yAxisStep;
}

double QEXTWaveChart::hLineStep() const
{
    Q_D(const QEXTWaveChart);
    return d->m_hLineStep;
}

double QEXTWaveChart::vLineStep() const
{
    Q_D(const QEXTWaveChart);
    return d->m_vLineStep;
}

double QEXTWaveChart::space() const
{
    Q_D(const QEXTWaveChart);
    return d->m_space;
}

QString QEXTWaveChart::title() const
{
    Q_D(const QEXTWaveChart);
    return d->m_title;
}

bool QEXTWaveChart::smoothEnable() const
{
    Q_D(const QEXTWaveChart);
    return d->m_smooth;
}

bool QEXTWaveChart::titleVisible() const
{
    Q_D(const QEXTWaveChart);
    return d->m_titleVisible;
}

bool QEXTWaveChart::hLineVisible() const
{
    Q_D(const QEXTWaveChart);
    return d->m_hLineVisible;
}

bool QEXTWaveChart::vLineVisible() const
{
    Q_D(const QEXTWaveChart);
    return d->m_vLineVisible;
}

bool QEXTWaveChart::pointVisible() const
{
    Q_D(const QEXTWaveChart);
    return d->m_pointVisible;
}

bool QEXTWaveChart::pointBackgroundVisible() const
{
    Q_D(const QEXTWaveChart);
    return d->m_pointBackgroundVisible;
}

QColor QEXTWaveChart::backgroundStartColor() const
{
    Q_D(const QEXTWaveChart);
    return d->m_backgroundStartColor;
}

QColor QEXTWaveChart::backgroundEndColor() const
{
    Q_D(const QEXTWaveChart);
    return d->m_backgroundEndColor;
}

QColor QEXTWaveChart::textColor() const
{
    Q_D(const QEXTWaveChart);
    return d->m_textColor;
}

QColor QEXTWaveChart::pointColor() const
{
    Q_D(const QEXTWaveChart);
    return d->m_pointColor;
}

QSize QEXTWaveChart::sizeHint() const
{
    return QSize(500, 300);
}

QSize QEXTWaveChart::minimumSizeHint() const
{
    return QSize(200, 70);
}

void QEXTWaveChart::addData(double data)
{
    Q_D(QEXTWaveChart);
    d->m_dataList.push_front(data);
    this->updateData();
}

void QEXTWaveChart::setData(const QVector<double> &data)
{
    Q_D(QEXTWaveChart);
    if (data != d->m_dataList)
    {
        d->m_dataList = data;
        this->updateData();
    }
}

void QEXTWaveChart::clearData()
{
    Q_D(QEXTWaveChart);
    d->m_dataList.clear();
    this->update();
}

void QEXTWaveChart::setMinValue(double value)
{
    Q_D(QEXTWaveChart);
    if (d->m_minValue != value) {
        d->m_minValue = value;
        this->update();
    }
}

void QEXTWaveChart::setMaxValue(double value)
{
    Q_D(QEXTWaveChart);
    if (d->m_maxValue != value) {
        d->m_maxValue = value;
        this->update();
    }
}

void QEXTWaveChart::setXAxisStep(double step)
{
    Q_D(QEXTWaveChart);
    if (d->m_xAxisStep != step) {
        d->m_xAxisStep = step;
        this->update();
    }
}

void QEXTWaveChart::setYAxisStep(double step)
{
    Q_D(QEXTWaveChart);
    if (d->m_yAxisStep != step) {
        d->m_yAxisStep = step;
        this->update();
    }
}

void QEXTWaveChart::setHLineStep(double step)
{
    Q_D(QEXTWaveChart);
    if (d->m_hLineStep != step) {
        d->m_hLineStep = step;
        this->update();
    }
}

void QEXTWaveChart::setVLineStep(double step)
{
    Q_D(QEXTWaveChart);
    if (d->m_vLineStep != step) {
        d->m_vLineStep = step;
        this->update();
    }
}

void QEXTWaveChart::setSpace(double space)
{
    Q_D(QEXTWaveChart);
    if (d->m_space != space) {
        d->m_space = space;
        this->update();
    }
}

void QEXTWaveChart::setTitle(const QString &title)
{
    Q_D(QEXTWaveChart);
    if (d->m_title != title) {
        d->m_title = title;
        this->update();
    }
}

void QEXTWaveChart::setSmoothEnable(bool enable)
{
    Q_D(QEXTWaveChart);
    if (d->m_smooth != enable) {
        d->m_smooth = enable;
        this->update();
    }
}

void QEXTWaveChart::setTitleVisible(bool visiable)
{
    Q_D(QEXTWaveChart);
    if (d->m_titleVisible != visiable) {
        d->m_titleVisible = visiable;
        this->update();
    }
}

void QEXTWaveChart::setHLineVisible(bool visiable)
{
    Q_D(QEXTWaveChart);
    if (d->m_hLineVisible != visiable) {
        d->m_hLineVisible = visiable;
        this->update();
    }
}

void QEXTWaveChart::setVLineVisible(bool visiable)
{
    Q_D(QEXTWaveChart);
    if (d->m_vLineVisible != visiable) {
        d->m_vLineVisible = visiable;
        this->update();
    }
}

void QEXTWaveChart::setPointVisible(bool visiable)
{
    Q_D(QEXTWaveChart);
    if (d->m_pointVisible != visiable) {
        d->m_pointVisible = visiable;
        this->update();
    }
}

void QEXTWaveChart::setPointBackgroundVisible(bool visiable)
{
    Q_D(QEXTWaveChart);
    if (d->m_pointBackgroundVisible != visiable) {
        d->m_pointBackgroundVisible = visiable;
        this->update();
    }
}

void QEXTWaveChart::setBackgroundStartColor(const QColor &color)
{
    Q_D(QEXTWaveChart);
    if (d->m_backgroundStartColor != color) {
        d->m_backgroundStartColor = color;
        this->update();
    }
}

void QEXTWaveChart::setBackgroundEndColor(const QColor &color)
{
    Q_D(QEXTWaveChart);
    if (d->m_backgroundEndColor != color) {
        d->m_backgroundEndColor = color;
        this->update();
    }
}

void QEXTWaveChart::setTextColor(const QColor &color)
{
    Q_D(QEXTWaveChart);
    if (d->m_textColor != color) {
        d->m_textColor = color;
        this->update();
    }
}

void QEXTWaveChart::setPointColor(const QColor &color)
{
    Q_D(QEXTWaveChart);
    if (d->m_pointColor != color) {
        d->m_pointColor = color;
        this->update();
    }
}

