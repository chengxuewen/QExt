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

#include <qextInput.h>
#include <ui_qextInput.h>

#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <QScrollBar>
#include <QKeyEvent>
#include <QMutex>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QMatrix>
#include <QMutexLocker>
#include <QFile>



class QExtInputPrivate
{
public:
    QExtInputPrivate();
    ~QExtInputPrivate();

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
    QExtInput *q_ptr;
    Q_DECLARE_PUBLIC(QExtInput)

    bool m_bIsUpper;
    bool m_bIsNumber;
    bool m_bOnlyControl;
    int m_iColumnCount;
    int m_iMaxCount;

    QString m_strDataBasePath;
    QString m_strIconType;
    QExtInput::PopUpTypes m_ePopUpType;
    QExtInput::InputTypes m_eInputType;
    QExtInput::StyleTypes m_eStyleType;

    QWidget *m_pCurrentWidget;
    QList<QLabel *> m_listChineseLabel;
    QList<QLabel *> m_listMoreChineseLabel;

    QStringList m_listAllPinYin;
    QExtGooglePinYin m_googlePinYin;

    QString m_strMainTextColor;
    QString m_strButtonHoveColor;
    QString m_strLastText;

    QPropertyAnimation *m_pChineseAnimation;
    QPropertyAnimation *m_pMoreAnimation;

    QStringList m_listSelectKey;
    QStringList m_listSelectValue;
    QStringList m_listUserKey;
    QStringList m_listUserValue;
};


QExtInputPrivate::QExtInputPrivate()
{
    m_ePopUpType = QExtInput::PopUp_BottomCenter;
    m_eStyleType = QExtInput::Style_Black;
}

QExtInputPrivate::~QExtInputPrivate()
{

}

void QExtInputPrivate::initForm()
{
#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
    q_ptr->setWindowFlags(Qt::Tool | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#else
    q_ptr->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
#endif
    Q_INIT_RESOURCE(qextWidgets);
    m_pCurrentWidget = 0;
    m_bIsUpper = false;
    m_bIsNumber = false;
    m_bOnlyControl = false;
    m_iColumnCount = 8;
    m_iMaxCount = 256;
    m_strDataBasePath = qApp->applicationDirPath();

    //Bind buttons to events
    QList<QPushButton *> listButton;
    listButton << q_ptr->ui->widgetLetter->findChildren<QPushButton *>();
    listButton << q_ptr->ui->widgetNumber->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton) {
        pButton->setProperty("btnInput", true);
        QObject::connect(pButton, SIGNAL(clicked()), q_ptr, SLOT(buttonClicked()));
    }

    //Set letter properties
    listButton.clear();
    listButton << q_ptr->ui->widgetLetter1->findChildren<QPushButton *>();
    listButton << q_ptr->ui->widgetLetter2->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton) {
        pButton->setProperty("btnLetter", true);
    }

    //Set all button input methods not available + long press to automatically repeat the event
    listButton.clear();
    listButton << q_ptr->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButton) {
        pButton->setFocusPolicy(Qt::NoFocus);
        pButton->setProperty("noinput", true);
        pButton->setAutoRepeat(true);
        pButton->setAutoRepeatDelay(500);
    }

    //By default, a maximum of 256 are generated and added to the top scroll area
    for (int i = 0; i < m_iMaxCount; i++) {
        QLabel *lab = new QLabel;
        lab->setProperty("labCn", true);
        lab->setEnabled(false);
        q_ptr->ui->layout->addWidget(lab);
        m_listChineseLabel << lab;
    }

    //The default is to generate a maximum of 256, which is added to more scrolling areas
    int iRow = 0;
    int iColumn = 0;
    for (int i = 0; i < m_iMaxCount; i++) {
        QLabel *pLabel = new QLabel();
        pLabel->setProperty("labMore", true);
        pLabel->setEnabled(false);
        pLabel->setAlignment(Qt::AlignCenter);
        pLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        q_ptr->ui->gridLayout->addWidget(pLabel, iRow, iColumn);
        m_listMoreChineseLabel << pLabel;

        iColumn++;
        if (iColumn >= m_iColumnCount) {
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
    q_ptr->setInputType(QExtInput::Input_English);
    //Input method panel style black- black blue- light blue brown- gray- black gray- gray Silvery - silver
    q_ptr->setStyleType(QExtInput::Style_Black);

    //Define an animation to produce a smooth value
    m_pChineseAnimation = new QPropertyAnimation(q_ptr->ui->scrollAreaCn->horizontalScrollBar(), "value");
    m_pChineseAnimation->setEasingCurve(QEasingCurve::OutCirc);
    m_pChineseAnimation->setDuration(500);

    m_pMoreAnimation = new QPropertyAnimation(q_ptr->ui->scrollAreaMore->verticalScrollBar(), "value");
    m_pMoreAnimation->setEasingCurve(QEasingCurve::OutCirc);
    m_pMoreAnimation->setDuration(500);
}

void QExtInputPrivate::init()
{
    if (m_bOnlyControl) {
        q_ptr->ui->labPY->setVisible(false);
        q_ptr->installEventFilter(q_ptr);
        q_ptr->ui->labType->installEventFilter(q_ptr);
        q_ptr->ui->labType2->installEventFilter(q_ptr);
        q_ptr->ui->labMore->installEventFilter(q_ptr);
        q_ptr->ui->widgetCn->installEventFilter(q_ptr);
        q_ptr->ui->widgetMore->installEventFilter(q_ptr);

        foreach (QLabel *pLabel, m_listChineseLabel) {
            pLabel->installEventFilter(q_ptr);
        }

        foreach (QLabel *pLabel, m_listMoreChineseLabel) {
            pLabel->installEventFilter(q_ptr);
        }
    } else {
        //Bind globally to change the focus signal slot
        QObject::connect(qApp, SIGNAL(focusChanged(QWidget *, QWidget *)), q_ptr, SLOT(focusChanged(QWidget *, QWidget *)));
        qApp->installEventFilter(q_ptr);
    }

    m_googlePinYin.open(m_strDataBasePath);
    this->readChinese();
}

void QExtInputPrivate::buttonClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(q_ptr->sender());
    QString strObjectName = pButton->objectName();
    QString strButtonText = pButton->text();
    QString strLabelText = q_ptr->ui->labPY->text();
    q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    if ("btnUpper" == strObjectName) {
        m_bIsUpper = !m_bIsUpper;
        q_ptr->setUpper(m_bIsUpper);
        clearChinese();
        q_ptr->ui->labPY->clear();
    } else if ("btnNumber" == strObjectName) {
        q_ptr->setInputType(QExtInput::Input_Number);
    } else if ("btnNumber2" == strObjectName) {
        m_bIsNumber = !m_bIsNumber;
        q_ptr->setNumber(m_bIsNumber);
    } else if ("btnDelete" == strObjectName || "btnDelete2" == strObjectName) {
        //If the current mode is Chinese, delete the corresponding pinyin, and then delete the content of the corresponding text input box after deleting the pinyin
        int iLength = strLabelText.length();
        if (QExtInput::Input_Chinese == m_eInputType && iLength > 0) {
            q_ptr->ui->labPY->setText(strLabelText.left(iLength - 1));
            this->selectChinese();
        } else {
            this->deleteValue();
        }

        q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
        q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);
    } else if ("btnSpace" == strObjectName || "btnSpace2" == strObjectName) {
        //If The Chinese mode is to be entered and the character is to be entered, the first Chinese character is inserted if there is any Chinese character
        if (QExtInput::Input_Chinese == m_eInputType && !strLabelText.isEmpty()) {
            QString strText = m_listChineseLabel.first()->text();
            if (strText.isEmpty()) {
                this->insertValue(strLabelText);
            } else {
                this->insertValue(strText);
            }
            this->clearChinese();
        } else {
            this->insertValue(" ");
        }
    } else if ("btnEnter" == strObjectName || "btnEnter2" == strObjectName) {
        //If Chinese mode and the letter is to be entered, insert the letter immediately
        if (QExtInput::Input_Chinese == m_eInputType && !strLabelText.isEmpty()) {
            this->insertValue(strLabelText);
            this->clearChinese();
        }

        if (QEXT_DECL_NULLPTR != m_pCurrentWidget && !m_bOnlyControl) {
            this->hidePanel();
            QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier, QString("\n"));
            QApplication::sendEvent(m_pCurrentWidget, &keyPress);
        } else {
            this->insertValue("\n");
        }
    } else {
        //If it is an & button, the real text is to remove the preceding & character because the corresponding & is filtered
        if ("&&" == strButtonText) {
            strButtonText = "&";
        }

        //If the current mode is not Chinese, click the button corresponding to text as the passing parameter, uppercase first
        if (QExtInput::Input_Chinese != m_eInputType || m_bIsUpper) {
            this->insertValue(strButtonText);
        } else {
            if (pButton->property("btnLetter").toBool()) {
                q_ptr->ui->labPY->setText(strLabelText + strButtonText);
                this->selectChinese();
            }
        }
    }
}

void QExtInputPrivate::focusChanged(QWidget *oldWidget, QWidget *nowWidget)
{
    //    qDebug() << "oldWidget:" << oldWidget << "nowWidget:" << nowWidget;
    Q_UNUSED(oldWidget);
    m_pCurrentWidget = nowWidget;
    if (nowWidget != 0 && !q_ptr->isAncestorOf(nowWidget)) {
        //If the corresponding property NoInput is true or read-only, it is not displayed
        if (nowWidget->property("noinput").toBool() || nowWidget->property("readOnly").toBool()) {
            m_pCurrentWidget = 0;
            QTimer::singleShot(0, q_ptr, SLOT(hidePanel()));
            return;
        }

        if (nowWidget->inherits("QWidget")) {
            //Legal input control, can be added by itself
            QStringList listClassNames;
            listClassNames << "QLineEdit" << "QTextEdit" << "QPlainTextEdit" << "QAbstractSpinBox" << "QComboBox";
            listClassNames << "QQuickWidget" << "QWebView" << "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget";

            //Finds out if the current focus control is a legally entered control
            bool bExist = false;
            foreach (QString strClassName, listClassNames) {
                if (nowWidget->inherits(strClassName.toLatin1().constData())) {
                    //Determines whether the drop-down box's editable property is true if it is currently a drop-down box
                    if (strClassName != "QComboBox" || nowWidget->property("editable").toBool()) {
                        bExist = true;
                        break;
                    }
                }
            }

            if (bExist) {
                this->showPanel();
                this->movePosition();
            } else {
                m_pCurrentWidget = 0;
                this->hidePanel();
            }
        }
    }
}

void QExtInputPrivate::movePosition()
{
    //According to the user's choice of input method location Settings - center display - bottom fill - displayed directly below the input box
    static int iDeskWidth = qApp->desktop()->availableGeometry().width();
    static int iDeskHeight = qApp->desktop()->availableGeometry().height();
    int iWidth = q_ptr->width();
    int iHeight = q_ptr->height();

    if (QExtInput::PopUp_Center == m_ePopUpType) {
        QPoint pos = QPoint(iDeskWidth / 2 - iWidth / 2, iDeskHeight / 2 - iHeight / 2);
        q_ptr->setGeometry(pos.x(), pos.y(), iWidth, iHeight);
    } else if (QExtInput::PopUp_BottomCenter == m_ePopUpType) {
        QRect rect = m_pCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = m_pCurrentWidget->mapToGlobal(pos);
        int iX = (iDeskWidth - iWidth) / 2;
        int iY = iDeskHeight - iHeight;
        if (pos.y() + iHeight > iDeskHeight) {
            iY = pos.y() - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    } else if (QExtInput::PopUp_FocusHCenter == m_ePopUpType) {
        QRect rect = m_pCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = m_pCurrentWidget->mapToGlobal(pos);
        int iX = (iDeskWidth - iWidth) / 2;
        int iY = pos.y();
        if (iY + iHeight > iDeskHeight) {
            iY = iY - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    } else if (QExtInput::PopUp_Control == m_ePopUpType) {
        QRect rect = m_pCurrentWidget->rect();
        QPoint pos = QPoint(rect.left(), rect.bottom() + 2);
        pos = m_pCurrentWidget->mapToGlobal(pos);
        int iX = pos.x();
        if (iX + iWidth > iDeskWidth) {
            iX = iDeskWidth - iWidth;
        }
        int iY = pos.y();
        if (iY + iHeight > iDeskHeight) {
            iY = iY - iHeight - rect.height() - 2;
        }
        q_ptr->setGeometry(iX, iY, iWidth, iHeight);
    }
}

void QExtInputPrivate::selectChinese()
{
    //Empty the Chinese characters
    this->clearChinese();

    //For the current pinyin query Chinese characters, if the maximum number of Chinese characters to take the first
    QString strLabelText = q_ptr->ui->labPY->text();
    if (strLabelText.length() > 15) {
        qDebug() << "input too long";
        return;
    }

    int iCount = m_googlePinYin.select(strLabelText);
    iCount = iCount > m_iMaxCount ? m_iMaxCount : iCount;

    //Insert the user to create the word Chinese characters, the highest priority, insert the first
    int iIndexUser = m_listUserKey.indexOf(strLabelText);
    if (iIndexUser >= 0) {
        QString strChineses = m_listUserValue.at(iIndexUser);
        QStringList list = strChineses.split("|");
        for (int i = list.count() - 1; i >= 0; i--) {
            QString strChinese = list.at(i);
            if (!strChinese.isEmpty()) {
                m_listAllPinYin.insert(0, strChinese);
            }
        }
    }

    //Insert the user-selected word, in the middle of the priority list, immediately after the user-generated word
    int iIndexSelect = m_listSelectKey.indexOf(strLabelText);
    if (iIndexSelect >= 0) {
        QString strChineses = m_listSelectValue.at(iIndexSelect);
        QStringList list = strChineses.split("|");
        for (int i = 0; i < list.count(); i++) {
            QString strChinese = list.at(i);
            if (!strChinese.isEmpty() && !m_listAllPinYin.contains(strChinese)) {
                m_listAllPinYin << strChinese;
            }
        }
    }

    //Insert queried Chinese characters that have been filtered in the Chinese character queue
    for (int i = 0; i < iCount; i++) {
        QString strText = m_googlePinYin.getChinese(i);
        if (!strText.isEmpty() && !m_listAllPinYin.contains(strText)) {
            m_listAllPinYin << strText;
        }
    }

    //According to the Chinese character
    this->showChinese();
}

void QExtInputPrivate::showChinese()
{
    for (int i = 0; i < m_iMaxCount; i++) {
        m_listChineseLabel.at(i)->clear();
        m_listMoreChineseLabel.at(i)->clear();
        m_listChineseLabel.at(i)->setEnabled(false);
        m_listMoreChineseLabel.at(i)->setEnabled(false);
    }

    for (int i = 0; i < m_listAllPinYin.count(); i++) {
        m_listChineseLabel.at(i)->setText(m_listAllPinYin.at(i));
        m_listMoreChineseLabel.at(i)->setText(m_listAllPinYin.at(i));
        m_listChineseLabel.at(i)->setEnabled(true);
        m_listMoreChineseLabel.at(i)->setEnabled(true);
    }
}

void QExtInputPrivate::clearChinese()
{
    m_listAllPinYin.clear();
    for (int i = 0; i < m_iMaxCount; i++) {
        m_listChineseLabel.at(i)->clear();
        m_listMoreChineseLabel.at(i)->clear();
        m_listChineseLabel.at(i)->setEnabled(false);
        m_listMoreChineseLabel.at(i)->setEnabled(false);
    }
}

void QExtInputPrivate::readChinese()
{
    //Load the local priority lexicon
    m_listSelectKey.clear();
    m_listSelectValue.clear();
    QFile fileSelect(m_strDataBasePath + "/chinese_select.txt");
    if (fileSelect.open(QFile::ReadOnly | QFile::Text)) {
        while(!fileSelect.atEnd()) {
            QString line = fileSelect.readLine();
            line = line.replace("\n", "");
            QStringList list = line.split(" ");
            m_listSelectKey << list.at(0);
            m_listSelectValue << list.at(1);
        }

        fileSelect.close();
    }

    //Loads the local custom thesaurus
    m_listUserKey.clear();
    m_listUserValue.clear();
    QFile fileUser(m_strDataBasePath + "/chinese_user.txt");
    if (fileUser.open(QFile::ReadOnly | QFile::Text)) {
        while(!fileUser.atEnd()) {
            QString line = fileUser.readLine();
            line = line.replace("\n", "");
            QStringList list = line.split(" ");
            m_listUserKey << list.at(0);
            m_listUserValue << list.at(1);
        }

        fileUser.close();
    }
}

void QExtInputPrivate::saveChinese(const QString &value)
{
    //Not currently in Chinese input state need not be processed
    if (QExtInput::Input_Chinese != m_eInputType || value.isEmpty() || m_strLastText.isEmpty()) {
        return;
    }

    //Insert the currently selected Character into the file as the priority word library
    QString strPinyin = q_ptr->ui->labPY->text();
    int iIndex = m_listSelectKey.indexOf(strPinyin);

    //If the current letter is already in the priority thesaurus file, update the character corresponding to that letter
    if (iIndex >= 0) {
        QStringList listTemp;
        QString strChineses = m_listSelectValue.at(iIndex);
        QStringList list = strChineses.split("|");

        //If it already exists, it does not need to be added at present. It can be directly inserted in the front after
        bool bExist = list.contains(value);
        foreach (QString str, list) {
            if (bExist && str == value) {
                continue;
            }
            if (!str.isEmpty()) {
                listTemp << str;
            }
        }

        listTemp.insert(0, value);
        m_listSelectValue[iIndex] = listTemp.join("|");
    } else {
        m_listSelectKey << strPinyin;
        m_listSelectValue << value;
    }

    QStringList list;
    int iCount = m_listSelectKey.count();
    for (int i = 0; i < iCount; i++) {
        list << QString("%1 %2").arg(m_listSelectKey.at(i)).arg(m_listSelectValue.at(i));
    }

    //Re-save the priority thesaurus file
    QString strData = list.join("\n");
    QFile file(m_strDataBasePath + "/chinese_select.txt");
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(strData.toUtf8());
    }
}

void QExtInputPrivate::insertValue(const QString &value)
{
    //Just use it as a separate panel and send the selected content
    if (m_bOnlyControl) {
        this->saveChinese(value);
        this->clearValue();
        emit q_ptr->receiveValue(value);
        return;
    }

    if (m_pCurrentWidget == 0) {
        return;
    }

    //Save the currently selected character to the file as the preferred character
    this->saveChinese(value);

    //Cast to uppercase if a control is enabled for permanent uppercase
    QString strText = m_pCurrentWidget->property("upper").toBool() ? value.toUpper() : value;
    if (!strText.isEmpty()) {
        QKeyEvent keyPress(QEvent::KeyPress, 0, Qt::NoModifier, QString(strText));
        QApplication::sendEvent(m_pCurrentWidget, &keyPress);
    }

    this->clearValue();
}

void QExtInputPrivate::clearValue()
{
    //Empty the pinyin TAB and restore the scroll bar
    q_ptr->ui->labPY->clear();
    q_ptr->ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    q_ptr->ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    //Hide the Chinese character panel and display the letter panel if it is displayed on the Chinese character panel
    if (q_ptr->ui->widgetChinese->isVisible()) {
        q_ptr->ui->widgetLetter->setVisible(true);
        q_ptr->ui->widgetNumber->setVisible(false);
        q_ptr->ui->widgetChinese->setVisible(false);
    }
}

void QExtInputPrivate::deleteValue()
{
    if (QEXT_DECL_NULLPTR == m_pCurrentWidget) {
        return;
    }

    QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, QString());
    QApplication::sendEvent(m_pCurrentWidget, &keyPress);
}

void QExtInputPrivate::showPanel()
{
    if (q_ptr->isEnabled()) {
        //Hide the Chinese character panel and display the letter panel if it is displayed on the Chinese character panel
        QString strFlag = m_pCurrentWidget->property("flag").toString();
        if (m_pCurrentWidget->inherits("QAbstractSpinBox")) {
            strFlag = "number";
        }

        if (strFlag == "number") {
            if (QExtInput::Input_Number != m_eInputType) {
                q_ptr->setVisible(false);
                q_ptr->setInputType(QExtInput::Input_Number);
            }

            m_bIsNumber = false;
            q_ptr->setNumber(m_bIsNumber);
        } else {
            if (QExtInput::Input_Number == m_eInputType) {
                q_ptr->setVisible(false);
                q_ptr->setInputType(QExtInput::Input_English);
            }
        }

        q_ptr->setVisible(true);
    }
}

void QExtInputPrivate::hidePanel()
{
    this->clearChinese();
    q_ptr->ui->labPY->clear();
    q_ptr->setVisible(false);
}

QExtInput *QExtInput::sm_pInstance = QEXT_DECL_NULLPTR;
QExtInput *QExtInput::Instance()
{
    if (QEXT_DECL_NULLPTR == sm_pInstance) {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        sm_pInstance = new QExtInput;
#ifdef Q_WS_QWS
        sm_pInstance->show();
#endif
        sm_pInstance->hide();
    }
    return sm_pInstance;
}

QExtInput::QExtInput(QWidget *parent) : QWidget(parent), ui(new Ui::QExtInput)
{
    ui->setupUi(this);
    dd_ptr = new QExtInputPrivate;
    dd_ptr->q_ptr = this;
    dd_ptr->initForm();
    QTimer::singleShot(100, this, SLOT(init()));
}

QExtInput::~QExtInput()
{
    delete dd_ptr;
    delete ui;
}

void QExtInput::showEvent(QShowEvent *)
{
    this->update();
}

bool QExtInput::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        //Handle dragging itself
        static QPoint mousePoint;
        static bool bMousePressed = false;
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        //Remember the coordinates when you press, and move to the position where the mouse has been left off
        if (event->type() == QEvent::MouseButtonPress) {
            if (pMouseEvent->button() == Qt::LeftButton) {
                bMousePressed = true;
                mousePoint = pMouseEvent->globalPos() - this->pos();
                return true;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            bMousePressed = false;
            return true;
        } else if (event->type() == QEvent::MouseMove) {
            if (bMousePressed && (pMouseEvent->buttons() & Qt::LeftButton && PopUp_BottomCenter != dd_ptr->m_ePopUpType)) {
                this->move(pMouseEvent->globalPos() - mousePoint);
                this->update();
                return true;
            }
        }
    } else if (watched == ui->labMore) {
        if (event->type() == QEvent::MouseButtonPress) {
            if (Input_Chinese == dd_ptr->m_eInputType && !dd_ptr->m_bIsUpper && dd_ptr->m_listChineseLabel.first()->isEnabled()) {
                if (!ui->widgetChinese->isVisible()) {
                    ui->widgetLetter->setVisible(false);
                    ui->widgetNumber->setVisible(false);
                    ui->widgetChinese->setVisible(true);
                } else {
                    ui->widgetLetter->setVisible(true);
                    ui->widgetNumber->setVisible(false);
                    ui->widgetChinese->setVisible(false);
                }
                return true;
            }
        }
    } else if (watched == ui->labType) {
        if (event->type() == QEvent::MouseButtonPress) {
            if (Input_English == dd_ptr->m_eInputType) {
                this->setInputType(Input_Chinese);
            } else if (Input_Chinese == dd_ptr->m_eInputType) {
                this->setInputType(Input_English);
            }
        }
    } else if (watched == ui->labType2) {
        if (event->type() == QEvent::MouseButtonPress) {
            this->setInputType(Input_English);
        }
    } else if (watched == ui->widgetCn) {
        //Do not continue if there are no Chinese characters or if there are no Chinese characters in the press or if the current number of Chinese character tags is too small
        if (!dd_ptr->m_listChineseLabel.first()->isEnabled() || dd_ptr->m_strLastText.isEmpty()) {
            return false;
        }

        //Remember the last time you hold down the drag, if it's too short, it's considered a slide. Start the slide animation
        static bool bPressed = false;
        static QPoint lastPos = QPoint();
        static QDateTime lastTime = QDateTime::currentDateTime();
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        if (event->type() == QEvent::MouseButtonPress) {
            bPressed = true;
            lastPos = pMouseEvent->pos();
            dd_ptr->m_pChineseAnimation->stop();
            lastTime = QDateTime::currentDateTime();
        } else if (event->type() == QEvent::MouseButtonRelease) {
            bPressed = false;
            if (lastPos != pMouseEvent->pos()) {
                //Determine the current time and the mouse press event comparison, short time indicates a slide
                QDateTime now = QDateTime::currentDateTime();
                if (lastTime.msecsTo(now) < 600) {
                    //The following values can be changed to adjust the amplitude
                    bool bMoveleft = (pMouseEvent->pos().x() - lastPos.x()) < 0;
                    int iOffset = bMoveleft ? 350 : -350;
                    int iValue = ui->scrollAreaCn->horizontalScrollBar()->value();
                    dd_ptr->m_pChineseAnimation->setStartValue(iValue);
                    dd_ptr->m_pChineseAnimation->setEndValue(iValue + iOffset);
                    dd_ptr->m_pChineseAnimation->start();
                }
            }
        } else if (event->type() == QEvent::MouseMove) {
            if (bPressed && dd_ptr->m_listChineseLabel.first()->isEnabled()) {
                //Calculate the distance traveled
                bool bMoveleft = (pMouseEvent->pos().x() - lastPos.x()) < 0;
                int iOffset = bMoveleft ? 5 : -5;
                int iValue = ui->scrollAreaCn->horizontalScrollBar()->value();
                ui->scrollAreaCn->horizontalScrollBar()->setValue(iValue + iOffset);
                return true;
            }
        }
    } else if (watched == ui->widgetMore) {
        //Do not continue if there are no Chinese characters or if there are no Chinese characters in the press or if the current number of Chinese character tags is too small
        if (!dd_ptr->m_listMoreChineseLabel.first()->isEnabled() || dd_ptr->m_strLastText.isEmpty()) {
            return false;
        }
        static bool bPressed = false;
        static QPoint lastPos = QPoint();
        static QDateTime lastTime = QDateTime::currentDateTime();
        QMouseEvent *pMouseEvent = static_cast<QMouseEvent *>(event);

        if (event->type() == QEvent::MouseButtonPress) {
            bPressed = true;
            lastPos = pMouseEvent->pos();
            dd_ptr->m_pMoreAnimation->stop();
            lastTime = QDateTime::currentDateTime();
        } else if (event->type() == QEvent::MouseButtonRelease) {
            bPressed = false;
            if (lastPos != pMouseEvent->pos()) {
                //Determine the current time and the mouse press event comparison, short time indicates a slide
                QDateTime now = QDateTime::currentDateTime();
                if (lastTime.msecsTo(now) < 600) {
                    //The following values can be changed to adjust the amplitude
                    bool bMovebottom = (pMouseEvent->pos().y() - lastPos.y()) < 0;
                    int iOffset = bMovebottom ? 150 : -150;
                    int iValue = ui->scrollAreaMore->verticalScrollBar()->value();
                    dd_ptr->m_pMoreAnimation->setStartValue(iValue);
                    dd_ptr->m_pMoreAnimation->setEndValue(iValue + iOffset);
                    dd_ptr->m_pMoreAnimation->start();
                }
            }
        } else if (event->type() == QEvent::MouseMove) {
            if (bPressed && dd_ptr->m_listMoreChineseLabel.first()->isEnabled()) {
                //Calculate the distance traveled
                bool bMovebottom = (pMouseEvent->pos().y() - lastPos.y()) < 0;
                int iOffset = bMovebottom ? 5 : -5;
                int iValue = ui->scrollAreaMore->verticalScrollBar()->value();
                ui->scrollAreaMore->verticalScrollBar()->setValue(iValue + iOffset);
                return true;
            }
        }
    } else if (watched->inherits("QLabel")) {
        QLabel *pLabel = (QLabel *)watched;
        if (!dd_ptr->m_bIsUpper && Input_Chinese == dd_ptr->m_eInputType) {
            if (pLabel->property("labCn").toBool()) {
                //Remember the location of the scroll bar that was last pressed; if the scroll bar has not changed all the time, the label is considered to have been clicked
                static int iLastPosition = 0;
                if (event->type() == QEvent::MouseButtonPress) {
                    iLastPosition = ui->scrollAreaCn->horizontalScrollBar()->value();
                    dd_ptr->m_strLastText = pLabel->text();
                } else if (event->type() == QEvent::MouseButtonRelease) {
                    if (iLastPosition == ui->scrollAreaCn->horizontalScrollBar()->value() && !dd_ptr->m_strLastText.isEmpty()) {
                        dd_ptr->insertValue(pLabel->text());
                        dd_ptr->clearChinese();
                    }
                }
            } else if (pLabel->property("labMore").toBool()) {
                //Remember the location of the scroll bar that was last pressed; if the scroll bar has not changed all the time, the label is considered to have been clicked
                static int iLastPosition = 0;
                if (event->type() == QEvent::MouseButtonPress) {
                    iLastPosition = ui->scrollAreaMore->verticalScrollBar()->value();
                    dd_ptr->m_strLastText = pLabel->text();
                } else if (event->type() == QEvent::MouseButtonRelease) {
                    if (iLastPosition == ui->scrollAreaMore->verticalScrollBar()->value() && !dd_ptr->m_strLastText.isEmpty()) {
                        dd_ptr->insertValue(pLabel->text());
                        dd_ptr->clearChinese();
                    }
                }
            }
        }
    } else {
        if (event->type() == QEvent::MouseButtonPress) {
            if (dd_ptr->m_pCurrentWidget != 0) {
                if (!this->isVisible()) {
                    dd_ptr->showPanel();
                }
            } else {
                if (this->isVisible()) {
                    dd_ptr->hidePanel();
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void QExtInput::setFontInfo(const QString &fontName, const int &iBtnFontSize, const int &iLabFontSize)
{
    QFont btnFont(fontName, iBtnFontSize);
    QFont labFont(fontName, iLabFontSize);

    QList<QPushButton *> listButtons = this->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButtons) {
        pButton->setFont(btnFont);
    }

    ui->labType->setFont(btnFont);
    ui->labType2->setFont(btnFont);
    ui->labPY->setFont(labFont);

    foreach (QLabel *pLabel, dd_ptr->m_listChineseLabel) {
        pLabel->setFont(labFont);
    }

    foreach (QLabel *pLabel, dd_ptr->m_listMoreChineseLabel) {
        pLabel->setFont(labFont);
        pLabel->setFixedHeight(iLabFontSize + 30);
    }
}

void QExtInput::setIconSize(const int &iIconWidth, const int &iIconHeight)
{
    QSize sizeUpper(iIconWidth + 3, iIconHeight);
    QSize sizeDelete(iIconWidth + 10, iIconHeight);
    ui->btnUpper->setIconSize(sizeUpper);
    ui->btnDelete->setIconSize(sizeDelete);
    ui->btnDelete2->setIconSize(sizeDelete);
}

void QExtInput::setSpacing(const int &iSpacing)
{
    ui->widgetLetter1->layout()->setSpacing(iSpacing);
    ui->widgetLetter2->layout()->setSpacing(iSpacing);
    ui->widgetLetter3->layout()->setSpacing(iSpacing);
    ui->widgetNumber1->layout()->setSpacing(iSpacing);
    ui->widgetNumber2->layout()->setSpacing(iSpacing);
    ui->widgetNumber3->layout()->setSpacing(iSpacing);
}

void QExtInput::setTopHeight(const int &iTopHeight)
{
    ui->widgetTop->setFixedHeight(iTopHeight);
}

void QExtInput::setOnlyControl(const bool &bOnlyControl)
{
    dd_ptr->m_bOnlyControl = bOnlyControl;
}

void QExtInput::setColumnCount(const int &iColumnCount)
{
    dd_ptr->m_iColumnCount = iColumnCount;
}

void QExtInput::setMaxCount(const int &iMaxCount)
{
    dd_ptr->m_iMaxCount = iMaxCount;
}

void QExtInput::setDbPath(const QString &dbPath)
{
    dd_ptr->m_strDataBasePath = dbPath;
}

void QExtInput::setPopUpType(const QExtInput::PopUpTypes &eType)
{
    dd_ptr->m_ePopUpType = eType;
}

void QExtInput::setInputType(const InputTypes &eInputType)
{
    //Each mode change clears out the original characters
    dd_ptr->clearChinese();
    ui->labPY->clear();
    ui->scrollAreaCn->horizontalScrollBar()->setValue(0);
    ui->scrollAreaMore->verticalScrollBar()->setValue(0);

    dd_ptr->m_eInputType = eInputType;
    if (Input_Number == eInputType) {
        ui->widgetLetter->setVisible(false);
        ui->widgetNumber->setVisible(true);
        ui->widgetChinese->setVisible(false);
    } else if (Input_English == eInputType) {
        ui->widgetLetter->setVisible(true);
        ui->widgetNumber->setVisible(false);
        ui->widgetChinese->setVisible(false);
        ui->labType->setText(QString("<font color='%1'>中/</font><font color='%2' size='4'>英</font>")
                             .arg(dd_ptr->m_strMainTextColor).arg(dd_ptr->m_strButtonHoveColor));
    } else if (Input_Chinese == eInputType) {
        ui->widgetLetter->setVisible(true);
        ui->widgetNumber->setVisible(false);
        ui->widgetChinese->setVisible(false);
        ui->labType->setText(QString("<font color='%2' size='4'>中</font><font color='%1'>/英</font>")
                             .arg(dd_ptr->m_strMainTextColor).arg(dd_ptr->m_strButtonHoveColor));
    }
}

void QExtInput::setUpper(const bool &bIsUpper)
{
    QList<QPushButton *> listButtons = ui->widgetLetter->findChildren<QPushButton *>();
    foreach (QPushButton *pButton, listButtons) {
        QString strText = bIsUpper ? pButton->text().toUpper() : pButton->text().toLower();
        pButton->setText(strText);
    }

    //Change the icon
    ui->btnUpper->setIcon(QIcon(QString(":/QExtWidgets/image/btn_%1_%2.png").arg(bIsUpper ? "daxie" : "xiaoxie").arg(dd_ptr->m_strIconType)));
}

void QExtInput::setNumber(const bool &bIsNumber)
{
    //You can change special symbols
    QStringList listChars;
    if (bIsNumber) {
        listChars << "【" << "】" << "{" << "}" << "#" << "%" << "^" << "*" << "+" << "=";
        listChars << "_" << "—" << "\\" << "|" << "~" << "《" << "》" << "$" << "&&" << "*_*";
        listChars << "…" << "," << ":" << ";" << "<" << ">";
    } else {
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

    ui->btnNumber2->setText(QString("%1").arg(dd_ptr->m_bIsNumber ? "123" : "#+="));
}

void QExtInput::setStyleType(const StyleTypes &eStyle)
{
    dd_ptr->m_eStyleType = eStyle;
    dd_ptr->m_strIconType = "white";
    if (Style_Black == eStyle) {
        setColor("#191919", "#F3F3F3", "#313131", "#24B1DF", "#F3F3F3", "#F95717", "#F3F3F3");
    } else if (Style_Blue == eStyle) {
        setColor("#377FC9", "#F3F3F3", "#4189D3", "#386487", "#F3F3F3", "#386487", "#F3F3F3");
    } else if (Style_Gray == eStyle) {
        setColor("#989898", "#FFFFFF", "#A2A2A2", "#333333", "#F3F3F3", "#2E2E2E", "#F3F3F3");
    } else if (Style_Brown == eStyle) {
        setColor("#667481", "#F3F3F3", "#566373", "#4189D3", "#F3F3F3", "#4189D3", "#F3F3F3");
    } else if (Style_Silvery == eStyle) {
        setColor("#868690", "#000002", "#C3C2C7", "#F0F0F0", "#000002", "#F0F0F0", "#000002");
        dd_ptr->m_strIconType = "black";
    }

    ui->labMore->setPixmap(QString(":/QExtWidgets/image/btn_%1_%2.png").arg("more").arg(dd_ptr->m_strIconType));
    ui->btnDelete->setIcon(QIcon(QString(":/QExtWidgets/image/btn_%1_%2.png").arg("delete").arg(dd_ptr->m_strIconType)));
    ui->btnDelete2->setIcon(QIcon(QString(":/QExtWidgets/image/btn_%1_%2.png").arg("delete").arg(dd_ptr->m_strIconType)));
    ui->btnUpper->setIcon(QIcon(QString(":/QExtWidgets/image/btn_%1_%2.png").arg(dd_ptr->m_bIsUpper ? "daxie" : "xiaoxie").arg(dd_ptr->m_strIconType)));
}

void QExtInput::setColor(const QString &mainBkgColor, const QString &mainTextColor,
                        const QString &btnBkgColor, const QString &btnHoveColor,
                        const QString &btnHoveTextColor, const QString &labHoveColor,
                        const QString &labHoveTextColor)
{
    dd_ptr->m_strMainTextColor = mainTextColor;
    dd_ptr->m_strButtonHoveColor = btnHoveColor;

    QStringList listStrQss;
    listStrQss.append(QString("QScrollArea{border:none;background:rgba(255,255,255,0);}QWidget#widgetCn,QWidget#widgetMore{background:rgba(0,0,0,0);}"));
    listStrQss.append(QString("QWidget#widgetTop,QWidget#widgetLetter,QWidget#widgetNumber,QWidget#widgetChinese{background-color:%1;}").arg(mainBkgColor));
    listStrQss.append(QString("#labType,#labType2,QPushButton{border-width:0px;border-radius:3px;color:%1;}").arg(mainTextColor));
    listStrQss.append(QString("#labType,#labType2,QPushButton{padding:0px;background-color:%1;}").arg(btnBkgColor));
    //If it is only a touch screen, please use the following sentence
    //qss.append(QString("QPushButton:pressed{background-color:%1;color:%2;}").arg(btnHoveColor).arg(btnHoveTextColor));
    listStrQss.append(QString("QPushButton:pressed,QPushButton:hover{background-color:%1;color:%2;}").arg(btnHoveColor).arg(btnHoveTextColor));
    listStrQss.append(QString("QLabel{padding:0px 5px 0px 5px;border-width:0px;border-radius:3px;color:%1;background:none;}").arg(mainTextColor));
    listStrQss.append(QString("QLabel:pressed,QLabel:hover{background-color:%1;color:%2;}").arg(labHoveColor).arg(labHoveTextColor));
    listStrQss.append(QString("QLabel:disabled{background:none;}"));
    this->setStyleSheet(listStrQss.join(""));

    ui->labType->setText(QString("<font color='%1'>中/</font><font color='%2' size='4'>英</font>").arg(mainTextColor).arg(btnHoveColor));
    ui->labType2->setText(QString("<font color='%2' size='4'>中</font><font color='%1'>/英</font>").arg(mainTextColor).arg(btnHoveColor));
    qApp->processEvents();
}

#include <moc_qextInput.cpp>
