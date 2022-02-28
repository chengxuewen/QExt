#include <qextIpAddressEdit.h>
#include <qextIpAddressEdit_p.h>

#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QValidator>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#else
#include <QRegExp>
#endif

QEXTIpAddressEditPrivate::QEXTIpAddressEditPrivate(QEXTIpAddressEdit *q)
    : q_ptr(q)
{

}

QEXTIpAddressEditPrivate::~QEXTIpAddressEditPrivate()
{

}

void QEXTIpAddressEditPrivate::initForm(QEXTIpAddressEdit *qq)
{
    m_backgroundColor = "#FFFFFF";
    m_textColor = "#303030";
    m_dotColor = "#303030";
    m_borderColor = "#A6B5B8";
    m_borderRadius = 3;

    m_labDot1 = new QLabel;
    m_labDot1->setAlignment(Qt::AlignCenter);
    m_labDot1->setText(".");

    m_labDot2 = new QLabel;
    m_labDot2->setAlignment(Qt::AlignCenter);
    m_labDot2->setText(".");

    m_labDot3 = new QLabel;
    m_labDot3->setAlignment(Qt::AlignCenter);
    m_labDot3->setText(".");

    m_txtIP1 = new QLineEdit;
    m_txtIP1->setObjectName("txtIP1");
    m_txtIP1->setAlignment(Qt::AlignCenter);
    m_txtIP1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_txtIP1, SIGNAL(textChanged(QString)), qq, SLOT(textChanged(QString)));

    m_txtIP2 = new QLineEdit;
    m_txtIP2->setObjectName("txtIP2");
    m_txtIP2->setAlignment(Qt::AlignCenter);
    m_txtIP2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_txtIP2, SIGNAL(textChanged(QString)), qq, SLOT(textChanged(QString)));

    m_txtIP3 = new QLineEdit;
    m_txtIP3->setObjectName("txtIP3");
    m_txtIP3->setAlignment(Qt::AlignCenter);
    m_txtIP3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_txtIP3, SIGNAL(textChanged(QString)), qq, SLOT(textChanged(QString)));

    m_txtIP4 = new QLineEdit;
    m_txtIP4->setObjectName("txtIP4");
    m_txtIP4->setAlignment(Qt::AlignCenter);
    m_txtIP4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QObject::connect(m_txtIP4, SIGNAL(textChanged(QString)), qq, SLOT(textChanged(QString)));

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    QRegularExpression regExp("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
    m_txtIP1->setValidator(new QRegularExpressionValidator(regExp, qq));
    m_txtIP2->setValidator(new QRegularExpressionValidator(regExp, qq));
    m_txtIP3->setValidator(new QRegularExpressionValidator(regExp, qq));
    m_txtIP4->setValidator(new QRegularExpressionValidator(regExp, qq));
#else
    QRegExp regExp("(2[0-5]{2}|2[0-4][0-9]|1?[0-9]{1,2})");
    m_txtIP1->setValidator(new QRegExpValidator(regExp, qq));
    m_txtIP2->setValidator(new QRegExpValidator(regExp, qq));
    m_txtIP3->setValidator(new QRegExpValidator(regExp, qq));
    m_txtIP4->setValidator(new QRegExpValidator(regExp, qq));
#endif

    m_txtIP1->installEventFilter(qq);
    m_txtIP2->installEventFilter(qq);
    m_txtIP3->installEventFilter(qq);
    m_txtIP4->installEventFilter(qq);

    QFrame *frame = new QFrame(qq);
    frame->setObjectName("frameIP");

    QVBoxLayout *verticalLayout = new QVBoxLayout(qq);
    verticalLayout->setMargin(0);
    verticalLayout->setSpacing(0);
    verticalLayout->addWidget(frame);

    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_txtIP1);
    layout->addWidget(m_labDot1);
    layout->addWidget(m_txtIP2);
    layout->addWidget(m_labDot2);
    layout->addWidget(m_txtIP3);
    layout->addWidget(m_labDot3);
    layout->addWidget(m_txtIP4);
}

void QEXTIpAddressEditPrivate::updateQSS(QEXTIpAddressEdit *qq)
{
    QStringList qss;
    qss.append(QString("QFrame#frameIP{border:1px solid %1;border-radius:%2px;}").arg(m_borderColor.name()).arg(m_borderRadius));
    qss.append(QString("QLabel{min-width:15px;background-color:%1;color:%2;}").arg(m_backgroundColor.name()).arg(m_dotColor.name()));
    qss.append(QString("QLineEdit{background-color:%1;color:%2;border:none;}").arg(m_backgroundColor.name()).arg(m_textColor.name()));
    qss.append(QString("QLineEdit#txtIP1{border-top-left-radius:%1px;border-bottom-left-radius:%1px;}").arg(m_borderRadius));
    qss.append(QString("QLineEdit#txtIP4{border-top-right-radius:%1px;border-bottom-right-radius:%1px;}").arg(m_borderRadius));
    qq->setStyleSheet(qss.join(""));
}


QEXTIpAddressEdit::QEXTIpAddressEdit(QWidget *parent)
    : QWidget(parent), dd_ptr(new QEXTIpAddressEditPrivate(this))
{
    Q_D(QEXTIpAddressEdit);
    this->setObjectName("IpAddressEdit");
    d->initForm(this);
    d->updateQSS(this);
}

QEXTIpAddressEdit::~QEXTIpAddressEdit()
{

}

bool QEXTIpAddressEdit::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QEXTIpAddressEdit);
    if (event->type() == QEvent::KeyPress)
    {
        QLineEdit *txt = (QLineEdit *)watched;
        if (txt == d->m_txtIP1 || txt == d->m_txtIP2 || txt == d->m_txtIP3 || txt == d->m_txtIP4)
        {
            QKeyEvent *key = (QKeyEvent *)event;

            if (key->text() == ".")
            {
                this->focusNextChild();
            }

            if (key->key() == Qt::Key_Backspace)
            {
                if (txt->text().length() <= 1)
                {
                    this->focusNextPrevChild(false);
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void QEXTIpAddressEdit::textChanged(const QString &text)
{
    Q_D(QEXTIpAddressEdit);
    int len = text.length();
    int value = text.toInt();

    if (len == 3)
    {
        if (value >= 100 && value <= 255)
        {
            this->focusNextChild();
        }
    }

    d->m_ip = QString("%1.%2.%3.%4").arg(d->m_txtIP1->text()).arg(d->m_txtIP2->text()).arg(d->m_txtIP3->text()).arg(d->m_txtIP4->text());
    emit this->ipChanged(d->m_ip);
}

QString QEXTIpAddressEdit::iP() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_ip;
}

QColor QEXTIpAddressEdit::backgroundColor() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_backgroundColor;
}

QColor QEXTIpAddressEdit::textColor() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_textColor;
}

QColor QEXTIpAddressEdit::dotColor() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_dotColor;
}

QColor QEXTIpAddressEdit::borderColor() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_borderColor;
}

int QEXTIpAddressEdit::borderRadius() const
{
    Q_D(const QEXTIpAddressEdit);
    return d->m_borderRadius;
}

QSize QEXTIpAddressEdit::sizeHint() const
{
    return QSize(250, 20);
}

QSize QEXTIpAddressEdit::minimumSizeHint() const
{
    return QSize(30, 10);
}

void QEXTIpAddressEdit::setIP(const QString &ip)
{
    Q_D(QEXTIpAddressEdit);
    QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    if (!regExp.exactMatch(ip))
    {
        return;
    }

    if (ip != d->m_ip)
    {
        d->m_ip = ip;

        QStringList list = ip.split(".");
        d->m_txtIP1->setText(list.at(0));
        d->m_txtIP2->setText(list.at(1));
        d->m_txtIP3->setText(list.at(2));
        d->m_txtIP4->setText(list.at(3));
    }
}

void QEXTIpAddressEdit::clear()
{
    Q_D(QEXTIpAddressEdit);
    d->m_txtIP1->clear();
    d->m_txtIP2->clear();
    d->m_txtIP3->clear();
    d->m_txtIP4->clear();
    d->m_txtIP1->setFocus();
}

void QEXTIpAddressEdit::setBackgroundColor(const QColor &color)
{
    Q_D(QEXTIpAddressEdit);
    if (d->m_backgroundColor != color)
    {
        d->m_backgroundColor = color;
        d->updateQSS(this);
    }
}

void QEXTIpAddressEdit::setTextColor(const QColor &color)
{
    Q_D(QEXTIpAddressEdit);
    if (d->m_textColor != color)
    {
        d->m_textColor = color;
        d->updateQSS(this);
    }
}

void QEXTIpAddressEdit::setDotColor(const QColor &color)
{
    Q_D(QEXTIpAddressEdit);
    if (d->m_dotColor != color)
    {
        d->m_dotColor = color;
        d->updateQSS(this);
    }
}

void QEXTIpAddressEdit::setBorderColor(const QColor &color)
{
    Q_D(QEXTIpAddressEdit);
    if (d->m_borderColor != color)
    {
        d->m_borderColor = color;
        d->updateQSS(this);
    }
}

void QEXTIpAddressEdit::setBorderRadius(int radius)
{
    Q_D(QEXTIpAddressEdit);
    if (d->m_borderRadius != radius)
    {
        d->m_borderRadius = radius;
        d->updateQSS(this);
    }
}
