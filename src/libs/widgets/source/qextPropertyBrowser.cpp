#include <private/qextPropertyBrowser_p.h>

#include <QSet>
#include <QMap>
#include <QIcon>
#include <QLineEdit>
#include <QDateTime>
#include <QLocale>
#include <QTimer>
#include <QIcon>
#include <QMetaEnum>
#include <QFontDatabase>
#include <QStyleOption>
#include <QStyle>
#include <QPainter>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QApplication>
#include <QPainter>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QCheckBox>
#include <QLineEdit>
#include <QMenu>
#include <QSpinBox>
#include <QScrollBar>
#include <QComboBox>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QToolButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QSpacerItem>
#include <QGridLayout>
#include <QGroupBox>
#include <QTimer>
#include <QIcon>
#include <QTreeWidget>
#include <QItemDelegate>
#include <QHeaderView>
#include <QFocusEvent>
#include <QPalette>
#include <QVariant>
#include <QGlobalStatic>

#include <limits.h>
#include <float.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

/***********************************************************************************************************************
** qextPropertyBrowser_p
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

QPixmap QExtPropertyBrowserUtils::brushValuePixmap(const QBrush &b)
{
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QPainter painter(&img);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(0, 0, img.width(), img.height(), b);
    QColor color = b.color();
    if (color.alpha() != 255)
    {
        // indicate alpha by an inset
        QBrush  opaqueBrush = b;
        color.setAlpha(255);
        opaqueBrush.setColor(color);
        painter.fillRect(img.width() / 4, img.height() / 4,
                         img.width() / 2, img.height() / 2, opaqueBrush);
    }
    painter.end();
    return QPixmap::fromImage(img);
}

QIcon QExtPropertyBrowserUtils::brushValueIcon(const QBrush &b)
{
    return QIcon(brushValuePixmap(b));
}

QString QExtPropertyBrowserUtils::colorValueText(const QColor &c)
{
    return QCoreApplication::translate("QExtPropertyBrowserUtils", "[%1, %2, %3] (%4)")
            .arg(c.red()).arg(c.green()).arg(c.blue()).arg(c.alpha());
}

QPixmap QExtPropertyBrowserUtils::fontValuePixmap(const QFont &font)
{
    QFont f = font;
    QImage img(16, 16, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);
    QPainter p(&img);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::Antialiasing, true);
    f.setPointSize(13);
    p.setFont(f);
    QTextOption t;
    t.setAlignment(Qt::AlignCenter);
    p.drawText(QRect(0, 0, 16, 16), QString(QLatin1Char('A')), t);
    return QPixmap::fromImage(img);
}

QIcon QExtPropertyBrowserUtils::fontValueIcon(const QFont &f)
{
    return QIcon(fontValuePixmap(f));
}

QString QExtPropertyBrowserUtils::fontValueText(const QFont &f)
{
    return QCoreApplication::translate("QExtPropertyBrowserUtils", "[%1, %2]")
            .arg(f.family()).arg(f.pointSize());
}


QExtBoolEdit::QExtBoolEdit(QWidget *parent) :
    QWidget(parent),
    m_checkBox(new QCheckBox(this)),
    m_textVisible(true)
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
    setLayout(lt);
    connect(m_checkBox, SIGNAL(toggled(bool)), this, SIGNAL(toggled(bool)));
    setFocusProxy(m_checkBox);
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
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


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
        QAction *actionBefore = 0;
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
** qextPropertyBrowser
***********************************************************************************************************************/
class QExtPropertyPrivate
{
public:
    QExtPropertyPrivate(QExtAbstractPropertyManager *manager) : m_enabled(true), m_modified(false), m_manager(manager) {}

    QExtProperty *q_ptr;

    QSet<QExtProperty *> m_parentItems;
    QList<QExtProperty *> m_subItems;

    QString m_toolTip;
    QString m_statusTip;
    QString m_whatsThis;
    QString m_name;
    bool m_enabled;
    bool m_modified;

    QExtAbstractPropertyManager * const m_manager;
};

class QExtAbstractPropertyManagerPrivate
{
public:
    void propertyDestroyed(QExtProperty *property);
    void propertyChanged(QExtProperty *property) const;
    void propertyRemoved(QExtProperty *property, QExtProperty *parentProperty) const;
    void propertyInserted(QExtProperty *property, QExtProperty *parentProperty, QExtProperty *afterProperty) const;

    QSet<QExtProperty *> m_properties;

private:
    QExtAbstractPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtAbstractPropertyManager)
};



QExtProperty::QExtProperty(QExtAbstractPropertyManager *manager)
{
    d_ptr = new QExtPropertyPrivate(manager);
    d_ptr->q_ptr = this;
}

QExtProperty::~QExtProperty()
{
    QSetIterator<QExtProperty *> itParent(d_ptr->m_parentItems);
    while (itParent.hasNext())
    {
        QExtProperty *property = itParent.next();
        property->d_ptr->m_manager->d_ptr->propertyRemoved(this, property);
    }

    d_ptr->m_manager->d_ptr->propertyDestroyed(this);

    QListIterator<QExtProperty *> itChild(d_ptr->m_subItems);
    while (itChild.hasNext())
    {
        QExtProperty *property = itChild.next();
        property->d_ptr->m_parentItems.remove(this);
    }

    itParent.toFront();
    while (itParent.hasNext())
    {
        QExtProperty *property = itParent.next();
        property->d_ptr->m_subItems.removeAll(this);
    }
    delete d_ptr;
}

QList<QExtProperty *> QExtProperty::subProperties() const
{
    return d_ptr->m_subItems;
}

QExtAbstractPropertyManager *QExtProperty::propertyManager() const
{
    return d_ptr->m_manager;
}

QString QExtProperty::toolTip() const
{
    return d_ptr->m_toolTip;
}

QString QExtProperty::statusTip() const
{
    return d_ptr->m_statusTip;
}

QString QExtProperty::whatsThis() const
{
    return d_ptr->m_whatsThis;
}

QString QExtProperty::propertyName() const
{
    return d_ptr->m_name;
}

bool QExtProperty::isEnabled() const
{
    return d_ptr->m_enabled;
}

bool QExtProperty::isModified() const
{
    return d_ptr->m_modified;
}

bool QExtProperty::hasValue() const
{
    return d_ptr->m_manager->hasValue(this);
}

QIcon QExtProperty::valueIcon() const
{
    return d_ptr->m_manager->valueIcon(this);
}

QString QExtProperty::valueText() const
{
    return d_ptr->m_manager->valueText(this);
}

QString QExtProperty::displayText() const
{
    return d_ptr->m_manager->displayText(this);
}

void QExtProperty::setToolTip(const QString &text)
{
    if (d_ptr->m_toolTip == text)
    {
        return;
    }

    d_ptr->m_toolTip = text;
    this->propertyChanged();
}

void QExtProperty::setStatusTip(const QString &text)
{
    if (d_ptr->m_statusTip == text)
    {
        return;
    }

    d_ptr->m_statusTip = text;
    this->propertyChanged();
}

void QExtProperty::setWhatsThis(const QString &text)
{
    if (d_ptr->m_whatsThis == text)
    {
        return;
    }

    d_ptr->m_whatsThis = text;
    this->propertyChanged();
}

void QExtProperty::setPropertyName(const QString &text)
{
    if (d_ptr->m_name == text)
    {
        return;
    }

    d_ptr->m_name = text;
    this->propertyChanged();
}

void QExtProperty::setEnabled(bool enable)
{
    if (d_ptr->m_enabled == enable)
    {
        return;
    }

    d_ptr->m_enabled = enable;
    this->propertyChanged();
}

void QExtProperty::setModified(bool modified)
{
    if (d_ptr->m_modified == modified)
    {
        return;
    }

    d_ptr->m_modified = modified;
    this->propertyChanged();
}

void QExtProperty::addSubProperty(QExtProperty *property)
{
    QExtProperty *after = 0;
    if (d_ptr->m_subItems.count() > 0)
    {
        after = d_ptr->m_subItems.last();
    }
    this->insertSubProperty(property, after);
}

void QExtProperty::insertSubProperty(QExtProperty *property, QExtProperty *afterProperty)
{
    if (!property)
    {
        return;
    }

    if (property == this)
    {
        return;
    }

    // traverse all children of item. if this item is a child of item then cannot add.
    QList<QExtProperty *> pendingList = property->subProperties();
    QHash<QExtProperty *, bool> visited;
    while (!pendingList.isEmpty())
    {
        QExtProperty *i = pendingList.first();
        if (i == this)
        {
            return;
        }
        pendingList.removeFirst();
        if (visited.contains(i))
        {
            continue;
        }
        visited[i] = true;
        pendingList += i->subProperties();
    }

    pendingList = subProperties();
    int pos = 0;
    int newPos = 0;
    QExtProperty *properAfterProperty = 0;
    while (pos < pendingList.count())
    {
        QExtProperty *i = pendingList.at(pos);
        if (i == property)
        {
            return; // if item is already inserted in this item then cannot add.
        }
        if (i == afterProperty)
        {
            newPos = pos + 1;
            properAfterProperty = afterProperty;
        }
        pos++;
    }

    d_ptr->m_subItems.insert(newPos, property);
    property->d_ptr->m_parentItems.insert(this);

    d_ptr->m_manager->d_ptr->propertyInserted(property, this, properAfterProperty);
}

void QExtProperty::removeSubProperty(QExtProperty *property)
{
    if (!property)
    {
        return;
    }

    d_ptr->m_manager->d_ptr->propertyRemoved(property, this);

    QList<QExtProperty *> pendingList = subProperties();
    int pos = 0;
    while (pos < pendingList.count())
    {
        if (pendingList.at(pos) == property)
        {
            d_ptr->m_subItems.removeAt(pos);
            property->d_ptr->m_parentItems.remove(this);

            return;
        }
        pos++;
    }
}

void QExtProperty::propertyChanged()
{
    d_ptr->m_manager->d_ptr->propertyChanged(this);
}


void QExtAbstractPropertyManagerPrivate::propertyDestroyed(QExtProperty *property)
{
    if (m_properties.contains(property))
    {
        emit q_ptr->propertyDestroyed(property);
        q_ptr->uninitializeProperty(property);
        m_properties.remove(property);
    }
}

void QExtAbstractPropertyManagerPrivate::propertyChanged(QExtProperty *property) const
{
    emit q_ptr->propertyChanged(property);
}

void QExtAbstractPropertyManagerPrivate::propertyRemoved(QExtProperty *property,
                                                         QExtProperty *parentProperty) const
{
    emit q_ptr->propertyRemoved(property, parentProperty);
}

void QExtAbstractPropertyManagerPrivate::propertyInserted(QExtProperty *property,
                                                          QExtProperty *parentProperty, QExtProperty *afterProperty) const
{
    emit q_ptr->propertyInserted(property, parentProperty, afterProperty);
}


QExtAbstractPropertyManager::QExtAbstractPropertyManager(QObject *parent)
    : QObject(parent)
{
    d_ptr = new QExtAbstractPropertyManagerPrivate;
    d_ptr->q_ptr = this;

}

QExtAbstractPropertyManager::~QExtAbstractPropertyManager()
{
    this->clear();
    delete d_ptr;
}

void QExtAbstractPropertyManager::clear() const
{
    while (!properties().isEmpty())
    {
        QSetIterator<QExtProperty *> itProperty(properties());
        QExtProperty *prop = itProperty.next();
        delete prop;
    }
}

QSet<QExtProperty *> QExtAbstractPropertyManager::properties() const
{
    return d_ptr->m_properties;
}

bool QExtAbstractPropertyManager::hasValue(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return true;
}

QIcon QExtAbstractPropertyManager::valueIcon(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return QIcon();
}

QString QExtAbstractPropertyManager::valueText(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return QString();
}

QString QExtAbstractPropertyManager::displayText(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return QString();
}

EchoMode QExtAbstractPropertyManager::echoMode(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return QLineEdit::Normal;
}

QExtProperty *QExtAbstractPropertyManager::addProperty(const QString &name)
{
    QExtProperty *property = createProperty();
    if (property)
    {
        property->setPropertyName(name);
        d_ptr->m_properties.insert(property);
        this->initializeProperty(property);
    }
    return property;
}

QExtProperty *QExtAbstractPropertyManager::createProperty()
{
    return new QExtProperty(this);
}

void QExtAbstractPropertyManager::uninitializeProperty(QExtProperty *property)
{
    Q_UNUSED(property)
}


class QExtBrowserItemPrivate
{
public:
    QExtBrowserItemPrivate(QExtAbstractPropertyBrowser *browser, QExtProperty *property, QExtBrowserItem *parent)
        : q_ptr(0)
        , m_browser(browser)
        , m_property(property)
        , m_parent(parent)
    {
    }

    void addChild(QExtBrowserItem *index, QExtBrowserItem *after);
    void removeChild(QExtBrowserItem *index);

    QExtBrowserItem *q_ptr;
    QExtAbstractPropertyBrowser * const m_browser;
    QExtProperty *m_property;
    QExtBrowserItem *m_parent;
    QList<QExtBrowserItem *> m_children;
};

void QExtBrowserItemPrivate::addChild(QExtBrowserItem *index, QExtBrowserItem *after)
{
    if (m_children.contains(index))
    {
        return;
    }
    int idx = m_children.indexOf(after) + 1; // we insert after returned idx, if it was -1 then we set idx to 0;
    m_children.insert(idx, index);
}

void QExtBrowserItemPrivate::removeChild(QExtBrowserItem *index)
{
    m_children.removeAll(index);
}

QExtProperty *QExtBrowserItem::property() const
{
    return d_ptr->m_property;
}

QExtBrowserItem *QExtBrowserItem::parent() const
{
    return d_ptr->m_parent;
}

QList<QExtBrowserItem *> QExtBrowserItem::children() const
{
    return d_ptr->m_children;
}

QExtAbstractPropertyBrowser *QExtBrowserItem::browser() const
{
    return d_ptr->m_browser;
}

QExtBrowserItem::QExtBrowserItem(QExtAbstractPropertyBrowser *browser, QExtProperty *property, QExtBrowserItem *parent)
{
    d_ptr = new QExtBrowserItemPrivate(browser, property, parent);
    d_ptr->q_ptr = this;
}

QExtBrowserItem::~QExtBrowserItem()
{
    delete d_ptr;
}


typedef QMap<QExtAbstractPropertyBrowser *, QMap<QExtAbstractPropertyManager *, QExtAbstractEditorFactoryBase *> > Map1;
typedef QMap<QExtAbstractPropertyManager *, QMap<QExtAbstractEditorFactoryBase *, QList<QExtAbstractPropertyBrowser *> > > Map2;
Q_GLOBAL_STATIC(Map1, sg_viewToManagerToFactory)
Q_GLOBAL_STATIC(Map2, sg_managerToFactoryToViews)

class QExtAbstractPropertyBrowserPrivate
{
    QExtAbstractPropertyBrowser *q_ptr;
    Q_DECLARE_PUBLIC(QExtAbstractPropertyBrowser)
public:
    QExtAbstractPropertyBrowserPrivate();

    void insertSubTree(QExtProperty *property, QExtProperty *parentProperty);
    void removeSubTree(QExtProperty *property, QExtProperty *parentProperty);
    void createBrowserIndexes(QExtProperty *property, QExtProperty *parentProperty, QExtProperty *afterProperty);
    void removeBrowserIndexes(QExtProperty *property, QExtProperty *parentProperty);
    QExtBrowserItem *createBrowserIndex(QExtProperty *property, QExtBrowserItem *parentIndex, QExtBrowserItem *afterIndex);
    void removeBrowserIndex(QExtBrowserItem *index);
    void clearIndex(QExtBrowserItem *index);

    void slotPropertyInserted(QExtProperty *property, QExtProperty *parentProperty, QExtProperty *afterProperty);
    void slotPropertyRemoved(QExtProperty *property, QExtProperty *parentProperty);
    void slotPropertyDestroyed(QExtProperty *property);
    void slotPropertyDataChanged(QExtProperty *property);

    QList<QExtProperty *> m_subItems;
    QMap<QExtAbstractPropertyManager *, QList<QExtProperty *> > m_managerToProperties;
    QMap<QExtProperty *, QList<QExtProperty *> > m_propertyToParents;

    QMap<QExtProperty *, QExtBrowserItem *> m_topLevelPropertyToIndex;
    QList<QExtBrowserItem *> m_topLevelIndexes;
    QMap<QExtProperty *, QList<QExtBrowserItem *> > m_propertyToIndexes;

    QExtBrowserItem *m_currentItem;
};

QExtAbstractPropertyBrowserPrivate::QExtAbstractPropertyBrowserPrivate()
    : m_currentItem(0)
{
}

void QExtAbstractPropertyBrowserPrivate::insertSubTree(QExtProperty *property, QExtProperty *parentProperty)
{
    if (m_propertyToParents.contains(property))
    {
        // property was already inserted, so its manager is connected
        // and all its children are inserted and theirs managers are connected
        // we just register new parent (parent has to be new).
        m_propertyToParents[property].append(parentProperty);
        // don't need to update m_managerToProperties map since
        // m_managerToProperties[manager] already contains property.
        return;
    }
    QExtAbstractPropertyManager *manager = property->propertyManager();
    if (m_managerToProperties[manager].isEmpty())
    {
        // connect manager's signals
        q_ptr->connect(manager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
                       q_ptr, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
        q_ptr->connect(manager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
                       q_ptr, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
        q_ptr->connect(manager, SIGNAL(propertyDestroyed(QExtProperty *)),
                       q_ptr, SLOT(slotPropertyDestroyed(QExtProperty *)));
        q_ptr->connect(manager, SIGNAL(propertyChanged(QExtProperty *)),
                       q_ptr, SLOT(slotPropertyDataChanged(QExtProperty *)));
    }
    m_managerToProperties[manager].append(property);
    m_propertyToParents[property].append(parentProperty);

    QList<QExtProperty *> subList = property->subProperties();
    QListIterator<QExtProperty *> iter(subList);
    while (iter.hasNext())
    {
        QExtProperty *subProperty = iter.next();
        insertSubTree(subProperty, property);
    }
}

void QExtAbstractPropertyBrowserPrivate::removeSubTree(QExtProperty *property, QExtProperty *parentProperty)
{
    if (!m_propertyToParents.contains(property))
    {
        // ASSERT
        return;
    }

    m_propertyToParents[property].removeAll(parentProperty);
    if (!m_propertyToParents[property].isEmpty())
    {
        return;
    }

    m_propertyToParents.remove(property);
    QExtAbstractPropertyManager *manager = property->propertyManager();
    m_managerToProperties[manager].removeAll(property);
    if (m_managerToProperties[manager].isEmpty())
    {
        // disconnect manager's signals
        q_ptr->disconnect(manager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
                          q_ptr, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
        q_ptr->disconnect(manager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
                          q_ptr, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
        q_ptr->disconnect(manager, SIGNAL(propertyDestroyed(QExtProperty *)),
                          q_ptr, SLOT(slotPropertyDestroyed(QExtProperty *)));
        q_ptr->disconnect(manager, SIGNAL(propertyChanged(QExtProperty *)),
                          q_ptr, SLOT(slotPropertyDataChanged(QExtProperty *)));

        m_managerToProperties.remove(manager);
    }

    QList<QExtProperty *> subList = property->subProperties();
    QListIterator<QExtProperty *> iter(subList);
    while (iter.hasNext())
    {
        QExtProperty *subProperty = iter.next();
        this->removeSubTree(subProperty, property);
    }
}

void QExtAbstractPropertyBrowserPrivate::createBrowserIndexes(QExtProperty *property, QExtProperty *parentProperty,
                                                              QExtProperty *afterProperty)
{
    QHash<QExtBrowserItem *, QExtBrowserItem *> parentToAfter;
    if (afterProperty)
    {
        QMap<QExtProperty *, QList<QExtBrowserItem *> >::ConstIterator it = m_propertyToIndexes.find(afterProperty);
        if (it == m_propertyToIndexes.constEnd())
        {
            return;
        }

        QList<QExtBrowserItem *> indexes = it.value();
        QListIterator<QExtBrowserItem *> itIndex(indexes);
        while (itIndex.hasNext())
        {
            QExtBrowserItem *idx = itIndex.next();
            QExtBrowserItem *parentIdx = idx->parent();
            if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
            {
                parentToAfter[idx->parent()] = idx;
            }
        }
    }
    else if (parentProperty)
    {
        QMap<QExtProperty *, QList<QExtBrowserItem *> >::ConstIterator iter = m_propertyToIndexes.find(parentProperty);
        if (iter == m_propertyToIndexes.constEnd())
        {
            return;
        }

        QList<QExtBrowserItem *> indexes = iter.value();
        QListIterator<QExtBrowserItem *> iterIndex(indexes);
        while (iterIndex.hasNext())
        {
            QExtBrowserItem *idx = iterIndex.next();
            parentToAfter[idx] = 0;
        }
    }
    else
    {
        parentToAfter[0] = 0;
    }

    const QHash<QExtBrowserItem *, QExtBrowserItem *>::ConstIterator pcend = parentToAfter.constEnd();
    for (QHash<QExtBrowserItem *, QExtBrowserItem *>::ConstIterator it = parentToAfter.constBegin(); it != pcend; ++it)
    {
        this->createBrowserIndex(property, it.key(), it.value());
    }
}

QExtBrowserItem *QExtAbstractPropertyBrowserPrivate::createBrowserIndex(QExtProperty *property,
                                                                        QExtBrowserItem *parentIndex,
                                                                        QExtBrowserItem *afterIndex)
{
    QExtBrowserItem *newIndex = new QExtBrowserItem(q_ptr, property, parentIndex);
    if (parentIndex)
    {
        parentIndex->d_ptr->addChild(newIndex, afterIndex);
    }
    else
    {
        m_topLevelPropertyToIndex[property] = newIndex;
        m_topLevelIndexes.insert(m_topLevelIndexes.indexOf(afterIndex) + 1, newIndex);
    }
    m_propertyToIndexes[property].append(newIndex);

    q_ptr->itemInserted(newIndex, afterIndex);

    QList<QExtProperty *> subItems = property->subProperties();
    QListIterator<QExtProperty *> itChild(subItems);
    QExtBrowserItem *afterChild = 0;
    while (itChild.hasNext())
    {
        QExtProperty *child = itChild.next();
        afterChild = createBrowserIndex(child, newIndex, afterChild);
    }
    return newIndex;
}

void QExtAbstractPropertyBrowserPrivate::removeBrowserIndexes(QExtProperty *property, QExtProperty *parentProperty)
{
    QList<QExtBrowserItem *> toRemove;
    QMap<QExtProperty *, QList<QExtBrowserItem *> >::ConstIterator it = m_propertyToIndexes.find(property);
    if (it == m_propertyToIndexes.constEnd())
    {
        return;
    }

    QList<QExtBrowserItem *> indexes = it.value();
    QListIterator<QExtBrowserItem *> itIndex(indexes);
    while (itIndex.hasNext())
    {
        QExtBrowserItem *idx = itIndex.next();
        QExtBrowserItem *parentIdx = idx->parent();
        if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
        {
            toRemove.append(idx);
        }
    }

    QListIterator<QExtBrowserItem *> itRemove(toRemove);
    while (itRemove.hasNext())
    {
        QExtBrowserItem *index = itRemove.next();
        this->removeBrowserIndex(index);
    }
}

void QExtAbstractPropertyBrowserPrivate::removeBrowserIndex(QExtBrowserItem *index)
{
    QList<QExtBrowserItem *> children = index->children();
    for (int i = children.count(); i > 0; i--)
    {
        this->removeBrowserIndex(children.at(i - 1));
    }

    q_ptr->itemRemoved(index);

    if (index->parent())
    {
        index->parent()->d_ptr->removeChild(index);
    }
    else
    {
        m_topLevelPropertyToIndex.remove(index->property());
        m_topLevelIndexes.removeAll(index);
    }

    QExtProperty *property = index->property();

    m_propertyToIndexes[property].removeAll(index);
    if (m_propertyToIndexes[property].isEmpty())
    {
        m_propertyToIndexes.remove(property);
    }

    delete index;
}

void QExtAbstractPropertyBrowserPrivate::clearIndex(QExtBrowserItem *index)
{
    QList<QExtBrowserItem *> children = index->children();
    QListIterator<QExtBrowserItem *> itChild(children);
    while (itChild.hasNext())
    {
        clearIndex(itChild.next());
    }
    delete index;
}

void QExtAbstractPropertyBrowserPrivate::slotPropertyInserted(QExtProperty *property,
                                                              QExtProperty *parentProperty, QExtProperty *afterProperty)
{
    if (!m_propertyToParents.contains(parentProperty))
    {
        return;
    }
    this->createBrowserIndexes(property, parentProperty, afterProperty);
    this->insertSubTree(property, parentProperty);
    //q_ptr->propertyInserted(property, parentProperty, afterProperty);
}

void QExtAbstractPropertyBrowserPrivate::slotPropertyRemoved(QExtProperty *property,
                                                             QExtProperty *parentProperty)
{
    if (!m_propertyToParents.contains(parentProperty))
    {
        return;
    }
    this->removeSubTree(property, parentProperty); // this line should be probably moved down after propertyRemoved call
    //q_ptr->propertyRemoved(property, parentProperty);
    this->removeBrowserIndexes(property, parentProperty);
}

void QExtAbstractPropertyBrowserPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (!m_subItems.contains(property))
    {
        return;
    }
    q_ptr->removeProperty(property);
}

void QExtAbstractPropertyBrowserPrivate::slotPropertyDataChanged(QExtProperty *property)
{
    if (!m_propertyToParents.contains(property))
    {
        return;
    }

    QMap<QExtProperty *, QList<QExtBrowserItem *> >::ConstIterator it = m_propertyToIndexes.find(property);
    if (it == m_propertyToIndexes.constEnd())
    {
        return;
    }

    QList<QExtBrowserItem *> indexes = it.value();
    QListIterator<QExtBrowserItem *> itIndex(indexes);
    while (itIndex.hasNext())
    {
        QExtBrowserItem *idx = itIndex.next();
        q_ptr->itemChanged(idx);
    }
    //q_ptr->propertyChanged(property);
}


QExtAbstractPropertyBrowser::QExtAbstractPropertyBrowser(QWidget *parent)
    : QWidget(parent)
{
    d_ptr = new QExtAbstractPropertyBrowserPrivate;
    d_ptr->q_ptr = this;

}

QExtAbstractPropertyBrowser::~QExtAbstractPropertyBrowser()
{
    QList<QExtBrowserItem *> indexes = this->topLevelItems();
    QListIterator<QExtBrowserItem *> itItem(indexes);
    while (itItem.hasNext())
    {
        d_ptr->clearIndex(itItem.next());
    }
    delete d_ptr;
}

QList<QExtProperty *> QExtAbstractPropertyBrowser::properties() const
{
    return d_ptr->m_subItems;
}

QList<QExtBrowserItem *> QExtAbstractPropertyBrowser::items(QExtProperty *property) const
{
    return d_ptr->m_propertyToIndexes.value(property);
}

QExtBrowserItem *QExtAbstractPropertyBrowser::topLevelItem(QExtProperty *property) const
{
    return d_ptr->m_topLevelPropertyToIndex.value(property);
}

QList<QExtBrowserItem *> QExtAbstractPropertyBrowser::topLevelItems() const
{
    return d_ptr->m_topLevelIndexes;
}

void QExtAbstractPropertyBrowser::clear()
{
    QList<QExtProperty *> subList = this->properties();
    QListIterator<QExtProperty *> itSub(subList);
    itSub.toBack();
    while (itSub.hasPrevious())
    {
        QExtProperty *property = itSub.previous();
        this->removeProperty(property);
    }
}

QExtBrowserItem *QExtAbstractPropertyBrowser::addProperty(QExtProperty *property)
{
    QExtProperty *afterProperty = 0;
    if (d_ptr->m_subItems.count() > 0)
    {
        afterProperty = d_ptr->m_subItems.last();
    }
    return this->insertProperty(property, afterProperty);
}

QExtBrowserItem *QExtAbstractPropertyBrowser::insertProperty(QExtProperty *property, QExtProperty *afterProperty)
{
    if (!property)
    {
        return 0;
    }

    // if item is already inserted in this item then cannot add.
    QList<QExtProperty *> pendingList = this->properties();
    int pos = 0;
    int newPos = 0;
    while (pos < pendingList.count())
    {
        QExtProperty *prop = pendingList.at(pos);
        if (prop == property)
        {
            return 0;
        }
        if (prop == afterProperty)
        {
            newPos = pos + 1;
        }
        pos++;
    }
    d_ptr->createBrowserIndexes(property, 0, afterProperty);

    // traverse inserted subtree and connect to manager's signals
    d_ptr->insertSubTree(property, 0);

    d_ptr->m_subItems.insert(newPos, property);
    //propertyInserted(property, 0, properAfterProperty);
    return this->topLevelItem(property);
}

void QExtAbstractPropertyBrowser::removeProperty(QExtProperty *property)
{
    if (!property)
    {
        return;
    }

    QList<QExtProperty *> pendingList = this->properties();
    int pos = 0;
    while (pos < pendingList.count())
    {
        if (pendingList.at(pos) == property)
        {
            d_ptr->m_subItems.removeAt(pos); //perhaps this two lines
            d_ptr->removeSubTree(property, 0); //should be moved down after propertyRemoved call.
            //propertyRemoved(property, 0);

            d_ptr->removeBrowserIndexes(property, 0);

            // when item is deleted, item will call removeItem for top level items,
            // and itemRemoved for nested items.
            return;
        }
        pos++;
    }
}

QWidget *QExtAbstractPropertyBrowser::createEditor(QExtProperty *property, QWidget *parent)
{
    QExtAbstractEditorFactoryBase *factory = 0;
    QExtAbstractPropertyManager *manager = property->propertyManager();

    if (sg_viewToManagerToFactory()->contains(this) && (*sg_viewToManagerToFactory())[this].contains(manager))
    {
        factory = (*sg_viewToManagerToFactory())[this][manager];
    }

    if (!factory)
    {
        return 0;
    }
    return factory->createEditor(property, parent);
}

bool QExtAbstractPropertyBrowser::addFactory(QExtAbstractPropertyManager *abstractManager,
                                             QExtAbstractEditorFactoryBase *abstractFactory)
{
    bool connectNeeded = false;
    if (!sg_managerToFactoryToViews()->contains(abstractManager) ||
            !(*sg_managerToFactoryToViews())[abstractManager].contains(abstractFactory))
    {
        connectNeeded = true;
    }
    else if ((*sg_managerToFactoryToViews())[abstractManager][abstractFactory].contains(this))
    {
        return connectNeeded;
    }

    if (sg_viewToManagerToFactory()->contains(this) && (*sg_viewToManagerToFactory())[this].contains(abstractManager))
    {
        unsetFactoryForManager(abstractManager);
    }

    (*sg_managerToFactoryToViews())[abstractManager][abstractFactory].append(this);
    (*sg_viewToManagerToFactory())[this][abstractManager] = abstractFactory;

    return connectNeeded;
}

void QExtAbstractPropertyBrowser::unsetFactoryForManager(QExtAbstractPropertyManager *manager)
{
    if (!sg_viewToManagerToFactory()->contains(this) || !(*sg_viewToManagerToFactory())[this].contains(manager))
    {
        return;
    }

    QExtAbstractEditorFactoryBase *abstractFactory = (*sg_viewToManagerToFactory())[this][manager];
    (*sg_viewToManagerToFactory())[this].remove(manager);
    if ((*sg_viewToManagerToFactory())[this].isEmpty())
    {
        (*sg_viewToManagerToFactory()).remove(this);
    }

    (*sg_managerToFactoryToViews())[manager][abstractFactory].removeAll(this);
    if ((*sg_managerToFactoryToViews())[manager][abstractFactory].isEmpty())
    {
        (*sg_managerToFactoryToViews())[manager].remove(abstractFactory);
        abstractFactory->breakConnection(manager);
        if ((*sg_managerToFactoryToViews())[manager].isEmpty())
        {
            (*sg_managerToFactoryToViews()).remove(manager);
        }
    }
}

QExtBrowserItem *QExtAbstractPropertyBrowser::currentItem() const
{
    return d_ptr->m_currentItem;
}

void QExtAbstractPropertyBrowser::setCurrentItem(QExtBrowserItem *item)
{
    QExtBrowserItem *oldItem = d_ptr->m_currentItem;
    d_ptr->m_currentItem = item;
    if (oldItem != item)
    {
        emit  this->currentItemChanged(item);
    }
}


/***********************************************************************************************************************
** qtpropertymanager
***********************************************************************************************************************/
template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
    {
        data->maxVal = data->minVal;
    }

    if (data->val < data->minVal)
    {
        data->val = data->minVal;
    }
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
    {
        data->minVal = data->maxVal;
    }

    if (data->val > data->maxVal)
    {
        data->val = data->maxVal;
    }
}

template <class PrivateData, class Value>
static void setSizeMinimumData(PrivateData *data, const Value &newMinVal)
{
    data->minVal = newMinVal;
    if (data->maxVal.width() < data->minVal.width())
    {
        data->maxVal.setWidth(data->minVal.width());
    }
    if (data->maxVal.height() < data->minVal.height())
    {
        data->maxVal.setHeight(data->minVal.height());
    }

    if (data->val.width() < data->minVal.width())
    {
        data->val.setWidth(data->minVal.width());
    }
    if (data->val.height() < data->minVal.height())
    {
        data->val.setHeight(data->minVal.height());
    }
}

template <class PrivateData, class Value>
static void setSizeMaximumData(PrivateData *data, const Value &newMaxVal)
{
    data->maxVal = newMaxVal;
    if (data->minVal.width() > data->maxVal.width())
    {
        data->minVal.setWidth(data->maxVal.width());
    }
    if (data->minVal.height() > data->maxVal.height())
    {
        data->minVal.setHeight(data->maxVal.height());
    }

    if (data->val.width() > data->maxVal.width())
    {
        data->val.setWidth(data->maxVal.width());
    }
    if (data->val.height() > data->maxVal.height())
    {
        data->val.setHeight(data->maxVal.height());
    }
}

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
    SizeValue croppedVal = val;
    if (minVal.width() > val.width())
    {
        croppedVal.setWidth(minVal.width());
    }
    else if (maxVal.width() < val.width())
    {
        croppedVal.setWidth(maxVal.width());
    }

    if (minVal.height() > val.height())
    {
        croppedVal.setHeight(minVal.height());
    }
    else if (maxVal.height() < val.height())
    {
        croppedVal.setHeight(maxVal.height());
    }

    return croppedVal;
}

// Match the exact signature of qBound for VS 6.
QSize qBound(QSize minVal, QSize val, QSize maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

namespace
{

namespace
{
template <class Value>
void orderBorders(Value &minVal, Value &maxVal)
{
    if (minVal > maxVal)
    {
        qSwap(minVal, maxVal);
    }
}

template <class Value>
static void orderSizeBorders(Value &minVal, Value &maxVal)
{
    Value fromSize = minVal;
    Value toSize = maxVal;
    if (fromSize.width() > toSize.width())
    {
        fromSize.setWidth(maxVal.width());
        toSize.setWidth(minVal.width());
    }
    if (fromSize.height() > toSize.height())
    {
        fromSize.setHeight(maxVal.height());
        toSize.setHeight(minVal.height());
    }
    minVal = fromSize;
    maxVal = toSize;
}

void orderBorders(QSize &minVal, QSize &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

void orderBorders(QSizeF &minVal, QSizeF &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

}
}


template <class Value, class PrivateData>
static Value getData(const QMap<const QExtProperty *, PrivateData> &propertyMap, Value PrivateData::*data,
                     const QExtProperty *property, const Value &defaultValue = Value())
{
    typedef QMap<const QExtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
    {
        return defaultValue;
    }
    return it.value().*data;
}

template <class Value, class PrivateData>
static Value getValue(const QMap<const QExtProperty *, PrivateData> &propertyMap,
                      const QExtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMinimum(const QMap<const QExtProperty *, PrivateData> &propertyMap,
                        const QExtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::minVal, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMaximum(const QMap<const QExtProperty *, PrivateData> &propertyMap,
                        const QExtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::maxVal, property, defaultValue);
}

template <class ValueChangeParameter, class Value, class PropertyManager>
static void setSimpleValue(QMap<const QExtProperty *, Value> &propertyMap, PropertyManager *manager,
                           void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                           void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                           QExtProperty *property, const Value &val)
{
    typedef QMap<const QExtProperty *, Value> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = propertyMap.find(property);
    if (it == propertyMap.end())
    {
        return;
    }

    if (it.value() == val)
    {
        return;
    }

    it.value() = val;

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setValueInRange(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                            QExtProperty *property, const Value &val,
                            void (PropertyManagerPrivate::*setSubPropertyValue)(QExtProperty *, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QExtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    PrivateData &data = it.value();

    if (data.val == val)
    {
        return;
    }

    const Value oldVal = data.val;

    data.val = qBound(data.minVal, val, data.maxVal);

    if (data.val == oldVal)
    {
        return;
    }

    if (setSubPropertyValue)
    {
        (managerPrivate->*setSubPropertyValue)(property, data.val);
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setBorderValues(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtProperty *property, const Value &minVal, const Value &maxVal,
                            void (PropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *,
                                                                                ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QExtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    Value fromVal = minVal;
    Value toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (data.minVal == fromVal && data.maxVal == toVal)
    {
        return;
    }

    const Value oldVal = data.val;

    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
    {
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);
    }

    if (data.val == oldVal)
    {
        return;
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setBorderValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                           void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                           void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                           void (PropertyManager::*rangeChangedSignal)(QExtProperty *, ValueChangeParameter, ValueChangeParameter),
                           QExtProperty *property,
                           Value (PrivateData::*getRangeVal)() const,
                           void (PrivateData::*setRangeVal)(ValueChangeParameter), const Value &borderVal,
                           void (PropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *,
                                                                               ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef QMap<const QExtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
    {
        return;
    }

    PrivateData &data = it.value();

    if ((data.*getRangeVal)() == borderVal)
    {
        return;
    }

    const Value oldVal = data.val;

    (data.*setRangeVal)(borderVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
    {
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);
    }

    if (data.val == oldVal)
    {
        return;
    }

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMinimumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtProperty *property, const Value &minVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *,
                                                        ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>
            (manager, managerPrivate,
             propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
             property, &PropertyManagerPrivate::Data::minimumValue, &PropertyManagerPrivate::Data::setMinimumValue, minVal, setSubPropertyRange);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMaximumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
                            void (PropertyManager::*propertyChangedSignal)(QExtProperty *),
                            void (PropertyManager::*valueChangedSignal)(QExtProperty *, ValueChangeParameter),
                            void (PropertyManager::*rangeChangedSignal)(QExtProperty *, ValueChangeParameter, ValueChangeParameter),
                            QExtProperty *property, const Value &maxVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *,
                                                        ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = 0;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>
            (manager, managerPrivate,
             propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
             property, &PropertyManagerPrivate::Data::maximumValue, &PropertyManagerPrivate::Data::setMaximumValue, maxVal, setSubPropertyRange);
}

class QtMetaEnumProvider
{
public:
    QtMetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }
    QStringList languageEnumNames() const { return m_languageEnumNames; }
    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const;

private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country> > m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int> > m_countryToIndex;
    QMetaEnum m_policyEnum;
};

#if QT_VERSION < 0x040300

static QList<QLocale::Country> countriesForLanguage(QLocale::Language language)
{
    QList<QLocale::Country> countries;
    QLocale::Country country = QLocale::AnyCountry;
    while (country <= QLocale::LastCountry)
    {
        QLocale locale(language, country);
        if (locale.language() == language && !countries.contains(locale.country()))
        {
            countries << locale.country();
        }
        country = (QLocale::Country)((uint)country + 1); // ++country
    }
    return countries;
}

#endif

static QList<QLocale::Country> sortCountries(const QList<QLocale::Country> &countries)
{
    QMultiMap<QString, QLocale::Country> nameToCountry;
    QListIterator<QLocale::Country> itCountry(countries);
    while (itCountry.hasNext())
    {
        QLocale::Country country = itCountry.next();
        nameToCountry.insert(QLocale::countryToString(country), country);
    }
    return nameToCountry.values();
}

void QtMetaEnumProvider::initLocale()
{
    QMultiMap<QString, QLocale::Language> nameToLanguage;
    QLocale::Language language = QLocale::C;
    while (language <= QLocale::LastLanguage)
    {
        QLocale locale(language);
        if (locale.language() == language)
        {
            nameToLanguage.insert(QLocale::languageToString(language), language);
        }
        language = (QLocale::Language)((uint)language + 1); // ++language
    }

    const QLocale system = QLocale::system();
    if (!nameToLanguage.contains(QLocale::languageToString(system.language())))
        nameToLanguage.insert(QLocale::languageToString(system.language()), system.language());

    QList<QLocale::Language> languages = nameToLanguage.values();
    QListIterator<QLocale::Language> itLang(languages);
    while (itLang.hasNext())
    {
        QLocale::Language language = itLang.next();
        QList<QLocale::Country> countries;
#if QT_VERSION < 0x040300
        countries = countriesForLanguage(language);
#else
        countries = QLocale::countriesForLanguage(language);
#endif
        if (countries.isEmpty() && language == system.language())
        {
            countries << system.country();
        }

        if (!countries.isEmpty() && !m_languageToIndex.contains(language))
        {
            countries = sortCountries(countries);
            int langIdx = m_languageEnumNames.count();
            m_indexToLanguage[langIdx] = language;
            m_languageToIndex[language] = langIdx;
            QStringList countryNames;
            QListIterator<QLocale::Country> it(countries);
            int countryIdx = 0;
            while (it.hasNext())
            {
                QLocale::Country country = it.next();
                countryNames << QLocale::countryToString(country);
                m_indexToCountry[langIdx][countryIdx] = country;
                m_countryToIndex[language][country] = countryIdx;
                ++countryIdx;
            }
            m_languageEnumNames << QLocale::languageToString(language);
            m_countryEnumNames[language] = countryNames;
        }
    }
}

QtMetaEnumProvider::QtMetaEnumProvider()
{
    QMetaProperty p;

    p = QExtMetaEnumWrapper::staticMetaObject.property(QExtMetaEnumWrapper::staticMetaObject.propertyOffset() + 0);
    m_policyEnum = p.enumerator();
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
    {
        m_policyEnumNames << QLatin1String(m_policyEnum.key(i));
    }

    this->initLocale();
}

QSizePolicy::Policy QtMetaEnumProvider::indexToSizePolicy(int index) const
{
    return static_cast<QSizePolicy::Policy>(m_policyEnum.value(index));
}

int QtMetaEnumProvider::sizePolicyToIndex(QSizePolicy::Policy policy) const
{
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
    {
        if (indexToSizePolicy(i) == policy)
        {
            return i;
        }
    }
    return -1;
}

void QtMetaEnumProvider::indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language,
                                       QLocale::Country *country) const
{
    QLocale::Language l = QLocale::C;
    QLocale::Country c = QLocale::AnyCountry;
    if (m_indexToLanguage.contains(languageIndex))
    {
        l = m_indexToLanguage[languageIndex];
        if (m_indexToCountry.contains(languageIndex) && m_indexToCountry[languageIndex].contains(countryIndex))
        {
            c = m_indexToCountry[languageIndex][countryIndex];
        }
    }
    if (language)
    {
        *language = l;
    }
    if (country)
    {
        *country = c;
    }
}

void QtMetaEnumProvider::localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex,
                                       int *countryIndex) const
{
    int l = -1;
    int c = -1;
    if (m_languageToIndex.contains(language))
    {
        l = m_languageToIndex[language];
        if (m_countryToIndex.contains(language) && m_countryToIndex[language].contains(country))
        {
            c = m_countryToIndex[language][country];
        }
    }

    if (languageIndex)
    {
        *languageIndex = l;
    }
    if (countryIndex)
    {
        *countryIndex = c;
    }
}

Q_GLOBAL_STATIC(QtMetaEnumProvider, metaEnumProvider)


QExtGroupPropertyManager::QExtGroupPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{

}

QExtGroupPropertyManager::~QExtGroupPropertyManager()
{

}

bool QExtGroupPropertyManager::hasValue(const QExtProperty *property) const
{
    Q_UNUSED(property)
    return false;
}

void QExtGroupPropertyManager::initializeProperty(QExtProperty *property)
{
    Q_UNUSED(property)
}

void QExtGroupPropertyManager::uninitializeProperty(QExtProperty *property)
{
    Q_UNUSED(property)
}


class QExtIntPropertyManagerPrivate
{
    QExtIntPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtIntPropertyManager)
public:

    struct Data
    {
        Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1), readOnly(false) {}
        int val;
        int minVal;
        int maxVal;
        int singleStep;
        bool readOnly;
        int minimumValue() const { return minVal; }
        int maximumValue() const { return maxVal; }
        void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};



QExtIntPropertyManager::QExtIntPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtIntPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

QExtIntPropertyManager::~QExtIntPropertyManager()
{
    this->clear();
    delete d_ptr;
}

int QExtIntPropertyManager::value(const QExtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

int QExtIntPropertyManager::minimum(const QExtProperty *property) const
{
    return getMinimum<int>(d_ptr->m_values, property, 0);
}

int QExtIntPropertyManager::maximum(const QExtProperty *property) const
{
    return getMaximum<int>(d_ptr->m_values, property, 0);
}

int QExtIntPropertyManager::singleStep(const QExtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtIntPropertyManagerPrivate::Data::singleStep, property, 0);
}

bool QExtIntPropertyManager::isReadOnly(const QExtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtIntPropertyManagerPrivate::Data::readOnly, property, false);
}

QString QExtIntPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return QString::number(it.value().val);
}

void QExtIntPropertyManager::setValue(QExtProperty *property, int val)
{
    void (QExtIntPropertyManagerPrivate::*setSubPropertyValue)(QExtProperty *, int) = 0;
    setValueInRange<int, QExtIntPropertyManagerPrivate, QExtIntPropertyManager, int>(this, d_ptr,
                                                                                     &QExtIntPropertyManager::propertyChanged,
                                                                                     &QExtIntPropertyManager::valueChanged,
                                                                                     property, val, setSubPropertyValue);
}

void QExtIntPropertyManager::setMinimum(QExtProperty *property, int minVal)
{
    setMinimumValue<int, QExtIntPropertyManagerPrivate, QExtIntPropertyManager, int, QExtIntPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                          &QExtIntPropertyManager::propertyChanged,
                                                                                                                          &QExtIntPropertyManager::valueChanged,
                                                                                                                          &QExtIntPropertyManager::rangeChanged,
                                                                                                                          property, minVal);
}

void QExtIntPropertyManager::setMaximum(QExtProperty *property, int maxVal)
{
    setMaximumValue<int, QExtIntPropertyManagerPrivate, QExtIntPropertyManager, int, QExtIntPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                          &QExtIntPropertyManager::propertyChanged,
                                                                                                                          &QExtIntPropertyManager::valueChanged,
                                                                                                                          &QExtIntPropertyManager::rangeChanged,
                                                                                                                          property, maxVal);
}

void QExtIntPropertyManager::setRange(QExtProperty *property, int minVal, int maxVal)
{
    void (QExtIntPropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *, int, int, int) = 0;
    setBorderValues<int, QExtIntPropertyManagerPrivate, QExtIntPropertyManager, int>(this, d_ptr,
                                                                                     &QExtIntPropertyManager::propertyChanged,
                                                                                     &QExtIntPropertyManager::valueChanged,
                                                                                     &QExtIntPropertyManager::rangeChanged,
                                                                                     property, minVal, maxVal, setSubPropertyRange);
}

void QExtIntPropertyManager::setSingleStep(QExtProperty *property, int step)
{
    const QExtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtIntPropertyManagerPrivate::Data data = it.value();

    if (step < 0)
    {
        step = 0;
    }

    if (data.singleStep == step)
    {
        return;
    }

    data.singleStep = step;

    it.value() = data;

    emit this->singleStepChanged(property, data.singleStep);
}

void QExtIntPropertyManager::setReadOnly(QExtProperty *property, bool readOnly)
{
    const QExtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtIntPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

void QExtIntPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtIntPropertyManagerPrivate::Data();
}

void QExtIntPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}


class QExtDoublePropertyManagerPrivate
{
    QExtDoublePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtDoublePropertyManager)
public:

    struct Data
    {
        Data() : val(0), minVal(-INT_MAX), maxVal(INT_MAX), singleStep(1), decimals(2), readOnly(false) {}
        double val;
        double minVal;
        double maxVal;
        double singleStep;
        int decimals;
        bool readOnly;
        double minimumValue() const { return minVal; }
        double maximumValue() const { return maxVal; }
        void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};



/*!
    \fn void QExtDoublePropertyManager::rangeChanged(QExtProperty *property, double minimum, double maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid values, passing a pointer to the
    \a property and the new \a minimum and \a maximum values

    \sa setRange()
*/

/*!
    \fn void QExtDoublePropertyManager::decimalsChanged(QExtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setDecimals()
*/

/*!
    \fn void QExtDoublePropertyManager::singleStepChanged(QExtProperty *property, double step)

    This signal is emitted whenever a property created by this manager
    changes its single step property, passing a pointer to the
    \a property and the new \a step value

    \sa setSingleStep()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtDoublePropertyManager::QExtDoublePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtDoublePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys  this manager, and all the properties it has created.
*/
QExtDoublePropertyManager::~QExtDoublePropertyManager()
{
    this->clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa setValue()
*/
double QExtDoublePropertyManager::value(const QExtProperty *property) const
{
    return getValue<double>(d_ptr->m_values, property, 0.0);
}

/*!
    Returns the given \a property's minimum value.

    \sa maximum(), setRange()
*/
double QExtDoublePropertyManager::minimum(const QExtProperty *property) const
{
    return getMinimum<double>(d_ptr->m_values, property, 0.0);
}

/*!
    Returns the given \a property's maximum value.

    \sa minimum(), setRange()
*/
double QExtDoublePropertyManager::maximum(const QExtProperty *property) const
{
    return getMaximum<double>(d_ptr->m_values, property, 0.0);
}

/*!
    Returns the given \a property's step value.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa setSingleStep()
*/
double QExtDoublePropertyManager::singleStep(const QExtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QExtDoublePropertyManagerPrivate::Data::singleStep, property, 0);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setDecimals()
*/
int QExtDoublePropertyManager::decimals(const QExtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtDoublePropertyManagerPrivate::Data::decimals, property, 0);
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QExtDoublePropertyManager::setReadOnly
*/
bool QExtDoublePropertyManager::isReadOnly(const QExtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtDoublePropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    \reimp
*/
QString QExtDoublePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }
    return QLocale::system().toString(it.value().val, 'f', it.value().decimals);
}

/*!
    \fn void QExtDoublePropertyManager::setValue(QExtProperty *property, double value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given
    \a property's range, the \a value is adjusted to the nearest valid value
    within the range.

    \sa value(), setRange(), valueChanged()
*/
void QExtDoublePropertyManager::setValue(QExtProperty *property, double val)
{
    void (QExtDoublePropertyManagerPrivate::*setSubPropertyValue)(QExtProperty *, double) = 0;
    setValueInRange<double, QExtDoublePropertyManagerPrivate, QExtDoublePropertyManager, double>(this, d_ptr,
                                                                                                 &QExtDoublePropertyManager::propertyChanged,
                                                                                                 &QExtDoublePropertyManager::valueChanged,
                                                                                                 property, val, setSubPropertyValue);
}

/*!
    Sets the step value for the given \a property to \a step.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa singleStep()
*/
void QExtDoublePropertyManager::setSingleStep(QExtProperty *property, double step)
{
    const QExtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtDoublePropertyManagerPrivate::Data data = it.value();

    if (step < 0)
    {
        step = 0;
    }

    if (data.singleStep == step)
    {
        return;
    }

    data.singleStep = step;

    it.value() = data;

    emit this->singleStepChanged(property, data.singleStep);
}

/*!
    Sets read-only status of the property.

    \sa QExtDoublePropertyManager::setReadOnly
*/
void QExtDoublePropertyManager::setReadOnly(QExtProperty *property, bool readOnly)
{
    const QExtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);

    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

/*!
    \fn void QExtDoublePropertyManager::setDecimals(QExtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa decimals()
*/
void QExtDoublePropertyManager::setDecimals(QExtProperty *property, int prec)
{
    const QExtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtDoublePropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    {
        prec = 13;
    }
    else if (prec < 0)
    {
        prec = 0;
    }

    if (data.decimals == prec)
    {
        return;
    }

    data.decimals = prec;

    it.value() = data;

    emit this->decimalsChanged(property, data.decimals);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QExtDoublePropertyManager::setMinimum(QExtProperty *property, double minVal)
{
    setMinimumValue<double, QExtDoublePropertyManagerPrivate, QExtDoublePropertyManager, double, QExtDoublePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtDoublePropertyManager::propertyChanged,
                                                                                                                                         &QExtDoublePropertyManager::valueChanged,
                                                                                                                                         &QExtDoublePropertyManager::rangeChanged,
                                                                                                                                         property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting the maximum value, the minimum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QExtDoublePropertyManager::setMaximum(QExtProperty *property, double maxVal)
{
    setMaximumValue<double, QExtDoublePropertyManagerPrivate, QExtDoublePropertyManager, double, QExtDoublePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtDoublePropertyManager::propertyChanged,
                                                                                                                                         &QExtDoublePropertyManager::valueChanged,
                                                                                                                                         &QExtDoublePropertyManager::rangeChanged,
                                                                                                                                         property, maxVal);
}

/*!
    \fn void QExtDoublePropertyManager::setRange(QExtProperty *property, double minimum, double maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QExtDoublePropertyManager::setRange(QExtProperty *property, double minVal, double maxVal)
{
    void (QExtDoublePropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *, double, double, double) = 0;
    setBorderValues<double, QExtDoublePropertyManagerPrivate, QExtDoublePropertyManager, double>(this, d_ptr,
                                                                                                 &QExtDoublePropertyManager::propertyChanged,
                                                                                                 &QExtDoublePropertyManager::valueChanged,
                                                                                                 &QExtDoublePropertyManager::rangeChanged,
                                                                                                 property, minVal, maxVal, setSubPropertyRange);
}

/*!
    \reimp
*/
void QExtDoublePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtDoublePropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QExtDoublePropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtStringPropertyManager

class QExtStringPropertyManagerPrivate
{
    QExtStringPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtStringPropertyManager)
public:

    struct Data
    {
        Data() : regExp(QString(QLatin1Char('*')),  Qt::CaseSensitive, QRegExp::Wildcard),
            echoMode(QLineEdit::Normal), readOnly(false)
        {
        }
        QString val;
        QRegExp regExp;
        int echoMode;
        bool readOnly;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    QMap<const QExtProperty *, Data> m_values;
};

/*!
    \class QExtStringPropertyManager

    \brief The QExtStringPropertyManager provides and manages QString properties.

    A string property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The current value can be checked against a regular expression. To
    set the regular expression use the setRegExp() slot, use the
    regExp() function to retrieve the currently set expression.

    In addition, QExtStringPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the regExpChanged() signal which is emitted whenever
    such a property changes its currently set regular expression.

    \sa QExtAbstractPropertyManager, QExtLineEditFactory
*/

/*!
    \fn void QExtStringPropertyManager::valueChanged(QExtProperty *property, const QString &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtStringPropertyManager::regExpChanged(QExtProperty *property, const QRegExp &regExp)

    This signal is emitted whenever a property created by this manager
    changes its currenlty set regular expression, passing a pointer to
    the \a property and the new \a regExp as parameters.

    \sa setRegExp()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtStringPropertyManager::QExtStringPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtStringPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtStringPropertyManager::~QExtStringPropertyManager()
{
    this->clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns an empty string.

    \sa setValue()
*/
QString QExtStringPropertyManager::value(const QExtProperty *property) const
{
    return getValue<QString>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's currently set regular expression.

    If the given \a property is not managed by this manager, this
    function returns an empty expression.

    \sa setRegExp()
*/
QRegExp QExtStringPropertyManager::regExp(const QExtProperty *property) const
{
    return getData<QRegExp>(d_ptr->m_values, &QExtStringPropertyManagerPrivate::Data::regExp, property, QRegExp());
}

EchoMode QExtStringPropertyManager::echoMode(const QExtProperty *property) const
{
    return (EchoMode)getData<int>(d_ptr->m_values, &QExtStringPropertyManagerPrivate::Data::echoMode, property, 0);
}

bool QExtStringPropertyManager::isReadOnly(const QExtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtStringPropertyManagerPrivate::Data::readOnly, property, false);
}

QString QExtStringPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    return it.value().val;
}

/*!
    \reimp
*/
QString QExtStringPropertyManager::displayText(const QExtProperty *property) const
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    QLineEdit edit;
    edit.setEchoMode((EchoMode)it.value().echoMode);
    edit.setText(it.value().val);
    return edit.displayText();
}

/*!
    \fn void QExtStringPropertyManager::setValue(QExtProperty *property, const QString &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value doesn't match the given \a property's
    regular expression, this function does nothing.

    \sa value(), setRegExp(), valueChanged()
*/
void QExtStringPropertyManager::setValue(QExtProperty *property, const QString &val)
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtStringPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
    {
        return;
    }

    if (data.regExp.isValid() && !data.regExp.exactMatch(val))
    {
        return;
    }

    data.val = val;

    it.value() = data;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

/*!
    Sets the regular expression of the given \a property to \a regExp.

    \sa regExp(), setValue(), regExpChanged()
*/
void QExtStringPropertyManager::setRegExp(QExtProperty *property, const QRegExp &regExp)
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtStringPropertyManagerPrivate::Data data = it.value() ;

    if (data.regExp == regExp)
    {
        return;
    }

    data.regExp = regExp;

    it.value() = data;

    emit this->regExpChanged(property, data.regExp);
}


void QExtStringPropertyManager::setEchoMode(QExtProperty *property, EchoMode echoMode)
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtStringPropertyManagerPrivate::Data data = it.value();

    if (data.echoMode == echoMode)
    {
        return;
    }

    data.echoMode = echoMode;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->echoModeChanged(property, data.echoMode);
}

void QExtStringPropertyManager::setReadOnly(QExtProperty *property, bool readOnly)
{
    const QExtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtStringPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
    {
        return;
    }

    data.readOnly = readOnly;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->readOnlyChanged(property, data.readOnly);
}

/*!
    \reimp
*/
void QExtStringPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtStringPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QExtStringPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtBoolPropertyManager
//     Return an icon containing a check box indicator
static QIcon drawCheckBox(bool value)
{
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    // Figure out size of an indicator and make sure it is not scaled down in a list view item
    // by making the pixmap as big as a list view icon and centering the indicator in it.
    // (if it is smaller, it can't be helped)
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // Center?
        const int xoff = (pixmapWidth  > indicatorWidth)  ? (pixmapWidth  - indicatorWidth)  / 2 : 0;
        const int yoff = (pixmapHeight > indicatorHeight) ? (pixmapHeight - indicatorHeight) / 2 : 0;
        QPainter painter(&pixmap);
        painter.translate(xoff, yoff);
        style->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, &painter);
    }
    return QIcon(pixmap);
}

class QExtBoolPropertyManagerPrivate
{
    QExtBoolPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtBoolPropertyManager)
public:
    QExtBoolPropertyManagerPrivate();

    struct Data
    {
        Data() : val(false), textVisible(true) {}
        bool val;
        bool textVisible;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    const QIcon m_checkedIcon;
    const QIcon m_uncheckedIcon;
};

QExtBoolPropertyManagerPrivate::QExtBoolPropertyManagerPrivate() :
    m_checkedIcon(drawCheckBox(true)),
    m_uncheckedIcon(drawCheckBox(false))
{
}

/*!
    \class QExtBoolPropertyManager

    \brief The QExtBoolPropertyManager class provides and manages boolean properties.

    The property's value can be retrieved using the value() function,
    and set using the setValue() slot.

    In addition, QExtBoolPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager, QExtCheckBoxFactory
*/

/*!
    \fn void QExtBoolPropertyManager::valueChanged(QExtProperty *property, bool value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtBoolPropertyManager::QExtBoolPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtBoolPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtBoolPropertyManager::~QExtBoolPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns false.

    \sa setValue()
*/
bool QExtBoolPropertyManager::value(const QExtProperty *property) const
{
    return getValue<bool>(d_ptr->m_values, property, false);
}

bool QExtBoolPropertyManager::textVisible(const QExtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QExtBoolPropertyManagerPrivate::Data::textVisible, property, false);
}

/*!
    \reimp
*/
QString QExtBoolPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QString();
    }

    const QExtBoolPropertyManagerPrivate::Data &data = it.value();
    if (!data.textVisible)
    {
        return QString();
    }

    static const QString trueText = tr("True");
    static const QString falseText = tr("False");
    return data.val ? trueText : falseText;
}

/*!
    \reimp
*/
QIcon QExtBoolPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    {
        return QIcon();
    }

    return it.value().val ? d_ptr->m_checkedIcon : d_ptr->m_uncheckedIcon;
}

/*!
    \fn void QExtBoolPropertyManager::setValue(QExtProperty *property, bool value)

    Sets the value of the given \a property to \a value.

    \sa value()
*/
void QExtBoolPropertyManager::setValue(QExtProperty *property, bool val)
{
    const QExtBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    {
        return;
    }

    QExtBoolPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
    {
        return;
    }

    data.val = val;
    it.value() = data;

    emit this->propertyChanged(property);
    emit this->valueChanged(property, data.val);
}

void QExtBoolPropertyManager::setTextVisible(QExtProperty *property, bool textVisible)
{
    const QExtBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtBoolPropertyManagerPrivate::Data data = it.value();

    if (data.textVisible == textVisible)
        return;

    data.textVisible = textVisible;
    it.value() = data;

    emit propertyChanged(property);
    emit textVisibleChanged(property, data.textVisible);
}

/*!
    \reimp
*/
void QExtBoolPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtBoolPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QExtBoolPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtDatePropertyManager

class QExtDatePropertyManagerPrivate
{
    QExtDatePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtDatePropertyManager)
public:

    struct Data
    {
        Data() : val(QDate::currentDate()), minVal(QDate(1752, 9, 14)),
            maxVal(QDate(7999, 12, 31)) {}
        QDate val;
        QDate minVal;
        QDate maxVal;
        QDate minimumValue() const { return minVal; }
        QDate maximumValue() const { return maxVal; }
        void setMinimumValue(const QDate &newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(const QDate &newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    QString m_format;

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    QMap<const QExtProperty *, Data> m_values;
};

/*!
    \class QExtDatePropertyManager

    \brief The QExtDatePropertyManager provides and manages QDate properties.

    A date property has a current value, and a range specifying the
    valid dates. The range is defined by a minimum and a maximum
    value.

    The property's values can be retrieved using the minimum(),
    maximum() and value() functions, and can be set using the
    setMinimum(), setMaximum() and setValue() slots. Alternatively,
    the range can be defined in one go using the setRange() slot.

    In addition, QExtDatePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid dates.

    \sa QExtAbstractPropertyManager, QExtDateEditFactory, QExtDateTimePropertyManager
*/

/*!
    \fn void QExtDatePropertyManager::valueChanged(QExtProperty *property, const QDate &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtDatePropertyManager::rangeChanged(QExtProperty *property, const QDate &minimum, const QDate &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid dates, passing a pointer to the \a
    property and the new \a minimum and \a maximum dates.

    \sa setRange()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtDatePropertyManager::QExtDatePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtDatePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtDatePropertyManager::~QExtDatePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns an invalid date.

    \sa setValue()
*/
QDate QExtDatePropertyManager::value(const QExtProperty *property) const
{
    return getValue<QDate>(d_ptr->m_values, property);
}

/*!
    Returns the given \a  property's  minimum date.

    \sa maximum(), setRange()
*/
QDate QExtDatePropertyManager::minimum(const QExtProperty *property) const
{
    return getMinimum<QDate>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum date.

    \sa minimum(), setRange()
*/
QDate QExtDatePropertyManager::maximum(const QExtProperty *property) const
{
    return getMaximum<QDate>(d_ptr->m_values, property);
}

/*!
    \reimp
*/
QString QExtDatePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtDatePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().val.toString(d_ptr->m_format);
}

/*!
    \fn void QExtDatePropertyManager::setValue(QExtProperty *property, const QDate &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not a valid date according to the
    given \a property's range, the value is adjusted to the nearest
    valid value within the range.

    \sa value(), setRange(), valueChanged()
*/
void QExtDatePropertyManager::setValue(QExtProperty *property, const QDate &val)
{
    void (QExtDatePropertyManagerPrivate::*setSubPropertyValue)(QExtProperty *, const QDate &) = 0;
    setValueInRange<const QDate &, QExtDatePropertyManagerPrivate, QExtDatePropertyManager, const QDate>(this, d_ptr,
                                                                                                         &QExtDatePropertyManager::propertyChanged,
                                                                                                         &QExtDatePropertyManager::valueChanged,
                                                                                                         property, val, setSubPropertyValue);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa minimum(), setRange()
*/
void QExtDatePropertyManager::setMinimum(QExtProperty *property, const QDate &minVal)
{
    setMinimumValue<const QDate &, QExtDatePropertyManagerPrivate, QExtDatePropertyManager, QDate, QExtDatePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtDatePropertyManager::propertyChanged,
                                                                                                                                         &QExtDatePropertyManager::valueChanged,
                                                                                                                                         &QExtDatePropertyManager::rangeChanged,
                                                                                                                                         property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting the maximum value, the minimum and current
    values are adjusted if necessary (ensuring that the range remains
    valid and that the current value is within in the range).

    \sa maximum(), setRange()
*/
void QExtDatePropertyManager::setMaximum(QExtProperty *property, const QDate &maxVal)
{
    setMaximumValue<const QDate &, QExtDatePropertyManagerPrivate, QExtDatePropertyManager, QDate, QExtDatePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                         &QExtDatePropertyManager::propertyChanged,
                                                                                                                                         &QExtDatePropertyManager::valueChanged,
                                                                                                                                         &QExtDatePropertyManager::rangeChanged,
                                                                                                                                         property, maxVal);
}

/*!
    \fn void QExtDatePropertyManager::setRange(QExtProperty *property, const QDate &minimum, const QDate &maximum)

    Sets the range of valid dates.

    This is a convenience function defining the range of valid dates
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new date range, the current value is adjusted if
    necessary (ensuring that the value remains in date range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QExtDatePropertyManager::setRange(QExtProperty *property, const QDate &minVal, const QDate &maxVal)
{
    void (QExtDatePropertyManagerPrivate::*setSubPropertyRange)(QExtProperty *, const QDate &,
                                                                const QDate &, const QDate &) = 0;
    setBorderValues<const QDate &, QExtDatePropertyManagerPrivate, QExtDatePropertyManager, QDate>(this, d_ptr,
                                                                                                   &QExtDatePropertyManager::propertyChanged,
                                                                                                   &QExtDatePropertyManager::valueChanged,
                                                                                                   &QExtDatePropertyManager::rangeChanged,
                                                                                                   property, minVal, maxVal, setSubPropertyRange);
}

/*!
    \reimp
*/
void QExtDatePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtDatePropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QExtDatePropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtTimePropertyManager

class QExtTimePropertyManagerPrivate
{
    QExtTimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtTimePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtProperty *, QTime> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QExtTimePropertyManager

    \brief The QExtTimePropertyManager provides and manages QTime properties.

    A time property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QExtTimePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager, QExtTimeEditFactory
*/

/*!
    \fn void QExtTimePropertyManager::valueChanged(QExtProperty *property, const QTime &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtTimePropertyManager::QExtTimePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtTimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.timeFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtTimePropertyManager::~QExtTimePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns an invalid time object.

    \sa setValue()
*/
QTime QExtTimePropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QTime());
}

/*!
    \reimp
*/
QString QExtTimePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtTimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(d_ptr->m_format);
}

/*!
    \fn void QExtTimePropertyManager::setValue(QExtProperty *property, const QTime &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QExtTimePropertyManager::setValue(QExtProperty *property, const QTime &val)
{
    setSimpleValue<const QTime &, QTime, QExtTimePropertyManager>(d_ptr->m_values, this,
                                                                  &QExtTimePropertyManager::propertyChanged,
                                                                  &QExtTimePropertyManager::valueChanged,
                                                                  property, val);
}

/*!
    \reimp
*/
void QExtTimePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QTime::currentTime();
}

/*!
    \reimp
*/
void QExtTimePropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtDateTimePropertyManager

class QExtDateTimePropertyManagerPrivate
{
    QExtDateTimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtDateTimePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtProperty *, QDateTime> PropertyValueMap;
    PropertyValueMap m_values;
};

/*! \class QExtDateTimePropertyManager

    \brief The QExtDateTimePropertyManager provides and manages QDateTime properties.

    A date and time property has a current value which can be
    retrieved using the value() function, and set using the setValue()
    slot. In addition, QExtDateTimePropertyManager provides the
    valueChanged() signal which is emitted whenever a property created
    by this manager changes.

    \sa QExtAbstractPropertyManager, QExtDateTimeEditFactory, QExtDatePropertyManager
*/

/*!
    \fn void QExtDateTimePropertyManager::valueChanged(QExtProperty *property, const QDateTime &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtDateTimePropertyManager::QExtDateTimePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtDateTimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
    d_ptr->m_format += QLatin1Char(' ');
    d_ptr->m_format += loc.timeFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtDateTimePropertyManager::~QExtDateTimePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid QDateTime object.

    \sa setValue()
*/
QDateTime QExtDateTimePropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QDateTime());
}

/*!
    \reimp
*/
QString QExtDateTimePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtDateTimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(d_ptr->m_format);
}

/*!
    \fn void QExtDateTimePropertyManager::setValue(QExtProperty *property, const QDateTime &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QExtDateTimePropertyManager::setValue(QExtProperty *property, const QDateTime &val)
{
    setSimpleValue<const QDateTime &, QDateTime, QExtDateTimePropertyManager>(d_ptr->m_values, this,
                                                                              &QExtDateTimePropertyManager::propertyChanged,
                                                                              &QExtDateTimePropertyManager::valueChanged,
                                                                              property, val);
}

/*!
    \reimp
*/
void QExtDateTimePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QDateTime::currentDateTime();
}

/*!
    \reimp
*/
void QExtDateTimePropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtKeySequencePropertyManager

class QExtKeySequencePropertyManagerPrivate
{
    QExtKeySequencePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtKeySequencePropertyManager)
public:

    QString m_format;

    typedef QMap<const QExtProperty *, QKeySequence> PropertyValueMap;
    PropertyValueMap m_values;
};

/*! \class QExtKeySequencePropertyManager

    \brief The QExtKeySequencePropertyManager provides and manages QKeySequence properties.

    A key sequence's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QExtKeySequencePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager
*/

/*!
    \fn void QExtKeySequencePropertyManager::valueChanged(QExtProperty *property, const QKeySequence &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtKeySequencePropertyManager::QExtKeySequencePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtKeySequencePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtKeySequencePropertyManager::~QExtKeySequencePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an empty QKeySequence object.

    \sa setValue()
*/
QKeySequence QExtKeySequencePropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QKeySequence());
}

/*!
    \reimp
*/
QString QExtKeySequencePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtKeySequencePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().toString(QKeySequence::NativeText);
}

/*!
    \fn void QExtKeySequencePropertyManager::setValue(QExtProperty *property, const QKeySequence &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QExtKeySequencePropertyManager::setValue(QExtProperty *property, const QKeySequence &val)
{
    setSimpleValue<const QKeySequence &, QKeySequence, QExtKeySequencePropertyManager>(d_ptr->m_values, this,
                                                                                       &QExtKeySequencePropertyManager::propertyChanged,
                                                                                       &QExtKeySequencePropertyManager::valueChanged,
                                                                                       property, val);
}

/*!
    \reimp
*/
void QExtKeySequencePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QKeySequence();
}

/*!
    \reimp
*/
void QExtKeySequencePropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtCharPropertyManager

class QExtCharPropertyManagerPrivate
{
    QExtCharPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtCharPropertyManager)
public:

    typedef QMap<const QExtProperty *, QChar> PropertyValueMap;
    PropertyValueMap m_values;
};

/*! \class QExtCharPropertyManager

    \brief The QExtCharPropertyManager provides and manages QChar properties.

    A char's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QExtCharPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager
*/

/*!
    \fn void QExtCharPropertyManager::valueChanged(QExtProperty *property, const QChar &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtCharPropertyManager::QExtCharPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtCharPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtCharPropertyManager::~QExtCharPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an null QChar object.

    \sa setValue()
*/
QChar QExtCharPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QChar());
}

/*!
    \reimp
*/
QString QExtCharPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtCharPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QChar c = it.value();
    return c.isNull() ? QString() : QString(c);
}

/*!
    \fn void QExtCharPropertyManager::setValue(QExtProperty *property, const QChar &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QExtCharPropertyManager::setValue(QExtProperty *property, const QChar &val)
{
    setSimpleValue<const QChar &, QChar, QExtCharPropertyManager>(d_ptr->m_values, this,
                                                                  &QExtCharPropertyManager::propertyChanged,
                                                                  &QExtCharPropertyManager::valueChanged,
                                                                  property, val);
}

/*!
    \reimp
*/
void QExtCharPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QChar();
}

/*!
    \reimp
*/
void QExtCharPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtLocalePropertyManager

class QExtLocalePropertyManagerPrivate
{
    QExtLocalePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtLocalePropertyManager)
public:

    QExtLocalePropertyManagerPrivate();

    void slotEnumChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);

    typedef QMap<const QExtProperty *, QLocale> PropertyValueMap;
    PropertyValueMap m_values;

    QExtEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToLanguage;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToCountry;

    QMap<const QExtProperty *, QExtProperty *> m_languageToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_countryToProperty;
};

QExtLocalePropertyManagerPrivate::QExtLocalePropertyManagerPrivate()
{
}

void QExtLocalePropertyManagerPrivate::slotEnumChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_languageToProperty.value(property, 0)) {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(value, 0, &newLanguage, 0);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    } else if (QExtProperty *prop = m_countryToProperty.value(property, 0)) {
        const QLocale loc = m_values[prop];
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(m_enumPropertyManager->value(m_propertyToLanguage.value(prop)), value, &newLanguage, &newCountry);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    }
}

void QExtLocalePropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *subProp = m_languageToProperty.value(property, 0)) {
        m_propertyToLanguage[subProp] = 0;
        m_languageToProperty.remove(property);
    } else if (QExtProperty *subProp = m_countryToProperty.value(property, 0)) {
        m_propertyToCountry[subProp] = 0;
        m_countryToProperty.remove(property);
    }
}

/*!
    \class QExtLocalePropertyManager

    \brief The QExtLocalePropertyManager provides and manages QLocale properties.

    A locale property has nested \e language and \e country
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by QExtEnumPropertyManager object.
    These submanager can be retrieved using the subEnumPropertyManager()
    function. In order to provide editing widgets for the subproperties
    in a property browser widget, this manager must be associated with editor factory.

    In addition, QExtLocalePropertyManager provides the valueChanged()
    signal which is emitted whenever a property created by this
    manager changes.

    \sa QExtAbstractPropertyManager, QExtEnumPropertyManager
*/

/*!
    \fn void QExtLocalePropertyManager::valueChanged(QExtProperty *property, const QLocale &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtLocalePropertyManager::QExtLocalePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtLocalePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_enumPropertyManager = new QExtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotEnumChanged(QExtProperty *, int)));

    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtLocalePropertyManager::~QExtLocalePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e language
    and \e country subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtEnumPropertyManager *QExtLocalePropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns the default locale.

    \sa setValue()
*/
QLocale QExtLocalePropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QLocale());
}

/*!
    \reimp
*/
QString QExtLocalePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtLocalePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    QLocale loc = it.value();

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(loc.language(), loc.country(), &langIdx, &countryIdx);
    QString str = tr("%1, %2")
            .arg(metaEnumProvider()->languageEnumNames().at(langIdx))
            .arg(metaEnumProvider()->countryEnumNames(loc.language()).at(countryIdx));
    return str;
}

/*!
    \fn void QExtLocalePropertyManager::setValue(QExtProperty *property, const QLocale &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtLocalePropertyManager::setValue(QExtProperty *property, const QLocale &val)
{
    const QExtLocalePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    const QLocale loc = it.value();
    if (loc == val)
        return;

    it.value() = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);
    if (loc.language() != val.language()) {
        d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToLanguage.value(property), langIdx);
        d_ptr->m_enumPropertyManager->setEnumNames(d_ptr->m_propertyToCountry.value(property),
                                                   metaEnumProvider()->countryEnumNames(val.language()));
    }
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToCountry.value(property), countryIdx);

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QExtLocalePropertyManager::initializeProperty(QExtProperty *property)
{
    QLocale val;
    d_ptr->m_values[property] = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);

    QExtProperty *languageProp = d_ptr->m_enumPropertyManager->addProperty();
    languageProp->setPropertyName(tr("Language"));
    d_ptr->m_enumPropertyManager->setEnumNames(languageProp, metaEnumProvider()->languageEnumNames());
    d_ptr->m_enumPropertyManager->setValue(languageProp, langIdx);
    d_ptr->m_propertyToLanguage[property] = languageProp;
    d_ptr->m_languageToProperty[languageProp] = property;
    property->addSubProperty(languageProp);

    QExtProperty *countryProp = d_ptr->m_enumPropertyManager->addProperty();
    countryProp->setPropertyName(tr("Country"));
    d_ptr->m_enumPropertyManager->setEnumNames(countryProp, metaEnumProvider()->countryEnumNames(val.language()));
    d_ptr->m_enumPropertyManager->setValue(countryProp, countryIdx);
    d_ptr->m_propertyToCountry[property] = countryProp;
    d_ptr->m_countryToProperty[countryProp] = property;
    property->addSubProperty(countryProp);
}

/*!
    \reimp
*/
void QExtLocalePropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *languageProp = d_ptr->m_propertyToLanguage[property];
    if (languageProp) {
        d_ptr->m_languageToProperty.remove(languageProp);
        delete languageProp;
    }
    d_ptr->m_propertyToLanguage.remove(property);

    QExtProperty *countryProp = d_ptr->m_propertyToCountry[property];
    if (countryProp) {
        d_ptr->m_countryToProperty.remove(countryProp);
        delete countryProp;
    }
    d_ptr->m_propertyToCountry.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtPointPropertyManager

class QExtPointPropertyManagerPrivate
{
    QExtPointPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPointPropertyManager)
public:

    void slotIntChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);

    typedef QMap<const QExtProperty *, QPoint> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToX;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToY;

    QMap<const QExtProperty *, QExtProperty *> m_xToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_yToProperty;
};

void QExtPointPropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (QExtProperty *xprop = m_xToProperty.value(property, 0)) {
        QPoint p = m_values[xprop];
        p.setX(value);
        q_ptr->setValue(xprop, p);
    } else if (QExtProperty *yprop = m_yToProperty.value(property, 0)) {
        QPoint p = m_values[yprop];
        p.setY(value);
        q_ptr->setValue(yprop, p);
    }
}

void QExtPointPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_xToProperty.value(property, 0)) {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_yToProperty.value(property, 0)) {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
}

/*! \class QExtPointPropertyManager

    \brief The QExtPointPropertyManager provides and manages QPoint properties.

    A point property has nested \e x and \e y subproperties. The
    top-level property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The subproperties are created by a QExtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QExtPointPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes.

    \sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtPointFPropertyManager
*/

/*!
    \fn void QExtPointPropertyManager::valueChanged(QExtProperty *property, const QPoint &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtPointPropertyManager::QExtPointPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtPointPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtPointPropertyManager::~QExtPointPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x and \e y
    subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtPointPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a point with coordinates (0, 0).

    \sa setValue()
*/
QPoint QExtPointPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QPoint());
}

/*!
    \reimp
*/
QString QExtPointPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtPointPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPoint v = it.value();
    return QString(tr("(%1, %2)").arg(QString::number(v.x()))
                   .arg(QString::number(v.y())));
}

/*!
    \fn void QExtPointPropertyManager::setValue(QExtProperty *property, const QPoint &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtPointPropertyManager::setValue(QExtProperty *property, const QPoint &val)
{
    const QExtPointPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QExtPointPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QPoint(0, 0);

    QExtProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

/*!
    \reimp
*/
void QExtPointPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtPointFPropertyManager

class QExtPointFPropertyManagerPrivate
{
    QExtPointFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtPointFPropertyManager)
public:

    struct Data
    {
        Data() : decimals(2) {}
        QPointF val;
        int decimals;
    };

    void slotDoubleChanged(QExtProperty *property, double value);
    void slotPropertyDestroyed(QExtProperty *property);

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToX;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToY;

    QMap<const QExtProperty *, QExtProperty *> m_xToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_yToProperty;
};

void QExtPointFPropertyManagerPrivate::slotDoubleChanged(QExtProperty *property, double value)
{
    if (QExtProperty *prop = m_xToProperty.value(property, 0)) {
        QPointF p = m_values[prop].val;
        p.setX(value);
        q_ptr->setValue(prop, p);
    } else if (QExtProperty *prop = m_yToProperty.value(property, 0)) {
        QPointF p = m_values[prop].val;
        p.setY(value);
        q_ptr->setValue(prop, p);
    }
}

void QExtPointFPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp  = m_xToProperty.value(property, 0)) {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_yToProperty.value(property, 0)) {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    }
}

/*! \class QExtPointFPropertyManager

    \brief The QExtPointFPropertyManager provides and manages QPointF properties.

    A point property has nested \e x and \e y subproperties. The
    top-level property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The subproperties are created by a QExtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QExtPointFPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes.

    \sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtPointPropertyManager
*/

/*!
    \fn void QExtPointFPropertyManager::valueChanged(QExtProperty *property, const QPointF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtPointFPropertyManager::decimalsChanged(QExtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setDecimals()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtPointFPropertyManager::QExtPointFPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtPointFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtPointFPropertyManager::~QExtPointFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x and \e y
    subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtDoublePropertyManager *QExtPointFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a point with coordinates (0, 0).

    \sa setValue()
*/
QPointF QExtPointFPropertyManager::value(const QExtProperty *property) const
{
    return getValue<QPointF>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setDecimals()
*/
int QExtPointFPropertyManager::decimals(const QExtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtPointFPropertyManagerPrivate::Data::decimals, property, 0);
}

/*!
    \reimp
*/
QString QExtPointFPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtPointFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPointF v = it.value().val;
    const int dec =  it.value().decimals;
    return QString(tr("(%1, %2)").arg(QString::number(v.x(), 'f', dec))
                   .arg(QString::number(v.y(), 'f', dec)));
}

/*!
    \fn void QExtPointFPropertyManager::setValue(QExtProperty *property, const QPointF &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtPointFPropertyManager::setValue(QExtProperty *property, const QPointF &val)
{
    const QExtPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \fn void QExtPointFPropertyManager::setDecimals(QExtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa decimals()
*/
void QExtPointFPropertyManager::setDecimals(QExtProperty *property, int prec)
{
    const QExtPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtPointFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

/*!
    \reimp
*/
void QExtPointFPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtPointFPropertyManagerPrivate::Data();

    QExtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

/*!
    \reimp
*/
void QExtPointFPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtSizePropertyManager

class QExtSizePropertyManagerPrivate
{
    QExtSizePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtSizePropertyManager)
public:

    void slotIntChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);
    void setValue(QExtProperty *property, const QSize &val);
    void setRange(QExtProperty *property,
                  const QSize &minVal, const QSize &maxVal, const QSize &val);

    struct Data
    {
        Data() : val(QSize(0, 0)), minVal(QSize(0, 0)), maxVal(QSize(INT_MAX, INT_MAX)) {}
        QSize val;
        QSize minVal;
        QSize maxVal;
        QSize minimumValue() const { return minVal; }
        QSize maximumValue() const { return maxVal; }
        void setMinimumValue(const QSize &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSize &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToW;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToH;

    QMap<const QExtProperty *, QExtProperty *> m_wToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_hToProperty;
};

void QExtSizePropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_wToProperty.value(property, 0)) {
        QSize s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } else if (QExtProperty *prop = m_hToProperty.value(property, 0)) {
        QSize s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QExtSizePropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_wToProperty.value(property, 0)) {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_hToProperty.value(property, 0)) {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void QExtSizePropertyManagerPrivate::setValue(QExtProperty *property, const QSize &val)
{
    m_intPropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_intPropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QExtSizePropertyManagerPrivate::setRange(QExtProperty *property,
                                              const QSize &minVal, const QSize &maxVal, const QSize &val)
{
    QExtProperty *wProperty = m_propertyToW.value(property);
    QExtProperty *hProperty = m_propertyToH.value(property);
    m_intPropertyManager->setRange(wProperty, minVal.width(), maxVal.width());
    m_intPropertyManager->setValue(wProperty, val.width());
    m_intPropertyManager->setRange(hProperty, minVal.height(), maxVal.height());
    m_intPropertyManager->setValue(hProperty, val.height());
}

/*!
    \class QExtSizePropertyManager

    \brief The QExtSizePropertyManager provides and manages QSize properties.

    A size property has nested \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QExtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A size property also has a range of valid values defined by a
    minimum size and a maximum size. These sizes can be retrieved
    using the minimum() and the maximum() functions, and set using the
    setMinimum() and setMaximum() slots. Alternatively, the range can
    be defined in one go using the setRange() slot.

    In addition, QExtSizePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid sizes.

    \sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtSizeFPropertyManager
*/

/*!
    \fn void QExtSizePropertyManager::valueChanged(QExtProperty *property, const QSize &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtSizePropertyManager::rangeChanged(QExtProperty *property, const QSize &minimum, const QSize &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid sizes, passing a pointer to the \a
    property and the new \a minimum and \a maximum sizes.

    \sa setRange()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtSizePropertyManager::QExtSizePropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtSizePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtSizePropertyManager::~QExtSizePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e width and \e height
    subproperties.

    In order to provide editing widgets for the \e width and \e height
    properties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtSizePropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid size

    \sa setValue()
*/
QSize QExtSizePropertyManager::value(const QExtProperty *property) const
{
    return getValue<QSize>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's minimum size value.

    \sa setMinimum(), maximum(), setRange()
*/
QSize QExtSizePropertyManager::minimum(const QExtProperty *property) const
{
    return getMinimum<QSize>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum size value.

    \sa setMaximum(), minimum(), setRange()
*/
QSize QExtSizePropertyManager::maximum(const QExtProperty *property) const
{
    return getMaximum<QSize>(d_ptr->m_values, property);
}

/*!
    \reimp
*/
QString QExtSizePropertyManager::valueText(const QExtProperty *property) const
{
    const QExtSizePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSize v = it.value().val;
    return QString(tr("%1 x %2").arg(QString::number(v.width()))
                   .arg(QString::number(v.height())));
}

/*!
    \fn void QExtSizePropertyManager::setValue(QExtProperty *property, const QSize &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's size range, the \a value is adjusted to the nearest
    valid value within the size range.

    \sa value(), setRange(), valueChanged()
*/
void QExtSizePropertyManager::setValue(QExtProperty *property, const QSize &val)
{
    setValueInRange<const QSize &, QExtSizePropertyManagerPrivate, QExtSizePropertyManager, const QSize>(this, d_ptr,
                                                                                                         &QExtSizePropertyManager::propertyChanged,
                                                                                                         &QExtSizePropertyManager::valueChanged,
                                                                                                         property, val, &QExtSizePropertyManagerPrivate::setValue);
}

/*!
    Sets the minimum size value for the given \a property to \a minVal.

    When setting the minimum size value, the maximum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QExtSizePropertyManager::setMinimum(QExtProperty *property, const QSize &minVal)
{
    setBorderValue<const QSize &, QExtSizePropertyManagerPrivate, QExtSizePropertyManager, QSize, QExtSizePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                        &QExtSizePropertyManager::propertyChanged,
                                                                                                                                        &QExtSizePropertyManager::valueChanged,
                                                                                                                                        &QExtSizePropertyManager::rangeChanged,
                                                                                                                                        property,
                                                                                                                                        &QExtSizePropertyManagerPrivate::Data::minimumValue,
                                                                                                                                        &QExtSizePropertyManagerPrivate::Data::setMinimumValue,
                                                                                                                                        minVal, &QExtSizePropertyManagerPrivate::setRange);
}

/*!
    Sets the maximum size value for the given \a property to \a maxVal.

    When setting the maximum size value, the minimum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QExtSizePropertyManager::setMaximum(QExtProperty *property, const QSize &maxVal)
{
    setBorderValue<const QSize &, QExtSizePropertyManagerPrivate, QExtSizePropertyManager, QSize, QExtSizePropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                        &QExtSizePropertyManager::propertyChanged,
                                                                                                                                        &QExtSizePropertyManager::valueChanged,
                                                                                                                                        &QExtSizePropertyManager::rangeChanged,
                                                                                                                                        property,
                                                                                                                                        &QExtSizePropertyManagerPrivate::Data::maximumValue,
                                                                                                                                        &QExtSizePropertyManagerPrivate::Data::setMaximumValue,
                                                                                                                                        maxVal, &QExtSizePropertyManagerPrivate::setRange);
}

/*!
    \fn void QExtSizePropertyManager::setRange(QExtProperty *property, const QSize &minimum, const QSize &maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within the range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QExtSizePropertyManager::setRange(QExtProperty *property, const QSize &minVal, const QSize &maxVal)
{
    setBorderValues<const QSize &, QExtSizePropertyManagerPrivate, QExtSizePropertyManager, QSize>(this, d_ptr,
                                                                                                   &QExtSizePropertyManager::propertyChanged,
                                                                                                   &QExtSizePropertyManager::valueChanged,
                                                                                                   &QExtSizePropertyManager::rangeChanged,
                                                                                                   property, minVal, maxVal, &QExtSizePropertyManagerPrivate::setRange);
}

/*!
    \reimp
*/
void QExtSizePropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtSizePropertyManagerPrivate::Data();

    QExtProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QExtSizePropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtSizeFPropertyManager

class QExtSizeFPropertyManagerPrivate
{
    QExtSizeFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtSizeFPropertyManager)
public:

    void slotDoubleChanged(QExtProperty *property, double value);
    void slotPropertyDestroyed(QExtProperty *property);
    void setValue(QExtProperty *property, const QSizeF &val);
    void setRange(QExtProperty *property,
                  const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val);

    struct Data
    {
        Data() : val(QSizeF(0, 0)), minVal(QSizeF(0, 0)), maxVal(QSizeF(INT_MAX, INT_MAX)), decimals(2) {}
        QSizeF val;
        QSizeF minVal;
        QSizeF maxVal;
        int decimals;
        QSizeF minimumValue() const { return minVal; }
        QSizeF maximumValue() const { return maxVal; }
        void setMinimumValue(const QSizeF &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSizeF &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToW;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToH;

    QMap<const QExtProperty *, QExtProperty *> m_wToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_hToProperty;
};

void QExtSizeFPropertyManagerPrivate::slotDoubleChanged(QExtProperty *property, double value)
{
    if (QExtProperty *prop = m_wToProperty.value(property, 0)) {
        QSizeF s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } else if (QExtProperty *prop = m_hToProperty.value(property, 0)) {
        QSizeF s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QExtSizeFPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_wToProperty.value(property, 0)) {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_hToProperty.value(property, 0)) {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void QExtSizeFPropertyManagerPrivate::setValue(QExtProperty *property, const QSizeF &val)
{
    m_doublePropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_doublePropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QExtSizeFPropertyManagerPrivate::setRange(QExtProperty *property,
                                               const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val)
{
    m_doublePropertyManager->setRange(m_propertyToW[property], minVal.width(), maxVal.width());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setRange(m_propertyToH[property], minVal.height(), maxVal.height());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QExtSizeFPropertyManager

    \brief The QExtSizeFPropertyManager provides and manages QSizeF properties.

    A size property has nested \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QExtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A size property also has a range of valid values defined by a
    minimum size and a maximum size. These sizes can be retrieved
    using the minimum() and the maximum() functions, and set using the
    setMinimum() and setMaximum() slots. Alternatively, the range can
    be defined in one go using the setRange() slot.

    In addition, QExtSizeFPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid sizes.

    \sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtSizePropertyManager
*/

/*!
    \fn void QExtSizeFPropertyManager::valueChanged(QExtProperty *property, const QSizeF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtSizeFPropertyManager::rangeChanged(QExtProperty *property, const QSizeF &minimum, const QSizeF &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid sizes, passing a pointer to the \a
    property and the new \a minimum and \a maximum sizes.

    \sa setRange()
*/

/*!
    \fn void QExtSizeFPropertyManager::decimalsChanged(QExtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setDecimals()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtSizeFPropertyManager::QExtSizeFPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtSizeFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtSizeFPropertyManager::~QExtSizeFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e width and \e height
    subproperties.

    In order to provide editing widgets for the \e width and \e height
    properties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtDoublePropertyManager *QExtSizeFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid size

    \sa setValue()
*/
QSizeF QExtSizeFPropertyManager::value(const QExtProperty *property) const
{
    return getValue<QSizeF>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setDecimals()
*/
int QExtSizeFPropertyManager::decimals(const QExtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtSizeFPropertyManagerPrivate::Data::decimals, property, 0);
}

/*!
    Returns the given \a property's minimum size value.

    \sa setMinimum(), maximum(), setRange()
*/
QSizeF QExtSizeFPropertyManager::minimum(const QExtProperty *property) const
{
    return getMinimum<QSizeF>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum size value.

    \sa setMaximum(), minimum(), setRange()
*/
QSizeF QExtSizeFPropertyManager::maximum(const QExtProperty *property) const
{
    return getMaximum<QSizeF>(d_ptr->m_values, property);
}

/*!
    \reimp
*/
QString QExtSizeFPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtSizeFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSizeF v = it.value().val;
    const int dec = it.value().decimals;
    return QString(tr("%1 x %2").arg(QString::number(v.width(), 'f', dec))
                   .arg(QString::number(v.height(), 'f', dec)));
}

/*!
    \fn void QExtSizeFPropertyManager::setValue(QExtProperty *property, const QSizeF &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's size range, the \a value is adjusted to the nearest
    valid value within the size range.

    \sa value(), setRange(), valueChanged()
*/
void QExtSizeFPropertyManager::setValue(QExtProperty *property, const QSizeF &val)
{
    setValueInRange<const QSizeF &, QExtSizeFPropertyManagerPrivate, QExtSizeFPropertyManager, QSizeF>(this, d_ptr,
                                                                                                       &QExtSizeFPropertyManager::propertyChanged,
                                                                                                       &QExtSizeFPropertyManager::valueChanged,
                                                                                                       property, val, &QExtSizeFPropertyManagerPrivate::setValue);
}

/*!
    \fn void QExtSizeFPropertyManager::setDecimals(QExtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa decimals()
*/
void QExtSizeFPropertyManager::setDecimals(QExtProperty *property, int prec)
{
    const QExtSizeFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtSizeFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

/*!
    Sets the minimum size value for the given \a property to \a minVal.

    When setting the minimum size value, the maximum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QExtSizeFPropertyManager::setMinimum(QExtProperty *property, const QSizeF &minVal)
{
    setBorderValue<const QSizeF &, QExtSizeFPropertyManagerPrivate, QExtSizeFPropertyManager, QSizeF, QExtSizeFPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                             &QExtSizeFPropertyManager::propertyChanged,
                                                                                                                                             &QExtSizeFPropertyManager::valueChanged,
                                                                                                                                             &QExtSizeFPropertyManager::rangeChanged,
                                                                                                                                             property,
                                                                                                                                             &QExtSizeFPropertyManagerPrivate::Data::minimumValue,
                                                                                                                                             &QExtSizeFPropertyManagerPrivate::Data::setMinimumValue,
                                                                                                                                             minVal, &QExtSizeFPropertyManagerPrivate::setRange);
}

/*!
    Sets the maximum size value for the given \a property to \a maxVal.

    When setting the maximum size value, the minimum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QExtSizeFPropertyManager::setMaximum(QExtProperty *property, const QSizeF &maxVal)
{
    setBorderValue<const QSizeF &, QExtSizeFPropertyManagerPrivate, QExtSizeFPropertyManager, QSizeF, QExtSizeFPropertyManagerPrivate::Data>(this, d_ptr,
                                                                                                                                             &QExtSizeFPropertyManager::propertyChanged,
                                                                                                                                             &QExtSizeFPropertyManager::valueChanged,
                                                                                                                                             &QExtSizeFPropertyManager::rangeChanged,
                                                                                                                                             property,
                                                                                                                                             &QExtSizeFPropertyManagerPrivate::Data::maximumValue,
                                                                                                                                             &QExtSizeFPropertyManagerPrivate::Data::setMaximumValue,
                                                                                                                                             maxVal, &QExtSizeFPropertyManagerPrivate::setRange);
}

/*!
    \fn void QExtSizeFPropertyManager::setRange(QExtProperty *property, const QSizeF &minimum, const QSizeF &maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within the range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QExtSizeFPropertyManager::setRange(QExtProperty *property, const QSizeF &minVal, const QSizeF &maxVal)
{
    setBorderValues<const QSizeF &, QExtSizeFPropertyManagerPrivate, QExtSizeFPropertyManager, QSizeF>(this, d_ptr,
                                                                                                       &QExtSizeFPropertyManager::propertyChanged,
                                                                                                       &QExtSizeFPropertyManager::valueChanged,
                                                                                                       &QExtSizeFPropertyManager::rangeChanged,
                                                                                                       property, minVal, maxVal, &QExtSizeFPropertyManagerPrivate::setRange);
}

/*!
    \reimp
*/
void QExtSizeFPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtSizeFPropertyManagerPrivate::Data();

    QExtProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QExtSizeFPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtRectPropertyManager

class QExtRectPropertyManagerPrivate
{
    QExtRectPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtRectPropertyManager)
public:

    void slotIntChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);
    void setConstraint(QExtProperty *property, const QRect &constraint, const QRect &val);

    struct Data
    {
        Data() : val(0, 0, 0, 0) {}
        QRect val;
        QRect constraint;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToX;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToY;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToW;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToH;

    QMap<const QExtProperty *, QExtProperty *> m_xToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_yToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_wToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_hToProperty;
};

void QExtRectPropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_xToProperty.value(property, 0)) {
        QRect r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_yToProperty.value(property)) {
        QRect r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_wToProperty.value(property, 0)) {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_hToProperty.value(property, 0)) {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QExtRectPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_xToProperty.value(property, 0)) {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_yToProperty.value(property, 0)) {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_wToProperty.value(property, 0)) {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_hToProperty.value(property, 0)) {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void QExtRectPropertyManagerPrivate::setConstraint(QExtProperty *property,
                                                   const QRect &constraint, const QRect &val)
{
    const bool isNull = constraint.isNull();
    const int left   = isNull ? INT_MIN : constraint.left();
    const int right  = isNull ? INT_MAX : constraint.left() + constraint.width();
    const int top    = isNull ? INT_MIN : constraint.top();
    const int bottom = isNull ? INT_MAX : constraint.top() + constraint.height();
    const int width  = isNull ? INT_MAX : constraint.width();
    const int height = isNull ? INT_MAX : constraint.height();

    m_intPropertyManager->setRange(m_propertyToX[property], left, right);
    m_intPropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_intPropertyManager->setRange(m_propertyToW[property], 0, width);
    m_intPropertyManager->setRange(m_propertyToH[property], 0, height);

    m_intPropertyManager->setValue(m_propertyToX[property], val.x());
    m_intPropertyManager->setValue(m_propertyToY[property], val.y());
    m_intPropertyManager->setValue(m_propertyToW[property], val.width());
    m_intPropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QExtRectPropertyManager

    \brief The QExtRectPropertyManager provides and manages QRect properties.

    A rectangle property has nested \e x, \e y, \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QExtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A rectangle property also has a constraint rectangle which can be
    retrieved using the constraint() function, and set using the
    setConstraint() slot.

    In addition, QExtRectPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the constraintChanged() signal which is emitted
    whenever such a property changes its constraint rectangle.

    \sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtRectFPropertyManager
*/

/*!
    \fn void QExtRectPropertyManager::valueChanged(QExtProperty *property, const QRect &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtRectPropertyManager::constraintChanged(QExtProperty *property, const QRect &constraint)

    This signal is emitted whenever property changes its constraint
    rectangle, passing a pointer to the \a property and the new \a
    constraint rectangle as parameters.

    \sa setConstraint()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtRectPropertyManager::QExtRectPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtRectPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtRectPropertyManager::~QExtRectPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x, \e y, \e width
    and \e height subproperties.

    In order to provide editing widgets for the mentioned
    subproperties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtRectPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid rectangle.

    \sa setValue(), constraint()
*/
QRect QExtRectPropertyManager::value(const QExtProperty *property) const
{
    return getValue<QRect>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's constraining rectangle. If returned value is null QRect it means there is no constraint applied.

    \sa value(), setConstraint()
*/
QRect QExtRectPropertyManager::constraint(const QExtProperty *property) const
{
    return getData<QRect>(d_ptr->m_values, &QExtRectPropertyManagerPrivate::Data::constraint, property, QRect());
}

/*!
    \reimp
*/
QString QExtRectPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtRectPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRect v = it.value().val;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x()))
                   .arg(QString::number(v.y()))
                   .arg(QString::number(v.width()))
                   .arg(QString::number(v.height())));
}

/*!
    \fn void QExtRectPropertyManager::setValue(QExtProperty *property, const QRect &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    If the specified \a value is not inside the given \a property's
    constraining rectangle, the value is adjusted accordingly to fit
    within the constraint.

    \sa value(), setConstraint(), valueChanged()
*/
void QExtRectPropertyManager::setValue(QExtProperty *property, const QRect &val)
{
    const QExtRectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtRectPropertyManagerPrivate::Data data = it.value();

    QRect newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRect r1 = data.constraint;
        const QRect r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (data.val == newRect)
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's constraining rectangle to \a
    constraint.

    When setting the constraint, the current value is adjusted if
    necessary (ensuring that the current rectangle value is inside the
    constraint). In order to reset the constraint pass a null QRect value.

    \sa setValue(), constraint(), constraintChanged()
*/
void QExtRectPropertyManager::setConstraint(QExtProperty *property, const QRect &constraint)
{
    const QExtRectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtRectPropertyManagerPrivate::Data data = it.value();

    QRect newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
        return;

    const QRect oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRect r1 = data.constraint;
        QRect r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    \reimp
*/
void QExtRectPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtRectPropertyManagerPrivate::Data();

    QExtProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QExtProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QExtRectPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QExtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtRectFPropertyManager

class QExtRectFPropertyManagerPrivate
{
    QExtRectFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtRectFPropertyManager)
public:

    void slotDoubleChanged(QExtProperty *property, double value);
    void slotPropertyDestroyed(QExtProperty *property);
    void setConstraint(QExtProperty *property, const QRectF &constraint, const QRectF &val);

    struct Data
    {
        Data() : val(0, 0, 0, 0), decimals(2) {}
        QRectF val;
        QRectF constraint;
        int decimals;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToX;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToY;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToW;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToH;

    QMap<const QExtProperty *, QExtProperty *> m_xToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_yToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_wToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_hToProperty;
};

void QExtRectFPropertyManagerPrivate::slotDoubleChanged(QExtProperty *property, double value)
{
    if (QExtProperty *prop = m_xToProperty.value(property, 0)) {
        QRectF r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_yToProperty.value(property, 0)) {
        QRectF r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_wToProperty.value(property, 0)) {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } else if (QExtProperty *prop = m_hToProperty.value(property, 0)) {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QExtRectFPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_xToProperty.value(property, 0)) {
        m_propertyToX[pointProp] = 0;
        m_xToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_yToProperty.value(property, 0)) {
        m_propertyToY[pointProp] = 0;
        m_yToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_wToProperty.value(property, 0)) {
        m_propertyToW[pointProp] = 0;
        m_wToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_hToProperty.value(property, 0)) {
        m_propertyToH[pointProp] = 0;
        m_hToProperty.remove(property);
    }
}

void QExtRectFPropertyManagerPrivate::setConstraint(QExtProperty *property,
                                                    const QRectF &constraint, const QRectF &val)
{
    const bool isNull = constraint.isNull();
    const float left   = isNull ? FLT_MIN : constraint.left();
    const float right  = isNull ? FLT_MAX : constraint.left() + constraint.width();
    const float top    = isNull ? FLT_MIN : constraint.top();
    const float bottom = isNull ? FLT_MAX : constraint.top() + constraint.height();
    const float width  = isNull ? FLT_MAX : constraint.width();
    const float height = isNull ? FLT_MAX : constraint.height();

    m_doublePropertyManager->setRange(m_propertyToX[property], left, right);
    m_doublePropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_doublePropertyManager->setRange(m_propertyToW[property], 0, width);
    m_doublePropertyManager->setRange(m_propertyToH[property], 0, height);

    m_doublePropertyManager->setValue(m_propertyToX[property], val.x());
    m_doublePropertyManager->setValue(m_propertyToY[property], val.y());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QExtRectFPropertyManager

    \brief The QExtRectFPropertyManager provides and manages QRectF properties.

    A rectangle property has nested \e x, \e y, \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QExtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A rectangle property also has a constraint rectangle which can be
    retrieved using the constraint() function, and set using the
    setConstraint() slot.

    In addition, QExtRectFPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the constraintChanged() signal which is emitted
    whenever such a property changes its constraint rectangle.

    \sa QExtAbstractPropertyManager, QExtDoublePropertyManager, QExtRectPropertyManager
*/

/*!
    \fn void QExtRectFPropertyManager::valueChanged(QExtProperty *property, const QRectF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtRectFPropertyManager::constraintChanged(QExtProperty *property, const QRectF &constraint)

    This signal is emitted whenever property changes its constraint
    rectangle, passing a pointer to the \a property and the new \a
    constraint rectangle as parameters.

    \sa setConstraint()
*/

/*!
    \fn void QExtRectFPropertyManager::decimalsChanged(QExtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setDecimals()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtRectFPropertyManager::QExtRectFPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtRectFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QExtDoublePropertyManager(this);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotDoubleChanged(QExtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtRectFPropertyManager::~QExtRectFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x, \e y, \e width
    and \e height subproperties.

    In order to provide editing widgets for the mentioned
    subproperties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtDoublePropertyManager *QExtRectFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid rectangle.

    \sa setValue(), constraint()
*/
QRectF QExtRectFPropertyManager::value(const QExtProperty *property) const
{
    return getValue<QRectF>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setDecimals()
*/
int QExtRectFPropertyManager::decimals(const QExtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QExtRectFPropertyManagerPrivate::Data::decimals, property, 0);
}

/*!
    Returns the given \a property's constraining rectangle. If returned value is null QRectF it means there is no constraint applied.

    \sa value(), setConstraint()
*/
QRectF QExtRectFPropertyManager::constraint(const QExtProperty *property) const
{
    return getData<QRectF>(d_ptr->m_values, &QExtRectFPropertyManagerPrivate::Data::constraint, property, QRect());
}

/*!
    \reimp
*/
QString QExtRectFPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtRectFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRectF v = it.value().val;
    const int dec = it.value().decimals;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x(), 'f', dec))
                   .arg(QString::number(v.y(), 'f', dec))
                   .arg(QString::number(v.width(), 'f', dec))
                   .arg(QString::number(v.height(), 'f', dec)));
}

/*!
    \fn void QExtRectFPropertyManager::setValue(QExtProperty *property, const QRectF &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    If the specified \a value is not inside the given \a property's
    constraining rectangle, the value is adjusted accordingly to fit
    within the constraint.

    \sa value(), setConstraint(), valueChanged()
*/
void QExtRectFPropertyManager::setValue(QExtProperty *property, const QRectF &val)
{
    const QExtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtRectFPropertyManagerPrivate::Data data = it.value();

    QRectF newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRectF r1 = data.constraint;
        const QRectF r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (data.val == newRect)
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's constraining rectangle to \a
    constraint.

    When setting the constraint, the current value is adjusted if
    necessary (ensuring that the current rectangle value is inside the
    constraint). In order to reset the constraint pass a null QRectF value.

    \sa setValue(), constraint(), constraintChanged()
*/
void QExtRectFPropertyManager::setConstraint(QExtProperty *property, const QRectF &constraint)
{
    const QExtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtRectFPropertyManagerPrivate::Data data = it.value();

    QRectF newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
        return;

    const QRectF oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRectF r1 = data.constraint;
        QRectF r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    \fn void QExtRectFPropertyManager::setDecimals(QExtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa decimals()
*/
void QExtRectFPropertyManager::setDecimals(QExtProperty *property, int prec)
{
    const QExtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtRectFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.decimals == prec)
        return;

    data.decimals = prec;
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit decimalsChanged(property, data.decimals);
}

/*!
    \reimp
*/
void QExtRectFPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtRectFPropertyManagerPrivate::Data();

    QExtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QExtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QExtProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setDecimals(wProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QExtProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setDecimals(hProp, decimals(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QExtRectFPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QExtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QExtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QExtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtEnumPropertyManager

class QExtEnumPropertyManagerPrivate
{
    QExtEnumPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtEnumPropertyManager)
public:

    struct Data
    {
        Data() : val(-1) {}
        int val;
        QStringList enumNames;
        QMap<int, QIcon> enumIcons;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QExtEnumPropertyManager

    \brief The QExtEnumPropertyManager provides and manages enum properties.

    Each enum property has an associated list of enum names which can
    be retrieved using the enumNames() function, and set using the
    corresponding setEnumNames() function. An enum property's value is
    represented by an index in this list, and can be retrieved and set
    using the value() and setValue() slots respectively.

    Each enum value can also have an associated icon. The mapping from
    values to icons can be set using the setEnumIcons() function and
    queried with the enumIcons() function.

    In addition, QExtEnumPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes. The enumNamesChanged() or enumIconsChanged() signal is emitted
    whenever the list of enum names or icons is altered.

    \sa QExtAbstractPropertyManager, QExtEnumEditorFactory
*/

/*!
    \fn void QExtEnumPropertyManager::valueChanged(QExtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtEnumPropertyManager::enumNamesChanged(QExtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its enum names, passing a pointer to the \a property and
    the new \a names as parameters.

    \sa setEnumNames()
*/

/*!
    \fn void QExtEnumPropertyManager::enumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &icons)

    This signal is emitted whenever a property created by this manager
    changes its enum icons, passing a pointer to the \a property and
    the new mapping of values to \a icons as parameters.

    \sa setEnumIcons()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtEnumPropertyManager::QExtEnumPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtEnumPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtEnumPropertyManager::~QExtEnumPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value which is an index in the
    list returned by enumNames()

    If the given property is not managed by this manager, this
    function returns -1.

    \sa enumNames(), setValue()
*/
int QExtEnumPropertyManager::value(const QExtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, -1);
}

/*!
    Returns the given \a property's list of enum names.

    \sa value(), setEnumNames()
*/
QStringList QExtEnumPropertyManager::enumNames(const QExtProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QExtEnumPropertyManagerPrivate::Data::enumNames, property, QStringList());
}

/*!
    Returns the given \a property's map of enum values to their icons.

    \sa value(), setEnumIcons()
*/
QMap<int, QIcon> QExtEnumPropertyManager::enumIcons(const QExtProperty *property) const
{
    return getData<QMap<int, QIcon> >(d_ptr->m_values, &QExtEnumPropertyManagerPrivate::Data::enumIcons, property, QMap<int, QIcon>());
}

/*!
    \reimp
*/
QString QExtEnumPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QExtEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    if (v >= 0 && v < data.enumNames.count())
        return data.enumNames.at(v);
    return QString();
}

/*!
    \reimp
*/
QIcon QExtEnumPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    const QExtEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    return data.enumIcons.value(v);
}

/*!
    \fn void QExtEnumPropertyManager::setValue(QExtProperty *property, int value)

    Sets the value of the given  \a property to \a value.

    The specified \a value must be less than the size of the given \a
    property's enumNames() list, and larger than (or equal to) 0.

    \sa value(), valueChanged()
*/
void QExtEnumPropertyManager::setValue(QExtProperty *property, int val)
{
    const QExtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtEnumPropertyManagerPrivate::Data data = it.value();

    if (val >= data.enumNames.count())
        return;

    if (val < 0 && data.enumNames.count() > 0)
        return;

    if (val < 0)
        val = -1;

    if (data.val == val)
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of enum names to \a
    enumNames. The \a property's current value is reset to 0
    indicating the first item of the list.

    If the specified \a enumNames list is empty, the \a property's
    current value is set to -1.

    \sa enumNames(), enumNamesChanged()
*/
void QExtEnumPropertyManager::setEnumNames(QExtProperty *property, const QStringList &enumNames)
{
    const QExtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtEnumPropertyManagerPrivate::Data data = it.value();

    if (data.enumNames == enumNames)
        return;

    data.enumNames = enumNames;

    data.val = -1;

    if (enumNames.count() > 0)
        data.val = 0;

    it.value() = data;

    emit enumNamesChanged(property, data.enumNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's map of enum values to their icons to \a
    enumIcons.

    Each enum value can have associated icon. This association is represented with passed \a enumIcons map.

    \sa enumNames(), enumNamesChanged()
*/
void QExtEnumPropertyManager::setEnumIcons(QExtProperty *property, const QMap<int, QIcon> &enumIcons)
{
    const QExtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    it.value().enumIcons = enumIcons;

    emit enumIconsChanged(property, it.value().enumIcons);

    emit propertyChanged(property);
}

/*!
    \reimp
*/
void QExtEnumPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtEnumPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QExtEnumPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QExtFlagPropertyManager

class QExtFlagPropertyManagerPrivate
{
    QExtFlagPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtFlagPropertyManager)
public:

    void slotBoolChanged(QExtProperty *property, bool value);
    void slotPropertyDestroyed(QExtProperty *property);

    struct Data
    {
        Data() : val(-1) {}
        int val;
        QStringList flagNames;
    };

    typedef QMap<const QExtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QExtBoolPropertyManager *m_boolPropertyManager;

    QMap<const QExtProperty *, QList<QExtProperty *> > m_propertyToFlags;

    QMap<const QExtProperty *, QExtProperty *> m_flagToProperty;
};

void QExtFlagPropertyManagerPrivate::slotBoolChanged(QExtProperty *property, bool value)
{
    QExtProperty *prop = m_flagToProperty.value(property, 0);
    if (prop == 0)
        return;

    QListIterator<QExtProperty *> itProp(m_propertyToFlags[prop]);
    int level = 0;
    while (itProp.hasNext()) {
        QExtProperty *p = itProp.next();
        if (p == property) {
            int v = m_values[prop].val;
            if (value) {
                v |= (1 << level);
            } else {
                v &= ~(1 << level);
            }
            q_ptr->setValue(prop, v);
            return;
        }
        level++;
    }
}

void QExtFlagPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    QExtProperty *flagProperty = m_flagToProperty.value(property, 0);
    if (flagProperty == 0)
        return;

    m_propertyToFlags[flagProperty].replace(m_propertyToFlags[flagProperty].indexOf(property), 0);
    m_flagToProperty.remove(property);
}

/*!
    \class QExtFlagPropertyManager

    \brief The QExtFlagPropertyManager provides and manages flag properties.

    Each flag property has an associated list of flag names which can
    be retrieved using the flagNames() function, and set using the
    corresponding setFlagNames() function.

    The flag manager provides properties with nested boolean
    subproperties representing each flag, i.e. a flag property's value
    is the binary combination of the subproperties' values. A
    property's value can be retrieved and set using the value() and
    setValue() slots respectively. The combination of flags is represented
    by single int value - that's why it's possible to store up to
    32 independent flags in one flag property.

    The subproperties are created by a QExtBoolPropertyManager object. This
    manager can be retrieved using the subBoolPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QExtFlagPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the flagNamesChanged() signal which is emitted
    whenever the list of flag names is altered.

    \sa QExtAbstractPropertyManager, QExtBoolPropertyManager
*/

/*!
    \fn void QExtFlagPropertyManager::valueChanged(QExtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a  property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtFlagPropertyManager::flagNamesChanged(QExtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its flag names, passing a pointer to the \a property and the
    new \a names as parameters.

    \sa setFlagNames()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtFlagPropertyManager::QExtFlagPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtFlagPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_boolPropertyManager = new QExtBoolPropertyManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotBoolChanged(QExtProperty *, bool)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtFlagPropertyManager::~QExtFlagPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that produces the nested boolean subproperties
    representing each flag.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtBoolPropertyManager *QExtFlagPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa flagNames(), setValue()
*/
int QExtFlagPropertyManager::value(const QExtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

/*!
    Returns the given \a property's list of flag names.

    \sa value(), setFlagNames()
*/
QStringList QExtFlagPropertyManager::flagNames(const QExtProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QExtFlagPropertyManagerPrivate::Data::flagNames, property, QStringList());
}

/*!
    \reimp
*/
QString QExtFlagPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtFlagPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QExtFlagPropertyManagerPrivate::Data &data = it.value();

    QString str;
    int level = 0;
    const QChar bar = QLatin1Char('|');
    const QStringList::const_iterator fncend = data.flagNames.constEnd();
    for (QStringList::const_iterator it =  data.flagNames.constBegin(); it != fncend; ++it) {
        if (data.val & (1 << level)) {
            if (!str.isEmpty())
                str += bar;
            str += *it;
        }

        level++;
    }
    return str;
}

/*!
    \fn void QExtFlagPropertyManager::setValue(QExtProperty *property, int value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    The specified \a value must be less than the binary combination of
    the property's flagNames() list size (i.e. less than 2\sup n,
    where \c n is the size of the list) and larger than (or equal to)
    0.

    \sa value(), valueChanged()
*/
void QExtFlagPropertyManager::setValue(QExtProperty *property, int val)
{
    const QExtFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtFlagPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
        return;

    if (val > (1 << data.flagNames.count()) - 1)
        return;

    if (val < 0)
        return;

    data.val = val;

    it.value() = data;

    QListIterator<QExtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    int level = 0;
    while (itProp.hasNext()) {
        QExtProperty *prop = itProp.next();
        if (prop)
            d_ptr->m_boolPropertyManager->setValue(prop, val & (1 << level));
        level++;
    }

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of flag names to \a flagNames. The
    property's current value is reset to 0 indicating the first item
    of the list.

    \sa flagNames(), flagNamesChanged()
*/
void QExtFlagPropertyManager::setFlagNames(QExtProperty *property, const QStringList &flagNames)
{
    const QExtFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QExtFlagPropertyManagerPrivate::Data data = it.value();

    if (data.flagNames == flagNames)
        return;

    data.flagNames = flagNames;
    data.val = 0;

    it.value() = data;

    QListIterator<QExtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QExtProperty *prop = itProp.next();
        if (prop) {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags[property].clear();

    QStringListIterator itFlag(flagNames);
    while (itFlag.hasNext()) {
        const QString flagName = itFlag.next();
        QExtProperty *prop = d_ptr->m_boolPropertyManager->addProperty();
        prop->setPropertyName(flagName);
        property->addSubProperty(prop);
        d_ptr->m_propertyToFlags[property].append(prop);
        d_ptr->m_flagToProperty[prop] = property;
    }

    emit flagNamesChanged(property, data.flagNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    \reimp
*/
void QExtFlagPropertyManager::initializeProperty(QExtProperty *property)
{
    d_ptr->m_values[property] = QExtFlagPropertyManagerPrivate::Data();

    d_ptr->m_propertyToFlags[property] = QList<QExtProperty *>();
}

/*!
    \reimp
*/
void QExtFlagPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QListIterator<QExtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QExtProperty *prop = itProp.next();
        if (prop) {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtSizePolicyPropertyManager

class QExtSizePolicyPropertyManagerPrivate
{
    QExtSizePolicyPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtSizePolicyPropertyManager)
public:

    QExtSizePolicyPropertyManagerPrivate();

    void slotIntChanged(QExtProperty *property, int value);
    void slotEnumChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);

    typedef QMap<const QExtProperty *, QSizePolicy> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;
    QExtEnumPropertyManager *m_enumPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToHPolicy;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToVPolicy;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToHStretch;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToVStretch;

    QMap<const QExtProperty *, QExtProperty *> m_hPolicyToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_vPolicyToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_hStretchToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_vStretchToProperty;
};

QExtSizePolicyPropertyManagerPrivate::QExtSizePolicyPropertyManagerPrivate()
{
}

void QExtSizePolicyPropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_hStretchToProperty.value(property, 0)) {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalStretch(value);
        q_ptr->setValue(prop, sp);
    } else if (QExtProperty *prop = m_vStretchToProperty.value(property, 0)) {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalStretch(value);
        q_ptr->setValue(prop, sp);
    }
}

void QExtSizePolicyPropertyManagerPrivate::slotEnumChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_hPolicyToProperty.value(property, 0)) {
        QSizePolicy sp = m_values[prop];
        sp.setHorizontalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    } else if (QExtProperty *prop = m_vPolicyToProperty.value(property, 0)) {
        QSizePolicy sp = m_values[prop];
        sp.setVerticalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    }
}

void QExtSizePolicyPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_hStretchToProperty.value(property, 0)) {
        m_propertyToHStretch[pointProp] = 0;
        m_hStretchToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_vStretchToProperty.value(property, 0)) {
        m_propertyToVStretch[pointProp] = 0;
        m_vStretchToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_hPolicyToProperty.value(property, 0)) {
        m_propertyToHPolicy[pointProp] = 0;
        m_hPolicyToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_vPolicyToProperty.value(property, 0)) {
        m_propertyToVPolicy[pointProp] = 0;
        m_vPolicyToProperty.remove(property);
    }
}

/*!
    \class QExtSizePolicyPropertyManager

    \brief The QExtSizePolicyPropertyManager provides and manages QSizePolicy properties.

    A size policy property has nested \e horizontalPolicy, \e
    verticalPolicy, \e horizontalStretch and \e verticalStretch
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by QExtIntPropertyManager and QExtEnumPropertyManager
    objects. These managers can be retrieved using the subIntPropertyManager()
    and subEnumPropertyManager() functions respectively. In order to provide
    editing widgets for the subproperties in a property browser widget,
    these managers must be associated with editor factories.

    In addition, QExtSizePolicyPropertyManager provides the valueChanged()
    signal which is emitted whenever a property created by this
    manager changes.

    \sa QExtAbstractPropertyManager, QExtIntPropertyManager, QExtEnumPropertyManager
*/

/*!
    \fn void QExtSizePolicyPropertyManager::valueChanged(QExtProperty *property, const QSizePolicy &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtSizePolicyPropertyManager::QExtSizePolicyPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtSizePolicyPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));
    d_ptr->m_enumPropertyManager = new QExtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotEnumChanged(QExtProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtSizePolicyPropertyManager::~QExtSizePolicyPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e horizontalStretch
    and \e verticalStretch subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtSizePolicyPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the manager that creates the nested \e horizontalPolicy
    and \e verticalPolicy subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtEnumPropertyManager *QExtSizePolicyPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns the default size policy.

    \sa setValue()
*/
QSizePolicy QExtSizePolicyPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QSizePolicy());
}

/*!
    \reimp
*/
QString QExtSizePolicyPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtSizePolicyPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QSizePolicy sp = it.value();
    const QtMetaEnumProvider *mep = metaEnumProvider();
    const int hIndex = mep->sizePolicyToIndex(sp.horizontalPolicy());
    const int vIndex = mep->sizePolicyToIndex(sp.verticalPolicy());
    //! Unknown size policy on reading invalid uic3 files
    const QString hPolicy = hIndex != -1 ? mep->policyEnumNames().at(hIndex) : tr("<Invalid>");
    const QString vPolicy = vIndex != -1 ? mep->policyEnumNames().at(vIndex) : tr("<Invalid>");
    const QString str = tr("[%1, %2, %3, %4]").arg(hPolicy, vPolicy).arg(sp.horizontalStretch()).arg(sp.verticalStretch());
    return str;
}

/*!
    \fn void QExtSizePolicyPropertyManager::setValue(QExtProperty *property, const QSizePolicy &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtSizePolicyPropertyManager::setValue(QExtProperty *property, const QSizePolicy &val)
{
    const QExtSizePolicyPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToHPolicy[property],
                                           metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToVPolicy[property],
                                           metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToHStretch[property],
                                          val.horizontalStretch());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToVStretch[property],
                                          val.verticalStretch());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QExtSizePolicyPropertyManager::initializeProperty(QExtProperty *property)
{
    QSizePolicy val;
    d_ptr->m_values[property] = val;

    QExtProperty *hPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    hPolicyProp->setPropertyName(tr("Horizontal Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(hPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(hPolicyProp,
                                           metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_propertyToHPolicy[property] = hPolicyProp;
    d_ptr->m_hPolicyToProperty[hPolicyProp] = property;
    property->addSubProperty(hPolicyProp);

    QExtProperty *vPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    vPolicyProp->setPropertyName(tr("Vertical Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(vPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(vPolicyProp,
                                           metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_propertyToVPolicy[property] = vPolicyProp;
    d_ptr->m_vPolicyToProperty[vPolicyProp] = property;
    property->addSubProperty(vPolicyProp);

    QExtProperty *hStretchProp = d_ptr->m_intPropertyManager->addProperty();
    hStretchProp->setPropertyName(tr("Horizontal Stretch"));
    d_ptr->m_intPropertyManager->setValue(hStretchProp, val.horizontalStretch());
    d_ptr->m_intPropertyManager->setRange(hStretchProp, 0, 0xff);
    d_ptr->m_propertyToHStretch[property] = hStretchProp;
    d_ptr->m_hStretchToProperty[hStretchProp] = property;
    property->addSubProperty(hStretchProp);

    QExtProperty *vStretchProp = d_ptr->m_intPropertyManager->addProperty();
    vStretchProp->setPropertyName(tr("Vertical Stretch"));
    d_ptr->m_intPropertyManager->setValue(vStretchProp, val.verticalStretch());
    d_ptr->m_intPropertyManager->setRange(vStretchProp, 0, 0xff);
    d_ptr->m_propertyToVStretch[property] = vStretchProp;
    d_ptr->m_vStretchToProperty[vStretchProp] = property;
    property->addSubProperty(vStretchProp);

}

/*!
    \reimp
*/
void QExtSizePolicyPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *hPolicyProp = d_ptr->m_propertyToHPolicy[property];
    if (hPolicyProp) {
        d_ptr->m_hPolicyToProperty.remove(hPolicyProp);
        delete hPolicyProp;
    }
    d_ptr->m_propertyToHPolicy.remove(property);

    QExtProperty *vPolicyProp = d_ptr->m_propertyToVPolicy[property];
    if (vPolicyProp) {
        d_ptr->m_vPolicyToProperty.remove(vPolicyProp);
        delete vPolicyProp;
    }
    d_ptr->m_propertyToVPolicy.remove(property);

    QExtProperty *hStretchProp = d_ptr->m_propertyToHStretch[property];
    if (hStretchProp) {
        d_ptr->m_hStretchToProperty.remove(hStretchProp);
        delete hStretchProp;
    }
    d_ptr->m_propertyToHStretch.remove(property);

    QExtProperty *vStretchProp = d_ptr->m_propertyToVStretch[property];
    if (vStretchProp) {
        d_ptr->m_vStretchToProperty.remove(vStretchProp);
        delete vStretchProp;
    }
    d_ptr->m_propertyToVStretch.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtFontPropertyManager:
// QExtFontPropertyManagerPrivate has a mechanism for reacting
// to QApplication::fontDatabaseChanged() [4.5], which is emitted
// when someone loads an application font. The signals are compressed
// using a timer with interval 0, which then causes the family
// enumeration manager to re-set its strings and index values
// for each property.

Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)

class QExtFontPropertyManagerPrivate
{
    QExtFontPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtFontPropertyManager)
public:

    QExtFontPropertyManagerPrivate();

    void slotIntChanged(QExtProperty *property, int value);
    void slotEnumChanged(QExtProperty *property, int value);
    void slotBoolChanged(QExtProperty *property, bool value);
    void slotPropertyDestroyed(QExtProperty *property);
    void slotFontDatabaseChanged();
    void slotFontDatabaseDelayedChange();

    QStringList m_familyNames;

    typedef QMap<const QExtProperty *, QFont> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;
    QExtEnumPropertyManager *m_enumPropertyManager;
    QExtBoolPropertyManager *m_boolPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToFamily;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToPointSize;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToBold;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToItalic;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToUnderline;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToStrikeOut;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToKerning;

    QMap<const QExtProperty *, QExtProperty *> m_familyToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_pointSizeToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_boldToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_italicToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_underlineToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_strikeOutToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_kerningToProperty;

    bool m_settingValue;
    QTimer *m_fontDatabaseChangeTimer;
};

QExtFontPropertyManagerPrivate::QExtFontPropertyManagerPrivate() :
    m_settingValue(false),
    m_fontDatabaseChangeTimer(0)
{
}

void QExtFontPropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QExtProperty *prop = m_pointSizeToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setPointSize(value);
        q_ptr->setValue(prop, f);
    }
}

void QExtFontPropertyManagerPrivate::slotEnumChanged(QExtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QExtProperty *prop = m_familyToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setFamily(m_familyNames.at(value));
        q_ptr->setValue(prop, f);
    }
}

void QExtFontPropertyManagerPrivate::slotBoolChanged(QExtProperty *property, bool value)
{
    if (m_settingValue)
        return;
    if (QExtProperty *prop = m_boldToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setBold(value);
        q_ptr->setValue(prop, f);
    } else if (QExtProperty *prop = m_italicToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setItalic(value);
        q_ptr->setValue(prop, f);
    } else if (QExtProperty *prop = m_underlineToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setUnderline(value);
        q_ptr->setValue(prop, f);
    } else if (QExtProperty *prop = m_strikeOutToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setStrikeOut(value);
        q_ptr->setValue(prop, f);
    } else if (QExtProperty *prop = m_kerningToProperty.value(property, 0)) {
        QFont f = m_values[prop];
        f.setKerning(value);
        q_ptr->setValue(prop, f);
    }
}

void QExtFontPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_pointSizeToProperty.value(property, 0)) {
        m_propertyToPointSize[pointProp] = 0;
        m_pointSizeToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_familyToProperty.value(property, 0)) {
        m_propertyToFamily[pointProp] = 0;
        m_familyToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_boldToProperty.value(property, 0)) {
        m_propertyToBold[pointProp] = 0;
        m_boldToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_italicToProperty.value(property, 0)) {
        m_propertyToItalic[pointProp] = 0;
        m_italicToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_underlineToProperty.value(property, 0)) {
        m_propertyToUnderline[pointProp] = 0;
        m_underlineToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_strikeOutToProperty.value(property, 0)) {
        m_propertyToStrikeOut[pointProp] = 0;
        m_strikeOutToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_kerningToProperty.value(property, 0)) {
        m_propertyToKerning[pointProp] = 0;
        m_kerningToProperty.remove(property);
    }
}

void  QExtFontPropertyManagerPrivate::slotFontDatabaseChanged()
{
    if (!m_fontDatabaseChangeTimer) {
        m_fontDatabaseChangeTimer = new QTimer(q_ptr);
        m_fontDatabaseChangeTimer->setInterval(0);
        m_fontDatabaseChangeTimer->setSingleShot(true);
        QObject::connect(m_fontDatabaseChangeTimer, SIGNAL(timeout()), q_ptr, SLOT(slotFontDatabaseDelayedChange()));
    }
    if (!m_fontDatabaseChangeTimer->isActive())
        m_fontDatabaseChangeTimer->start();
}

void QExtFontPropertyManagerPrivate::slotFontDatabaseDelayedChange()
{
    typedef QMap<const QExtProperty *, QExtProperty *> PropertyPropertyMap;
    // rescan available font names
    const QStringList oldFamilies = m_familyNames;
    m_familyNames = fontDatabase()->families();

    // Adapt all existing properties
    if (!m_propertyToFamily.empty()) {
        PropertyPropertyMap::const_iterator cend = m_propertyToFamily.constEnd();
        for (PropertyPropertyMap::const_iterator it = m_propertyToFamily.constBegin(); it != cend; ++it) {
            QExtProperty *familyProp = it.value();
            const int oldIdx = m_enumPropertyManager->value(familyProp);
            int newIdx = m_familyNames.indexOf(oldFamilies.at(oldIdx));
            if (newIdx < 0)
                newIdx = 0;
            m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
            m_enumPropertyManager->setValue(familyProp, newIdx);
        }
    }
}

/*!
    \class QExtFontPropertyManager

    \brief The QExtFontPropertyManager provides and manages QFont properties.

    A font property has nested \e family, \e pointSize, \e bold, \e
    italic, \e underline, \e strikeOut and \e kerning subproperties. The top-level
    property's value can be retrieved using the value() function, and
    set using the setValue() slot.

    The subproperties are created by QExtIntPropertyManager, QExtEnumPropertyManager and
    QExtBoolPropertyManager objects. These managers can be retrieved using the
    corresponding subIntPropertyManager(), subEnumPropertyManager() and
    subBoolPropertyManager() functions. In order to provide editing widgets
    for the subproperties in a property browser widget, these managers
    must be associated with editor factories.

    In addition, QExtFontPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager, QExtEnumPropertyManager, QExtIntPropertyManager, QExtBoolPropertyManager
*/

/*!
    \fn void QExtFontPropertyManager::valueChanged(QExtProperty *property, const QFont &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtFontPropertyManager::QExtFontPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtFontPropertyManagerPrivate;
    d_ptr->q_ptr = this;
#if QT_VERSION >= 0x040500
    QObject::connect(qApp, SIGNAL(fontDatabaseChanged()), this, SLOT(slotFontDatabaseChanged()));
#endif

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));
    d_ptr->m_enumPropertyManager = new QExtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotEnumChanged(QExtProperty *, int)));
    d_ptr->m_boolPropertyManager = new QExtBoolPropertyManager(this);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotBoolChanged(QExtProperty *, bool)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtFontPropertyManager::~QExtFontPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the \e pointSize subproperty.

    In order to provide editing widgets for the \e pointSize property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtFontPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the manager that create the \e family subproperty.

    In order to provide editing widgets for the \e family property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtEnumPropertyManager *QExtFontPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the manager that creates the  \e bold, \e italic, \e underline,
    \e strikeOut and \e kerning subproperties.

    In order to provide editing widgets for the mentioned properties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtBoolPropertyManager *QExtFontPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns a font object that uses the application's default
    font.

    \sa setValue()
*/
QFont QExtFontPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QFont());
}

/*!
    \reimp
*/
QString QExtFontPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return QExtPropertyBrowserUtils::fontValueText(it.value());
}

/*!
    \reimp
*/
QIcon QExtFontPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return QExtPropertyBrowserUtils::fontValueIcon(it.value());
}

/*!
    \fn void QExtFontPropertyManager::setValue(QExtProperty *property, const QFont &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtFontPropertyManager::setValue(QExtProperty *property, const QFont &val)
{
    const QExtFontPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    const QFont oldVal = it.value();
    if (oldVal == val && oldVal.resolve() == val.resolve())
        return;

    it.value() = val;

    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    bool settingValue = d_ptr->m_settingValue;
    d_ptr->m_settingValue = true;
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToFamily[property], idx);
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToPointSize[property], val.pointSize());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToBold[property], val.bold());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToItalic[property], val.italic());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToUnderline[property], val.underline());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToStrikeOut[property], val.strikeOut());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToKerning[property], val.kerning());
    d_ptr->m_settingValue = settingValue;

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QExtFontPropertyManager::initializeProperty(QExtProperty *property)
{
    QFont val;
    d_ptr->m_values[property] = val;

    QExtProperty *familyProp = d_ptr->m_enumPropertyManager->addProperty();
    familyProp->setPropertyName(tr("Family"));
    if (d_ptr->m_familyNames.empty())
        d_ptr->m_familyNames = fontDatabase()->families();
    d_ptr->m_enumPropertyManager->setEnumNames(familyProp, d_ptr->m_familyNames);
    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    d_ptr->m_enumPropertyManager->setValue(familyProp, idx);
    d_ptr->m_propertyToFamily[property] = familyProp;
    d_ptr->m_familyToProperty[familyProp] = property;
    property->addSubProperty(familyProp);

    QExtProperty *pointSizeProp = d_ptr->m_intPropertyManager->addProperty();
    pointSizeProp->setPropertyName(tr("Point Size"));
    d_ptr->m_intPropertyManager->setValue(pointSizeProp, val.pointSize());
    d_ptr->m_intPropertyManager->setMinimum(pointSizeProp, 1);
    d_ptr->m_propertyToPointSize[property] = pointSizeProp;
    d_ptr->m_pointSizeToProperty[pointSizeProp] = property;
    property->addSubProperty(pointSizeProp);

    QExtProperty *boldProp = d_ptr->m_boolPropertyManager->addProperty();
    boldProp->setPropertyName(tr("Bold"));
    d_ptr->m_boolPropertyManager->setValue(boldProp, val.bold());
    d_ptr->m_propertyToBold[property] = boldProp;
    d_ptr->m_boldToProperty[boldProp] = property;
    property->addSubProperty(boldProp);

    QExtProperty *italicProp = d_ptr->m_boolPropertyManager->addProperty();
    italicProp->setPropertyName(tr("Italic"));
    d_ptr->m_boolPropertyManager->setValue(italicProp, val.italic());
    d_ptr->m_propertyToItalic[property] = italicProp;
    d_ptr->m_italicToProperty[italicProp] = property;
    property->addSubProperty(italicProp);

    QExtProperty *underlineProp = d_ptr->m_boolPropertyManager->addProperty();
    underlineProp->setPropertyName(tr("Underline"));
    d_ptr->m_boolPropertyManager->setValue(underlineProp, val.underline());
    d_ptr->m_propertyToUnderline[property] = underlineProp;
    d_ptr->m_underlineToProperty[underlineProp] = property;
    property->addSubProperty(underlineProp);

    QExtProperty *strikeOutProp = d_ptr->m_boolPropertyManager->addProperty();
    strikeOutProp->setPropertyName(tr("Strikeout"));
    d_ptr->m_boolPropertyManager->setValue(strikeOutProp, val.strikeOut());
    d_ptr->m_propertyToStrikeOut[property] = strikeOutProp;
    d_ptr->m_strikeOutToProperty[strikeOutProp] = property;
    property->addSubProperty(strikeOutProp);

    QExtProperty *kerningProp = d_ptr->m_boolPropertyManager->addProperty();
    kerningProp->setPropertyName(tr("Kerning"));
    d_ptr->m_boolPropertyManager->setValue(kerningProp, val.kerning());
    d_ptr->m_propertyToKerning[property] = kerningProp;
    d_ptr->m_kerningToProperty[kerningProp] = property;
    property->addSubProperty(kerningProp);
}

/*!
    \reimp
*/
void QExtFontPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *familyProp = d_ptr->m_propertyToFamily[property];
    if (familyProp) {
        d_ptr->m_familyToProperty.remove(familyProp);
        delete familyProp;
    }
    d_ptr->m_propertyToFamily.remove(property);

    QExtProperty *pointSizeProp = d_ptr->m_propertyToPointSize[property];
    if (pointSizeProp) {
        d_ptr->m_pointSizeToProperty.remove(pointSizeProp);
        delete pointSizeProp;
    }
    d_ptr->m_propertyToPointSize.remove(property);

    QExtProperty *boldProp = d_ptr->m_propertyToBold[property];
    if (boldProp) {
        d_ptr->m_boldToProperty.remove(boldProp);
        delete boldProp;
    }
    d_ptr->m_propertyToBold.remove(property);

    QExtProperty *italicProp = d_ptr->m_propertyToItalic[property];
    if (italicProp) {
        d_ptr->m_italicToProperty.remove(italicProp);
        delete italicProp;
    }
    d_ptr->m_propertyToItalic.remove(property);

    QExtProperty *underlineProp = d_ptr->m_propertyToUnderline[property];
    if (underlineProp) {
        d_ptr->m_underlineToProperty.remove(underlineProp);
        delete underlineProp;
    }
    d_ptr->m_propertyToUnderline.remove(property);

    QExtProperty *strikeOutProp = d_ptr->m_propertyToStrikeOut[property];
    if (strikeOutProp) {
        d_ptr->m_strikeOutToProperty.remove(strikeOutProp);
        delete strikeOutProp;
    }
    d_ptr->m_propertyToStrikeOut.remove(property);

    QExtProperty *kerningProp = d_ptr->m_propertyToKerning[property];
    if (kerningProp) {
        d_ptr->m_kerningToProperty.remove(kerningProp);
        delete kerningProp;
    }
    d_ptr->m_propertyToKerning.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtColorPropertyManager

class QExtColorPropertyManagerPrivate
{
    QExtColorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtColorPropertyManager)
public:

    void slotIntChanged(QExtProperty *property, int value);
    void slotPropertyDestroyed(QExtProperty *property);

    typedef QMap<const QExtProperty *, QColor> PropertyValueMap;
    PropertyValueMap m_values;

    QExtIntPropertyManager *m_intPropertyManager;

    QMap<const QExtProperty *, QExtProperty *> m_propertyToR;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToG;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToB;
    QMap<const QExtProperty *, QExtProperty *> m_propertyToA;

    QMap<const QExtProperty *, QExtProperty *> m_rToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_gToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_bToProperty;
    QMap<const QExtProperty *, QExtProperty *> m_aToProperty;
};

void QExtColorPropertyManagerPrivate::slotIntChanged(QExtProperty *property, int value)
{
    if (QExtProperty *prop = m_rToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setRed(value);
        q_ptr->setValue(prop, c);
    } else if (QExtProperty *prop = m_gToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setGreen(value);
        q_ptr->setValue(prop, c);
    } else if (QExtProperty *prop = m_bToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setBlue(value);
        q_ptr->setValue(prop, c);
    } else if (QExtProperty *prop = m_aToProperty.value(property, 0)) {
        QColor c = m_values[prop];
        c.setAlpha(value);
        q_ptr->setValue(prop, c);
    }
}

void QExtColorPropertyManagerPrivate::slotPropertyDestroyed(QExtProperty *property)
{
    if (QExtProperty *pointProp = m_rToProperty.value(property, 0)) {
        m_propertyToR[pointProp] = 0;
        m_rToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_gToProperty.value(property, 0)) {
        m_propertyToG[pointProp] = 0;
        m_gToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_bToProperty.value(property, 0)) {
        m_propertyToB[pointProp] = 0;
        m_bToProperty.remove(property);
    } else if (QExtProperty *pointProp = m_aToProperty.value(property, 0)) {
        m_propertyToA[pointProp] = 0;
        m_aToProperty.remove(property);
    }
}

/*!
    \class QExtColorPropertyManager

    \brief The QExtColorPropertyManager provides and manages QColor properties.

    A color property has nested \e red, \e green and \e blue
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QExtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function.  In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QExtColorPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QExtAbstractPropertyManager, QExtAbstractPropertyBrowser, QExtIntPropertyManager
*/

/*!
    \fn void QExtColorPropertyManager::valueChanged(QExtProperty *property, const QColor &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtColorPropertyManager::QExtColorPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtColorPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QExtIntPropertyManager(this);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotIntChanged(QExtProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QExtProperty *)),
            this, SLOT(slotPropertyDestroyed(QExtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtColorPropertyManager::~QExtColorPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that produces the nested \e red, \e green and
    \e blue subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QExtAbstractPropertyBrowser::setFactoryForManager()
*/
QExtIntPropertyManager *QExtColorPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns an invalid color.

    \sa setValue()
*/
QColor QExtColorPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QColor());
}

/*!
    \reimp
*/

QString QExtColorPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return QExtPropertyBrowserUtils::colorValueText(it.value());
}

/*!
    \reimp
*/

QIcon QExtColorPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();
    return QExtPropertyBrowserUtils::brushValueIcon(QBrush(it.value()));
}

/*!
    \fn void QExtColorPropertyManager::setValue(QExtProperty *property, const QColor &value)

    Sets the value of the given \a property to \a value.  Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QExtColorPropertyManager::setValue(QExtProperty *property, const QColor &val)
{
    const QExtColorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == val)
        return;

    it.value() = val;

    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToR[property], val.red());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToG[property], val.green());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToB[property], val.blue());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToA[property], val.alpha());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \reimp
*/
void QExtColorPropertyManager::initializeProperty(QExtProperty *property)
{
    QColor val;
    d_ptr->m_values[property] = val;

    QExtProperty *rProp = d_ptr->m_intPropertyManager->addProperty();
    rProp->setPropertyName(tr("Red"));
    d_ptr->m_intPropertyManager->setValue(rProp, val.red());
    d_ptr->m_intPropertyManager->setRange(rProp, 0, 0xFF);
    d_ptr->m_propertyToR[property] = rProp;
    d_ptr->m_rToProperty[rProp] = property;
    property->addSubProperty(rProp);

    QExtProperty *gProp = d_ptr->m_intPropertyManager->addProperty();
    gProp->setPropertyName(tr("Green"));
    d_ptr->m_intPropertyManager->setValue(gProp, val.green());
    d_ptr->m_intPropertyManager->setRange(gProp, 0, 0xFF);
    d_ptr->m_propertyToG[property] = gProp;
    d_ptr->m_gToProperty[gProp] = property;
    property->addSubProperty(gProp);

    QExtProperty *bProp = d_ptr->m_intPropertyManager->addProperty();
    bProp->setPropertyName(tr("Blue"));
    d_ptr->m_intPropertyManager->setValue(bProp, val.blue());
    d_ptr->m_intPropertyManager->setRange(bProp, 0, 0xFF);
    d_ptr->m_propertyToB[property] = bProp;
    d_ptr->m_bToProperty[bProp] = property;
    property->addSubProperty(bProp);

    QExtProperty *aProp = d_ptr->m_intPropertyManager->addProperty();
    aProp->setPropertyName(tr("Alpha"));
    d_ptr->m_intPropertyManager->setValue(aProp, val.alpha());
    d_ptr->m_intPropertyManager->setRange(aProp, 0, 0xFF);
    d_ptr->m_propertyToA[property] = aProp;
    d_ptr->m_aToProperty[aProp] = property;
    property->addSubProperty(aProp);
}

/*!
    \reimp
*/
void QExtColorPropertyManager::uninitializeProperty(QExtProperty *property)
{
    QExtProperty *rProp = d_ptr->m_propertyToR[property];
    if (rProp) {
        d_ptr->m_rToProperty.remove(rProp);
        delete rProp;
    }
    d_ptr->m_propertyToR.remove(property);

    QExtProperty *gProp = d_ptr->m_propertyToG[property];
    if (gProp) {
        d_ptr->m_gToProperty.remove(gProp);
        delete gProp;
    }
    d_ptr->m_propertyToG.remove(property);

    QExtProperty *bProp = d_ptr->m_propertyToB[property];
    if (bProp) {
        d_ptr->m_bToProperty.remove(bProp);
        delete bProp;
    }
    d_ptr->m_propertyToB.remove(property);

    QExtProperty *aProp = d_ptr->m_propertyToA[property];
    if (aProp) {
        d_ptr->m_aToProperty.remove(aProp);
        delete aProp;
    }
    d_ptr->m_propertyToA.remove(property);

    d_ptr->m_values.remove(property);
}

// QExtCursorPropertyManager

// Make sure icons are removed as soon as QApplication is destroyed, otherwise,
// handles are leaked on X11.
static void clearCursorDatabase();
namespace {
struct CursorDatabase : public QExtCursorDatabase
{
    CursorDatabase()
    {
        qAddPostRoutine(clearCursorDatabase);
    }
};
}
Q_GLOBAL_STATIC(QExtCursorDatabase, cursorDatabase)

static void clearCursorDatabase()
{
    cursorDatabase()->clear();
}

class QExtCursorPropertyManagerPrivate
{
    QExtCursorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtCursorPropertyManager)
public:
    typedef QMap<const QExtProperty *, QCursor> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QExtCursorPropertyManager

    \brief The QExtCursorPropertyManager provides and manages QCursor properties.

    A cursor property has a current value which can be
    retrieved using the value() function, and set using the setValue()
    slot. In addition, QExtCursorPropertyManager provides the
    valueChanged() signal which is emitted whenever a property created
    by this manager changes.

    \sa QExtAbstractPropertyManager
*/

/*!
    \fn void QExtCursorPropertyManager::valueChanged(QExtProperty *property, const QCursor &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtCursorPropertyManager::QExtCursorPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtCursorPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtCursorPropertyManager::~QExtCursorPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a default QCursor object.

    \sa setValue()
*/
#ifndef QT_NO_CURSOR
QCursor QExtCursorPropertyManager::value(const QExtProperty *property) const
{
    return d_ptr->m_values.value(property, QCursor());
}
#endif

/*!
    \reimp
*/
QString QExtCursorPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtCursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return cursorDatabase()->cursorToShapeName(it.value());
}

/*!
    \reimp
*/
QIcon QExtCursorPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtCursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return cursorDatabase()->cursorToShapeIcon(it.value());
}

/*!
    \fn void QExtCursorPropertyManager::setValue(QExtProperty *property, const QCursor &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QExtCursorPropertyManager::setValue(QExtProperty *property, const QCursor &value)
{
#ifndef QT_NO_CURSOR
    const QExtCursorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().shape() == value.shape() && value.shape() != Qt::BitmapCursor)
        return;

    it.value() = value;

    emit propertyChanged(property);
    emit valueChanged(property, value);
#endif
}

/*!
    \reimp
*/
void QExtCursorPropertyManager::initializeProperty(QExtProperty *property)
{
#ifndef QT_NO_CURSOR
    d_ptr->m_values[property] = QCursor();
#endif
}

/*!
    \reimp
*/
void QExtCursorPropertyManager::uninitializeProperty(QExtProperty *property)
{
    d_ptr->m_values.remove(property);
}


/***********************************************************************************************************************
** qteditorfactory
***********************************************************************************************************************/

// Set a hard coded left margin to account for the indentation
// of the tree view icon when switching to an editor

static inline void setupTreeViewEditorMargin(QLayout *lt)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        lt->setContentsMargins(DecorationMargin, 0, 0, 0);
    else
        lt->setContentsMargins(0, 0, DecorationMargin, 0);
}

// ---------- EditorFactoryPrivate :
// Base class for editor factory private classes. Manages mapping of properties to editors and vice versa.

template <class Editor>
class EditorFactoryPrivate
{
public:

    typedef QList<Editor *> EditorList;
    typedef QMap<QExtProperty *, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor *, QExtProperty *> EditorToPropertyMap;

    Editor *createEditor(QExtProperty *property, QWidget *parent);
    void initializeEditor(QExtProperty *property, Editor *e);
    void slotEditorDestroyed(QObject *object);

    PropertyToEditorListMap  m_createdEditors;
    EditorToPropertyMap m_editorToProperty;
};

template <class Editor>
Editor *EditorFactoryPrivate<Editor>::createEditor(QExtProperty *property, QWidget *parent)
{
    Editor *editor = new Editor(parent);
    initializeEditor(property, editor);
    return editor;
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeEditor(QExtProperty *property, Editor *editor)
{
    typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        it = m_createdEditors.insert(property, EditorList());
    it.value().append(editor);
    m_editorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject *object)
{
    const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
    for (typename EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            Editor *editor = itEditor.key();
            QExtProperty *property = itEditor.value();
            const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
            if (pit != m_createdEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdEditors.erase(pit);
            }
            m_editorToProperty.erase(itEditor);
            return;
        }
    }
}

// ------------ QExtSpinBoxFactory

class QExtSpinBoxFactoryPrivate : public EditorFactoryPrivate<QSpinBox>
{
    QExtSpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtSpinBoxFactory)
public:

    void slotPropertyChanged(QExtProperty *property, int value);
    void slotRangeChanged(QExtProperty *property, int min, int max);
    void slotSingleStepChanged(QExtProperty *property, int step);
    void slotReadOnlyChanged(QExtProperty *property, bool readOnly);
    void slotSetValue(int value);
};

void QExtSpinBoxFactoryPrivate::slotPropertyChanged(QExtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        if (editor->value() != value) {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void QExtSpinBoxFactoryPrivate::slotRangeChanged(QExtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtSpinBoxFactoryPrivate::slotSingleStepChanged(QExtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtSpinBoxFactoryPrivate::slotReadOnlyChanged( QExtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtSpinBoxFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QSpinBox *, QExtProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QSpinBox *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/*!
    \class QExtSpinBoxFactory

    \brief The QExtSpinBoxFactory class provides QSpinBox widgets for
    properties created by QExtIntPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtSpinBoxFactory::QExtSpinBoxFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtIntPropertyManager>(parent)
{
    d_ptr = new QExtSpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtSpinBoxFactory::~QExtSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtSpinBoxFactory::connectPropertyManager(QExtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtSpinBoxFactory::createEditor(QExtIntPropertyManager *manager, QExtProperty *property,
                                          QWidget *parent)
{
    QSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtSpinBoxFactory::disconnectPropertyManager(QExtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));
}

// QExtSliderFactory

class QExtSliderFactoryPrivate : public EditorFactoryPrivate<QSlider>
{
    QExtSliderFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtSliderFactory)
public:
    void slotPropertyChanged(QExtProperty *property, int value);
    void slotRangeChanged(QExtProperty *property, int min, int max);
    void slotSingleStepChanged(QExtProperty *property, int step);
    void slotSetValue(int value);
};

void QExtSliderFactoryPrivate::slotPropertyChanged(QExtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtSliderFactoryPrivate::slotRangeChanged(QExtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtSliderFactoryPrivate::slotSingleStepChanged(QExtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtSliderFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QSlider *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QSlider *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor ) {
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/*!
    \class QExtSliderFactory

    \brief The QExtSliderFactory class provides QSlider widgets for
    properties created by QExtIntPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtSliderFactory::QExtSliderFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtIntPropertyManager>(parent)
{
    d_ptr = new QExtSliderFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtSliderFactory::~QExtSliderFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtSliderFactory::connectPropertyManager(QExtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtSliderFactory::createEditor(QExtIntPropertyManager *manager, QExtProperty *property,
                                         QWidget *parent)
{
    QSlider *editor = new QSlider(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtSliderFactory::disconnectPropertyManager(QExtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
}

// QExtSliderFactory

class QExtScrollBarFactoryPrivate : public  EditorFactoryPrivate<QScrollBar>
{
    QExtScrollBarFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtScrollBarFactory)
public:
    void slotPropertyChanged(QExtProperty *property, int value);
    void slotRangeChanged(QExtProperty *property, int min, int max);
    void slotSingleStepChanged(QExtProperty *property, int step);
    void slotSetValue(int value);
};

void QExtScrollBarFactoryPrivate::slotPropertyChanged(QExtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtScrollBarFactoryPrivate::slotRangeChanged(QExtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtScrollBarFactoryPrivate::slotSingleStepChanged(QExtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QScrollBar *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtScrollBarFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QScrollBar *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QScrollBar *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtScrollBarFactory

    \brief The QExtScrollBarFactory class provides QScrollBar widgets for
    properties created by QExtIntPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtScrollBarFactory::QExtScrollBarFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtIntPropertyManager>(parent)
{
    d_ptr = new QExtScrollBarFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtScrollBarFactory::~QExtScrollBarFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtScrollBarFactory::connectPropertyManager(QExtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtScrollBarFactory::createEditor(QExtIntPropertyManager *manager, QExtProperty *property,
                                            QWidget *parent)
{
    QScrollBar *editor = new QScrollBar(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtScrollBarFactory::disconnectPropertyManager(QExtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
               this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtProperty *, int)),
               this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
}

// QExtCheckBoxFactory

class QExtCheckBoxFactoryPrivate : public EditorFactoryPrivate<QExtBoolEdit>
{
    QExtCheckBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtCheckBoxFactory)
public:
    void slotPropertyChanged(QExtProperty *property, bool value);
    void slotTextVisibleChanged(QExtProperty *property, bool textVisible);
    void slotSetValue(bool value);
};

void QExtCheckBoxFactoryPrivate::slotPropertyChanged(QExtProperty *property, bool value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QExtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QExtBoolEdit *editor = itEditor.next();
        editor->blockCheckBoxSignals(true);
        editor->setChecked(value);
        editor->blockCheckBoxSignals(false);
    }
}

void QExtCheckBoxFactoryPrivate::slotTextVisibleChanged(QExtProperty *property, bool textVisible)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtBoolPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QExtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QExtBoolEdit *editor = itEditor.next();
        editor->setTextVisible(textVisible);
    }
}

void QExtCheckBoxFactoryPrivate::slotSetValue(bool value)
{
    QObject *object = q_ptr->sender();

    const QMap<QExtBoolEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QExtBoolEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtBoolPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtCheckBoxFactory

    \brief The QExtCheckBoxFactory class provides QCheckBox widgets for
    properties created by QExtBoolPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtBoolPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtCheckBoxFactory::QExtCheckBoxFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtBoolPropertyManager>(parent)
{
    d_ptr = new QExtCheckBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtCheckBoxFactory::~QExtCheckBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCheckBoxFactory::connectPropertyManager(QExtBoolPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotPropertyChanged(QExtProperty *, bool)));
    connect(manager, SIGNAL(textVisibleChanged(QExtProperty *, bool)),
            this, SLOT(slotTextVisibleChanged(QExtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtCheckBoxFactory::createEditor(QExtBoolPropertyManager *manager, QExtProperty *property,
                                           QWidget *parent)
{
    QExtBoolEdit *editor = d_ptr->createEditor(property, parent);
    editor->setChecked(manager->value(property));
    editor->setTextVisible(manager->textVisible(property));

    connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetValue(bool)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCheckBoxFactory::disconnectPropertyManager(QExtBoolPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, bool)),
               this, SLOT(slotPropertyChanged(QExtProperty *, bool)));
    disconnect(manager, SIGNAL(textVisibleChanged(QExtProperty *, bool)),
               this, SLOT(slotTextVisibleChanged(QExtProperty *, bool)));
}

// QExtDoubleSpinBoxFactory

class QExtDoubleSpinBoxFactoryPrivate : public EditorFactoryPrivate<QDoubleSpinBox>
{
    QExtDoubleSpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtDoubleSpinBoxFactory)
public:

    void slotPropertyChanged(QExtProperty *property, double value);
    void slotRangeChanged(QExtProperty *property, double min, double max);
    void slotSingleStepChanged(QExtProperty *property, double step);
    void slotDecimalsChanged(QExtProperty *property, int prec);
    void slotReadOnlyChanged(QExtProperty *property, bool readOnly);
    void slotSetValue(double value);
};

void QExtDoubleSpinBoxFactoryPrivate::slotPropertyChanged(QExtProperty *property, double value)
{
    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        if (editor->value() != value) {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
}

void QExtDoubleSpinBoxFactoryPrivate::slotRangeChanged(QExtProperty *property,
                                                       double min, double max)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtDoubleSpinBoxFactoryPrivate::slotSingleStepChanged(QExtProperty *property, double step)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QExtDoubleSpinBoxFactoryPrivate::slotReadOnlyChanged( QExtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtDoubleSpinBoxFactoryPrivate::slotDecimalsChanged(QExtProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDecimals(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtDoubleSpinBoxFactoryPrivate::slotSetValue(double value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleSpinBox *, QExtProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QDoubleSpinBox *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

/*! \class QExtDoubleSpinBoxFactory

    \brief The QExtDoubleSpinBoxFactory class provides QDoubleSpinBox
    widgets for properties created by QExtDoublePropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtDoublePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtDoubleSpinBoxFactory::QExtDoubleSpinBoxFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtDoublePropertyManager>(parent)
{
    d_ptr = new QExtDoubleSpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtDoubleSpinBoxFactory::~QExtDoubleSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDoubleSpinBoxFactory::connectPropertyManager(QExtDoublePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotPropertyChanged(QExtProperty *, double)));
    connect(manager, SIGNAL(rangeChanged(QExtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtProperty *, double, double)));
    connect(manager, SIGNAL(singleStepChanged(QExtProperty *, double)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, double)));
    connect(manager, SIGNAL(decimalsChanged(QExtProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtDoubleSpinBoxFactory::createEditor(QExtDoublePropertyManager *manager,
                                                QExtProperty *property, QWidget *parent)
{
    QDoubleSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setDecimals(manager->decimals(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDoubleSpinBoxFactory::disconnectPropertyManager(QExtDoublePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, double)),
               this, SLOT(slotPropertyChanged(QExtProperty *, double)));
    disconnect(manager, SIGNAL(rangeChanged(QExtProperty *, double, double)),
               this, SLOT(slotRangeChanged(QExtProperty *, double, double)));
    disconnect(manager, SIGNAL(singleStepChanged(QExtProperty *, double)),
               this, SLOT(slotSingleStepChanged(QExtProperty *, double)));
    disconnect(manager, SIGNAL(decimalsChanged(QExtProperty *, int)),
               this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));
}

// QExtLineEditFactory

class QExtLineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit>
{
    QExtLineEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtLineEditFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QString &value);
    void slotRegExpChanged(QExtProperty *property, const QRegExp &regExp);
    void slotSetValue(const QString &value);
    void slotEchoModeChanged(QExtProperty *, int);
    void slotReadOnlyChanged(QExtProperty *, bool);
};

void QExtLineEditFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                     const QString &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QLineEdit *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        if (editor->text() != value) {
            editor->blockSignals(true);
            editor->setText(value);
            editor->blockSignals(false);
        }
    }
}

void QExtLineEditFactoryPrivate::slotRegExpChanged(QExtProperty *property,
                                                   const QRegExp &regExp)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        const QValidator *oldValidator = editor->validator();
        QValidator *newValidator = 0;
        if (regExp.isValid()) {
            newValidator = new QRegExpValidator(regExp, editor);
        }
        editor->setValidator(newValidator);
        if (oldValidator)
            delete oldValidator;
        editor->blockSignals(false);
    }
}

void QExtLineEditFactoryPrivate::slotEchoModeChanged(QExtProperty *property, int echoMode)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setEchoMode((EchoMode)echoMode);
        editor->blockSignals(false);
    }
}

void QExtLineEditFactoryPrivate::slotReadOnlyChanged( QExtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QExtLineEditFactoryPrivate::slotSetValue(const QString &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QLineEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QLineEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtStringPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}



/*!
    \class QExtLineEditFactory

    \brief The QExtLineEditFactory class provides QLineEdit widgets for
    properties created by QExtStringPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtStringPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtLineEditFactory::QExtLineEditFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtStringPropertyManager>(parent)
{
    d_ptr = new QExtLineEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtLineEditFactory::~QExtLineEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtLineEditFactory::connectPropertyManager(QExtStringPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QString &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QString &)));
    connect(manager, SIGNAL(regExpChanged(QExtProperty *, const QRegExp &)),
            this, SLOT(slotRegExpChanged(QExtProperty *, const QRegExp &)));
    connect(manager, SIGNAL(echoModeChanged(QExtProperty*, int)),
            this, SLOT(slotEchoModeChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QExtProperty*, bool)),
            this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtLineEditFactory::createEditor(QExtStringPropertyManager *manager,
                                           QExtProperty *property, QWidget *parent)
{

    QLineEdit *editor = d_ptr->createEditor(property, parent);
    editor->setEchoMode((EchoMode)manager->echoMode(property));
    editor->setReadOnly(manager->isReadOnly(property));
    QRegExp regExp = manager->regExp(property);
    if (regExp.isValid()) {
        QValidator *validator = new QRegExpValidator(regExp, editor);
        editor->setValidator(validator);
    }
    editor->setText(manager->value(property));

    connect(editor, SIGNAL(textChanged(const QString &)),
            this, SLOT(slotSetValue(const QString &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtLineEditFactory::disconnectPropertyManager(QExtStringPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QString &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QString &)));
    disconnect(manager, SIGNAL(regExpChanged(QExtProperty *, const QRegExp &)),
               this, SLOT(slotRegExpChanged(QExtProperty *, const QRegExp &)));
    disconnect(manager, SIGNAL(echoModeChanged(QExtProperty*,int)),
               this, SLOT(slotEchoModeChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QExtProperty*, bool)),
               this, SLOT(slotReadOnlyChanged(QExtProperty *, bool)));

}

// QExtDateEditFactory

class QExtDateEditFactoryPrivate : public EditorFactoryPrivate<QDateEdit>
{
    QExtDateEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtDateEditFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QDate &value);
    void slotRangeChanged(QExtProperty *property, const QDate &min, const QDate &max);
    void slotSetValue(const QDate &value);
};

void QExtDateEditFactoryPrivate::slotPropertyChanged(QExtProperty *property, const QDate &value)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDate(value);
        editor->blockSignals(false);
    }
}

void QExtDateEditFactoryPrivate::slotRangeChanged(QExtProperty *property,
                                                  const QDate &min, const QDate &max)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtDatePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateRange(min, max);
        editor->setDate(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtDateEditFactoryPrivate::slotSetValue(const QDate &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDateEdit *, QExtProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QDateEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtDatePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtDateEditFactory

    \brief The QExtDateEditFactory class provides QDateEdit widgets for
    properties created by QExtDatePropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtDatePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtDateEditFactory::QExtDateEditFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtDatePropertyManager>(parent)
{
    d_ptr = new QExtDateEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtDateEditFactory::~QExtDateEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDateEditFactory::connectPropertyManager(QExtDatePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QDate &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QDate &)));
    connect(manager, SIGNAL(rangeChanged(QExtProperty *, const QDate &, const QDate &)),
            this, SLOT(slotRangeChanged(QExtProperty *, const QDate &, const QDate &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtDateEditFactory::createEditor(QExtDatePropertyManager *manager, QExtProperty *property,
                                           QWidget *parent)
{
    QDateEdit *editor = d_ptr->createEditor(property, parent);
    editor->setCalendarPopup(true);
    editor->setDateRange(manager->minimum(property), manager->maximum(property));
    editor->setDate(manager->value(property));

    connect(editor, SIGNAL(dateChanged(const QDate &)),
            this, SLOT(slotSetValue(const QDate &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDateEditFactory::disconnectPropertyManager(QExtDatePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QDate &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QDate &)));
    disconnect(manager, SIGNAL(rangeChanged(QExtProperty *, const QDate &, const QDate &)),
               this, SLOT(slotRangeChanged(QExtProperty *, const QDate &, const QDate &)));
}

// QExtTimeEditFactory

class QExtTimeEditFactoryPrivate : public EditorFactoryPrivate<QTimeEdit>
{
    QExtTimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtTimeEditFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QTime &value);
    void slotSetValue(const QTime &value);
};

void QExtTimeEditFactoryPrivate::slotPropertyChanged(QExtProperty *property, const QTime &value)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setTime(value);
        editor->blockSignals(false);
    }
}

void QExtTimeEditFactoryPrivate::slotSetValue(const QTime &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QTimeEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QTimeEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtTimeEditFactory

    \brief The QExtTimeEditFactory class provides QTimeEdit widgets for
    properties created by QExtTimePropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtTimePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtTimeEditFactory::QExtTimeEditFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtTimePropertyManager>(parent)
{
    d_ptr = new QExtTimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtTimeEditFactory::~QExtTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtTimeEditFactory::connectPropertyManager(QExtTimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QTime &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QTime &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtTimeEditFactory::createEditor(QExtTimePropertyManager *manager, QExtProperty *property,
                                           QWidget *parent)
{
    QTimeEdit *editor = d_ptr->createEditor(property, parent);
    editor->setTime(manager->value(property));

    connect(editor, SIGNAL(timeChanged(const QTime &)),
            this, SLOT(slotSetValue(const QTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtTimeEditFactory::disconnectPropertyManager(QExtTimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QTime &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QTime &)));
}

// QExtDateTimeEditFactory

class QExtDateTimeEditFactoryPrivate : public EditorFactoryPrivate<QDateTimeEdit>
{
    QExtDateTimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtDateTimeEditFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QDateTime &value);
    void slotSetValue(const QDateTime &value);

};

void QExtDateTimeEditFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                         const QDateTime &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QDateTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateTime(value);
        editor->blockSignals(false);
    }
}

void QExtDateTimeEditFactoryPrivate::slotSetValue(const QDateTime &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QDateTimeEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QDateTimeEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtDateTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtDateTimeEditFactory

    \brief The QExtDateTimeEditFactory class provides QDateTimeEdit
    widgets for properties created by QExtDateTimePropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtDateTimePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtDateTimeEditFactory::QExtDateTimeEditFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtDateTimePropertyManager>(parent)
{
    d_ptr = new QExtDateTimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtDateTimeEditFactory::~QExtDateTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDateTimeEditFactory::connectPropertyManager(QExtDateTimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QDateTime &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QDateTime &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtDateTimeEditFactory::createEditor(QExtDateTimePropertyManager *manager,
                                               QExtProperty *property, QWidget *parent)
{
    QDateTimeEdit *editor =  d_ptr->createEditor(property, parent);
    editor->setDateTime(manager->value(property));

    connect(editor, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(slotSetValue(const QDateTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtDateTimeEditFactory::disconnectPropertyManager(QExtDateTimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QDateTime &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QDateTime &)));
}

// QExtKeySequenceEditorFactory

class QExtKeySequenceEditorFactoryPrivate : public EditorFactoryPrivate<QExtKeySequenceEdit>
{
    QExtKeySequenceEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtKeySequenceEditorFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QKeySequence &value);
    void slotSetValue(const QKeySequence &value);
};

void QExtKeySequenceEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                              const QKeySequence &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QExtKeySequenceEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QExtKeySequenceEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setKeySequence(value);
        editor->blockSignals(false);
    }
}

void QExtKeySequenceEditorFactoryPrivate::slotSetValue(const QKeySequence &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QExtKeySequenceEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QExtKeySequenceEdit *, QExtProperty *>::ConstIterator itEditor =  m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtKeySequencePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtKeySequenceEditorFactory

    \brief The QExtKeySequenceEditorFactory class provides editor
    widgets for properties created by QExtKeySequencePropertyManager objects.

    \sa QExtAbstractEditorFactory
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtKeySequenceEditorFactory::QExtKeySequenceEditorFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtKeySequencePropertyManager>(parent)
{
    d_ptr = new QExtKeySequenceEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtKeySequenceEditorFactory::~QExtKeySequenceEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtKeySequenceEditorFactory::connectPropertyManager(QExtKeySequencePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QKeySequence &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QKeySequence &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtKeySequenceEditorFactory::createEditor(QExtKeySequencePropertyManager *manager,
                                                    QExtProperty *property, QWidget *parent)
{
    QExtKeySequenceEdit *editor = d_ptr->createEditor(property, parent);
    editor->setKeySequence(manager->value(property));

    connect(editor, SIGNAL(keySequenceChanged(const QKeySequence &)),
            this, SLOT(slotSetValue(const QKeySequence &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtKeySequenceEditorFactory::disconnectPropertyManager(QExtKeySequencePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QKeySequence &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QKeySequence &)));
}

// QExtCharEdit
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
    if (o == m_lineEdit && e->type() == QEvent::ContextMenu) {
        QContextMenuEvent *c = static_cast<QContextMenuEvent *>(e);
        QMenu *menu = m_lineEdit->createStandardContextMenu();
        QList<QAction *> actions = menu->actions();
        QListIterator<QAction *> itAction(actions);
        while (itAction.hasNext()) {
            QAction *action = itAction.next();
            action->setShortcut(QKeySequence());
            QString actionString = action->text();
            const int pos = actionString.lastIndexOf(QLatin1Char('\t'));
            if (pos > 0)
                actionString = actionString.remove(pos, actionString.length() - pos);
            action->setText(actionString);
        }
        QAction *actionBefore = 0;
        if (actions.count() > 0)
            actionBefore = actions[0];
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
        return;
    setValue(QChar());
    emit valueChanged(m_value);
}

void QExtCharEdit::handleKeyEvent(QKeyEvent *e)
{
    const int key = e->key();
    switch (key) {
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
        return;

    const QChar c = text.at(0);
    if (!c.isPrint())
        return;

    if (m_value == c)
        return;

    m_value = c;
    const QString str = m_value.isNull() ? QString() : QString(m_value);
    m_lineEdit->setText(str);
    e->accept();
    emit valueChanged(m_value);
}

void QExtCharEdit::setValue(const QChar &value)
{
    if (value == m_value)
        return;

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
    handleKeyEvent(e);
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
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool QExtCharEdit::event(QEvent *e)
{
    switch(e->type()) {
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

// QExtCharEditorFactory

class QExtCharEditorFactoryPrivate : public EditorFactoryPrivate<QExtCharEdit>
{
    QExtCharEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtCharEditorFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QChar &value);
    void slotSetValue(const QChar &value);

};

void QExtCharEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                       const QChar &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QExtCharEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QExtCharEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
}

void QExtCharEditorFactoryPrivate::slotSetValue(const QChar &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QExtCharEdit *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QExtCharEdit *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtCharPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtCharEditorFactory

    \brief The QExtCharEditorFactory class provides editor
    widgets for properties created by QExtCharPropertyManager objects.

    \sa QExtAbstractEditorFactory
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtCharEditorFactory::QExtCharEditorFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtCharPropertyManager>(parent)
{
    d_ptr = new QExtCharEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtCharEditorFactory::~QExtCharEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCharEditorFactory::connectPropertyManager(QExtCharPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QChar &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QChar &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtCharEditorFactory::createEditor(QExtCharPropertyManager *manager,
                                             QExtProperty *property, QWidget *parent)
{
    QExtCharEdit *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(const QChar &)),
            this, SLOT(slotSetValue(const QChar &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCharEditorFactory::disconnectPropertyManager(QExtCharPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QChar &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QChar &)));
}

// QExtEnumEditorFactory

class QExtEnumEditorFactoryPrivate : public EditorFactoryPrivate<QComboBox>
{
    QExtEnumEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtEnumEditorFactory)
public:

    void slotPropertyChanged(QExtProperty *property, int value);
    void slotEnumNamesChanged(QExtProperty *property, const QStringList &);
    void slotEnumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &);
    void slotSetValue(int value);
};

void QExtEnumEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;

    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setCurrentIndex(value);
        editor->blockSignals(false);
    }
}

void QExtEnumEditorFactoryPrivate::slotEnumNamesChanged(QExtProperty *property,
                                                        const QStringList &enumNames)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QMap<int, QIcon> enumIcons = manager->enumIcons(property);

    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->clear();
        editor->addItems(enumNames);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtEnumEditorFactoryPrivate::slotEnumIconsChanged(QExtProperty *property,
                                                        const QMap<int, QIcon> &enumIcons)
{
    if (!m_createdEditors.contains(property))
        return;

    QExtEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    const QStringList enumNames = manager->enumNames(property);
    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QExtEnumEditorFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QComboBox *, QExtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QComboBox *, QExtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtEnumPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtEnumEditorFactory

    \brief The QExtEnumEditorFactory class provides QComboBox widgets for
    properties created by QExtEnumPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtEnumPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtEnumEditorFactory::QExtEnumEditorFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtEnumPropertyManager>(parent)
{
    d_ptr = new QExtEnumEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtEnumEditorFactory::~QExtEnumEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtEnumEditorFactory::connectPropertyManager(QExtEnumPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    connect(manager, SIGNAL(enumNamesChanged(QExtProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtProperty *, const QStringList &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtEnumEditorFactory::createEditor(QExtEnumPropertyManager *manager, QExtProperty *property,
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
        editor->setItemIcon(i, enumIcons.value(i));
    editor->setCurrentIndex(manager->value(property));

    connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtEnumEditorFactory::disconnectPropertyManager(QExtEnumPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, int)),
               this, SLOT(slotPropertyChanged(QExtProperty *, int)));
    disconnect(manager, SIGNAL(enumNamesChanged(QExtProperty *, const QStringList &)),
               this, SLOT(slotEnumNamesChanged(QExtProperty *, const QStringList &)));
}

// QExtCursorEditorFactory
Q_GLOBAL_STATIC(QExtCursorDatabase, cursorEditorFactoryDatabase)

class QExtCursorEditorFactoryPrivate
{
    QExtCursorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtCursorEditorFactory)
public:
    QExtCursorEditorFactoryPrivate();

    void slotPropertyChanged(QExtProperty *property, const QCursor &cursor);
    void slotEnumChanged(QExtProperty *property, int value);
    void slotEditorDestroyed(QObject *object);

    QExtEnumEditorFactory *m_enumEditorFactory;
    QExtEnumPropertyManager *m_enumPropertyManager;

    QMap<QExtProperty *, QExtProperty *> m_propertyToEnum;
    QMap<QExtProperty *, QExtProperty *> m_enumToProperty;
    QMap<QExtProperty *, QList<QWidget *> > m_enumToEditors;
    QMap<QWidget *, QExtProperty *> m_editorToEnum;
    bool m_updatingEnum;
};

QExtCursorEditorFactoryPrivate::QExtCursorEditorFactoryPrivate()
    : m_updatingEnum(false)
{

}

void QExtCursorEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property, const QCursor &cursor)
{
    // update enum property
    QExtProperty *enumProp = m_propertyToEnum.value(property);
    if (!enumProp)
        return;

    m_updatingEnum = true;
    m_enumPropertyManager->setValue(enumProp, cursorEditorFactoryDatabase()->cursorToValue(cursor));
    m_updatingEnum = false;
}

void QExtCursorEditorFactoryPrivate::slotEnumChanged(QExtProperty *property, int value)
{
    if (m_updatingEnum)
        return;
    // update cursor property
    QExtProperty *prop = m_enumToProperty.value(property);
    if (!prop)
        return;
    QExtCursorPropertyManager *cursorManager = q_ptr->propertyManager(prop);
    if (!cursorManager)
        return;
#ifndef QT_NO_CURSOR
    cursorManager->setValue(prop, QCursor(cursorEditorFactoryDatabase()->valueToCursor(value)));
#endif
}

void QExtCursorEditorFactoryPrivate::slotEditorDestroyed(QObject *object)
{
    // remove from m_editorToEnum map;
    // remove from m_enumToEditors map;
    // if m_enumToEditors doesn't contains more editors delete enum property;
    const  QMap<QWidget *, QExtProperty *>::ConstIterator ecend = m_editorToEnum.constEnd();
    for (QMap<QWidget *, QExtProperty *>::ConstIterator itEditor = m_editorToEnum.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QWidget *editor = itEditor.key();
            QExtProperty *enumProp = itEditor.value();
            m_editorToEnum.remove(editor);
            m_enumToEditors[enumProp].removeAll(editor);
            if (m_enumToEditors[enumProp].isEmpty()) {
                m_enumToEditors.remove(enumProp);
                QExtProperty *property = m_enumToProperty.value(enumProp);
                m_enumToProperty.remove(enumProp);
                m_propertyToEnum.remove(property);
                delete enumProp;
            }
            return;
        }
}

/*!
    \class QExtCursorEditorFactory

    \brief The QExtCursorEditorFactory class provides QComboBox widgets for
    properties created by QExtCursorPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtCursorPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtCursorEditorFactory::QExtCursorEditorFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtCursorPropertyManager>(parent)
{
    d_ptr = new QExtCursorEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_enumEditorFactory = new QExtEnumEditorFactory(this);
    d_ptr->m_enumPropertyManager = new QExtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotEnumChanged(QExtProperty *, int)));
    d_ptr->m_enumEditorFactory->addPropertyManager(d_ptr->m_enumPropertyManager);
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtCursorEditorFactory::~QExtCursorEditorFactory()
{
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCursorEditorFactory::connectPropertyManager(QExtCursorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty *, const QCursor &)),
            this, SLOT(slotPropertyChanged(QExtProperty *, const QCursor &)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtCursorEditorFactory::createEditor(QExtCursorPropertyManager *manager, QExtProperty *property,
                                               QWidget *parent)
{
    QExtProperty *enumProp = 0;
    if (d_ptr->m_propertyToEnum.contains(property)) {
        enumProp = d_ptr->m_propertyToEnum[property];
    } else {
        enumProp = d_ptr->m_enumPropertyManager->addProperty(property->propertyName());
        d_ptr->m_enumPropertyManager->setEnumNames(enumProp, cursorEditorFactoryDatabase()->cursorShapeNames());
        d_ptr->m_enumPropertyManager->setEnumIcons(enumProp, cursorEditorFactoryDatabase()->cursorShapeIcons());
#ifndef QT_NO_CURSOR
        d_ptr->m_enumPropertyManager->setValue(enumProp, cursorEditorFactoryDatabase()->cursorToValue(manager->value(property)));
#endif
        d_ptr->m_propertyToEnum[property] = enumProp;
        d_ptr->m_enumToProperty[enumProp] = property;
    }
    QExtAbstractEditorFactoryBase *af = d_ptr->m_enumEditorFactory;
    QWidget *editor = af->createEditor(enumProp, parent);
    d_ptr->m_enumToEditors[enumProp].append(editor);
    d_ptr->m_editorToEnum[editor] = enumProp;
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtCursorEditorFactory::disconnectPropertyManager(QExtCursorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty *, const QCursor &)),
               this, SLOT(slotPropertyChanged(QExtProperty *, const QCursor &)));
}

// QExtColorEditWidget
QExtColorEditWidget::QExtColorEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::brushValuePixmap(QBrush(m_color)));
    m_label->setText(QExtPropertyBrowserUtils::colorValueText(m_color));
}

void QExtColorEditWidget::setValue(const QColor &c)
{
    if (m_color != c) {
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
    if (ok && newRgba != oldRgba) {
        setValue(QColor::fromRgba(newRgba));
        emit valueChanged(m_color);
    }
}

bool QExtColorEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: { // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
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
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// QExtColorEditorFactoryPrivate

class QExtColorEditorFactoryPrivate : public EditorFactoryPrivate<QExtColorEditWidget>
{
    QExtColorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtColorEditorFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QColor &value);
    void slotSetValue(const QColor &value);
};

void QExtColorEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                        const QColor &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QListIterator<QExtColorEditWidget *> itEditor(it.value());

    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
}

void QExtColorEditorFactoryPrivate::slotSetValue(const QColor &value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtColorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtColorEditorFactory

    \brief The QExtColorEditorFactory class provides color editing  for
    properties created by QExtColorPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtColorPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtColorEditorFactory::QExtColorEditorFactory(QObject *parent) :
    QExtAbstractEditorFactory<QExtColorPropertyManager>(parent),
    d_ptr(new QExtColorEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtColorEditorFactory::~QExtColorEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtColorEditorFactory::connectPropertyManager(QExtColorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty*,QColor)),
            this, SLOT(slotPropertyChanged(QExtProperty*,QColor)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtColorEditorFactory::createEditor(QExtColorPropertyManager *manager,
                                              QExtProperty *property, QWidget *parent)
{
    QExtColorEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QColor)), this, SLOT(slotSetValue(QColor)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtColorEditorFactory::disconnectPropertyManager(QExtColorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty*,QColor)), this, SLOT(slotPropertyChanged(QExtProperty*,QColor)));
}

// QExtFontEditWidget
QExtFontEditWidget::QExtFontEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::fontValuePixmap(m_font));
    m_label->setText(QExtPropertyBrowserUtils::fontValueText(m_font));
}

void QExtFontEditWidget::setValue(const QFont &f)
{
    if (m_font != f) {
        m_font = f;
        m_pixmapLabel->setPixmap(QExtPropertyBrowserUtils::fontValuePixmap(f));
        m_label->setText(QExtPropertyBrowserUtils::fontValueText(f));
    }
}

void QExtFontEditWidget::buttonClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this, tr("Select Font"));
    if (ok && newFont != m_font) {
        QFont f = m_font;
        // prevent mask for unchanged attributes, don't change other attributes (like kerning, etc...)
        if (m_font.family() != newFont.family())
            f.setFamily(newFont.family());
        if (m_font.pointSize() != newFont.pointSize())
            f.setPointSize(newFont.pointSize());
        if (m_font.bold() != newFont.bold())
            f.setBold(newFont.bold());
        if (m_font.italic() != newFont.italic())
            f.setItalic(newFont.italic());
        if (m_font.underline() != newFont.underline())
            f.setUnderline(newFont.underline());
        if (m_font.strikeOut() != newFont.strikeOut())
            f.setStrikeOut(newFont.strikeOut());
        setValue(f);
        emit valueChanged(m_font);
    }
}

bool QExtFontEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: { // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
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
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// QExtFontEditorFactoryPrivate

class QExtFontEditorFactoryPrivate : public EditorFactoryPrivate<QExtFontEditWidget>
{
    QExtFontEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtFontEditorFactory)
public:

    void slotPropertyChanged(QExtProperty *property, const QFont &value);
    void slotSetValue(const QFont &value);
};

void QExtFontEditorFactoryPrivate::slotPropertyChanged(QExtProperty *property,
                                                       const QFont &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QListIterator<QExtFontEditWidget *> itEditor(it.value());

    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
}

void QExtFontEditorFactoryPrivate::slotSetValue(const QFont &value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QExtProperty *property = itEditor.value();
            QExtFontPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

/*!
    \class QExtFontEditorFactory

    \brief The QExtFontEditorFactory class provides font editing for
    properties created by QExtFontPropertyManager objects.

    \sa QExtAbstractEditorFactory, QExtFontPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtFontEditorFactory::QExtFontEditorFactory(QObject *parent) :
    QExtAbstractEditorFactory<QExtFontPropertyManager>(parent),
    d_ptr(new QExtFontEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtFontEditorFactory::~QExtFontEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtFontEditorFactory::connectPropertyManager(QExtFontPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QExtProperty*,QFont)),
            this, SLOT(slotPropertyChanged(QExtProperty*,QFont)));
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtFontEditorFactory::createEditor(QExtFontPropertyManager *manager,
                                             QExtProperty *property, QWidget *parent)
{
    QExtFontEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QFont)), this, SLOT(slotSetValue(QFont)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtFontEditorFactory::disconnectPropertyManager(QExtFontPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QExtProperty*,QFont)), this, SLOT(slotPropertyChanged(QExtProperty*,QFont)));
}


/***********************************************************************************************************************
** qtbuttonpropertybrowser
***********************************************************************************************************************/
class QExtButtonPropertyBrowserPrivate
{
    QExtButtonPropertyBrowser *q_ptr;
    Q_DECLARE_PUBLIC(QExtButtonPropertyBrowser)
public:

    void init(QWidget *parent);

    void propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex);
    void propertyRemoved(QExtBrowserItem *index);
    void propertyChanged(QExtBrowserItem *index);
    QWidget *createEditor(QExtProperty *property, QWidget *parent) const
    { return q_ptr->createEditor(property, parent); }

    void slotEditorDestroyed();
    void slotUpdate();
    void slotToggled(bool checked);

    struct WidgetItem
    {
        WidgetItem() : widget(0), label(0), widgetLabel(0),
            button(0), container(0), layout(0), /*line(0), */parent(0), expanded(false) { }
        QWidget *widget; // can be null
        QLabel *label; // main label with property name
        QLabel *widgetLabel; // label substitute showing the current value if there is no widget
        QToolButton *button; // expandable button for items with children
        QWidget *container; // container which is expanded when the button is clicked
        QGridLayout *layout; // layout in container
        WidgetItem *parent;
        QList<WidgetItem *> children;
        bool expanded;
    };
private:
    void updateLater();
    void updateItem(WidgetItem *item);
    void insertRow(QGridLayout *layout, int row) const;
    void removeRow(QGridLayout *layout, int row) const;
    int gridRow(WidgetItem *item) const;
    int gridSpan(WidgetItem *item) const;
    void setExpanded(WidgetItem *item, bool expanded);
    QToolButton *createButton(QWidget *panret = 0) const;

    QMap<QExtBrowserItem *, WidgetItem *> m_indexToItem;
    QMap<WidgetItem *, QExtBrowserItem *> m_itemToIndex;
    QMap<QWidget *, WidgetItem *> m_widgetToItem;
    QMap<QObject *, WidgetItem *> m_buttonToItem;
    QGridLayout *m_mainLayout;
    QList<WidgetItem *> m_children;
    QList<WidgetItem *> m_recreateQueue;
};

QToolButton *QExtButtonPropertyBrowserPrivate::createButton(QWidget *parent) const
{
    QToolButton *button = new QToolButton(parent);
    button->setCheckable(true);
    button->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    button->setArrowType(Qt::DownArrow);
    button->setIconSize(QSize(3, 16));
    /*
    QIcon icon;
    icon.addPixmap(q_ptr->style()->standardPixmap(QStyle::SP_ArrowDown), QIcon::Normal, QIcon::Off);
    icon.addPixmap(q_ptr->style()->standardPixmap(QStyle::SP_ArrowUp), QIcon::Normal, QIcon::On);
    button->setIcon(icon);
    */
    return button;
}

int QExtButtonPropertyBrowserPrivate::gridRow(WidgetItem *item) const
{
    QList<WidgetItem *> siblings;
    if (item->parent)
        siblings = item->parent->children;
    else
        siblings = m_children;

    int row = 0;
    QListIterator<WidgetItem *> it(siblings);
    while (it.hasNext()) {
        WidgetItem *sibling = it.next();
        if (sibling == item)
            return row;
        row += gridSpan(sibling);
    }
    return -1;
}

int QExtButtonPropertyBrowserPrivate::gridSpan(WidgetItem *item) const
{
    if (item->container && item->expanded)
        return 2;
    return 1;
}

void QExtButtonPropertyBrowserPrivate::init(QWidget *parent)
{
    m_mainLayout = new QGridLayout();
    parent->setLayout(m_mainLayout);
    QLayoutItem *item = new QSpacerItem(0, 0,
                                        QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(item, 0, 0);
}

void QExtButtonPropertyBrowserPrivate::slotEditorDestroyed()
{
    QWidget *editor = qobject_cast<QWidget *>(q_ptr->sender());
    if (!editor)
        return;
    if (!m_widgetToItem.contains(editor))
        return;
    m_widgetToItem[editor]->widget = 0;
    m_widgetToItem.remove(editor);
}

void QExtButtonPropertyBrowserPrivate::slotUpdate()
{
    QListIterator<WidgetItem *> itItem(m_recreateQueue);
    while (itItem.hasNext()) {
        WidgetItem *item = itItem.next();

        WidgetItem *parent = item->parent;
        QWidget *w = 0;
        QGridLayout *l = 0;
        const int oldRow = gridRow(item);
        if (parent) {
            w = parent->container;
            l = parent->layout;
        } else {
            w = q_ptr;
            l = m_mainLayout;
        }

        int span = 1;
        if (!item->widget && !item->widgetLabel)
            span = 2;
        item->label = new QLabel(w);
        item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        l->addWidget(item->label, oldRow, 0, 1, span);

        updateItem(item);
    }
    m_recreateQueue.clear();
}

void QExtButtonPropertyBrowserPrivate::setExpanded(WidgetItem *item, bool expanded)
{
    if (item->expanded == expanded)
        return;

    if (!item->container)
        return;

    item->expanded = expanded;
    const int row = gridRow(item);
    WidgetItem *parent = item->parent;
    QGridLayout *l = 0;
    if (parent)
        l = parent->layout;
    else
        l = m_mainLayout;

    if (expanded) {
        insertRow(l, row + 1);
        l->addWidget(item->container, row + 1, 0, 1, 2);
        item->container->show();
    } else {
        l->removeWidget(item->container);
        item->container->hide();
        removeRow(l, row + 1);
    }

    item->button->setChecked(expanded);
    item->button->setArrowType(expanded ? Qt::UpArrow : Qt::DownArrow);
}

void QExtButtonPropertyBrowserPrivate::slotToggled(bool checked)
{
    WidgetItem *item = m_buttonToItem.value(q_ptr->sender());
    if (!item)
        return;

    setExpanded(item, checked);

    if (checked)
        emit q_ptr->expanded(m_itemToIndex.value(item));
    else
        emit q_ptr->collapsed(m_itemToIndex.value(item));
}

void QExtButtonPropertyBrowserPrivate::updateLater()
{
    QTimer::singleShot(0, q_ptr, SLOT(slotUpdate()));
}

void QExtButtonPropertyBrowserPrivate::propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex)
{
    WidgetItem *afterItem = m_indexToItem.value(afterIndex);
    WidgetItem *parentItem = m_indexToItem.value(index->parent());

    WidgetItem *newItem = new WidgetItem();
    newItem->parent = parentItem;

    QGridLayout *layout = 0;
    QWidget *parentWidget = 0;
    int row = -1;
    if (!afterItem) {
        row = 0;
        if (parentItem)
            parentItem->children.insert(0, newItem);
        else
            m_children.insert(0, newItem);
    } else {
        row = gridRow(afterItem) + gridSpan(afterItem);
        if (parentItem)
            parentItem->children.insert(parentItem->children.indexOf(afterItem) + 1, newItem);
        else
            m_children.insert(m_children.indexOf(afterItem) + 1, newItem);
    }

    if (!parentItem) {
        layout = m_mainLayout;
        parentWidget = q_ptr;
    } else {
        if (!parentItem->container) {
            m_recreateQueue.removeAll(parentItem);
            WidgetItem *grandParent = parentItem->parent;
            QGridLayout *l = 0;
            const int oldRow = gridRow(parentItem);
            if (grandParent) {
                l = grandParent->layout;
            } else {
                l = m_mainLayout;
            }
            QFrame *container = new QFrame();
            container->setFrameShape(QFrame::Panel);
            container->setFrameShadow(QFrame::Raised);
            parentItem->container = container;
            parentItem->button = createButton();
            m_buttonToItem[parentItem->button] = parentItem;
            q_ptr->connect(parentItem->button, SIGNAL(toggled(bool)), q_ptr, SLOT(slotToggled(bool)));
            parentItem->layout = new QGridLayout();
            container->setLayout(parentItem->layout);
            if (parentItem->label) {
                l->removeWidget(parentItem->label);
                delete parentItem->label;
                parentItem->label = 0;
            }
            int span = 1;
            if (!parentItem->widget && !parentItem->widgetLabel)
                span = 2;
            l->addWidget(parentItem->button, oldRow, 0, 1, span);
            updateItem(parentItem);
        }
        layout = parentItem->layout;
        parentWidget = parentItem->container;
    }

    newItem->label = new QLabel(parentWidget);
    newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    newItem->widget = createEditor(index->property(), parentWidget);
    if (newItem->widget) {
        QObject::connect(newItem->widget, SIGNAL(destroyed()), q_ptr, SLOT(slotEditorDestroyed()));
        m_widgetToItem[newItem->widget] = newItem;
    } else if (index->property()->hasValue()) {
        newItem->widgetLabel = new QLabel(parentWidget);
        newItem->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
    }

    insertRow(layout, row);
    int span = 1;
    if (newItem->widget)
        layout->addWidget(newItem->widget, row, 1);
    else if (newItem->widgetLabel)
        layout->addWidget(newItem->widgetLabel, row, 1);
    else
        span = 2;
    layout->addWidget(newItem->label, row, 0, span, 1);

    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    updateItem(newItem);
}

void QExtButtonPropertyBrowserPrivate::propertyRemoved(QExtBrowserItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);

    WidgetItem *parentItem = item->parent;

    const int row = gridRow(item);

    if (parentItem)
        parentItem->children.removeAt(parentItem->children.indexOf(item));
    else
        m_children.removeAt(m_children.indexOf(item));

    const int colSpan = gridSpan(item);

    m_buttonToItem.remove(item->button);

    if (item->widget)
        delete item->widget;
    if (item->label)
        delete item->label;
    if (item->widgetLabel)
        delete item->widgetLabel;
    if (item->button)
        delete item->button;
    if (item->container)
        delete item->container;

    if (!parentItem) {
        removeRow(m_mainLayout, row);
        if (colSpan > 1)
            removeRow(m_mainLayout, row);
    } else if (parentItem->children.count() != 0) {
        removeRow(parentItem->layout, row);
        if (colSpan > 1)
            removeRow(parentItem->layout, row);
    } else {
        const WidgetItem *grandParent = parentItem->parent;
        QGridLayout *l = 0;
        if (grandParent) {
            l = grandParent->layout;
        } else {
            l = m_mainLayout;
        }

        const int parentRow = gridRow(parentItem);
        const int parentSpan = gridSpan(parentItem);

        l->removeWidget(parentItem->button);
        l->removeWidget(parentItem->container);
        delete parentItem->button;
        delete parentItem->container;
        parentItem->button = 0;
        parentItem->container = 0;
        parentItem->layout = 0;
        if (!m_recreateQueue.contains(parentItem))
            m_recreateQueue.append(parentItem);
        if (parentSpan > 1)
            removeRow(l, parentRow + 1);

        updateLater();
    }
    m_recreateQueue.removeAll(item);

    delete item;
}

void QExtButtonPropertyBrowserPrivate::insertRow(QGridLayout *layout, int row) const
{
    QMap<QLayoutItem *, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count()) {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r >= row) {
            itemToPos[layout->takeAt(idx)] = QRect(r + 1, c, rs, cs);
        } else {
            idx++;
        }
    }

    const QMap<QLayoutItem *, QRect>::ConstIterator icend =  itemToPos.constEnd();
    for(QMap<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

void QExtButtonPropertyBrowserPrivate::removeRow(QGridLayout *layout, int row) const
{
    QMap<QLayoutItem *, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count()) {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r > row) {
            itemToPos[layout->takeAt(idx)] = QRect(r - 1, c, rs, cs);
        } else {
            idx++;
        }
    }

    const QMap<QLayoutItem *, QRect>::ConstIterator icend =  itemToPos.constEnd();
    for(QMap<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

void QExtButtonPropertyBrowserPrivate::propertyChanged(QExtBrowserItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    updateItem(item);
}

void QExtButtonPropertyBrowserPrivate::updateItem(WidgetItem *item)
{
    QExtProperty *property = m_itemToIndex[item]->property();
    if (item->button) {
        QFont font = item->button->font();
        font.setUnderline(property->isModified());
        item->button->setFont(font);
        item->button->setText(property->propertyName());
        item->button->setToolTip(property->toolTip());
        item->button->setStatusTip(property->statusTip());
        item->button->setWhatsThis(property->whatsThis());
        item->button->setEnabled(property->isEnabled());
    }
    if (item->label) {
        QFont font = item->label->font();
        font.setUnderline(property->isModified());
        item->label->setFont(font);
        item->label->setText(property->propertyName());
        item->label->setToolTip(property->toolTip());
        item->label->setStatusTip(property->statusTip());
        item->label->setWhatsThis(property->whatsThis());
        item->label->setEnabled(property->isEnabled());
    }
    if (item->widgetLabel) {
        QFont font = item->widgetLabel->font();
        font.setUnderline(false);
        item->widgetLabel->setFont(font);
        item->widgetLabel->setText(property->valueText());
        item->widgetLabel->setToolTip(property->valueText());
        item->widgetLabel->setEnabled(property->isEnabled());
    }
    if (item->widget) {
        QFont font = item->widget->font();
        font.setUnderline(false);
        item->widget->setFont(font);
        item->widget->setEnabled(property->isEnabled());
        item->widget->setToolTip(property->valueText());
    }
}



/*!
    \class QExtButtonPropertyBrowser

    \brief The QExtButtonPropertyBrowser class provides a drop down QToolButton
    based property browser.

    A property browser is a widget that enables the user to edit a
    given set of properties. Each property is represented by a label
    specifying the property's name, and an editing widget (e.g. a line
    edit or a combobox) holding its value. A property can have zero or
    more subproperties.

    QExtButtonPropertyBrowser provides drop down button for all nested
    properties, i.e. subproperties are enclosed by a container associated with
    the drop down button. The parent property's name is displayed as button text. For example:

    \image qtbuttonpropertybrowser.png

    Use the QExtAbstractPropertyBrowser API to add, insert and remove
    properties from an instance of the QExtButtonPropertyBrowser
    class. The properties themselves are created and managed by
    implementations of the QExtAbstractPropertyManager class.

    \sa QExtTreePropertyBrowser, QExtAbstractPropertyBrowser
*/

/*!
    \fn void QExtButtonPropertyBrowser::collapsed(QExtBrowserItem *item)

    This signal is emitted when the \a item is collapsed.

    \sa expanded(), setExpanded()
*/

/*!
    \fn void QExtButtonPropertyBrowser::expanded(QExtBrowserItem *item)

    This signal is emitted when the \a item is expanded.

    \sa collapsed(), setExpanded()
*/

/*!
    Creates a property browser with the given \a parent.
*/
QExtButtonPropertyBrowser::QExtButtonPropertyBrowser(QWidget *parent)
    : QExtAbstractPropertyBrowser(parent)
{
    d_ptr = new QExtButtonPropertyBrowserPrivate;
    d_ptr->q_ptr = this;

    d_ptr->init(this);
}

/*!
    Destroys this property browser.

    Note that the properties that were inserted into this browser are
    \e not destroyed since they may still be used in other
    browsers. The properties are owned by the manager that created
    them.

    \sa QExtProperty, QExtAbstractPropertyManager
*/
QExtButtonPropertyBrowser::~QExtButtonPropertyBrowser()
{
    const QMap<QExtButtonPropertyBrowserPrivate::WidgetItem *, QExtBrowserItem *>::ConstIterator icend = d_ptr->m_itemToIndex.constEnd();
    for (QMap<QExtButtonPropertyBrowserPrivate::WidgetItem *, QExtBrowserItem *>::ConstIterator  it =  d_ptr->m_itemToIndex.constBegin(); it != icend; ++it)
        delete it.key();
    delete d_ptr;
}

/*!
    \reimp
*/
void QExtButtonPropertyBrowser::itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

/*!
    \reimp
*/
void QExtButtonPropertyBrowser::itemRemoved(QExtBrowserItem *item)
{
    d_ptr->propertyRemoved(item);
}

/*!
    \reimp
*/
void QExtButtonPropertyBrowser::itemChanged(QExtBrowserItem *item)
{
    d_ptr->propertyChanged(item);
}

/*!
    Sets the \a item to either collapse or expanded, depending on the value of \a expanded.

    \sa isExpanded(), expanded(), collapsed()
*/

void QExtButtonPropertyBrowser::setExpanded(QExtBrowserItem *item, bool expanded)
{
    QExtButtonPropertyBrowserPrivate::WidgetItem *itm = d_ptr->m_indexToItem.value(item);
    if (itm)
        d_ptr->setExpanded(itm, expanded);
}

/*!
    Returns true if the \a item is expanded; otherwise returns false.

    \sa setExpanded()
*/

bool QExtButtonPropertyBrowser::isExpanded(QExtBrowserItem *item) const
{
    QExtButtonPropertyBrowserPrivate::WidgetItem *itm = d_ptr->m_indexToItem.value(item);
    if (itm)
        return itm->expanded;
    return false;
}


/***********************************************************************************************************************
** qtgroupboxpropertybrowser
***********************************************************************************************************************/

class QExtGroupBoxPropertyBrowserPrivate
{
    QExtGroupBoxPropertyBrowser *q_ptr;
    Q_DECLARE_PUBLIC(QExtGroupBoxPropertyBrowser)
public:

    void init(QWidget *parent);

    void propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex);
    void propertyRemoved(QExtBrowserItem *index);
    void propertyChanged(QExtBrowserItem *index);
    QWidget *createEditor(QExtProperty *property, QWidget *parent) const
    { return q_ptr->createEditor(property, parent); }

    void slotEditorDestroyed();
    void slotUpdate();

    struct WidgetItem
    {
        WidgetItem() : widget(0), label(0), widgetLabel(0),
            groupBox(0), layout(0), line(0), parent(0) { }
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

    QMap<QExtBrowserItem *, WidgetItem *> m_indexToItem;
    QMap<WidgetItem *, QExtBrowserItem *> m_itemToIndex;
    QMap<QWidget *, WidgetItem *> m_widgetToItem;
    QGridLayout *m_mainLayout;
    QList<WidgetItem *> m_children;
    QList<WidgetItem *> m_recreateQueue;
};

void QExtGroupBoxPropertyBrowserPrivate::init(QWidget *parent)
{
    m_mainLayout = new QGridLayout();
    parent->setLayout(m_mainLayout);
    QLayoutItem *item = new QSpacerItem(0, 0,
                                        QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(item, 0, 0);
}

void QExtGroupBoxPropertyBrowserPrivate::slotEditorDestroyed()
{
    QWidget *editor = qobject_cast<QWidget *>(q_ptr->sender());
    if (!editor)
        return;
    if (!m_widgetToItem.contains(editor))
        return;
    m_widgetToItem[editor]->widget = 0;
    m_widgetToItem.remove(editor);
}

void QExtGroupBoxPropertyBrowserPrivate::slotUpdate()
{
    QListIterator<WidgetItem *> itItem(m_recreateQueue);
    while (itItem.hasNext()) {
        WidgetItem *item = itItem.next();

        WidgetItem *par = item->parent;
        QWidget *w = 0;
        QGridLayout *l = 0;
        int oldRow = -1;
        if (!par) {
            w = q_ptr;
            l = m_mainLayout;
            oldRow = m_children.indexOf(item);
        } else {
            w = par->groupBox;
            l = par->layout;
            oldRow = par->children.indexOf(item);
            if (hasHeader(par))
                oldRow += 2;
        }

        if (item->widget) {
            item->widget->setParent(w);
        } else if (item->widgetLabel) {
            item->widgetLabel->setParent(w);
        } else {
            item->widgetLabel = new QLabel(w);
            item->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
            item->widgetLabel->setTextFormat(Qt::PlainText);
        }
        int span = 1;
        if (item->widget)
            l->addWidget(item->widget, oldRow, 1, 1, 1);
        else if (item->widgetLabel)
            l->addWidget(item->widgetLabel, oldRow, 1, 1, 1);
        else
            span = 2;
        item->label = new QLabel(w);
        item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        l->addWidget(item->label, oldRow, 0, 1, span);

        updateItem(item);
    }
    m_recreateQueue.clear();
}

void QExtGroupBoxPropertyBrowserPrivate::updateLater()
{
    QTimer::singleShot(0, q_ptr, SLOT(slotUpdate()));
}

void QExtGroupBoxPropertyBrowserPrivate::propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex)
{
    WidgetItem *afterItem = m_indexToItem.value(afterIndex);
    WidgetItem *parentItem = m_indexToItem.value(index->parent());

    WidgetItem *newItem = new WidgetItem();
    newItem->parent = parentItem;

    QGridLayout *layout = 0;
    QWidget *parentWidget = 0;
    int row = -1;
    if (!afterItem) {
        row = 0;
        if (parentItem)
            parentItem->children.insert(0, newItem);
        else
            m_children.insert(0, newItem);
    } else {
        if (parentItem) {
            row = parentItem->children.indexOf(afterItem) + 1;
            parentItem->children.insert(row, newItem);
        } else {
            row = m_children.indexOf(afterItem) + 1;
            m_children.insert(row, newItem);
        }
    }
    if (parentItem && hasHeader(parentItem))
        row += 2;

    if (!parentItem) {
        layout = m_mainLayout;
        parentWidget = q_ptr;;
    } else {
        if (!parentItem->groupBox) {
            m_recreateQueue.removeAll(parentItem);
            WidgetItem *par = parentItem->parent;
            QWidget *w = 0;
            QGridLayout *l = 0;
            int oldRow = -1;
            if (!par) {
                w = q_ptr;
                l = m_mainLayout;
                oldRow = m_children.indexOf(parentItem);
            } else {
                w = par->groupBox;
                l = par->layout;
                oldRow = par->children.indexOf(parentItem);
                if (hasHeader(par))
                    oldRow += 2;
            }
            parentItem->groupBox = new QGroupBox(w);
            parentItem->layout = new QGridLayout();
            parentItem->groupBox->setLayout(parentItem->layout);
            if (parentItem->label) {
                l->removeWidget(parentItem->label);
                delete parentItem->label;
                parentItem->label = 0;
            }
            if (parentItem->widget) {
                l->removeWidget(parentItem->widget);
                parentItem->widget->setParent(parentItem->groupBox);
                parentItem->layout->addWidget(parentItem->widget, 0, 0, 1, 2);
                parentItem->line = new QFrame(parentItem->groupBox);
            } else if (parentItem->widgetLabel) {
                l->removeWidget(parentItem->widgetLabel);
                delete parentItem->widgetLabel;
                parentItem->widgetLabel = 0;
            }
            if (parentItem->line) {
                parentItem->line->setFrameShape(QFrame::HLine);
                parentItem->line->setFrameShadow(QFrame::Sunken);
                parentItem->layout->addWidget(parentItem->line, 1, 0, 1, 2);
            }
            l->addWidget(parentItem->groupBox, oldRow, 0, 1, 2);
            updateItem(parentItem);
        }
        layout = parentItem->layout;
        parentWidget = parentItem->groupBox;
    }

    newItem->label = new QLabel(parentWidget);
    newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    newItem->widget = createEditor(index->property(), parentWidget);
    if (!newItem->widget) {
        newItem->widgetLabel = new QLabel(parentWidget);
        newItem->widgetLabel->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
        newItem->widgetLabel->setTextFormat(Qt::PlainText);
    } else {
        QObject::connect(newItem->widget, SIGNAL(destroyed()), q_ptr, SLOT(slotEditorDestroyed()));
        m_widgetToItem[newItem->widget] = newItem;
    }

    insertRow(layout, row);
    int span = 1;
    if (newItem->widget)
        layout->addWidget(newItem->widget, row, 1);
    else if (newItem->widgetLabel)
        layout->addWidget(newItem->widgetLabel, row, 1);
    else
        span = 2;
    layout->addWidget(newItem->label, row, 0, 1, span);

    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    updateItem(newItem);
}

void QExtGroupBoxPropertyBrowserPrivate::propertyRemoved(QExtBrowserItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);

    WidgetItem *parentItem = item->parent;

    int row = -1;

    if (parentItem) {
        row = parentItem->children.indexOf(item);
        parentItem->children.removeAt(row);
        if (hasHeader(parentItem))
            row += 2;
    } else {
        row = m_children.indexOf(item);
        m_children.removeAt(row);
    }

    if (item->widget)
        delete item->widget;
    if (item->label)
        delete item->label;
    if (item->widgetLabel)
        delete item->widgetLabel;
    if (item->groupBox)
        delete item->groupBox;

    if (!parentItem) {
        removeRow(m_mainLayout, row);
    } else if (parentItem->children.count() != 0) {
        removeRow(parentItem->layout, row);
    } else {
        WidgetItem *par = parentItem->parent;
        QGridLayout *l = 0;
        int oldRow = -1;
        if (!par) {
            l = m_mainLayout;
            oldRow = m_children.indexOf(parentItem);
        } else {
            l = par->layout;
            oldRow = par->children.indexOf(parentItem);
            if (hasHeader(par))
                oldRow += 2;
        }

        if (parentItem->widget) {
            parentItem->widget->hide();
            parentItem->widget->setParent(0);
        } else if (parentItem->widgetLabel) {
            parentItem->widgetLabel->hide();
            parentItem->widgetLabel->setParent(0);
        } else {
            //parentItem->widgetLabel = new QLabel(w);
        }
        l->removeWidget(parentItem->groupBox);
        delete parentItem->groupBox;
        parentItem->groupBox = 0;
        parentItem->line = 0;
        parentItem->layout = 0;
        if (!m_recreateQueue.contains(parentItem))
            m_recreateQueue.append(parentItem);
        updateLater();
    }
    m_recreateQueue.removeAll(item);

    delete item;
}

void QExtGroupBoxPropertyBrowserPrivate::insertRow(QGridLayout *layout, int row) const
{
    QMap<QLayoutItem *, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count()) {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r >= row) {
            itemToPos[layout->takeAt(idx)] = QRect(r + 1, c, rs, cs);
        } else {
            idx++;
        }
    }

    const QMap<QLayoutItem *, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QMap<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

void QExtGroupBoxPropertyBrowserPrivate::removeRow(QGridLayout *layout, int row) const
{
    QMap<QLayoutItem *, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count()) {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r > row) {
            itemToPos[layout->takeAt(idx)] = QRect(r - 1, c, rs, cs);
        } else {
            idx++;
        }
    }

    const QMap<QLayoutItem *, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QMap<QLayoutItem *, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it) {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

bool QExtGroupBoxPropertyBrowserPrivate::hasHeader(WidgetItem *item) const
{
    if (item->widget)
        return true;
    return false;
}

void QExtGroupBoxPropertyBrowserPrivate::propertyChanged(QExtBrowserItem *index)
{
    WidgetItem *item = m_indexToItem.value(index);

    updateItem(item);
}

void QExtGroupBoxPropertyBrowserPrivate::updateItem(WidgetItem *item)
{
    QExtProperty *property = m_itemToIndex[item]->property();
    if (item->groupBox) {
        QFont font = item->groupBox->font();
        font.setUnderline(property->isModified());
        item->groupBox->setFont(font);
        item->groupBox->setTitle(property->propertyName());
        item->groupBox->setToolTip(property->toolTip());
        item->groupBox->setStatusTip(property->statusTip());
        item->groupBox->setWhatsThis(property->whatsThis());
        item->groupBox->setEnabled(property->isEnabled());
    }
    if (item->label) {
        QFont font = item->label->font();
        font.setUnderline(property->isModified());
        item->label->setFont(font);
        item->label->setText(property->propertyName());
        item->label->setToolTip(property->toolTip());
        item->label->setStatusTip(property->statusTip());
        item->label->setWhatsThis(property->whatsThis());
        item->label->setEnabled(property->isEnabled());
    }
    if (item->widgetLabel) {
        QFont font = item->widgetLabel->font();
        font.setUnderline(false);
        item->widgetLabel->setFont(font);
        item->widgetLabel->setText(property->valueText());
        item->widgetLabel->setToolTip(property->valueText());
        item->widgetLabel->setEnabled(property->isEnabled());
    }
    if (item->widget) {
        QFont font = item->widget->font();
        font.setUnderline(false);
        item->widget->setFont(font);
        item->widget->setEnabled(property->isEnabled());
        item->widget->setToolTip(property->valueText());
    }
    //item->setIcon(1, property->valueIcon());
}



/*!
    \class QExtGroupBoxPropertyBrowser

    \brief The QExtGroupBoxPropertyBrowser class provides a QGroupBox
    based property browser.

    A property browser is a widget that enables the user to edit a
    given set of properties. Each property is represented by a label
    specifying the property's name, and an editing widget (e.g. a line
    edit or a combobox) holding its value. A property can have zero or
    more subproperties.

    QExtGroupBoxPropertyBrowser provides group boxes for all nested
    properties, i.e. subproperties are enclosed by a group box with
    the parent property's name as its title. For example:

    \image qtgroupboxpropertybrowser.png

    Use the QExtAbstractPropertyBrowser API to add, insert and remove
    properties from an instance of the QExtGroupBoxPropertyBrowser
    class. The properties themselves are created and managed by
    implementations of the QExtAbstractPropertyManager class.

    \sa QExtTreePropertyBrowser, QExtAbstractPropertyBrowser
*/

/*!
    Creates a property browser with the given \a parent.
*/
QExtGroupBoxPropertyBrowser::QExtGroupBoxPropertyBrowser(QWidget *parent)
    : QExtAbstractPropertyBrowser(parent)
{
    d_ptr = new QExtGroupBoxPropertyBrowserPrivate;
    d_ptr->q_ptr = this;

    d_ptr->init(this);
}

/*!
    Destroys this property browser.

    Note that the properties that were inserted into this browser are
    \e not destroyed since they may still be used in other
    browsers. The properties are owned by the manager that created
    them.

    \sa QExtProperty, QExtAbstractPropertyManager
*/
QExtGroupBoxPropertyBrowser::~QExtGroupBoxPropertyBrowser()
{
    const QMap<QExtGroupBoxPropertyBrowserPrivate::WidgetItem *, QExtBrowserItem *>::ConstIterator icend = d_ptr->m_itemToIndex.constEnd();
    for (QMap<QExtGroupBoxPropertyBrowserPrivate::WidgetItem *, QExtBrowserItem *>::ConstIterator it = d_ptr->m_itemToIndex.constBegin(); it != icend; ++it)
        delete it.key();
    delete d_ptr;
}

/*!
    \reimp
*/
void QExtGroupBoxPropertyBrowser::itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

/*!
    \reimp
*/
void QExtGroupBoxPropertyBrowser::itemRemoved(QExtBrowserItem *item)
{
    d_ptr->propertyRemoved(item);
}

/*!
    \reimp
*/
void QExtGroupBoxPropertyBrowser::itemChanged(QExtBrowserItem *item)
{
    d_ptr->propertyChanged(item);
}


/***********************************************************************************************************************
** qttreepropertybrowser
***********************************************************************************************************************/
class QExtPropertyEditorView;
class QExtTreePropertyBrowserPrivate
{
    QExtTreePropertyBrowser *q_ptr;
    Q_DECLARE_PUBLIC(QExtTreePropertyBrowser)

public:
    QExtTreePropertyBrowserPrivate();
    void init(QWidget *parent);

    void propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex);
    void propertyRemoved(QExtBrowserItem *index);
    void propertyChanged(QExtBrowserItem *index);
    QWidget *createEditor(QExtProperty *property, QWidget *parent) const
    { return q_ptr->createEditor(property, parent); }
    QExtProperty *indexToProperty(const QModelIndex &index) const;
    QTreeWidgetItem *indexToItem(const QModelIndex &index) const;
    QExtBrowserItem *indexToBrowserItem(const QModelIndex &index) const;
    bool lastColumn(int column) const;
    void disableItem(QTreeWidgetItem *item) const;
    void enableItem(QTreeWidgetItem *item) const;
    bool hasValue(QTreeWidgetItem *item) const;

    void slotCollapsed(const QModelIndex &index);
    void slotExpanded(const QModelIndex &index);

    QColor calculatedBackgroundColor(QExtBrowserItem *item) const;

    QExtPropertyEditorView *treeWidget() const { return m_treeWidget; }
    bool markPropertiesWithoutValue() const { return m_markPropertiesWithoutValue; }

    QExtBrowserItem *currentItem() const;
    void setCurrentItem(QExtBrowserItem *browserItem, bool block);
    void editItem(QExtBrowserItem *browserItem);

    void slotCurrentBrowserItemChanged(QExtBrowserItem *item);
    void slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *);

    QTreeWidgetItem *editedItem() const;

private:
    void updateItem(QTreeWidgetItem *item);

    QMap<QExtBrowserItem *, QTreeWidgetItem *> m_indexToItem;
    QMap<QTreeWidgetItem *, QExtBrowserItem *> m_itemToIndex;

    QMap<QExtBrowserItem *, QColor> m_indexToBackgroundColor;

    QExtPropertyEditorView *m_treeWidget;

    bool m_headerVisible;
    QExtTreePropertyBrowser::ResizeMode m_resizeMode;
    class QExtPropertyEditorDelegate *m_delegate;
    bool m_markPropertiesWithoutValue;
    bool m_browserChangedBlocked;
    QIcon m_expandIcon;
};

// ------------ QExtPropertyEditorView
QExtPropertyEditorView::QExtPropertyEditorView(QWidget *parent) :
    QTreeWidget(parent),
    m_editorPrivate(0)
{
    connect(header(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(resizeColumnToContents(int)));
}

void QExtPropertyEditorView::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV3 opt = option;
    bool hasValue = true;
    if (m_editorPrivate) {
        QExtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        const QColor c = option.palette.color(QPalette::Dark);
        painter->fillRect(option.rect, c);
        opt.palette.setColor(QPalette::AlternateBase, c);
    } else {
        const QColor c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid()) {
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

void QExtPropertyEditorView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Space: // Trigger Edit
        if (!m_editorPrivate->editedItem())
            if (const QTreeWidgetItem *item = currentItem())
                if (item->columnCount() >= 2 && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
                    event->accept();
                    // If the current position is at column 0, move to 1.
                    QModelIndex index = currentIndex();
                    if (index.column() == 0) {
                        index = index.sibling(index.row(), 1);
                        setCurrentIndex(index);
                    }
                    edit(index);
                    return;
                }
        break;
    default:
        break;
    }
    QTreeWidget::keyPressEvent(event);
}

void QExtPropertyEditorView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    QTreeWidgetItem *item = itemAt(event->pos());

    if (item) {
        if ((item != m_editorPrivate->editedItem()) && (event->button() == Qt::LeftButton)
                && (header()->logicalIndexAt(event->pos().x()) == 1)
                && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
            editItem(item, 1);
        } else if (!m_editorPrivate->hasValue(item) && m_editorPrivate->markPropertiesWithoutValue() && !rootIsDecorated()) {
            if (event->pos().x() + header()->offset() < 20)
                item->setExpanded(!item->isExpanded());
        }
    }
}

// ------------ QExtPropertyEditorDelegate
int QExtPropertyEditorDelegate::indentation(const QModelIndex &index) const
{
    if (!m_editorPrivate)
        return 0;

    QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
    int indent = 0;
    while (item->parent()) {
        item = item->parent();
        ++indent;
    }
    if (m_editorPrivate->treeWidget()->rootIsDecorated())
        ++indent;
    return indent * m_editorPrivate->treeWidget()->indentation();
}

void QExtPropertyEditorDelegate::slotEditorDestroyed(QObject *object)
{
    if (QWidget *w = qobject_cast<QWidget *>(object)) {
        const EditorToPropertyMap::iterator it = m_editorToProperty.find(w);
        if (it != m_editorToProperty.end()) {
            m_propertyToEditor.remove(it.value());
            m_editorToProperty.erase(it);
        }
        if (m_editedWidget == w)
        {
            m_editedWidget = 0;
            m_editedItem = 0;
        }
    }
}

void QExtPropertyEditorDelegate::closeEditor(QExtProperty *property)
{
    if (QWidget *w = m_propertyToEditor.value(property, 0))
        w->deleteLater();
}

QWidget *QExtPropertyEditorDelegate::createEditor(QWidget *parent,
                                                  const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if (index.column() == 1 && m_editorPrivate) {
        QExtProperty *property = m_editorPrivate->indexToProperty(index);
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (property && item && (item->flags() & Qt::ItemIsEnabled)) {
            QWidget *editor = m_editorPrivate->createEditor(property, parent);
            if (editor) {
                editor->setAutoFillBackground(true);
                editor->installEventFilter(const_cast<QExtPropertyEditorDelegate *>(this));
                connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
                m_propertyToEditor[property] = editor;
                m_editorToProperty[editor] = property;
                m_editedItem = item;
                m_editedWidget = editor;
            }
            return editor;
        }
    }
    return 0;
}

void QExtPropertyEditorDelegate::updateEditorGeometry(QWidget *editor,
                                                      const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));
}

void QExtPropertyEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    bool hasValue = true;
    if (m_editorPrivate) {
        QExtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    QStyleOptionViewItemV3 opt = option;
    if ((m_editorPrivate && index.column() == 0) || !hasValue) {
        QExtProperty *property = m_editorPrivate->indexToProperty(index);
        if (property && property->isModified()) {
            opt.font.setBold(true);
            opt.fontMetrics = QFontMetrics(opt.font);
        }
    }
    QColor c;
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        c = opt.palette.color(QPalette::Dark);
        opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
    } else {
        c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid() && (opt.features & QStyleOptionViewItemV2::Alternate))
            c = c.lighter(112);
    }
    if (c.isValid())
        painter->fillRect(option.rect, c);
    opt.state &= ~QStyle::State_HasFocus;
    if (index.column() == 1) {
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (m_editedItem && m_editedItem == item)
            m_disablePainting = true;
    }
    QItemDelegate::paint(painter, opt, index);
    if (option.type)
        m_disablePainting = false;

    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    if (!m_editorPrivate || (!m_editorPrivate->lastColumn(index.column()) && hasValue)) {
        int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }
    painter->restore();
}

void QExtPropertyEditorDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                                const QRect &rect, const QPixmap &pixmap) const
{
    if (m_disablePainting)
        return;

    QItemDelegate::drawDecoration(painter, option, rect, pixmap);
}

void QExtPropertyEditorDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                                             const QRect &rect, const QString &text) const
{
    if (m_disablePainting)
        return;

    QItemDelegate::drawDisplay(painter, option, rect, text);
}

QSize QExtPropertyEditorDelegate::sizeHint(const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(3, 4);
}

bool QExtPropertyEditorDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusOut) {
        QFocusEvent *fe = static_cast<QFocusEvent *>(event);
        if (fe->reason() == Qt::ActiveWindowFocusReason)
            return false;
    }
    return QItemDelegate::eventFilter(object, event);
}

//  -------- QExtTreePropertyBrowserPrivate implementation
QExtTreePropertyBrowserPrivate::QExtTreePropertyBrowserPrivate() :
    m_treeWidget(0),
    m_headerVisible(true),
    m_resizeMode(QExtTreePropertyBrowser::Stretch),
    m_delegate(0),
    m_markPropertiesWithoutValue(false),
    m_browserChangedBlocked(false)
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

void QExtTreePropertyBrowserPrivate::init(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setMargin(0);
    m_treeWidget = new QExtPropertyEditorView(parent);
    m_treeWidget->setEditorPrivate(this);
    m_treeWidget->setIconSize(QSize(18, 18));
    layout->addWidget(m_treeWidget);
    parent->setFocusProxy(m_treeWidget);

    m_treeWidget->setColumnCount(2);
    QStringList labels;
    labels.append(QCoreApplication::translate("QExtTreePropertyBrowser", "Property"));
    labels.append(QCoreApplication::translate("QExtTreePropertyBrowser", "Value"));
    m_treeWidget->setHeaderLabels(labels);
    m_treeWidget->setAlternatingRowColors(true);
    m_treeWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);
    m_delegate = new QExtPropertyEditorDelegate(parent);
    m_delegate->setEditorPrivate(this);
    m_treeWidget->setItemDelegate(m_delegate);
#if QT_DEPRECATED_SINCE(5, 0)
    m_treeWidget->header()->setMovable(false);
    m_treeWidget->header()->setResizeMode(QHeaderView::Stretch);
#endif

    m_expandIcon = drawIndicatorIcon(q_ptr->palette(), q_ptr->style());

    QObject::connect(m_treeWidget, SIGNAL(collapsed(const QModelIndex &)), q_ptr, SLOT(slotCollapsed(const QModelIndex &)));
    QObject::connect(m_treeWidget, SIGNAL(expanded(const QModelIndex &)), q_ptr, SLOT(slotExpanded(const QModelIndex &)));
    QObject::connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), q_ptr, SLOT(slotCurrentTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

QExtBrowserItem *QExtTreePropertyBrowserPrivate::currentItem() const
{
    if (QTreeWidgetItem *treeItem = m_treeWidget->currentItem())
        return m_itemToIndex.value(treeItem);
    return 0;
}

void QExtTreePropertyBrowserPrivate::setCurrentItem(QExtBrowserItem *browserItem, bool block)
{
    const bool blocked = block ? m_treeWidget->blockSignals(true) : false;
    if (browserItem == 0)
        m_treeWidget->setCurrentItem(0);
    else
        m_treeWidget->setCurrentItem(m_indexToItem.value(browserItem));
    if (block)
        m_treeWidget->blockSignals(blocked);
}

QExtProperty *QExtTreePropertyBrowserPrivate::indexToProperty(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    QExtBrowserItem *idx = m_itemToIndex.value(item);
    if (idx)
        return idx->property();
    return 0;
}

QExtBrowserItem *QExtTreePropertyBrowserPrivate::indexToBrowserItem(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    return m_itemToIndex.value(item);
}

QTreeWidgetItem *QExtTreePropertyBrowserPrivate::indexToItem(const QModelIndex &index) const
{
    return m_treeWidget->indexToItem(index);
}

bool QExtTreePropertyBrowserPrivate::lastColumn(int column) const
{
    return m_treeWidget->header()->visualIndex(column) == m_treeWidget->columnCount() - 1;
}

void QExtTreePropertyBrowserPrivate::disableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    if (flags & Qt::ItemIsEnabled) {
        flags &= ~Qt::ItemIsEnabled;
        item->setFlags(flags);
        m_delegate->closeEditor(m_itemToIndex[item]->property());
        const int childCount = item->childCount();
        for (int i = 0; i < childCount; i++) {
            QTreeWidgetItem *child = item->child(i);
            disableItem(child);
        }
    }
}

void QExtTreePropertyBrowserPrivate::enableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    flags |= Qt::ItemIsEnabled;
    item->setFlags(flags);
    const int childCount = item->childCount();
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem *child = item->child(i);
        QExtProperty *property = m_itemToIndex[child]->property();
        if (property->isEnabled()) {
            enableItem(child);
        }
    }
}

bool QExtTreePropertyBrowserPrivate::hasValue(QTreeWidgetItem *item) const
{
    QExtBrowserItem *browserItem = m_itemToIndex.value(item);
    if (browserItem)
        return browserItem->property()->hasValue();
    return false;
}

void QExtTreePropertyBrowserPrivate::propertyInserted(QExtBrowserItem *index, QExtBrowserItem *afterIndex)
{
    QTreeWidgetItem *afterItem = m_indexToItem.value(afterIndex);
    QTreeWidgetItem *parentItem = m_indexToItem.value(index->parent());

    QTreeWidgetItem *newItem = 0;
    if (parentItem) {
        newItem = new QTreeWidgetItem(parentItem, afterItem);
    } else {
        newItem = new QTreeWidgetItem(m_treeWidget, afterItem);
    }
    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    m_treeWidget->setItemExpanded(newItem, true);

    updateItem(newItem);
}

void QExtTreePropertyBrowserPrivate::propertyRemoved(QExtBrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    if (m_treeWidget->currentItem() == item) {
        m_treeWidget->setCurrentItem(0);
    }

    delete item;

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);
    m_indexToBackgroundColor.remove(index);
}

void QExtTreePropertyBrowserPrivate::propertyChanged(QExtBrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    updateItem(item);
}

void QExtTreePropertyBrowserPrivate::updateItem(QTreeWidgetItem *item)
{
    QExtProperty *property = m_itemToIndex[item]->property();
    QIcon expandIcon;
    if (property->hasValue()) {
        QString toolTip = property->toolTip();
        if (toolTip.isEmpty())
            toolTip = property->displayText();
        item->setToolTip(1, toolTip);
        item->setIcon(1, property->valueIcon());
        property->displayText().isEmpty() ? item->setText(1, property->valueText()) : item->setText(1, property->displayText());
    } else if (markPropertiesWithoutValue() && !m_treeWidget->rootIsDecorated()) {
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
    if (property->isEnabled()) {
        QTreeWidgetItem *parent = item->parent();
        if (!parent || (parent->flags() & Qt::ItemIsEnabled))
            isEnabled = true;
        else
            isEnabled = false;
    } else {
        isEnabled = false;
    }
    if (wasEnabled != isEnabled) {
        if (isEnabled)
            enableItem(item);
        else
            disableItem(item);
    }
    m_treeWidget->viewport()->update();
}

QColor QExtTreePropertyBrowserPrivate::calculatedBackgroundColor(QExtBrowserItem *item) const
{
    QExtBrowserItem *i = item;
    const QMap<QExtBrowserItem *, QColor>::const_iterator itEnd = m_indexToBackgroundColor.constEnd();
    while (i) {
        QMap<QExtBrowserItem *, QColor>::const_iterator it = m_indexToBackgroundColor.constFind(i);
        if (it != itEnd)
            return it.value();
        i = i->parent();
    }
    return QColor();
}

void QExtTreePropertyBrowserPrivate::slotCollapsed(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QExtBrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit q_ptr->collapsed(idx);
}

void QExtTreePropertyBrowserPrivate::slotExpanded(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    QExtBrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit q_ptr->expanded(idx);
}

void QExtTreePropertyBrowserPrivate::slotCurrentBrowserItemChanged(QExtBrowserItem *item)
{
    if (!m_browserChangedBlocked && item != currentItem())
        setCurrentItem(item, true);
}

void QExtTreePropertyBrowserPrivate::slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *)
{
    QExtBrowserItem *browserItem = newItem ? m_itemToIndex.value(newItem) : 0;
    m_browserChangedBlocked = true;
    q_ptr->setCurrentItem(browserItem);
    m_browserChangedBlocked = false;
}

QTreeWidgetItem *QExtTreePropertyBrowserPrivate::editedItem() const
{
    return m_delegate->editedItem();
}

void QExtTreePropertyBrowserPrivate::editItem(QExtBrowserItem *browserItem)
{
    if (QTreeWidgetItem *treeItem = m_indexToItem.value(browserItem, 0)) {
        m_treeWidget->setCurrentItem (treeItem, 1);
        m_treeWidget->editItem(treeItem, 1);
    }
}

/*!
    \class QExtTreePropertyBrowser

    \brief The QExtTreePropertyBrowser class provides QTreeWidget based
    property browser.

    A property browser is a widget that enables the user to edit a
    given set of properties. Each property is represented by a label
    specifying the property's name, and an editing widget (e.g. a line
    edit or a combobox) holding its value. A property can have zero or
    more subproperties.

    QExtTreePropertyBrowser provides a tree based view for all nested
    properties, i.e. properties that have subproperties can be in an
    expanded (subproperties are visible) or collapsed (subproperties
    are hidden) state. For example:

    \image qttreepropertybrowser.png

    Use the QExtAbstractPropertyBrowser API to add, insert and remove
    properties from an instance of the QExtTreePropertyBrowser class.
    The properties themselves are created and managed by
    implementations of the QExtAbstractPropertyManager class.

    \sa QExtGroupBoxPropertyBrowser, QExtAbstractPropertyBrowser
*/

/*!
    \fn void QExtTreePropertyBrowser::collapsed(QExtBrowserItem *item)

    This signal is emitted when the \a item is collapsed.

    \sa expanded(), setExpanded()
*/

/*!
    \fn void QExtTreePropertyBrowser::expanded(QExtBrowserItem *item)

    This signal is emitted when the \a item is expanded.

    \sa collapsed(), setExpanded()
*/

/*!
    Creates a property browser with the given \a parent.
*/
QExtTreePropertyBrowser::QExtTreePropertyBrowser(QWidget *parent)
    : QExtAbstractPropertyBrowser(parent)
{
    d_ptr = new QExtTreePropertyBrowserPrivate;
    d_ptr->q_ptr = this;

    d_ptr->init(this);
    connect(this, SIGNAL(currentItemChanged(QExtBrowserItem*)), this, SLOT(slotCurrentBrowserItemChanged(QExtBrowserItem*)));
}

/*!
    Destroys this property browser.

    Note that the properties that were inserted into this browser are
    \e not destroyed since they may still be used in other
    browsers. The properties are owned by the manager that created
    them.

    \sa QExtProperty, QExtAbstractPropertyManager
*/
QExtTreePropertyBrowser::~QExtTreePropertyBrowser()
{
    delete d_ptr;
}

/*!
    \property QExtTreePropertyBrowser::indentation
    \brief indentation of the items in the tree view.
*/
int QExtTreePropertyBrowser::indentation() const
{
    return d_ptr->m_treeWidget->indentation();
}

void QExtTreePropertyBrowser::setIndentation(int i)
{
    d_ptr->m_treeWidget->setIndentation(i);
}

/*!
  \property QExtTreePropertyBrowser::rootIsDecorated
  \brief whether to show controls for expanding and collapsing root items.
*/
bool QExtTreePropertyBrowser::rootIsDecorated() const
{
    return d_ptr->m_treeWidget->rootIsDecorated();
}

void QExtTreePropertyBrowser::setRootIsDecorated(bool show)
{
    d_ptr->m_treeWidget->setRootIsDecorated(show);
    QMapIterator<QTreeWidgetItem *, QExtBrowserItem *> it(d_ptr->m_itemToIndex);
    while (it.hasNext()) {
        QExtProperty *property = it.next().value()->property();
        if (!property->hasValue())
            d_ptr->updateItem(it.key());
    }
}

/*!
  \property QExtTreePropertyBrowser::alternatingRowColors
  \brief whether to draw the background using alternating colors.
  By default this property is set to true.
*/
bool QExtTreePropertyBrowser::alternatingRowColors() const
{
    return d_ptr->m_treeWidget->alternatingRowColors();
}

void QExtTreePropertyBrowser::setAlternatingRowColors(bool enable)
{
    d_ptr->m_treeWidget->setAlternatingRowColors(enable);
    QMapIterator<QTreeWidgetItem *, QExtBrowserItem *> it(d_ptr->m_itemToIndex);
}

/*!
  \property QExtTreePropertyBrowser::headerVisible
  \brief whether to show the header.
*/
bool QExtTreePropertyBrowser::isHeaderVisible() const
{
    return d_ptr->m_headerVisible;
}

void QExtTreePropertyBrowser::setHeaderVisible(bool visible)
{
    if (d_ptr->m_headerVisible == visible)
        return;

    d_ptr->m_headerVisible = visible;
    d_ptr->m_treeWidget->header()->setVisible(visible);
}

/*!
  \enum QExtTreePropertyBrowser::ResizeMode

  The resize mode specifies the behavior of the header sections.

  \value Interactive The user can resize the sections.
  The sections can also be resized programmatically using setSplitterPosition().

  \value Fixed The user cannot resize the section.
  The section can only be resized programmatically using setSplitterPosition().

  \value Stretch QHeaderView will automatically resize the section to fill the available space.
  The size cannot be changed by the user or programmatically.

  \value ResizeToContents QHeaderView will automatically resize the section to its optimal
  size based on the contents of the entire column.
  The size cannot be changed by the user or programmatically.

  \sa setResizeMode()
*/

/*!
    \property QExtTreePropertyBrowser::resizeMode
    \brief the resize mode of setions in the header.
*/

QExtTreePropertyBrowser::ResizeMode QExtTreePropertyBrowser::resizeMode() const
{
    return d_ptr->m_resizeMode;
}

void QExtTreePropertyBrowser::setResizeMode(QExtTreePropertyBrowser::ResizeMode mode)
{
    if (d_ptr->m_resizeMode == mode)
        return;

    d_ptr->m_resizeMode = mode;
    QHeaderView::ResizeMode m = QHeaderView::Stretch;
    switch (mode) {
    case QExtTreePropertyBrowser::Interactive:      m = QHeaderView::Interactive;      break;
    case QExtTreePropertyBrowser::Fixed:            m = QHeaderView::Fixed;            break;
    case QExtTreePropertyBrowser::ResizeToContents: m = QHeaderView::ResizeToContents; break;
    case QExtTreePropertyBrowser::Stretch:
    default:                                      m = QHeaderView::Stretch;          break;
    }
#if QT_DEPRECATED_SINCE(5, 0)
    d_ptr->m_treeWidget->header()->setResizeMode(m);
#endif
}

/*!
    \property QExtTreePropertyBrowser::splitterPosition
    \brief the position of the splitter between the colunms.
*/

int QExtTreePropertyBrowser::splitterPosition() const
{
    return d_ptr->m_treeWidget->header()->sectionSize(0);
}

void QExtTreePropertyBrowser::setSplitterPosition(int position)
{
    d_ptr->m_treeWidget->header()->resizeSection(0, position);
}

/*!
    Sets the \a item to either collapse or expanded, depending on the value of \a expanded.

    \sa isExpanded(), expanded(), collapsed()
*/

void QExtTreePropertyBrowser::setExpanded(QExtBrowserItem *item, bool expanded)
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
        treeItem->setExpanded(expanded);
}

/*!
    Returns true if the \a item is expanded; otherwise returns false.

    \sa setExpanded()
*/

bool QExtTreePropertyBrowser::isExpanded(QExtBrowserItem *item) const
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
        return treeItem->isExpanded();
    return false;
}

/*!
    Returns true if the \a item is visible; otherwise returns false.

    \sa setItemVisible()
    \since 4.5
*/

bool QExtTreePropertyBrowser::isItemVisible(QExtBrowserItem *item) const
{
    if (const QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
        return !treeItem->isHidden();
    return false;
}

/*!
    Sets the \a item to be visible, depending on the value of \a visible.

   \sa isItemVisible()
   \since 4.5
*/

void QExtTreePropertyBrowser::setItemVisible(QExtBrowserItem *item, bool visible)
{
    if (QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
        treeItem->setHidden(!visible);
}

/*!
    Sets the \a item's background color to \a color. Note that while item's background
    is rendered every second row is being drawn with alternate color (which is a bit lighter than items \a color)

    \sa backgroundColor(), calculatedBackgroundColor()
*/

void QExtTreePropertyBrowser::setBackgroundColor(QExtBrowserItem *item, const QColor &color)
{
    if (!d_ptr->m_indexToItem.contains(item))
        return;
    if (color.isValid())
        d_ptr->m_indexToBackgroundColor[item] = color;
    else
        d_ptr->m_indexToBackgroundColor.remove(item);
    d_ptr->m_treeWidget->viewport()->update();
}

/*!
    Returns the \a item's color. If there is no color set for item it returns invalid color.

    \sa calculatedBackgroundColor(), setBackgroundColor()
*/

QColor QExtTreePropertyBrowser::backgroundColor(QExtBrowserItem *item) const
{
    return d_ptr->m_indexToBackgroundColor.value(item);
}

/*!
    Returns the \a item's color. If there is no color set for item it returns parent \a item's
    color (if there is no color set for parent it returns grandparent's color and so on). In case
    the color is not set for \a item and it's top level item it returns invalid color.

    \sa backgroundColor(), setBackgroundColor()
*/

QColor QExtTreePropertyBrowser::calculatedBackgroundColor(QExtBrowserItem *item) const
{
    return d_ptr->calculatedBackgroundColor(item);
}

/*!
    \property QExtTreePropertyBrowser::propertiesWithoutValueMarked
    \brief whether to enable or disable marking properties without value.

    When marking is enabled the item's background is rendered in dark color and item's
    foreground is rendered with light color.

    \sa propertiesWithoutValueMarked()
*/
void QExtTreePropertyBrowser::setPropertiesWithoutValueMarked(bool mark)
{
    if (d_ptr->m_markPropertiesWithoutValue == mark)
        return;

    d_ptr->m_markPropertiesWithoutValue = mark;
    QMapIterator<QTreeWidgetItem *, QExtBrowserItem *> it(d_ptr->m_itemToIndex);
    while (it.hasNext()) {
        QExtProperty *property = it.next().value()->property();
        if (!property->hasValue())
            d_ptr->updateItem(it.key());
    }
    d_ptr->m_treeWidget->viewport()->update();
}

bool QExtTreePropertyBrowser::propertiesWithoutValueMarked() const
{
    return d_ptr->m_markPropertiesWithoutValue;
}

/*!
    \reimp
*/
void QExtTreePropertyBrowser::itemInserted(QExtBrowserItem *item, QExtBrowserItem *afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

/*!
    \reimp
*/
void QExtTreePropertyBrowser::itemRemoved(QExtBrowserItem *item)
{
    d_ptr->propertyRemoved(item);
}

/*!
    \reimp
*/
void QExtTreePropertyBrowser::itemChanged(QExtBrowserItem *item)
{
    d_ptr->propertyChanged(item);
}

/*!
    Sets the current item to \a item and opens the relevant editor for it.
*/
void QExtTreePropertyBrowser::editItem(QExtBrowserItem *item)
{
    d_ptr->editItem(item);
}


/***********************************************************************************************************************
** qtvariantproperty
***********************************************************************************************************************/

class QtEnumPropertyType
{
};


class QtFlagPropertyType
{
};


class QtGroupPropertyType
{
};

Q_DECLARE_METATYPE(QtEnumPropertyType)
Q_DECLARE_METATYPE(QtFlagPropertyType)
Q_DECLARE_METATYPE(QtGroupPropertyType)

/*!
    Returns the type id for an enum property.

    Note that the property's value type can be retrieved using the
    valueType() function (which is QVariant::Int for the enum property
    type).

    \sa propertyType(), valueType()
*/
int QExtVariantPropertyManager::enumTypeId()
{
    return qMetaTypeId<QtEnumPropertyType>();
}

/*!
    Returns the type id for a flag property.

    Note that the property's value type can be retrieved using the
    valueType() function (which is QVariant::Int for the flag property
    type).

    \sa propertyType(), valueType()
*/
int QExtVariantPropertyManager::flagTypeId()
{
    return qMetaTypeId<QtFlagPropertyType>();
}

/*!
    Returns the type id for a group property.

    Note that the property's value type can be retrieved using the
    valueType() function (which is QVariant::Invalid for the group
    property type, since it doesn't provide any value).

    \sa propertyType(), valueType()
*/
int QExtVariantPropertyManager::groupTypeId()
{
    return qMetaTypeId<QtGroupPropertyType>();
}

/*!
    Returns the type id for a icon map attribute.

    Note that the property's attribute type can be retrieved using the
    attributeType() function.

    \sa attributeType(), QExtEnumPropertyManager::enumIcons()
*/
int QExtVariantPropertyManager::iconMapTypeId()
{
    return qMetaTypeId<QtIconMap>();
}

typedef QMap<const QExtProperty *, QExtProperty *> PropertyMap;
Q_GLOBAL_STATIC(PropertyMap, propertyToWrappedProperty)

static QExtProperty *wrappedProperty(QExtProperty *property)
{
    return propertyToWrappedProperty()->value(property, 0);
}

class QExtVariantPropertyPrivate
{
    QExtVariantProperty *q_ptr;
public:
    QExtVariantPropertyPrivate(QExtVariantPropertyManager *m) : manager(m) {}

    QExtVariantPropertyManager *manager;
};

/*!
    \class QExtVariantProperty

    \brief The QExtVariantProperty class is a convenience class handling
    QVariant based properties.

    QExtVariantProperty provides additional API: A property's type,
    value type, attribute values and current value can easily be
    retrieved using the propertyType(), valueType(), attributeValue()
    and value() functions respectively. In addition, the attribute
    values and the current value can be set using the corresponding
    setValue() and setAttribute() functions.

    For example, instead of writing:

    \code
        QExtVariantPropertyManager *variantPropertyManager;
        QExtProperty *property;

        variantPropertyManager->setValue(property, 10);
    \endcode

    you can write:

    \code
        QExtVariantPropertyManager *variantPropertyManager;
        QExtVariantProperty *property;

        property->setValue(10);
    \endcode

    QExtVariantProperty instances can only be created by the
    QExtVariantPropertyManager class.

    \sa QExtProperty, QExtVariantPropertyManager, QExtVariantEditorFactory
*/

/*!
    Creates a variant property using the given \a manager.

    Do not use this constructor to create variant property instances;
    use the QExtVariantPropertyManager::addProperty() function
    instead.  This constructor is used internally by the
    QExtVariantPropertyManager::createProperty() function.

    \sa QExtVariantPropertyManager
*/
QExtVariantProperty::QExtVariantProperty(QExtVariantPropertyManager *manager)
    : QExtProperty(manager),  d_ptr(new QExtVariantPropertyPrivate(manager))
{

}

/*!
    Destroys this property.

    \sa QExtProperty::~QExtProperty()
*/
QExtVariantProperty::~QExtVariantProperty()
{
    delete d_ptr;
}

/*!
    Returns the property's current value.

    \sa valueType(), setValue()
*/
QVariant QExtVariantProperty::value() const
{
    return d_ptr->manager->value(this);
}

/*!
    Returns this property's value for the specified \a attribute.

    QExtVariantPropertyManager provides a couple of related functions:
    \l{QExtVariantPropertyManager::attributes()}{attributes()} and
    \l{QExtVariantPropertyManager::attributeType()}{attributeType()}.

    \sa setAttribute()
*/
QVariant QExtVariantProperty::attributeValue(const QString &attribute) const
{
    return d_ptr->manager->attributeValue(this, attribute);
}

/*!
    Returns the type of this property's value.

    \sa propertyType()
*/
int QExtVariantProperty::valueType() const
{
    return d_ptr->manager->valueType(this);
}

/*!
    Returns this property's type.

    QExtVariantPropertyManager provides several related functions:
    \l{QExtVariantPropertyManager::enumTypeId()}{enumTypeId()},
    \l{QExtVariantPropertyManager::flagTypeId()}{flagTypeId()} and
    \l{QExtVariantPropertyManager::groupTypeId()}{groupTypeId()}.

    \sa valueType()
*/
int QExtVariantProperty::propertyType() const
{
    return d_ptr->manager->propertyType(this);
}

/*!
    Sets the value of this property to \a value.

    The specified \a value must be of the type returned by
    valueType(), or of a type that can be converted to valueType()
    using the QVariant::canConvert() function; otherwise this function
    does nothing.

    \sa value()
*/
void QExtVariantProperty::setValue(const QVariant &value)
{
    d_ptr->manager->setValue(this, value);
}

/*!
    Sets the \a attribute of property to \a value.

    QExtVariantPropertyManager provides the related
    \l{QExtVariantPropertyManager::setAttribute()}{setAttribute()}
    function.

    \sa attributeValue()
*/
void QExtVariantProperty::setAttribute(const QString &attribute, const QVariant &value)
{
    d_ptr->manager->setAttribute(this, attribute, value);
}

class QExtVariantPropertyManagerPrivate
{
    QExtVariantPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QExtVariantPropertyManager)
public:
    QExtVariantPropertyManagerPrivate();

    bool m_creatingProperty;
    bool m_creatingSubProperties;
    bool m_destroyingSubProperties;
    int m_propertyType;

    void slotValueChanged(QExtProperty *property, int val);
    void slotRangeChanged(QExtProperty *property, int min, int max);
    void slotSingleStepChanged(QExtProperty *property, int step);
    void slotValueChanged(QExtProperty *property, double val);
    void slotRangeChanged(QExtProperty *property, double min, double max);
    void slotSingleStepChanged(QExtProperty *property, double step);
    void slotDecimalsChanged(QExtProperty *property, int prec);
    void slotValueChanged(QExtProperty *property, bool val);
    void slotValueChanged(QExtProperty *property, const QString &val);
    void slotRegExpChanged(QExtProperty *property, const QRegExp &regExp);
    void slotEchoModeChanged(QExtProperty *property, int);
    void slotValueChanged(QExtProperty *property, const QDate &val);
    void slotRangeChanged(QExtProperty *property, const QDate &min, const QDate &max);
    void slotValueChanged(QExtProperty *property, const QTime &val);
    void slotValueChanged(QExtProperty *property, const QDateTime &val);
    void slotValueChanged(QExtProperty *property, const QKeySequence &val);
    void slotValueChanged(QExtProperty *property, const QChar &val);
    void slotValueChanged(QExtProperty *property, const QLocale &val);
    void slotValueChanged(QExtProperty *property, const QPoint &val);
    void slotValueChanged(QExtProperty *property, const QPointF &val);
    void slotValueChanged(QExtProperty *property, const QSize &val);
    void slotRangeChanged(QExtProperty *property, const QSize &min, const QSize &max);
    void slotValueChanged(QExtProperty *property, const QSizeF &val);
    void slotRangeChanged(QExtProperty *property, const QSizeF &min, const QSizeF &max);
    void slotValueChanged(QExtProperty *property, const QRect &val);
    void slotConstraintChanged(QExtProperty *property, const QRect &val);
    void slotValueChanged(QExtProperty *property, const QRectF &val);
    void slotConstraintChanged(QExtProperty *property, const QRectF &val);
    void slotValueChanged(QExtProperty *property, const QColor &val);
    void slotEnumChanged(QExtProperty *property, int val);
    void slotEnumNamesChanged(QExtProperty *property, const QStringList &enumNames);
    void slotEnumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &enumIcons);
    void slotValueChanged(QExtProperty *property, const QSizePolicy &val);
    void slotValueChanged(QExtProperty *property, const QFont &val);
    void slotValueChanged(QExtProperty *property, const QCursor &val);
    void slotFlagChanged(QExtProperty *property, int val);
    void slotFlagNamesChanged(QExtProperty *property, const QStringList &flagNames);
    void slotReadOnlyChanged(QExtProperty *property, bool readOnly);
    void slotTextVisibleChanged(QExtProperty *property, bool textVisible);
    void slotPropertyInserted(QExtProperty *property, QExtProperty *parent, QExtProperty *after);
    void slotPropertyRemoved(QExtProperty *property, QExtProperty *parent);

    void valueChanged(QExtProperty *property, const QVariant &val);

    int internalPropertyToType(QExtProperty *property) const;
    QExtVariantProperty *createSubProperty(QExtVariantProperty *parent, QExtVariantProperty *after,
                                           QExtProperty *internal);
    void removeSubProperty(QExtVariantProperty *property);

    QMap<int, QExtAbstractPropertyManager *> m_typeToPropertyManager;
    QMap<int, QMap<QString, int> > m_typeToAttributeToAttributeType;

    QMap<const QExtProperty *, QPair<QExtVariantProperty *, int> > m_propertyToType;

    QMap<int, int> m_typeToValueType;


    QMap<QExtProperty *, QExtVariantProperty *> m_internalToProperty;

    const QString m_constraintAttribute;
    const QString m_singleStepAttribute;
    const QString m_decimalsAttribute;
    const QString m_enumIconsAttribute;
    const QString m_enumNamesAttribute;
    const QString m_flagNamesAttribute;
    const QString m_maximumAttribute;
    const QString m_minimumAttribute;
    const QString m_regExpAttribute;
    const QString m_echoModeAttribute;
    const QString m_readOnlyAttribute;
    const QString m_textVisibleAttribute;
};

QExtVariantPropertyManagerPrivate::QExtVariantPropertyManagerPrivate() :
    m_constraintAttribute(QLatin1String("constraint")),
    m_singleStepAttribute(QLatin1String("singleStep")),
    m_decimalsAttribute(QLatin1String("decimals")),
    m_enumIconsAttribute(QLatin1String("enumIcons")),
    m_enumNamesAttribute(QLatin1String("enumNames")),
    m_flagNamesAttribute(QLatin1String("flagNames")),
    m_maximumAttribute(QLatin1String("maximum")),
    m_minimumAttribute(QLatin1String("minimum")),
    m_regExpAttribute(QLatin1String("regExp")),
    m_echoModeAttribute(QLatin1String("echoMode")),
    m_readOnlyAttribute(QLatin1String("readOnly")),
    m_textVisibleAttribute(QLatin1String("textVisible"))
{
}

int QExtVariantPropertyManagerPrivate::internalPropertyToType(QExtProperty *property) const
{
    int type = 0;
    QExtAbstractPropertyManager *internPropertyManager = property->propertyManager();
    if (qobject_cast<QExtIntPropertyManager *>(internPropertyManager))
        type = QVariant::Int;
    else if (qobject_cast<QExtEnumPropertyManager *>(internPropertyManager))
        type = QExtVariantPropertyManager::enumTypeId();
    else if (qobject_cast<QExtBoolPropertyManager *>(internPropertyManager))
        type = QVariant::Bool;
    else if (qobject_cast<QExtDoublePropertyManager *>(internPropertyManager))
        type = QVariant::Double;
    return type;
}

QExtVariantProperty *QExtVariantPropertyManagerPrivate::createSubProperty(QExtVariantProperty *parent,
                                                                          QExtVariantProperty *after, QExtProperty *internal)
{
    int type = internalPropertyToType(internal);
    if (!type)
        return 0;

    bool wasCreatingSubProperties = m_creatingSubProperties;
    m_creatingSubProperties = true;

    QExtVariantProperty *varChild = q_ptr->addProperty(type, internal->propertyName());

    m_creatingSubProperties = wasCreatingSubProperties;

    varChild->setPropertyName(internal->propertyName());
    varChild->setToolTip(internal->toolTip());
    varChild->setStatusTip(internal->statusTip());
    varChild->setWhatsThis(internal->whatsThis());

    m_internalToProperty[internal] = varChild;
    propertyToWrappedProperty()->insert(varChild, internal);

    parent->insertSubProperty(varChild, after);
    return varChild;
}

void QExtVariantPropertyManagerPrivate::removeSubProperty(QExtVariantProperty *property)
{
    QExtProperty *internChild = wrappedProperty(property);
    bool wasDestroyingSubProperties = m_destroyingSubProperties;
    m_destroyingSubProperties = true;
    delete property;
    m_destroyingSubProperties = wasDestroyingSubProperties;
    m_internalToProperty.remove(internChild);
    propertyToWrappedProperty()->remove(property);
}

void QExtVariantPropertyManagerPrivate::slotPropertyInserted(QExtProperty *property,
                                                             QExtProperty *parent, QExtProperty *after)
{
    if (m_creatingProperty)
        return;

    QExtVariantProperty *varParent = m_internalToProperty.value(parent, 0);
    if (!varParent)
        return;

    QExtVariantProperty *varAfter = 0;
    if (after) {
        varAfter = m_internalToProperty.value(after, 0);
        if (!varAfter)
            return;
    }

    createSubProperty(varParent, varAfter, property);
}

void QExtVariantPropertyManagerPrivate::slotPropertyRemoved(QExtProperty *property, QExtProperty *parent)
{
    Q_UNUSED(parent)

    QExtVariantProperty *varProperty = m_internalToProperty.value(property, 0);
    if (!varProperty)
        return;

    removeSubProperty(varProperty);
}

void QExtVariantPropertyManagerPrivate::valueChanged(QExtProperty *property, const QVariant &val)
{
    QExtVariantProperty *varProp = m_internalToProperty.value(property, 0);
    if (!varProp)
        return;
    emit q_ptr->valueChanged(varProp, val);
    emit q_ptr->propertyChanged(varProp);
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, int val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRangeChanged(QExtProperty *property, int min, int max)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtVariantPropertyManagerPrivate::slotSingleStepChanged(QExtProperty *property, int step)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, double val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRangeChanged(QExtProperty *property, double min, double max)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtVariantPropertyManagerPrivate::slotSingleStepChanged(QExtProperty *property, double step)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_singleStepAttribute, QVariant(step));
}

void QExtVariantPropertyManagerPrivate::slotDecimalsChanged(QExtProperty *property, int prec)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_decimalsAttribute, QVariant(prec));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, bool val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QString &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRegExpChanged(QExtProperty *property, const QRegExp &regExp)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_regExpAttribute, QVariant(regExp));
}

void QExtVariantPropertyManagerPrivate::slotEchoModeChanged(QExtProperty *property, int mode)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_echoModeAttribute, QVariant(mode));
}

void QExtVariantPropertyManagerPrivate::slotReadOnlyChanged(QExtProperty *property, bool readOnly)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_readOnlyAttribute, QVariant(readOnly));
}

void QExtVariantPropertyManagerPrivate::slotTextVisibleChanged(QExtProperty *property, bool textVisible)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_textVisibleAttribute, QVariant(textVisible));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QDate &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRangeChanged(QExtProperty *property, const QDate &min, const QDate &max)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QTime &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QDateTime &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QKeySequence &val)
{
    QVariant v;
    qVariantSetValue(v, val);
    valueChanged(property, v);
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QChar &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QLocale &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QPoint &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QPointF &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QSize &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRangeChanged(QExtProperty *property, const QSize &min, const QSize &max)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QSizeF &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotRangeChanged(QExtProperty *property, const QSizeF &min, const QSizeF &max)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        emit q_ptr->attributeChanged(varProp, m_minimumAttribute, QVariant(min));
        emit q_ptr->attributeChanged(varProp, m_maximumAttribute, QVariant(max));
    }
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QRect &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotConstraintChanged(QExtProperty *property, const QRect &constraint)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QRectF &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotConstraintChanged(QExtProperty *property, const QRectF &constraint)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_constraintAttribute, QVariant(constraint));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QColor &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotEnumNamesChanged(QExtProperty *property, const QStringList &enumNames)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_enumNamesAttribute, QVariant(enumNames));
}

void QExtVariantPropertyManagerPrivate::slotEnumIconsChanged(QExtProperty *property, const QMap<int, QIcon> &enumIcons)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0)) {
        QVariant v;
        qVariantSetValue(v, enumIcons);
        emit q_ptr->attributeChanged(varProp, m_enumIconsAttribute, v);
    }
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QSizePolicy &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QFont &val)
{
    valueChanged(property, QVariant(val));
}

void QExtVariantPropertyManagerPrivate::slotValueChanged(QExtProperty *property, const QCursor &val)
{
#ifndef QT_NO_CURSOR
    valueChanged(property, QVariant(val));
#endif
}

void QExtVariantPropertyManagerPrivate::slotFlagNamesChanged(QExtProperty *property, const QStringList &flagNames)
{
    if (QExtVariantProperty *varProp = m_internalToProperty.value(property, 0))
        emit q_ptr->attributeChanged(varProp, m_flagNamesAttribute, QVariant(flagNames));
}

/*!
    \class QExtVariantPropertyManager

    \brief The QExtVariantPropertyManager class provides and manages QVariant based properties.

    QExtVariantPropertyManager provides the addProperty() function which
    creates QExtVariantProperty objects. The QExtVariantProperty class is
    a convenience class handling QVariant based properties inheriting
    QExtProperty. A QExtProperty object created by a
    QExtVariantPropertyManager instance can be converted into a
    QExtVariantProperty object using the variantProperty() function.

    The property's value can be retrieved using the value(), and set
    using the setValue() slot. In addition the property's type, and
    the type of its value, can be retrieved using the propertyType()
    and valueType() functions respectively.

    A property's type is a QVariant::Type enumerator value, and
    usually a property's type is the same as its value type. But for
    some properties the types differ, for example for enums, flags and
    group types in which case QExtVariantPropertyManager provides the
    enumTypeId(), flagTypeId() and groupTypeId() functions,
    respectively, to identify their property type (the value types are
    QVariant::Int for the enum and flag types, and QVariant::Invalid
    for the group type).

    Use the isPropertyTypeSupported() function to check if a particular
    property type is supported. The currently supported property types
    are:

    \table
    \header
        \o Property Type
        \o Property Type Id
    \row
        \o int
        \o QVariant::Int
    \row
        \o double
        \o QVariant::Double
    \row
        \o bool
        \o QVariant::Bool
    \row
        \o QString
        \o QVariant::String
    \row
        \o QDate
        \o QVariant::Date
    \row
        \o QTime
        \o QVariant::Time
    \row
        \o QDateTime
        \o QVariant::DateTime
    \row
        \o QKeySequence
        \o QVariant::KeySequence
    \row
        \o QChar
        \o QVariant::Char
    \row
        \o QLocale
        \o QVariant::Locale
    \row
        \o QPoint
        \o QVariant::Point
    \row
        \o QPointF
        \o QVariant::PointF
    \row
        \o QSize
        \o QVariant::Size
    \row
        \o QSizeF
        \o QVariant::SizeF
    \row
        \o QRect
        \o QVariant::Rect
    \row
        \o QRectF
        \o QVariant::RectF
    \row
        \o QColor
        \o QVariant::Color
    \row
        \o QSizePolicy
        \o QVariant::SizePolicy
    \row
        \o QFont
        \o QVariant::Font
    \row
        \o QCursor
        \o QVariant::Cursor
    \row
        \o enum
        \o enumTypeId()
    \row
        \o flag
        \o flagTypeId()
    \row
        \o group
        \o groupTypeId()
    \endtable

    Each property type can provide additional attributes,
    e.g. QVariant::Int and QVariant::Double provides minimum and
    maximum values. The currently supported attributes are:

    \table
    \header
        \o Property Type
        \o Attribute Name
        \o Attribute Type
    \row
        \o \c int
        \o minimum
        \o QVariant::Int
    \row
        \o
        \o maximum
        \o QVariant::Int
    \row
        \o
        \o singleStep
        \o QVariant::Int
    \row
        \o \c double
        \o minimum
        \o QVariant::Double
    \row
        \o
        \o maximum
        \o QVariant::Double
    \row
        \o
        \o singleStep
        \o QVariant::Double
    \row
        \o
        \o decimals
        \o QVariant::Int
    \row
        \o \c bool
        \o textVisible
        \o QVariant::Bool
    \row
        \o QString
        \o regExp
        \o QVariant::RegExp
    \row
        \o
        \o echoMode
        \o QVariant::Int
    \row
        \o QDate
        \o minimum
        \o QVariant::Date
    \row
        \o
        \o maximum
        \o QVariant::Date
    \row
        \o QPointF
        \o decimals
        \o QVariant::Int
    \row
        \o QSize
        \o minimum
        \o QVariant::Size
    \row
        \o
        \o maximum
        \o QVariant::Size
    \row
        \o QSizeF
        \o minimum
        \o QVariant::SizeF
    \row
        \o
        \o maximum
        \o QVariant::SizeF
    \row
        \o
        \o decimals
        \o QVariant::Int
    \row
        \o QRect
        \o constraint
        \o QVariant::Rect
    \row
        \o QRectF
        \o constraint
        \o QVariant::RectF
    \row
        \o
        \o decimals
        \o QVariant::Int
    \row
        \o \c enum
        \o enumNames
        \o QVariant::StringList
    \row
        \o
        \o enumIcons
        \o iconMapTypeId()
    \row
        \o \c flag
        \o flagNames
        \o QVariant::StringList
    \endtable

    The attributes for a given property type can be retrieved using
    the attributes() function. Each attribute has a value type which
    can be retrieved using the attributeType() function, and a value
    accessible through the attributeValue() function. In addition, the
    value can be set using the setAttribute() slot.

    QtVariantManager also provides the valueChanged() signal which is
    emitted whenever a property created by this manager change, and
    the attributeChanged() signal which is emitted whenever an
    attribute of such a property changes.

    \sa QExtVariantProperty, QExtVariantEditorFactory
*/

/*!
    \fn void QExtVariantPropertyManager::valueChanged(QExtProperty *property, const QVariant &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QExtVariantPropertyManager::attributeChanged(QExtProperty *property,
                const QString &attribute, const QVariant &value)

    This signal is emitted whenever an attribute of a property created
    by this manager changes its value, passing a pointer to the \a
    property, the \a attribute and the new \a value as parameters.

    \sa setAttribute()
*/

/*!
    Creates a manager with the given \a parent.
*/
QExtVariantPropertyManager::QExtVariantPropertyManager(QObject *parent)
    : QExtAbstractPropertyManager(parent)
{
    d_ptr = new QExtVariantPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_creatingProperty = false;
    d_ptr->m_creatingSubProperties = false;
    d_ptr->m_destroyingSubProperties = false;
    d_ptr->m_propertyType = 0;

    // IntPropertyManager
    QExtIntPropertyManager *intPropertyManager = new QExtIntPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Int] = intPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_minimumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_maximumAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_singleStepAttribute] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Int][d_ptr->m_readOnlyAttribute] = QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Int] = QVariant::Int;
    connect(intPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(intPropertyManager, SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(intPropertyManager, SIGNAL(singleStepChanged(QExtProperty *, int)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, int)));
    // DoublePropertyManager
    QExtDoublePropertyManager *doublePropertyManager = new QExtDoublePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Double] = doublePropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_minimumAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_maximumAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_singleStepAttribute] =
            QVariant::Double;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Double][d_ptr->m_readOnlyAttribute] =
            QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Double] = QVariant::Double;
    connect(doublePropertyManager, SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotValueChanged(QExtProperty *, double)));
    connect(doublePropertyManager, SIGNAL(rangeChanged(QExtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtProperty *, double, double)));
    connect(doublePropertyManager, SIGNAL(singleStepChanged(QExtProperty *, double)),
            this, SLOT(slotSingleStepChanged(QExtProperty *, double)));
    connect(doublePropertyManager, SIGNAL(decimalsChanged(QExtProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    // BoolPropertyManager
    QExtBoolPropertyManager *boolPropertyManager = new QExtBoolPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Bool] = boolPropertyManager;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Bool][d_ptr->m_textVisibleAttribute] = QVariant::Bool;
    d_ptr->m_typeToValueType[QVariant::Bool] = QVariant::Bool;
    connect(boolPropertyManager, SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotValueChanged(QExtProperty *, bool)));
    connect(boolPropertyManager, SIGNAL(textVisibleChanged(QExtProperty*, bool)),
            this, SLOT(slotTextVisibleChanged(QExtProperty*, bool)));
    // StringPropertyManager
    QExtStringPropertyManager *stringPropertyManager = new QExtStringPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::String] = stringPropertyManager;
    d_ptr->m_typeToValueType[QVariant::String] = QVariant::String;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_regExpAttribute] =
            QVariant::RegExp;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_echoModeAttribute] =
            QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::String][d_ptr->m_readOnlyAttribute] =
            QVariant::Bool;

    connect(stringPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QString &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QString &)));
    connect(stringPropertyManager, SIGNAL(regExpChanged(QExtProperty *, const QRegExp &)),
            this, SLOT(slotRegExpChanged(QExtProperty *, const QRegExp &)));
    connect(stringPropertyManager, SIGNAL(echoModeChanged(QExtProperty*,int)),
            this, SLOT(slotEchoModeChanged(QExtProperty*, int)));
    connect(stringPropertyManager, SIGNAL(readOnlyChanged(QExtProperty*, bool)),
            this, SLOT(slotReadOnlyChanged(QExtProperty*, bool)));

    // DatePropertyManager
    QExtDatePropertyManager *datePropertyManager = new QExtDatePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Date] = datePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Date] = QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_minimumAttribute] =
            QVariant::Date;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Date][d_ptr->m_maximumAttribute] =
            QVariant::Date;
    connect(datePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QDate &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QDate &)));
    connect(datePropertyManager, SIGNAL(rangeChanged(QExtProperty *, const QDate &, const QDate &)),
            this, SLOT(slotRangeChanged(QExtProperty *, const QDate &, const QDate &)));
    // TimePropertyManager
    QExtTimePropertyManager *timePropertyManager = new QExtTimePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Time] = timePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Time] = QVariant::Time;
    connect(timePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QTime &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QTime &)));
    // DateTimePropertyManager
    QExtDateTimePropertyManager *dateTimePropertyManager = new QExtDateTimePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::DateTime] = dateTimePropertyManager;
    d_ptr->m_typeToValueType[QVariant::DateTime] = QVariant::DateTime;
    connect(dateTimePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QDateTime &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QDateTime &)));
    // KeySequencePropertyManager
    QExtKeySequencePropertyManager *keySequencePropertyManager = new QExtKeySequencePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::KeySequence] = keySequencePropertyManager;
    d_ptr->m_typeToValueType[QVariant::KeySequence] = QVariant::KeySequence;
    connect(keySequencePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QKeySequence &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QKeySequence &)));
    // CharPropertyManager
    QExtCharPropertyManager *charPropertyManager = new QExtCharPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Char] = charPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Char] = QVariant::Char;
    connect(charPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QChar &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QChar &)));
    // LocalePropertyManager
    QExtLocalePropertyManager *localePropertyManager = new QExtLocalePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Locale] = localePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Locale] = QVariant::Locale;
    connect(localePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QLocale &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QLocale &)));
    connect(localePropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(localePropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(localePropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // PointPropertyManager
    QExtPointPropertyManager *pointPropertyManager = new QExtPointPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Point] = pointPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Point] = QVariant::Point;
    connect(pointPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QPoint &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QPoint &)));
    connect(pointPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(pointPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(pointPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // PointFPropertyManager
    QExtPointFPropertyManager *pointFPropertyManager = new QExtPointFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::PointF] = pointFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::PointF] = QVariant::PointF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::PointF][d_ptr->m_decimalsAttribute] =
            QVariant::Int;
    connect(pointFPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QPointF &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QPointF &)));
    connect(pointFPropertyManager, SIGNAL(decimalsChanged(QExtProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    connect(pointFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotValueChanged(QExtProperty *, double)));
    connect(pointFPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(pointFPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // SizePropertyManager
    QExtSizePropertyManager *sizePropertyManager = new QExtSizePropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Size] = sizePropertyManager;
    d_ptr->m_typeToValueType[QVariant::Size] = QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_minimumAttribute] =
            QVariant::Size;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Size][d_ptr->m_maximumAttribute] =
            QVariant::Size;
    connect(sizePropertyManager, SIGNAL(valueChanged(QExtProperty *, const QSize &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QSize &)));
    connect(sizePropertyManager, SIGNAL(rangeChanged(QExtProperty *, const QSize &, const QSize &)),
            this, SLOT(slotRangeChanged(QExtProperty *, const QSize &, const QSize &)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(sizePropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(sizePropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(sizePropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // SizeFPropertyManager
    QExtSizeFPropertyManager *sizeFPropertyManager = new QExtSizeFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizeF] = sizeFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizeF] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_minimumAttribute] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_maximumAttribute] = QVariant::SizeF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::SizeF][d_ptr->m_decimalsAttribute] = QVariant::Int;
    connect(sizeFPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QSizeF &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QSizeF &)));
    connect(sizeFPropertyManager, SIGNAL(rangeChanged(QExtProperty *, const QSizeF &, const QSizeF &)),
            this, SLOT(slotRangeChanged(QExtProperty *, const QSizeF &, const QSizeF &)));
    connect(sizeFPropertyManager, SIGNAL(decimalsChanged(QExtProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotValueChanged(QExtProperty *, double)));
    connect(sizeFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(QExtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtProperty *, double, double)));
    connect(sizeFPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(sizeFPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // RectPropertyManager
    QExtRectPropertyManager *rectPropertyManager = new QExtRectPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Rect] = rectPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Rect] = QVariant::Rect;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::Rect][d_ptr->m_constraintAttribute] = QVariant::Rect;
    connect(rectPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QRect &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QRect &)));
    connect(rectPropertyManager, SIGNAL(constraintChanged(QExtProperty *, const QRect &)),
            this, SLOT(slotConstraintChanged(QExtProperty *, const QRect &)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(rectPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(rectPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(rectPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // RectFPropertyManager
    QExtRectFPropertyManager *rectFPropertyManager = new QExtRectFPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::RectF] = rectFPropertyManager;
    d_ptr->m_typeToValueType[QVariant::RectF] = QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_constraintAttribute] = QVariant::RectF;
    d_ptr->m_typeToAttributeToAttributeType[QVariant::RectF][d_ptr->m_decimalsAttribute] = QVariant::Int;
    connect(rectFPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QRectF &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QRectF &)));
    connect(rectFPropertyManager, SIGNAL(constraintChanged(QExtProperty *, const QRectF &)),
            this, SLOT(slotConstraintChanged(QExtProperty *, const QRectF &)));
    connect(rectFPropertyManager, SIGNAL(decimalsChanged(QExtProperty *, int)),
            this, SLOT(slotDecimalsChanged(QExtProperty *, int)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(valueChanged(QExtProperty *, double)),
            this, SLOT(slotValueChanged(QExtProperty *, double)));
    connect(rectFPropertyManager->subDoublePropertyManager(), SIGNAL(rangeChanged(QExtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QExtProperty *, double, double)));
    connect(rectFPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(rectFPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // ColorPropertyManager
    QExtColorPropertyManager *colorPropertyManager = new QExtColorPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Color] = colorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Color] = QVariant::Color;
    connect(colorPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QColor &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QColor &)));
    connect(colorPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(colorPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(colorPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // EnumPropertyManager
    int enumId = enumTypeId();
    QExtEnumPropertyManager *enumPropertyManager = new QExtEnumPropertyManager(this);
    d_ptr->m_typeToPropertyManager[enumId] = enumPropertyManager;
    d_ptr->m_typeToValueType[enumId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumNamesAttribute] = QVariant::StringList;
    d_ptr->m_typeToAttributeToAttributeType[enumId][d_ptr->m_enumIconsAttribute] = iconMapTypeId();
    connect(enumPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(enumPropertyManager, SIGNAL(enumNamesChanged(QExtProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtProperty *, const QStringList &)));
    connect(enumPropertyManager, SIGNAL(enumIconsChanged(QExtProperty *, const QMap<int, QIcon> &)),
            this, SLOT(slotEnumIconsChanged(QExtProperty *, const QMap<int, QIcon> &)));
    // SizePolicyPropertyManager
    QExtSizePolicyPropertyManager *sizePolicyPropertyManager = new QExtSizePolicyPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::SizePolicy] = sizePolicyPropertyManager;
    d_ptr->m_typeToValueType[QVariant::SizePolicy] = QVariant::SizePolicy;
    connect(sizePolicyPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QSizePolicy &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QSizePolicy &)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(sizePolicyPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(sizePolicyPropertyManager->subEnumPropertyManager(),
            SIGNAL(enumNamesChanged(QExtProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtProperty *, const QStringList &)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(sizePolicyPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // FontPropertyManager
    QExtFontPropertyManager *fontPropertyManager = new QExtFontPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Font] = fontPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Font] = QVariant::Font;
    connect(fontPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QFont &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QFont &)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(fontPropertyManager->subIntPropertyManager(), SIGNAL(rangeChanged(QExtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QExtProperty *, int, int)));
    connect(fontPropertyManager->subEnumPropertyManager(), SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(fontPropertyManager->subEnumPropertyManager(),
            SIGNAL(enumNamesChanged(QExtProperty *, const QStringList &)),
            this, SLOT(slotEnumNamesChanged(QExtProperty *, const QStringList &)));
    connect(fontPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotValueChanged(QExtProperty *, bool)));
    connect(fontPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(fontPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // CursorPropertyManager
    QExtCursorPropertyManager *cursorPropertyManager = new QExtCursorPropertyManager(this);
    d_ptr->m_typeToPropertyManager[QVariant::Cursor] = cursorPropertyManager;
    d_ptr->m_typeToValueType[QVariant::Cursor] = QVariant::Cursor;
    connect(cursorPropertyManager, SIGNAL(valueChanged(QExtProperty *, const QCursor &)),
            this, SLOT(slotValueChanged(QExtProperty *, const QCursor &)));
    // FlagPropertyManager
    int flagId = flagTypeId();
    QExtFlagPropertyManager *flagPropertyManager = new QExtFlagPropertyManager(this);
    d_ptr->m_typeToPropertyManager[flagId] = flagPropertyManager;
    d_ptr->m_typeToValueType[flagId] = QVariant::Int;
    d_ptr->m_typeToAttributeToAttributeType[flagId][d_ptr->m_flagNamesAttribute] =
            QVariant::StringList;
    connect(flagPropertyManager, SIGNAL(valueChanged(QExtProperty *, int)),
            this, SLOT(slotValueChanged(QExtProperty *, int)));
    connect(flagPropertyManager, SIGNAL(flagNamesChanged(QExtProperty *, const QStringList &)),
            this, SLOT(slotFlagNamesChanged(QExtProperty *, const QStringList &)));
    connect(flagPropertyManager->subBoolPropertyManager(), SIGNAL(valueChanged(QExtProperty *, bool)),
            this, SLOT(slotValueChanged(QExtProperty *, bool)));
    connect(flagPropertyManager, SIGNAL(propertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyInserted(QExtProperty *, QExtProperty *, QExtProperty *)));
    connect(flagPropertyManager, SIGNAL(propertyRemoved(QExtProperty *, QExtProperty *)),
            this, SLOT(slotPropertyRemoved(QExtProperty *, QExtProperty *)));
    // FlagPropertyManager
    int groupId = groupTypeId();
    QExtGroupPropertyManager *groupPropertyManager = new QExtGroupPropertyManager(this);
    d_ptr->m_typeToPropertyManager[groupId] = groupPropertyManager;
    d_ptr->m_typeToValueType[groupId] = QVariant::Invalid;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QExtVariantPropertyManager::~QExtVariantPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property converted into a QExtVariantProperty.

    If the \a property was not created by this variant manager, the
    function returns 0.

    \sa createProperty()
*/
QExtVariantProperty *QExtVariantPropertyManager::variantProperty(const QExtProperty *property) const
{
    const QMap<const QExtProperty *, QPair<QExtVariantProperty *, int> >::const_iterator it = d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
        return 0;
    return it.value().first;
}

/*!
    Returns true if the given \a propertyType is supported by this
    variant manager; otherwise false.

    \sa propertyType()
*/
bool QExtVariantPropertyManager::isPropertyTypeSupported(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
        return true;
    return false;
}

/*!
   Creates and returns a variant property of the given \a propertyType
   with the given \a name.

   If the specified \a propertyType is not supported by this variant
   manager, this function returns 0.

   Do not use the inherited
   QExtAbstractPropertyManager::addProperty() function to create a
   variant property (that function will always return 0 since it will
   not be clear what type the property should have).

    \sa isPropertyTypeSupported()
*/
QExtVariantProperty *QExtVariantPropertyManager::addProperty(int propertyType, const QString &name)
{
    if (!isPropertyTypeSupported(propertyType))
        return 0;

    bool wasCreating = d_ptr->m_creatingProperty;
    d_ptr->m_creatingProperty = true;
    d_ptr->m_propertyType = propertyType;
    QExtProperty *property = QExtAbstractPropertyManager::addProperty(name);
    d_ptr->m_creatingProperty = wasCreating;
    d_ptr->m_propertyType = 0;

    if (!property)
        return 0;

    return variantProperty(property);
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid variant.

    \sa setValue()
*/
QVariant QExtVariantPropertyManager::value(const QExtProperty *property) const
{
    QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return QVariant();

    QExtAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtIntPropertyManager *intManager = qobject_cast<QExtIntPropertyManager *>(manager)) {
        return intManager->value(internProp);
    } else if (QExtDoublePropertyManager *doubleManager = qobject_cast<QExtDoublePropertyManager *>(manager)) {
        return doubleManager->value(internProp);
    } else if (QExtBoolPropertyManager *boolManager = qobject_cast<QExtBoolPropertyManager *>(manager)) {
        return boolManager->value(internProp);
    } else if (QExtStringPropertyManager *stringManager = qobject_cast<QExtStringPropertyManager *>(manager)) {
        return stringManager->value(internProp);
    } else if (QExtDatePropertyManager *dateManager = qobject_cast<QExtDatePropertyManager *>(manager)) {
        return dateManager->value(internProp);
    } else if (QExtTimePropertyManager *timeManager = qobject_cast<QExtTimePropertyManager *>(manager)) {
        return timeManager->value(internProp);
    } else if (QExtDateTimePropertyManager *dateTimeManager = qobject_cast<QExtDateTimePropertyManager *>(manager)) {
        return dateTimeManager->value(internProp);
    } else if (QExtKeySequencePropertyManager *keySequenceManager = qobject_cast<QExtKeySequencePropertyManager *>(manager)) {
#if QT_VERSION < 0x050000
        return keySequenceManager->value(internProp);
#else
        return QVariant::fromValue(keySequenceManager->value(internProp));
#endif
    } else if (QExtCharPropertyManager *charManager = qobject_cast<QExtCharPropertyManager *>(manager)) {
        return charManager->value(internProp);
    } else if (QExtLocalePropertyManager *localeManager = qobject_cast<QExtLocalePropertyManager *>(manager)) {
        return localeManager->value(internProp);
    } else if (QExtPointPropertyManager *pointManager = qobject_cast<QExtPointPropertyManager *>(manager)) {
        return pointManager->value(internProp);
    } else if (QExtPointFPropertyManager *pointFManager = qobject_cast<QExtPointFPropertyManager *>(manager)) {
        return pointFManager->value(internProp);
    } else if (QExtSizePropertyManager *sizeManager = qobject_cast<QExtSizePropertyManager *>(manager)) {
        return sizeManager->value(internProp);
    } else if (QExtSizeFPropertyManager *sizeFManager = qobject_cast<QExtSizeFPropertyManager *>(manager)) {
        return sizeFManager->value(internProp);
    } else if (QExtRectPropertyManager *rectManager = qobject_cast<QExtRectPropertyManager *>(manager)) {
        return rectManager->value(internProp);
    } else if (QExtRectFPropertyManager *rectFManager = qobject_cast<QExtRectFPropertyManager *>(manager)) {
        return rectFManager->value(internProp);
    } else if (QExtColorPropertyManager *colorManager = qobject_cast<QExtColorPropertyManager *>(manager)) {
        return colorManager->value(internProp);
    } else if (QExtEnumPropertyManager *enumManager = qobject_cast<QExtEnumPropertyManager *>(manager)) {
        return enumManager->value(internProp);
    } else if (QExtSizePolicyPropertyManager *sizePolicyManager =
               qobject_cast<QExtSizePolicyPropertyManager *>(manager)) {
        return sizePolicyManager->value(internProp);
    } else if (QExtFontPropertyManager *fontManager = qobject_cast<QExtFontPropertyManager *>(manager)) {
        return fontManager->value(internProp);
#ifndef QT_NO_CURSOR
    } else if (QExtCursorPropertyManager *cursorManager = qobject_cast<QExtCursorPropertyManager *>(manager)) {
        return cursorManager->value(internProp);
#endif
    } else if (QExtFlagPropertyManager *flagManager = qobject_cast<QExtFlagPropertyManager *>(manager)) {
        return flagManager->value(internProp);
    }
    return QVariant();
}

/*!
    Returns the given \a property's value type.

    \sa propertyType()
*/
int QExtVariantPropertyManager::valueType(const QExtProperty *property) const
{
    int propType = propertyType(property);
    return valueType(propType);
}

/*!
    \overload

    Returns the value type associated with the given \a propertyType.
*/
int QExtVariantPropertyManager::valueType(int propertyType) const
{
    if (d_ptr->m_typeToValueType.contains(propertyType))
        return d_ptr->m_typeToValueType[propertyType];
    return 0;
}

/*!
    Returns the given \a property's type.

    \sa valueType()
*/
int QExtVariantPropertyManager::propertyType(const QExtProperty *property) const
{
    const QMap<const QExtProperty *, QPair<QExtVariantProperty *, int> >::const_iterator it = d_ptr->m_propertyToType.constFind(property);
    if (it == d_ptr->m_propertyToType.constEnd())
        return 0;
    return it.value().second;
}

/*!
    Returns the given \a property's value for the specified \a
    attribute

    If the given \a property was not created by \e this manager, or if
    the specified \a attribute does not exist, this function returns
    an invalid variant.

    \sa attributes(), attributeType(), setAttribute()
*/
QVariant QExtVariantPropertyManager::attributeValue(const QExtProperty *property, const QString &attribute) const
{
    int propType = propertyType(property);
    if (!propType)
        return QVariant();

    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return QVariant();

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
        return QVariant();

    QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return QVariant();

    QExtAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtIntPropertyManager *intManager = qobject_cast<QExtIntPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return intManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return intManager->minimum(internProp);
        if (attribute == d_ptr->m_singleStepAttribute)
            return intManager->singleStep(internProp);
        if (attribute == d_ptr->m_readOnlyAttribute)
            return intManager->isReadOnly(internProp);
        return QVariant();
    } else if (QExtDoublePropertyManager *doubleManager = qobject_cast<QExtDoublePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return doubleManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return doubleManager->minimum(internProp);
        if (attribute == d_ptr->m_singleStepAttribute)
            return doubleManager->singleStep(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return doubleManager->decimals(internProp);
        if (attribute == d_ptr->m_readOnlyAttribute)
            return doubleManager->isReadOnly(internProp);
        return QVariant();
    } else if (QExtBoolPropertyManager *boolManager = qobject_cast<QExtBoolPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_textVisibleAttribute)
            return boolManager->textVisible(internProp);
        return QVariant();
    } else if (QExtStringPropertyManager *stringManager = qobject_cast<QExtStringPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_regExpAttribute)
            return stringManager->regExp(internProp);
        if (attribute == d_ptr->m_echoModeAttribute)
            return stringManager->echoMode(internProp);
        if (attribute == d_ptr->m_readOnlyAttribute)
            return stringManager->isReadOnly(internProp);
        return QVariant();
    } else if (QExtDatePropertyManager *dateManager = qobject_cast<QExtDatePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return dateManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return dateManager->minimum(internProp);
        return QVariant();
    } else if (QExtPointFPropertyManager *pointFManager = qobject_cast<QExtPointFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_decimalsAttribute)
            return pointFManager->decimals(internProp);
        return QVariant();
    } else if (QExtSizePropertyManager *sizeManager = qobject_cast<QExtSizePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return sizeManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return sizeManager->minimum(internProp);
        return QVariant();
    } else if (QExtSizeFPropertyManager *sizeFManager = qobject_cast<QExtSizeFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            return sizeFManager->maximum(internProp);
        if (attribute == d_ptr->m_minimumAttribute)
            return sizeFManager->minimum(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return sizeFManager->decimals(internProp);
        return QVariant();
    } else if (QExtRectPropertyManager *rectManager = qobject_cast<QExtRectPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            return rectManager->constraint(internProp);
        return QVariant();
    } else if (QExtRectFPropertyManager *rectFManager = qobject_cast<QExtRectFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            return rectFManager->constraint(internProp);
        if (attribute == d_ptr->m_decimalsAttribute)
            return rectFManager->decimals(internProp);
        return QVariant();
    } else if (QExtEnumPropertyManager *enumManager = qobject_cast<QExtEnumPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_enumNamesAttribute)
            return enumManager->enumNames(internProp);
        if (attribute == d_ptr->m_enumIconsAttribute) {
            QVariant v;
            qVariantSetValue(v, enumManager->enumIcons(internProp));
            return v;
        }
        return QVariant();
    } else if (QExtFlagPropertyManager *flagManager = qobject_cast<QExtFlagPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_flagNamesAttribute)
            return flagManager->flagNames(internProp);
        return QVariant();
    }
    return QVariant();
}

/*!
    Returns a list of the given \a propertyType 's attributes.

    \sa attributeValue(), attributeType()
*/
QStringList QExtVariantPropertyManager::attributes(int propertyType) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return QStringList();
    return it.value().keys();
}

/*!
    Returns the type of the specified \a attribute of the given \a
    propertyType.

    If the given \a propertyType is not supported by \e this manager,
    or if the given \a propertyType does not possess the specified \a
    attribute, this function returns QVariant::Invalid.

    \sa attributes(), valueType()
*/
int QExtVariantPropertyManager::attributeType(int propertyType, const QString &attribute) const
{
    QMap<int, QMap<QString, int> >::ConstIterator it =
            d_ptr->m_typeToAttributeToAttributeType.find(propertyType);
    if (it == d_ptr->m_typeToAttributeToAttributeType.constEnd())
        return 0;

    QMap<QString, int> attributes = it.value();
    QMap<QString, int>::ConstIterator itAttr = attributes.find(attribute);
    if (itAttr == attributes.constEnd())
        return 0;
    return itAttr.value();
}

/*!
    \fn void QExtVariantPropertyManager::setValue(QExtProperty *property, const QVariant &value)

    Sets the value of the given \a property to \a value.

    The specified \a value must be of a type returned by valueType(),
    or of type that can be converted to valueType() using the
    QVariant::canConvert() function, otherwise this function does
    nothing.

    \sa value(), QExtVariantProperty::setValue(), valueChanged()
*/
void QExtVariantPropertyManager::setValue(QExtProperty *property, const QVariant &val)
{
    int propType = val.userType();
    if (!propType)
        return;

    int valType = valueType(property);

    if (propType != valType && !val.canConvert(static_cast<QVariant::Type>(valType)))
        return;

    QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return;


    QExtAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtIntPropertyManager *intManager = qobject_cast<QExtIntPropertyManager *>(manager)) {
        intManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    } else if (QExtDoublePropertyManager *doubleManager = qobject_cast<QExtDoublePropertyManager *>(manager)) {
        doubleManager->setValue(internProp, qextVariantValue<double>(val));
        return;
    } else if (QExtBoolPropertyManager *boolManager = qobject_cast<QExtBoolPropertyManager *>(manager)) {
        boolManager->setValue(internProp, qextVariantValue<bool>(val));
        return;
    } else if (QExtStringPropertyManager *stringManager = qobject_cast<QExtStringPropertyManager *>(manager)) {
        stringManager->setValue(internProp, qextVariantValue<QString>(val));
        return;
    } else if (QExtDatePropertyManager *dateManager = qobject_cast<QExtDatePropertyManager *>(manager)) {
        dateManager->setValue(internProp, qextVariantValue<QDate>(val));
        return;
    } else if (QExtTimePropertyManager *timeManager = qobject_cast<QExtTimePropertyManager *>(manager)) {
        timeManager->setValue(internProp, qextVariantValue<QTime>(val));
        return;
    } else if (QExtDateTimePropertyManager *dateTimeManager = qobject_cast<QExtDateTimePropertyManager *>(manager)) {
        dateTimeManager->setValue(internProp, qextVariantValue<QDateTime>(val));
        return;
    } else if (QExtKeySequencePropertyManager *keySequenceManager = qobject_cast<QExtKeySequencePropertyManager *>(manager)) {
        keySequenceManager->setValue(internProp, qextVariantValue<QKeySequence>(val));
        return;
    } else if (QExtCharPropertyManager *charManager = qobject_cast<QExtCharPropertyManager *>(manager)) {
        charManager->setValue(internProp, qextVariantValue<QChar>(val));
        return;
    } else if (QExtLocalePropertyManager *localeManager = qobject_cast<QExtLocalePropertyManager *>(manager)) {
        localeManager->setValue(internProp, qextVariantValue<QLocale>(val));
        return;
    } else if (QExtPointPropertyManager *pointManager = qobject_cast<QExtPointPropertyManager *>(manager)) {
        pointManager->setValue(internProp, qextVariantValue<QPoint>(val));
        return;
    } else if (QExtPointFPropertyManager *pointFManager = qobject_cast<QExtPointFPropertyManager *>(manager)) {
        pointFManager->setValue(internProp, qextVariantValue<QPointF>(val));
        return;
    } else if (QExtSizePropertyManager *sizeManager = qobject_cast<QExtSizePropertyManager *>(manager)) {
        sizeManager->setValue(internProp, qextVariantValue<QSize>(val));
        return;
    } else if (QExtSizeFPropertyManager *sizeFManager = qobject_cast<QExtSizeFPropertyManager *>(manager)) {
        sizeFManager->setValue(internProp, qextVariantValue<QSizeF>(val));
        return;
    } else if (QExtRectPropertyManager *rectManager = qobject_cast<QExtRectPropertyManager *>(manager)) {
        rectManager->setValue(internProp, qextVariantValue<QRect>(val));
        return;
    } else if (QExtRectFPropertyManager *rectFManager = qobject_cast<QExtRectFPropertyManager *>(manager)) {
        rectFManager->setValue(internProp, qextVariantValue<QRectF>(val));
        return;
    } else if (QExtColorPropertyManager *colorManager = qobject_cast<QExtColorPropertyManager *>(manager)) {
        colorManager->setValue(internProp, qextVariantValue<QColor>(val));
        return;
    } else if (QExtEnumPropertyManager *enumManager = qobject_cast<QExtEnumPropertyManager *>(manager)) {
        enumManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    } else if (QExtSizePolicyPropertyManager *sizePolicyManager =
               qobject_cast<QExtSizePolicyPropertyManager *>(manager)) {
        sizePolicyManager->setValue(internProp, qextVariantValue<QSizePolicy>(val));
        return;
    } else if (QExtFontPropertyManager *fontManager = qobject_cast<QExtFontPropertyManager *>(manager)) {
        fontManager->setValue(internProp, qextVariantValue<QFont>(val));
        return;
#ifndef QT_NO_CURSOR
    } else if (QExtCursorPropertyManager *cursorManager = qobject_cast<QExtCursorPropertyManager *>(manager)) {
        cursorManager->setValue(internProp, qextVariantValue<QCursor>(val));
        return;
#endif
    } else if (QExtFlagPropertyManager *flagManager = qobject_cast<QExtFlagPropertyManager *>(manager)) {
        flagManager->setValue(internProp, qextVariantValue<int>(val));
        return;
    }
}

/*!
    Sets the value of the specified \a attribute of the given \a
    property, to \a value.

    The new \a value's type must be of the type returned by
    attributeType(), or of a type that can be converted to
    attributeType() using the QVariant::canConvert() function,
    otherwise this function does nothing.

    \sa attributeValue(), QExtVariantProperty::setAttribute(), attributeChanged()
*/
void QExtVariantPropertyManager::setAttribute(QExtProperty *property,
                                              const QString &attribute, const QVariant &value)
{
    QVariant oldAttr = attributeValue(property, attribute);
    if (!oldAttr.isValid())
        return;

    int attrType = value.userType();
    if (!attrType)
        return;

    if (attrType != attributeType(propertyType(property), attribute) &&
            !value.canConvert((QVariant::Type)attrType))
        return;

    QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    if (internProp == 0)
        return;

    QExtAbstractPropertyManager *manager = internProp->propertyManager();
    if (QExtIntPropertyManager *intManager = qobject_cast<QExtIntPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            intManager->setMaximum(internProp, qextVariantValue<int>(value));
        else if (attribute == d_ptr->m_minimumAttribute)
            intManager->setMinimum(internProp, qextVariantValue<int>(value));
        else if (attribute == d_ptr->m_singleStepAttribute)
            intManager->setSingleStep(internProp, qextVariantValue<int>(value));
        else if (attribute == d_ptr->m_readOnlyAttribute)
            intManager->setReadOnly(internProp, qextVariantValue<bool>(value));
        return;
    } else if (QExtDoublePropertyManager *doubleManager = qobject_cast<QExtDoublePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            doubleManager->setMaximum(internProp, qextVariantValue<double>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            doubleManager->setMinimum(internProp, qextVariantValue<double>(value));
        if (attribute == d_ptr->m_singleStepAttribute)
            doubleManager->setSingleStep(internProp, qextVariantValue<double>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            doubleManager->setDecimals(internProp, qextVariantValue<int>(value));
        if (attribute == d_ptr->m_readOnlyAttribute)
            doubleManager->setReadOnly(internProp, qextVariantValue<bool>(value));
        return;
    } else if (QExtBoolPropertyManager *boolManager = qobject_cast<QExtBoolPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_textVisibleAttribute)
            boolManager->setTextVisible(internProp, qextVariantValue<bool>(value));
        return;
    } else if (QExtStringPropertyManager *stringManager = qobject_cast<QExtStringPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_regExpAttribute)
            stringManager->setRegExp(internProp, qextVariantValue<QRegExp>(value));
        if (attribute == d_ptr->m_echoModeAttribute)
            stringManager->setEchoMode(internProp, (EchoMode)qextVariantValue<int>(value));
        if (attribute == d_ptr->m_readOnlyAttribute)
            stringManager->setReadOnly(internProp, (EchoMode)qextVariantValue<bool>(value));
        return;
    } else if (QExtDatePropertyManager *dateManager = qobject_cast<QExtDatePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            dateManager->setMaximum(internProp, qextVariantValue<QDate>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            dateManager->setMinimum(internProp, qextVariantValue<QDate>(value));
        return;
    } else if (QExtPointFPropertyManager *pointFManager = qobject_cast<QExtPointFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_decimalsAttribute)
            pointFManager->setDecimals(internProp, qextVariantValue<int>(value));
        return;
    } else if (QExtSizePropertyManager *sizeManager = qobject_cast<QExtSizePropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            sizeManager->setMaximum(internProp, qextVariantValue<QSize>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            sizeManager->setMinimum(internProp, qextVariantValue<QSize>(value));
        return;
    } else if (QExtSizeFPropertyManager *sizeFManager = qobject_cast<QExtSizeFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_maximumAttribute)
            sizeFManager->setMaximum(internProp, qextVariantValue<QSizeF>(value));
        if (attribute == d_ptr->m_minimumAttribute)
            sizeFManager->setMinimum(internProp, qextVariantValue<QSizeF>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            sizeFManager->setDecimals(internProp, qextVariantValue<int>(value));
        return;
    } else if (QExtRectPropertyManager *rectManager = qobject_cast<QExtRectPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            rectManager->setConstraint(internProp, qextVariantValue<QRect>(value));
        return;
    } else if (QExtRectFPropertyManager *rectFManager = qobject_cast<QExtRectFPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_constraintAttribute)
            rectFManager->setConstraint(internProp, qextVariantValue<QRectF>(value));
        if (attribute == d_ptr->m_decimalsAttribute)
            rectFManager->setDecimals(internProp, qextVariantValue<int>(value));
        return;
    } else if (QExtEnumPropertyManager *enumManager = qobject_cast<QExtEnumPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_enumNamesAttribute)
            enumManager->setEnumNames(internProp, qextVariantValue<QStringList>(value));
        if (attribute == d_ptr->m_enumIconsAttribute)
            enumManager->setEnumIcons(internProp, qextVariantValue<QtIconMap>(value));
        return;
    } else if (QExtFlagPropertyManager *flagManager = qobject_cast<QExtFlagPropertyManager *>(manager)) {
        if (attribute == d_ptr->m_flagNamesAttribute)
            flagManager->setFlagNames(internProp, qextVariantValue<QStringList>(value));
        return;
    }
}

/*!
    \reimp
*/
bool QExtVariantPropertyManager::hasValue(const QExtProperty *property) const
{
    if (propertyType(property) == groupTypeId())
        return false;
    return true;
}

/*!
    \reimp
*/
QString QExtVariantPropertyManager::valueText(const QExtProperty *property) const
{
    const QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    return internProp ? !internProp->displayText().isEmpty() ? internProp->displayText() : internProp->valueText() : QString();
}

/*!
    \reimp
*/
QIcon QExtVariantPropertyManager::valueIcon(const QExtProperty *property) const
{
    const QExtProperty *internProp = propertyToWrappedProperty()->value(property, 0);
    return internProp ? internProp->valueIcon() : QIcon();
}

/*!
    \reimp
*/
void QExtVariantPropertyManager::initializeProperty(QExtProperty *property)
{
    QExtVariantProperty *varProp = variantProperty(property);
    if (!varProp)
        return;

    QMap<int, QExtAbstractPropertyManager *>::ConstIterator it =
            d_ptr->m_typeToPropertyManager.find(d_ptr->m_propertyType);
    if (it != d_ptr->m_typeToPropertyManager.constEnd()) {
        QExtProperty *internProp = 0;
        if (!d_ptr->m_creatingSubProperties) {
            QExtAbstractPropertyManager *manager = it.value();
            internProp = manager->addProperty();
            d_ptr->m_internalToProperty[internProp] = varProp;
        }
        propertyToWrappedProperty()->insert(varProp, internProp);
        if (internProp) {
            QList<QExtProperty *> children = internProp->subProperties();
            QListIterator<QExtProperty *> itChild(children);
            QExtVariantProperty *lastProperty = 0;
            while (itChild.hasNext()) {
                QExtVariantProperty *prop = d_ptr->createSubProperty(varProp, lastProperty, itChild.next());
                lastProperty = prop ? prop : lastProperty;
            }
        }
    }
}

/*!
    \reimp
*/
void QExtVariantPropertyManager::uninitializeProperty(QExtProperty *property)
{
    const QMap<const QExtProperty *, QPair<QExtVariantProperty *, int> >::iterator type_it = d_ptr->m_propertyToType.find(property);
    if (type_it == d_ptr->m_propertyToType.end())
        return;

    PropertyMap::iterator it = propertyToWrappedProperty()->find(property);
    if (it != propertyToWrappedProperty()->end()) {
        QExtProperty *internProp = it.value();
        if (internProp) {
            d_ptr->m_internalToProperty.remove(internProp);
            if (!d_ptr->m_destroyingSubProperties) {
                delete internProp;
            }
        }
        propertyToWrappedProperty()->erase(it);
    }
    d_ptr->m_propertyToType.erase(type_it);
}

/*!
    \reimp
*/
QExtProperty *QExtVariantPropertyManager::createProperty()
{
    if (!d_ptr->m_creatingProperty)
        return 0;

    QExtVariantProperty *property = new QExtVariantProperty(this);
    d_ptr->m_propertyToType.insert(property, qMakePair(property, d_ptr->m_propertyType));

    return property;
}

/////////////////////////////

class QExtVariantEditorFactoryPrivate
{
    QExtVariantEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QExtVariantEditorFactory)
public:

    QExtSpinBoxFactory           *m_spinBoxFactory;
    QExtDoubleSpinBoxFactory     *m_doubleSpinBoxFactory;
    QExtCheckBoxFactory          *m_checkBoxFactory;
    QExtLineEditFactory          *m_lineEditFactory;
    QExtDateEditFactory          *m_dateEditFactory;
    QExtTimeEditFactory          *m_timeEditFactory;
    QExtDateTimeEditFactory      *m_dateTimeEditFactory;
    QExtKeySequenceEditorFactory *m_keySequenceEditorFactory;
    QExtCharEditorFactory        *m_charEditorFactory;
    QExtEnumEditorFactory        *m_comboBoxFactory;
    QExtCursorEditorFactory      *m_cursorEditorFactory;
    QExtColorEditorFactory       *m_colorEditorFactory;
    QExtFontEditorFactory        *m_fontEditorFactory;

    QMap<QExtAbstractEditorFactoryBase *, int> m_factoryToType;
    QMap<int, QExtAbstractEditorFactoryBase *> m_typeToFactory;
};

/*!
    \class QExtVariantEditorFactory

    \brief The QExtVariantEditorFactory class provides widgets for properties
    created by QExtVariantPropertyManager objects.

    The variant factory provides the following widgets for the
    specified property types:

    \table
    \header
        \o Property Type
        \o Widget
    \row
        \o \c int
        \o QSpinBox
    \row
        \o \c double
        \o QDoubleSpinBox
    \row
        \o \c bool
        \o QCheckBox
    \row
        \o QString
        \o QLineEdit
    \row
        \o QDate
        \o QDateEdit
    \row
        \o QTime
        \o QTimeEdit
    \row
        \o QDateTime
        \o QDateTimeEdit
    \row
        \o QKeySequence
        \o customized editor
    \row
        \o QChar
        \o customized editor
    \row
        \o \c enum
        \o QComboBox
    \row
        \o QCursor
        \o QComboBox
    \endtable

    Note that QExtVariantPropertyManager supports several additional property
    types for which the QExtVariantEditorFactory class does not provide
    editing widgets, e.g. QPoint and QSize. To provide widgets for other
    types using the variant approach, derive from the QExtVariantEditorFactory
    class.

    \sa QExtAbstractEditorFactory, QExtVariantPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QExtVariantEditorFactory::QExtVariantEditorFactory(QObject *parent)
    : QExtAbstractEditorFactory<QExtVariantPropertyManager>(parent)
{
    d_ptr = new QExtVariantEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_spinBoxFactory = new QExtSpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_spinBoxFactory] = QVariant::Int;
    d_ptr->m_typeToFactory[QVariant::Int] = d_ptr->m_spinBoxFactory;

    d_ptr->m_doubleSpinBoxFactory = new QExtDoubleSpinBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_doubleSpinBoxFactory] = QVariant::Double;
    d_ptr->m_typeToFactory[QVariant::Double] = d_ptr->m_doubleSpinBoxFactory;

    d_ptr->m_checkBoxFactory = new QExtCheckBoxFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_checkBoxFactory] = QVariant::Bool;
    d_ptr->m_typeToFactory[QVariant::Bool] = d_ptr->m_checkBoxFactory;

    d_ptr->m_lineEditFactory = new QExtLineEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_lineEditFactory] = QVariant::String;
    d_ptr->m_typeToFactory[QVariant::String] = d_ptr->m_lineEditFactory;

    d_ptr->m_dateEditFactory = new QExtDateEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateEditFactory] = QVariant::Date;
    d_ptr->m_typeToFactory[QVariant::Date] = d_ptr->m_dateEditFactory;

    d_ptr->m_timeEditFactory = new QExtTimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_timeEditFactory] = QVariant::Time;
    d_ptr->m_typeToFactory[QVariant::Time] = d_ptr->m_timeEditFactory;

    d_ptr->m_dateTimeEditFactory = new QExtDateTimeEditFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_dateTimeEditFactory] = QVariant::DateTime;
    d_ptr->m_typeToFactory[QVariant::DateTime] = d_ptr->m_dateTimeEditFactory;

    d_ptr->m_keySequenceEditorFactory = new QExtKeySequenceEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_keySequenceEditorFactory] = QVariant::KeySequence;
    d_ptr->m_typeToFactory[QVariant::KeySequence] = d_ptr->m_keySequenceEditorFactory;

    d_ptr->m_charEditorFactory = new QExtCharEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_charEditorFactory] = QVariant::Char;
    d_ptr->m_typeToFactory[QVariant::Char] = d_ptr->m_charEditorFactory;

    d_ptr->m_cursorEditorFactory = new QExtCursorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_cursorEditorFactory] = QVariant::Cursor;
    d_ptr->m_typeToFactory[QVariant::Cursor] = d_ptr->m_cursorEditorFactory;

    d_ptr->m_colorEditorFactory = new QExtColorEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_colorEditorFactory] = QVariant::Color;
    d_ptr->m_typeToFactory[QVariant::Color] = d_ptr->m_colorEditorFactory;

    d_ptr->m_fontEditorFactory = new QExtFontEditorFactory(this);
    d_ptr->m_factoryToType[d_ptr->m_fontEditorFactory] = QVariant::Font;
    d_ptr->m_typeToFactory[QVariant::Font] = d_ptr->m_fontEditorFactory;

    d_ptr->m_comboBoxFactory = new QExtEnumEditorFactory(this);
    const int enumId = QExtVariantPropertyManager::enumTypeId();
    d_ptr->m_factoryToType[d_ptr->m_comboBoxFactory] = enumId;
    d_ptr->m_typeToFactory[enumId] = d_ptr->m_comboBoxFactory;
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QExtVariantEditorFactory::~QExtVariantEditorFactory()
{
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtVariantEditorFactory::connectPropertyManager(QExtVariantPropertyManager *manager)
{
    QList<QExtIntPropertyManager *> intPropertyManagers = qextFindChildren<QExtIntPropertyManager *>(manager);
    QListIterator<QExtIntPropertyManager *> itInt(intPropertyManagers);
    while (itInt.hasNext())
        d_ptr->m_spinBoxFactory->addPropertyManager(itInt.next());

    QList<QExtDoublePropertyManager *> doublePropertyManagers = qextFindChildren<QExtDoublePropertyManager *>(manager);
    QListIterator<QExtDoublePropertyManager *> itDouble(doublePropertyManagers);
    while (itDouble.hasNext())
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itDouble.next());

    QList<QExtBoolPropertyManager *> boolPropertyManagers = qextFindChildren<QExtBoolPropertyManager *>(manager);
    QListIterator<QExtBoolPropertyManager *> itBool(boolPropertyManagers);
    while (itBool.hasNext())
        d_ptr->m_checkBoxFactory->addPropertyManager(itBool.next());

    QList<QExtStringPropertyManager *> stringPropertyManagers = qextFindChildren<QExtStringPropertyManager *>(manager);
    QListIterator<QExtStringPropertyManager *> itString(stringPropertyManagers);
    while (itString.hasNext())
        d_ptr->m_lineEditFactory->addPropertyManager(itString.next());

    QList<QExtDatePropertyManager *> datePropertyManagers = qextFindChildren<QExtDatePropertyManager *>(manager);
    QListIterator<QExtDatePropertyManager *> itDate(datePropertyManagers);
    while (itDate.hasNext())
        d_ptr->m_dateEditFactory->addPropertyManager(itDate.next());

    QList<QExtTimePropertyManager *> timePropertyManagers = qextFindChildren<QExtTimePropertyManager *>(manager);
    QListIterator<QExtTimePropertyManager *> itTime(timePropertyManagers);
    while (itTime.hasNext())
        d_ptr->m_timeEditFactory->addPropertyManager(itTime.next());

    QList<QExtDateTimePropertyManager *> dateTimePropertyManagers = qextFindChildren<QExtDateTimePropertyManager *>(manager);
    QListIterator<QExtDateTimePropertyManager *> itDateTime(dateTimePropertyManagers);
    while (itDateTime.hasNext())
        d_ptr->m_dateTimeEditFactory->addPropertyManager(itDateTime.next());

    QList<QExtKeySequencePropertyManager *> keySequencePropertyManagers = qextFindChildren<QExtKeySequencePropertyManager *>(manager);
    QListIterator<QExtKeySequencePropertyManager *> itKeySequence(keySequencePropertyManagers);
    while (itKeySequence.hasNext())
        d_ptr->m_keySequenceEditorFactory->addPropertyManager(itKeySequence.next());

    QList<QExtCharPropertyManager *> charPropertyManagers = qextFindChildren<QExtCharPropertyManager *>(manager);
    QListIterator<QExtCharPropertyManager *> itChar(charPropertyManagers);
    while (itChar.hasNext())
        d_ptr->m_charEditorFactory->addPropertyManager(itChar.next());

    QList<QExtLocalePropertyManager *> localePropertyManagers = qextFindChildren<QExtLocalePropertyManager *>(manager);
    QListIterator<QExtLocalePropertyManager *> itLocale(localePropertyManagers);
    while (itLocale.hasNext())
        d_ptr->m_comboBoxFactory->addPropertyManager(itLocale.next()->subEnumPropertyManager());

    QList<QExtPointPropertyManager *> pointPropertyManagers = qextFindChildren<QExtPointPropertyManager *>(manager);
    QListIterator<QExtPointPropertyManager *> itPoint(pointPropertyManagers);
    while (itPoint.hasNext())
        d_ptr->m_spinBoxFactory->addPropertyManager(itPoint.next()->subIntPropertyManager());

    QList<QExtPointFPropertyManager *> pointFPropertyManagers = qextFindChildren<QExtPointFPropertyManager *>(manager);
    QListIterator<QExtPointFPropertyManager *> itPointF(pointFPropertyManagers);
    while (itPointF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itPointF.next()->subDoublePropertyManager());

    QList<QExtSizePropertyManager *> sizePropertyManagers = qextFindChildren<QExtSizePropertyManager *>(manager);
    QListIterator<QExtSizePropertyManager *> itSize(sizePropertyManagers);
    while (itSize.hasNext())
        d_ptr->m_spinBoxFactory->addPropertyManager(itSize.next()->subIntPropertyManager());

    QList<QExtSizeFPropertyManager *> sizeFPropertyManagers = qextFindChildren<QExtSizeFPropertyManager *>(manager);
    QListIterator<QExtSizeFPropertyManager *> itSizeF(sizeFPropertyManagers);
    while (itSizeF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itSizeF.next()->subDoublePropertyManager());

    QList<QExtRectPropertyManager *> rectPropertyManagers = qextFindChildren<QExtRectPropertyManager *>(manager);
    QListIterator<QExtRectPropertyManager *> itRect(rectPropertyManagers);
    while (itRect.hasNext())
        d_ptr->m_spinBoxFactory->addPropertyManager(itRect.next()->subIntPropertyManager());

    QList<QExtRectFPropertyManager *> rectFPropertyManagers = qextFindChildren<QExtRectFPropertyManager *>(manager);
    QListIterator<QExtRectFPropertyManager *> itRectF(rectFPropertyManagers);
    while (itRectF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->addPropertyManager(itRectF.next()->subDoublePropertyManager());

    QList<QExtColorPropertyManager *> colorPropertyManagers = qextFindChildren<QExtColorPropertyManager *>(manager);
    QListIterator<QExtColorPropertyManager *> itColor(colorPropertyManagers);
    while (itColor.hasNext()) {
        QExtColorPropertyManager *manager = itColor.next();
        d_ptr->m_colorEditorFactory->addPropertyManager(manager);
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
    }

    QList<QExtEnumPropertyManager *> enumPropertyManagers = qextFindChildren<QExtEnumPropertyManager *>(manager);
    QListIterator<QExtEnumPropertyManager *> itEnum(enumPropertyManagers);
    while (itEnum.hasNext())
        d_ptr->m_comboBoxFactory->addPropertyManager(itEnum.next());

    QList<QExtSizePolicyPropertyManager *> sizePolicyPropertyManagers = qextFindChildren<QExtSizePolicyPropertyManager *>(manager);
    QListIterator<QExtSizePolicyPropertyManager *> itSizePolicy(sizePolicyPropertyManagers);
    while (itSizePolicy.hasNext()) {
        QExtSizePolicyPropertyManager *manager = itSizePolicy.next();
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->addPropertyManager(manager->subEnumPropertyManager());
    }

    QList<QExtFontPropertyManager *> fontPropertyManagers = qextFindChildren<QExtFontPropertyManager *>(manager);
    QListIterator<QExtFontPropertyManager *> itFont(fontPropertyManagers);
    while (itFont.hasNext()) {
        QExtFontPropertyManager *manager = itFont.next();
        d_ptr->m_fontEditorFactory->addPropertyManager(manager);
        d_ptr->m_spinBoxFactory->addPropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->addPropertyManager(manager->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->addPropertyManager(manager->subBoolPropertyManager());
    }

    QList<QExtCursorPropertyManager *> cursorPropertyManagers = qextFindChildren<QExtCursorPropertyManager *>(manager);
    QListIterator<QExtCursorPropertyManager *> itCursor(cursorPropertyManagers);
    while (itCursor.hasNext())
        d_ptr->m_cursorEditorFactory->addPropertyManager(itCursor.next());

    QList<QExtFlagPropertyManager *> flagPropertyManagers = qextFindChildren<QExtFlagPropertyManager *>(manager);
    QListIterator<QExtFlagPropertyManager *> itFlag(flagPropertyManagers);
    while (itFlag.hasNext())
        d_ptr->m_checkBoxFactory->addPropertyManager(itFlag.next()->subBoolPropertyManager());
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
QWidget *QExtVariantEditorFactory::createEditor(QExtVariantPropertyManager *manager, QExtProperty *property,
                                                QWidget *parent)
{
    const int propType = manager->propertyType(property);
    QExtAbstractEditorFactoryBase *factory = d_ptr->m_typeToFactory.value(propType, 0);
    if (!factory)
        return 0;
    return factory->createEditor(wrappedProperty(property), parent);
}

/*!
    \internal

    Reimplemented from the QExtAbstractEditorFactory class.
*/
void QExtVariantEditorFactory::disconnectPropertyManager(QExtVariantPropertyManager *manager)
{
    QList<QExtIntPropertyManager *> intPropertyManagers = qextFindChildren<QExtIntPropertyManager *>(manager);
    QListIterator<QExtIntPropertyManager *> itInt(intPropertyManagers);
    while (itInt.hasNext())
        d_ptr->m_spinBoxFactory->removePropertyManager(itInt.next());

    QList<QExtDoublePropertyManager *> doublePropertyManagers = qextFindChildren<QExtDoublePropertyManager *>(manager);
    QListIterator<QExtDoublePropertyManager *> itDouble(doublePropertyManagers);
    while (itDouble.hasNext())
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itDouble.next());

    QList<QExtBoolPropertyManager *> boolPropertyManagers = qextFindChildren<QExtBoolPropertyManager *>(manager);
    QListIterator<QExtBoolPropertyManager *> itBool(boolPropertyManagers);
    while (itBool.hasNext())
        d_ptr->m_checkBoxFactory->removePropertyManager(itBool.next());

    QList<QExtStringPropertyManager *> stringPropertyManagers = qextFindChildren<QExtStringPropertyManager *>(manager);
    QListIterator<QExtStringPropertyManager *> itString(stringPropertyManagers);
    while (itString.hasNext())
        d_ptr->m_lineEditFactory->removePropertyManager(itString.next());

    QList<QExtDatePropertyManager *> datePropertyManagers = qextFindChildren<QExtDatePropertyManager *>(manager);
    QListIterator<QExtDatePropertyManager *> itDate(datePropertyManagers);
    while (itDate.hasNext())
        d_ptr->m_dateEditFactory->removePropertyManager(itDate.next());

    QList<QExtTimePropertyManager *> timePropertyManagers = qextFindChildren<QExtTimePropertyManager *>(manager);
    QListIterator<QExtTimePropertyManager *> itTime(timePropertyManagers);
    while (itTime.hasNext())
        d_ptr->m_timeEditFactory->removePropertyManager(itTime.next());

    QList<QExtDateTimePropertyManager *> dateTimePropertyManagers = qextFindChildren<QExtDateTimePropertyManager *>(manager);
    QListIterator<QExtDateTimePropertyManager *> itDateTime(dateTimePropertyManagers);
    while (itDateTime.hasNext())
        d_ptr->m_dateTimeEditFactory->removePropertyManager(itDateTime.next());

    QList<QExtKeySequencePropertyManager *> keySequencePropertyManagers = qextFindChildren<QExtKeySequencePropertyManager *>(manager);
    QListIterator<QExtKeySequencePropertyManager *> itKeySequence(keySequencePropertyManagers);
    while (itKeySequence.hasNext())
        d_ptr->m_keySequenceEditorFactory->removePropertyManager(itKeySequence.next());

    QList<QExtCharPropertyManager *> charPropertyManagers = qextFindChildren<QExtCharPropertyManager *>(manager);
    QListIterator<QExtCharPropertyManager *> itChar(charPropertyManagers);
    while (itChar.hasNext())
        d_ptr->m_charEditorFactory->removePropertyManager(itChar.next());

    QList<QExtLocalePropertyManager *> localePropertyManagers = qextFindChildren<QExtLocalePropertyManager *>(manager);
    QListIterator<QExtLocalePropertyManager *> itLocale(localePropertyManagers);
    while (itLocale.hasNext())
        d_ptr->m_comboBoxFactory->removePropertyManager(itLocale.next()->subEnumPropertyManager());

    QList<QExtPointPropertyManager *> pointPropertyManagers = qextFindChildren<QExtPointPropertyManager *>(manager);
    QListIterator<QExtPointPropertyManager *> itPoint(pointPropertyManagers);
    while (itPoint.hasNext())
        d_ptr->m_spinBoxFactory->removePropertyManager(itPoint.next()->subIntPropertyManager());

    QList<QExtPointFPropertyManager *> pointFPropertyManagers = qextFindChildren<QExtPointFPropertyManager *>(manager);
    QListIterator<QExtPointFPropertyManager *> itPointF(pointFPropertyManagers);
    while (itPointF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itPointF.next()->subDoublePropertyManager());

    QList<QExtSizePropertyManager *> sizePropertyManagers = qextFindChildren<QExtSizePropertyManager *>(manager);
    QListIterator<QExtSizePropertyManager *> itSize(sizePropertyManagers);
    while (itSize.hasNext())
        d_ptr->m_spinBoxFactory->removePropertyManager(itSize.next()->subIntPropertyManager());

    QList<QExtSizeFPropertyManager *> sizeFPropertyManagers = qextFindChildren<QExtSizeFPropertyManager *>(manager);
    QListIterator<QExtSizeFPropertyManager *> itSizeF(sizeFPropertyManagers);
    while (itSizeF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itSizeF.next()->subDoublePropertyManager());

    QList<QExtRectPropertyManager *> rectPropertyManagers = qextFindChildren<QExtRectPropertyManager *>(manager);
    QListIterator<QExtRectPropertyManager *> itRect(rectPropertyManagers);
    while (itRect.hasNext())
        d_ptr->m_spinBoxFactory->removePropertyManager(itRect.next()->subIntPropertyManager());

    QList<QExtRectFPropertyManager *> rectFPropertyManagers = qextFindChildren<QExtRectFPropertyManager *>(manager);
    QListIterator<QExtRectFPropertyManager *> itRectF(rectFPropertyManagers);
    while (itRectF.hasNext())
        d_ptr->m_doubleSpinBoxFactory->removePropertyManager(itRectF.next()->subDoublePropertyManager());

    QList<QExtColorPropertyManager *> colorPropertyManagers = qextFindChildren<QExtColorPropertyManager *>(manager);
    QListIterator<QExtColorPropertyManager *> itColor(colorPropertyManagers);
    while (itColor.hasNext()) {
        QExtColorPropertyManager *manager = itColor.next();
        d_ptr->m_colorEditorFactory->removePropertyManager(manager);
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
    }

    QList<QExtEnumPropertyManager *> enumPropertyManagers = qextFindChildren<QExtEnumPropertyManager *>(manager);
    QListIterator<QExtEnumPropertyManager *> itEnum(enumPropertyManagers);
    while (itEnum.hasNext())
        d_ptr->m_comboBoxFactory->removePropertyManager(itEnum.next());

    QList<QExtSizePolicyPropertyManager *> sizePolicyPropertyManagers = qextFindChildren<QExtSizePolicyPropertyManager *>(manager);
    QListIterator<QExtSizePolicyPropertyManager *> itSizePolicy(sizePolicyPropertyManagers);
    while (itSizePolicy.hasNext()) {
        QExtSizePolicyPropertyManager *manager = itSizePolicy.next();
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(manager->subEnumPropertyManager());
    }

    QList<QExtFontPropertyManager *> fontPropertyManagers = qextFindChildren<QExtFontPropertyManager *>(manager);
    QListIterator<QExtFontPropertyManager *> itFont(fontPropertyManagers);
    while (itFont.hasNext()) {
        QExtFontPropertyManager *manager = itFont.next();
        d_ptr->m_fontEditorFactory->removePropertyManager(manager);
        d_ptr->m_spinBoxFactory->removePropertyManager(manager->subIntPropertyManager());
        d_ptr->m_comboBoxFactory->removePropertyManager(manager->subEnumPropertyManager());
        d_ptr->m_checkBoxFactory->removePropertyManager(manager->subBoolPropertyManager());
    }

    QList<QExtCursorPropertyManager *> cursorPropertyManagers = qextFindChildren<QExtCursorPropertyManager *>(manager);
    QListIterator<QExtCursorPropertyManager *> itCursor(cursorPropertyManagers);
    while (itCursor.hasNext())
        d_ptr->m_cursorEditorFactory->removePropertyManager(itCursor.next());

    QList<QExtFlagPropertyManager *> flagPropertyManagers = qextFindChildren<QExtFlagPropertyManager *>(manager);
    QListIterator<QExtFlagPropertyManager *> itFlag(flagPropertyManagers);
    while (itFlag.hasNext())
        d_ptr->m_checkBoxFactory->removePropertyManager(itFlag.next()->subBoolPropertyManager());
}


#include "moc_qextPropertyBrowser.cpp"
