#include <QAbstractItemView>
#include <QComboBox>
#include <QLineEdit>
#include <QMouseEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QVBoxLayout>
#include <qextMvvmCustomEventFilters.h>
#include <qextMvvmSelectableComboboxEditor.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmUtils.h>



//! Provides custom style delegate for QComboBox to allow checkboxes.

class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QCheckListStyledItemDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const QEXT_DECL_OVERRIDE
    {
        auto styleOption = const_cast<QStyleOptionViewItem&>(option);
        styleOption.showDecorationSelected = false;
        QStyledItemDelegate::paint(painter, styleOption, index);
    }
};

// ----------------------------------------------------------------------------

QEXTMvvmSelectableComboBoxEditor::QEXTMvvmSelectableComboBoxEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent)
    , m_box(new QComboBox)
    , m_wheelEventFilter(new QEXTMvvmWheelEventFilter(this))
    , m_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheelEventFilter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), &QLineEdit::selectionChanged, m_box->lineEdit(),
            &QLineEdit::deselect);

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);
    setConnected(true);
}

QSize QEXTMvvmSelectableComboBoxEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize QEXTMvvmSelectableComboBoxEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool QEXTMvvmSelectableComboBoxEditor::isPersistent() const
{
    return true;
}

//! Propagate check state from the model to QEXTMvvmComboProperty.

void QEXTMvvmSelectableComboBoxEditor::onModelDataChanged(const QModelIndex &topLeft, const QModelIndex&,
                                                  const QVector<int> &roles)
{
#if QT_VERSION > QT_VERSION_CHECK(5, 9, 0)
    // for older versions this role is always empty
    if (!roles.contains(Qt::CheckStateRole))
        return;
#endif

    auto item = m_model->itemFromIndex(topLeft);
    if (!item)
        return;

    QEXTMvvmComboProperty comboProperty = m_data.value<QEXTMvvmComboProperty>();
    auto state = item->checkState() == Qt::Checked ? true : false;
    comboProperty.setSelected(topLeft.row(), state);

    updateBoxLabel();
    setDataIntern(QVariant::fromValue<QEXTMvvmComboProperty>(comboProperty));
}

//! Processes press event in QComboBox's underlying list view.

void QEXTMvvmSelectableComboBoxEditor::onClickedList(const QModelIndex& index)
{
    if (auto item = m_model->itemFromIndex(index)) {
        auto state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

//! Handles mouse clicks on QComboBox elements.

bool QEXTMvvmSelectableComboBoxEditor::eventFilter(QObject* obj, QEvent* event)
{
    if (isClickToSelect(obj, event)) {
        // Handles mouse clicks on QListView when it is expanded from QComboBox
        // 1) Prevents list from closing while selecting items.
        // 2) Correctly calculates underlying model index when mouse is over check box style
        // element.
        const auto mouseEvent = static_cast<const QMouseEvent*>(event);
        auto index = m_box->view()->indexAt(mouseEvent->pos());
        onClickedList(index);
        return true;

    } else if (isClickToExpand(obj, event)) {
        // Expands box when clicking on None/Multiple label
        m_box->showPopup();
        return true;

    } else {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void QEXTMvvmSelectableComboBoxEditor::updateComponents()
{
    if (!m_data.canConvert<QEXTMvvmComboProperty>())
        return;

    QEXTMvvmComboProperty property = m_data.value<QEXTMvvmComboProperty>();

    setConnected(false);
    m_model->clear();

    auto labels = property.values();
    auto selectedIndices = property.selectedIndices();

    for (size_t i = 0; i < labels.size(); ++i) {
        auto item = new QStandardItem(labels[i]);
        m_model->invisibleRootItem()->appendRow(item);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckable(true);

        auto state = selectedIndices.contains(i) ? Qt::Checked : Qt::Unchecked;
        item->setData(state, Qt::CheckStateRole);
    }

    setConnected(true);
    updateBoxLabel();
}

void QEXTMvvmSelectableComboBoxEditor::setConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_model, &QStandardItemModel::dataChanged, this,
                &QEXTMvvmSelectableComboBoxEditor::onModelDataChanged);
    } else {
        disconnect(m_model, &QStandardItemModel::dataChanged, this,
                   &QEXTMvvmSelectableComboBoxEditor::onModelDataChanged);
    }
}

//! Update text on QComboBox with the label provided by combo property.

void QEXTMvvmSelectableComboBoxEditor::updateBoxLabel()
{
    QEXTMvvmComboProperty combo = m_data.value<QEXTMvvmComboProperty>();
    m_box->setCurrentText(combo.label());
}

bool QEXTMvvmSelectableComboBoxEditor::isClickToSelect(QObject* obj, QEvent* event) const
{
    return obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease;
}

bool QEXTMvvmSelectableComboBoxEditor::isClickToExpand(QObject* obj, QEvent* event) const
{
    return obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease;
}
