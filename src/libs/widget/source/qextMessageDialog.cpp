#include <qextMessageDialog.h>
#include <qextMessageDialog_p.h>

#include <qextFontAwesome.h>
#include <qextIconButton.h>

#include <QCoreApplication>
#include <QApplication>
#include <QKeySequence>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QStyle>

QVector<QIcon> QEXTMessageDialogPrivate::sm_contentIconVector;
QMap<int, QIcon> QEXTMessageDialogPrivate::sm_buttonIconMap;

QEXTMessageDialogPrivate::QEXTMessageDialogPrivate(QEXTMessageDialog *q)
    : q_ptr(q)
{
    QEXTMessageDialogPrivate::initIcons();
    m_buttonsVector.resize(QEXTMessageDialog::ButtonRoleNum);
}

QEXTMessageDialogPrivate::~QEXTMessageDialogPrivate()
{

}

void QEXTMessageDialogPrivate::initIcons()
{
    if (sm_buttonIconMap.isEmpty())
    {
        sm_buttonIconMap[QEXTMessageDialog::Button_Ok] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Save] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_SaveAll] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Open] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Yes] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_YesToAll] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_No] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_NoToAll] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Abort] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Retry] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Ignore] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Close] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Cancel] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Discard] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Help] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Apply] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_Reset] = QIcon();
        sm_buttonIconMap[QEXTMessageDialog::Button_RestoreDefaults] = QIcon();
    }
    if (sm_contentIconVector.isEmpty())
    {
        sm_contentIconVector.resize(QEXTMessageDialog::IconNum);
        sm_contentIconVector[QEXTMessageDialog::Icon_Information] = qextFontAwesome->icon(QEXTFontAwesome::FA_info);
        sm_contentIconVector[QEXTMessageDialog::Icon_Critical] = qextFontAwesome->icon(QEXTFontAwesome::FA_exclamation);
        sm_contentIconVector[QEXTMessageDialog::Icon_Question] = qextFontAwesome->icon(QEXTFontAwesome::FA_question);
        sm_contentIconVector[QEXTMessageDialog::Icon_Warning] = qextFontAwesome->icon(QEXTFontAwesome::FA_warning);
    }
}

void QEXTMessageDialogPrivate::initDialog()
{
    m_titleBarWidget = new QWidget(q_ptr);
    m_titleBarWidget->setObjectName("titleBar");
    m_titleBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_titleBarWidget->setMinimumHeight(30);
    m_titlebarIconLabel = new QLabel(m_titleBarWidget);
    m_titlebarIconLabel->setObjectName("titlebarIconLabel");
    m_titlebarIconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_titlebarIconLabel->setMinimumSize(30, 30);
    m_titlebarTextLabel = new QLabel(m_titleBarWidget);
    m_titlebarTextLabel->setObjectName("titlebarTextLabel");
    m_titlebarTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_titleBarCloseButton = new QEXTIconButton(qextFontAwesome->icon(QEXTFontAwesome::FA_window_close), m_titleBarWidget);
    m_titleBarCloseButton->setObjectName("titleBarCloseButton");
    m_titleBarCloseButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_titleBarCloseButton->setMinimumSize(30, 30);
    QObject::connect(m_titleBarCloseButton, SIGNAL(clicked(bool)), q_ptr, SLOT(onCloseButtonClicked()));
    QHBoxLayout *titleBarLayout = new QHBoxLayout;
    titleBarLayout->addWidget(m_titlebarIconLabel);
    titleBarLayout->addWidget(m_titlebarTextLabel);
    titleBarLayout->addWidget(m_titleBarCloseButton);
    titleBarLayout->setMargin(0);
    titleBarLayout->setSpacing(0);
    m_titleBarWidget->setLayout(titleBarLayout);

    m_contentWidget = new QWidget(q_ptr);
    m_contentWidget->setObjectName("content");
    m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_contentIconLabel = new QLabel(m_contentWidget);
    m_contentIconLabel->setObjectName("contentIconLabel");
    m_contentIconLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_contentIconLabel->setMinimumSize(100, 100);
    m_contentTextLabel = new QLabel(m_contentWidget);
    m_contentTextLabel->setObjectName("contentTextLabel");
    m_contentTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(m_contentIconLabel);
    contentLayout->addWidget(m_contentTextLabel);
    m_contentWidget->setLayout(contentLayout);

    m_buttonBoxWidget = new QWidget(q_ptr);
    m_buttonBoxWidget->setObjectName("buttonBox");
    m_buttonBoxWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_buttonBoxWidget->setMinimumHeight(40);
    m_buttonBoxLayout = new QHBoxLayout;
    m_buttonBoxLayout->setMargin(0);
    m_buttonBoxLayout->setSpacing(0);
    m_buttonBoxWidget->setLayout(m_buttonBoxLayout);

    QVBoxLayout *dialogLayout = new QVBoxLayout;
    dialogLayout->addWidget(m_titleBarWidget);
    dialogLayout->addWidget(m_contentWidget);
    dialogLayout->addWidget(m_buttonBoxWidget);
    dialogLayout->setMargin(0);
    dialogLayout->setSpacing(0);
    q_ptr->setLayout(dialogLayout);

    q_ptr->setTitleText(m_titlebarTextLabel->text());
    q_ptr->setTitleBar(m_titlebarTextLabel);
    q_ptr->setResizeEnable(true);
    q_ptr->setMoveEnable(true);

    QStringList list;
    list << "#titleBar{background:#BBBBBB;}";
    list << "#content{border:2px solid #BBBBBB;background:#FFFFFF;}";
    q_ptr->setStyleSheet(list.join(""));
}

void QEXTMessageDialogPrivate::layoutButtons()
{
    for (int i = m_buttonBoxLayout->count() - 1; i >= 0; --i) {
        QLayoutItem *item = m_buttonBoxLayout->takeAt(i);
        if (QWidget *widget = item->widget())
        {
            widget->hide();
        }
        delete item;
    }

    if (!m_checkBox.isNull())
    {
        m_buttonBoxLayout->addWidget(m_checkBox.data());
    }

    m_buttonBoxLayout->addStretch();
    for (int i = 0; i < QEXTMessageDialog::ButtonRoleNum; ++i)
    {
        const QList<QAbstractButton *> &buttonList = m_buttonsVector[i];
        this->addButtonsToLayout(buttonList, false);
    }

    QWidget *lastWidget = QEXT_DECL_NULLPTR;
    q_ptr->setFocusProxy(QEXT_DECL_NULLPTR);
    for (int i = 0; i < m_buttonBoxLayout->count(); ++i) {
        QLayoutItem *item = m_buttonBoxLayout->itemAt(i);
        if (QWidget *widget = item->widget()) {
            if (lastWidget)
            {
                QWidget::setTabOrder(lastWidget, widget);
            }
            else
            {
                q_ptr->setFocusProxy(widget);
            }
            lastWidget = widget;
        }
    }
}

void QEXTMessageDialogPrivate::addButtonsToLayout(const QList<QAbstractButton *> &buttonList, bool reverse)
{
    int start = reverse ? buttonList.count() - 1 : 0;
    int end = reverse ? -1 : buttonList.count();
    int step = reverse ? -1 : 1;

    for (int i = start; i != end; i += step) {
        QAbstractButton *button = buttonList.at(i);
        m_buttonBoxLayout->addWidget(button);
        button->show();
    }
}

QAbstractButton *QEXTMessageDialogPrivate::createButton(QEXTMessageDialog::ButtonType type)
{
    QIcon icon = sm_buttonIconMap[type];
    QAbstractButton *button = new QPushButton(QEXTMessageDialog::buttonTypeText(type), q_ptr);
    QStyle *style = q_ptr->style();
    if (style->styleHint(QStyle::SH_DialogButtonBox_ButtonsHaveIcons, 0, q_ptr) && !icon.isNull())
    {
        button->setIcon(icon);
    }
    m_buttonHash.insert(button, type);
    QEXTMessageDialog::ButtonRoleType role = QEXTMessageDialog::buttonTypeRole(type);
    if (role != QEXTMessageDialog::ButtonRole_Invalid)
    {
        this->addButton(button, role);
    }
    else
    {
        qWarning("QEXTMessageDialogPrivate::createButton: Invalid ButtonRole, button not added");
    }

#ifdef Q_DEAD_CODE_FROM_QT4_MAC
    // Since mnemonics is off by default on Mac, we add a Cmd-D
    // shortcut here to e.g. make the "Don't Save" button work nativly:
    if (QEXTMessageDialog::Button_Discard == type)
    {
        button->setShortcut(QKeySequence(QLatin1String("Ctrl+D")));
    }
#endif

    return button;
}

void QEXTMessageDialogPrivate::createButtons(QEXTMessageDialog::ButtonTypes buttons)
{
    uint i = QEXTMessageDialog::Button_FirstButton;
    while (i <= QEXTMessageDialog::Button_LastButton) {
        if (i & buttons) {
            this->createButton(QEXTMessageDialog::ButtonType(i));
        }
        i = i << 1;
    }
    this->layoutButtons();
}

void QEXTMessageDialogPrivate::addButton(QAbstractButton *button, QEXTMessageDialog::ButtonRoleType role)
{
    QObject::connect(button, SIGNAL(clicked()), q_ptr, SLOT(onHandleButtonClicked()));
    QObject::connect(button, SIGNAL(destroyed()), q_ptr, SLOT(onHandleButtonDestroyed()));
    m_buttonsVector[role].append(button);
    this->layoutButtons();
}

void QEXTMessageDialogPrivate::removeButton(QAbstractButton *button)
{
    if (button)
    {
        m_buttonHash.remove(button);
        for (int i = 0; i < QEXTMessageDialog::ButtonRoleNum; ++i) {
            QList<QAbstractButton *> &list = m_buttonsVector[i];
            for (int j = 0; j < list.count(); ++j) {
                if (list.at(j) == button) {
                    list.takeAt(j);
                    if (!m_customButtonList.contains(button)) {
                        QObject::disconnect(button, SIGNAL(clicked()), q_ptr, SLOT(onHandleButtonClicked()));
                        QObject::disconnect(button, SIGNAL(destroyed()), q_ptr, SLOT(onHandleButtonDestroyed()));
                    }
                    break;
                }
            }
        }
    }
}

void QEXTMessageDialogPrivate::updateSize()
{
    //    if (!q_ptr->isVisible())
    //    {
    //        return;
    //    }

    //    QSize screenSize = QApplication::desktop()->availableGeometry(QCursor::pos()).size();
    //#if defined(Q_OS_WINCE)
    //    // the width of the screen, less the window border.
    //    int hardLimit = screenSize.width() - (q->frameGeometry().width() - q->geometry().width());
    //#else
    //    int hardLimit = qMin(screenSize.width() - 480, 1000); // can never get bigger than this
    //    // on small screens allows the messagebox be the same size as the screen
    //    if (screenSize.width() <= 1024)
    //    {
    //        hardLimit = screenSize.width();
    //    }
    //#endif
    //#ifdef Q_OS_MAC
    //    int softLimit = qMin(screenSize.width()/2, 420);
    //#else
    //    // note: ideally on windows, hard and soft limits but it breaks compat
    //#ifndef Q_OS_WINCE
    //    int softLimit = qMin(screenSize.width()/2, 500);
    //#else
    //    int softLimit = qMin(screenSize.width() * 3 / 4, 500);
    //#endif //Q_OS_WINCE
    //#endif

    //    if (informativeLabel)
    //        informativeLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    //    m_contentTextLabel->setWordWrap(false); // makes the label return min size
    //    int width = this->layoutMinimumWidth();

    //    if (width > softLimit) {
    //        label->setWordWrap(true);
    //        width = qMax(softLimit, layoutMinimumWidth());

    //        if (width > hardLimit) {
    //            label->d_func()->ensureTextControl();
    //            if (QWidgetTextControl *control = label->d_func()->control) {
    //                QTextOption opt = control->document()->defaultTextOption();
    //                opt.setWrapMode(QTextOption::WrapAnywhere);
    //                control->document()->setDefaultTextOption(opt);
    //            }
    //            width = hardLimit;
    //        }
    //    }

    //    if (informativeLabel) {
    //        label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //        QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    //        policy.setHeightForWidth(true);
    //        informativeLabel->setSizePolicy(policy);
    //        width = qMax(width, layoutMinimumWidth());
    //        if (width > hardLimit) { // longest word is really big, so wrap anywhere
    //            informativeLabel->d_func()->ensureTextControl();
    //            if (QWidgetTextControl *control = informativeLabel->d_func()->control) {
    //                QTextOption opt = control->document()->defaultTextOption();
    //                opt.setWrapMode(QTextOption::WrapAnywhere);
    //                control->document()->setDefaultTextOption(opt);
    //            }
    //            width = hardLimit;
    //        }
    //        policy.setHeightForWidth(label->wordWrap());
    //        label->setSizePolicy(policy);
    //    }

    //    QFontMetrics fm(QApplication::font("QMdiSubWindowTitleBar"));
    //    int windowTitleWidth = qMin(fm.width(q->windowTitle()) + 50, hardLimit);
    //    if (windowTitleWidth > width)
    //        width = windowTitleWidth;

    //    layout->activate();
    //    int height = (layout->hasHeightForWidth())
    //            ? layout->totalHeightForWidth(width)
    //            : layout->totalMinimumSize().height();

    //    q->setFixedSize(width, height);
    //    QCoreApplication::removePostedEvents(q_ptr, QEvent::LayoutRequest);
}



const int QEXTMessageDialog::IconNum = 5;
const int QEXTMessageDialog::ButtonRoleNum = 11;
const int QEXTMessageDialog::ButtonNum = 27;

QEXTMessageDialog::QEXTMessageDialog(QWidget *parent)
    : QEXTFramelessDialog(parent)
    , d_ptr(new QEXTMessageDialogPrivate(this))
{
    d_ptr->initDialog();
}

QEXTMessageDialog::QEXTMessageDialog(QEXTMessageDialog::IconType icon, const QString &title, const QString &text,
                                     ButtonTypes buttons, QWidget *parent)
    : QEXTFramelessDialog(parent)
    , d_ptr(new QEXTMessageDialogPrivate(this))
{
    d_ptr->initDialog();
    this->setTitleText(title);
    this->setMessageText(text);
    this->setIconType(icon);
    this->setButtonTypes(buttons);
}

QEXTMessageDialog::~QEXTMessageDialog()
{

}

void QEXTMessageDialog::addButton(QAbstractButton *button, QEXTMessageDialog::ButtonRoleType role)
{
    if (button)
    {
        this->removeButton(button);
        d_ptr->addButton(button, role);
    }
}

QAbstractButton *QEXTMessageDialog::addButton(const QString &text, QEXTMessageDialog::ButtonRoleType role)
{
    QPushButton *pushButton = new QPushButton(text);
    d_ptr->addButton(pushButton, role);
    //    d_ptr->updateSize();
    return pushButton;
}

QAbstractButton *QEXTMessageDialog::addButton(QEXTMessageDialog::ButtonType button)
{
    QAbstractButton *pushButton = d_ptr->createButton(button);
    return pushButton;
}

void QEXTMessageDialog::removeButton(QAbstractButton *button)
{
    if (d_ptr->m_defaultButton == button)
    {
        d_ptr->m_defaultButton = QEXT_DECL_NULLPTR;
    }
    d_ptr->removeButton(button);
    //    d_ptr->updateSize();
}

QList<QAbstractButton *> QEXTMessageDialog::buttons() const
{
    QList<QAbstractButton *> buttons;
    for (int i = 0; i < ButtonRoleNum; ++i)
    {
        const QList<QAbstractButton *> &list = d_ptr->m_buttonsVector[i];
        buttons.append(list);
    }
    return buttons;
}

QEXTMessageDialog::ButtonRoleType QEXTMessageDialog::buttonRole(QAbstractButton *button) const
{
    for (int i = 0; i < ButtonRoleNum; ++i)
    {
        const QList<QAbstractButton *> &list = d_ptr->m_buttonsVector[i];
        for (int j = 0; j < list.count(); ++j)
        {
            if (list.at(j) == button)
            {
                return ButtonRoleType(i);
            }
        }
    }
    return ButtonRole_Invalid;
}

void QEXTMessageDialog::setButtonTypes(ButtonTypes buttons)
{
    d_ptr->createButtons(buttons);
    QList<QAbstractButton *> buttonList = this->buttons();
    if (!buttonList.contains(d_ptr->m_escapeButton))
    {
        d_ptr->m_escapeButton = QEXT_DECL_NULLPTR;
    }
    if (!buttonList.contains(d_ptr->m_defaultButton))
    {
        d_ptr->m_defaultButton = QEXT_DECL_NULLPTR;
    }
    d_ptr->updateSize();
}

QEXTMessageDialog::ButtonTypes QEXTMessageDialog::buttonTypes() const
{
    QEXTMessageDialog::ButtonTypes buttons = Button_None;
    QHash<QAbstractButton *, QEXTMessageDialog::ButtonType>::const_iterator iter = d_ptr->m_buttonHash.constBegin();
    while (iter != d_ptr->m_buttonHash.constEnd())
    {
        buttons |= iter.value();
        ++iter;
    }
    return buttons;
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::buttonType(QAbstractButton *button) const
{
    return d_ptr->m_buttonHash.value(button);
}

QAbstractButton *QEXTMessageDialog::button(QEXTMessageDialog::ButtonType type) const
{
    return d_ptr->m_buttonHash.key(type);
}

QAbstractButton *QEXTMessageDialog::defaultButton() const
{
    return d_ptr->m_defaultButton;
}

void QEXTMessageDialog::setDefaultButton(QAbstractButton *button)
{
    d_ptr->m_defaultButton = button;
    if (button)
    {
        button->setFocus();
    }
}

void QEXTMessageDialog::setDefaultButton(QEXTMessageDialog::ButtonType button)
{
    QAbstractButton *defaultButton = this->button(button);
    this->setDefaultButton(defaultButton);
}

QAbstractButton *QEXTMessageDialog::escapeButton() const
{
    return d_ptr->m_escapeButton;
}

void QEXTMessageDialog::setEscapeButton(QAbstractButton *button)
{
    if (this->buttons().contains(button))
    {
        d_ptr->m_escapeButton = button;
    }
}

void QEXTMessageDialog::setEscapeButton(QEXTMessageDialog::ButtonType button)
{
    QAbstractButton *escapeButton = this->button(button);
    this->setEscapeButton(escapeButton);
}

QAbstractButton *QEXTMessageDialog::clickedButton() const
{
    return d_ptr->m_clickedButton;
}

QString QEXTMessageDialog::messageText() const
{
    return d_ptr->m_contentTextLabel->text();
}

void QEXTMessageDialog::setMessageText(const QString &text)
{
    d_ptr->m_contentTextLabel->setText(text);
    //    d_ptr->updateSize();
}

QSize QEXTMessageDialog::iconSize() const
{
    return d_ptr->m_contentIconLabel->size();
}

void QEXTMessageDialog::setIconSize(QSize size)
{
    d_ptr->m_contentIconLabel->setFixedSize(size);
    QPixmap pixmap = d_ptr->m_currentIcon.pixmap(size);
    d_ptr->m_contentIconLabel->setPixmap(pixmap);
}

QEXTMessageDialog::IconType QEXTMessageDialog::iconType() const
{
    return d_ptr->m_iconType;
}

void QEXTMessageDialog::setIconType(IconType icon)
{
    d_ptr->m_iconType = icon;
    d_ptr->m_currentIcon = d_ptr->sm_contentIconVector[icon];
    QPixmap pixmap = d_ptr->m_currentIcon.pixmap(d_ptr->m_contentIconLabel->size());
    d_ptr->m_contentIconLabel->setPixmap(pixmap);
}

QIcon QEXTMessageDialog::icon() const
{
    return d_ptr->m_currentIcon;
}

void QEXTMessageDialog::setIcon(const QIcon &icon)
{
    d_ptr->m_currentIcon = icon;
    d_ptr->m_iconType = Icon_None;
    QPixmap pixmap = d_ptr->m_currentIcon.pixmap(d_ptr->m_contentIconLabel->size());
    d_ptr->m_contentIconLabel->setPixmap(pixmap);
}

QIcon QEXTMessageDialog::titleIcon() const
{
    return d_ptr->m_titleIcon;
}

void QEXTMessageDialog::setTitleIcon(const QIcon &icon)
{
    d_ptr->m_titleIcon = icon;
    QPixmap pixmap = icon.pixmap(d_ptr->m_titlebarIconLabel->size());
    d_ptr->m_titlebarIconLabel->setPixmap(pixmap);
}

QString QEXTMessageDialog::titleText() const
{
    return d_ptr->m_titlebarTextLabel->text();
}

void QEXTMessageDialog::setTitleText(const QString &text)
{
    d_ptr->m_titlebarTextLabel->setText(text);
    this->setWindowTitle(text);
}

Qt::TextFormat QEXTMessageDialog::textFormat() const
{
    return d_ptr->m_contentTextLabel->textFormat();
}

void QEXTMessageDialog::setTextFormat(Qt::TextFormat format)
{
    d_ptr->m_contentTextLabel->setTextFormat(format);
}

void QEXTMessageDialog::setTextInteractionFlags(Qt::TextInteractionFlags flags)
{
    d_ptr->m_contentTextLabel->setTextInteractionFlags(flags);
}

Qt::TextInteractionFlags QEXTMessageDialog::textInteractionFlags() const
{
    return d_ptr->m_contentTextLabel->textInteractionFlags();
}

void QEXTMessageDialog::setCheckBox(QCheckBox *cb)
{

}

QCheckBox *QEXTMessageDialog::checkBox() const
{

}

QWidget *QEXTMessageDialog::titleBarWidget()
{
    return d_ptr->m_titleBarWidget;
}

QWidget *QEXTMessageDialog::contentWidget()
{
    return d_ptr->m_contentWidget;
}

QIcon QEXTMessageDialog::buttonIcon(QEXTMessageDialog::ButtonType type)
{
    return QEXTMessageDialogPrivate::sm_buttonIconMap[type];
}

void QEXTMessageDialog::setButtonIcon(const QIcon &icon, QEXTMessageDialog::ButtonType type)
{
    QEXTMessageDialogPrivate::sm_buttonIconMap[type] = icon;
}

QIcon QEXTMessageDialog::contentIcon(QEXTMessageDialog::IconType type)
{
    return QEXTMessageDialogPrivate::sm_contentIconVector[type];
}

void QEXTMessageDialog::setContentIcon(const QIcon &icon, QEXTMessageDialog::IconType type)
{
    QEXTMessageDialogPrivate::sm_contentIconVector[type] = icon;
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::showMessageDialog(QWidget *parent, QEXTMessageDialog::IconType icon,
                                                                   const QString &title, const QString &text,
                                                                   ButtonTypes buttons, QEXTMessageDialog::ButtonType defaultButton)
{
    QEXTMessageDialog dialog(icon, title, text, QEXTMessageDialog::Button_None, parent);

    uint mask = QEXTMessageDialog::Button_FirstButton;
    //    while (mask <= QEXTMessageDialog::Button_LastButton)
    //    {
    //        uint sb = buttons & mask;
    //        mask <<= 1;
    //        if (!sb)
    //        {
    //            continue;
    //        }
    //        QAbstractButton *button = this->addButton((QEXTMessageDialog::buttonType)sb);
    //        // Choose the first accept role as the default
    //        if (this->defaultButton())
    //        {
    //            continue;
    //        }
    //        if ((defaultButton == QEXTMessageDialog::NoButton && buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
    //                || (defaultButton != QMessageBox::NoButton && sb == uint(defaultButton)))
    //            msgBox.setDefaultButton(button);
    //    }
    //    if (msgBox.exec() == -1)
    //        return QMessageBox::Cancel;
    return QEXTMessageDialog::ButtonType(dialog.exec());
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::information(QWidget *parent, const QString &title, const QString &text,
                                                             ButtonTypes buttons, QEXTMessageDialog::ButtonType defaultButton)
{
    return QEXTMessageDialog::showMessageDialog(parent, Icon_Information, title, text, buttons, defaultButton);
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::question(QWidget *parent, const QString &title, const QString &text,
                                                          ButtonTypes buttons, QEXTMessageDialog::ButtonType defaultButton)
{
    return QEXTMessageDialog::showMessageDialog(parent, Icon_Question, title, text, buttons, defaultButton);
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::warning(QWidget *parent, const QString &title, const QString &text,
                                                         ButtonTypes buttons, QEXTMessageDialog::ButtonType defaultButton)
{
    return QEXTMessageDialog::showMessageDialog(parent, Icon_Warning, title, text, buttons, defaultButton);
}

QEXTMessageDialog::ButtonType QEXTMessageDialog::critical(QWidget *parent, const QString &title, const QString &text,
                                                          ButtonTypes buttons, QEXTMessageDialog::ButtonType defaultButton)
{
    return QEXTMessageDialog::showMessageDialog(parent, Icon_Critical, title, text, buttons, defaultButton);
}

QString QEXTMessageDialog::buttonTypeText(int type)
{
    switch (type)
    {
    case Button_Ok:
        return QCoreApplication::translate("QEXTMessageDialog", "OK");
    case Button_Save:
        return QCoreApplication::translate("QEXTMessageDialog", "Save");
    case Button_SaveAll:
        return QCoreApplication::translate("QEXTMessageDialog", "Save All");
    case Button_Open:
        return QCoreApplication::translate("QEXTMessageDialog", "Open");
    case Button_Yes:
        return QCoreApplication::translate("QEXTMessageDialog", "&Yes");
    case Button_YesToAll:
        return QCoreApplication::translate("QEXTMessageDialog", "Yes to &All");
    case Button_No:
        return QCoreApplication::translate("QEXTMessageDialog", "&No");
    case Button_NoToAll:
        return QCoreApplication::translate("QEXTMessageDialog", "N&o to All");
    case Button_Abort:
        return QCoreApplication::translate("QEXTMessageDialog", "Abort");
    case Button_Retry:
        return QCoreApplication::translate("QEXTMessageDialog", "Retry");
    case Button_Ignore:
        return QCoreApplication::translate("QEXTMessageDialog", "Ignore");
    case Button_Close:
        return QCoreApplication::translate("QEXTMessageDialog", "Close");
    case Button_Cancel:
        return QCoreApplication::translate("QEXTMessageDialog", "Cancel");
    case Button_Discard:
        return QCoreApplication::translate("QEXTMessageDialog", "Discard");
    case Button_Help:
        return QCoreApplication::translate("QEXTMessageDialog", "Help");
    case Button_Apply:
        return QCoreApplication::translate("QEXTMessageDialog", "Apply");
    case Button_Reset:
        return QCoreApplication::translate("QEXTMessageDialog", "Reset");
    case Button_RestoreDefaults:
        return QCoreApplication::translate("QEXTMessageDialog", "Restore Defaults");
    default:
        break;
    }
    return QString();
}

QEXTMessageDialog::ButtonRoleType QEXTMessageDialog::buttonTypeRole(int type)
{
    switch (type)
    {
    case Button_Ok:
    case Button_Save:
    case Button_Open:
    case Button_SaveAll:
    case Button_Retry:
    case Button_Ignore:
        return ButtonRole_Accept;
    case Button_Cancel:
    case Button_Close:
    case Button_Abort:
        return ButtonRole_Reject;
    case Button_Discard:
        return ButtonRole_Destructive;
    case Button_Help:
        return ButtonRole_Help;
    case Button_Apply:
        return ButtonRole_Apply;
    case Button_Yes:
    case Button_YesToAll:
        return ButtonRole_Yes;
    case Button_No:
    case Button_NoToAll:
        return ButtonRole_No;
    case Button_RestoreDefaults:
    case Button_Reset:
        return ButtonRole_Reset;
    default:
        break;
    }
    return ButtonRole_Invalid;
}

void QEXTMessageDialog::onCloseButtonClicked()
{
    this->reject();
}

void QEXTMessageDialog::onHandleButtonClicked()
{
    QAbstractButton *button = qobject_cast<QAbstractButton *>(this->sender());
    if (button)
    {
        // Can't fetch this *after* emitting clicked, as clicked may destroy the button
        // or change its role. Now changing the role is not possible yet, but arguably
        // both clicked and accepted/rejected/etc. should be emitted "atomically"
        // depending on whatever role the button had at the time of the click.
        const QEXTMessageDialog::ButtonRoleType buttonRole = this->buttonRole(button);
        emit this->clicked(button);

        switch (buttonRole) {
        case ButtonRole_Accept:
        case ButtonRole_Yes:
            this->accept();
            break;
        case ButtonRole_Reject:
        case ButtonRole_No:
            this->reject();
            break;
        case ButtonRole_Help:
            emit this->helpRequested();
            break;
        default:
            break;
        }
    }
}

void QEXTMessageDialog::onHandleButtonDestroyed()
{
    if (QObject *object = this->sender()) {
        this->removeButton(static_cast<QAbstractButton *>(object));
    }
}

bool QEXTMessageDialog::event(QEvent *event)
{
    return QEXTFramelessDialog::event(event);
}

void QEXTMessageDialog::resizeEvent(QResizeEvent *event)
{
    QEXTFramelessDialog::resizeEvent(event);
}

void QEXTMessageDialog::showEvent(QShowEvent *event)
{
    QEXTFramelessDialog::showEvent(event);
}

void QEXTMessageDialog::closeEvent(QCloseEvent *event)
{
    QEXTFramelessDialog::closeEvent(event);
}

void QEXTMessageDialog::keyPressEvent(QKeyEvent *event)
{
    QEXTFramelessDialog::keyPressEvent(event);
}

void QEXTMessageDialog::changeEvent(QEvent *event)
{
    QEXTFramelessDialog::changeEvent(event);
}

#include <qextMessageDialog.moc>
