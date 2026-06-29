#include <private/qextKeyboardInputContext_p.h>
#include <qextPinyinInputMethod.h>
#include <qextKeyboardLayout.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QInputDialog>
#include <QWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QScreen>
#include <QThread>

#define WINDOW_HEIGHT QApplication::desktop()->height()

QExtKeyboardInputContextPrivate::QExtKeyboardInputContextPrivate(QExtKeyboardInputContext *q)
    : q_ptr(q)
    , mVisible(false)
    , mNeedHiden(true)
    , mFilterEvent(QEXT_NULLPTR)
    , mFocusObject(QEXT_NULLPTR)
    , mInputPanel(QEXT_NULLPTR)
{
    mInputPanelSize = QSize(800, 600);
    mInputPanelPopupMode = QExtKeyboardInputContext::PopupMode_BottomCenter;
    mEditableWidgetClassNames << "QLineEdit"
                              << "QTextEdit"
                              << "QPlainTextEdit"
                              << "QAbstractSpinBox"
                              << "QComboBox"
                              << "QQuickWidget"
                              << "QWebView"
                              << "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget";
    mReadonlyWidgetClassNames << "QAbstractItemView"
                              << "QPushButton"
                              << "QFrame";
    mEditablePropertyNames << "editable";
    mReadonlyPropertyNames << "noinput"
                           << "readOnly";
}

QExtKeyboardInputContextPrivate::~QExtKeyboardInputContextPrivate()
{
}

QExtKeyboardInputContext::QExtKeyboardInputContext()
    : QPlatformInputContext()
    , dd_ptr(new QExtKeyboardInputContextPrivate(this))
{
    Q_D(QExtKeyboardInputContext);
    d->mInputMethod = new QExtPinyinInputMethod(this);
    qobject_cast<QExtPinyinInputMethod*>(d->mInputMethod)->setInputContext(this);
    d->mInputMethodHints = Qt::ImhNone;
    QExtKeyboardLayout().LoadLayout(":/QExtKeyboard/layout/main.json");
}

QExtKeyboardInputContext *QExtKeyboardInputContext::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtKeyboardInputContext *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtKeyboardInputContext;
        onceFlag.leave();
    }
    return instance;
}

QExtKeyboardInputContext::~QExtKeyboardInputContext()
{
    qCDebug(QExtKeyboard) << "~QExtKeyboardInputContext()";
}

bool QExtKeyboardInputContext::isValid() const
{
    return true;
}

QRectF QExtKeyboardInputContext::keyboardRect() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->mInputPanel ? d->mInputPanel->rect() : QRect();
}

bool QExtKeyboardInputContext::isAnimating() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->mInputPanel ? d->mInputPanel->isAnimating() : false;
}

void QExtKeyboardInputContext::commit(const QString &text, int replaceFrom, int replaceLength)
{
    QList<QInputMethodEvent::Attribute> attributes;
    //attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Selection,0,0,QVariant()));

    QInputMethodEvent inputEvent(QString(), attributes);
    inputEvent.setCommitString(text, replaceFrom, replaceLength);
    this->sendEvent(&inputEvent);
}

void QExtKeyboardInputContext::commit()
{
}

void QExtKeyboardInputContext::showInputPanel()
{
    Q_D(QExtKeyboardInputContext);
    qCDebug(QExtKeyboard) << "[QExtKbd::showInputPanel] ENTER mVisible=" << d->mVisible
                          << "panel=" << (d->mInputPanel ? (d->mInputPanel->isVisible() ? "visible" : "hidden") : "null");
    d->mVisible = true;
    if (d->mInputPanel && d->mInputPanelPopupMode == PopupMode_BottomCenter)
    {
        qCDebug(QExtKeyboard) << "[QExtKbd::showInputPanel] → direct animationShow() (bypass isVisible check)";
        d->mInputPanel->animationShow();
    }
    else
    {
        this->updateInputPanelVisible();
    }
    //    this->updateInputPanelVisible();
    qCDebug(QExtKeyboard) << "[QExtKbd::showInputPanel] EXIT  mVisible=" << d->mVisible;
}

void QExtKeyboardInputContext::hideInputPanel()
{
    Q_D(QExtKeyboardInputContext);
    qCDebug(QExtKeyboard) << "[QExtKbd::hideInputPanel] ENTER mVisible=" << d->mVisible << "mNeedHiden=" << d->mNeedHiden
                          << "panel=" << (d->mInputPanel ? (d->mInputPanel->isVisible() ? "visible" : "hidden") : "null");
    if (d->mVisible)
    {
        d->mVisible = false;
    }
    if (d->mInputPanel && d->mInputPanelPopupMode == PopupMode_BottomCenter)
    {
        qCDebug(QExtKeyboard) << "[QExtKbd::hideInputPanel] → direct animationHide()";
        d->mInputPanel->animationHide();
    }
    else
    {
        this->updateInputPanelVisible();
    }
    //    this->updateInputPanelVisible();
    d->mInputMethod->reset();
    qCDebug(QExtKeyboard) << "[QExtKbd::hideInputPanel] EXIT  mVisible=" << d->mVisible;
}

bool QExtKeyboardInputContext::isInputPanelVisible() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->mInputPanel ? d->mInputPanel->isVisible() : false;
}

QObject *QExtKeyboardInputContext::focusObject()
{
    Q_D(const QExtKeyboardInputContext);
    return d->mFocusObject;
}

void QExtKeyboardInputContext::setFocusObject(QObject *object)
{
    Q_D(QExtKeyboardInputContext);
    qCDebug(QExtKeyboard) << "[QExtKbd::setFocusObject] object=" << object
                          << (object ? QString(" class=%1 isWidget=%2").arg(object->metaObject()->className()).arg(object->isWidgetType()) : QString(" null"));

    static const int deskWidth = qApp->desktop()->availableGeometry().width();
    static const int deskHeight = qApp->desktop()->availableGeometry().height();
    bool editableWidget = true;
    if (d->mFocusObject != object)
    {
        if (d->mFocusObject)
        {
            if (!d->mPreeditText.isEmpty())
            {
                this->setPreeditText(QString());
            }

            d->mFocusObject->removeEventFilter(this);
        }
        d->mFocusObject = object;
        if (d->mFocusObject)
        {
            if (d->mFocusObject->isWidgetType())
            {
                const QString superClassName = d->mFocusObject->metaObject()->superClass()->className();
                // qCDebug(QExtKeyboard) << "superClassName=" << superClassName;
                if (editableWidget)
                {
                    if (d->mReadonlyWidgetClassNames.contains(superClassName))
                    {
                        // qCDebug(QExtKeyboard) << "ret:readonlyWidget=" << superClassName;
                        editableWidget = false;
                    }
                }

                QStringList::ConstIterator iter;
                if (editableWidget)
                {
                    for (iter = d->mReadonlyPropertyNames.constBegin(); iter != d->mReadonlyPropertyNames.constEnd(); ++iter)
                    {
                        const QVariant property = d->mFocusObject->property((*iter).toLatin1().data());
                        if (property.isValid() && property.toBool())
                        {
                            // qCDebug(QExtKeyboard) << "ret:readonlyProperty=" << (*iter);
                            editableWidget = false;
                        }
                    }
                }
                if (editableWidget)
                {
                    for (iter = d->mEditablePropertyNames.constBegin(); iter != d->mEditablePropertyNames.constEnd(); ++iter)
                    {
                        const QVariant property = d->mFocusObject->property((*iter).toLatin1().data());
                        if (property.isValid() && !property.toBool())
                        {
                            // qCDebug(QExtKeyboard) << "ret:editableProperty=" << (*iter);
                            editableWidget = false;
                        }
                    }
                }

                if (editableWidget)
                {
                    const int deskWidth = qApp->desktop()->availableGeometry().width();
                    const int deskHeight = qApp->desktop()->availableGeometry().height();
                    QWidget *focusWidget = qobject_cast<QWidget *>(d->mFocusObject);
                    const QRect rect = focusWidget->rect();
                    QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
                    pos = focusWidget->mapToGlobal(pos);

                    int x = pos.x();
                    if (x + d->mInputPanelSize.width() > deskWidth)
                    {
                        x = deskWidth - d->mInputPanelSize.width();
                    }

                    int y = pos.y();
                    if (y + d->mInputPanelSize.height() > deskHeight)
                    {
                        y = y - d->mInputPanelSize.height() - rect.height() - 2;
                    }

                    d->mInputPanelFollowPos = QPoint(x, y);
                    qCDebug(QExtKeyboard) << "inputPanelFollowPos=" << d->mInputPanelFollowPos;
                    if (!d->mInputPanel.isNull() && PopupMode_AutoFollow == d->mInputPanelPopupMode)
                    {
                        d->mInputPanel->move(d->mInputPanelFollowPos);
                    }
                }
            }
            d->mFocusObject->installEventFilter(this);
        }
        // emit this->focusObjectChanged();
    }

    qCDebug(QExtKeyboard) << "[QExtKbd::setFocusObject] → calling update(Qt::ImQueryAll)";
    this->update(Qt::ImQueryAll);
}


void QExtKeyboardInputContext::update(Qt::InputMethodQueries queries)
{
    Q_UNUSED(queries);
    Q_D(QExtKeyboardInputContext);

    bool enabled = this->inputMethodQuery(Qt::ImEnabled).toBool();
    qCDebug(QExtKeyboard) << "[QExtKbd::update] enabled=" << enabled
                          << "mVisible=" << d->mVisible << "mNeedHiden=" << d->mNeedHiden
                          << "panel=" << (d->mInputPanel ? (d->mInputPanel->isVisible() ? "vis" : "hid") : "null");
    if (enabled && d->mInputPanel.isNull())
    {
        d->mInputPanel = QExtKeyboardPanel::instance();
        d->mInputPanel->setObjectName("Qt5KeyBoard");
        connect(d->mInputPanel.data(), &QExtKeyboardPanel::hideKeyboard,
                this, &QExtKeyboardInputContext::hideKeyboard);
        connect(d->mInputPanel.data(), &QExtKeyboardPanel::keyPressed,
                d->mInputMethod, &QExtAbstractInputMethod::keyEvent);
        connect(d->mInputPanel.data(), &QExtKeyboardPanel::changeLanguage,
                d->mInputMethod, &QExtAbstractInputMethod::changeLanguage);
        connect(d->mInputPanel.data(), &QExtKeyboardPanel::chooseCandidate,
                d->mInputMethod, &QExtAbstractInputMethod::chooseCandidate);

        connect(d->mInputMethod, &QExtAbstractInputMethod::showCandidateList,
                d->mInputPanel.data(), &QExtKeyboardPanel::setCandidateList);
        connect(d->mInputMethod, &QExtAbstractInputMethod::showLanguageName,
                d->mInputPanel.data(), &QExtKeyboardPanel::setLanguageName);

        d->mInputPanel->setFixedSize(d->mInputPanelSize);
    }

    if (enabled)
    {
        if (d->mVisible)
        {
            qCDebug(QExtKeyboard) << "[QExtKbd::update] → branch: maintain visibility";
            d->mNeedHiden = false;
            this->updateInputPanelVisible();
        }
        else
        {
            qCDebug(QExtKeyboard) << "[QExtKbd::update] → branch: showInputPanel()";
            this->showInputPanel();
        }
    }
    else
    {
        qCDebug(QExtKeyboard) << "[QExtKbd::update] → branch: hideInputPanel()";
        d->mNeedHiden = true;
        this->hideInputPanel();
    }

    Qt::InputMethodHints inputMethodHints = Qt::InputMethodHints(inputMethodQuery(Qt::ImHints).toInt());
    bool newInputMethodHints = inputMethodHints != d->mInputMethodHints;
    d->mInputMethodHints = inputMethodHints;
    if (newInputMethodHints && d->mInputPanel)
    {
        d->mInputPanel->setInputMethodHints(inputMethodHints);
    }
}

void QExtKeyboardInputContext::sendKeyEvent(QKeyEvent *event)
{
    Q_D(QExtKeyboardInputContext);
    const QGuiApplication *app = qApp;
    QWindow *focusWindow = app ? app->focusWindow() : QEXT_NULLPTR;
    if (focusWindow)
    {
        d->mFilterEvent = event;
        QGuiApplication::sendEvent(focusWindow, event);
        d->mFilterEvent = QEXT_NULLPTR;
    }
}

void QExtKeyboardInputContext::sendEvent(QEvent *event)
{
    Q_D(QExtKeyboardInputContext);
    if (d->mFocusObject)
    {
        d->mFilterEvent = event;
        QGuiApplication::sendEvent(d->mFocusObject, event);
        d->mFilterEvent = QEXT_NULLPTR;
    }
}

QSize QExtKeyboardInputContext::inputPanelSize() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->mInputPanelSize;
}

void QExtKeyboardInputContext::setInputPanelSize(const QSize &size)
{
    Q_D(QExtKeyboardInputContext);
    if (size != d->mInputPanelSize)
    {
        d->mInputPanelSize = size;
        if (!d->mInputPanel.isNull())
        {
            d->mInputPanel->setFixedSize(size);
        }
        emit this->inputPanelSizeChanged(size);
    }
}

void QExtKeyboardInputContext::setInputPanelSize(int width, int height)
{
    this->setInputPanelSize(QSize(width, height));
}

QExtKeyboardInputContext::PopupModeEnum QExtKeyboardInputContext::inputPanelPopupMode() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->mInputPanelPopupMode;
}

void QExtKeyboardInputContext::setInputPanelPopupMode(PopupModeEnum mode)
{
    Q_D(QExtKeyboardInputContext);
    if (mode != d->mInputPanelPopupMode)
    {
        d->mInputPanelPopupMode = mode;
        emit this->inputPanelPopupModeChanged(mode);
    }
}

void QExtKeyboardInputContext::hideKeyboard()
{
    Q_D(QExtKeyboardInputContext);
    qCDebug(QExtKeyboard) << "[QExtKbd::hideKeyboard] ENTER mVisible=" << d->mVisible
                          << "panel=" << (d->mInputPanel ? (d->mInputPanel->isVisible() ? "vis" : "hid") : "null");
    if (d->mInputPanel)
    {
        d->mVisible = false;
        d->mInputPanel->hide();
        d->mInputPanel->onHideSymbol();
    }
    qCDebug(QExtKeyboard) << "[QExtKbd::hideKeyboard] EXIT  mVisible=" << d->mVisible;
}


bool testAttribute(const QList<QInputMethodEvent::Attribute> &attributes, QInputMethodEvent::AttributeType attributeType)
{
    for (const QInputMethodEvent::Attribute &attribute : qAsConst(attributes))
    {
        if (attribute.type == attributeType)
        {
            return true;
        }
    }
    return false;
}

void QExtKeyboardInputContext::sendPreedit(const QString &text, const QExtKeyboardInputContext::AttributesList &attributes,
                                           int replaceFrom, int replaceLength)
{
    Q_D(QExtKeyboardInputContext);
    d->mPreeditText = text;

    QInputMethodEvent event(text, attributes);
    const bool replace = replaceFrom != 0 || replaceLength > 0;
    if (replace)
    {
        event.setCommitString(QString(), replaceFrom, replaceLength);
    }

    this->sendEvent(&event);

    // Send also to shadow input if only attributes changed.
    // In this case the update() may not be called, so the shadow
    // input may be out of sync.
    //    if (_shadow.inputItem() && !replace && !text.isEmpty() &&
    //            !textChanged && attributesChanged) {
    //        VIRTUALKEYBOARD_DEBUG() << "QVirtualKeyboardInputContextPrivate::sendPreedit(shadow)"
    //#ifdef SENSITIVE_DEBUG
    //               << text << replaceFrom << replaceLength
    //#endif
    //            ;
    //        event.setAccepted(true);
    //        QGuiApplication::sendEvent(_shadow.inputItem(), &event);
    //}
}

void QExtKeyboardInputContext::updateInputPanelVisible()
{
    Q_D(QExtKeyboardInputContext);
    if (!d->mInputPanel)
    {
        qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] panel=null, return";
        return;
    }

    bool pv = d->mInputPanel->isVisible();
    qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] mVisible=" << d->mVisible << "panel.isVisible=" << pv
                          << "mismatch=" << (d->mVisible != pv) << "mode=" << d->mInputPanelPopupMode;

    if (d->mVisible != pv)
    {
        switch (d->mInputPanelPopupMode)
        {
        case PopupMode_BottomCenter:
        {
            qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] → bottomCenter animationSetVisible(" << d->mVisible << ")";
            d->mInputPanel->animationSetVisible(d->mVisible);
            break;
        }
        case PopupMode_AutoFollow:
        {
            if (d->mVisible)
            {
                qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] → autoFollow show() at" << d->mInputPanelFollowPos;
                d->mInputPanel->move(d->mInputPanelFollowPos);
                d->mInputPanel->show();
            }
            else
            {
                qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] → autoFollow hide()";
                d->mInputPanel->hide();
            }
            break;
        }
        default:
            break;
        }
    }
    else
    {
        qCDebug(QExtKeyboard) << "[QExtKbd::updateInputPanelVisible] → NO-OP (mVisible==isVisible, possible deadlock)";
    }
}

QVariant QExtKeyboardInputContext::inputMethodQuery(Qt::InputMethodQuery query)
{
    QInputMethodQueryEvent event(query);
    this->sendEvent(&event);
    return event.value(query);
}


void QExtKeyboardInputContext::setPreeditText(const QString &text, QExtKeyboardInputContext::AttributesList attributes,
                                              int replaceFrom, int replaceLength)
{
    // Add default attributes
    if (!text.isEmpty())
    {
        if (!testAttribute(attributes, QInputMethodEvent::TextFormat))
        {
            QTextCharFormat textFormat;
            textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
            attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, text.length(), textFormat));
        }
    }
    /*
    else if (d->_forceCursorPosition != -1)
    {
        d->addSelectionAttribute(attributes);
    }
    */

    this->sendPreedit(text, attributes, replaceFrom, replaceLength);
}

void QExtKeyboardInputContext::sendKeyClick(int key, const QString &text, int modifiers)
{
    QKeyEvent pressEvent(QEvent::KeyPress, key, Qt::KeyboardModifiers(modifiers), text);
    QKeyEvent releaseEvent(QEvent::KeyRelease, key, Qt::KeyboardModifiers(modifiers), text);

    this->sendKeyEvent(&pressEvent);
    this->sendKeyEvent(&releaseEvent);
}

