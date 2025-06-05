#include <private/qextPEAbstractPropertyEditor_p.h>
#include <private/qextPEWidgetFactory_p.h>

#include <QMenu>
#include <QStyle>
#include <QAction>
#include <QPainter>
#include <QComboBox>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QToolButton>
#include <QFontDialog>
#include <QColorDialog>
#include <QStyleOption>
#include <QGlobalStatic>
#include <QAbstractItemView>


/***********************************************************************************************************************
 * QExtPESpinBoxFactory
***********************************************************************************************************************/
void QExtPESpinBoxFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSpinBox *editor = itEditor.next();
        if (editor->value() != value)
        {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void QExtPESpinBoxFactoryPrivate::slotRangeChanged(QExtPEProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPESpinBoxFactoryPrivate::slotSingleStepChanged(QExtPEProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtPESpinBoxFactoryPrivate::slotReadOnlyChanged( QExtPEProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtPESpinBoxFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    QMap<QSpinBox *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QSpinBox *, QExtPEProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor !=  ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPESpinBoxFactory::QExtPESpinBoxFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>(parent)
{
    d_ptr = new QExtPESpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPESpinBoxFactory::~QExtPESpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPESpinBoxFactory::connectPropertyManager(QExtPEIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtPEProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));
}

QWidget *QExtPESpinBoxFactory::createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{
    QSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPESpinBoxFactory::disconnectPropertyManager(QExtPEIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtPEProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));
}


/***********************************************************************************************************************
 * QExtPESliderFactory
***********************************************************************************************************************/

void QExtPESliderFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtPESliderFactoryPrivate::slotRangeChanged(QExtPEProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPESliderFactoryPrivate::slotSingleStepChanged(QExtPEProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtPESliderFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    QMap<QSlider *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QSlider *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor )
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPESliderFactory::QExtPESliderFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>(parent)
{
    d_ptr = new QExtPESliderFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPESliderFactory::~QExtPESliderFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPESliderFactory::connectPropertyManager(QExtPEIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
}

QWidget *QExtPESliderFactory::createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{
    QSlider *editor = new QSlider(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPESliderFactory::disconnectPropertyManager(QExtPEIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
}


/***********************************************************************************************************************
 * QExtPEScrollBarFactory
***********************************************************************************************************************/
void QExtPEScrollBarFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtPEScrollBarFactoryPrivate::slotRangeChanged(QExtPEProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEScrollBarFactoryPrivate::slotSingleStepChanged(QExtPEProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QScrollBar *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtPEScrollBarFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    QMap<QScrollBar *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QScrollBar *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEScrollBarFactory::QExtPEScrollBarFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEIntPropertyManager>(parent)
{
    d_ptr = new QExtPEScrollBarFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPEScrollBarFactory::~QExtPEScrollBarFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEScrollBarFactory::connectPropertyManager(QExtPEIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
}

QWidget *QExtPEScrollBarFactory::createEditor(QExtPEIntPropertyManager *manager, QExtPEProperty *property,
                                            QWidget *parent)
{
    QScrollBar *editor = new QScrollBar(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEScrollBarFactory::disconnectPropertyManager(QExtPEIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtPEProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtPEProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtPEProperty *, int)));
}


/***********************************************************************************************************************
 * QExtBoolEdit
***********************************************************************************************************************/
QExtBoolEdit::QExtBoolEdit(QWidget *parent)
    : QWidget(parent)
    , m_checkBox(new QCheckBox(this))
    , m_textVisible(true)
{
    QHBoxLayout *lt = new QHBoxLayout;
    if (QApplication::layoutDirection() == Qt::LeftToRight)
    {
        lt->setContentsMargins(4, 0, 0, 0);
    }
    else
    {
        lt->setContentsMargins(0, 0, 4, 0);
    }
    lt->addWidget(m_checkBox);
    this->setLayout(lt);
    connect(m_checkBox, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
    // bugfix:Avoid focus shadow masks when using customizing indicator images using QSS
    // this->setFocusProxy(m_checkBox);
    m_checkBox->setText(tr("True"));
}

void QExtBoolEdit::setTextVisible(bool textVisible)
{
    if (m_textVisible == textVisible)
    {
        return;
    }

    m_textVisible = textVisible;
    if (m_textVisible)
    {
        m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
    }
    else
    {
        m_checkBox->setText(QString());
    }
}

Qt::CheckState QExtBoolEdit::checkState() const
{
    return m_checkBox->checkState();
}

void QExtBoolEdit::setCheckState(Qt::CheckState state)
{
    m_checkBox->setCheckState(state);
}

bool QExtBoolEdit::isChecked() const
{
    return m_checkBox->isChecked();
}

void QExtBoolEdit::setChecked(bool c)
{
    m_checkBox->setChecked(c);
    if (!m_textVisible)
    {
        return;
    }
    m_checkBox->setText(isChecked() ? tr("True") : tr("False"));
}

bool QExtBoolEdit::blockCheckBoxSignals(bool block)
{
    return m_checkBox->blockSignals(block);
}

void QExtBoolEdit::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_checkBox->click();
        event->accept();
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void QExtBoolEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/***********************************************************************************************************************
 * QExtPECheckBoxFactory
***********************************************************************************************************************/
void QExtPECheckBoxFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, bool value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QExtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QExtBoolEdit *editor = itEditor.next();
        editor->blockCheckBoxSignals(true);
        editor->setChecked(value);
        editor->blockCheckBoxSignals(false);
    }
}

void QExtPECheckBoxFactoryPrivate::slotTextVisibleChanged(QExtPEProperty *property, bool textVisible)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEBoolPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QExtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QExtBoolEdit *editor = itEditor.next();
        editor->setTextVisible(textVisible);
    }
}

void QExtPECheckBoxFactoryPrivate::slotSetValue(bool value)
{
    QObject *object = q_ptr->sender();
    QMap<QExtBoolEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QExtBoolEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEBoolPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPECheckBoxFactory::QExtPECheckBoxFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEBoolPropertyManager>(parent)
{
    d_ptr = new QExtPECheckBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPECheckBoxFactory::~QExtPECheckBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPECheckBoxFactory::connectPropertyManager(QExtPEBoolPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, bool)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, bool)));
    connect(manager, SIGNAL(textVisibleChanged(QExtPEProperty *, bool)),
            this, SLOT(slotTextVisibleChanged(QExtPEProperty *, bool)));
}

QWidget *QExtPECheckBoxFactory::createEditor(QExtPEBoolPropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{
    QExtBoolEdit *editor = d_ptr->createEditor(property, parent);
    editor->setChecked(manager->value(property));
    editor->setTextVisible(manager->textVisible(property));

    connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetValue(bool)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPECheckBoxFactory::disconnectPropertyManager(QExtPEBoolPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, bool)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, bool)));
    disconnect(manager, SIGNAL(textVisibleChanged(QExtPEProperty *, bool)),
               this, SLOT(slotTextVisibleChanged(QExtPEProperty *, bool)));
}


/***********************************************************************************************************************
 * QExtPEDoubleSpinBoxFactory
***********************************************************************************************************************/
void QExtPEDoubleSpinBoxFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, double value)
{
    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QDoubleSpinBox *editor = itEditor.next();
        if (editor->value() != value)
        {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void QExtPEDoubleSpinBoxFactoryPrivate::slotRangeChanged(QExtPEProperty *property, double min, double max)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext())
    {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEDoubleSpinBoxFactoryPrivate::slotSingleStepChanged(QExtPEProperty *property, double step)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext())
    {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtPEDoubleSpinBoxFactoryPrivate::slotReadOnlyChanged( QExtPEProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtPEDoubleSpinBoxFactoryPrivate::slotDecimalsChanged(QExtPEProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext())
    {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDecimals(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEDoubleSpinBoxFactoryPrivate::slotSetValue(double value)
{
    QObject *object = q_ptr->sender();
    QMap<QDoubleSpinBox *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QDoubleSpinBox *, QExtPEProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEDoubleSpinBoxFactory::QExtPEDoubleSpinBoxFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEDoublePropertyManager>(parent)
{
    d_ptr = new QExtPEDoubleSpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPEDoubleSpinBoxFactory::~QExtPEDoubleSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEDoubleSpinBoxFactory::connectPropertyManager(QExtPEDoublePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, double)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, double)));
    connect(manager, SIGNAL(rangeChanged(QExtPEProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, double, double)));
    connect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, double)),
            this, SLOT(slotSingleStepChanged(QExtPEProperty *, double)));
    connect(manager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtPEProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));
}

QWidget *QExtPEDoubleSpinBoxFactory::createEditor(QExtPEDoublePropertyManager *manager,
                                                QExtPEProperty *property, QWidget *parent)
{
    QDoubleSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setDecimals(manager->decimals(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEDoubleSpinBoxFactory::disconnectPropertyManager(QExtPEDoublePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, double)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, double)));
    disconnect(manager, SIGNAL(rangeChanged(QExtPEProperty *, double, double)),
               this, SLOT(slotRangeChanged(QExtPEProperty *, double, double)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtPEProperty *, double)),
               this, SLOT(slotSingleStepChanged(QExtPEProperty *, double)));
    disconnect(manager, SIGNAL(decimalsChanged(QExtPEProperty *, int)),
               this, SLOT(slotDecimalsChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtPEProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));
}


/***********************************************************************************************************************
 * QExtPELineEditFactory
***********************************************************************************************************************/
void QExtPELineEditFactoryPrivate::slotPropertyChanged(QExtPEProperty *property,
                                                     const QString &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QLineEdit *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QLineEdit *editor = itEditor.next();
        if (editor->text() != value)
        {
            editor->blockSignals(true);
            editor->setText(value);
            editor->blockSignals(false);
        }
    }
}

void QExtPELineEditFactoryPrivate::slotRegExpChanged(QExtPEProperty *property,
                                                   const QRegExp &regExp)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        const QValidator *oldValidator = editor->validator();
        QValidator *newValidator = QEXT_NULLPTR;
        if (regExp.isValid())
        {
            newValidator = new QRegExpValidator(regExp, editor);
        }
        editor->setValidator(newValidator);
        if (oldValidator)
        {
            delete oldValidator;
        }
        editor->blockSignals(false);
    }
}

void QExtPELineEditFactoryPrivate::slotEchoModeChanged(QExtPEProperty *property, int echoMode)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setEchoMode((EchoMode)echoMode);
        editor->blockSignals(false);
    }
}

void QExtPELineEditFactoryPrivate::slotReadOnlyChanged( QExtPEProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtPELineEditFactoryPrivate::slotSetValue(const QString &value)
{
    QObject *object = q_ptr->sender();
    QMap<QLineEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QLineEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEStringPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}



QExtPELineEditFactory::QExtPELineEditFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEStringPropertyManager>(parent)
{
    d_ptr = new QExtPELineEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPELineEditFactory::~QExtPELineEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPELineEditFactory::connectPropertyManager(QExtPEStringPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QString &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QString &)));
    connect(manager, SIGNAL(regExpChanged(QExtPEProperty *, const QRegExp &)),
            this, SLOT(slotRegExpChanged(QExtPEProperty *, const QRegExp &)));
    connect(manager, SIGNAL(echoModeChanged(QExtPEProperty*, int)),
            this, SLOT(slotEchoModeChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtPEProperty*, bool)),
            this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));
}

QWidget *QExtPELineEditFactory::createEditor(QExtPEStringPropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{

    QLineEdit *editor = d_ptr->createEditor(property, parent);
    editor->setEchoMode((EchoMode)manager->echoMode(property));
    editor->setReadOnly(manager->isReadOnly(property));
    QRegExp regExp = manager->regExp(property);
    if (regExp.isValid())
    {
        QValidator *validator = new QRegExpValidator(regExp, editor);
        editor->setValidator(validator);
    }
    editor->setText(manager->value(property));

    connect(editor, SIGNAL(textChanged(const QString &)), this, SLOT(slotSetValue(const QString &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPELineEditFactory::disconnectPropertyManager(QExtPEStringPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QString &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QString &)));
    disconnect(manager, SIGNAL(regExpChanged(QExtPEProperty *, const QRegExp &)),
               this, SLOT(slotRegExpChanged(QExtPEProperty *, const QRegExp &)));
    disconnect(manager, SIGNAL(echoModeChanged(QExtPEProperty*,int)),
               this, SLOT(slotEchoModeChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtPEProperty*, bool)),
               this, SLOT(slotReadOnlyChanged(QExtPEProperty *, bool)));

}


/***********************************************************************************************************************
 * QExtPEDateEditFactory
***********************************************************************************************************************/
void QExtPEDateEditFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QDate &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDate(value);
        editor->blockSignals(false);
    }
}

void QExtPEDateEditFactoryPrivate::slotRangeChanged(QExtPEProperty *property, const QDate &min, const QDate &max)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEDatePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateRange(min, max);
        editor->setDate(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEDateEditFactoryPrivate::slotSetValue(const QDate &value)
{
    QObject *object = q_ptr->sender();
    QMap<QDateEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QDateEdit *, QExtPEProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEDatePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEDateEditFactory::QExtPEDateEditFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEDatePropertyManager>(parent)
{
    d_ptr = new QExtPEDateEditFactoryPrivate();
    d_ptr->q_ptr = this;
}

QExtPEDateEditFactory::~QExtPEDateEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEDateEditFactory::connectPropertyManager(QExtPEDatePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QDate &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QDate &)));
    connect(manager, SIGNAL(rangeChanged(QExtPEProperty *, const QDate &, const QDate &)),
            this, SLOT(slotRangeChanged(QExtPEProperty *, const QDate &, const QDate &)));
}

QWidget *QExtPEDateEditFactory::createEditor(QExtPEDatePropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{
    QDateEdit *editor = d_ptr->createEditor(property, parent);
    editor->setCalendarPopup(true);
    editor->setDateRange(manager->minimum(property), manager->maximum(property));
    editor->setDate(manager->value(property));

    connect(editor, SIGNAL(dateChanged(const QDate &)), this, SLOT(slotSetValue(const QDate &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEDateEditFactory::disconnectPropertyManager(QExtPEDatePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QDate &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QDate &)));
    disconnect(manager, SIGNAL(rangeChanged(QExtPEProperty *, const QDate &, const QDate &)),
               this, SLOT(slotRangeChanged(QExtPEProperty *, const QDate &, const QDate &)));
}



/***********************************************************************************************************************
 * QExtPETimeEditFactory
***********************************************************************************************************************/
void QExtPETimeEditFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QTime &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }
    QListIterator<QTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setTime(value);
        editor->blockSignals(false);
    }
}

void QExtPETimeEditFactoryPrivate::slotSetValue(const QTime &value)
{
    QObject *object = q_ptr->sender();
    QMap<QTimeEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QTimeEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPETimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPETimeEditFactory::QExtPETimeEditFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPETimePropertyManager>(parent)
{
    d_ptr = new QExtPETimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPETimeEditFactory::~QExtPETimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPETimeEditFactory::connectPropertyManager(QExtPETimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QTime &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QTime &)));
}

QWidget *QExtPETimeEditFactory::createEditor(QExtPETimePropertyManager *manager, QExtPEProperty *property, QWidget *parent)
{
    QTimeEdit *editor = d_ptr->createEditor(property, parent);
    editor->setTime(manager->value(property));

    connect(editor, SIGNAL(timeChanged(const QTime &)), this, SLOT(slotSetValue(const QTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPETimeEditFactory::disconnectPropertyManager(QExtPETimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QTime &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QTime &)));
}



/***********************************************************************************************************************
 * QExtPEDateTimeEditFactory
***********************************************************************************************************************/
void QExtPEDateTimeEditFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QDateTime &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QDateTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QDateTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateTime(value);
        editor->blockSignals(false);
    }
}

void QExtPEDateTimeEditFactoryPrivate::slotSetValue(const QDateTime &value)
{
    QObject *object = q_ptr->sender();
    QMap<QDateTimeEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QDateTimeEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEDateTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEDateTimeEditFactory::QExtPEDateTimeEditFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEDateTimePropertyManager>(parent)
{
    d_ptr = new QExtPEDateTimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPEDateTimeEditFactory::~QExtPEDateTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEDateTimeEditFactory::connectPropertyManager(QExtPEDateTimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QDateTime &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QDateTime &)));
}

QWidget *QExtPEDateTimeEditFactory::createEditor(QExtPEDateTimePropertyManager *manager, QExtPEProperty *property,
                                               QWidget *parent)
{
    QDateTimeEdit *editor =  d_ptr->createEditor(property, parent);
    editor->setDateTime(manager->value(property));

    connect(editor, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(slotSetValue(const QDateTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEDateTimeEditFactory::disconnectPropertyManager(QExtPEDateTimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QDateTime &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QDateTime &)));
}



/***********************************************************************************************************************
 * QExtKeySequenceEdit
***********************************************************************************************************************/
QExtKeySequenceEdit::QExtKeySequenceEdit(QWidget *parent)
    : QWidget(parent), m_num(0), m_lineEdit(new QLineEdit(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->setMargin(0);
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setFocusProxy(this);
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
}

bool QExtKeySequenceEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_lineEdit && e->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent *c = static_cast<QContextMenuEvent *>(e);
        QMenu *menu = m_lineEdit->createStandardContextMenu();
        const QList<QAction *> actions = menu->actions();
        QListIterator<QAction *> itAction(actions);
        while (itAction.hasNext())
        {
            QAction *action = itAction.next();
            action->setShortcut(QKeySequence());
            QString actionString = action->text();
            const int pos = actionString.lastIndexOf(QLatin1Char('\t'));
            if (pos > 0)
            {
                actionString.remove(pos, actionString.length() - pos);
            }
            action->setText(actionString);
        }
        QAction *actionBefore = QEXT_NULLPTR;
        if (actions.count() > 0)
        {
            actionBefore = actions[0];
        }
        QAction *clearAction = new QAction(tr("Clear Shortcut"), menu);
        menu->insertAction(actionBefore, clearAction);
        menu->insertSeparator(actionBefore);
        clearAction->setEnabled(!m_keySequence.isEmpty());
        connect(clearAction, SIGNAL(triggered()), this, SLOT(slotClearShortcut()));
        menu->exec(c->globalPos());
        delete menu;
        e->accept();
        return true;
    }

    return QWidget::eventFilter(o, e);
}

void QExtKeySequenceEdit::slotClearShortcut()
{
    if (m_keySequence.isEmpty())
    {
        return;
    }
    setKeySequence(QKeySequence());
    emit keySequenceChanged(m_keySequence);
}

void QExtKeySequenceEdit::handleKeyEvent(QKeyEvent *e)
{
    int nextKey = e->key();
    if (nextKey == Qt::Key_Control || nextKey == Qt::Key_Shift || nextKey == Qt::Key_Meta ||
        nextKey == Qt::Key_Alt || nextKey == Qt::Key_Super_L || nextKey == Qt::Key_AltGr)
    {
        return;
    }

    nextKey |= translateModifiers(e->modifiers(), e->text());
    int k0 = m_keySequence[0];
    int k1 = m_keySequence[1];
    int k2 = m_keySequence[2];
    int k3 = m_keySequence[3];
    switch (m_num)
    {
    case 0: k0 = nextKey; k1 = 0; k2 = 0; k3 = 0; break;
    case 1: k1 = nextKey; k2 = 0; k3 = 0; break;
    case 2: k2 = nextKey; k3 = 0; break;
    case 3: k3 = nextKey; break;
    default: break;
    }
    ++m_num;
    if (m_num > 3)
    {
        m_num = 0;
    }
    m_keySequence = QKeySequence(k0, k1, k2, k3);
    m_lineEdit->setText(m_keySequence.toString(QKeySequence::NativeText));
    e->accept();
    emit keySequenceChanged(m_keySequence);
}

void QExtKeySequenceEdit::setKeySequence(const QKeySequence &sequence)
{
    if (sequence == m_keySequence)
    {
        return;
    }
    m_num = 0;
    m_keySequence = sequence;
    m_lineEdit->setText(m_keySequence.toString(QKeySequence::NativeText));
}

QKeySequence QExtKeySequenceEdit::keySequence() const
{
    return m_keySequence;
}

int QExtKeySequenceEdit::translateModifiers(Qt::KeyboardModifiers state, const QString &text) const
{
    int result = 0;
    if ((state & Qt::ShiftModifier) && (text.size() == 0 || !text.at(0).isPrint() ||
                                        text.at(0).isLetter() || text.at(0).isSpace()))
    {
        result |= Qt::SHIFT;
    }
    if (state & Qt::ControlModifier)
    {
        result |= Qt::CTRL;
    }
    if (state & Qt::MetaModifier)
    {
        result |= Qt::META;
    }
    if (state & Qt::AltModifier)
    {
        result |= Qt::ALT;
    }
    return result;
}

void QExtKeySequenceEdit::focusInEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    m_lineEdit->selectAll();
    QWidget::focusInEvent(e);
}

void QExtKeySequenceEdit::focusOutEvent(QFocusEvent *e)
{
    m_num = 0;
    m_lineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void QExtKeySequenceEdit::keyPressEvent(QKeyEvent *e)
{
    this->handleKeyEvent(e);
    e->accept();
}

void QExtKeySequenceEdit::keyReleaseEvent(QKeyEvent *e)
{
    m_lineEdit->event(e);
}

void QExtKeySequenceEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool QExtKeySequenceEdit::event(QEvent *e)
{
    if (e->type() == QEvent::Shortcut || e->type() == QEvent::ShortcutOverride || e->type() == QEvent::KeyRelease)
    {
        e->accept();
        return true;
    }
    return QWidget::event(e);
}

/***********************************************************************************************************************
 * QExtPEKeySequenceEditorFactory
***********************************************************************************************************************/
void QExtPEKeySequenceEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QKeySequence &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QExtKeySequenceEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QExtKeySequenceEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setKeySequence(value);
        editor->blockSignals(false);
    }
}

void QExtPEKeySequenceEditorFactoryPrivate::slotSetValue(const QKeySequence &value)
{
    QObject *object = q_ptr->sender();
    QMap<QExtKeySequenceEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QExtKeySequenceEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor =  m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEKeySequencePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEKeySequenceEditorFactory::QExtPEKeySequenceEditorFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEKeySequencePropertyManager>(parent)
{
    d_ptr = new QExtPEKeySequenceEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPEKeySequenceEditorFactory::~QExtPEKeySequenceEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEKeySequenceEditorFactory::connectPropertyManager(QExtPEKeySequencePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QKeySequence &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QKeySequence &)));
}

QWidget *QExtPEKeySequenceEditorFactory::createEditor(QExtPEKeySequencePropertyManager *manager,
                                                    QExtPEProperty *property, QWidget *parent)
{
    QExtKeySequenceEdit *editor = d_ptr->createEditor(property, parent);
    editor->setKeySequence(manager->value(property));

    connect(editor, SIGNAL(keySequenceChanged(const QKeySequence &)), this, SLOT(slotSetValue(const QKeySequence &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEKeySequenceEditorFactory::disconnectPropertyManager(QExtPEKeySequencePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QKeySequence &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QKeySequence &)));
}



/***********************************************************************************************************************
 * QExtCharEdit
***********************************************************************************************************************/
QExtCharEdit::QExtCharEdit(QWidget *parent)
    : QWidget(parent),  m_lineEdit(new QLineEdit(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->setMargin(0);
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setFocusProxy(this);
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
}

bool QExtCharEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_lineEdit && e->type() == QEvent::ContextMenu)
    {
        QContextMenuEvent *c = static_cast<QContextMenuEvent *>(e);
        QMenu *menu = m_lineEdit->createStandardContextMenu();
        QList<QAction *> actions = menu->actions();
        QListIterator<QAction *> itAction(actions);
        while (itAction.hasNext())
        {
            QAction *action = itAction.next();
            action->setShortcut(QKeySequence());
            QString actionString = action->text();
            const int pos = actionString.lastIndexOf(QLatin1Char('\t'));
            if (pos > 0)
            {
                actionString = actionString.remove(pos, actionString.length() - pos);
            }
            action->setText(actionString);
        }
        QAction *actionBefore = QEXT_NULLPTR;
        if (actions.count() > 0)
        {
            actionBefore = actions[0];
        }
        QAction *clearAction = new QAction(tr("Clear Char"), menu);
        menu->insertAction(actionBefore, clearAction);
        menu->insertSeparator(actionBefore);
        clearAction->setEnabled(!m_value.isNull());
        connect(clearAction, SIGNAL(triggered()), this, SLOT(slotClearChar()));
        menu->exec(c->globalPos());
        delete menu;
        e->accept();
        return true;
    }

    return QWidget::eventFilter(o, e);
}

void QExtCharEdit::slotClearChar()
{
    if (m_value.isNull())
    {
        return;
    }
    this->setValue(QChar());
    emit this->valueChanged(m_value);
}

void QExtCharEdit::handleKeyEvent(QKeyEvent *e)
{
    const int key = e->key();
    switch (key)
    {
    case Qt::Key_Control:
    case Qt::Key_Shift:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_Super_L:
    case Qt::Key_Return:
        return;
    default:
        break;
    }

    const QString text = e->text();
    if (text.count() != 1)
    {
        return;
    }

    const QChar c = text.at(0);
    if (!c.isPrint())
    {
        return;
    }

    if (m_value == c)
    {
        return;
    }

    m_value = c;
    const QString str = m_value.isNull() ? QString() : QString(m_value);
    m_lineEdit->setText(str);
    e->accept();
    emit this->valueChanged(m_value);
}

void QExtCharEdit::setValue(const QChar &value)
{
    if (value == m_value)
    {
        return;
    }

    m_value = value;
    QString str = value.isNull() ? QString() : QString(value);
    m_lineEdit->setText(str);
}

QChar QExtCharEdit::value() const
{
    return m_value;
}

void QExtCharEdit::focusInEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    m_lineEdit->selectAll();
    QWidget::focusInEvent(e);
}

void QExtCharEdit::focusOutEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void QExtCharEdit::keyPressEvent(QKeyEvent *e)
{
    this->handleKeyEvent(e);
    e->accept();
}

void QExtCharEdit::keyReleaseEvent(QKeyEvent *e)
{
    m_lineEdit->event(e);
}

void QExtCharEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool QExtCharEdit::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Shortcut:
    case QEvent::ShortcutOverride:
    case QEvent::KeyRelease:
        e->accept();
        return true;
    default:
        break;
    }
    return QWidget::event(e);
}



/***********************************************************************************************************************
 * QExtPECharEditorFactory
***********************************************************************************************************************/
void QExtPECharEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property,
                                                       const QChar &value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QExtCharEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QExtCharEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtPECharEditorFactoryPrivate::slotSetValue(const QChar &value)
{
    QObject *object = q_ptr->sender();
    QMap<QExtCharEdit *, QExtPEProperty *>::ConstIterator itEditor;
    const QMap<QExtCharEdit *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPECharPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPECharEditorFactory::QExtPECharEditorFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPECharPropertyManager>(parent)
{
    d_ptr = new QExtPECharEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPECharEditorFactory::~QExtPECharEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPECharEditorFactory::connectPropertyManager(QExtPECharPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QChar &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QChar &)));
}

QWidget *QExtPECharEditorFactory::createEditor(QExtPECharPropertyManager *manager,
                                             QExtPEProperty *property, QWidget *parent)
{
    QExtCharEdit *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(const QChar &)), this, SLOT(slotSetValue(const QChar &)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPECharEditorFactory::disconnectPropertyManager(QExtPECharPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QChar &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QChar &)));
}



/***********************************************************************************************************************
 * QExtPEEnumEditorFactory
***********************************************************************************************************************/
void QExtPEEnumEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setCurrentIndex(value);
        editor->blockSignals(false);
    }
}

void QExtPEEnumEditorFactoryPrivate::slotEnumNamesChanged(QExtPEProperty *property, const QStringList &enumNames)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    QMap<int, QIcon> enumIcons = manager->enumIcons(property);

    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->clear();
        editor->addItems(enumNames);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
        {
            editor->setItemIcon(i, enumIcons.value(i));
        }
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEEnumEditorFactoryPrivate::slotEnumIconsChanged(QExtPEProperty *property, const QMap<int, QIcon> &enumIcons)
{
    if (!m_createdEditors.contains(property))
    {
        return;
    }

    QExtPEEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    {
        return;
    }

    const QStringList enumNames = manager->enumNames(property);
    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext())
    {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
        {
            editor->setItemIcon(i, enumIcons.value(i));
        }
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtPEEnumEditorFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    QMap<QComboBox *, QExtPEProperty *>::ConstIterator itEditor;
    const  QMap<QComboBox *, QExtPEProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEEnumPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEEnumEditorFactory::QExtPEEnumEditorFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPEEnumPropertyManager>(parent)
{
    d_ptr = new QExtPEEnumEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

QExtPEEnumEditorFactory::~QExtPEEnumEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEEnumEditorFactory::connectPropertyManager(QExtPEEnumPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    connect(manager, SIGNAL(enumNamesChanged(QExtPEProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtPEProperty *, const QStringList &)));
}

QWidget *QExtPEEnumEditorFactory::createEditor(QExtPEEnumPropertyManager *manager, QExtPEProperty *property,
                                             QWidget *parent)
{
    QComboBox *editor = d_ptr->createEditor(property, parent);
    editor->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    editor->setMinimumContentsLength(1);
    editor->view()->setTextElideMode(Qt::ElideRight);
    QStringList enumNames = manager->enumNames(property);
    editor->addItems(enumNames);
    QMap<int, QIcon> enumIcons = manager->enumIcons(property);
    const int enumNamesCount = enumNames.count();
    for (int i = 0; i < enumNamesCount; i++)
    {
        editor->setItemIcon(i, enumIcons.value(i));
    }
    editor->setCurrentIndex(manager->value(property));

    connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEEnumEditorFactory::disconnectPropertyManager(QExtPEEnumPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, int)));
    disconnect(manager, SIGNAL(enumNamesChanged(QExtPEProperty *, const QStringList &)),
               this, SLOT(slotEnumNamesChanged(QExtPEProperty *, const QStringList &)));
}



/***********************************************************************************************************************
** QExtCursorDatabase
***********************************************************************************************************************/
QExtCursorDatabase::QExtCursorDatabase()
{
    this->appendCursor(Qt::ArrowCursor, QCoreApplication::translate("QExtCursorDatabase", "Arrow"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-arrow.png")));
    this->appendCursor(Qt::UpArrowCursor, QCoreApplication::translate("QExtCursorDatabase", "Up Arrow"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-uparrow.png")));
    this->appendCursor(Qt::CrossCursor, QCoreApplication::translate("QExtCursorDatabase", "Cross"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-cross.png")));
    this->appendCursor(Qt::WaitCursor, QCoreApplication::translate("QExtCursorDatabase", "Wait"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-wait.png")));
    this->appendCursor(Qt::IBeamCursor, QCoreApplication::translate("QExtCursorDatabase", "IBeam"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-ibeam.png")));
    this->appendCursor(Qt::SizeVerCursor, QCoreApplication::translate("QExtCursorDatabase", "Size Vertical"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizev.png")));
    this->appendCursor(Qt::SizeHorCursor, QCoreApplication::translate("QExtCursorDatabase", "Size Horizontal"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeh.png")));
    this->appendCursor(Qt::SizeFDiagCursor, QCoreApplication::translate("QExtCursorDatabase", "Size Backslash"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizef.png")));
    this->appendCursor(Qt::SizeBDiagCursor, QCoreApplication::translate("QExtCursorDatabase", "Size Slash"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeb.png")));
    this->appendCursor(Qt::SizeAllCursor, QCoreApplication::translate("QExtCursorDatabase", "Size All"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-sizeall.png")));
    this->appendCursor(Qt::BlankCursor, QCoreApplication::translate("QExtCursorDatabase", "Blank"),
                       QIcon());
    this->appendCursor(Qt::SplitVCursor, QCoreApplication::translate("QExtCursorDatabase", "Split Vertical"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-vsplit.png")));
    this->appendCursor(Qt::SplitHCursor, QCoreApplication::translate("QExtCursorDatabase", "Split Horizontal"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hsplit.png")));
    this->appendCursor(Qt::PointingHandCursor, QCoreApplication::translate("QExtCursorDatabase", "Pointing Hand"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-hand.png")));
    this->appendCursor(Qt::ForbiddenCursor, QCoreApplication::translate("QExtCursorDatabase", "Forbidden"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-forbidden.png")));
    this->appendCursor(Qt::OpenHandCursor, QCoreApplication::translate("QExtCursorDatabase", "Open Hand"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-openhand.png")));
    this->appendCursor(Qt::ClosedHandCursor, QCoreApplication::translate("QExtCursorDatabase", "Closed Hand"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-closedhand.png")));
    this->appendCursor(Qt::WhatsThisCursor, QCoreApplication::translate("QExtCursorDatabase", "What's This"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-whatsthis.png")));
    this->appendCursor(Qt::BusyCursor, QCoreApplication::translate("QExtCursorDatabase", "Busy"),
                       QIcon(QLatin1String(":/qt-project.org/qtpropertybrowser/images/cursor-busy.png")));
}

void QExtCursorDatabase::clear()
{
    m_cursorNames.clear();
    m_cursorIcons.clear();
    m_valueToCursorShape.clear();
    m_cursorShapeToValue.clear();
}

void QExtCursorDatabase::appendCursor(Qt::CursorShape shape, const QString &name, const QIcon &icon)
{
    if (m_cursorShapeToValue.contains(shape))
    {
        return;
    }
    const int value = m_cursorNames.count();
    m_cursorNames.append(name);
    m_cursorIcons.insert(value, icon);
    m_valueToCursorShape.insert(value, shape);
    m_cursorShapeToValue.insert(shape, value);
}

QStringList QExtCursorDatabase::cursorShapeNames() const
{
    return m_cursorNames;
}

QMap<int, QIcon> QExtCursorDatabase::cursorShapeIcons() const
{
    return m_cursorIcons;
}

QString QExtCursorDatabase::cursorToShapeName(const QCursor &cursor) const
{
    const int val = cursorToValue(cursor);
    if (val >= 0)
    {
        return m_cursorNames.at(val);
    }
    return QString();
}

QIcon QExtCursorDatabase::cursorToShapeIcon(const QCursor &cursor) const
{
    const int val = cursorToValue(cursor);
    return m_cursorIcons.value(val);
}

int QExtCursorDatabase::cursorToValue(const QCursor &cursor) const
{
#ifndef QT_NO_CURSOR
    Qt::CursorShape shape = cursor.shape();
    if (m_cursorShapeToValue.contains(shape))
    {
        return m_cursorShapeToValue[shape];
    }
#endif
    return -1;
}

#ifndef QT_NO_CURSOR
QCursor QExtCursorDatabase::valueToCursor(int value) const
{
    if (m_valueToCursorShape.contains(value))
    {
        return QCursor(m_valueToCursorShape[value]);
    }
    return QCursor();
}
#endif

/***********************************************************************************************************************
 * QExtPECursorEditorFactory
***********************************************************************************************************************/
Q_GLOBAL_STATIC(QExtCursorDatabase, cursorEditorFactoryDatabase)

QExtPECursorEditorFactoryPrivate::QExtPECursorEditorFactoryPrivate()
    : m_updatingEnum(false)
{

}

void QExtPECursorEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QCursor &cursor)
{
    // update enum property
    QExtPEProperty *enumProp = m_propertyToEnum.value(property);
    if (!enumProp)
    {
        return;
    }

    m_updatingEnum = true;
    m_enumPropertyManager->setValue(enumProp, cursorEditorFactoryDatabase()->cursorToValue(cursor));
    m_updatingEnum = false;
}

void QExtPECursorEditorFactoryPrivate::slotEnumChanged(QExtPEProperty *property, int value)
{
    if (m_updatingEnum)
    {
        return;
    }
    // update cursor property
    QExtPEProperty *prop = m_enumToProperty.value(property);
    if (!prop)
    {
        return;
    }
    QExtPECursorPropertyManager *cursorManager = q_ptr->propertyManager(prop);
    if (!cursorManager)
    {
        return;
    }
#ifndef QT_NO_CURSOR
    cursorManager->setValue(prop, QCursor(cursorEditorFactoryDatabase()->valueToCursor(value)));
#endif
}

void QExtPECursorEditorFactoryPrivate::slotEditorDestroyed(QObject *object)
{
    // remove from m_editorToEnum map;
    // remove from m_enumToEditors map;
    // if m_enumToEditors doesn't contains more editors delete enum property;
    QMap<QWidget *, QExtPEProperty *>::ConstIterator itEditor;
    const  QMap<QWidget *, QExtPEProperty *>::ConstIterator ecend = m_editorToEnum.constEnd();
    for (itEditor = m_editorToEnum.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QWidget *editor = itEditor.key();
            QExtPEProperty *enumProp = itEditor.value();
            m_editorToEnum.remove(editor);
            m_enumToEditors[enumProp].removeAll(editor);
            if (m_enumToEditors[enumProp].isEmpty())
            {
                m_enumToEditors.remove(enumProp);
                QExtPEProperty *property = m_enumToProperty.value(enumProp);
                m_enumToProperty.remove(enumProp);
                m_propertyToEnum.remove(property);
                delete enumProp;
            }
            return;
        }
    }
}


QExtPECursorEditorFactory::QExtPECursorEditorFactory(QObject *parent)
    : QExtPEAbstractWidgetFactory<QExtPECursorPropertyManager>(parent)
{
    d_ptr = new QExtPECursorEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_enumEditorFactory = new QExtPEEnumEditorFactory(this);
    d_ptr->m_enumPropertyManager = new QExtPEEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtPEProperty *, int)),
            this, SLOT(slotEnumChanged(QExtPEProperty *, int)));
    d_ptr->m_enumEditorFactory->addPropertyManager(d_ptr->m_enumPropertyManager);
}

QExtPECursorEditorFactory::~QExtPECursorEditorFactory()
{
    delete d_ptr;
}

void QExtPECursorEditorFactory::connectPropertyManager(QExtPECursorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QCursor &)),
            this, SLOT(slotPropertyChanged(QExtPEProperty *, const QCursor &)));
}

QWidget *QExtPECursorEditorFactory::createEditor(QExtPECursorPropertyManager *manager, QExtPEProperty *property,
                                               QWidget *parent)
{
    QExtPEProperty *enumProp = QEXT_NULLPTR;
    if (d_ptr->m_propertyToEnum.contains(property))
    {
        enumProp = d_ptr->m_propertyToEnum[property];
    }
    else
    {
        enumProp = d_ptr->m_enumPropertyManager->addProperty(property->propertyName());
        d_ptr->m_enumPropertyManager->setEnumNames(enumProp, cursorEditorFactoryDatabase()->cursorShapeNames());
        d_ptr->m_enumPropertyManager->setEnumIcons(enumProp, cursorEditorFactoryDatabase()->cursorShapeIcons());
#ifndef QT_NO_CURSOR
        d_ptr->m_enumPropertyManager->setValue(enumProp, cursorEditorFactoryDatabase()->cursorToValue(manager->value(property)));
#endif
        d_ptr->m_propertyToEnum[property] = enumProp;
        d_ptr->m_enumToProperty[enumProp] = property;
    }
    QExtPEAbstractWidgetFactoryBase *af = d_ptr->m_enumEditorFactory;
    QWidget *editor = af->createEditor(enumProp, parent);
    d_ptr->m_enumToEditors[enumProp].append(editor);
    d_ptr->m_editorToEnum[editor] = enumProp;
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPECursorEditorFactory::disconnectPropertyManager(QExtPECursorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty *, const QCursor &)),
               this, SLOT(slotPropertyChanged(QExtPEProperty *, const QCursor &)));
}



/***********************************************************************************************************************
 * QExtColorEditWidget
***********************************************************************************************************************/
QExtColorEditWidget::QExtColorEditWidget(QWidget *parent)
    : QWidget(parent)
    , m_pixmapLabel(new QLabel)
    , m_label(new QLabel)
    , m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setMargin(0);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setToolButtonStyle(Qt::ToolButtonTextOnly);
    m_button->setText(tr("..."));
    m_button->setFixedWidth(qMax(30, this->height()));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    this->setFocusProxy(m_button);
    this->setFocusPolicy(m_button->focusPolicy());
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::brushValuePixmap(QBrush(m_color)));
    m_label->setText(QExtPropertyBrowserUtils::colorValueText(m_color));
}

void QExtColorEditWidget::setValue(const QColor &c)
{
    if (m_color != c)
    {
        m_color = c;
        m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::brushValuePixmap(QBrush(c)));
        m_label->setText(QExtPropertyBrowserUtils::colorValueText(c));
    }
}

void QExtColorEditWidget::buttonClicked()
{
    bool ok = false;
    QRgb oldRgba = m_color.rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
    if (ok && newRgba != oldRgba)
    {
        this->setValue(QColor::fromRgba(newRgba));
        emit this->valueChanged(m_color);
    }
}

bool QExtColorEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button)
    {
        switch (ev->type())
        {
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        {
            // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key())
            {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void QExtColorEditWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void QExtColorEditWidget::resizeEvent(QResizeEvent *event)
{
    m_button->setFixedWidth(qMax(30, event->size().height()));
    QWidget::resizeEvent(event);
}



/***********************************************************************************************************************
 * QExtPEColorEditorFactory
***********************************************************************************************************************/
void QExtPEColorEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QColor &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
    {
        return;
    }
    QListIterator<QExtColorEditWidget *> itEditor(it.value());

    while (itEditor.hasNext())
    {
        itEditor.next()->setValue(value);
    }
}

void QExtPEColorEditorFactoryPrivate::slotSetValue(const QColor &value)
{
    QObject *object = q_ptr->sender();
    EditorToPropertyMap::ConstIterator itEditor;
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEColorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEColorEditorFactory::QExtPEColorEditorFactory(QObject *parent) :
    QExtPEAbstractWidgetFactory<QExtPEColorPropertyManager>(parent),
    d_ptr(new QExtPEColorEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

QExtPEColorEditorFactory::~QExtPEColorEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEColorEditorFactory::connectPropertyManager(QExtPEColorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty*,QColor)), this, SLOT(slotPropertyChanged(QExtPEProperty*,QColor)));
}

QWidget *QExtPEColorEditorFactory::createEditor(QExtPEColorPropertyManager *manager,
                                              QExtPEProperty *property, QWidget *parent)
{
    QExtColorEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QColor)), this, SLOT(slotSetValue(QColor)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEColorEditorFactory::disconnectPropertyManager(QExtPEColorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty*,QColor)), this, SLOT(slotPropertyChanged(QExtPEProperty*,QColor)));
}


/***********************************************************************************************************************
 * QExtFontEditWidget
***********************************************************************************************************************/
QExtFontEditWidget::QExtFontEditWidget(QWidget *parent)
    : QWidget(parent)
    , m_pixmapLabel(new QLabel)
    , m_label(new QLabel)
    , m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setToolButtonStyle(Qt::ToolButtonTextOnly);
    m_button->setText(tr("..."));
    m_button->setFixedWidth(qMax(30, this->height()));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    this->setFocusProxy(m_button);
    this->setFocusPolicy(m_button->focusPolicy());
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::fontValuePixmap(m_font));
    m_label->setText(QExtPropertyBrowserUtils::fontValueText(m_font));
}

void QExtFontEditWidget::setValue(const QFont &f)
{
    if (m_font != f)
    {
        m_font = f;
        m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::fontValuePixmap(f));
        m_label->setText(QExtPropertyBrowserUtils::fontValueText(f));
    }
}

void QExtFontEditWidget::buttonClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this, tr("Select Font"));
    if (ok && newFont != m_font)
    {
        QFont f = m_font;
        // prevent mask for unchanged attributes, don't change other attributes (like kerning, etc...)
        if (m_font.family() != newFont.family())
        {
            f.setFamily(newFont.family());
        }
        if (m_font.pointSize() != newFont.pointSize())
        {
            f.setPointSize(newFont.pointSize());
        }
        if (m_font.bold() != newFont.bold())
        {
            f.setBold(newFont.bold());
        }
        if (m_font.italic() != newFont.italic())
        {
            f.setItalic(newFont.italic());
        }
        if (m_font.underline() != newFont.underline())
        {
            f.setUnderline(newFont.underline());
        }
        if (m_font.strikeOut() != newFont.strikeOut())
        {
            f.setStrikeOut(newFont.strikeOut());
        }
        this->setValue(f);
        emit this->valueChanged(m_font);
    }
}

bool QExtFontEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button)
    {
        switch (ev->type())
        {
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        {
            // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key())
            {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
        break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void QExtFontEditWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void QExtFontEditWidget::resizeEvent(QResizeEvent *event)
{
    m_button->setFixedWidth(qMax(30, event->size().height()));
    QWidget::resizeEvent(event);
}



/***********************************************************************************************************************
 * QExtPEFontEditorFactory
***********************************************************************************************************************/
void QExtPEFontEditorFactoryPrivate::slotPropertyChanged(QExtPEProperty *property, const QFont &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
    {
        return;
    }
    QListIterator<QExtFontEditWidget *> itEditor(it.value());

    while (itEditor.hasNext())
    {
        itEditor.next()->setValue(value);
    }
}

void QExtPEFontEditorFactoryPrivate::slotSetValue(const QFont &value)
{
    QObject *object = q_ptr->sender();
    EditorToPropertyMap::ConstIterator itEditor;
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
    {
        if (itEditor.key() == object)
        {
            QExtPEProperty *property = itEditor.value();
            QExtPEFontPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
            {
                return;
            }
            manager->setValue(property, value);
            return;
        }
    }
}


QExtPEFontEditorFactory::QExtPEFontEditorFactory(QObject *parent) :
    QExtPEAbstractWidgetFactory<QExtPEFontPropertyManager>(parent),
    d_ptr(new QExtPEFontEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

QExtPEFontEditorFactory::~QExtPEFontEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

void QExtPEFontEditorFactory::connectPropertyManager(QExtPEFontPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtPEProperty*,QFont)), this, SLOT(slotPropertyChanged(QExtPEProperty*,QFont)));
}

QWidget *QExtPEFontEditorFactory::createEditor(QExtPEFontPropertyManager *manager,
                                             QExtPEProperty *property, QWidget *parent)
{
    QExtFontEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QFont)), this, SLOT(slotSetValue(QFont)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

void QExtPEFontEditorFactory::disconnectPropertyManager(QExtPEFontPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtPEProperty*,QFont)), this, SLOT(slotPropertyChanged(QExtPEProperty*,QFont)));
}


#include <moc_qextPEWidgetFactory.cpp>
