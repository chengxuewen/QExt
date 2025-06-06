#include <qextPEPropertyGroupBoxEditor.h>

#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>

class QExtPEPropertyGroupBoxEditorPrivate
{
    QExtPEPropertyGroupBoxEditor *q_ptr;
    Q_DECLARE_PUBLIC(QExtPEPropertyGroupBoxEditor)
public:

    void init(QWidget *parent);

    void propertyInserted(QExtPEPropertyItem *index, QExtPEPropertyItem *afterIndex);
    void propertyRemoved(QExtPEPropertyItem *index);
    void propertyChanged(QExtPEPropertyItem *index);
    QWidget *createEditor(QExtPEProperty *property, QWidget *parent) const
    { return q_ptr->createEditor(property, parent); }

    void slotEditorDestroyed();
    void slotUpdate();

    struct WidgetItem
    {
        WidgetItem() : widget(QEXT_NULLPTR), label(QEXT_NULLPTR), widgetLabel(QEXT_NULLPTR),
            groupBox(QEXT_NULLPTR), layout(QEXT_NULLPTR), line(QEXT_NULLPTR), parent(QEXT_NULLPTR) { }
        QWidget *widget; // can be null
        QLabel *label;
        QLabel *widgetLabel;
        QGroupBox *groupBox;
        QGridLayout *layout;
        QFrame *line;
        WidgetItem *parent;
        QList<WidgetItem *> children;
    };
private:
    void updateLater();
    void updateItem(WidgetItem *item);
    void insertRow(QGridLayout *layout, int row) const;
    void removeRow(QGridLayout *layout, int row) const;

    bool hasHeader(WidgetItem *item) const;

    QMap<QExtPEPropertyItem *, WidgetItem *> m_indexToItem;
    QMap<WidgetItem *, QExtPEPropertyItem *> m_itemToIndex;
    QMap<QWidget *, WidgetItem *> m_widgetToItem;
    QGridLayout *m_mainLayout;
    QList<WidgetItem *> m_children;
    QList<WidgetItem *> m_recreateQueue;
};

void QExtPEPropertyGroupBoxEditorPrivate::init(QWidget *parent)
{
    m_mainLayout = new QGridLayout();
    parent->setLayout(m_mainLayout);
    QLayoutItem *item = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(item, 0, 0);
}

void QExtPEPropertyGroupBoxEditorPrivate::slotEditorDestroyed()
{
    QWidget *editor = qobject_cast<QWidget *>(q_ptr->sender());
    if (!editor)
    {
        return;
    }
    if (!m_widgetToItem.contains(editor))
    {
        return;
    }
    m_widgetToItem[editor]->widget = QEXT_NULLPTR;
    m_widgetToItem.remove(editor);
}

void QExtPEPropertyGroupBoxEditorPrivate::slotUpdate()
{
    QListIterator<WidgetItem *> itItem(m_recreateQueue);
    while (itItem.hasNext())
    {
        WidgetItem *item = itItem.next();

        WidgetItem *par = item->parent;
        QWidget *w = QEXT_NULLPTR;
        QGridLayout *l = QEXT_NULLPTR;
        int oldRow = -1;
        if (!par)
        {
            w = q_ptr;
            l = m_mainLayout;
            oldRow = m_children.indexOf(item);
        }
        else
        {
            w = par->groupBox;
            l = par->layout;
            oldRow = par->children.indexOf(item);
            if (this->hasHeader(par))
            {
                oldRow += 2;
            }
        }

        if (item->widget)
        {
            item->widget->setParent(w);
        }
        else if (item->widgetLabel)
        {
            item->widgetLabel->setParent(w);
        }
        else
        {
            item->widgetLabel = new QLabel(w);
            item->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
            item->widgetLabel->setTextFormat(Qt::PlainText);
        }
        int span = 1;
        if (item->widget)
        {
            l->addWidget(item->widget, oldRow, 1, 1, 1);
        }
        else if (item->widgetLabel)
        {
            l->addWidget(item->widgetLabel, oldRow, 1, 1, 1);
        }
        else
        {
            span = 2;
        }
        item->label = new QLabel(w);
        item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        l->addWidget(item->label, oldRow, 0, 1, span);

        this->updateItem(item);
    }
    m_recreateQueue.clear();
}

void QExtPEPropertyGroupBoxEditorPrivate::updateLater()
{
    QTimer::singleShot(0, q_ptr, SLOT(slotUpdate()));
}

void QExtPEPropertyGroupBoxEditorPrivate::propertyInserted(QExtPEPropertyItem *index, QExtPEPropertyItem *afterIndex)
{
    WidgetItem *afterItem = m_indexToItem.value(afterIndex);
    WidgetItem *parentItem = m_indexToItem.value(index->parent());

    WidgetItem *newItem = new WidgetItem();
    newItem->parent = parentItem;

    QGridLayout *layout = QEXT_NULLPTR;
    QWidget *parentWidget = QEXT_NULLPTR;
    int row = -1;
    if (!afterItem)
    {
        row = 0;
        if (parentItem)
        {
            parentItem->children.insert(0, newItem);
        }
        else
        {
            m_children.insert(0, newItem);
        }
    }
    else
    {
        if (parentItem)
        {
            row = parentItem->children.indexOf(afterItem) + 1;
            parentItem->children.insert(row, newItem);
        }
        else
        {
            row = m_children.indexOf(afterItem) + 1;
            m_children.insert(row, newItem);
        }
    }
    if (parentItem && this->hasHeader(parentItem))
    {
        row += 2;
    }

    if (!parentItem)
    {
        layout = m_mainLayout;
        parentWidget = q_ptr;;
    }
    else
    {
        if (!parentItem->groupBox)
        {
            m_recreateQueue.removeAll(parentItem);
            WidgetItem *par = parentItem->parent;
            QWidget *w = QEXT_NULLPTR;
            QGridLayout *l = QEXT_NULLPTR;
            int oldRow = -1;
            if (!par)
            {
                w = q_ptr;
                l = m_mainLayout;
                oldRow = m_children.indexOf(parentItem);
            }
            else
            {
                w = par->groupBox;
                l = par->layout;
                oldRow = par->children.indexOf(parentItem);
                if (this->hasHeader(par))
                {
                    oldRow += 2;
                }
            }
            parentItem->groupBox = new QGroupBox(w);
            parentItem->layout = new QGridLayout();
            parentItem->groupBox->setLayout(parentItem->layout);
            if (parentItem->label)
            {
                l->removeWidget(parentItem->label);
                delete parentItem->label;
                parentItem->label = QEXT_NULLPTR;
            }
            if (parentItem->widget)
            {
                l->removeWidget(parentItem->widget);
                parentItem->widget->setParent(parentItem->groupBox);
                parentItem->layout->addWidget(parentItem->widget, 0, 0, 1, 2);
                parentItem->line = new QFrame(parentItem->groupBox);
            }
            else if (parentItem->widgetLabel)
            {
                l->removeWidget(parentItem->widgetLabel);
                delete parentItem->widgetLabel;
                parentItem->widgetLabel = QEXT_NULLPTR;
            }
            if (parentItem->line)
            {
                parentItem->line->setFrameShape(QFrame::HLine);
                parentItem->line->setFrameShadow(QFrame::Sunken);
                parentItem->layout->addWidget(parentItem->line, 1, 0, 1, 2);
            }
            l->addWidget(parentItem->groupBox, oldRow, 0, 1, 2);
            this->updateItem(parentItem);
        }
        layout = parentItem->layout;
        parentWidget = parentItem->groupBox;
    }

    newItem->label = new QLabel(parentWidget);
    newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    newItem->widget = this->createEditor(index->property(), parentWidget);
    if (!newItem->widget)
    {
        newItem->widgetLabel = new QLabel(parentWidget);
        newItem->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
        newItem->widgetLabel->setTextFormat(Qt::PlainText);
    }
    else
    {
        QObject::connect(newItem->widget, SIGNAL(destroyed()), q_ptr, SLOT(slotEditorDestroyed()));
        m_widgetToItem[newItem->widget] = newItem;
    }

    this->insertRow(layout, row);
    int span = 1;
    if (newItem->widget)
    {
        layout->addWidget(newItem->widget, row, 1);
    }
    else if (newItem->widgetLabel)
    {
        layout->addWidget(newItem->widgetLabel, row, 1);
    }
    else
    {
        span = 2;
    }
    layout->addWidget(newItem->label, row, 0, 1, span);

    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    this->updateItem(newItem);
}

void QExtPEPropertyGroupBoxEditorPrivate::propertyRemoved(QExtPEPropertyItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);

    WidgetItem *parentItem = item->parent;

    int row = -1;

    if (parentItem)
    {
        row = parentItem->children.indexOf(item);
        parentItem->children.removeAt(row);
        if (this->hasHeader(parentItem))
        {
            row += 2;
        }
    }
    else
    {
        row = m_children.indexOf(item);
        m_children.removeAt(row);
    }

    if (item->widget)
    {
        delete item->widget;
    }
    if (item->label)
    {
        delete item->label;
    }
    if (item->widgetLabel)
    {
        delete item->widgetLabel;
    }
    if (item->groupBox)
    {
        delete item->groupBox;
    }

    if (!parentItem)
    {
        this->removeRow(m_mainLayout, row);
    }
    else if (parentItem->children.count() != 0)
    {
        this->removeRow(parentItem->layout, row);
    }
    else
    {
        WidgetItem *par = parentItem->parent;
        QGridLayout *l = QEXT_NULLPTR;
        int oldRow = -1;
        if (!par)
        {
            l = m_mainLayout;
            oldRow = m_children.indexOf(parentItem);
        }
        else
        {
            l = par->layout;
            oldRow = par->children.indexOf(parentItem);
            if (this->hasHeader(par))
            {
                oldRow += 2;
            }
        }

        if (parentItem->widget)
        {
            parentItem->widget->hide();
            parentItem->widget->setParent(0);
        }
        else if (parentItem->widgetLabel)
        {
            parentItem->widgetLabel->hide();
            parentItem->widgetLabel->setParent(0);
        }
        else
        {
            //parentItem->widgetLabel = new QLabel(w);
        }
        l->removeWidget(parentItem->groupBox);
        delete parentItem->groupBox;
        parentItem->groupBox = QEXT_NULLPTR;
        parentItem->line = QEXT_NULLPTR;
        parentItem->layout = QEXT_NULLPTR;
        if (!m_recreateQueue.contains(parentItem))
        {
            m_recreateQueue.append(parentItem);
        }
        this->updateLater();
    }
    m_recreateQueue.removeAll(item);

    delete item;
}

void QExtPEPropertyGroupBoxEditorPrivate::insertRow(QGridLayout *layout, int row) const
{
    QMap<QLayoutItem *, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count())
    {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r >= row)
        {
            itemToPos[layout->takeAt(idx)] = QRect(r + 1, c, rs, cs);
        }
        else
        {
            idx++;
        }
    }

    const QMap<QLayoutItem *, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QMap<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it)
    {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

void QExtPEPropertyGroupBoxEditorPrivate::removeRow(QGridLayout *layout, int row) const
{
    int idx = 0;
    QHash<QLayoutItem *, QRect> itemToPos;
    while (idx < layout->count())
    {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r > row)
        {
            itemToPos[layout->takeAt(idx)] = QRect(r - 1, c, rs, cs);
        }
        else
        {
            idx++;
        }
    }

    const QHash<QLayoutItem *, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QHash<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it)
    {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

bool QExtPEPropertyGroupBoxEditorPrivate::hasHeader(WidgetItem *item) const
{
    if (item->widget)
    {
        return true;
    }
    return false;
}

void QExtPEPropertyGroupBoxEditorPrivate::propertyChanged(QExtPEPropertyItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    this->updateItem(item);
}

void QExtPEPropertyGroupBoxEditorPrivate::updateItem(WidgetItem *item)
{
    QExtPEProperty *property = m_itemToIndex[item]->property();
    if (item->groupBox)
    {
        QFont font = item->groupBox->font();
        font.setUnderline(property->isModified());
        item->groupBox->setFont(font);
        item->groupBox->setTitle(property->propertyName());
        item->groupBox->setToolTip(property->toolTip());
        item->groupBox->setStatusTip(property->statusTip());
        item->groupBox->setWhatsThis(property->whatsThis());
        item->groupBox->setEnabled(property->isEnabled());
    }
    if (item->label)
    {
        QFont font = item->label->font();
        font.setUnderline(property->isModified());
        item->label->setFont(font);
        item->label->setText(property->propertyName());
        item->label->setToolTip(property->toolTip());
        item->label->setStatusTip(property->statusTip());
        item->label->setWhatsThis(property->whatsThis());
        item->label->setEnabled(property->isEnabled());
    }
    if (item->widgetLabel)
    {
        QFont font = item->widgetLabel->font();
        font.setUnderline(false);
        item->widgetLabel->setFont(font);
        item->widgetLabel->setText(property->valueText());
        item->widgetLabel->setToolTip(property->valueText());
        item->widgetLabel->setEnabled(property->isEnabled());
    }
    if (item->widget)
    {
        QFont font = item->widget->font();
        font.setUnderline(false);
        item->widget->setFont(font);
        item->widget->setEnabled(property->isEnabled());
        item->widget->setToolTip(property->valueText());
    }
    //item->setIcon(1, property->valueIcon());
}



QExtPEPropertyGroupBoxEditor::QExtPEPropertyGroupBoxEditor(QWidget *parent)
    : QExtPEAbstractPropertyEditor(parent)
{
    dd_ptr = new QExtPEPropertyGroupBoxEditorPrivate;
    dd_ptr->q_ptr = this;

    dd_ptr->init(this);
}

QExtPEPropertyGroupBoxEditor::~QExtPEPropertyGroupBoxEditor()
{
    QMap<QExtPEPropertyGroupBoxEditorPrivate::WidgetItem *, QExtPEPropertyItem *>::ConstIterator it;
    for (it = dd_ptr->m_itemToIndex.constBegin(); it != dd_ptr->m_itemToIndex.constEnd(); ++it)
    {
        delete it.key();
    }
    delete dd_ptr;
}

void QExtPEPropertyGroupBoxEditor::itemInserted(QExtPEPropertyItem *item, QExtPEPropertyItem *afterItem)
{
    dd_ptr->propertyInserted(item, afterItem);
}

void QExtPEPropertyGroupBoxEditor::itemRemoved(QExtPEPropertyItem *item)
{
    dd_ptr->propertyRemoved(item);
}

void QExtPEPropertyGroupBoxEditor::itemChanged(QExtPEPropertyItem *item)
{
    dd_ptr->propertyChanged(item);
}

#include <moc_qextPEPropertyGroupBoxEditor.cpp>
