#ifndef _QEXTPLOTMODEL_H
#define _QEXTPLOTMODEL_H

#include <qextPlot.h>

#include <QAbstractTableModel>
#include <QStyledItemDelegate>

class QExtPlot;
class QExtPlotManager;
class QExtPlotModelPrivate;
class QEXT_PLOT_API QExtPlotModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum ColumnEnum
    {
        Column_Name = 0,
        Column_Title,
        Column_Width,
        Column_Visibility,
        Column_XAxisRange,
        Column_YAxisRange,
    };
    QEXT_STATIC_CONSTANT_NUMBER(ColumnEnumNum, 6)

    QExtPlotModel(QExtPlotManager *manager, QObject *parent = QEXT_NULLPTR);
    ~QExtPlotModel() QEXT_OVERRIDE;

    // implemented from QAbstractItemModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const QEXT_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const QEXT_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) QEXT_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const QEXT_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const QEXT_OVERRIDE;

    QExtPlot::SharedPtr plot(int index) const;
    int plotIndex(const QExtPlot::SharedPtr &plot) const;
    QList<QExtPlot::SharedPtr> plotList() const;

    static QString columnTypeString(int type, bool isEng = false);

protected slots:
    void onPlotAboutToBeSorted();
    void onPlotSorted();

    void onPlotAboutToBeRegistered(const QExtPlot::SharedPtr &plot);
    void onPlotRegistered(const QExtPlot::SharedPtr &plot);

    void onPlotAboutToBeUnregistered(const QExtPlot::SharedPtr &plot);
    void onPlotUnregistered(const QExtPlot::SharedPtr &plot);

    void onPlotPropertyChanged(const QExtPlot::SharedPtr &plot, const QString &name);

protected:
    QScopedPointer<QExtPlotModelPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtPlotModel)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtPlotModel)
};


class QEXT_PLOT_API QExtPlotItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QExtPlotItemDelegate(QObject *parent = QEXT_NULLPTR) : QStyledItemDelegate(parent) {}
    ~QExtPlotItemDelegate() QEXT_OVERRIDE {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const QEXT_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const QEXT_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_OVERRIDE
    {
        return QStyledItemDelegate::sizeHint(option, index) + QSize(10, 0);
    }
};

#endif // _QEXTPLOTMODEL_H
