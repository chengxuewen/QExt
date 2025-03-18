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
    , m_visible(false)
    , m_needHiden(true)
    , m_filterEvent(QEXT_NULLPTR)
    , m_focusObject(QEXT_NULLPTR)
    , m_inputPanel(QEXT_NULLPTR)
{
    m_inputPanelSize = QSize(800, 600);
    m_inputPanelPopupMode = QExtKeyboardInputContext::PopupMode_BottomCenter;
    m_editableWidgetClassNames << "QLineEdit"
                               << "QTextEdit"
                               << "QPlainTextEdit"
                               << "QAbstractSpinBox"
                               << "QComboBox"
                               << "QQuickWidget"
                               << "QWebView"
                               << "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget";
    m_readonlyWidgetClassNames << "QAbstractItemView"
                               << "QPushButton"
                               << "QFrame";
    m_editablePropertyNames << "editable";
    m_readonlyPropertyNames << "noinput"
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
    d->m_inputMethod = new QExtPinyinInputMethod(this);
    qobject_cast<QExtPinyinInputMethod*>(d->m_inputMethod)->setInputContext(this);
    d->m_inputMethodHints = Qt::ImhNone;
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
    qDebug() << "~QExtKeyboardInputContext()";
}

bool QExtKeyboardInputContext::isValid() const
{
    return true;
}

QRectF QExtKeyboardInputContext::keyboardRect() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->m_inputPanel ? d->m_inputPanel->rect() : QRect();
}

bool QExtKeyboardInputContext::isAnimating() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->m_inputPanel ? d->m_inputPanel->isAnimating() : false;
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
    if (!d->m_visible)
    {
        d->m_visible = true;
    }
    this->updateInputPanelVisible();
}

void QExtKeyboardInputContext::hideInputPanel()
{
    Q_D(QExtKeyboardInputContext);
    if (d->m_visible && d->m_needHiden)
    {
        d->m_visible = false;
    }

    this->updateInputPanelVisible();
    d->m_inputMethod->reset();
}

bool QExtKeyboardInputContext::isInputPanelVisible() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->m_inputPanel ? d->m_inputPanel->isVisible() : false;
}

QObject *QExtKeyboardInputContext::focusObject()
{
    Q_D(const QExtKeyboardInputContext);
    return d->m_focusObject;
}

void QExtKeyboardInputContext::setFocusObject(QObject *object)
{
    Q_D(QExtKeyboardInputContext);
    static const int deskWidth = qApp->desktop()->availableGeometry().width();
    static const int deskHeight = qApp->desktop()->availableGeometry().height();
    bool editableWidget = true;
    if (d->m_focusObject != object)
    {
        if (d->m_focusObject)
        {
            if (!d->m_preeditText.isEmpty())
            {
                this->setPreeditText(QString());
            }

            d->m_focusObject->removeEventFilter(this);
        }
        d->m_focusObject = object;
        if (d->m_focusObject)
        {
            if (d->m_focusObject->isWidgetType())
            {
                const QString superClassName = d->m_focusObject->metaObject()->superClass()->className();
                // qDebug() << "superClassName=" << superClassName;
                if (editableWidget)
                {
                    if (d->m_readonlyWidgetClassNames.contains(superClassName))
                    {
                        // qDebug() << "ret:readonlyWidget=" << superClassName;
                        editableWidget = false;
                    }
                }

                QStringList::ConstIterator iter;
                if (editableWidget)
                {
                    for (iter = d->m_readonlyPropertyNames.constBegin(); iter != d->m_readonlyPropertyNames.constEnd(); ++iter)
                    {
                        const QVariant property = d->m_focusObject->property((*iter).toLatin1().data());
                        if (property.isValid() && property.toBool())
                        {
                            // qDebug() << "ret:readonlyProperty=" << (*iter);
                            editableWidget = false;
                        }
                    }
                }
                if (editableWidget)
                {
                    for (iter = d->m_editablePropertyNames.constBegin(); iter != d->m_editablePropertyNames.constEnd(); ++iter)
                    {
                        const QVariant property = d->m_focusObject->property((*iter).toLatin1().data());
                        if (property.isValid() && !property.toBool())
                        {
                            // qDebug() << "ret:editableProperty=" << (*iter);
                            editableWidget = false;
                        }
                    }
                }

                if (editableWidget)
                {
                    const int deskWidth = qApp->desktop()->availableGeometry().width();
                    const int deskHeight = qApp->desktop()->availableGeometry().height();
                    QWidget *focusWidget = qobject_cast<QWidget *>(d->m_focusObject);
                    const QRect rect = focusWidget->rect();
                    QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
                    pos = focusWidget->mapToGlobal(pos);

                    int x = pos.x();
                    if (x + d->m_inputPanelSize.width() > deskWidth)
                    {
                        x = deskWidth - d->m_inputPanelSize.width();
                    }

                    int y = pos.y();
                    if (y + d->m_inputPanelSize.height() > deskHeight)
                    {
                        y = y - d->m_inputPanelSize.height() - rect.height() - 2;
                    }

                    d->m_inputPanelFollowPos = QPoint(x, y);
                    // qDebug() << "inputPanelFollowPos=" << d->m_inputPanelFollowPos;
                    if (!d->m_inputPanel.isNull() && PopupMode_AutoFollow == d->m_inputPanelPopupMode)
                    {
                        d->m_inputPanel->move(d->m_inputPanelFollowPos);
                    }
                }
            }
            d->m_focusObject->installEventFilter(this);
        }
        // emit this->focusObjectChanged();
    }

    this->update(Qt::ImQueryAll);
}


void QExtKeyboardInputContext::update(Qt::InputMethodQueries queries)
{
    Q_UNUSED(queries);
    Q_D(QExtKeyboardInputContext);

    bool enabled = this->inputMethodQuery(Qt::ImEnabled).toBool();
    // qDebug() << "enabled=" << enabled << ", queries=" << queries;
    if (enabled && d->m_inputPanel.isNull())
    {
        d->m_inputPanel = QExtKeyboardPanel::instance();
        d->m_inputPanel->setObjectName("Qt5KeyBoard");
        connect(d->m_inputPanel.data(), &QExtKeyboardPanel::hideKeyboard,
                this, &QExtKeyboardInputContext::hideKeyboard);
        connect(d->m_inputPanel.data(), &QExtKeyboardPanel::keyPressed,
                d->m_inputMethod, &QExtAbstractInputMethod::keyEvent);
        connect(d->m_inputPanel.data(), &QExtKeyboardPanel::changeLanguage,
                d->m_inputMethod, &QExtAbstractInputMethod::changeLanguage);
        connect(d->m_inputPanel.data(), &QExtKeyboardPanel::chooseCandidate,
                d->m_inputMethod, &QExtAbstractInputMethod::chooseCandidate);

        connect(d->m_inputMethod, &QExtAbstractInputMethod::showCandidateList,
                d->m_inputPanel.data(), &QExtKeyboardPanel::setCandidateList);
        connect(d->m_inputMethod, &QExtAbstractInputMethod::showLanguageName,
                d->m_inputPanel.data(), &QExtKeyboardPanel::setLanguageName);

        d->m_inputPanel->setFixedSize(d->m_inputPanelSize);
    }

    //if (m_inputContext) {
    if (enabled)
    {
        //m_inputContext->priv()->update(queries);
        if (d->m_visible)
        {
            d->m_needHiden = false;
            this->updateInputPanelVisible();
        }
    }
    else
    {
        d->m_needHiden = true;
        this->hideInputPanel();
    }
    // m_inputContext->priv()->setFocus(enabled);
    //}

    Qt::InputMethodHints inputMethodHints = Qt::InputMethodHints(inputMethodQuery(Qt::ImHints).toInt());
    bool newInputMethodHints = inputMethodHints != d->m_inputMethodHints;
    d->m_inputMethodHints = inputMethodHints;
    if (newInputMethodHints && d->m_inputPanel)
    {
        d->m_inputPanel->setInputMethodHints(inputMethodHints);
    }
}

void QExtKeyboardInputContext::sendKeyEvent(QKeyEvent *event)
{
    Q_D(QExtKeyboardInputContext);
    const QGuiApplication *app = qApp;
    QWindow *focusWindow = app ? app->focusWindow() : nullptr;
    if (focusWindow)
    {
        d->m_filterEvent = event;
        QGuiApplication::sendEvent(focusWindow, event);
        d->m_filterEvent = nullptr;
    }
}

void QExtKeyboardInputContext::sendEvent(QEvent *event)
{
    Q_D(QExtKeyboardInputContext);
    if (d->m_focusObject)
    {
        d->m_filterEvent = event;
        QGuiApplication::sendEvent(d->m_focusObject, event);
        d->m_filterEvent = nullptr;
    }
}

QSize QExtKeyboardInputContext::inputPanelSize() const
{
    Q_D(const QExtKeyboardInputContext);
    return d->m_inputPanelSize;
}

void QExtKeyboardInputContext::setInputPanelSize(const QSize &size)
{
    Q_D(QExtKeyboardInputContext);
    if (size != d->m_inputPanelSize)
    {
        d->m_inputPanelSize = size;
        if (!d->m_inputPanel.isNull())
        {
            d->m_inputPanel->setFixedSize(size);
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
    return d->m_inputPanelPopupMode;
}

void QExtKeyboardInputContext::setInputPanelPopupMode(PopupModeEnum mode)
{
    Q_D(QExtKeyboardInputContext);
    if (mode != d->m_inputPanelPopupMode)
    {
        d->m_inputPanelPopupMode = mode;
        emit this->inputPanelPopupModeChanged(mode);
    }
}

void QExtKeyboardInputContext::hideKeyboard()
{
    Q_D(QExtKeyboardInputContext);
    if (d->m_inputPanel)
    {
        d->m_inputPanel->hide();
        d->m_inputPanel->onHideSymbol();
    }
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
    d->m_preeditText = text;

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
    if (!d->m_inputPanel)
    {
        return;
    }

    if (d->m_visible != d->m_inputPanel->isVisible())
    {
        switch (d->m_inputPanelPopupMode)
        {
        case PopupMode_BottomCenter:
        {
            d->m_inputPanel->animationSetVisible(d->m_visible);
            break;
        }
        case PopupMode_AutoFollow:
        {
            if (d->m_visible)
            {
                d->m_inputPanel->move(d->m_inputPanelFollowPos);
                d->m_inputPanel->show();
            }
            else
            {
                d->m_inputPanel->hide();
            }
            break;
        }
        default:
            break;
        }
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

