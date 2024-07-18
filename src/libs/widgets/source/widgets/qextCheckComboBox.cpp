#include <qextCheckComboBox.h>

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

    QStringList m_itemList;
    QStringList m_checkLockItems;
    QSet<QString> m_checkedItems;

private:
    QEXT_DECL_PUBLIC(QExtCheckComboBoxModel)
    QEXT_DISABLE_COPY_MOVE(QExtCheckComboBoxModelPrivate)
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
        if (!m_checkedItems.contains(text))
        {
            m_checkedItems.insert(text);
            return true;
        }
    }
    else
    {
        if (m_checkedItems.contains(text))
        {
            m_checkedItems.remove(text);
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
    if (!d->m_checkLockItems.contains(d->m_itemList.at(index.row())))
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
            return d->m_itemList.at(index.row());
        }
        else if (Qt::CheckStateRole == role)
        {
            return d->m_checkedItems.contains(d->m_itemList.at(index.row())) ? Qt::Checked : Qt::Unchecked;
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
    QString text = d->m_itemList.at(index.row());
    if (!d->m_checkLockItems.contains(text))
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
    if (d->m_itemList.contains(text))
    {
        this->beginResetModel();
        d->m_itemList.removeOne(text);
        d->m_checkedItems.remove(text);
        this->endResetModel();
    }
}

QStringList QExtCheckComboBoxModel::checkedItems() const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->m_checkedItems.values();
}

bool QExtCheckComboBoxModel::isItemChecked(const QString &text) const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->m_checkedItems.contains(text);
}

void QExtCheckComboBoxModel::setItemChecked(const QString &text, bool checked)
{
    Q_D(QExtCheckComboBoxModel);
    if (!d->m_itemList.contains(text))
    {
        this->beginResetModel();
        d->m_itemList.append(text);
        this->endResetModel();
    }
    if (d->setCheckState(text, checked))
    {
        QModelIndex index = this->index(d->m_itemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

QStringList QExtCheckComboBoxModel::checkLockItems() const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->m_checkLockItems;
}

void QExtCheckComboBoxModel::removeCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBoxModel);
    if (d->m_checkLockItems.contains(text))
    {
        d->m_checkLockItems.removeOne(text);
        QModelIndex index = this->index(d->m_itemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

void QExtCheckComboBoxModel::appendCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBoxModel);
    if (!d->m_checkLockItems.contains(text))
    {
        d->m_checkLockItems.append(text);
        QModelIndex index = this->index(d->m_itemList.indexOf(text), 0);
        emit this->dataChanged(index, index);
    }
}

void QExtCheckComboBoxModel::setCheckLockItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBoxModel);
    if (texts != d->m_checkLockItems)
    {
        this->beginResetModel();
        d->m_checkLockItems = texts;
        this->endResetModel();
    }
}

int QExtCheckComboBoxModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const QExtCheckComboBoxModel);
    return d->m_itemList.size();
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

    QPointer<QExtCheckComboBoxLineEdit> m_lineEdit;
    QPointer<QExtCheckComboBoxModel> m_model;

private:
    QEXT_DECL_PUBLIC(QExtCheckComboBox)
    QEXT_DISABLE_COPY_MOVE(QExtCheckComboBoxPrivate)
};

QExtCheckComboBoxPrivate::QExtCheckComboBoxPrivate(QExtCheckComboBox *q)
    : q_ptr(q)
{
}

QExtCheckComboBoxPrivate::~QExtCheckComboBoxPrivate()
{
}

void QExtCheckComboBoxPrivate::updateText()
{
    m_lineEdit->setText(m_model->checkedItems().join(", "));
}

QExtCheckComboBox::QExtCheckComboBox(QWidget *parent)
    : QComboBox(parent)
    , dd_ptr(new QExtCheckComboBoxPrivate(this))
{
    Q_D(QExtCheckComboBox);
    d->m_model = new QExtCheckComboBoxModel(this);
    this->setModel(d->m_model.data());
    this->setView(new QListView(this));
    d->m_lineEdit = new QExtCheckComboBoxLineEdit(this);
    d->m_lineEdit->setReadOnly(true);
    connect(d->m_lineEdit.data(), SIGNAL(mouseRelease()), this, SLOT(showPopup()));
    this->setLineEdit(d->m_lineEdit.data());
    this->setProperty("readOnly", true);
}

QExtCheckComboBox::~QExtCheckComboBox()
{
}

QStringList QExtCheckComboBox::checkLockItems() const
{
    Q_D(const QExtCheckComboBox);
    return d->m_model.isNull() ? QStringList() : d->m_model->checkLockItems();
}

void QExtCheckComboBox::removeCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBox);
    if (!d->m_model.isNull())
    {
        d->m_model->removeCheckLockItem(text);
    }
}

void QExtCheckComboBox::appendCheckLockItem(const QString &text)
{
    Q_D(QExtCheckComboBox);
    if (!d->m_model.isNull())
    {
        d->m_model->appendCheckLockItem(text);
    }
}

void QExtCheckComboBox::setCheckLockItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBox);
    if (!d->m_model.isNull())
    {
        d->m_model->setCheckLockItems(texts);
    }
}

QStringList QExtCheckComboBox::checkedItems() const
{
    Q_D(const QExtCheckComboBox);
    return d->m_model.isNull() ? QStringList() : d->m_model->checkedItems();
}

void QExtCheckComboBox::setCheckedItems(const QStringList &texts)
{
    Q_D(QExtCheckComboBox);
    QStringList::ConstIterator iter;
    for (iter = texts.begin(); iter != texts.end(); ++iter)
    {
        d->m_model->setItemChecked((*iter), true);
    }
    d->updateText();
}

bool QExtCheckComboBox::isItemChecked(const QString &text)
{
    Q_D(const QExtCheckComboBox);
    return d->m_model.isNull() ? false : d->m_model->isItemChecked(text);
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
    if (!d->m_model.isNull())
    {
        d->m_model->setItemChecked(text, checked);
        d->updateText();
    }
}

void QExtCheckComboBox::hidePopup()
{
    QRect rect = this->rect();
    QAbstractItemModel *model = this->model();
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
        return true;
    }
    return QObject::eventFilter(watched, event);
}
