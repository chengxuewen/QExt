#include <private/qextKeyboard_p.h>

#include <QDebug>
#include <QRegExp>
#include <QVBoxLayout>
#include <QListWidgetItem>
#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
#   include <QScroller>
#endif

/***********************************************************************************************************************
** QExtKeyButton
***********************************************************************************************************************/
QExtKeyButton::Type QExtKeyButton::find(const QString &value)
{
    QRegExp rx("[a-z]");
    if (rx.exactMatch(value))
    {
        return QExtKeyButton::LowerCase;
    }

    rx = QRegExp("[A-Z]");
    if (rx.exactMatch(value))
    {
        return QExtKeyButton::UpperCase;
    }

    return QExtKeyButton::SpecialChar;
}

QExtKeyButton::Mode QExtKeyButton::find(QExtKeyButton::Type type)
{
    foreach (QExtKeyButton::Mode mode, m_modes)
    {
        if (mode.type == type)
        {
            return mode;
        }
    }

    return m_modes.first();
}

QExtKeyButton::Mode QExtKeyButton::findNext()
{
    for(int i = 0; i < m_modes.count(); i++)
    {
        QExtKeyButton::Mode mode = m_modes[i];
        if (mode.display == m_mode.display)
        {
            if (i+1 < m_modes.count())
            {
                return m_modes.at(i+1);
            }
            else
            {
                return m_modes.first();
            }
        }
    }

    return m_modes.first();
}

void QExtKeyButton::setDisplayContent(const QVariant &content)
{
    if (content.type() == QVariant::String)
    {
        const QString &text = content.toString().toStdString().data();
        this->setText(text);
    }
    else if (content.type() == QVariant::Icon)
    {
        const QIcon &icon = content.value<QIcon>();
        this->setIcon(icon);
        this->setIconSize(QSize(1.2 * width(), 1.2 * height()));
    }
}

QExtKeyButton::QExtKeyButton(const QList<QExtKeyButton::Mode> modes, QWidget *parent)
    : QPushButton(parent)
{
    Q_ASSERT(!modes.isEmpty());
    this->setFocusPolicy(Qt::NoFocus);
    this->setAutoRepeat(true);

    foreach (Mode mode, modes)
    {
        if (mode.type == Auto)
        {
            mode.type = find(mode.value);
        }

        if (mode.display.isNull())
        {
            mode.display = mode.value;
        }
        m_modes.append(mode);
    }

    if (!modes.isEmpty())
    {
        m_preMode = m_mode = m_modes.first();
        this->setDisplayContent(m_mode.display);
    }

    connect(this, SIGNAL(pressed()), this, SLOT(onPressed()));
}

QExtKeyButton::Mode QExtKeyButton::mode()
{
    return m_mode;
}

void QExtKeyButton::onReponse(const QObject *receiverObj, const QString &receiver)
{
    connect(this, SIGNAL(pressed(int,QString)), receiverObj, receiver.toStdString().c_str());
}

void QExtKeyButton::switchCapsLock()
{
    if (m_mode.type == SpecialChar)
    {
        return;
    }

    m_preMode = m_mode;
    m_mode = find(m_mode.type == LowerCase ? UpperCase : LowerCase);
    this->setDisplayContent(m_mode.display);
}

void QExtKeyButton::switchSpecialChar()
{
    if (m_mode.type == SpecialChar)
    {
        m_mode = m_preMode;
    }
    else
    {
        m_preMode = m_mode;
        m_mode = find(SpecialChar);
    }

    this->setDisplayContent(m_mode.display);
}

void QExtKeyButton::switching()
{
    m_mode = findNext();
    this->setDisplayContent(m_mode.display);
}

void QExtKeyButton::onPressed()
{
    emit this->pressed(m_mode.key, m_mode.value);
}


/***********************************************************************************************************************
** QExtNumberKeyboard
***********************************************************************************************************************/
typedef QList<QExtKeyButton::Mode> Modes;
typedef QList<Modes> ModesList;

static const char *s_backspace_icon = ":/Image/backspace.png";
static const char *s_space_icon     = ":/Image/space.png";
static const char *s_pack_up_icon   = ":/Image/pack_up.png";

QExtNumberKeyboard::QExtNumberKeyboard(QWidget *parent) : QExtAbstractKeyboard(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setSpacing(0);
    layout->setMargin(0);


    auto createLayout = [&](ModesList list)
    {
        QHBoxLayout *h = new QHBoxLayout;
        h->setSizeConstraint(QLayout::SetNoConstraint);

        foreach (Modes iter, list)
        {
            QExtKeyButton *button = createButton(iter);
            h->addWidget(button);
        }

        layout->addLayout(h);
    };

    const QList<Modes> modeListBar1 = {
                                       {{Qt::Key_1, "1"}},
                                       {{Qt::Key_2, "2"}},
                                       {{Qt::Key_3, "3"}},
                                       {{Qt::Key_Backspace, "", QIcon(s_backspace_icon)}},
                                       };

    const QList<Modes> modeListBar2 = {
                                       {{Qt::Key_4, "4"}},
                                       {{Qt::Key_5, "5"}},
                                       {{Qt::Key_6, "6"}},
                                       {{Qt::Key_Escape, "", QIcon(s_pack_up_icon)}},
                                       };

    const QList<Modes> modeListBar3 = {
                                       {{Qt::Key_7, "7"}},
                                       {{Qt::Key_8, "8"}},
                                       {{Qt::Key_9, "9"}},
                                       {{Qt::Key_Minus, ","}},
                                       };

    const QList<Modes> modeListBar4 = {
                                       {{Qt::Key_unknown, "."}},
                                       {{Qt::Key_0, "0"}},
                                       {{Qt::Key_Space, " ", QIcon(s_space_icon)}},
                                       {{Qt::Key_unknown, ":"}},
                                       };

    createLayout(modeListBar1);
    createLayout(modeListBar2);
    createLayout(modeListBar3);
    createLayout(modeListBar4);

    this->setLayout(layout);
}

QExtKeyButton *QExtNumberKeyboard::createButton(QList<QExtKeyButton::Mode> modes)
{
    QExtKeyButton *button = new QExtKeyButton(modes, this);
    button->onReponse(this, SLOT(onButtonPressed(const int&, const QString&)));
    button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return button;
}

void QExtNumberKeyboard::onButtonPressed(const int &code, const QString &text)
{
    this->onKeyPressed(code, text);
}


/***********************************************************************************************************************
** QExtKeyboard
***********************************************************************************************************************/
QExtKeyboardPrivate::QExtKeyboardPrivate(QExtKeyboard *q)
    : q_ptr(q)
{

}

QExtKeyboardPrivate::~QExtKeyboardPrivate()
{

}


typedef QList<QExtKeyButton::Mode> Modes;
typedef QList<Modes> ModesList;

const int NORMAL_BUTTON_WIDTH  = 55;
const int NORMAL_BUTTON_HEIGHT = 45;

const QString BACKSPACE_ICON = ":/Image/backspace.png";
const QString ENTER_ICON     = ":/Image/enter.png";
const QString SPACE_ICON     = ":/Image/space.png";
const QString CAPLOCK_ICON   = ":/Image/caplock.png";

const double BUTTON_SPACING_RATIO = 0.030;
const double BUTTON_WIDTH_RATIO   = 0.09;
const double BUTTON_HEIGHT_RATIO  = 0.2;

const QList<Modes> modeListBar1 =
    {
    {{Qt::Key_Q, "q"}, {Qt::Key_Q, "Q"}, {Qt::Key_1, "1"}},
    {{Qt::Key_W, "w"}, {Qt::Key_W, "W"}, {Qt::Key_2, "2"}},
    {{Qt::Key_E, "e"}, {Qt::Key_E, "E"}, {Qt::Key_3, "3"}},
    {{Qt::Key_R, "r"}, {Qt::Key_R, "R"}, {Qt::Key_4, "4"}},
    {{Qt::Key_T, "t"}, {Qt::Key_T, "T"}, {Qt::Key_5, "5"}},
    {{Qt::Key_Y, "y"}, {Qt::Key_Y, "Y"}, {Qt::Key_6, "6"}},
    {{Qt::Key_U, "u"}, {Qt::Key_U, "U"}, {Qt::Key_7, "7"}},
    {{Qt::Key_I, "i"}, {Qt::Key_I, "I"}, {Qt::Key_8, "8"}},
    {{Qt::Key_O, "o"}, {Qt::Key_O, "O"}, {Qt::Key_9, "9"}},
    {{Qt::Key_P, "p"}, {Qt::Key_P, "P"}, {Qt::Key_0, "0"}},
};

const QList<Modes> modeListBar2 =
    {
    {{Qt::Key_A, "a"}, {Qt::Key_A, "A"}, {Qt::Key_unknown, "."}},
    {{Qt::Key_S, "s"}, {Qt::Key_S, "S"}, {Qt::Key_unknown, "?"}},
    {{Qt::Key_D, "d"}, {Qt::Key_D, "D"}, {Qt::Key_At,      "!"}},
    {{Qt::Key_F, "f"}, {Qt::Key_F, "F"}, {Qt::Key_NumberSign, "*"}},
    {{Qt::Key_G, "g"}, {Qt::Key_G, "G"}, {Qt::Key_Percent, "#"}},
    {{Qt::Key_H, "h"}, {Qt::Key_H, "H"}, {Qt::Key_unknown, "\""}},
    {{Qt::Key_J, "j"}, {Qt::Key_J, "J"}, {Qt::Key_unknown, "&", "&&"}},
    {{Qt::Key_K, "k"}, {Qt::Key_K, "K"}, {Qt::Key_unknown, "%"}},
    {{Qt::Key_L, "l"}, {Qt::Key_L, "L"}, {Qt::Key_unknown, "@"}},
};

const QList<Modes> modeListBar3 =
    {
    {{Qt::Key_CapsLock, "", ""/*大小写切换*/}},
    {{Qt::Key_Z, "z"}, {Qt::Key_Z, "Z"}, {Qt::Key_ParenLeft, "("}},
    {{Qt::Key_X, "x"}, {Qt::Key_X, "X"}, {Qt::Key_ParenLeft, ")"}},
    {{Qt::Key_C, "c"}, {Qt::Key_C, "C"}, {Qt::Key_Minus,     "-"}},
    {{Qt::Key_V, "v"}, {Qt::Key_V, "V"}, {Qt::Key_unknown,   "_"}},
    {{Qt::Key_B, "b"}, {Qt::Key_B, "B"}, {Qt::Key_unknown,   ":"}},
    {{Qt::Key_N, "n"}, {Qt::Key_N, "N"}, {Qt::Key_Semicolon, ";"}},
    {{Qt::Key_M, "m"}, {Qt::Key_M, "M"}, {Qt::Key_Slash,     "/"}},
    {{Qt::Key_Backspace, "", ""/*退格*/}}
};

const QList<Modes> modeListBar4 =
    {
    {{Qt::Key_Mode_switch, "",  "?123"}},
    {{Qt::Key_Context1,    "",  "En"},    {Qt::Key_Context1, "", QStringLiteral("中")}},
    {{Qt::Key_Space,       " ", ""/*空格*/}},
    {{Qt::Key_Enter,       "",  ""/*换行*/}}
};


QExtKeyboard::QExtKeyboard(QWidget *parent)
    : QExtAbstractKeyboard(parent)
    , m_isChinese(false)
    , dd_ptr(new QExtKeyboardPrivate(this))
{
    m_chineseWidget = new ChineseWidget(this);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    resize(850, 320);
    resizeButton();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addWidget(chineseBar(), 12);
    layout->addLayout(h1(), 15);
    layout->addLayout(h2(), 15);
    layout->addLayout(h3(), 15);
    layout->addLayout(h4(), 15);

    setLayout(layout);

    connect(m_chineseWidget, SIGNAL(pressedChanged(int, const QString &)), this, SLOT(onKeyPressed(int, const QString &)));
    connect(m_chineseWidget, SIGNAL(pressedChanged(const int &, const QString &)), this, SLOT(clearBufferText()));
}

QExtKeyboard::~QExtKeyboard()
{

}

void QExtKeyboard::resizeEvent(QResizeEvent *e)
{
    resizeButton();
}

void QExtKeyboard::switchCapsLock()
{
    QList<QExtKeyButton *> buttons = findChildren<QExtKeyButton *>();
    foreach(QExtKeyButton *button, buttons)
    {
        button->switchCapsLock();
    }
}

void QExtKeyboard::switchSpecialChar()
{
    QList<QExtKeyButton *> buttons = findChildren<QExtKeyButton *>();
    foreach(QExtKeyButton *button, buttons)
    {
        button->switchSpecialChar();
    }
}

void QExtKeyboard::switchEnOrCh()
{
    m_isChinese = !m_isChinese;
    QList<QExtKeyButton *> buttons = findChildren<QExtKeyButton *>();
    foreach(QExtKeyButton *button, buttons)
    {
        if (button->mode().key == Qt::Key_Context1)
        {
            button->switching();
        }
    }
}

void QExtKeyboard::onButtonPressed(const int &code, const QString &text)
{

    if (! m_isChinese)
    {
        this->onKeyPressed(code, text);
        m_bufferText.clear();
        return;
    }

    QRegExp rx("[a-zA-Z]");
    if (!rx.exactMatch(text) && m_bufferText.isEmpty())
    {
        this->onKeyPressed(code, text);
        return;
    }

    if (code == Qt::Key_Backspace)
    {
        m_bufferText.chop(1);
    }
    else
    {
        m_bufferText.append(text);
    }
    m_chineseWidget->setText(m_bufferText);
}

void QExtKeyboard::clearBufferText()
{
    m_bufferText.clear();
}

QExtKeyButton *QExtKeyboard::createButton(QList<QExtKeyButton::Mode> modes)
{
    QExtKeyButton *button = new QExtKeyButton(modes, this);
    button->onReponse(this, SLOT(onButtonPressed(const int&, const QString&)));
    button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return button;
}

QWidget *QExtKeyboard::createBar(const QList<QList<QExtKeyButton::Mode> > &modes)
{
    QWidget *widget = new QWidget;

    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < modes.count(); i++)
    {
        QExtKeyButton *button = createButton(modes.at(i));
        h->addWidget(button);
    }

    widget->setLayout(h);
    return widget;
}

QWidget *QExtKeyboard::chineseBar()
{
    m_chineseWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return m_chineseWidget;
}

QHBoxLayout *QExtKeyboard::h1()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSizeConstraint(QLayout::SetNoConstraint);
    for (int i = 0; i < modeListBar1.count(); i++)
    {
        QExtKeyButton *button = createButton(modeListBar1.at(i));
        h->addWidget(button);
    }

    return h;
}

QHBoxLayout *QExtKeyboard::h2()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->addSpacing(20);
    for (int i = 0; i < modeListBar2.count(); i++)
    {
        QExtKeyButton *button = createButton(modeListBar2.at(i));
        h->addWidget(button);
    }
    h->addSpacing(20);

    return h;
}

QHBoxLayout *QExtKeyboard::h3()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(0);
    for (int i = 0; i < modeListBar3.count(); i++)
    {
        QExtKeyButton *button = createButton(modeListBar3.at(i));
        if (i == 0 || i == (modeListBar3.count() - 1))
        {
            h->addWidget(button, 70);
        }
        else
        {
            h->addWidget(button, 69);
        }
    }

    return h;
}

QHBoxLayout *QExtKeyboard::h4()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(0);
    for (int i = 0; i < modeListBar4.count(); i++)
    {
        QExtKeyButton *button = this->createButton(modeListBar4.at(i));
        if (i == 0)
        {
            h->addWidget(button, 12);
        }
        if (i == 1)
        {
            h->addWidget(button, 10);
        }
        if (i == 2)
        {
            h->addWidget(button, 56);
        }
        if (i == 3)
        {
            h->addWidget(button, 22);
        }
    }

    return h;
}

QWidget *QExtKeyboard::candidateList()
{
    return m_chineseWidget;
}

void QExtKeyboard::resizeButton()
{
    foreach (QExtKeyButton *button, findChildren<QExtKeyButton *>())
    {
        int fixedWidth = width()*BUTTON_WIDTH_RATIO;
        int fixedHeight = height()*BUTTON_HEIGHT_RATIO;
        button->setIconSize(QSize(2*fixedWidth/3, 2*fixedHeight/3));

        switch (button->mode().key)
        {
        case Qt::Key_Backspace:
            button->setIcon(QIcon(BACKSPACE_ICON));
            break;
        case Qt::Key_CapsLock:
            button->setIcon(QIcon(CAPLOCK_ICON));
            connect(button, SIGNAL(pressed()), this, SLOT(switchCapsLock()), Qt::UniqueConnection);
            break;
        case Qt::Key_Mode_switch:
            connect(button, SIGNAL(pressed()), this, SLOT(switchSpecialChar()), Qt::UniqueConnection);
            break;
        case Qt::Key_Context1:
            connect(button, SIGNAL(pressed()), this, SLOT(switchEnOrCh()), Qt::UniqueConnection);
            break;
        case Qt::Key_Enter:
            button->setIcon(QIcon(ENTER_ICON));
            break;
        case Qt::Key_Space:
            button->setIcon(QIcon(SPACE_ICON));
            break;
        default:
            break;
        }
    }
}

ChineseWidget::ChineseWidget(QWidget *parent)
    : QListWidget(parent)
{
#ifdef ENABLED_CHINESE_LIB
    loadChineseLib();
#endif

#ifdef ENABLED_CHINESE_PHRASE_LIB
    loadChinesePhraseLib();
#endif

#ifdef ENABLED_GOOGLE_CHINESE_LIB
    loadGoogleChineseLib();
#endif

    this->setFocusPolicy(Qt::NoFocus);
    /* 设置为列表显示模式 */
    this->setViewMode(QListView::ListMode);

    /* 从左往右排列 */
    this->setFlow(QListView::LeftToRight);

    /* 屏蔽水平滑动条 */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 屏蔽垂直滑动条 */
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 设置为像素滚动 */
    this->setHorizontalScrollMode(QListWidget::ScrollPerPixel);

#if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
    /* 设置鼠标左键拖动 */
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);
#endif

    /* 设置样式 */
    setStyleSheet("                                                                           \
                  QListWidget { outline: none; border:1px solid #00000000; color: black; }    \
                  QListWidget::Item { width: 50px; height: 50px; }                            \
                  QListWidget::Item:hover { background: #4395ff; color: white; }              \
                  QListWidget::item:selected { background: #4395ff; color: black; }           \
                  QListWidget::item:selected:!active { background: #00000000; color: black; } \
                  ");

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

void ChineseWidget::setText(const QString &text)
{
    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem *item = takeItem(i);
        delete item;
        item = NULL;
    }

    this->clear();
    this->addOneItem(text);

    if (!m_data.contains(text.left(1)))
    {
        return;
    }

    /* 通过获取首字母索引词库内容，用于加快匹配词(组)。 */
    const QList<QPair<QString, QString> > &tmp = m_data[text.left(1)];
    for (int i = 0; i < tmp.count(); i++)
    {
        const QPair<QString, QString> &each = tmp.at(i);
        /* 模糊匹配 */
        if (each.first.left(text.count()) != text)
        {
            continue;
        }

        /* 添加到候选栏, 并限制数量 */
        if (this->count() <= 30)
        {
            this->addOneItem(each.second);
        }
        else
        {
            break;
        }
    }
}

void ChineseWidget::onItemClicked(QListWidgetItem *item)
{
    emit this->pressedChanged(-1, item->text());
    this->setText("");
}

void ChineseWidget::addOneItem(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text, this);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(50);
    item->setFont(font);

    /* 设置文字居中 */
    item->setTextAlignment(Qt::AlignCenter);
    bool isChinese = QRegExp("^[\u4E00-\u9FA5]+").indexIn(text.left(1)) != -1;

    int width = font.pointSize();
    if (isChinese)
    {
        width += text.count()*font.pointSize()*1.5;
    }
    else
    {
        width += text.count()*font.pointSize()*2/3;
    }

    item->setSizeHint(QSize(width, 50));
    this->addItem(item);
}

void ChineseWidget::loadChineseLib()
{
    QFile pinyin(":/QExtWidgets/pinyin/pinyin.txt");
    if (! pinyin.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open pinyin file failed!";
        return;
    }

    while (! pinyin.atEnd())
    {
        QString buf = QString::fromUtf8(pinyin.readLine()).trimmed();
        QRegExp regExp("^[\u4E00-\u9FA5]+");

        int index = regExp.indexIn(buf);
        if (index == -1)
        {
            continue;
        }

        QString first = buf.right(buf.size() - regExp.matchedLength());
        QString second = buf.mid(index, regExp.matchedLength());

        QList<QPair<QString, QString> > &tmp = m_data[first.left(1)];
        tmp.append(qMakePair(first, second));
    }

    pinyin.close();
}

void ChineseWidget::loadChinesePhraseLib()
{
    /* 加载词组字库内容 */
    QFile pinyin(":/QExtWidgets/pinyin/pinyin_phrase.txt");
    if (! pinyin.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open pinyin file failed!";
        return;
    }

    /* 按行读取内容 */
    while (! pinyin.atEnd())
    {
        QString buf = QString::fromUtf8(pinyin.readLine()).trimmed();
        if (buf.isEmpty())
        {
            continue;
        }

        /* 去除#号后的注释内容 */
        if (buf.left(1) == "#")
        {
            continue;
        }

        /* 正则匹配词组内容并通过组捕获获取'词组'和'拼音' */
        QRegExp regExp("(\\S+): ([\\S ]+)");
        int pos = 0;
        while ((pos = regExp.indexIn(buf, pos)) != -1)
        {
            pos += regExp.matchedLength();
            QString second = regExp.cap(1);  /* 词组 */
            QString first = regExp.cap(2); /* 拼音 */

            QStringList strList = first.split(" ");
            QString abb;
            for (int i = 0; i < strList.count(); i++)
            {
                /* 获得拼音词组的首字母(用于缩写匹配) */
                abb += strList.at(i).left(1);
            }
            QList<QPair<QString, QString> > &tmp = m_data[first.left(1)];
            /* 将'拼音(缩写)'和'词组'写入匹配容器 */
            tmp.append(qMakePair(abb, second));
            /* 将'拼音(全拼)'和'词组'写入匹配容器 */
            tmp.append(qMakePair(first.remove(" "), second));
        }
    }

    pinyin.close();
}

void ChineseWidget::loadGoogleChineseLib()
{
    QFile file(":/QExtWidgets/pinyin/rawdict_utf16_65105_freq_sort.txt");
    if (! file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open pinyin file failed!" << file.fileName();
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-16"); // change the file codec to UTF-16.

    QStringList lines = in.readAll().split("\n");

    for (QString each : lines)
    {
        QRegExp re(R"RX((\S+).((?:-?\d+)(?:\.\d+)).((?:-?\d+)(?:\.\d+)?).(.*))RX");
        int pos = 0;

        bool isMatching = false;
        while ((pos = re.indexIn(each, pos)) != -1)
        {
            pos += re.matchedLength();
            if (re.captureCount() != 4)
            {
                continue;
            }

            isMatching = true;
            QString hanzi = re.cap(1); // 汉字
            QString weight = re.cap(2); // 权重
            QString tmp = re.cap(3); // 未知
            QString pinyin = re.cap(4); // 拼音(可能是词组)

            QStringList strList = pinyin.split(" ");
            QString abb;
            for (int i = 0; i < strList.count(); i++)
            {
                /* 获得拼音词组的首字母(用于缩写匹配) */
                abb += strList.at(i).left(1);
            }

            QList<QPair<QString, QString> > &list = m_data[pinyin.left(1)];
            if (strList.count() > 1)
            {
                /* 将'拼音(缩写)'和'词组'写入匹配容器 */
                list.append(qMakePair(abb, hanzi));
            }
            /* 将'拼音(全拼)'和'词组'写入匹配容器 */
            list.append(qMakePair(pinyin.remove(" "), hanzi));
        }

        if (!isMatching)
        {
            qDebug() << each;
        }
    }

    file.close();
}
