#include <qextPlotModel.h>
#include <qextPlotManager.h>
#include <qextPlotConstants.h>

#include <qwt_text.h>

#include <QDebug>
#include <QPointer>
#include <QSpinBox>
#include <QApplication>
#include <QInputMethodEvent>

class QExtPlotModelPrivate
{
    QExtPlotModel * const q_ptr;
    QEXT_DECL_PUBLIC(QExtPlotModel)
    QEXT_DISABLE_COPY_MOVE(QExtPlotModelPrivate)
public:
    explicit QExtPlotModelPrivate(QExtPlotModel *q);
    virtual ~QExtPlotModelPrivate();

    QPointer<QExtPlotManager> mPlotManager;
};

QExtPlotModelPrivate::QExtPlotModelPrivate(QExtPlotModel *q)
    : q_ptr(q)
{
}

QExtPlotModelPrivate::~QExtPlotModelPrivate()
{
}

QExtPlotModel::QExtPlotModel(QExtPlotManager *manager, QObject *parent)
    : QAbstractTableModel(parent)
    , dd_ptr(new QExtPlotModelPrivate(this))
{
    Q_D(QExtPlotModel);
    d->mPlotManager = manager;
    // connect(d->mPlotManager.data(), SIGNAL(plotAboutToBeSorted, this, &QExtPlotModel::onPlotAboutToBeSorted);
    // connect(d->mPlotManager.data(), &QExtPlotManager::plotSorted, this, &QExtPlotModel::onPlotSorted);
    connect(d->mPlotManager.data(), SIGNAL(plotAboutToBeRegistered(QExtPlot::SharedPtr)),
            this, SLOT(onPlotAboutToBeRegistered(QExtPlot::SharedPtr)));
    connect(d->mPlotManager.data(), SIGNAL(plotRegistered(QExtPlot::SharedPtr)),
            this, SLOT(onPlotRegistered(QExtPlot::SharedPtr)));
    connect(d->mPlotManager.data(), SIGNAL(plotAboutToBeUnregistered(QExtPlot::SharedPtr)),
            this, SLOT(onPlotAboutToBeUnregistered(QExtPlot::SharedPtr)));
    connect(d->mPlotManager.data(), SIGNAL(plotUnregistered(QExtPlot::SharedPtr)),
            this, SLOT(onPlotUnregistered(QExtPlot::SharedPtr)));
    connect(d->mPlotManager.data(), SIGNAL(plotPropertyChanged(QExtPlot::SharedPtr,QString)),
            this, SLOT(onPlotPropertyChanged(QExtPlot::SharedPtr,QString)));
}

QExtPlotModel::~QExtPlotModel()
{
}

int QExtPlotModel::rowCount(const QModelIndex &/*parent*/) const
{
    Q_D(const QExtPlotModel);
    return d->mPlotManager->plotCount();
}

int QExtPlotModel::columnCount(const QModelIndex &/*parent*/) const
{
    return ColumnEnumNum;
}

QVariant QExtPlotModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QExtPlotModel);
    // check index
    if (index.row() >= d->mPlotManager->plotCount() || index.row() < 0)
    {
        return QVariant();
    }

    QExtPlot::SharedPtr plot = d->mPlotManager->plot(index.row());
    switch (index.column())
    {
    case Column_Name:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->name();
        }
        break;
    }
    case Column_Title:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->title().text();
        }
        break;
    }
    case Column_Visibility:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->isPlotVisible() ? tr("Visible") : tr("Invisible");
        }
        else if (role == Qt::CheckStateRole)
        {
            return plot->isPlotVisible() ? Qt::Checked : Qt::Unchecked;
        }
        break;
    }
    case Column_Width:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->plotWidth();
        }
        break;
    }
    case Column_XAxisRange:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->xAxisRangeText();
        }
        break;
    }
    case Column_YAxisRange:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return plot->yAxisRangeText();
        }
        break;
    }
    default:
        break;
    }

    return QVariant();
}

bool QExtPlotModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(QExtPlotModel);
    // check index
    if (index.row() >= d->mPlotManager->plotCount() || index.row() < 0)
    {
        return false;
    }

    QExtPlot::SharedPtr plot = d->mPlotManager->plot(index.row());
    // set name
    bool ret = false;
    switch (index.column())
    {
    case Column_Title:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            plot->setTitle(value.toString());
            ret = true;
        }
        break;
    }
    case Column_Visibility:
    {
        if (role == Qt::CheckStateRole)
        {
            bool checked = value.toInt() == Qt::Checked;
            plot->setPlotVisible(checked);
            ret = true;
        }
        break;
    }
    case Column_Width:
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            plot->setPlotWidth(value.toDouble());
            ret = true;
        }
        break;
    }
    default:
        break;
    }

    if (ret)
    {
        emit this->dataChanged(index, index, QVector< int >({ role }));
    }

    return ret;
}

Qt::ItemFlags QExtPlotModel::flags(const QModelIndex &index) const
{
    switch (index.column())
    {
    case Column_Name:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_Title:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case Column_Visibility:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    case Column_Width:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    case Column_XAxisRange:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    case Column_YAxisRange:
        return Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    default:
        break;
    }

    return Qt::NoItemFlags;
}

QVariant QExtPlotModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_D(const QExtPlotModel);
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            if (section >= 0 && section < ColumnEnumNum)
            {
                return QExtPlotModel::columnTypeString(section);
            }
        }
    }
    else // vertical
    {
        if (section < d->mPlotManager->plotCount() && role == Qt::DisplayRole)
        {
            return QString::number(section + 1);
        }
    }

    return QVariant();
}

QExtPlot::SharedPtr QExtPlotModel::plot(int index) const
{
    Q_D(const QExtPlotModel);
    return d->mPlotManager->plot(index);
}

int QExtPlotModel::plotIndex(const QExtPlot::SharedPtr &plot) const
{
    Q_D(const QExtPlotModel);
    return d->mPlotManager->plotIndex(plot);
}

QList<QExtPlot::SharedPtr> QExtPlotModel::plotList() const
{
    Q_D(const QExtPlotModel);
    return d->mPlotManager->plotList();
}

QString QExtPlotModel::columnTypeString(int type, bool isEng)
{
    switch (type)
    {
    case Column_Name:
        return isEng ? "Name" : tr("Name");
    case Column_Title:
        return isEng ? "Title" : tr("Title");
    case Column_Width:
        return isEng ? "Width" : tr("Width");
    case Column_Visibility:
        return isEng ? "Visibility" : tr("Visibility");
    case Column_XAxisRange:
        return isEng ? "X Axis Range" : tr("X Axis Range");
    case Column_YAxisRange:
        return isEng ? "Y Axis Range" : tr("Y Axis Range");
    default:
        break;
    }
    return "";
}

void QExtPlotModel::onPlotAboutToBeSorted()
{
    this->beginResetModel();
}

void QExtPlotModel::onPlotSorted()
{
    this->endResetModel();
}

void QExtPlotModel::onPlotAboutToBeRegistered(const QExtPlot::SharedPtr &/*plot*/)
{
    this->beginResetModel();
}

void QExtPlotModel::onPlotRegistered(const QExtPlot::SharedPtr &/*plot*/)
{
    this->endResetModel();
}

void QExtPlotModel::onPlotAboutToBeUnregistered(const QExtPlot::SharedPtr &/*plot*/)
{
    this->beginResetModel();
}

void QExtPlotModel::onPlotUnregistered(const QExtPlot::SharedPtr &/*plot*/)
{
    this->endResetModel();
}

void QExtPlotModel::onPlotPropertyChanged(const QExtPlot::SharedPtr &plot, const QString &name)
{
    Q_D(QExtPlotModel);
    const int index = d->mPlotManager->plotIndex(plot);
    QModelIndex leftIndex  = this->index(index, 0);
    QModelIndex rightIndex  = this->index(index, Column_YAxisRange);
    emit this->dataChanged(leftIndex, rightIndex);
}


QWidget *QExtPlotItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    if (index.isValid())
    {
        switch (index.column())
        {
        case QExtPlotModel::Column_Width:
        {
            auto widget = new QSpinBox(parent);
            widget->setInputMethodHints(Qt::ImhDigitsOnly);
            widget->setRange(10, 999999999);
            return widget;
        }
        default:
            break;
        }
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void QExtPlotItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid())
    {
        switch (index.column())
        {
        case QExtPlotModel::Column_Width:
        {
            auto spinBox = qobject_cast< QSpinBox * >(editor);
            if (spinBox)
            {
                const auto width = index.model()->data(index, Qt::EditRole).toInt();
                spinBox->setValue(width);
            }
        }
        default:
            break;
        }
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void QExtPlotItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.isValid())
    {
        switch (index.column())
        {
        case QExtPlotModel::Column_Width:
        {
            auto spinBox = qobject_cast< QSpinBox * >(editor);
            if (spinBox)
            {
                model->setData(index, spinBox->value(), Qt::EditRole);
            }
            return;
        }
        default:
            break;
        }
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}
