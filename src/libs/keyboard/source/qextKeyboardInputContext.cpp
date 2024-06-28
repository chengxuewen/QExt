#include <private/qextKeyboardInputContext_p.h>
#include <qextPinyinInputMethod.h>
#include <qextKeyboardLayout.h>

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
    , m_filterEvent(nullptr)
    , m_focusObject(nullptr)
    , m_inputPanel(nullptr)
{

}

QExtKeyboardInputContextPrivate::~QExtKeyboardInputContextPrivate()
{

}


QExtKeyboardInputContext::QExtKeyboardInputContext()
    : QPlatformInputContext()
    , dd_ptr(new QExtKeyboardInputContextPrivate(this))
    //    , m_visible(false)
    //    , m_needHiden(true)
    //    , m_filterEvent(nullptr)
    //    , m_focusObject(nullptr)
    //    , m_inputPanel(nullptr)
{
    Q_D(QExtKeyboardInputContext);
    d->m_inputMethod = new QExtPinyinInputMethod(this);
    qobject_cast<QExtPinyinInputMethod*>(d->m_inputMethod)->setInputContext(this);
    d->m_inputMethodHints = Qt::ImhNone;
    QExtKeyboardLayout().LoadLayout(":/layout/main.json");
}

QExtKeyboardInputContext::~QExtKeyboardInputContext()
{
    //    qDebug() << "~QExtKeyboardInputContext()";
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

    sendEvent(&inputEvent);
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
            d->m_focusObject->installEventFilter(this);
        }

        //emit focusObjectChanged();
    }

    this->update(Qt::ImQueryAll);
}


void QExtKeyboardInputContext::update(Qt::InputMethodQueries queries)
{
    Q_UNUSED(queries);
    Q_D(QExtKeyboardInputContext);

    bool enabled = this->inputMethodQuery(Qt::ImEnabled).toBool();

    if (enabled && d->m_inputPanel.isNull())
    {
        d->m_inputPanel = new QExtKeyboardContainer;
        d->m_inputPanel->setObjectName("Qt5KeyBoard");
        connect(d->m_inputPanel.data(), &QExtKeyboardContainer::hideKeyboard,
                this, &QExtKeyboardInputContext::hideKeyboard);
        connect(d->m_inputPanel.data(), &QExtKeyboardContainer::keyPressed,
                d->m_inputMethod, &QExtAbstractInputMethod::keyEvent);
        connect(d->m_inputPanel.data(), &QExtKeyboardContainer::changeLanguage,
                d->m_inputMethod, &QExtAbstractInputMethod::changeLanguage);
        connect(d->m_inputPanel.data(), &QExtKeyboardContainer::chooseCandidate,
                d->m_inputMethod, &QExtAbstractInputMethod::chooseCandidate);

        connect(d->m_inputMethod, &QExtAbstractInputMethod::showCandidateList,
                d->m_inputPanel.data(), &QExtKeyboardContainer::setCandidateList);
        connect(d->m_inputMethod, &QExtAbstractInputMethod::showLanguageName,
                d->m_inputPanel.data(), &QExtKeyboardContainer::setLanguageName);

        //        connect(m_inputPanel.data(), &QObject::destroyed, [this]() { m_inputPanel = nullptr; });

        d->m_inputPanel->resize(1000, 400);
        d->m_inputPanel->move((QApplication::desktop()->width() - d->m_inputPanel->width()) / 2,
                              WINDOW_HEIGHT - d->m_inputPanel->height());
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
        if (d->m_visible)
        {
            d->m_inputPanel->animationShow();
        }
        else
        {
            d->m_inputPanel->animationHide();
        }

        //emit InputPanelVisibleChanged();
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

