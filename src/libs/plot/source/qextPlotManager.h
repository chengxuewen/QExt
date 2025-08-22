#ifndef _QEXTPLOTMANAGER_H
#define _QEXTPLOTMANAGER_H

#include <qextSingleton.h>
#include <qextPlotModel.h>
#include <qextPlotGroup.h>
#include <qextPlotFactory.h>
#include <qextSerializable.h>
#include <qextPlotConstants.h>

#include <QObject>

class QExtPlotManagerPrivate;
class QEXT_PLOT_API QExtPlotManager : public QExtSerializableObject, public QExtSingleton<QExtPlotManager>
{
    Q_OBJECT
    QEXT_DECLARE_SINGLETON(QExtPlotManager)
public:
    QExtPlotFactory &plotFactory();

    int plotCount() const;
    QExtPlot::SharedPtr plot(int index) const;
    QList<QExtPlot::SharedPtr> plotList() const;
    int plotIndex(const QExtPlot::SharedPtr &plot) const;

    QExtPlotGroup::SharedPtr plotGroup(const QString &name = "") const;

    bool isPlotSerializationConstructEnabled(const QExtPlot::SharedPtr &plot);
    void setPlotSerializationConstructEnable(const QExtPlot::SharedPtr &plot, bool enable);

    void unregisterPlot(const QExtPlot::SharedPtr &plot);
    QExtPlot::SharedPtr createRegisterPlot(const QString &type, qint64 id = 0, const QString &groupName = "");
    QExtPlot::SharedPtr createRegisterPlot(const QString &type, const QString &name, const QString &groupName = "");
    QExtPlotGroup::SharedPtr registerPlot(QExtPlot::SharedPtr &plot, qint64 id = 0, const QString &groupName = "")
    {
        return this->registerPlot(plot, id, "", groupName);
    }
    QExtPlotGroup::SharedPtr registerPlot(QExtPlot::SharedPtr &plot, const QString &name, const QString &groupName = "")
    {
        return this->registerPlot(plot, 0, name, groupName);
    }
    QExtPlotGroup::SharedPtr registerPlot(QExtPlot::SharedPtr &plot, qint64 id, const QString &name, const QString &groupName);

    QExtPlotModel *makePlotModel(QObject *parent = QEXT_NULLPTR);

    SerializedItemsMap plotSerializedItems(const QString &tag) const;

    void serializeLoad(const SerializedItemsMap &items) QEXT_OVERRIDE;
    SerializedItemsMap serializeSave() const QEXT_OVERRIDE;

Q_SIGNALS:
    void plotAboutToBeRegistered(const QExtPlot::SharedPtr &plot);
    void plotRegistered(const QExtPlot::SharedPtr &plot);
    void plotAboutToBeUnregistered(const QExtPlot::SharedPtr &plot);
    void plotUnregistered(const QExtPlot::SharedPtr &plot);

    void plotGroupAboutToBeCreated(const QExtPlotGroup::SharedPtr &plotGroup);
    void plotGroupCreated(const QExtPlotGroup::SharedPtr &plotGroup);
    void plotGroupAboutToBeDestroyed(const QExtPlotGroup::SharedPtr &plotGroup);
    void plotGroupDestroyed(const QExtPlotGroup::SharedPtr &plotGroup);

    void plotListChanged(const QList<QExtPlot::SharedPtr> &plotList);
    void plotPropertyChanged(const QExtPlot::SharedPtr &plot, const QString &name);

protected:
    explicit QExtPlotManager(QObject *parent = QEXT_NULLPTR);
    ~QExtPlotManager() QEXT_OVERRIDE;

    void onAboutToBeDestroyed() QEXT_OVERRIDE;

private:
    QScopedPointer<QExtPlotManagerPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPlotManager)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotManager)
};

#define qextPlotManager QExtPlotManager::instance();

#endif // _QEXTPLOTMANAGER_H
