#include <qextInputMethodTrigger.h>
#include <qextKeyboardConstants.h>
#include <qextDateTimeUtils.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QEvent>
#include <QTimer>
#include <QWidget>
#include <QPointer>
#include <QApplication>

class QExtInputMethodTriggerPrivate
{
public:
    explicit QExtInputMethodTriggerPrivate(QExtInputMethodTrigger *q);
    virtual ~QExtInputMethodTriggerPrivate();

    QExtInputMethodTrigger * const q_ptr;

    void updateFocusedWidget(QWidget *widget);

    bool m_touched;
    bool m_pressed;
    qint64 m_touchedTimestamp;
    bool m_autoTriggerInputMethod;
    QPointer<QWidget> m_focusedWidget;
    QStringList m_editableSuperClassNames;

private:
    QEXT_DECL_PUBLIC(QExtInputMethodTrigger)
    QEXT_DISABLE_COPY_MOVE(QExtInputMethodTriggerPrivate)
};

QExtInputMethodTriggerPrivate::QExtInputMethodTriggerPrivate(QExtInputMethodTrigger *q)
    : q_ptr(q)
    , m_touched(false)
    , m_pressed(false)
    , m_touchedTimestamp(0)
    , m_autoTriggerInputMethod(false)
{
    m_editableSuperClassNames << "QLineEdit"
                              << "QTextEdit"
                              << "QSpinBox"
                              << "QComboBox"
                              << "QDoubleSpinBox"
                              << "QPlainTextEdit"
                              << "QAbstractSpinBox"
                              << "QQuickWidget"
                              << "QWebView"
                              << "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget";
}

QExtInputMethodTriggerPrivate::~QExtInputMethodTriggerPrivate()
{
}

void QExtInputMethodTriggerPrivate::updateFocusedWidget(QWidget *widget)
{
    Q_Q(QExtInputMethodTrigger);
    //Finds out if the current focus control is a legally entered control
    if (widget != m_focusedWidget.data())
    {
        bool showKeyboard = false;
        m_focusedWidget = widget;
        if (widget)
        {
            if (!widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_NOINPUT).toBool() &&
                !widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_READONLY).toBool())
            {
                const QMetaObject *metaObject = widget->metaObject();
                while (metaObject)
                {
                    QString superClassName = metaObject->className();
                    if (m_editableSuperClassNames.contains(superClassName))
                    {
                        // qDebug() << "superClassName=" << superClassName;
                        //Determines whether the drop-down box's editable property is true if it is currently a drop-down box
                        if (superClassName != "QComboBox" ||
                            widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_EDITABLE).toBool())
                        {
                            showKeyboard = true;
                            break;
                        }
                    }
                    metaObject = metaObject->superClass();
                }
            }
        }
        if (showKeyboard)
        {

            qint64 timestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
            // qDebug() << "singleShot:showKeyboard:touched:" << timestamp - m_touchedTimestamp;
            if (timestamp - m_touchedTimestamp <= 100)
            {
                QTimer::singleShot(0, q, SLOT(showKeyboard()));
            }
        }
    }
}

QExtInputMethodTrigger *QExtInputMethodTrigger::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtInputMethodTrigger *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtInputMethodTrigger;
        QObject::connect(qApp, SIGNAL(destroyed(QObject*)), instance, SLOT(deleteLater()));
        onceFlag.leave();
    }
    return instance;
}

QExtInputMethodTrigger::~QExtInputMethodTrigger()
{
}

bool QExtInputMethodTrigger::isAutoTriggerInputMethodEnabled() const
{
    Q_D(const QExtInputMethodTrigger);
    return d->m_autoTriggerInputMethod;
}

void QExtInputMethodTrigger::setAutoTriggerInputMethodEnable(bool enable)
{
    Q_D(QExtInputMethodTrigger);
    if (enable != d->m_autoTriggerInputMethod)
    {
        if (d->m_autoTriggerInputMethod)
        {
            qApp->removeEventFilter(this);
        }
        d->m_autoTriggerInputMethod = enable;
        if (d->m_autoTriggerInputMethod)
        {
            qApp->installEventFilter(this);
        }
        emit this->autoTriggerInputMethodEnableChanged(enable);
    }
}

void QExtInputMethodTrigger::showKeyboard()
{
    QInputMethod *inputMethod = QApplication::inputMethod();
    if (inputMethod)
    {
        inputMethod->show();
    }
}

void QExtInputMethodTrigger::hideKeyboard()
{
    QInputMethod *inputMethod = QApplication::inputMethod();
    if (inputMethod)
    {
        inputMethod->hide();
    }
}

QExtInputMethodTrigger::QExtInputMethodTrigger(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtInputMethodTriggerPrivate(this))
{
}

bool QExtInputMethodTrigger::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QExtInputMethodTrigger);
    switch (event->type())
    {
    case QEvent::TouchBegin:
        d->m_touched = true;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchBegin:" << watched;
        break;
    case QEvent::TouchUpdate:
        d->m_touched = true;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchUpdate:" << watched;
        break;
    case QEvent::TouchCancel:
        d->m_touched = false;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchCancel:" << watched;
        break;
    case QEvent::TouchEnd:
        d->m_touched = false;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchEnd:" << watched;
        break;
    default:
    {
        if (watched && watched->isWidgetType())
        {
            QWidget *widget = qobject_cast<QWidget *>(watched);
            if (widget)
            {
                switch (event->type())
                {
                case QEvent::MouseButtonPress:
                    d->m_pressed = true;
                    // qDebug() << "QExtInputMethodTrigger::eventFilter():MouseButtonPress:" << widget;
                    break;
                case QEvent::MouseButtonRelease:
                    d->m_pressed = false;
                    // qDebug() << "QExtInputMethodTrigger::eventFilter():MouseButtonRelease:" << widget;
                    break;
                case QEvent::FocusIn:
                    d->updateFocusedWidget(widget);
                    // qDebug() << "QExtInputMethodTrigger::eventFilter():FocusIn:" << widget;
                    break;
                case QEvent::FocusOut:
                    d->updateFocusedWidget(QEXT_NULLPTR);
                    // qDebug() << "QExtInputMethodTrigger::eventFilter():FocusOut:" << widget;
                    break;
                default:
                    break;
                }
            }
        }
        break;
    }
    }
    return QObject::eventFilter(watched, event);
}
