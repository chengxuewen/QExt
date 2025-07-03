#ifndef _QEXTPLOTGROUP_H
#define _QEXTPLOTGROUP_H

#include <qextPlot.h>
#include <qextSerializable.h>

#include <QObject>

class QExtPlotGroupPrivate;
class QEXT_PLOT_API QExtPlotGroup : public QExtSerializableObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtPlotGroup> SharedPtr;

    QExtPlotGroup(const QString &name, QObject *parent = QEXT_NULLPTR);
    ~QExtPlotGroup() QEXT_OVERRIDE;

    QString name() const;

    QExtPlot::SharedPtr plot(qint64 id) const;
    QList<QExtPlot::SharedPtr> plotList() const;

    void insert(const QExtPlot::SharedPtr &plot);
    void remove(const QExtPlot::SharedPtr &plot);

    bool contains(qint64 plotId) const;
    bool contains(const QExtPlot::SharedPtr &plot) const;

    void serializeLoad(const SerializedItems &items) QEXT_OVERRIDE;
    SerializedItems serializeSave() const QEXT_OVERRIDE;

Q_SIGNALS:
    void plotAboutToBeInserted(const QExtPlot::SharedPtr &plot);
    void plotInserted(const QExtPlot::SharedPtr &plot);

    void plotAboutToBeRemoved(const QExtPlot::SharedPtr &plot);
    void plotRemoved(const QExtPlot::SharedPtr &plot);

    void plotListChanged(const QList<QExtPlot::SharedPtr> &plotList);
    void plotPropertyChanged(const QExtPlot::SharedPtr &plot, const QString &name);

protected:
    QScopedPointer<QExtPlotGroupPrivate> dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtPlotGroup)
    QEXT_DISABLE_COPY_MOVE(QExtPlotGroup)
};

#endif // _QEXTPLOTGROUP_H
