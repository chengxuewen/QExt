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

    bool mTouched;
    bool mPressed;
    qint64 mTouchedTimestamp;
    QTimer mShowKeyboardTimer;
    QAtomicInt mShowKeyboardFlag;
    bool mAutoTriggerInputMethod;
    QPointer<QWidget> mFocusedWidget;
    QStringList mEditableSuperClassNames;

private:
    QEXT_DECLARE_PUBLIC(QExtInputMethodTrigger)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtInputMethodTriggerPrivate)
};

QExtInputMethodTriggerPrivate::QExtInputMethodTriggerPrivate(QExtInputMethodTrigger *q)
    : q_ptr(q)
    , mTouched(false)
    , mPressed(false)
    , mTouchedTimestamp(0)
    , mShowKeyboardFlag(false)
    , mAutoTriggerInputMethod(false)
{
    mEditableSuperClassNames << "QLineEdit"
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
    if (widget != mFocusedWidget.data())
    {
        bool showKeyboard = false;
        mFocusedWidget = widget;
        if (widget && widget->isEnabled())
        {
            qCDebug(lcQExtKeyboard) << "widget=" << widget;
            if (!widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_NOINPUT).toBool() &&
                    !widget->property(QExtKeyboardConstants::WIDGET_PROPERTY_READONLY).toBool())
            {
                const QMetaObject *metaObject = widget->metaObject();
                while (metaObject)
                {
                    QString superClassName = metaObject->className();
                    if (mEditableSuperClassNames.contains(superClassName))
                    {
                        qCDebug(lcQExtKeyboard) << "superClassName=" << superClassName;
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
        mShowKeyboardFlag = showKeyboard;
        if (showKeyboard)
        {
            qint64 timestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
            qCDebug(lcQExtKeyboard) << "singleShot:showKeyboard:touched:" << timestamp - mTouchedTimestamp;
            if (timestamp - mTouchedTimestamp <= 1000)
            {
                qCDebug(lcQExtKeyboard) << "mShowKeyboardTimer.start()";
                mShowKeyboardTimer.start();
                return;
            }
        }
        if (mShowKeyboardTimer.isActive())
        {
            mShowKeyboardTimer.stop();
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
    return d->mAutoTriggerInputMethod;
}

void QExtInputMethodTrigger::setAutoTriggerInputMethodEnable(bool enable)
{
    Q_D(QExtInputMethodTrigger);
    if (enable != d->mAutoTriggerInputMethod)
    {
        if (d->mAutoTriggerInputMethod)
        {
            qApp->removeEventFilter(this);
        }
        d->mAutoTriggerInputMethod = enable;
        if (d->mAutoTriggerInputMethod)
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
    qCDebug(lcQExtKeyboard) << "onShowKeyboardTimerTimeout():" << d->mShowKeyboardFlag.loadAcquire();
    if (d->mShowKeyboardFlag.loadAcquire())
    {
        this->showKeyboard();
    }
}

QExtInputMethodTrigger::QExtInputMethodTrigger(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtInputMethodTriggerPrivate(this))
{
    Q_D(QExtInputMethodTrigger);
    d->mShowKeyboardTimer.setInterval(100);
    d->mShowKeyboardTimer.setSingleShot(true);
    connect(&d->mShowKeyboardTimer, SIGNAL(timeout()), this, SLOT(onShowKeyboardTimerTimeout()));
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
        d->mTouched = true;
        d->mTouchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():TouchBegin:" << watched;
        break;
    }
    case QEvent::TouchUpdate:
    {
        d->mTouched = true;
        d->mTouchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():TouchUpdate:" << watched;
        break;
    }
    case QEvent::TouchCancel:
    {
        d->mTouched = false;
        d->mTouchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():TouchCancel:" << watched;
        break;
    }
    case QEvent::TouchEnd:
    {
        d->mTouched = false;
        d->mTouchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
        qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():TouchEnd:" << watched;
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
                {
                    //                    d->mPressed = true;
                    const QString className = watched->metaObject()->className();
                    if (className.contains("QQuickText"))
                    {
                        d->mPressed = true;
                        d->mTouchedTimestamp = QExtDateTimeUtils::msecsTimeSinceEpoch();
                        this->showKeyboard();
                    }
                    qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():MouseButtonPress:" << widget;
                    break;
                }
                case QEvent::MouseButtonRelease:
                {
                    d->mPressed = false;
                    qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():MouseButtonRelease:" << widget;
                    break;
                }
                case QEvent::FocusIn:
                {
                    d->updateFocusedWidget(widget);
                    qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():FocusIn:" << widget;
                    break;
                }
                case QEvent::FocusOut:
                {
                    d->updateFocusedWidget(QEXT_NULLPTR);
                    qCDebug(lcQExtKeyboard) << "QExtInputMethodTrigger::eventFilter():FocusOut:" << widget;
                    break;
                }
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
