#include <qextMvvmColorMapInfoFormatter.h>
#include <qextMvvmUtils.h>

#include <qcustomplot.h>

namespace
{
    QCPColorMap *qextMvvmFindColorMap(QCustomPlot *customPlot)
    {
        for (int i = 0; i < customPlot->plottableCount(); ++i)
        {
            QCPColorMap *plottable = dynamic_cast<QCPColorMap *>(customPlot->plottable());
            if (plottable)
            {
                return plottable;
            }
        }

        return QEXT_DECL_NULLPTR;
    }

    struct Context
    {
        Context() : xPos(0.0), yPos(0.0), nx(0.0), ny(0.0), value(0.0) { }
        double xPos;
        double yPos;
        int nx;
        int ny;
        double value;
    };

    QString qextMvvmComposeString(const Context &context)
    {
        QString string;
        string += "[x: " + QString::number(context.xPos, 'g', 3) + ", ";
        string += "y: " + QString::number(context.yPos, 'g', 3) + "] ";
        string += "[binx: " + QString::number(context.nx) + ", ";
        string += "biny: " + QString::number(context.ny) + "] ";
        string += "[value: " + QString::number(context.value, 'e', 6) + "]";
        return string;
    }
} // namespace

QString QEXTMvvmColorMapInfoFormatter::statusString(QCustomPlot *customPlot, double x, double y) const
{
    // shall we provide caching here?
    QCPColorMap *colorMap = qextMvvmFindColorMap(customPlot);
    Context context;
    context.xPos = x;
    context.yPos = y;

    colorMap->data()->coordToCell(x, y, &context.nx, &context.ny);
    context.value = colorMap->data()->cell(context.nx, context.ny);

    return qextMvvmComposeString(context);
}
