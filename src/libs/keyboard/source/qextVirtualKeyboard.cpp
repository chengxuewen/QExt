/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/
#pragma execution_character_set("utf-8")
#include <qextVirtualKeyboard.h>
#include <ui_qextVirtualKeyboard.h>
#include "qextPinyin.h"

#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QMatrix>
#include <QScrollBar>
#include <QKeyEvent>
#include <QMutex>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QPointer>
#include <QMutexLocker>
#include <QFile>

class QExtVirtualKeyboardPrivate
{
public:
    QExtVirtualKeyboardPrivate();
    ~QExtVirtualKeyboardPrivate();

    void initForm();        //Move to the right place
    void init();            //Initializes the database and more

    void buttonClicked();      //Input method panel button processing
    void focusChanged(QWidget *oldWidget, QWidget *nowWidget);  //Focus change event slot function handling

    void movePosition();    //Move to the right place
    void selectChinese();   //Query the Chinese characters
    void showChinese();     //Displays the Chinese characters that are queried
    void clearChinese();    //Empty the current Chinese character message

    void readChinese();     //Read the priority library file
    void saveChinese(const QString &value);     //Save the currently selected character to a file

    void insertValue(const QString &value);     //Inserts a value into the current focus control
    void clearValue();      //Clear the value and return to the original state
    void deleteValue();     //Deletes a character from the current focus control

    void showPanel();       //Display the input method panel
    void hidePanel();       //Hide the input method panel

private:
    QExtVirtualKeyboard *q_ptr;
    Q_DECLARE_PUBLIC(QExtVirtualKeyboard)

    bool mIsUpper;
    bool mIsNumber;
    bool mOnlyControl;
    int mColumnCount;
    int mMaxCount;

    QString mDataBasePath;
    QString mIconType;
    QExtVirtualKeyboard::PopUpTypes mPopUpType;
    QExtVirtualKeyboard::InputTypes mInputType;
    QExtVirtualKeyboard::StyleTypes mStyleType;

    QWidget *mCurrentWidget;
    QList<QLabel *> mChineseLabels;
    QList<QLabel *> mMoreChineseLabels;

    QStringList mAllPinYins;
    QExtPinyin mGooglePinYin;

    QString mMainTextColor;
    QString mButtonHoveColor;
    QString mLastText;

    QPropertyAnimation *mChineseAnimation;
    QPropertyAnimation *mMoreAnimation;

    QStringList mSelectKeys;
    QStringList mSelectValues;
    QStringList mUserKeys;
    QStringList mUserValues;
};

QExtVirtualKeyboardPrivate::QExtVirtualKeyboardPrivate()
{
    mPopUpType = QExtVirtualKeyboard::PopUp_BottomCenter;
    mStyleType = QExtVirtualKeyboard::Style_Black;
}

QExtVirtualKeyboardPrivate::~QExtVirtualKeyboardPrivate()
{
}

void QExtVirtualKeyboardPrivate::initForm()
{
#if (QT_VERSION > QT_VERSION_CHECK(5, 0, 0))
    q_ptr->setWindowFlags(Qt::Tool | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint |
                          Qt::X11BypassWindowManagerHint);
#else
    q_ptr->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#endif
    mCurrentWidget = 0;
    mIsUpper = false;
    mIsNumber = false;
    mOnlyControl = false;
    mColumnCount = 8;
    mMaxCount = 256;
    mDataBasePath = qApp->applicationDirPath();

    //Bind buttons to events
    QList<QPushButton *> listButton;
    listButton << q_ptr->ui->widgetLetter->findChildren<QPushButton *>();
    listButton << q_ptr->ui->widgetNumber->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton)
    {
        pButton->setProperty("btnInput", true);
        QObject::connect(pButton, SIGNAL(clicked()), q_ptr, SLOT(buttonClicked()));
    }

    //Set letter properties
    listButton.clear();
    listButton << q_ptr->ui->widgetLetter1->findChildren<QPushButton *>();
    listButton << q_ptr->ui->widgetLetter2->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton)
    {
        pButton->setProperty("btnLetter", true);
    }

    //Set all button input methods not available + long press to automatically repeat the event
    listButton.clear();
    listButton << q_ptr->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton)
    {
        pButton->setFocusPolicy(Qt::NoFocus);
        pButton->setProperty("noinput", true);
        pButton->setAutoRepeat(true);
        pButton->setAutoRepeatDelay(500);
    }

    //By default, a maximum of 256 are generated and added to the top scroll area
    for (int i = 0; i < mMaxCount; i++)
    {
        QLabel *lab = new QLabel;
        lab->setProperty("labCn", true);
        lab->setEnabled(false);
        q_ptr->ui->layout->addWidget(lab);
        mChineseLabels << lab;
    }

    //The default is to generate a maximum of 256, which is added to more scrolling areas
    int iRow = 0;
    int iColumn = 0;
    for (int i = 0; i < mMaxCount; i++)
    {
        QLabel *pLabel = new QLabel();
        pLabel->setProperty("labMore", true);
        pLabel->setEnabled(false);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        q_ptr->ui->gridLayout->addWidget(pLabel, iRow, iColumn);
        mMoreChineseLabels << pLabel;

        iColumn++;
        if (iColumn >= mColumnCount)
        {
            iRow++;
            iColumn = 0;
        }
    }

    q_ptr->ui->lab1->setEnabled(false);
    q_ptr->ui->lab2->setEnabled(false);
    q_ptr->ui->labPY->setEnabled(false);
    q_ptr->ui->labMore->setEnabled(false);

    //The font name and the font size of the button in the input method panel are the font size of the Chinese character area
    q_ptr->setFontInfo(q_ptr->font().family(), 11, 10);
    //Icon fixed size
    q_ptr->setIconSize(20, 20);
    //The space between the buttons
    q_ptr->setSpacing(6);
    //The height of the top Chinese character area
    q_ptr->setTopHeight(40);
    //Input method Mode English mode Chinese mode number Special character mode
    q_ptr->setInputType(QExtVirtualKeyboard::Input_English);
    //Input method panel style black- black blue- light blue brown- gray- black gray- gray Silvery - silver
    q_ptr->setStyleType(QExtVirtualKeyboard::Style_Black);

    //Define an animation to produce a smooth value
    mChineseAnimation = new QPropertyAnimation(q_ptr->ui->scrollAreaCn->horizontalScrollBar(), "value");
    mChineseAnimation->setEasingCurve(QEasingCurve::OutCirc);
    mChineseAnimation->setDuration(500);

    mMoreAnimation = new QPropertyAnimation(q_ptr->ui->scrollAreaMore->verticalScrollBar(), "value");
    mMoreAnimation->setEasingCurve(QEasingCurve::OutCirc);
    mMoreAnimation->setDuration(500);
}

void QExtVirtualKeyboardPrivate::init()
{
    if (mOnlyControl)
    {
        q_ptr->ui->labPY->setVisible(false);
        q_ptr->installEventFilter(q_ptr);
        q_ptr->ui->labType->installEventFilter(q_ptr);
        q_ptr->ui->labType2->installEventFilter(q_ptr);
        q_ptr->ui->labMore->installEventFilter(q_ptr);
        q_ptr->ui->widgetCn->installEventFilter(q_ptr);
        q_ptr->ui->widgetMore->installEventFilter(q_ptr);

        foreach (QLabel *pLabel, mChineseLabels)
        {
            pLabel->installEventFilter(q_ptr);
        }

        foreach (QLabel *pLabel, mMoreChineseLabels)
        {
            pLabel->installEventFilter(q_ptr);
        }
    }
    else
    {
        //Bind globally to change the focus signal slot
        QObject::connect(qApp, SIGNAL(focusChanged(QWidget * , QWidget * )), q_ptr,
                         SLOT(focusChanged(QWidget * , QWidget * )));
        qApp->installEventFilter(q_ptr);
    }

    mGooglePinYin.open(mDataBasePath);
    this->readChinese();
}

void QExtVirtualKeyboardPrivate::buttonClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(q_ptr->sender());
    QString strObjectName = pButton->objectName();
    QString strButtonText = pButton->text();
    QString strLabelText = q_ptr->ui->labPY->text();
    q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    if ("btnUpper" == strObjectName)
    {
        mIsUpper = !mIsUpper;
        q_ptr->setUpper(mIsUpper);
        clearChinese();
        q_ptr->ui->labPY->clear();
    }
    else if ("btnNumber" == strObjectName)
    {
        q_ptr->setInputType(QExtVirtualKeyboard::Input_Number);
    }
    else if ("btnNumber2" == strObjectName)
    {
        mIsNumber = !mIsNumber;
        q_ptr->setNumber(mIsNumber);
    }
    else if ("btnDelete" == strObjectName || "btnDelete2" == strObjectName)
    {
        //If the current mode is Chinese, delete the corresponding pinyin, and then delete the content of the corresponding text input box after deleting the pinyin
        int iLength = strLabelText.length();
        if (QExtVirtualKeyboard::Input_Chinese == mInputType && iLength > 0)
        {
            q_ptr->ui->labPY->setText(strLabelText.left(iLength - 1));
            this->selectChinese();
        }
        else
        {
            this->deleteValue();
        }

        q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
        q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);
    }
    else if ("btnSpace" == strObjectName || "btnSpace2" == strObjectName)
    {
        //If The Chinese mode is to be entered and the character is to be entered, the first Chinese character is inserted if there is any Chinese character
        if (QExtVirtualKeyboard::Input_Chinese == mInputType && !strLabelText.isEmpty())
        {
            QString strText = mChineseLabels.first()->text();
            if (strText.isEmpty())
            {
                this->insertValue(strLabelText);
            }
            else
            {
                this->insertValue(strText);
            }
            this->clearChinese();
        }
        else
        {
            this->insertValue(" ");
        }
    }
    else if ("btnEnter" == strObjectName || "btnEnter2" == strObjectName)
    {
        //If Chinese mode and the letter is to be entered, insert the letter immediately
        if (QExtVirtualKeyboard::Input_Chinese == mInputType && !strLabelText.isEmpty())
        {
            this->insertValue(strLabelText);
            this->clearChinese();
        }

        if (QEXT_NULLPTR != mCurrentWidget && !mOnlyControl)
        {
            this->hidePanel();
            QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier, QString("\n"));
            QApplication::sendEvent(mCurrentWidget, &keyPress);
        }
        else
        {
            this->insertValue("\n");
        }
    }
    else
    {
        //If it is an & button, the real text is to remove the preceding & character because the corresponding & is filtered
        if ("&&" == strButtonText)
        {
            strButtonText = "&";
        }

        //If the current mode is not Chinese, click the button corresponding to text as the passing parameter, uppercase first
        if (QExtVirtualKeyboard::Input_Chinese != mInputType || mIsUpper)
        {
            this->insertValue(strButtonText);
        }
        else
        {
            if (pButton->property("btnLetter").toBool())
            {
                q_ptr->ui->labPY->setText(strLabelText + strButtonText);
                this->selectChinese();
            }
        }
    }
}

void QExtVirtualKeyboardPrivate::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //    qCDebug(QExtKeyboard) << "oldWidget:" << oldWidget << "nowWidget:" << nowWidget;
    Q_UNUSED(oldWidget);
    mCurrentWidget = nowWidget;
    if (nowWidget != 0 && !q_ptr->isAncestorOf(nowWidget))
    {
        //If the corresponding property NoInput is true or read-only, it is not displayed
        if (nowWidget->property("noinput").toBool() || nowWidget->property("readOnly").toBool())
        {
            mCurrentWidget = 0;
            QTimer::singleShot(0, q_ptr, SLOT(hidePanel()));
            return;
        }

        if (nowWidget->inherits("QWidget"))
        {
            //Legal input control, can be added by itself
            QStringList listClassNames;
            listClassNames << "QLineEdit" << "QTextEdit" << "QPlainTextEdit" << "QAbstractSpinBox" << "QComboBox";
            listClassNames << "QQuickWidget" << "QWebView" << "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget";

            //Finds out if the current focus control is a legally entered control
            bool bExist = false;
            foreach (QString strClassName, listClassNames)
            {
                if (nowWidget->inherits(strClassName.toLatin1().constData()))
                {
                    //Determines whether the drop-down box's editable property is true if it is currently a drop-down box
                    if (strClassName != "QComboBox" || nowWidget->property("editable").toBool())
                    {
                        bExist = true;
                        break;
                    }
                }
            }

            if (bExist)
            {
                this->showPanel();
                this->movePosition();
            }
            else
            {
                mCurrentWidget = 0;
                this->hidePanel();
            }
        }
    }
}

void QExtVirtualKeyboardPrivate::movePosition()
{
    //According to the user's choice of input method location Settings - center display - bottom fill - displayed directly below the input box
    static int iDeskWidth = qApp->desktop()->availableGeometry().width();
    static int iDeskHeight = qApp->desktop()->availableGeometry().height();
    int iWidth = q_ptr->width();
    int iHeight = q_ptr->height();

    if (QExtVirtualKeyboard::PopUp_Center == mPopUpType)
    {
        QPoint pos = QPoint(iDeskWidth / 2 - iWidth / 2, iDeskHeight / 2 - iHeight / 2);
        q_ptr->setGeometry(pos.x(), pos.y(), iWidth, iHeight);
    }
    else if (QExtVirtualKeyboard::PopUp_BottomCenter == mPopUpType)
    {
        QRect rect = mCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = mCurrentWidget->mapToGlobal(pos);
        int iX = (iDeskWidth - iWidth) / 2;
        int iY = iDeskHeight - iHeight;
        if (pos.y() + iHeight > iDeskHeight)
        {
            iY = pos.y() - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    }
    else if (QExtVirtualKeyboard::PopUp_FocusHCenter == mPopUpType)
    {
        QRect rect = mCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = mCurrentWidget->mapToGlobal(pos);
        int iX = (iDeskWidth - iWidth) / 2;
        int iY = pos.y();
        if (iY + iHeight > iDeskHeight)
        {
            iY = iY - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    }
    else if (QExtVirtualKeyboard::PopUp_Control == mPopUpType)
    {
        QRect rect = mCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = mCurrentWidget->mapToGlobal(pos);
        int iX = pos.x();
        if (iX + iWidth > iDeskWidth)
        {
            iX = iDeskWidth - iWidth;
        }
        int iY = pos.y();
        if (iY + iHeight > iDeskHeight)
        {
            iY = iY - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    }
}

void QExtVirtualKeyboardPrivate::selectChinese()
{
    //Empty the Chinese characters
    this->clearChinese();

    //For the current pinyin query Chinese characters, if the maximum number of Chinese characters to take the first
    QString strLabelText = q_ptr->ui->labPY->text();
    if (strLabelText.length() > 15)
    {
        qCDebug(QExtKeyboard) << "input too long";
        return;
    }

    int iCount = mGooglePinYin.select(strLabelText);
    iCount = iCount > mMaxCount ? mMaxCount : iCount;

    //Insert the user to create the word Chinese characters, the highest priority, insert the first
    int iIndexUser = mUserKeys.indexOf(strLabelText);
    if (iIndexUser >= 0)
    {
        QString strChineses = mUserValues.at(iIndexUser);
        QStringList list = strChineses.split("|");
        for (int i = list.count() - 1; i >= 0; i--)
        {
            QString strChinese = list.at(i);
            if (!strChinese.isEmpty())
            {
                mAllPinYins.insert(0, strChinese);
            }
        }
    }

    //Insert the user-selected word, in the middle of the priority list, immediately after the user-generated word
    int iIndexSelect = mSelectKeys.indexOf(strLabelText);
    if (iIndexSelect >= 0)
    {
        QString strChineses = mSelectValues.at(iIndexSelect);
        QStringList list = strChineses.split("|");
        for (int i = 0; i < list.count(); i++)
        {
            QString strChinese = list.at(i);
            if (!strChinese.isEmpty() && !mAllPinYins.contains(strChinese))
            {
                mAllPinYins << strChinese;
            }
        }
    }

    //Insert queried Chinese characters that have been filtered in the Chinese character queue
    for (int i = 0; i < iCount; i++)
    {
        QString strText = mGooglePinYin.getChinese(i);
        if (!strText.isEmpty() && !mAllPinYins.contains(strText))
        {
            mAllPinYins << strText;
        }
    }

    //According to the Chinese character
    this->showChinese();
}

void QExtVirtualKeyboardPrivate::showChinese()
{
    for (int i = 0; i < mMaxCount; i++)
    {
        mChineseLabels.at(i)->clear();
        mMoreChineseLabels.at(i)->clear();
        mChineseLabels.at(i)->setEnabled(false);
        mMoreChineseLabels.at(i)->setEnabled(false);
    }

    for (int i = 0; i < mAllPinYins.count(); i++)
    {
        mChineseLabels.at(i)->setText(mAllPinYins.at(i));
        mMoreChineseLabels.at(i)->setText(mAllPinYins.at(i));
        mChineseLabels.at(i)->setEnabled(true);
        mMoreChineseLabels.at(i)->setEnabled(true);
    }
}

void QExtVirtualKeyboardPrivate::clearChinese()
{
    mAllPinYins.clear();
    for (int i = 0; i < mMaxCount; i++)
    {
        mChineseLabels.at(i)->clear();
        mMoreChineseLabels.at(i)->clear();
        mChineseLabels.at(i)->setEnabled(false);
        mMoreChineseLabels.at(i)->setEnabled(false);
    }
}

void QExtVirtualKeyboardPrivate::readChinese()
{
    //Load the local priority lexicon
    mSelectKeys.clear();
    mSelectValues.clear();
    QFile fileSelect(mDataBasePath + "/chinese_select.txt");
    if (fileSelect.open(QFile::ReadOnly | QFile::Text))
    {
        while (!fileSelect.atEnd())
        {
            QString line = fileSelect.readLine();
            line = line.replace("\n", "");
            QStringList list = line.split(" ");
            mSelectKeys << list.at(0);
            mSelectValues << list.at(1);
        }

        fileSelect.close();
    }

    //Loads the local custom thesaurus
    mUserKeys.clear();
    mUserValues.clear();
    QFile fileUser(mDataBasePath + "/chinese_user.txt");
    if (fileUser.open(QFile::ReadOnly | QFile::Text))
    {
        while (!fileUser.atEnd())
        {
            QString line = fileUser.readLine();
            line = line.replace("\n", "");
            QStringList list = line.split(" ");
            mUserKeys << list.at(0);
            mUserValues << list.at(1);
        }

        fileUser.close();
    }
}

void QExtVirtualKeyboardPrivate::saveChinese(const QString &value)
{
    //Not currently in Chinese input state need not be processed
    if (QExtVirtualKeyboard::Input_Chinese != mInputType || value.isEmpty() || mLastText.isEmpty())
    {
        return;
    }

    //Insert the currently selected Character into the file as the priority word library
    QString strPinyin = q_ptr->ui->labPY->text();
    int iIndex = mSelectKeys.indexOf(strPinyin);

    //If the current letter is already in the priority thesaurus file, update the character corresponding to that letter
    if (iIndex >= 0)
    {
        QStringList listTemp;
        QString strChineses = mSelectValues.at(iIndex);
        QStringList list = strChineses.split("|");

        //If it already exists, it does not need to be added at present. It can be directly inserted in the front after
        bool bExist = list.contains(value);
        foreach (QString str, list)
        {
            if (bExist && str == value)
            {
                continue;
            }
            if (!str.isEmpty())
            {
                listTemp << str;
            }
        }

        listTemp.insert(0, value);
        mSelectValues[iIndex] = listTemp.join("|");
    }
    else
    {
        mSelectKeys << strPinyin;
        mSelectValues << value;
    }

    QStringList list;
    int iCount = mSelectKeys.count();
    for (int i = 0; i < iCount; i++)
    {
        list << QString("%1 %2").arg(mSelectKeys.at(i)).arg(mSelectValues.at(i));
    }

    //Re-save the priority thesaurus file
    QString strData = list.join("\n");
    QFile file(mDataBasePath + "/chinese_select.txt");
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        file.write(strData.toUtf8());
    }
}

void QExtVirtualKeyboardPrivate::insertValue(const QString &value)
{
    //Just use it as a separate panel and send the selected content
    if (mOnlyControl)
    {
        this->saveChinese(value);
        this->clearValue();
        emit q_ptr->receiveValue(value);
        return;
    }

    if (mCurrentWidget == 0)
    {
        return;
    }

    //Save the currently selected character to the file as the preferred character
    this->saveChinese(value);

    //Cast to uppercase if a control is enabled for permanent uppercase
    QString strText = mCurrentWidget->property("upper").toBool() ? value.toUpper() : value;
    if (!strText.isEmpty())
    {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(strText));
        QApplication::sendEvent(mCurrentWidget, &keyPress);
    }

    this->clearValue();
}

void QExtVirtualKeyboardPrivate::clearValue()
{
    //Empty the pinyin TAB and restore the scroll bar
    q_ptr->ui->labPY->clear();
    q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    //Hide the Chinese character panel and display the letter panel if it is displayed on the Chinese character panel
    if (q_ptr->ui->widgetChinese->isVisible())
    {
        q_ptr->ui->widgetLetter->setVisible(true);
        q_ptr->ui->widgetNumber->setVisible(false);
        q_ptr->ui->widgetChinese->setVisible(false);
    }
}

void QExtVirtualKeyboardPrivate::deleteValue()
{
    if (QEXT_NULLPTR == mCurrentWidget)
    {
        return;
    }

    QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, QString());
    QApplication::sendEvent(mCurrentWidget, &keyPress);
}

void QExtVirtualKeyboardPrivate::showPanel()
{
    if (q_ptr->isEnabled())
    {
        //Hide the Chinese character panel and display the letter panel if it is displayed on the Chinese character panel
        QString strFlag = mCurrentWidget->property("flag").toString();
        if (mCurrentWidget->inherits("QAbstractSpinBox"))
        {
            strFlag = "number";
        }

        if (strFlag == "number")
        {
            if (QExtVirtualKeyboard::Input_Number != mInputType)
            {
                q_ptr->setVisible(false);
                q_ptr->setInputType(QExtVirtualKeyboard::Input_Number);
            }

            mIsNumber = false;
            q_ptr->setNumber(mIsNumber);
        }
        else
        {
            if (QExtVirtualKeyboard::Input_Number == mInputType)
            {
                q_ptr->setVisible(false);
                q_ptr->setInputType(QExtVirtualKeyboard::Input_English);
            }
        }

        q_ptr->setVisible(true);
    }
}

void QExtVirtualKeyboardPrivate::hidePanel()
{
    this->clearChinese();
    q_ptr->ui->labPY->clear();
    q_ptr->setVisible(false);
}

QExtVirtualKeyboard *QExtVirtualKeyboard::smInstance = QEXT_NULLPTR;
QExtVirtualKeyboard *QExtVirtualKeyboard::instance()
{
    if (QEXT_NULLPTR == smInstance)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        smInstance = new QExtVirtualKeyboard;
#ifdef Q_WS_QWS
        sm_pInstance->show();
#endif
        smInstance->hide();
    }
    return smInstance;
}

QExtVirtualKeyboard::QExtVirtualKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtVirtualKeyboard)
{
    ui->setupUi(this);
    dd_ptr = new QExtVirtualKeyboardPrivate;
    dd_ptr->q_ptr = this;
    dd_ptr->initForm();
    QTimer::singleShot(100, this, SLOT(init()));
}

QExtVirtualKeyboard::~QExtVirtualKeyboard()
{
    delete dd_ptr;
    delete ui;
}

void QExtVirtualKeyboard::showEvent(QShowEvent *)
{
    this->update();
}

bool QExtVirtualKeyboard::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this)
    {
        //Handle dragging itself
        static QPoint mousePoint;
        static bool bMousePressed = false;
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        //Remember the coordinates when you press, and move to the position where the mouse has been left off
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (pMouseEvent->button() == Qt::LeftButton)
            {
                bMousePressed = true;
                mousePoint = pMouseEvent->globalPos() - this->pos();
                return true;
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            bMousePressed = false;
            return true;
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (bMousePressed &&
                    (pMouseEvent->buttons() & Qt::LeftButton && PopUp_BottomCenter != dd_ptr->mPopUpType))
            {
                this->move(pMouseEvent->globalPos() - mousePoint);
                this->update();
                return true;
            }
        }
    }
    else if (watched == ui->labMore)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (Input_Chinese == dd_ptr->mInputType && !dd_ptr->mIsUpper &&
                    dd_ptr->mChineseLabels.first()->isEnabled())
            {
                if (!ui->widgetChinese->isVisible())
                {
                    ui->widgetLetter->setVisible(false);
                    ui->widgetNumber->setVisible(false);
                    ui->widgetChinese->setVisible(true);
                }
                else
                {
                    ui->widgetLetter->setVisible(true);
                    ui->widgetNumber->setVisible(false);
                    ui->widgetChinese->setVisible(false);
                }
                return true;
            }
        }
    }
    else if (watched == ui->labType)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (Input_English == dd_ptr->mInputType)
            {
                this->setInputType(Input_Chinese);
            }
            else if (Input_Chinese == dd_ptr->mInputType)
            {
                this->setInputType(Input_English);
            }
        }
    }
    else if (watched == ui->labType2)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            this->setInputType(Input_English);
        }
    }
    else if (watched == ui->widgetCn)
    {
        //Do not continue if there are no Chinese characters or if there are no Chinese characters in the press or if the current number of Chinese character tags is too small
        if (!dd_ptr->mChineseLabels.first()->isEnabled() || dd_ptr->mLastText.isEmpty())
        {
            return false;
        }

        //Remember the last time you hold down the drag, if it's too short, it's considered a slide. Start the slide animation
        static bool bPressed = false;
        static QPoint lastPos = QPoint();
        static QDateTime lastTime = QDateTime::currentDateTime();
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        if (event->type() == QEvent::MouseButtonPress)
        {
            bPressed = true;
            lastPos = pMouseEvent->pos();
            dd_ptr->mChineseAnimation->stop();
            lastTime = QDateTime::currentDateTime();
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            bPressed = false;
            if (lastPos != pMouseEvent->pos())
            {
                //Determine the current time and the mouse press event comparison, short time indicates a slide
                QDateTime now = QDateTime::currentDateTime();
                if (lastTime.msecsTo(now) < 600)
                {
                    //The following values can be changed to adjust the amplitude
                    bool bMoveleft = (pMouseEvent->pos().x() - lastPos.x()) < 0;
                    int iOffset = bMoveleft ? 350 : -350;
                    int iValue = ui->scrollAreaCn->horizontalScrollBar()->value();
                    dd_ptr->mChineseAnimation->setStartValue(iValue);
                    dd_ptr->mChineseAnimation->setEndValue(iValue + iOffset);
                    dd_ptr->mChineseAnimation->start();
                }
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (bPressed && dd_ptr->mChineseLabels.first()->isEnabled())
            {
                //Calculate the distance traveled
                bool bMoveleft = (pMouseEvent->pos().x() - lastPos.x()) < 0;
                int iOffset = bMoveleft ? 5 : -5;
                int iValue = ui->scrollAreaCn->horizontalScrollBar()->value();
                ui->scrollAreaCn->horizontalScrollBar()->setValue(iValue + iOffset);
                return true;
            }
        }
    }
    else if (watched == ui->widgetMore)
    {
        //Do not continue if there are no Chinese characters or if there are no Chinese characters in the press or if the current number of Chinese character tags is too small
        if (!dd_ptr->mMoreChineseLabels.first()->isEnabled() || dd_ptr->mLastText.isEmpty())
        {
            return false;
        }
        static bool bPressed = false;
        static QPoint lastPos = QPoint();
        static QDateTime lastTime = QDateTime::currentDateTime();
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        if (event->type() == QEvent::MouseButtonPress)
        {
            bPressed = true;
            lastPos = pMouseEvent->pos();
            dd_ptr->mMoreAnimation->stop();
            lastTime = QDateTime::currentDateTime();
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            bPressed = false;
            if (lastPos != pMouseEvent->pos())
            {
                //Determine the current time and the mouse press event comparison, short time indicates a slide
                QDateTime now = QDateTime::currentDateTime();
                if (lastTime.msecsTo(now) < 600)
                {
                    //The following values can be changed to adjust the amplitude
                    bool bMovebottom = (pMouseEvent->pos().y() - lastPos.y()) < 0;
                    int iOffset = bMovebottom ? 150 : -150;
                    int iValue = ui->scrollAreaMore->verticalScrollBar()->value();
                    dd_ptr->mMoreAnimation->setStartValue(iValue);
                    dd_ptr->mMoreAnimation->setEndValue(iValue + iOffset);
                    dd_ptr->mMoreAnimation->start();
                }
            }
        }
        else if (event->type() == QEvent::MouseMove)
        {
            if (bPressed && dd_ptr->mMoreChineseLabels.first()->isEnabled())
            {
                //Calculate the distance traveled
                bool bMovebottom = (pMouseEvent->pos().y() - lastPos.y()) < 0;
                int iOffset = bMovebottom ? 5 : -5;
                int iValue = ui->scrollAreaMore->verticalScrollBar()->value();
                ui->scrollAreaMore->verticalScrollBar()->setValue(iValue + iOffset);
                return true;
            }
        }
    }
    else if (watched->inherits("QLabel"))
    {
        QLabel *pLabel = (QLabel *)watched;
        if (!dd_ptr->mIsUpper && Input_Chinese == dd_ptr->mInputType)
        {
            if (pLabel->property("labCn").toBool())
            {
                //Remember the location of the scroll bar that was last pressed; if the scroll bar has not changed all the time, the label is considered to have been clicked
                static int iLastPosition = 0;
                if (event->type() == QEvent::MouseButtonPress)
                {
                    iLastPosition = ui->scrollAreaCn->horizontalScrollBar()->value();
                    dd_ptr->mLastText = pLabel->text();
                }
                else if (event->type() == QEvent::MouseButtonRelease)
                {
                    if (iLastPosition == ui->scrollAreaCn->horizontalScrollBar()->value() &&
                            !dd_ptr->mLastText.isEmpty())
                    {
                        dd_ptr->insertValue(pLabel->text());
                        dd_ptr->clearChinese();
                    }
                }
            }
            else if (pLabel->property("labMore").toBool())
            {
                //Remember the location of the scroll bar that was last pressed; if the scroll bar has not changed all the time, the label is considered to have been clicked
                static int iLastPosition = 0;
                if (event->type() == QEvent::MouseButtonPress)
                {
                    iLastPosition = ui->scrollAreaMore->verticalScrollBar()->value();
                    dd_ptr->mLastText = pLabel->text();
                }
                else if (event->type() == QEvent::MouseButtonRelease)
                {
                    if (iLastPosition == ui->scrollAreaMore->verticalScrollBar()->value() &&
                            !dd_ptr->mLastText.isEmpty())
                    {
                        dd_ptr->insertValue(pLabel->text());
                        dd_ptr->clearChinese();
                    }
                }
            }
        }
    }
    else
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            if (dd_ptr->mCurrentWidget != 0)
            {
                if (!this->isVisible())
                {
                    dd_ptr->showPanel();
                }
            }
            else
            {
                if (this->isVisible())
                {
                    dd_ptr->hidePanel();
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void QExtVirtualKeyboard::setFontInfo(const QString &fontName, const int &iBtnFontSize, const int &iLabFontSize)
{
    QFont btnFont(fontName, iBtnFontSize);
    QFont labFont(fontName, iLabFontSize);

    QList<QPushButton *> listButtons = this->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButtons)
    {
        pButton->setFont(btnFont);
    }

    ui->labType->setFont(btnFont);
    ui->labType2->setFont(btnFont);
    ui->labPY->setFont(labFont);

    foreach (QLabel *pLabel, dd_ptr->mChineseLabels)
    {
        pLabel->setFont(labFont);
    }

    foreach (QLabel *pLabel, dd_ptr->mMoreChineseLabels)
    {
        pLabel->setFont(labFont);
        pLabel->setFixedHeight(iLabFontSize + 30);
    }
}

void QExtVirtualKeyboard::setIconSize(const int &iIconWidth, const int &iIconHeight)
{
    QSize sizeUpper(iIconWidth + 3, iIconHeight);
    QSize sizeDelete(iIconWidth + 10, iIconHeight);
    ui->btnUpper->setIconSize(sizeUpper);
    ui->btnDelete->setIconSize(sizeDelete);
    ui->btnDelete2->setIconSize(sizeDelete);
}

void QExtVirtualKeyboard::setSpacing(const int &iSpacing)
{
    ui->widgetLetter1->layout()->setSpacing(iSpacing);
    ui->widgetLetter2->layout()->setSpacing(iSpacing);
    ui->widgetLetter3->layout()->setSpacing(iSpacing);
    ui->widgetNumber1->layout()->setSpacing(iSpacing);
    ui->widgetNumber2->layout()->setSpacing(iSpacing);
    ui->widgetNumber3->layout()->setSpacing(iSpacing);
}

void QExtVirtualKeyboard::setTopHeight(const int &iTopHeight)
{
    ui->widgetTop->setFixedHeight(iTopHeight);
}

void QExtVirtualKeyboard::setOnlyControl(const bool &bOnlyControl)
{
    dd_ptr->mOnlyControl = bOnlyControl;
}

void QExtVirtualKeyboard::setColumnCount(const int &iColumnCount)
{
    dd_ptr->mColumnCount = iColumnCount;
}

void QExtVirtualKeyboard::setMaxCount(const int &iMaxCount)
{
    dd_ptr->mMaxCount = iMaxCount;
}

void QExtVirtualKeyboard::setDbPath(const QString &dbPath)
{
    dd_ptr->mDataBasePath = dbPath;
}

void QExtVirtualKeyboard::setPopUpType(const QExtVirtualKeyboard::PopUpTypes &eType)
{
    dd_ptr->mPopUpType = eType;
}

void QExtVirtualKeyboard::setInputType(const InputTypes &eInputType)
{
    //Each mode change clears out the original characters
    dd_ptr->clearChinese();
    ui->labPY->clear();
    ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    dd_ptr->mInputType = eInputType;
    if (Input_Number == eInputType)
    {
        ui->widgetLetter->setVisible(false);
        ui->widgetNumber->setVisible(true);
        ui->widgetChinese->setVisible(false);
    }
    else if (Input_English == eInputType)
    {
        ui->widgetLetter->setVisible(true);
        ui->widgetNumber->setVisible(false);
        ui->widgetChinese->setVisible(false);
        ui->labType->setText(QString("<font color='%1'>ZH/</font><font color='%2' size='4'>Eng</font>")
                             .arg(dd_ptr->mMainTextColor).arg(dd_ptr->mButtonHoveColor));
    }
    else if (Input_Chinese == eInputType)
    {
        ui->widgetLetter->setVisible(true);
        ui->widgetNumber->setVisible(false);
        ui->widgetChinese->setVisible(false);
        ui->labType->setText(QString("<font color='%2' size='4'>ZH</font><font color='%1'>/Eng</font>")
                             .arg(dd_ptr->mMainTextColor).arg(dd_ptr->mButtonHoveColor));
    }
}

void QExtVirtualKeyboard::setUpper(const bool &bIsUpper)
{
    QList<QPushButton *> listButtons = ui->widgetLetter->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButtons)
    {
        QString strText = bIsUpper ? pButton->text().toUpper() : pButton->text().toLower();
        pButton->setText(strText);
    }

    //Change the icon
    ui->btnUpper->setIcon(QIcon(
                              QString(":/QExtKeyboard/input/btn_%1_%2.png").arg(bIsUpper ? "daxie" : "xiaoxie").arg(dd_ptr->mIconType)));
}

void QExtVirtualKeyboard::setNumber(const bool &bIsNumber)
{
    //You can change special symbols
    QStringList listChars;
    if (bIsNumber)
    {
        listChars << "【" << "】" << "{" << "}" << "#" << "%" << "^" << "*" << "+" << "=";
        listChars << "_" << "—" << "\\" << "|" << "~" << "《" << "》" << "$" << "&&" << "*_*";
        listChars << "…" << "," << ":" << ";" << "<" << ">";
    }
    else
    {
        listChars << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "0";
        listChars << "-" << "/" << "：" << "；" << "(" << ")" << "￥" << "@" << "“" << "”";
        listChars << "。" << "，" << "、" << "？" << "！" << ".";
    }

    ui->btn1->setText(listChars.at(0));
    ui->btn2->setText(listChars.at(1));
    ui->btn3->setText(listChars.at(2));
    ui->btn4->setText(listChars.at(3));
    ui->btn5->setText(listChars.at(4));
    ui->btn6->setText(listChars.at(5));
    ui->btn7->setText(listChars.at(6));
    ui->btn8->setText(listChars.at(7));
    ui->btn9->setText(listChars.at(8));
    ui->btn0->setText(listChars.at(9));
    ui->btn10->setText(listChars.at(10));
    ui->btn11->setText(listChars.at(11));
    ui->btn12->setText(listChars.at(12));
    ui->btn13->setText(listChars.at(13));
    ui->btn14->setText(listChars.at(14));
    ui->btn15->setText(listChars.at(15));
    ui->btn16->setText(listChars.at(16));
    ui->btn17->setText(listChars.at(17));
    ui->btn18->setText(listChars.at(18));
    ui->btn19->setText(listChars.at(19));
    ui->btn20->setText(listChars.at(20));
    ui->btn21->setText(listChars.at(21));
    ui->btn22->setText(listChars.at(22));
    ui->btn23->setText(listChars.at(23));
    ui->btn24->setText(listChars.at(24));
    ui->btn25->setText(listChars.at(25));

    ui->btnNumber2->setText(QString("%1").arg(dd_ptr->mIsNumber ? "123" : "#+="));
}

void QExtVirtualKeyboard::setStyleType(const StyleTypes &eStyle)
{
    dd_ptr->mStyleType = eStyle;
    dd_ptr->mIconType = "white";
    if (Style_Black == eStyle)
    {
        setColor("#191919", "#F3F3F3", "#313131", "#24B1DF", "#F3F3F3", "#F95717", "#F3F3F3");
    }
    else if (Style_Blue == eStyle)
    {
        setColor("#377FC9", "#F3F3F3", "#4189D3", "#386487", "#F3F3F3", "#386487", "#F3F3F3");
    }
    else if (Style_Gray == eStyle)
    {
        setColor("#989898", "#FFFFFF", "#A2A2A2", "#333333", "#F3F3F3", "#2E2E2E", "#F3F3F3");
    }
    else if (Style_Brown == eStyle)
    {
        setColor("#667481", "#F3F3F3", "#566373", "#4189D3", "#F3F3F3", "#4189D3", "#F3F3F3");
    }
    else if (Style_Silvery == eStyle)
    {
        setColor("#868690", "#000002", "#C3C2C7", "#F0F0F0", "#000002", "#F0F0F0", "#000002");
        dd_ptr->mIconType = "black";
    }

    ui->labMore->setPixmap(QString(":/QExtKeyboard/input/btn_%1_%2.png").arg("more").arg(dd_ptr->mIconType));
    ui->btnDelete->setIcon(
                QIcon(QString(":/QExtKeyboard/input/btn_%1_%2.png").arg("delete").arg(dd_ptr->mIconType)));
    ui->btnDelete2->setIcon(
                QIcon(QString(":/QExtKeyboard/input/btn_%1_%2.png").arg("delete").arg(dd_ptr->mIconType)));
    ui->btnUpper->setIcon(QIcon(
                              QString(":/QExtKeyboard/input/btn_%1_%2.png").arg(dd_ptr->mIsUpper ? "daxie" : "xiaoxie").arg(
                                  dd_ptr->mIconType)));
}

void QExtVirtualKeyboard::setColor(const QString &mainBkgColor, const QString &mainTextColor,
                                   const QString &btnBkgColor, const QString &btnHoveColor,
                                   const QString &btnHoveTextColor, const QString &labHoveColor,
                                   const QString &labHoveTextColor)
{
    dd_ptr->mMainTextColor = mainTextColor;
    dd_ptr->mButtonHoveColor = btnHoveColor;

    QStringList qssStrings;
    qssStrings.append(QString("QScrollArea{"
                              "border:none;"
                              "background:rgba(255,255,255,0);}"
                              "QWidget#widgetCn,"
                              "QWidget#widgetMore{"
                              "background:rgba(0,0,0,0);}"));
    qssStrings.append(QString("QWidget#widgetCn,"
                              "QWidget#widgetTop,"
                              "QWidget#widgetMore,"
                              "QWidget#widgetLetter,"
                              "QWidget#widgetLetter1,"
                              "QWidget#widgetLetter2,"
                              "QWidget#widgetLetter3,"
                              "QWidget#widgetNumber,"
                              "QWidget#widgetNumber1,"
                              "QWidget#widgetNumber2,"
                              "QWidget#widgetNumber3,"
                              "QWidget#widgetChinese{"
                              "background-color:%1;}").arg(mainBkgColor));
    qssStrings.append(QString("#labType,"
                              "#labType2,"
                              "QPushButton{"
                              "border-width:0px;"
                              "border-radius:3px;"
                              "color:%1;}").arg(mainTextColor));
    qssStrings.append(QString("#labType,"
                              "#labType2,"
                              "QPushButton{"
                              "padding:0px;"
                              "background-color:%1;}").arg(btnBkgColor));
    //If it is only a touch screen, please use the following sentence
    qssStrings.append(QString("QPushButton:pressed{"
                              "background-color:%1;"
                              "color:%2;}").arg(btnHoveColor).arg(btnHoveTextColor));
    qssStrings.append(QString("QPushButton:pressed,"
                              "QPushButton:hover{"
                              "background-color:%1;"
                              "color:%2;}").arg(btnHoveColor).arg(btnHoveTextColor));
    qssStrings.append(QString("QLabel{"
                              "padding:0px 5px 0px 5px;"
                              "border-width:0px;"
                              "border-radius:3px;"
                              "color:%1;"
                              "background:none;}").arg(mainTextColor));
    qssStrings.append(QString("QLabel:pressed,"
                              "QLabel:hover{"
                              "background-color:%1;"
                              "color:%2;}").arg(labHoveColor).arg(labHoveTextColor));
    qssStrings.append(QString("QLabel:disabled{"
                              "background:none;}"));
    this->setStyleSheet(qssStrings.join(""));

    ui->labType->setText(
                QString("<font color='%1'>ZH/</font><font color='%2' size='4'>Eng</font>").arg(mainTextColor).arg(btnHoveColor));
    ui->labType2->setText(
                QString("<font color='%2' size='4'>ZH</font><font color='%1'>/Eng</font>").arg(mainTextColor).arg(btnHoveColor));
    qApp->processEvents();
}

#include <moc_qextVirtualKeyboard.cpp>
