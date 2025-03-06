#include <qextNormalKeyboard.h>
#include <ui_qextNormalKeyboard.h>

#include <QtDebug>

QExtNormalKeyboard::QExtNormalKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtNormalKeyboard)
    , m_modifier(Qt::ShiftModifier)
{
    ui->setupUi(this);
    m_letterkeys[ui->A] = Qt::Key_A;
    m_letterkeys[ui->B] = Qt::Key_B;
    m_letterkeys[ui->C] = Qt::Key_C;
    m_letterkeys[ui->D] = Qt::Key_D;
    m_letterkeys[ui->E] = Qt::Key_E;
    m_letterkeys[ui->F] = Qt::Key_F;
    m_letterkeys[ui->G] = Qt::Key_G;
    m_letterkeys[ui->H] = Qt::Key_H;
    m_letterkeys[ui->I] = Qt::Key_I;
    m_letterkeys[ui->J] = Qt::Key_J;
    m_letterkeys[ui->K] = Qt::Key_K;
    m_letterkeys[ui->L] = Qt::Key_L;
    m_letterkeys[ui->M] = Qt::Key_M;
    m_letterkeys[ui->N] = Qt::Key_N;
    m_letterkeys[ui->O] = Qt::Key_O;
    m_letterkeys[ui->P] = Qt::Key_P;
    m_letterkeys[ui->Q] = Qt::Key_Q;
    m_letterkeys[ui->R] = Qt::Key_R;
    m_letterkeys[ui->S] = Qt::Key_S;
    m_letterkeys[ui->T] = Qt::Key_T;
    m_letterkeys[ui->U] = Qt::Key_U;
    m_letterkeys[ui->V] = Qt::Key_V;
    m_letterkeys[ui->W] = Qt::Key_W;
    m_letterkeys[ui->X] = Qt::Key_X;
    m_letterkeys[ui->Y] = Qt::Key_Y;
    m_letterkeys[ui->Z] = Qt::Key_Z;

    m_letterkeys[ui->enter] = Qt::Key_Enter;
    m_letterkeys[ui->shiftl] = Qt::Key_Shift;
    m_letterkeys[ui->shiftr] = Qt::Key_Shift;
    m_letterkeys[ui->space] = Qt::Key_Space;
    m_letterkeys[ui->backspace] = Qt::Key_Backspace;
    m_letterkeys[ui->period] = Qt::Key_Period;
    m_letterkeys[ui->apostrophe] = Qt::Key_Apostrophe;
    m_letterkeys[ui->minus] = Qt::Key_Minus;
    m_letterkeys[ui->at] = Qt::Key_At;

    ui->groupLetter->addButton(ui->backspace);
    ui->groupLetter->addButton(ui->enter);
    ui->groupLetter->addButton(ui->shiftl);
    ui->groupLetter->addButton(ui->shiftr);
    ui->groupLetter->addButton(ui->space);
    ui->groupLetter->addButton(ui->period);
    ui->groupLetter->addButton(ui->apostrophe);
    ui->groupLetter->addButton(ui->minus);
    ui->groupLetter->addButton(ui->at);

    connect(ui->hide, &QPushButton::clicked, this, &QExtNormalKeyboard::hideKeyboard);
    connect(ui->symbol, &QPushButton::clicked, this, &QExtNormalKeyboard::changeSymbol);
    connect(ui->language, &QPushButton::clicked, this, &QExtNormalKeyboard::changeLanguage);
    connect(ui->groupLetter, QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),
            this, &QExtNormalKeyboard::letterClicked);

    ui->shiftr->setIcon(QPixmap(":/QExtKeyboard/images/shift_checked.png"));
    ui->shiftl->setIcon(QPixmap(":/QExtKeyboard/images/shift_checked.png"));
}

QExtNormalKeyboard::~QExtNormalKeyboard()
{
    delete ui;
}

void QExtNormalKeyboard::setCurLanguage(const QString &lang)
{
    ui->space->setText(lang);
}

void QExtNormalKeyboard::letterClicked(QAbstractButton* button)
{
    if(m_letterkeys.contains(button))
    {
        if(m_letterkeys[button] == Qt::Key_Shift)
        {
            if(m_modifier == Qt::NoModifier)
            {
                m_modifier = Qt::ShiftModifier;
            }
            else if(m_modifier == Qt::ShiftModifier)
            {
                m_modifier = Qt::NoModifier;
            }

            if(m_modifier == Qt::ShiftModifier)
            {
                ui->shiftr->setIcon(QPixmap(":/QExtKeyboard/images/shift_checked.png"));
                ui->shiftl->setIcon(QPixmap(":/QExtKeyboard/images/shift_checked.png"));
                this->capsLock();
            }
            else
            {
                ui->shiftr->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
                ui->shiftl->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
                this->capsLock();
            }

            return;
        }


        if(m_modifier == Qt::ShiftModifier)
        {
            emit this->keyPressed(m_letterkeys[button],buttonText(button).toUpper(),Qt::NoModifier);

            ui->shiftr->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
            ui->shiftl->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
            m_modifier = Qt::NoModifier;
            this->capsLock();
        }
        else
        {
            emit this->keyPressed(m_letterkeys[button],buttonText(button).toLower(),Qt::NoModifier);
        }
    }
}

QString QExtNormalKeyboard::buttonText(QAbstractButton * button)
{
    if(m_letterkeys[button] == Qt::Key_Space)
    {
        return QLatin1String(" ");
    }
    else
    {
        return button->text();
    }

}

void QExtNormalKeyboard::capsLock()
{
    if(m_modifier == Qt::ShiftModifier)
    {
        ui->A->setText("A");
        ui->B->setText("B");
        ui->C->setText("C");
        ui->D->setText("D");
        ui->E->setText("E");
        ui->F->setText("F");
        ui->G->setText("G");
        ui->H->setText("H");
        ui->I->setText("I");
        ui->J->setText("J");
        ui->K->setText("K");
        ui->L->setText("L");
        ui->M->setText("M");
        ui->N->setText("N");
        ui->O->setText("O");
        ui->P->setText("P");
        ui->Q->setText("Q");
        ui->R->setText("R");
        ui->S->setText("S");
        ui->T->setText("T");
        ui->U->setText("U");
        ui->V->setText("V");
        ui->W->setText("W");
        ui->X->setText("X");
        ui->Y->setText("Y");
        ui->Z->setText("Z");
    }
    else
    {
        ui->A->setText("a");
        ui->B->setText("b");
        ui->C->setText("c");
        ui->D->setText("d");
        ui->E->setText("e");
        ui->F->setText("f");
        ui->G->setText("g");
        ui->H->setText("h");
        ui->I->setText("i");
        ui->J->setText("j");
        ui->K->setText("k");
        ui->L->setText("l");
        ui->M->setText("m");
        ui->N->setText("n");
        ui->O->setText("o");
        ui->P->setText("p");
        ui->Q->setText("q");
        ui->R->setText("r");
        ui->S->setText("s");
        ui->T->setText("t");
        ui->U->setText("u");
        ui->V->setText("v");
        ui->W->setText("w");
        ui->X->setText("x");
        ui->Y->setText("y");
        ui->Z->setText("z");
    }
}
