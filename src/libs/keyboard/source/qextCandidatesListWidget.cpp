#include <qextCandidatesListWidget.h>

#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QDebug>
#include <QtWidgets>

class QExtCandidatesListWidgetPrivate
{
public:
    explicit QExtCandidatesListWidgetPrivate(QExtCandidatesListWidget *q);
    virtual ~QExtCandidatesListWidgetPrivate();

    QExtCandidatesListWidget * const q_ptr;

    int mCurIndex;
    int mPageIndex;
    int mHeadTextIndex;
    int mTailTextIndex;
    QPushButton *mLastPage;
    QPushButton *mNextPage;
    QList<QRect> mTextRects;
    QList<int> mPageHeadIndex;
    QStringList mCandidatesList;

private:
    QEXT_DECLARE_PUBLIC(QExtCandidatesListWidget)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtCandidatesListWidgetPrivate)
};

QExtCandidatesListWidgetPrivate::QExtCandidatesListWidgetPrivate(QExtCandidatesListWidget *q)
    : q_ptr(q)
    , mCurIndex(0)
    , mPageIndex(0)
    , mHeadTextIndex(0)
    , mTailTextIndex(0)
    , mLastPage(QEXT_NULLPTR)
    , mNextPage(QEXT_NULLPTR)
{
}

QExtCandidatesListWidgetPrivate::~QExtCandidatesListWidgetPrivate()
{
}

QExtCandidatesListWidget::QExtCandidatesListWidget(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtCandidatesListWidgetPrivate(this))
{
    Q_D(QExtCandidatesListWidget);
    d->mLastPage = new QPushButton(this);
    d->mNextPage= new QPushButton(this);

    d->mLastPage->setText("<");
    d->mNextPage->setText(">");

    d->mLastPage->setMinimumSize(50, 40);
    d->mNextPage->setMinimumSize(50, 40);

    d->mNextPage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    d->mLastPage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    connect(d->mLastPage, &QPushButton::clicked,this, &QExtCandidatesListWidget::onLastPage);
    connect(d->mNextPage, &QPushButton::clicked,this, &QExtCandidatesListWidget::onNextPage);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(d->mLastPage);
    layout->addWidget(d->mNextPage);
    layout->addItem(new QSpacerItem(80, 40, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->setSpacing(5);

    this->setLayout(layout);
    this->setFont(QFont("Arial",20));

    d->mLastPage->setEnabled(false);
    d->mNextPage->setEnabled(false);
}

QExtCandidatesListWidget::~QExtCandidatesListWidget()
{
}

void QExtCandidatesListWidget::setCandidatesList(const QStringList &texts)
{
    Q_D(QExtCandidatesListWidget);
    d->mCandidatesList = texts;
    d->mPageIndex = 0;
    d->mCurIndex = 0;
    d->mHeadTextIndex = 0;
    d->mTailTextIndex = 0;
    d->mTextRects.clear();
    d->mPageHeadIndex.clear();
    d->mPageHeadIndex.append(0);
    this->update();
}

void QExtCandidatesListWidget::onLastPage()
{
    Q_D(QExtCandidatesListWidget);
    if(0 == d->mPageIndex)
    {
        return;
    }

    --d->mPageIndex;
    d->mHeadTextIndex = d->mPageHeadIndex.at(d->mPageIndex);

    if(0 == d->mPageIndex)
    {
        d->mLastPage->setEnabled(false);
    }
    this->update();
}

void QExtCandidatesListWidget::clear()
{
}

void QExtCandidatesListWidget::onNextPage()
{
    Q_D(QExtCandidatesListWidget);
    if(d->mTailTextIndex >= d->mCandidatesList.size() - 1)
    {
        return;
    }

    d->mLastPage->setEnabled(true);
    d->mHeadTextIndex = d->mTailTextIndex + 1;
    ++d->mPageIndex;

    if(d->mPageIndex >= d->mPageHeadIndex.size())
    {
        d->mPageHeadIndex.append(d->mHeadTextIndex);
    }
    this->update();
}

void QExtCandidatesListWidget::paintEvent(QPaintEvent *event)
{
    Q_D(QExtCandidatesListWidget);
    Q_UNUSED(event)

    QPainter painter(this);

    QFont font("Microsoft YaHei",18);
    painter.setFont(font);

    QRect rectText = d->mNextPage->geometry();
    rectText.setLeft(rectText.right() + 20);
    rectText.setRight(width());

    d->mTextRects.clear();
    int i;
    for(i = d->mHeadTextIndex;i < d->mCandidatesList.size();++i)
    {
        if(i == d->mHeadTextIndex)
        {
            painter.setPen(QColor(Qt::white));
        }
        else
        {
            painter.setPen(QColor(121, 193, 59));
        }

        QString strTextDraw = /*QString::number(i - headTextIndex + 1) + "." + */d->mCandidatesList[i];

        QRect br = painter.boundingRect(rectText,Qt::AlignLeft | Qt::AlignVCenter,strTextDraw);

        if(br.right() + 30 >= this->width())
        {
            d->mNextPage->setEnabled(true);
            break;
        }
        else
        {
            painter.drawText(rectText,Qt::AlignLeft | Qt::AlignVCenter,strTextDraw);
        }

        d->mTextRects.append(br);
        d->mTailTextIndex = i;
        rectText.translate(br.width() + 30, 0);
    }

    if(i >= d->mCandidatesList.size())
    {
        d->mNextPage->setEnabled(false);
    }
}

void QExtCandidatesListWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtCandidatesListWidget);
    for(int i = 0;i < d->mTextRects.size();++i)
    {
        if(d->mTextRects[i].contains(e->pos()))
        {
            this->chooseText(d->mHeadTextIndex + i);
        }
    }
}
