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

#ifndef _QEXTINPUT_H
#define _QEXTINPUT_H

#include <qextWidgetGlobal.h>
#include <qextPinyin.h>

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui
{
    class QExtInput;
}

class QExtInputPrivate;
class QEXT_WIDGETS_API QExtInput : public QWidget
{
    Q_OBJECT

public:
    enum PopUpTypes
    {
        PopUp_Center = 0,       //0-The form is displayed in the center
        PopUp_BottomCenter,     //1-The fill is shown horizontally in the middle at the bottom
        PopUp_FocusHCenter,     //2-Displayed horizontally in the middle of the corresponding input box
        PopUp_Control           //3-Displays near the location of the corresponding input box
    };

    enum InputTypes
    {
        Input_English = 0,      //0-English mode
        Input_Chinese,          //1-The Chinese model
        Input_Number            //2-Numeric special character pattern
    };

    enum StyleTypes
    {
        Style_Black = 0,
        Style_Blue,
        Style_Gray,
        Style_Brown,
        Style_Silvery
    };

public:
    static QExtInput *Instance();
    ~QExtInput();

public Q_SLOTS:
    //Sets the font name and size, including the font size of the button and the font size of the Chinese character section
    void setFontInfo(const QString &fontName, const int &iBtnFontSize, const int &iLabFontSize);
    //Set the icon size
    void setIconSize(const int &iIconWidth, const int &iIconHeight);
    //Set the space between the buttons
    void setSpacing(const int &iSpacing);
    //Set the height of the top Chinese character area
    void setTopHeight(const int &iTopHeight);

    //Settings are used only as controls
    void setOnlyControl(const bool &bOnlyControl);
    //Sets the number of Columns in the Chinese character panel
    void setColumnCount(const int &iColumnCount);
    //Set the maximum number of Chinese character tags
    void setMaxCount(const int &iMaxCount);

    //Sets the library path
    void setDbPath(const QString &dbPath);
    //Change letter case
    void setUpper(const bool &bIsUpper);
    //Changing numeric characters
    void setNumber(const bool &bIsNumber);
    /*Set the position where the input method pops up, and control-- displays directly
     *  below the corresponding input box -- bottom-- fill -- displays in the bottom
     *  center-- form center*/
    void setPopUpType(const PopUpTypes &eType);
    //Sets the current input method type
    void setInputType(const InputTypes &eInputType);
    //Set the input method color style
    void setStyleType(const StyleTypes &eStyle);
    //Change the input method panel style
    void setColor(const QString &mainBkgColor, const QString &mainTextColor,
                  const QString &btnBkgColor, const QString &btnHoveColor,
                  const QString &btnHoveTextColor, const QString &labHoveColor,
                  const QString &labHoveTextColor);

Q_SIGNALS:
    void receiveValue(const QString &value);

protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    explicit QExtInput(QWidget *parent = 0);

private:
    Ui::QExtInput *ui;
    QEXT_DISABLE_COPY_MOVE(QExtInput)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtInput)
    static QExtInput *sm_pInstance;
    QExtInputPrivate *dd_ptr;
    Q_PRIVATE_SLOT(d_func(), void init())
    Q_PRIVATE_SLOT(d_func(), void buttonClicked())
    Q_PRIVATE_SLOT(d_func(), void focusChanged(QWidget *oldWidget, QWidget *nowWidget))
    Q_PRIVATE_SLOT(d_func(), void showPanel())
    Q_PRIVATE_SLOT(d_func(), void hidePanel())
};

#endif // _QEXTINPUT_H
