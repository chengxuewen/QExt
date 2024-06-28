#include <qextSymbolKeyboard.h>
#include <ui_qextSymbolKeyboard.h>

QExtSymbolKeyboard::QExtSymbolKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtSymbolKeyboard)
{
    ui->setupUi(this);

    m_curPage = 0;
    m_maxPage = 2;

    m_page1.append({Qt::Key_1,"1"});
    m_page1.append({Qt::Key_2,"2"});
    m_page1.append({Qt::Key_3,"3"});
    m_page1.append({Qt::Key_4,"4"});
    m_page1.append({Qt::Key_5,"5"});
    m_page1.append({Qt::Key_6,"6"});
    m_page1.append({Qt::Key_7,"7"});
    m_page1.append({Qt::Key_8,"8"});
    m_page1.append({Qt::Key_9,"9"});
    m_page1.append({Qt::Key_0,"0"});

    m_page1.append({Qt::Key_At,"@"});
    m_page1.append({Qt::Key_NumberSign,"#"});
    m_page1.append({Qt::Key_Percent,"%"});
    m_page1.append({Qt::Key_Ampersand,"&&"});
    m_page1.append({Qt::Key_Asterisk,"*"});
    m_page1.append({Qt::Key_Minus,"-"});
    m_page1.append({Qt::Key_Plus,"+"});
    m_page1.append({Qt::Key_ParenLeft,"("});
    m_page1.append({Qt::Key_ParenRight,")"});

    m_page1.append({Qt::Key_Exclam,"!"});
    m_page1.append({Qt::Key_QuoteDbl,"\""});
    m_page1.append({Qt::Key_Less,"<"});
    m_page1.append({Qt::Key_Greater,">"});
    m_page1.append({Qt::Key_Apostrophe,"'"});
    m_page1.append({Qt::Key_Colon,":"});
    m_page1.append({Qt::Key_Semicolon,";"});
    m_page1.append({Qt::Key_Slash,"/"});
    m_page1.append({Qt::Key_Question,"?"});
    m_page1.append({Qt::Key_Period,"."});
    m_page1.append({0xE000, ":-)"});

    ////////////////////////////////////////////////////
    m_page1.append({Qt::Key_AsciiTilde,"~"});
    m_page1.append({Qt::Key_Agrave,"`"});
    m_page1.append({Qt::Key_Bar,"|"});
    m_page1.append({0x7B,"·"});
    m_page1.append({0x221A,"√"});
    m_page1.append({Qt::Key_division,"÷"});
    m_page1.append({Qt::Key_multiply,"×"});
    m_page1.append({Qt::Key_onehalf,"½"});
    m_page1.append({Qt::Key_BraceLeft,"{"});
    m_page1.append({Qt::Key_BraceRight,"}"});


    m_page1.append({Qt::Key_Dollar,"$"});
    m_page1.append({0x20AC,"€"});
    m_page1.append({0xC2,"£"});
    m_page1.append({0xA2,"¢"});
    m_page1.append({0xA5,"¥"});
    m_page1.append({Qt::Key_Equal,"="});
    m_page1.append({Qt::Key_section,"§"});
    m_page1.append({Qt::Key_BracketLeft,"["});
    m_page1.append({Qt::Key_BracketRight,"]"});

    m_page1.append({Qt::Key_Underscore,"_"});
    m_page1.append({0x2122,"™"});
    m_page1.append({0x00AE,"®"});
    m_page1.append({Qt::Key_guillemotleft,"«"});
    m_page1.append({Qt::Key_guillemotright,"»"});
    m_page1.append({0x201C,"“"});
    m_page1.append({0x201D,"”"});
    m_page1.append({Qt::Key_Backslash,"\\"});
    m_page1.append({Qt::Key_AsciiCircum,"^"});
    m_page1.append({0x2026,"\u2026"});
    m_page1.append({0xE000, ":-)"});

    m_symbolButtons.append(ui->btn1);
    m_symbolButtons.append(ui->btn2);
    m_symbolButtons.append(ui->btn3);
    m_symbolButtons.append(ui->btn4);
    m_symbolButtons.append(ui->btn5);
    m_symbolButtons.append(ui->btn6);
    m_symbolButtons.append(ui->btn7);
    m_symbolButtons.append(ui->btn8);
    m_symbolButtons.append(ui->btn9);
    m_symbolButtons.append(ui->btn10);
    m_symbolButtons.append(ui->btn11);
    m_symbolButtons.append(ui->btn12);
    m_symbolButtons.append(ui->btn13);
    m_symbolButtons.append(ui->btn14);
    m_symbolButtons.append(ui->btn15);
    m_symbolButtons.append(ui->btn16);
    m_symbolButtons.append(ui->btn17);
    m_symbolButtons.append(ui->btn18);
    m_symbolButtons.append(ui->btn19);
    m_symbolButtons.append(ui->btn20);
    m_symbolButtons.append(ui->btn21);
    m_symbolButtons.append(ui->btn22);
    m_symbolButtons.append(ui->btn23);
    m_symbolButtons.append(ui->btn24);
    m_symbolButtons.append(ui->btn25);
    m_symbolButtons.append(ui->btn26);
    m_symbolButtons.append(ui->btn27);
    m_symbolButtons.append(ui->btn28);
    m_symbolButtons.append(ui->btn29);
    m_symbolButtons.append(ui->btn30);

    ui->buttonGroup->addButton(ui->backspace);
    ui->buttonGroup->addButton(ui->enter);
    ui->buttonGroup->addButton(ui->space);


    m_keyMap[ui->space] = Qt::Key_Space;
    m_keyMap[ui->enter] = Qt::Key_Enter;
    m_keyMap[ui->backspace] = Qt::Key_Backspace;

    this->buttonRemap();

    connect(ui->language,&QPushButton::clicked,this,&QExtSymbolKeyboard::changeLanguage);
    connect(ui->symbol,&QPushButton::clicked,this,&QExtSymbolKeyboard::changeSymbol);
    connect(ui->buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this,&QExtSymbolKeyboard::onSymbolButtonClicked);

    connect(ui->pagel,&QPushButton::clicked,this,&QExtSymbolKeyboard::onChangePage);
    connect(ui->pager,&QPushButton::clicked,this,&QExtSymbolKeyboard::onChangePage);
    connect(ui->hide,&QPushButton::clicked,this,&QExtSymbolKeyboard::hideKeyboard);
}

QExtSymbolKeyboard::~QExtSymbolKeyboard()
{
    delete ui;
}

void QExtSymbolKeyboard::setCurLanguage(const QString &lang)
{
    ui->space->setText(lang);
}

void QExtSymbolKeyboard::onChangePage()
{
    ++m_curPage;
    m_curPage %= m_maxPage;

    this->buttonRemap();
}

void QExtSymbolKeyboard::onSymbolButtonClicked(QAbstractButton * button)
{
    emit this->keyPressed(Qt::Key(m_keyMap[button]),buttonText(button),Qt::NoModifier);
}

void QExtSymbolKeyboard::buttonRemap()
{
    int start = m_curPage * m_symbolButtons.size();
    for(int i = start; i < (m_curPage + 1) * m_symbolButtons.size() && i < m_page1.size(); ++i)
    {
        m_symbolButtons[i - start]->setText(m_page1[i].second);
        m_keyMap[m_symbolButtons[i - start]] = m_page1[i].first;
    }

    ui->pagel->setText(QString("%1/%2").arg(m_curPage + 1).arg(m_maxPage));
    ui->pager->setText(QString("%1/%2").arg(m_curPage + 1).arg(m_maxPage));
}

QString QExtSymbolKeyboard::buttonText(QAbstractButton * button)
{
    if(m_keyMap[button] == Qt::Key_Space)
    {
        return QLatin1String(" ");
    }
    else if(m_keyMap[button] == Qt::Key_Ampersand)
    {
        return QLatin1String("&");
    }
    else
    {
        return button->text();
    }
}
