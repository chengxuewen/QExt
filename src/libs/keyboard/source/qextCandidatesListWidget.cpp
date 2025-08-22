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

    int m_curIndex;
    int m_pageIndex;
    int m_headTextIndex;
    int m_tailTextIndex;
    QPushButton *m_lastPage;
    QPushButton *m_nextPage;
    QList<QRect> m_textRects;
    QList<int> m_pageHeadIndex;
    QStringList m_candidatesList;

private:
    QEXT_DECLARE_PUBLIC(QExtCandidatesListWidget)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtCandidatesListWidgetPrivate)
};

QExtCandidatesListWidgetPrivate::QExtCandidatesListWidgetPrivate(QExtCandidatesListWidget *q)
    : q_ptr(q)
    , m_curIndex(0)
    , m_pageIndex(0)
    , m_headTextIndex(0)
    , m_tailTextIndex(0)
    , m_lastPage(QEXT_NULLPTR)
    , m_nextPage(QEXT_NULLPTR)
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
    d->m_lastPage = new QPushButton(this);
    d->m_nextPage= new QPushButton(this);

    d->m_lastPage->setText("<");
    d->m_nextPage->setText(">");

    d->m_lastPage->setMinimumSize(50, 40);
    d->m_nextPage->setMinimumSize(50, 40);

    d->m_nextPage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    d->m_lastPage->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    connect(d->m_lastPage, &QPushButton::clicked,this, &QExtCandidatesListWidget::onLastPage);
    connect(d->m_nextPage, &QPushButton::clicked,this, &QExtCandidatesListWidget::onNextPage);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(d->m_lastPage);
    layout->addWidget(d->m_nextPage);
    layout->addItem(new QSpacerItem(80, 40, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layout->setSpacing(5);

    this->setLayout(layout);
    this->setFont(QFont("Arial",20));

    d->m_lastPage->setEnabled(false);
    d->m_nextPage->setEnabled(false);
}

QExtCandidatesListWidget::~QExtCandidatesListWidget()
{
}

void QExtCandidatesListWidget::setCandidatesList(const QStringList &texts)
{
    Q_D(QExtCandidatesListWidget);
    d->m_candidatesList = texts;
    d->m_pageIndex = 0;
    d->m_curIndex = 0;
    d->m_headTextIndex = 0;
    d->m_tailTextIndex = 0;
    d->m_textRects.clear();
    d->m_pageHeadIndex.clear();
    d->m_pageHeadIndex.append(0);
    this->update();
}

void QExtCandidatesListWidget::onLastPage()
{
    Q_D(QExtCandidatesListWidget);
    if(0 == d->m_pageIndex)
    {
        return;
    }

    --d->m_pageIndex;
    d->m_headTextIndex = d->m_pageHeadIndex.at(d->m_pageIndex);

    if(0 == d->m_pageIndex)
    {
        d->m_lastPage->setEnabled(false);
    }
    this->update();
}

void QExtCandidatesListWidget::clear()
{
}

void QExtCandidatesListWidget::onNextPage()
{
    Q_D(QExtCandidatesListWidget);
    if(d->m_tailTextIndex >= d->m_candidatesList.size() - 1)
    {
        return;
    }

    d->m_lastPage->setEnabled(true);
    d->m_headTextIndex = d->m_tailTextIndex + 1;
    ++d->m_pageIndex;

    if(d->m_pageIndex >= d->m_pageHeadIndex.size())
    {
        d->m_pageHeadIndex.append(d->m_headTextIndex);
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

    QRect rectText = d->m_nextPage->geometry();
    rectText.setLeft(rectText.right() + 20);
    rectText.setRight(width());

    d->m_textRects.clear();
    int i;
    for(i = d->m_headTextIndex;i < d->m_candidatesList.size();++i)
    {
        if(i == d->m_headTextIndex)
        {
            painter.setPen(QColor(Qt::white));
        }
        else
        {
            painter.setPen(QColor(121, 193, 59));
        }

        QString strTextDraw = /*QString::number(i - headTextIndex + 1) + "." + */d->m_candidatesList[i];

        QRect br = painter.boundingRect(rectText,Qt::AlignLeft | Qt::AlignVCenter,strTextDraw);

        if(br.right() + 30 >= this->width())
        {
            d->m_nextPage->setEnabled(true);
            break;
        }
        else
        {
            painter.drawText(rectText,Qt::AlignLeft | Qt::AlignVCenter,strTextDraw);
        }

        d->m_textRects.append(br);
        d->m_tailTextIndex = i;
        rectText.translate(br.width() + 30, 0);
    }

    if(i >= d->m_candidatesList.size())
    {
        d->m_nextPage->setEnabled(false);
    }
}

void QExtCandidatesListWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(QExtCandidatesListWidget);
    for(int i = 0;i < d->m_textRects.size();++i)
    {
        if(d->m_textRects[i].contains(e->pos()))
        {
            this->chooseText(d->m_headTextIndex + i);
        }
    }
}
