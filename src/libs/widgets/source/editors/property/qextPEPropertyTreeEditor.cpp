#include <private/qextPEPropertyTreeEditor_p.h>

#include <QEvent>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QFocusEvent>
#include <QHeaderView>
#include <QApplication>


/***********************************************************************************************************************
** QExtPEPropertyTreeEditorView
***********************************************************************************************************************/
// ------------ QExtPEPropertyTreeEditorView
QExtPEPropertyTreeEditorView::QExtPEPropertyTreeEditorView(QWidget *parent)
    : QTreeWidget(parent), m_editorPrivate(QEXT_NULLPTR)
{
    connect(header(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(resizeColumnToContents(int)));
}

void QExtPEPropertyTreeEditorView::paintEvent(QPaintEvent *paintEvent)
{
    QTreeWidget::paintEvent(paintEvent);
}

void QExtPEPropertyTreeEditorView::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    bool hasValue = true;
    if (m_editorPrivate)
    {
        QExtPEProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
        {
            hasValue = property->hasValue();
        }
    }
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue())
    {
        const QColor c = option.palette.color(QPalette::Dark);
        painter->fillRect(option.rect, c);
        opt.palette.setColor(QPalette::AlternateBase, c);
    }
    else
    {
        const QColor c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid())
        {
            painter->fillRect(option.rect, c);
            opt.palette.setColor(QPalette::AlternateBase, c.lighter(112));
        }
    }
    QTreeWidget::drawRow(painter, opt, index);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
    painter->restore();
}

void QExtPEPropertyTreeEditorView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Space: // Trigger Edit
        if (!m_editorPrivate->editedItem())
        {
            if (const QTreeWidgetItem *item = currentItem())
            {
                if (item->columnCount() >= 2 && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled)))
                {
                    event->accept();
                    // If the current position is at column 0, move to 1.
                    QModelIndex index = currentIndex();
                    if (index.column() == 0)
                    {
                        index = index.sibling(index.row(), 1);
                        setCurrentIndex(index);
                    }
                    this->edit(index);
                    return;
                }
            }
        }
        break;
    default:
        break;
    }
    QTreeWidget::keyPressEvent(event);
}

void QExtPEPropertyTreeEditorView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    QTreeWidgetItem *item = itemAt(event->pos());

    if (item)
    {
        if ((item != m_editorPrivate->editedItem()) && (event->button() == Qt::LeftButton)
            && (header()->logicalIndexAt(event->pos().x()) == 1)
            && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled)))
        {
            this->editItem(item, 1);
        }
        else if (!m_editorPrivate->hasValue(item) && m_editorPrivate->markPropertiesWithoutValue() && !rootIsDecorated())
        {
            if (event->pos().x() + header()->offset() < 20)
            {
                item->setExpanded(!item->isExpanded());
            }
        }
    }
}

// ------------ QExtPEPropertyTreeEditorDelegate
int QExtPEPropertyTreeEditorDelegate::indentation(const QModelIndex &index) const
{
    if (!m_editorPrivate)
    {
        return 0;
    }

    QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
    int indent = 0;
    while (item->parent())
    {
        item = item->parent();
        ++indent;
    }
    if (m_editorPrivate->treeWidget()->rootIsDecorated())
    {
        ++indent;
    }
    return indent * m_editorPrivate->treeWidget()->indentation();
}

void QExtPEPropertyTreeEditorDelegate::slotEditorDestroyed(QObject *object)
{
    if (QWidget *w = qobject_cast<QWidget *>(object))
    {
        const EditorToPropertyMap::iterator it = m_editorToProperty.find(w);
        if (it != m_editorToProperty.end())
        {
            m_propertyToEditor.remove(it.value());
            m_editorToProperty.erase(it);
        }
        if (m_editedWidget == w)
        {
            m_editedWidget = QEXT_NULLPTR;
            m_editedItem = QEXT_NULLPTR;
        }
    }
}

void QExtPEPropertyTreeEditorDelegate::closeEditor(QExtPEProperty *property)
{
    if (QWidget *w = m_propertyToEditor.value(property, QEXT_NULLPTR))
    {
        w->deleteLater();
    }
}

QWidget *QExtPEPropertyTreeEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                                  const QModelIndex &index) const
{
    if (index.column() == 1 && m_editorPrivate)
    {
        QExtPEProperty *property = m_editorPrivate->indexToProperty(index);
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (property && item && (item->flags() & Qt::ItemIsEnabled))
        {
            QWidget *editor = m_editorPrivate->createEditor(property, parent);
            if (editor)
            {
                editor->setAutoFillBackground(true);
                editor->installEventFilter(const_cast<QExtPEPropertyTreeEditorDelegate *>(this));
                connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
                m_propertyToEditor[property] = editor;
                m_editorToProperty[editor] = property;
                m_editedItem = item;
                m_editedWidget = editor;
            }
            return editor;
        }
    }
    return QEXT_NULLPTR;
}

void QExtPEPropertyTreeEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                      const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));
}

void QExtPEPropertyTreeEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    bool hasValue = true;
    if (m_editorPrivate)
    {
        QExtPEProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
        {
            hasValue = property->hasValue();
        }
    }
    QStyleOptionViewItem opt = option;
    if ((m_editorPrivate && index.column() == 0) || !hasValue)
    {
        QExtPEProperty *property = m_editorPrivate->indexToProperty(index);
        if (property && property->isModified())
        {
            opt.font.setBold(true);
            opt.fontMetrics = QFontMetrics(opt.font);
        }
    }
    QColor c;
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue())
    {
        c = opt.palette.color(QPalette::Dark);
        opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
    }
    else
    {
        c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid() && (opt.features & QStyleOptionViewItem::Alternate))
        {
            c = c.lighter(112);
        }
    }
    if (c.isValid())
    {
        painter->fillRect(option.rect, c);
    }
    opt.state &= ~QStyle::State_HasFocus;
    if (index.column() == 1)
    {
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (m_editedItem && m_editedItem == item)
        {
            m_disablePainting = true;
        }
    }
    QItemDelegate::paint(painter, opt, index);
    if (option.type)
    {
        m_disablePainting = false;
    }

    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    if (!m_editorPrivate || (!m_editorPrivate->lastColumn(index.column()) && hasValue))
    {
        int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }
    painter->restore();
}

void QExtPEPropertyTreeEditorDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                                const QRect &rect, const QPixmap &pixmap) const
{
    if (m_disablePainting)
    {
        return;
    }

    QItemDelegate::drawDecoration(painter, option, rect, pixmap);
}

void QExtPEPropertyTreeEditorDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                                             const QRect &rect, const QString &text) const
{
    if (m_disablePainting)
    {
        return;
    }

    QItemDelegate::drawDisplay(painter, option, rect, text);
}

QSize QExtPEPropertyTreeEditorDelegate::sizeHint(const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    auto size = QItemDelegate::sizeHint(option, index) + QSize(3, 4);
    if (m_itemMinimumHeight > 0)
    {
        size.setHeight(qMax(size.height(), m_itemMinimumHeight));
    }
    return size;
}

bool QExtPEPropertyTreeEditorDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusOut)
    {
        QFocusEvent *focusEvent = static_cast<QFocusEvent *>(event);
        if (focusEvent->reason() == Qt::ActiveWindowFocusReason)
        {
            return false;
        }
    }
    return QItemDelegate::eventFilter(object, event);
}

//  -------- QExtPEPropertyTreeEditorPrivate implementation
QExtPEPropertyTreeEditorPrivate::QExtPEPropertyTreeEditorPrivate()
    : m_treeWidget(QEXT_NULLPTR)
    , m_delegate(QEXT_NULLPTR)
    , m_headerVisible(true)
    , m_resizeMode(QExtPEPropertyTreeEditor::Stretch)
    , m_markPropertiesWithoutValue(false)
    , m_browserChangedBlocked(false)
{
}

// Draw an icon indicating opened/closing branches
static QIcon drawIndicatorIcon(const QPalette &palette, QStyle *style)
{
    QPixmap pix(14, 14);
    pix.fill(Qt::transparent);
    QStyleOption branchOption;
    QRect r(QPoint(0, 0), pix.size());
    branchOption.rect = QRect(2, 2, 9, 9); // ### hardcoded in qcommonstyle.cpp
    branchOption.palette = palette;
    branchOption.state = QStyle::State_Children;

    QPainter p;
    // Draw closed state
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();
    QIcon rc = pix;
    rc.addPixmap(pix, QIcon::Selected, QIcon::Off);
    // Draw opened state
    branchOption.state |= QStyle::State_Open;
    pix.fill(Qt::transparent);
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();

    rc.addPixmap(pix, QIcon::Normal, QIcon::On);
    rc.addPixmap(pix, QIcon::Selected, QIcon::On);
    return rc;
}

void QExtPEPropertyTreeEditorPrivate::init(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    m_treeWidget = new QExtPEPropertyTreeEditorView(parent);
    m_treeWidget->setEditorPrivate(this);
    m_treeWidget->setIconSize(QSize(18, 18));
    layout->addWidget(m_treeWidget);
    parent->setFocusProxy(m_treeWidget);

    m_treeWidget->setColumnCount(2);
    QStringList labels;
    labels.append(QCoreApplication::translate("QExtPEPropertyTreeEditor", "Property"));
    labels.append(QCoreApplication::translate("QExtPEPropertyTreeEditor", "Value"));
    m_treeWidget->setHeaderLabels(labels);
    m_treeWidget->setAlternatingRowColors(true);
    m_treeWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);
    m_delegate = new QExtPEPropertyTreeEditorDelegate(parent);
    m_delegate->setEditorPrivate(this);
    m_treeWidget->setItemDelegate(m_delegate);
#if QT_DEPRECATED_SINCE(5, 0)
    m_treeWidget->header()->setMovable(false);
    m_treeWidget->header()->setResizeMode(QHeaderView::Stretch);
#endif

    m_expandIcon = drawIndicatorIcon(q_ptr->palette(), q_ptr->style());

    QObject::connect(m_treeWidget, SIGNAL(collapsed(const QModelIndex &)),
                     q_ptr, SLOT(slotCollapsed(const QModelIndex &)));
    QObject::connect(m_treeWidget, SIGNAL(expanded(const QModelIndex &)),
                     q_ptr, SLOT(slotExpanded(const QModelIndex &)));
    QObject::connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                     q_ptr, SLOT(slotCurrentTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

QExtPEPropertyItem *QExtPEPropertyTreeEditorPrivate::currentItem() const
{
    if (QTreeWidgetItem *treeItem = m_treeWidget->currentItem())
    {
        return m_itemToIndex.value(treeItem);
    }
    return QEXT_NULLPTR;
}

void QExtPEPropertyTreeEditorPrivate::setCurrentItem(QExtPEPropertyItem *browserItem, bool block)
{
    const bool blocked = block ? m_treeWidget->blockSignals(true) : false;
    if (!browserItem)
    {
        m_treeWidget->setCurrentItem(QEXT_NULLPTR);
    }
    else
    {
        m_treeWidget->setCurrentItem(m_indexToItem.value(browserItem));
    }
    if (block)
    {
        m_treeWidget->blockSignals(blocked);
    }
}

QExtPEProperty *QExtPEPropertyTreeEditorPrivate::indexToProperty(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    QExtPEPropertyItem *idx = m_itemToIndex.value(item);
    if (idx)
    {
        return idx->property();
    }
    return QEXT_NULLPTR;
}

QExtPEPropertyItem *QExtPEPropertyTreeEditorPrivate::indexToBrowserItem(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    return m_itemToIndex.value(item);
}

QTreeWidgetItem *QExtPEPropertyTreeEditorPrivate::indexToItem(const QModelIndex &index) const
{
    return m_treeWidget->indexToItem(index);
}

bool QExtPEPropertyTreeEditorPrivate::lastColumn(int column) const
{
    return m_treeWidget->header()->visualIndex(column) == m_treeWidget->columnCount() - 1;
}

void QExtPEPropertyTreeEditorPrivate::disableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    if (flags & Qt::ItemIsEnabled)
    {
        flags &= ~Qt::ItemIsEnabled;
        item->setFlags(flags);
        m_delegate->closeEditor(m_itemToIndex[item]->property());
        const int childCount = item->childCount();
        for (int i = 0; i < childCount; i++)
        {
            QTreeWidgetItem *child = item->child(i);
            disableItem(child);
        }
    }
}

void QExtPEPropertyTreeEditorPrivate::enableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    flags |= Qt::ItemIsEnabled;
    item->setFlags(flags);
    const int childCount = item->childCount();
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *child = item->child(i);
        QExtPEProperty *property = m_itemToIndex[child]->property();
        if (property->isEnabled())
        {
            enableItem(child);
        }
    }
}

bool QExtPEPropertyTreeEditorPrivate::hasValue(QTreeWidgetItem *item) const
{
    QExtPEPropertyItem *browserItem = m_itemToIndex.value(item);
    if (browserItem)
    {
        return browserItem->property()->hasValue();
    }
    return false;
}

void QExtPEPropertyTreeEditorPrivate::propertyInserted(QExtPEPropertyItem *index, QExtPEPropertyItem *afterIndex)
{
    QTreeWidgetItem *afterItem = m_indexToItem.value(afterIndex);
    QTreeWidgetItem *parentItem = m_indexToItem.value(index->parent());

    QTreeWidgetItem *newItem = QEXT_NULLPTR;
    if (parentItem)
    {
        newItem = new QTreeWidgetItem(parentItem, afterItem);
    }
    else
    {
        newItem = new QTreeWidgetItem(m_treeWidget, afterItem);
    }
    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    m_treeWidget->setItemExpanded(newItem, true);

    this->updateItem(newItem);
}

void QExtPEPropertyTreeEditorPrivate::propertyRemoved(QExtPEPropertyItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    if (m_treeWidget->currentItem() == item)
    {
        m_treeWidget->setCurrentItem(0);
    }

    delete item;

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);
    m_indexToBackgroundColor.remove(index);
}

void QExtPEPropertyTreeEditorPrivate::propertyChanged(QExtPEPropertyItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);
    this->updateItem(item);
}

void QExtPEPropertyTreeEditorPrivate::updateItem(QTreeWidgetItem *item)
{
    QExtPEProperty *property = m_itemToIndex[item]->property();
    QIcon expandIcon;
    if (property->hasValue())
    {
        QString toolTip = property->toolTip();
        if (toolTip.isEmpty())
        {
            toolTip = property->displayText();
        }
        item->setToolTip(1, toolTip);
        item->setIcon(1, property->valueIcon());
        property->displayText().isEmpty() ? item->setText(1, property->valueText()) : item->setText(1, property->displayText());
    }
    else if (markPropertiesWithoutValue() && !m_treeWidget->rootIsDecorated())
    {
        expandIcon = m_expandIcon;
    }
    item->setIcon(0, expandIcon);
    item->setFirstColumnSpanned(!property->hasValue());
    item->setToolTip(0, property->propertyName());
    item->setStatusTip(0, property->statusTip());
    item->setWhatsThis(0, property->whatsThis());
    item->setText(0, property->propertyName());
    bool wasEnabled = item->flags() & Qt::ItemIsEnabled;
    bool isEnabled = wasEnabled;
    if (property->isEnabled())
    {
        QTreeWidgetItem *parent = item->parent();
        if (!parent || (parent->flags() & Qt::ItemIsEnabled))
        {
            isEnabled = true;
        }
        else
        {
            isEnabled = false;
        }
    }
    else
    {
        isEnabled = false;
    }
    if (wasEnabled != isEnabled)
    {
        if (isEnabled)
        {
            enableItem(item);
        }
        else
        {
            disableItem(item);
        }
    }
    m_treeWidget->viewport()->update();
}

QColor QExtPEPropertyTreeEditorPrivate::calculatedBackgroundColor(QExtPEPropertyItem *item) const
{
    QExtPEPropertyItem *i = item;
    const QMap<QExtPEPropertyItem *, QColor>::const_iterator itEnd = m_indexToBackgroundColor.constEnd();
    while (i)
    {
        QMap<QExtPEPropertyItem *, QColor>::const_iterator it = m_indexToBackgroundColor.constFind(i);
        if (it != itEnd)
        {
            return it.value();
        }
        i = i->parent();
    }
    return QColor();
}

void QExtPEPropertyTreeEditorPrivate::slotCollapsed(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QExtPEPropertyItem *idx = m_itemToIndex.value(item);
    if (item)
    {
        emit q_ptr->collapsed(idx);
    }
}

void QExtPEPropertyTreeEditorPrivate::slotExpanded(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QExtPEPropertyItem *idx = m_itemToIndex.value(item);
    if (item)
    {
        emit q_ptr->expanded(idx);
    }
}

void QExtPEPropertyTreeEditorPrivate::slotCurrentBrowserItemChanged(QExtPEPropertyItem *item)
{
    if (!m_browserChangedBlocked && item != currentItem())
    {
        this->setCurrentItem(item, true);
    }
}

void QExtPEPropertyTreeEditorPrivate::slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *)
{
    QExtPEPropertyItem *browserItem = newItem ? m_itemToIndex.value(newItem) : QEXT_NULLPTR;
    m_browserChangedBlocked = true;
    q_ptr->setCurrentItem(browserItem);
    m_browserChangedBlocked = false;
}

QTreeWidgetItem *QExtPEPropertyTreeEditorPrivate::editedItem() const
{
    return m_delegate->editedItem();
}

void QExtPEPropertyTreeEditorPrivate::editItem(QExtPEPropertyItem *browserItem)
{
    if (QTreeWidgetItem *treeItem = m_indexToItem.value(browserItem, QEXT_NULLPTR))
    {
        m_treeWidget->setCurrentItem (treeItem, 1);
        m_treeWidget->editItem(treeItem, 1);
    }
}



QExtPEPropertyTreeEditor::QExtPEPropertyTreeEditor(QWidget *parent)
    : QExtPEAbstractPropertyEditor(parent)
{
    d_ptr = new QExtPEPropertyTreeEditorPrivate;
    d_ptr->q_ptr = this;

    d_ptr->init(this);
    connect(this, SIGNAL(currentItemChanged(QExtPEPropertyItem*)), this, SLOT(slotCurrentBrowserItemChanged(QExtPEPropertyItem*)));
}

QExtPEPropertyTreeEditor::~QExtPEPropertyTreeEditor()
{
    delete d_ptr;
}

QTreeWidget *QExtPEPropertyTreeEditor::editorView() const
{
    return d_ptr->m_treeWidget;
}

int QExtPEPropertyTreeEditor::editorViewRowHeight() const
{
    return d_ptr->m_delegate->itemMinimumHeight();
}

void QExtPEPropertyTreeEditor::setEditorViewRowHeight(int height)
{
    d_ptr->m_delegate->setItemMinimumHeight(height);
}

int QExtPEPropertyTreeEditor::indentation() const
{
    return d_ptr->m_treeWidget->indentation();
}

void QExtPEPropertyTreeEditor::setIndentation(int i)
{
    d_ptr->m_treeWidget->setIndentation(i);
}

bool QExtPEPropertyTreeEditor::rootIsDecorated() const
{
    return d_ptr->m_treeWidget->rootIsDecorated();
}

void QExtPEPropertyTreeEditor::setRootIsDecorated(bool show)
{
    d_ptr->m_treeWidget->setRootIsDecorated(show);
    QMapIterator<QTreeWidgetItem *, QExtPEPropertyItem *> it(d_ptr->m_itemToIndex);
    while (it.hasNext())
    {
        QExtPEProperty *property = it.next().value()->property();
        if (!property->hasValue())
        {
            d_ptr->updateItem(it.key());
        }
    }
}

bool QExtPEPropertyTreeEditor::alternatingRowColors() const
{
    return d_ptr->m_treeWidget->alternatingRowColors();
}

void QExtPEPropertyTreeEditor::setAlternatingRowColors(bool enable)
{
    d_ptr->m_treeWidget->setAlternatingRowColors(enable);
    QMapIterator<QTreeWidgetItem *, QExtPEPropertyItem *> it(d_ptr->m_itemToIndex);
}

bool QExtPEPropertyTreeEditor::isHeaderVisible() const
{
    return d_ptr->m_headerVisible;
}

void QExtPEPropertyTreeEditor::setHeaderVisible(bool visible)
{
    if (visible == d_ptr->m_headerVisible)
    {
        return;
    }

    d_ptr->m_headerVisible = visible;
    d_ptr->m_treeWidget->header()->setVisible(visible);
}

QExtPEPropertyTreeEditor::ResizeMode QExtPEPropertyTreeEditor::resizeMode() const
{
    return d_ptr->m_resizeMode;
}

void QExtPEPropertyTreeEditor::setResizeMode(QExtPEPropertyTreeEditor::ResizeMode mode)
{
    if (mode == d_ptr->m_resizeMode)
    {
        return;
    }

    d_ptr->m_resizeMode = mode;
    QHeaderView::ResizeMode m = QHeaderView::Stretch;
    switch (mode)
    {
    case QExtPEPropertyTreeEditor::Interactive:      m = QHeaderView::Interactive;      break;
    case QExtPEPropertyTreeEditor::Fixed:            m = QHeaderView::Fixed;            break;
    case QExtPEPropertyTreeEditor::ResizeToContents: m = QHeaderView::ResizeToContents; break;
    case QExtPEPropertyTreeEditor::Stretch:
    default:                                      m = QHeaderView::Stretch;          break;
    }
#if QT_DEPRECATED_SINCE(5, 0)
    d_ptr->m_treeWidget->header()->setResizeMode(m);
#endif
}

int QExtPEPropertyTreeEditor::splitterPosition() const
{
    return d_ptr->m_treeWidget->header()->sectionSize(0);
}

void QExtPEPropertyTreeEditor::setSplitterPosition(int position)
{
    d_ptr->m_treeWidget->header()->resizeSection(0, position);
}

void QExtPEPropertyTreeEditor::setExpanded(QExtPEPropertyItem *item, bool expanded)
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
    {
        treeItem->setExpanded(expanded);
    }
}

bool QExtPEPropertyTreeEditor::isExpanded(QExtPEPropertyItem *item) const
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
    {
        return treeItem->isExpanded();
    }
    return false;
}

bool QExtPEPropertyTreeEditor::isItemVisible(QExtPEPropertyItem *item) const
{
    if (const QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
    {
        return !treeItem->isHidden();
    }
    return false;
}

void QExtPEPropertyTreeEditor::setItemVisible(QExtPEPropertyItem *item, bool visible)
{
    if (QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
    {
        treeItem->setHidden(!visible);
    }
}

void QExtPEPropertyTreeEditor::setBackgroundColor(QExtPEPropertyItem *item, const QColor &color)
{
    if (!d_ptr->m_indexToItem.contains(item))
    {
        return;
    }
    if (color.isValid())
    {
        d_ptr->m_indexToBackgroundColor[item] = color;
    }
    else
    {
        d_ptr->m_indexToBackgroundColor.remove(item);
    }
    d_ptr->m_treeWidget->viewport()->update();
}

QColor QExtPEPropertyTreeEditor::backgroundColor(QExtPEPropertyItem *item) const
{
    return d_ptr->m_indexToBackgroundColor.value(item);
}

QColor QExtPEPropertyTreeEditor::calculatedBackgroundColor(QExtPEPropertyItem *item) const
{
    return d_ptr->calculatedBackgroundColor(item);
}

void QExtPEPropertyTreeEditor::setPropertiesWithoutValueMarked(bool mark)
{
    if (d_ptr->m_markPropertiesWithoutValue == mark)
    {
        return;
    }

    d_ptr->m_markPropertiesWithoutValue = mark;
    QMapIterator<QTreeWidgetItem *, QExtPEPropertyItem *> it(d_ptr->m_itemToIndex);
    while (it.hasNext())
    {
        QExtPEProperty *property = it.next().value()->property();
        if (!property->hasValue())
        {
            d_ptr->updateItem(it.key());
        }
    }
    d_ptr->m_treeWidget->viewport()->update();
}

bool QExtPEPropertyTreeEditor::propertiesWithoutValueMarked() const
{
    return d_ptr->m_markPropertiesWithoutValue;
}

void QExtPEPropertyTreeEditor::itemInserted(QExtPEPropertyItem *item, QExtPEPropertyItem *afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

void QExtPEPropertyTreeEditor::itemRemoved(QExtPEPropertyItem *item)
{
    d_ptr->propertyRemoved(item);
}

void QExtPEPropertyTreeEditor::itemChanged(QExtPEPropertyItem *item)
{
    d_ptr->propertyChanged(item);
}

void QExtPEPropertyTreeEditor::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        QMapIterator<QTreeWidgetItem *, QExtPEPropertyItem *> it(d_ptr->m_itemToIndex);
        while (it.hasNext())
        {
            QExtPEProperty *property = it.next().value()->property();
            if (property->hasValue())
            {
                property->setStyleChanged(true);
                d_ptr->updateItem(it.key());
                property->setStyleChanged(false);
            }
        }
    }
    QExtPEAbstractPropertyEditor::changeEvent(event);
}

void QExtPEPropertyTreeEditor::editItem(QExtPEPropertyItem *item)
{
    d_ptr->editItem(item);
}


#include <moc_qextPEPropertyTreeEditor.cpp>
