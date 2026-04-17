#include <QQmlApplicationEngine>
#include <QElapsedTimer>
#include <QApplication>
#include <QDebug>
#include <QTimer>

#include <qextCoreConfig.h>
#include <qextQmlConfig.h>
#include <qextQuickQwtPlot.h>
#include <qextQuickQwtPlotCurve.h>

#ifndef QEXT_BUILD_SHARED
#   include <qextQuickLoader.h>
#endif

class MYQExtQuickQwtPlot : public QExtQuickQwtPlot
{
    Q_OBJECT
public:
    MYQExtQuickQwtPlot(QQuickItem* parent = nullptr)
        : QExtQuickQwtPlot(parent)
    {
        mCurveData = new QExtQuickQwtPointSeriesData;
        mRingSeriesData = new QExtQuickQwtPointIndexRingSeriesData(10);
        mCurve.reset(new QExtQuickQwtPlotCurve("Curve 1"));
        mCurve->setPenColor(Qt::red);
        mCurve->pen()->setWidth(3);
        //    d->mCurve->setStyle(QExtQuickQwtPlotCurve::Style::Steps);
        //    d->mCurve->setAttribute(QExtQuickQwtPlotCurve::Attribute::Inverted);
        mCurve->setRenderHint(QExtQuickQwtPlotCurve::RenderHint::Antialiasing);
//        mCurve->setData(mCurveData);
        mCurve->setData(mRingSeriesData);
        mCurve->attach(dynamic_cast<QExtQuickQwtPlot*>(this));
        this->replotAndUpdate();
        connect(&mTimer, &QTimer::timeout, this, [=]()
        {
            static double t, U;
//            U = (static_cast<double>(QEXT_RANDOM_INT()) / RAND_MAX) * 5;
            U += 1;

            mRingSeriesData->addSamples(&U);
            mCurveData->append(QPointF(t, U));
            qDebug() << Q_FUNC_INFO << QString("Adding dot t = %1, S = %2").arg(t).arg(U);
            t++;
            this->replotAndUpdate();
        });
        mTimer.setInterval(500);
        mTimer.start();
//        this->setBackgroundColor(QColor(255, 255, 255, 50));
    }
    ~MYQExtQuickQwtPlot() override
    {
        mCurveData = nullptr;
    }

protected:
    QTimer mTimer;
    QScopedPointer<QExtQuickQwtPlotCurve> mCurve;
    QExtQuickQwtPointSeriesData *mCurveData{nullptr};
    QExtQuickQwtPointIndexRingSeriesData *mRingSeriesData{nullptr};
};

int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

#ifndef QEXT_BUILD_SHARED
    QExtQuickLoader::load(&engine);
#else
    qDebug() << "addImportPath:" << QML_MODULES_DIR;
    engine.addImportPath(QML_MODULES_DIR);
#endif

    qmlRegisterType<MYQExtQuickQwtPlot>("MYQExtQuickQwtPlot", 1, 1, "MYQExtQuickQwtPlot");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    qDebug() << "Startup time:" << timer.elapsed() << "ms";

    return app.exec();
}
#include <main.moc>
