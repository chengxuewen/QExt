#include <qextMvvmExternalPropertyComboEditor.h>

#include <cfMvvmComboProperty.h>
#include <cfMvvmExternalProperty.h>

#include <cfLog.h>

#include <QVBoxLayout>

Q_DECLARE_METATYPE(CFMvvmExternalProperty)
Q_DECLARE_METATYPE(CFMvvmComboProperty)

QEXTMvvmExternalPropertyComboEditor::QEXTMvvmExternalPropertyComboEditor(Callback callback, QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_getPropertiesCallback(callback),
      m_box(new QComboBox),
      m_comboModel(new QStandardItemModel(this))
{
    this->setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    this->setLayout(layout);
    m_box->setModel(m_comboModel);
    this->setConnected(true);
}

QEXTMvvmExternalPropertyComboEditor::~QEXTMvvmExternalPropertyComboEditor()
{

}

QSize QEXTMvvmExternalPropertyComboEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize QEXTMvvmExternalPropertyComboEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void QEXTMvvmExternalPropertyComboEditor::onIndexChanged(int index)
{
    CFMvvmExternalProperty property = m_data.value<CFMvvmExternalProperty>();
    std::vector<CFMvvmExternalProperty> mdata = m_getPropertiesCallback();

    if (index >= 0 && index < static_cast<int>(mdata.size()))
    {
        if (property != mdata[static_cast<size_t>(index)])
        {
            this->setDataIntern(QVariant::fromValue(mdata[static_cast<size_t>(index)]));
        }
    }
}

void QEXTMvvmExternalPropertyComboEditor::updateComponents()
{
    this->setConnected(false);

    m_comboModel->clear();

    QStandardItem *parentItem = m_comboModel->invisibleRootItem();
    std::vector<CFMvvmExternalProperty> mdata = m_getPropertiesCallback();
    std::vector<CFMvvmExternalProperty>::iterator iter;
    for (iter = mdata.begin(); iter != mdata.end(); ++iter)
    {
        QStandardItem *item = new QStandardItem(QString::fromStdString(iter->text()));
        parentItem->appendRow(item);
        item->setData(QColor(QString::fromStdString(iter->color())), Qt::DecorationRole);
    }
    m_box->setCurrentIndex(internIndex());

    this->setConnected(true);
}

int QEXTMvvmExternalPropertyComboEditor::internIndex()
{
    if (!m_data.canConvert<CFMvvmExternalProperty>())
    {
        return 0;
    }

    CFMvvmExternalProperty property = m_data.value<CFMvvmExternalProperty>();
    int result = -1;
    std::vector<CFMvvmExternalProperty> mdata = m_getPropertiesCallback();
    std::vector<CFMvvmExternalProperty>::iterator iter;
    for (iter = mdata.begin(); iter != mdata.end(); ++iter)
    {
        ++result;
        if (property.identifier() == (*iter).identifier())
        {
            return result;
        }
    }
    return result;
}

void QEXTMvvmExternalPropertyComboEditor::setConnected(bool isConnected)
{
    if (isConnected)
    {
        connect(m_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)), Qt::UniqueConnection);
    }
    else
    {
        disconnect(m_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onIndexChanged(int)));
    }
}
