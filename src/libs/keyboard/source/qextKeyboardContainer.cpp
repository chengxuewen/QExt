#include <qextKeyboardContainer.h>

#include <QtDebug>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QPropertyAnimation>

class QExtKeyboardContainerPrivate
{
public:
    explicit QExtKeyboardContainerPrivate(QExtKeyboardContainer *q);
    virtual ~QExtKeyboardContainerPrivate();

    QExtKeyboardContainer * const q_ptr;

    bool m_hiding;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_bottomLayout;
    QPropertyAnimation *m_animation;
    QExtNormalKeyboard *m_normalKeyboard;
    QExtSymbolKeyboard *m_symbolKeyboard;
    QExtCandidatesListWidget *m_textDisplayWidget;

private:
    QEXT_DECL_PUBLIC(QExtKeyboardContainer)
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardContainerPrivate)
};

QExtKeyboardContainerPrivate::QExtKeyboardContainerPrivate(QExtKeyboardContainer *q)
    : q_ptr(q)
{
}

QExtKeyboardContainerPrivate::~QExtKeyboardContainerPrivate()
{
}

QExtKeyboardContainer::QExtKeyboardContainer(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtKeyboardContainerPrivate(this))
{
    Q_D(QExtKeyboardContainer);
    d->m_normalKeyboard = new QExtNormalKeyboard(this);
    d->m_symbolKeyboard = new QExtSymbolKeyboard(this);
    d->m_textDisplayWidget = new QExtCandidatesListWidget(this);
    d->m_textDisplayWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    d->m_textDisplayWidget->setMinimumSize(400, 50);
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
    //setWindowModality(Qt::WindowModal);
    this->setWindowFlags(windowFlags() | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus);

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

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::changeLanguage, this, &QExtKeyboardContainer::changeLanguage);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::changeLanguage, this, &QExtKeyboardContainer::changeLanguage);
    connect(d->m_normalKeyboard, &QExtNormalKeyboard::changeSymbol, this, &QExtKeyboardContainer::onChangeSymbol);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::changeSymbol, this, &QExtKeyboardContainer::onChangeSymbol);

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::hideKeyboard, this, &QExtKeyboardContainer::hideKeyboard);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::hideKeyboard, this, &QExtKeyboardContainer::hideKeyboard);

    connect(d->m_normalKeyboard, &QExtNormalKeyboard::keyPressed, this, &QExtKeyboardContainer::keyPressed);
    connect(d->m_symbolKeyboard, &QExtSymbolKeyboard::keyPressed, this, &QExtKeyboardContainer::keyPressed);
    connect(d->m_textDisplayWidget,&QExtCandidatesListWidget::chooseText,this,&QExtKeyboardContainer::chooseCandidate);

    d->m_animation = new QPropertyAnimation(this, "pos");
    d->m_animation->setDuration(300);
    connect(d->m_animation, &QAbstractAnimation::finished, this, &QExtKeyboardContainer::onAnimationFinished);
    d->m_hiding = false;

    this->setAttribute(Qt::WA_DeleteOnClose);
}

QExtKeyboardContainer::~QExtKeyboardContainer()
{
    Q_D(QExtKeyboardContainer);
    if(this->isAnimating())
    {
        d->m_animation->stop();
    }
}

bool QExtKeyboardContainer::isAnimating() const
{
    Q_D(const QExtKeyboardContainer);
    return d->m_animation->state() == QAbstractAnimation::Running;
}

void QExtKeyboardContainer::setCandidateList(const QStringList &texts)
{
    Q_D(QExtKeyboardContainer);
    d->m_textDisplayWidget->setCandidatesList(texts);
}

void QExtKeyboardContainer::setLanguageName(const QString &name)
{
    Q_D(QExtKeyboardContainer);
    d->m_normalKeyboard->setCurLanguage(name);
    d->m_symbolKeyboard->setCurLanguage(name);
}

void QExtKeyboardContainer::onChangeSymbol()
{
    Q_D(QExtKeyboardContainer);
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

void QExtKeyboardContainer::onHideSymbol()
{
    Q_D(QExtKeyboardContainer);
    if(!d->m_normalKeyboard->isVisible())
    {
        d->m_normalKeyboard->show();
        d->m_symbolKeyboard->hide();
    }
}

void QExtKeyboardContainer::animationHide()
{
    Q_D(QExtKeyboardContainer);
    int screenHeight = qApp->primaryScreen()->size().height();

    if(this->isAnimating())
    {
        d->m_animation->stop();
    }

    d->m_hiding = true;

    d->m_animation->setStartValue(QPoint(pos().x(),pos().y()));
    d->m_animation->setEndValue(QPoint(pos().x(),screenHeight));
    d->m_animation->start();
}

void QExtKeyboardContainer::animationShow()
{
    Q_D(QExtKeyboardContainer);
    this->move(this->pos().x(),qApp->primaryScreen()->size().height());

    this->show();

    int screenHeight = qApp->primaryScreen()->size().height();

    d->m_animation->setStartValue(QPoint(pos().x(),screenHeight));
    d->m_animation->setEndValue(QPoint(pos().x(),screenHeight - height()));
    d->m_animation->start();
}

void QExtKeyboardContainer::setInputMethodHints(Qt::InputMethodHints hints)
{
    Q_UNUSED(hints);
}

void QExtKeyboardContainer::onAnimationFinished()
{
    Q_D(QExtKeyboardContainer);
    if(d->m_hiding)
    {
        this->hide();
    }

    d->m_hiding = false;
}
