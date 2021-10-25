#include <qextMvvmSelectableComboBoxEditor.h>

#include <cfMvvmComboProperty.h>

#include <QDebug>
#include <QEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QAbstractItemView>
#include <QStyledItemDelegate>

CF_USE_NAMESPACE

Q_DECLARE_METATYPE(CFMvvmComboProperty)

class QEXTMvvmCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QEXTMvvmCheckListStyledItemDelegate(QObject *parent = QEXT_DECL_NULLPTR) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const QEXT_DECL_OVERRIDE
    {
        QStyleOptionViewItem &styleOption = const_cast<QStyleOptionViewItem &>(option);
        styleOption.showDecorationSelected = false;
        QStyledItemDelegate::paint(painter, styleOption, index);
    }
};

QEXTMvvmSelectableComboBoxEditor::QEXTMvvmSelectableComboBoxEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_box(new QComboBox),
      m_wheelEventFilter(new QEXTMvvmWheelEventFilter(this)),
      m_model(new QStandardItemModel(this))
{
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_box->installEventFilter(m_wheelEventFilter);
    m_box->view()->viewport()->installEventFilter(this);

    // Editable mode will be used to have None/Multiple labels on top
    m_box->setEditable(true);
    m_box->lineEdit()->setReadOnly(true);
    m_box->lineEdit()->installEventFilter(this);
    connect(m_box->lineEdit(), SIGNAL(selectionChanged()), this, SLOT(deselectLineEdit()));

    // transforms ordinary combo box into check list
    m_box->setItemDelegate(new QEXTMvvmCheckListStyledItemDelegate(this));
    m_box->setModel(m_model);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    this->setLayout(layout);
    this->setConnected(true);
}

QEXTMvvmSelectableComboBoxEditor::~QEXTMvvmSelectableComboBoxEditor()
{

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

void QEXTMvvmSelectableComboBoxEditor::onModelDataChanged(const QModelIndex &topLeft, const QModelIndex &, const QVector<int> &roles)
{
#if QT_VERSION > QT_VERSION_CHECK(5, 9, 0)
    // for older versions this role is always empty
    if (!roles.contains(Qt::CheckStateRole))
    {
        return;
    }
#endif

    QStandardItem *item = m_model->itemFromIndex(topLeft);
    if (!item)
    {
        return;
    }

    CFMvvmComboProperty comboProperty = m_data.value<CFMvvmComboProperty>();
    bool state = item->checkState() == Qt::Checked ? true : false;
    comboProperty.setSelected(topLeft.row(), state);

    this->updateBoxLabel();
    this->setDataIntern(QVariant::fromValue<CFMvvmComboProperty>(comboProperty));
}

void QEXTMvvmSelectableComboBoxEditor::onClickedList(const QModelIndex &index)
{
    if (QStandardItem *item = m_model->itemFromIndex(index))
    {
        Qt::CheckState state = item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked;
        item->setCheckState(state);
    }
}

void QEXTMvvmSelectableComboBoxEditor::deselectLineEdit()
{
    m_box->lineEdit()->deselect();
}

void QEXTMvvmSelectableComboBoxEditor::updateComponents()
{
    if (!m_data.canConvert<CFMvvmComboProperty>())
    {
        return;
    }

    CFMvvmComboProperty property = m_data.value<CFMvvmComboProperty>();

    this->setConnected(false);
    m_model->clear();

    std::vector<std::string> labels = property.values();
    std::vector<int> selectedIndices = property.selectedIndices();

    for (size_t i = 0; i < labels.size(); ++i)
    {
        QStandardItem *item = new QStandardItem(QString::fromStdString(labels[i]));
        m_model->invisibleRootItem()->appendRow(item);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckable(true);

        std::vector<int>::iterator found = std::find(selectedIndices.begin(), selectedIndices.end(), i);
        bool state = selectedIndices.end() != found ? Qt::Checked : Qt::Unchecked;
        item->setData(state, Qt::CheckStateRole);
    }

    this->setConnected(true);
    this->updateBoxLabel();
}

bool QEXTMvvmSelectableComboBoxEditor::eventFilter(QObject *obj, QEvent *event)
{
    if (this->isClickToSelect(obj, event))
    {
        // Handles mouse clicks on QListView when it is expanded from QComboBox
        // 1) Prevents list from closing while selecting items.
        // 2) Correctly calculates underlying model index when mouse is over check box style
        // element.
        const QMouseEvent *mouseEvent = static_cast<const QMouseEvent *>(event);
        QModelIndex index = m_box->view()->indexAt(mouseEvent->pos());
        this->onClickedList(index);
        return true;

    }
    else if (isClickToExpand(obj, event))
    {
        // Expands box when clicking on None/Multiple label
        m_box->showPopup();
        return true;

    }
    else
    {
        // Propagate to the parent class.
        return QObject::eventFilter(obj, event);
    }
}

void QEXTMvvmSelectableComboBoxEditor::setConnected(bool isConnected)
{
    if (isConnected)
    {
        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelDataChanged(QModelIndex,QModelIndex,QVector)));
    }
    else
    {
        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onModelDataChanged(QModelIndex,QModelIndex,QVector)));
    }
}

void QEXTMvvmSelectableComboBoxEditor::updateBoxLabel()
{
    CFMvvmComboProperty combo = m_data.value<CFMvvmComboProperty>();
    int index = m_box->findText(QString::fromStdString(combo.label()));
    m_box->setCurrentIndex(index);
}

bool QEXTMvvmSelectableComboBoxEditor::isClickToSelect(QObject *obj, QEvent *event) const
{
    return obj == m_box->view()->viewport() && event->type() == QEvent::MouseButtonRelease;
}

bool QEXTMvvmSelectableComboBoxEditor::isClickToExpand(QObject *obj, QEvent *event) const
{
    return obj == m_box->lineEdit() && event->type() == QEvent::MouseButtonRelease;
}
