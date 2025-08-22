#include <qextInputMethodTrigger.h>
#include <qextKeyboardConstants.h>
#include <qextSystemKeyboard.h>
#include <qextDateTimeUtils.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QEvent>
#include <QTimer>
#include <QWidget>
#include <QPointer>
#include <QComboBox>
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
    QTimer m_showKeyboardTimer;
    QAtomicInt m_showKeyboardFlag;
    bool m_autoTriggerInputMethod;
    QPointer<QWidget> m_focusedWidget;
    QStringList m_editableSuperClassNames;

private:
    QEXT_DECLARE_PUBLIC(QExtInputMethodTrigger)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtInputMethodTriggerPrivate)
};

QExtInputMethodTriggerPrivate::QExtInputMethodTriggerPrivate(QExtInputMethodTrigger *q)
    : q_ptr(q)
    , m_touched(false)
    , m_pressed(false)
    , m_touchedTimestamp(0)
    , m_showKeyboardFlag(false)
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
        if (widget && widget->isEnabled())
        {
            // qDebug() << "widget=" << widget;
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
                        QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
                        if (!comboBox || widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_EDITABLE).toBool())
                        {
                            showKeyboard = true;
                            break;
                        }
                    }
                    metaObject = metaObject->superClass();
                }
            }
        }
        m_showKeyboardFlag = showKeyboard;
        if (showKeyboard)
        {
            qint64 timestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
            // qDebug() << "singleShot:showKeyboard:touched:" << timestamp - m_touchedTimestamp;
            if (timestamp - m_touchedTimestamp <= 1000)
            {
                // qDebug() << "m_showKeyboardTimer.start()";
                m_showKeyboardTimer.start();
                return;
            }
        }
        if (m_showKeyboardTimer.isActive())
        {
            m_showKeyboardTimer.stop();
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

void QExtInputMethodTrigger::onShowKeyboardTimerTimeout()
{
    Q_D(QExtInputMethodTrigger);
    // qDebug() << "onShowKeyboardTimerTimeout():" << d->m_showKeyboardFlag.loadAcquire();
    if (d->m_showKeyboardFlag.loadAcquire())
    {
        this->showKeyboard();
    }
}

QExtInputMethodTrigger::QExtInputMethodTrigger(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtInputMethodTriggerPrivate(this))
{
    Q_D(QExtInputMethodTrigger);
    d->m_showKeyboardTimer.setInterval(100);
    d->m_showKeyboardTimer.setSingleShot(true);
    connect(&d->m_showKeyboardTimer, SIGNAL(timeout()), this, SLOT(onShowKeyboardTimerTimeout()));
}

bool QExtInputMethodTrigger::eventFilter(QObject *watched, QEvent *event)
{
    QEXT_WARNING_PUSH
    QEXT_WARNING_DISABLE_MSVC(4061)
    Q_D(QExtInputMethodTrigger);
    switch (event->type())
    {
    case QEvent::TouchBegin:
    {
        d->m_touched = true;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchBegin:" << watched;
        break;
    }
    case QEvent::TouchUpdate:
    {
        d->m_touched = true;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchUpdate:" << watched;
        break;
    }
    case QEvent::TouchCancel:
    {
        d->m_touched = false;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchCancel:" << watched;
        break;
    }
    case QEvent::TouchEnd:
    {
        d->m_touched = false;
        d->m_touchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        // qDebug() << "QExtInputMethodTrigger::eventFilter():TouchEnd:" << watched;
        break;
    }
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
    QEXT_WARNING_POP
}
