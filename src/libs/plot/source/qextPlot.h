#ifndef _QEXTPLOT_H
#define _QEXTPLOT_H

#include <qextRange.h>
#include <qextPlotGlobal.h>
#include <qextSerializable.h>
#include <qextPropertyModel.h>

#include <qwt_plot.h>

#include <QPointer>

class QExtPlotAutoRangeUpdater : public QObject
{
    Q_OBJECT
public:
    QExtPlotAutoRangeUpdater(bool enable = false) : mEnable(enable) {}
    virtual ~QExtPlotAutoRangeUpdater() {}

    bool isEnabled() const { return mEnable; }
    void setEnable(bool enable)
    {
        if (enable != mEnable)
        {
            mEnable = enable;
            this->onEnableChanged(enable);
            Q_EMIT this->enableChanged(enable);
        }
    }

    virtual QString labelText() const { return tr("Auto Scale"); }

    virtual void updateRange()
    {
        this->onEnableChanged(mEnable);
    }

Q_SIGNALS:
    void enableChanged(bool enable);

protected:
    virtual void onEnableChanged(bool enable) { Q_UNUSED(enable); }

private:
    bool mEnable;
};

class QExtPlotPrivate;
class QEXT_PLOT_API QExtPlot : public QwtPlot, public QExtSerializable
{
    Q_OBJECT
public:
    typedef QSharedPointer<QExtPlot> SharedPtr;

    explicit QExtPlot(QWidget *parent = QEXT_NULLPTR);
    explicit QExtPlot(QExtPlotPrivate *d, QWidget *parent = QEXT_NULLPTR);
    explicit QExtPlot(const QwtText &title, QWidget *parent = QEXT_NULLPTR);
    ~QExtPlot() QEXT_OVERRIDE;

    qint64 id() const;
    QString name() const;
    QString groupName() const;

    double plotWidth() const;
    void setPlotWidth(double width);

    bool isPlotVisible() const;
    void setPlotVisible(bool visiable);

    bool isXAxisGridVisible() const;
    void setXAxisGridVisible(bool visible);

    bool isYAxisGridVisible() const;
    void setYAxisGridVisible(bool visible);

    bool isXAxisMinorGridVisible() const;
    void setXAxisMinorGridVisible(bool visible);

    bool isYAxisMinorGridVisible() const;
    void setYAxisMinorGridVisible(bool visible);

    double xAxisMin() const;
    double xAxisMax() const;
    QExtRangeF xAxisRange() const;
    void setXAxisMin(double value);
    void setXAxisMax(double value);
    QString xAxisRangeText() const;
    void setXAxisRange(double min, double max);
    void setXAxisRange(const QExtRangeF &range) { this->setXAxisRange(range.min(), range.max()); }

    double yAxisMin() const;
    double yAxisMax() const;
    QExtRangeF yAxisRange() const;
    void setYAxisMin(double value);
    void setYAxisMax(double value);
    QString yAxisRangeText() const;
    void setYAxisRange(double min, double max);
    void setYAxisRange(const QExtRangeF &range) { this->setYAxisRange(range.min(), range.max()); }

    bool isXAxisAutoScaled() const;
    void setXAxisAutoScaled(bool autoScaled);
    QExtPlotAutoRangeUpdater *xAxisAutoRangeUpdater() const;
    void setXAxisAutoRangeUpdater(QExtPlotAutoRangeUpdater *updater);

    bool isYAxisAutoScaled() const;
    void setYAxisAutoScaled(bool autoScaled);
    QExtPlotAutoRangeUpdater *yAxisAutoRangeUpdater() const;
    void setYAxisAutoRangeUpdater(QExtPlotAutoRangeUpdater *updater);

    virtual bool initPlot(qint64 id, const QString &name = "", const QString &groupName = "");

    virtual QExtPropertyModel *propertyModel();
    virtual QExtPropertyDelegate *propertyDelegate(QObject *parent = QEXT_NULLPTR);

    virtual QString typeString() const;

    void serializeLoad(const SerializedItemsMap &items) QEXT_OVERRIDE;
    SerializedItemsMap serializeSave() const QEXT_OVERRIDE;

    static qint64 loadId(const SerializedItemsMap &items);
    static QString loadType(const SerializedItemsMap &items);
    static QString loadGroup(const SerializedItemsMap &items);

Q_SIGNALS:
    void plotPropertyChanged(const QString &propertyName);
    void plotAboutToBeDelete(QExtPlot *plot);
    void plotAliasChanged(QExtPlot *plot);
    void xAxisRangeChanged();
    void yAxisRangeChanged();

    void visibilityChanged(bool visible);
    void xAxisGridVisibleChanged(bool visible);
    void yAxisGridVisibleChanged(bool visible);
    void xAxisMinorGridVisibleChanged(bool visible);
    void yAxisMinorGridVisibleChanged(bool visible);

    void xAxisAutoScaleChanged(bool autoScaled);
    void yAxisAutoScaleChanged(bool autoScaled);

public Q_SLOTS:
    virtual void resetAxes();
    virtual void unzoom();

protected:
    virtual void initPropertyModel(QExtPropertyModel *propertyModel);

protected:
    QScopedPointer<QExtPlotPrivate> dd_ptr;
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPlot)
    QEXT_DISABLE_COPY_MOVE(QExtPlot)
};


class QExtPlotGridVisibleItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotGridVisibleItem(QExtPlot *plot);
    ~QExtPlotGridVisibleItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotGridVisibleItem)
};
class QExtPlotXAxisGridVisibleItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotXAxisGridVisibleItem(QExtPlot *plot);
    ~QExtPlotXAxisGridVisibleItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotXAxisGridVisibleItem)
};
class QExtPlotXAxisMinorGridVisibleItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotXAxisMinorGridVisibleItem(QExtPlot *plot);
    ~QExtPlotXAxisMinorGridVisibleItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotXAxisMinorGridVisibleItem)
};
class QExtPlotYAxisGridVisibleItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotYAxisGridVisibleItem(QExtPlot *plot);
    ~QExtPlotYAxisGridVisibleItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotYAxisGridVisibleItem)
};
class QExtPlotYAxisMinorGridVisibleItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotYAxisMinorGridVisibleItem(QExtPlot *plot);
    ~QExtPlotYAxisMinorGridVisibleItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotYAxisMinorGridVisibleItem)
};


class QExtPlotXAxisRangeItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotXAxisRangeItem(QExtPlot *plot);
    ~QExtPlotXAxisRangeItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotXAxisRangeItem)
};
class QExtPlotXAxisMinItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotXAxisMinItem(QExtPlot *plot);
    ~QExtPlotXAxisMinItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE { return Editor_DoubleSpinBox; }
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotXAxisMinItem)
};
class QExtPlotXAxisMaxItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotXAxisMaxItem(QExtPlot *plot);
    ~QExtPlotXAxisMaxItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE { return Editor_DoubleSpinBox; }
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotXAxisMaxItem)
};


class QExtPlotYAxisRangeItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotYAxisRangeItem(QExtPlot *plot);
    ~QExtPlotYAxisRangeItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotYAxisRangeItem)
};
class QExtPlotYAxisMinItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotYAxisMinItem(QExtPlot *plot);
    ~QExtPlotYAxisMinItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE { return Editor_DoubleSpinBox; }
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotYAxisMinItem)
};
class QExtPlotYAxisMaxItem : public QExtPropertyModelItem
{
    Q_OBJECT
public:
    QExtPlotYAxisMaxItem(QExtPlot *plot);
    ~QExtPlotYAxisMaxItem() QEXT_OVERRIDE {}

    QString name() const QEXT_OVERRIDE;
    Qt::ItemFlags flags() const QEXT_OVERRIDE;

    EditorEnum editorType() const QEXT_OVERRIDE { return Editor_DoubleSpinBox; }
    QWidget *initEditorProperty(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const QEXT_OVERRIDE;

    QVariant data(int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;

protected:
    QPointer<QExtPlot> mPlot;
    QEXT_DISABLE_COPY_MOVE(QExtPlotYAxisMaxItem)
};


#endif //_QEXTPLOT_H
