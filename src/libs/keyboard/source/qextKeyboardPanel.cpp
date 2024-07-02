#include <qextKeyboardPanel.h>
#include <qextNormalKeyboard.h>
#include <qextSymbolKeyboard.h>
#include <qextCandidatesListWidget.h>
#include <qextOnceFlag.h>

#include <QtDebug>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPropertyAnimation>

class QExtKeyboardPanelPrivate
{
public:
    explicit QExtKeyboardPanelPrivate(QExtKeyboardPanel *q);
    virtual ~QExtKeyboardPanelPrivate();

    QExtKeyboardPanel * const q_ptr;

    bool m_hiding;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_bottomLayout;
    QPropertyAnimation *m_animation;
    QExtNormalKeyboard *m_normalKeyboard;
    QExtSymbolKeyboard *m_symbolKeyboard;
    QExtCandidatesListWidget *m_textDisplayWidget;

private:
    QEXT_DECL_PUBLIC(QExtKeyboardPanel)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardPanelPrivate)
};

QExtKeyboardPanelPrivate::QExtKeyboardPanelPrivate(QExtKeyboardPanel *q)
    : q_ptr(q)
{
}

QExtKeyboardPanelPrivate::~QExtKeyboardPanelPrivate()
{
}

QExtKeyboardPanel::QExtKeyboardPanel(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtKeyboardPanelPrivate(this))
{
    Q_D(QExtKeyboardPanel);
    d->m_normalKeyboard = new QExtNormalKeyboard(this);
    d->m_symbolKeyboard = new QExtSymbolKeyboard(this);
    d->m_textDisplayWidget = new QExtCandidatesListWidget(this);
    d->m_textDisplayWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    d->m_textDisplayWidget->setMinimumSize(100, 50);
    d->m_textDisplayWidget->resize(1000, 50);

    d->m_mainLayout = new QVBoxLayout(this);
    d->m_mainLayout->addWidget(d->m_textDisplayWidget);

    QWidget * widgetContainer = new QWidget(this);
    d->m_bottomLayout = new QHBoxLayout;
    d->m_bottomLayout->addWidget(d->m_normalKeyboard);
    d->m_bottomLayout->addWidget(d->m_symbolKeyboard);
    d->m_bottomLayout->setMargin(0);
    widgetContainer->setLayout(d->m_bottomLayout);
    widgetContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->m_mainLayout->addWidget(widgetContainer);
    d->m_mainLayout->setStretch(0, 0);
    d->m_mainLayout->setStretch(1, 1);
    d->m_mainLayout->setSpacing(10);
    d->m_mainLayout->setContentsMargins(10, 10, 10, 10);

    d->m_symbolKeyboard->hide();

//将KeyboardContainer设置为模态窗口会导致下面的语句不起作用,虚拟键盘会抢输入框焦点
#if (QT_VERSION > QT_VERSION_CHECK(5, 0, 0))
    this->setWindowFlags(Qt::Tool |
                         Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint |
                         Qt::WindowDoesNotAcceptFocus |
                         Qt::X11BypassWindowManagerHint);
#else
    this->setWindowFlags(Qt::Tool |
                         Qt::WindowStaysOnTopHint |
                         Qt::FramelessWindowHint |
                         Qt::X11BypassWindowManagerHint);
#endif

    this->setStyleSheet("*{font-size: 18pt;font-family: 'Microsoft YaHei';outline: none} \
        QWidget\
        {\
                color: #eff0f1;\
                background-color: rgb(0,0,0);\
                selection-background-color:#3daee9;\
                selection-color: #eff0f1;\
                background-clip: border;\
                border-image: none;\
                border: 0px transparent black;\
                outline: 0;\
        }\
        QPushButton\
        {\
                color:rgb(255,255,255);\
                background-color:rgb(56,53,51);\
                border: none;\
                border-radius: 5px;\
        }\
        QPushButton:hover:pressed\
        {\
                color:rgb(255,255,255);\
                background-color:rgb(45,125,154);\
        }\
        QPushButton:hover:!pressed\
                            {\
                                    color:rgb(255,255,255);\
                                    background-color:rgb(42,40,38);\
                            }\
                            QPushButton:disabled\
        {\
                color:rgb(120,120,120);\
                background-color:rgb(20,20,20);\
        }"
        );

    d->m_textDisplayWidget->setStyleSheet("*{font-size: 18pt;font-family: 'Microsoft YaHei';outline: none} \
        QPushButton\
        {\
                color:rgb(255,255,255);\
                background-color:rgb(56,53,51);\
                border: none;\
                border-radius: 0px;\
        }\
        QPushButton:hover:pressed\
        {\
                color:rgb(255,255,255);\
                background-color:rgb(45,125,154);\
        }\
        QPushButton:hover:!pressed\
                            {\
                                    color:rgb(255,255,255);\
                                    background-color:rgb(42,40,38);\
                            }\
                            QPushButton:disabled\
        {\
                color:rgb(120,120,120);\
                background-color:rgb(20,20,20);\
        }"
        );

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::changeLanguage, this, &QExtKeyboardPanel::changeLanguage);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::changeLanguage, this, &QExtKeyboardPanel::changeLanguage);
    connect(d->m_normalKeyboard, &QExtNormalKeyboard::changeSymbol, this, &QExtKeyboardPanel::onChangeSymbol);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::changeSymbol, this, &QExtKeyboardPanel::onChangeSymbol);

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::hideKeyboard, this, &QExtKeyboardPanel::hideKeyboard);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::hideKeyboard, this, &QExtKeyboardPanel::hideKeyboard);

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::keyPressed, this, &QExtKeyboardPanel::keyPressed);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::keyPressed, this, &QExtKeyboardPanel::keyPressed);
    connect(d->m_textDisplayWidget,&QExtCandidatesListWidget::chooseText,this,&QExtKeyboardPanel::chooseCandidate);

    d->m_animation = new QPropertyAnimation(this, "pos");
    d->m_animation->setDuration(200);
    connect(d->m_animation, &QAbstractAnimation::finished, this, &QExtKeyboardPanel::onAnimationFinished);
    d->m_hiding = false;

    this->setAttribute(Qt::WA_DeleteOnClose);
}

QExtKeyboardPanel *QExtKeyboardPanel::instance()
{
    static QExtOnceFlag onceFlag;
    static QExtKeyboardPanel *instance = QEXT_NULLPTR;
    if (onceFlag.enter())
    {
        instance = new QExtKeyboardPanel;
        onceFlag.leave();
    }
    return instance;
}

QExtKeyboardPanel::~QExtKeyboardPanel()
{
    Q_D(QExtKeyboardPanel);
    if(this->isAnimating())
    {
        d->m_animation->stop();
    }
}

bool QExtKeyboardPanel::isAnimating() const
{
    Q_D(const QExtKeyboardPanel);
    return d->m_animation->state() == QAbstractAnimation::Running;
}

void QExtKeyboardPanel::setCandidateList(const QStringList &texts)
{
    Q_D(QExtKeyboardPanel);
    d->m_textDisplayWidget->setCandidatesList(texts);
}

void QExtKeyboardPanel::setLanguageName(const QString &name)
{
    Q_D(QExtKeyboardPanel);
    d->m_normalKeyboard->setCurLanguage(name);
    d->m_symbolKeyboard->setCurLanguage(name);
}

void QExtKeyboardPanel::onChangeSymbol()
{
    Q_D(QExtKeyboardPanel);
    if(d->m_normalKeyboard->isVisible())
    {
        d->m_normalKeyboard->hide();
        d->m_symbolKeyboard->show();
    }
    else
    {
        d->m_normalKeyboard->show();
        d->m_symbolKeyboard->hide();
    }

    emit this->changeSymbol();
}

void QExtKeyboardPanel::onHideSymbol()
{
    Q_D(QExtKeyboardPanel);
    if(!d->m_normalKeyboard->isVisible())
    {
        d->m_normalKeyboard->show();
        d->m_symbolKeyboard->hide();
    }
}

void QExtKeyboardPanel::animationHide()
{
    Q_D(QExtKeyboardPanel);
    int screenWidth = qApp->primaryScreen()->size().width();
    int screenHeight = qApp->primaryScreen()->size().height();
    const int posX = (screenWidth - this->width()) / 2;

    if(this->isAnimating())
    {
        d->m_animation->stop();
    }

    d->m_hiding = true;
    d->m_animation->setStartValue(QPoint(posX, this->pos().y()));
    d->m_animation->setEndValue(QPoint(posX, screenHeight));
    d->m_animation->start();
}

void QExtKeyboardPanel::animationShow()
{
    Q_D(QExtKeyboardPanel);
    int screenWidth = qApp->primaryScreen()->size().width();
    int screenHeight = qApp->primaryScreen()->size().height();
    const int posX = (screenWidth - this->width()) / 2;

    this->move(posX, qApp->primaryScreen()->size().height());
    this->show();

    d->m_animation->setStartValue(QPoint(posX, screenHeight));
    d->m_animation->setEndValue(QPoint(posX, screenHeight - this->height()));
    d->m_animation->start();
}

void QExtKeyboardPanel::animationSetVisible(bool visible)
{
    if (visible)
    {
        this->animationShow();
    }
    else
    {
        this->animationHide();
    }
}

void QExtKeyboardPanel::setInputMethodHints(Qt::InputMethodHints hints)
{
    Q_UNUSED(hints);
}

void QExtKeyboardPanel::onAnimationFinished()
{
    Q_D(QExtKeyboardPanel);
    if(d->m_hiding)
    {
        this->hide();
    }
    d->m_hiding = false;
}
