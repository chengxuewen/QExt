#include <qextMvvmGraphInfoFormatter.h>
#include <qextMvvmUtils.h>
#include <qcustomplot.h>
#include <sstream>



namespace
{

    QCPGraph *qextMvvmFindGraphNearby(QCustomPlot *custom_plot, double x, double y)
    {
        double widget_px = custom_plot->xAxis->coordToPixel(x);
        double widget_py = custom_plot->yAxis->coordToPixel(y);
        return dynamic_cast<QCPGraph *>(custom_plot->plottableAt(QPointF(widget_px, widget_py)));
    }

    int qextMvvmGetBin(const QCPGraph *graph, double x)
    {
        const int key_start = graph->findBegin(x);
        const int key_end = graph->findBegin(x, false); // false = do not expand range
        if (key_end == key_start || key_end == graph->dataCount())
        {
            return key_start;
        }
        return (x - graph->dataSortKey(key_start)) <= (graph->dataSortKey(key_end) - x) ? key_start
               : key_end;
    }

    struct Context
    {
        double xPos{0.0};
        double yPos{0.0};
        bool closeToGraph{false};
        int nx{0};
        double value{0.0};
    };

    QString qextMvvmComposeString(const Context &context)
    {
        QString string;
        string += "[x: " + QString::number(context.xPos, 'g', 3) + ", ";
        string += "y: " + QString::number(context.yPos, 'g', 3) + "] ";
        if (context.closeToGraph)
        {
            string += "[binx: " + QString::number(context.nx) + "] ";
            string += "[value: " + QString::number(context.value, 'e', 6) + "]";
        }
        return string;
    }

} // namespace

QString QEXTMvvmGraphInfoFormatter::statusString(QCustomPlot *custom_plot, double x, double y) const
{
    Context context{x, y};
    QCPGraph *qcpGraph = qextMvvmFindGraphNearby(custom_plot, x, y);
    if (qcpGraph)
    {
        context.closeToGraph = true;
        context.nx = qextMvvmGetBin(qcpGraph, x);
        context.value = qcpGraph->dataMainValue(context.nx);
    }

    return qextMvvmComposeString(context);
}
