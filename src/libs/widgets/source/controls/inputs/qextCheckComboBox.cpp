#include "qextCheckComboBox.h"

#include <QDebug>
#include <QEvent>
#include <QScreen>
#include <QPointer>
#include <QLineEdit>
#include <QMouseEvent>
#include <QListWidget>
#include <QApplication>
#include <QAbstractItemView>

class QExtCheckComboBoxModelPrivate
{
public:
    explicit QExtCheckComboBoxModelPrivate(QExtCheckComboBoxModel *q);
    virtual ~QExtCheckComboBoxModelPrivate();

    bool setCheckState(const QString &text, bool checked);

    QExtCheckComboBoxModel * q_ptr;

    QStringList mItemList;
    QStringList mCheckLockItems;
    QSet<QString> mCheckedItems;

private:
    QEXT_DECLARE_PUBLIC(QExtCheckComboBoxModel)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtCheckComboBoxModelPrivate)
};

QExtCheckComboBoxModelPrivate::QExtCheckComboBoxModelPrivate(QExtCheckComboBoxModel *q)
    : q_ptr(q)
{
}

QExtCheckComboBoxModelPrivate::~QExtCheckComboBoxModelPrivate()
{
}

bool QExtCheckComboBoxModelPrivate::setCheckState(const QString &text, bool checked)
{
    if (checked)
    {
        if (!mCheckedItems.contains(text))
        {
            mCheckedItems.insert(text);
            return true;
        }
    }
    else
    {
        if (mCheckedItems.contains(text))
        {
            mCheckedItems.remove(text);
            return true;
        }
    }
    return false;
}

QExtCheckComboBoxModel::QExtCheckComboBoxModel(QObject *parent)
    : QAbstractListModel(parent)
    , dd_ptr(new QExtCheckComboBoxModelPrivate(this))
{
}

QExtCheckComboBoxModel::~QExtCheckComboBoxModel()
{
}

Qt::ItemFlags QExtCheckComboBoxModel::flags(const QModelIndex &index) const
{
    Q_D(const QExtCheckComboBoxModel);
    if (!d->mCheckLockItems.contains(d->mItemList.at(index.row())))
    {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    return Qt::ItemIsEnabled;
}

QVariant QExtCheckComboBoxModel::data(const QModelIndex &index, int role) const
{
    Q_D(const QExtCheckComboBoxModel);
    if (index.isValid())
    {
        if (Qt::DisplayRole == role || Qt::EditRole == role)
        {
            return d->mItemList.at(index.row());
        }
        else if (Qt::CheckStateRole == role)
        {
            return d->mCheckedItems.contains(d->mItemList.at(index.row())) ? Qt::Checked : Qt::Unchecked;
        }
    }
    return QVariant();
}

bool QExtCheckComboBoxModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(QExtCheckComboBoxModel);
    if (!index.isValid())
    {
        return false;
    }

    bool ret = false;
    QString text = d->mItemList.at(index.row());
    if (!d->mCheckLockItems.contains(text))
    {
        if (Qt::CheckStateRole == role)
        {
            bool checked = value.toInt() == Qt::Checked;
            ret = d->setCheckState(text, checked);
        }
    }
    if (ret)
    {
        emit this->dataChanged(index, index, QVector<int>() << role);
    }
    return ret;
}

void QExtCheckComboBoxModel::removeItem(const QString &text)
{
    Q_D(QExtCheckComboBoxModel);
    if (d->mItemList.contains(text))
    {
        this->beginResetModel();
        d->mItemList.removeOne(text);
        d->mCheckedItems.remove(text);
        this->endResetModel();
    }
}

QStringList QExtCheckComboBoxModel::checkedItems() const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->mCheckedItems.values();
}

bool QExtCheckComboBoxModel::isItemChecked(const QString &text) const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->mCheckedItems.contains(text);
}

void QExtCheckComboBoxModel::setItemChecked(const QString &text, bool checked)
{
    Q_D(QExtCheckComboBoxModel);
    if (!d->mItemList.contains(text))
    {
        this->beginResetModel();
        d->mItemList.append(text);
        this->endResetModel();
    }
    if (d->setCheckState(text, checked))
    {
        QModelIndex index = this->index(d->mItemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

QStringList QExtCheckComboBoxModel::checkLockItems() const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->mCheckLockItems;
}

void QExtCheckComboBoxModel::removeCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBoxModel);
    if (d->mCheckLockItems.contains(text))
    {
        d->mCheckLockItems.removeOne(text);
        QModelIndex index = this->index(d->mItemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

void QExtCheckComboBoxModel::appendCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBoxModel);
    if (!d->mCheckLockItems.contains(text))
    {
        d->mCheckLockItems.append(text);
        QModelIndex index = this->index(d->mItemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

void QExtCheckComboBoxModel::setCheckLockItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBoxModel);
    if (texts != d->mCheckLockItems)
    {
        this->beginResetModel();
        d->mCheckLockItems = texts;
        this->endResetModel();
    }
}

int QExtCheckComboBoxModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->mItemList.size();
}

int QExtCheckComboBoxModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


class QExtCheckComboBoxPrivate
{
public:
    explicit QExtCheckComboBoxPrivate(QExtCheckComboBox *q);
    virtual ~QExtCheckComboBoxPrivate();

    void updateText();

    QExtCheckComboBox * const q_ptr;

    bool mSingleSelectModeEnabled;
    QPointer<QExtCheckComboBoxModel> mModel;
    QPointer<QExtCheckComboBoxLineEdit> mLineEdit;

private:
    QEXT_DECLARE_PUBLIC(QExtCheckComboBox)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtCheckComboBoxPrivate)
};

QExtCheckComboBoxPrivate::QExtCheckComboBoxPrivate(QExtCheckComboBox *q)
    : q_ptr(q)
{
    mSingleSelectModeEnabled = false;
}

QExtCheckComboBoxPrivate::~QExtCheckComboBoxPrivate()
{
}

void QExtCheckComboBoxPrivate::updateText()
{
    mLineEdit->setText(mModel->checkedItems().join(", "));
}

QExtCheckComboBox::QExtCheckComboBox(QWidget *parent)
    : QComboBox(parent)
    , dd_ptr(new QExtCheckComboBoxPrivate(this))
{
    Q_D(QExtCheckComboBox);
    d->mModel = new QExtCheckComboBoxModel(this);
    this->setModel(d->mModel.data());
    this->setView(new QListView(this));
    d->mLineEdit = new QExtCheckComboBoxLineEdit(this);
    d->mLineEdit->setReadOnly(true);
    connect(d->mLineEdit.data(), SIGNAL(mouseRelease()), this, SLOT(showPopup()));
    this->setLineEdit(d->mLineEdit.data());
    this->setProperty("readOnly", true);
}

QExtCheckComboBox::~QExtCheckComboBox()
{
}

bool QExtCheckComboBox::isSingleSelectModeEnabled() const
{
    Q_D(const QExtCheckComboBox);
    return d->mSingleSelectModeEnabled;
}

void QExtCheckComboBox::setSingleSelectModeEnabled(bool enable)
{
    Q_D(QExtCheckComboBox);
    if (enable != d->mSingleSelectModeEnabled)
    {
        d->mSingleSelectModeEnabled = enable;
        emit this->singleSelectModeEnabledChanged(enable);
    }
}

QStringList QExtCheckComboBox::checkLockItems() const
{
    Q_D(const QExtCheckComboBox);
    return d->mModel.isNull() ? QStringList() : d->mModel->checkLockItems();
}

void QExtCheckComboBox::removeCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBox);
    if (!d->mModel.isNull())
    {
        d->mModel->removeCheckLockItem(text);
    }
}

void QExtCheckComboBox::appendCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBox);
    if (!d->mModel.isNull())
    {
        d->mModel->appendCheckLockItem(text);
    }
}

void QExtCheckComboBox::setCheckLockItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBox);
    if (!d->mModel.isNull())
    {
        d->mModel->setCheckLockItems(texts);
    }
}

QStringList QExtCheckComboBox::checkedItems() const
{
    Q_D(const QExtCheckComboBox);
    return d->mModel.isNull() ? QStringList() : d->mModel->checkedItems();
}

void QExtCheckComboBox::setCheckedItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBox);
    QStringList::ConstIterator iter;
    for (iter = texts.begin(); iter != texts.end(); ++iter)
    {
        d->mModel->setItemChecked((*iter), true);
    }
    d->updateText();
}

bool QExtCheckComboBox::isItemChecked(const QString &text)
{
    Q_D(const QExtCheckComboBox);
    return d->mModel.isNull() ? false : d->mModel->isItemChecked(text);
}

void QExtCheckComboBox::setItemChecked(const QString &text, bool checked)
{
    this->addItem(text, checked);
}

void QExtCheckComboBox::addItems(const QStringList &texts)
{
    QStringList::ConstIterator iter;
    for (iter = texts.begin(); iter != texts.end(); ++iter)
    {
        this->addItem((*iter));
    }
}

void QExtCheckComboBox::addItem(const QString &text, bool checked)
{
    Q_D(QExtCheckComboBox);
    if (!d->mModel.isNull())
    {
        d->mModel->setItemChecked(text, checked);
        d->updateText();
    }
}

void QExtCheckComboBox::hidePopup()
{
    // QRect rect = this->rect();
    // QAbstractItemModel *model = this->model();
    QAbstractItemView *itemView = this->view();
    QPoint cursorPoint = itemView->mapFromGlobal(QCursor::pos());
    QRect viewRect = itemView->rect();

    // hidePopup if mouse pos in edit rect of combobox
    itemView->viewport()->update();
    if (!viewRect.contains(cursorPoint))
    {
        QComboBox::hidePopup();
        this->update();
        return;
    }
    // is parentWidget inVisible, set hidePopup
    QWidget *parentWidget = dynamic_cast<QWidget*>(this->parent());
    if (!parentWidget->isVisible())
    {
        QComboBox::hidePopup();
        this->update();
        return;
    }
}

void QExtCheckComboBox::showPopup()
{
    Q_D(QExtCheckComboBox);
    QStyle * const style = this->style();
    QStyleOptionComboBox opt;
    this->initStyleOption(&opt);
    QRect listRect(style->subControlRect(QStyle::CC_ComboBox, &opt,
                                         QStyle::SC_ComboBoxListBoxPopup, this));
    QPoint below = mapToGlobal(listRect.bottomLeft()); //left_bottom pos
    QScreen *screen = qApp->screenAt(below);
    if (!screen)
    {
        screen = qApp->primaryScreen();
    }
    QRect screenRect = screen->geometry();
    QWidget *topWidget = QApplication::topLevelAt(QCursor::pos());
    if (!topWidget)
    {
        QComboBox::showPopup();
        d->updateText();
        return;
    }
    QRect topWidgetRect = topWidget->rect();
    QPoint topWidgetPoint = topWidget->mapToGlobal(QPoint(0, 0));
    int toScreenBottom = screenRect.height() - below.y();
    int toWidgetBottom = topWidgetPoint.y() + topWidgetRect.height() - below.y();
    int showCount = qMin(toScreenBottom, toWidgetBottom) / 30;
    if (showCount >= 10)
    {
        this->setMaxVisibleItems(showCount);
    }
    else
    {
        this->setMaxVisibleItems(10);
    }
    QComboBox::showPopup();
    d->updateText();
}

void QExtCheckComboBox::setModel(QAbstractItemModel *model)
{
    QComboBox::setModel(model);
}

void QExtCheckComboBox::setView(QAbstractItemView *itemView)
{
    QComboBox::setView(itemView);
    this->view()->viewport()->installEventFilter(this);
}

bool QExtCheckComboBox::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QExtCheckComboBox);
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QModelIndex index = this->view()->indexAt(((QMouseEvent*)event)->pos());
        bool checked = Qt::Checked == this->view()->model()->data(index, Qt::CheckStateRole).toInt();
        this->view()->model()->setData(index, !checked ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
        d->updateText();
        if (d->mSingleSelectModeEnabled)
        {
            QComboBox::hidePopup();
            this->update();
        }
        return true;
    }
    return QObject::eventFilter(watched, event);
}
