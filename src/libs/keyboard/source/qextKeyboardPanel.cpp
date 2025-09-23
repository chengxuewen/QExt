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
    QVBoxLayout *mMainLayout;
    QHBoxLayout *mBottomLayout;
    QPropertyAnimation *m_animation;
    QExtNormalKeyboard *mNormalKeyboard;
    QExtSymbolKeyboard *mSymbolKeyboard;
    QExtCandidatesListWidget *mTextDisplayWidget;

private:
    QEXT_DECLARE_PUBLIC(QExtKeyboardPanel)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtKeyboardPanelPrivate)
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
    d->mNormalKeyboard = new QExtNormalKeyboard(this);
    d->mSymbolKeyboard = new QExtSymbolKeyboard(this);
    d->mTextDisplayWidget = new QExtCandidatesListWidget(this);
    d->mTextDisplayWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    d->mTextDisplayWidget->setMinimumSize(100, 50);
    d->mTextDisplayWidget->resize(1000, 50);

    d->mMainLayout = new QVBoxLayout(this);
    d->mMainLayout->addWidget(d->mTextDisplayWidget);

    QWidget * widgetContainer = new QWidget(this);
    d->mBottomLayout = new QHBoxLayout;
    d->mBottomLayout->addWidget(d->mNormalKeyboard);
    d->mBottomLayout->addWidget(d->mSymbolKeyboard);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    d->mBottomLayout->setMargin(0);
#endif
    widgetContainer->setLayout(d->mBottomLayout);
    widgetContainer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->mMainLayout->addWidget(widgetContainer);
    d->mMainLayout->setStretch(0, 0);
    d->mMainLayout->setStretch(1, 1);
    d->mMainLayout->setSpacing(10);
    d->mMainLayout->setContentsMargins(10, 10, 10, 10);

    d->mSymbolKeyboard->hide();

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

    d->mTextDisplayWidget->setStyleSheet("*{font-size: 18pt;font-family: 'Microsoft YaHei';outline: none} \
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

    connect(d->mNormalKeyboard, &QExtNormalKeyboard::changeLanguage, this, &QExtKeyboardPanel::changeLanguage);
    connect(d->mSymbolKeyboard, &QExtSymbolKeyboard::changeLanguage, this, &QExtKeyboardPanel::changeLanguage);
    connect(d->mNormalKeyboard, &QExtNormalKeyboard::changeSymbol, this, &QExtKeyboardPanel::onChangeSymbol);
    connect(d->mSymbolKeyboard, &QExtSymbolKeyboard::changeSymbol, this, &QExtKeyboardPanel::onChangeSymbol);

    connect(d->mNormalKeyboard, &QExtNormalKeyboard::hideKeyboard, this, &QExtKeyboardPanel::hideKeyboard);
    connect(d->mSymbolKeyboard, &QExtSymbolKeyboard::hideKeyboard, this, &QExtKeyboardPanel::hideKeyboard);

    connect(d->mNormalKeyboard, &QExtNormalKeyboard::keyPressed, this, &QExtKeyboardPanel::keyPressed);
    connect(d->mSymbolKeyboard, &QExtSymbolKeyboard::keyPressed, this, &QExtKeyboardPanel::keyPressed);
    connect(d->mTextDisplayWidget,&QExtCandidatesListWidget::chooseText,this,&QExtKeyboardPanel::chooseCandidate);

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
    d->mTextDisplayWidget->setCandidatesList(texts);
}

void QExtKeyboardPanel::setLanguageName(const QString &name)
{
    Q_D(QExtKeyboardPanel);
    d->mNormalKeyboard->setCurLanguage(name);
    d->mSymbolKeyboard->setCurLanguage(name);
}

void QExtKeyboardPanel::onChangeSymbol()
{
    Q_D(QExtKeyboardPanel);
    if(d->mNormalKeyboard->isVisible())
    {
        d->mNormalKeyboard->hide();
        d->mSymbolKeyboard->show();
    }
    else
    {
        d->mNormalKeyboard->show();
        d->mSymbolKeyboard->hide();
    }

    emit this->changeSymbol();
}

void QExtKeyboardPanel::onHideSymbol()
{
    Q_D(QExtKeyboardPanel);
    if(!d->mNormalKeyboard->isVisible())
    {
        d->mNormalKeyboard->show();
        d->mSymbolKeyboard->hide();
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
