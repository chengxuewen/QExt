#pragma execution_character_set("utf-8")

#include <qextSymbolKeyboard.h>
#include <ui_qextSymbolKeyboard.h>

QExtSymbolKeyboard::QExtSymbolKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtSymbolKeyboard)
{
    ui->setupUi(this);

    mCurPage = 0;
    mMaxPage = 2;

    mPage1.append({Qt::Key_1,"1"});
    mPage1.append({Qt::Key_2,"2"});
    mPage1.append({Qt::Key_3,"3"});
    mPage1.append({Qt::Key_4,"4"});
    mPage1.append({Qt::Key_5,"5"});
    mPage1.append({Qt::Key_6,"6"});
    mPage1.append({Qt::Key_7,"7"});
    mPage1.append({Qt::Key_8,"8"});
    mPage1.append({Qt::Key_9,"9"});
    mPage1.append({Qt::Key_0,"0"});

    mPage1.append({Qt::Key_At,"@"});
    mPage1.append({Qt::Key_NumberSign,"#"});
    mPage1.append({Qt::Key_Percent,"%"});
    mPage1.append({Qt::Key_Ampersand,"&&"});
    mPage1.append({Qt::Key_Asterisk,"*"});
    mPage1.append({Qt::Key_Minus,"-"});
    mPage1.append({Qt::Key_Plus,"+"});
    mPage1.append({Qt::Key_ParenLeft,"("});
    mPage1.append({Qt::Key_ParenRight,")"});

    mPage1.append({Qt::Key_Exclam,"!"});
    mPage1.append({Qt::Key_QuoteDbl,"\""});
    mPage1.append({Qt::Key_Less,"<"});
    mPage1.append({Qt::Key_Greater,">"});
    mPage1.append({Qt::Key_Apostrophe,"'"});
    mPage1.append({Qt::Key_Colon,":"});
    mPage1.append({Qt::Key_Semicolon,";"});
    mPage1.append({Qt::Key_Slash,"/"});
    mPage1.append({Qt::Key_Question,"?"});
    mPage1.append({Qt::Key_Period,"."});
    mPage1.append({0xE000, ":-)"});

    ////////////////////////////////////////////////////
    mPage1.append({Qt::Key_AsciiTilde,"~"});
    mPage1.append({Qt::Key_Agrave,"`"});
    mPage1.append({Qt::Key_Bar,"|"});
    mPage1.append({0x7B,"·"});
    mPage1.append({0x221A, "√"});
    mPage1.append({Qt::Key_division,"÷"});
    mPage1.append({Qt::Key_multiply,"×"});
    mPage1.append({Qt::Key_onehalf,"½"});
    mPage1.append({Qt::Key_BraceLeft,"{"});
    mPage1.append({Qt::Key_BraceRight,"}"});


    mPage1.append({Qt::Key_Dollar,"$"});
    mPage1.append({0x20AC, "€"});
    mPage1.append({0xC2,"£"});
    mPage1.append({0xA2,"¢"});
    mPage1.append({0xA5,"¥"});
    mPage1.append({Qt::Key_Equal,"="});
    mPage1.append({Qt::Key_section,"§"});
    mPage1.append({Qt::Key_BracketLeft,"["});
    mPage1.append({Qt::Key_BracketRight,"]"});

    mPage1.append({Qt::Key_Underscore,"_"});
    mPage1.append({0x2122,"™"});
    mPage1.append({0x00AE,"®"});
    mPage1.append({Qt::Key_guillemotleft,"«"});
    mPage1.append({Qt::Key_guillemotright,"»"});
    mPage1.append({0x201C,"“"});
    mPage1.append({0x201D,"”"});
    mPage1.append({Qt::Key_Backslash,"\\"});
    mPage1.append({Qt::Key_AsciiCircum,"^"});
    mPage1.append({0x2026,"\u2026"});
    mPage1.append({0xE000, ":-)"});

    mSymbolButtons.append(ui->btn1);
    mSymbolButtons.append(ui->btn2);
    mSymbolButtons.append(ui->btn3);
    mSymbolButtons.append(ui->btn4);
    mSymbolButtons.append(ui->btn5);
    mSymbolButtons.append(ui->btn6);
    mSymbolButtons.append(ui->btn7);
    mSymbolButtons.append(ui->btn8);
    mSymbolButtons.append(ui->btn9);
    mSymbolButtons.append(ui->btn10);
    mSymbolButtons.append(ui->btn11);
    mSymbolButtons.append(ui->btn12);
    mSymbolButtons.append(ui->btn13);
    mSymbolButtons.append(ui->btn14);
    mSymbolButtons.append(ui->btn15);
    mSymbolButtons.append(ui->btn16);
    mSymbolButtons.append(ui->btn17);
    mSymbolButtons.append(ui->btn18);
    mSymbolButtons.append(ui->btn19);
    mSymbolButtons.append(ui->btn20);
    mSymbolButtons.append(ui->btn21);
    mSymbolButtons.append(ui->btn22);
    mSymbolButtons.append(ui->btn23);
    mSymbolButtons.append(ui->btn24);
    mSymbolButtons.append(ui->btn25);
    mSymbolButtons.append(ui->btn26);
    mSymbolButtons.append(ui->btn27);
    mSymbolButtons.append(ui->btn28);
    mSymbolButtons.append(ui->btn29);
    mSymbolButtons.append(ui->btn30);

    ui->buttonGroup->addButton(ui->backspace);
    ui->buttonGroup->addButton(ui->enter);
    ui->buttonGroup->addButton(ui->space);


    mKeyMap[ui->space] = Qt::Key_Space;
    mKeyMap[ui->enter] = Qt::Key_Enter;
    mKeyMap[ui->backspace] = Qt::Key_Backspace;

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
    ++mCurPage;
    mCurPage %= mMaxPage;

    this->buttonRemap();
}

void QExtSymbolKeyboard::onSymbolButtonClicked(QAbstractButton * button)
{
    emit this->keyPressed(Qt::Key(mKeyMap[button]),buttonText(button),Qt::NoModifier);
}

void QExtSymbolKeyboard::buttonRemap()
{
    int start = mCurPage * mSymbolButtons.size();
    for(int i = start; i < (mCurPage + 1) * mSymbolButtons.size() && i < mPage1.size(); ++i)
    {
        mSymbolButtons[i - start]->setText(mPage1[i].second);
        mKeyMap[mSymbolButtons[i - start]] = mPage1[i].first;
    }

    ui->pagel->setText(QString("%1/%2").arg(mCurPage + 1).arg(mMaxPage));
    ui->pager->setText(QString("%1/%2").arg(mCurPage + 1).arg(mMaxPage));
}

QString QExtSymbolKeyboard::buttonText(QAbstractButton * button)
{
    if(mKeyMap[button] == Qt::Key_Space)
    {
        return QLatin1String(" ");
    }
    else if(mKeyMap[button] == Qt::Key_Ampersand)
    {
        return QLatin1String("&");
    }
    else
    {
        return button->text();
    }
}
