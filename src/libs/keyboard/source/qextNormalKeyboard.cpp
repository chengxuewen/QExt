#include <qextNormalKeyboard.h>
#include <ui_qextNormalKeyboard.h>

#include <QtDebug>

QExtNormalKeyboard::QExtNormalKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtNormalKeyboard)
    , mModifier(Qt::ShiftModifier)
{
    ui->setupUi(this);
    mLetterkeys[ui->A] = Qt::Key_A;
    mLetterkeys[ui->B] = Qt::Key_B;
    mLetterkeys[ui->C] = Qt::Key_C;
    mLetterkeys[ui->D] = Qt::Key_D;
    mLetterkeys[ui->E] = Qt::Key_E;
    mLetterkeys[ui->F] = Qt::Key_F;
    mLetterkeys[ui->G] = Qt::Key_G;
    mLetterkeys[ui->H] = Qt::Key_H;
    mLetterkeys[ui->I] = Qt::Key_I;
    mLetterkeys[ui->J] = Qt::Key_J;
    mLetterkeys[ui->K] = Qt::Key_K;
    mLetterkeys[ui->L] = Qt::Key_L;
    mLetterkeys[ui->M] = Qt::Key_M;
    mLetterkeys[ui->N] = Qt::Key_N;
    mLetterkeys[ui->O] = Qt::Key_O;
    mLetterkeys[ui->P] = Qt::Key_P;
    mLetterkeys[ui->Q] = Qt::Key_Q;
    mLetterkeys[ui->R] = Qt::Key_R;
    mLetterkeys[ui->S] = Qt::Key_S;
    mLetterkeys[ui->T] = Qt::Key_T;
    mLetterkeys[ui->U] = Qt::Key_U;
    mLetterkeys[ui->V] = Qt::Key_V;
    mLetterkeys[ui->W] = Qt::Key_W;
    mLetterkeys[ui->X] = Qt::Key_X;
    mLetterkeys[ui->Y] = Qt::Key_Y;
    mLetterkeys[ui->Z] = Qt::Key_Z;

    mLetterkeys[ui->enter] = Qt::Key_Enter;
    mLetterkeys[ui->shiftl] = Qt::Key_Shift;
    mLetterkeys[ui->shiftr] = Qt::Key_Shift;
    mLetterkeys[ui->space] = Qt::Key_Space;
    mLetterkeys[ui->backspace] = Qt::Key_Backspace;
    mLetterkeys[ui->period] = Qt::Key_Period;
    mLetterkeys[ui->apostrophe] = Qt::Key_Apostrophe;
    mLetterkeys[ui->minus] = Qt::Key_Minus;
    mLetterkeys[ui->at] = Qt::Key_At;

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
    if(mLetterkeys.contains(button))
    {
        if(mLetterkeys[button] == Qt::Key_Shift)
        {
            if(mModifier == Qt::NoModifier)
            {
                mModifier = Qt::ShiftModifier;
            }
            else if(mModifier == Qt::ShiftModifier)
            {
                mModifier = Qt::NoModifier;
            }

            if(mModifier == Qt::ShiftModifier)
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


        if(mModifier == Qt::ShiftModifier)
        {
            emit this->keyPressed(mLetterkeys[button],buttonText(button).toUpper(),Qt::NoModifier);

            ui->shiftr->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
            ui->shiftl->setIcon(QPixmap(":/QExtKeyboard/images/shift.png"));
            mModifier = Qt::NoModifier;
            this->capsLock();
        }
        else
        {
            emit this->keyPressed(mLetterkeys[button],buttonText(button).toLower(),Qt::NoModifier);
        }
    }
}

QString QExtNormalKeyboard::buttonText(QAbstractButton * button)
{
    if(mLetterkeys[button] == Qt::Key_Space)
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
    if(mModifier == Qt::ShiftModifier)
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
