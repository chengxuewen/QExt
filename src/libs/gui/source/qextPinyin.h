/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016~Present ChengXueWen. Contact: 1398831004@qq.com
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

#ifndef _QEXTPINYIN_H
#define _QEXTPINYIN_H

#include <qextGuiGlobal.h>

#include <QObject>

class QExtPinyinPrivate;
class QEXT_GUI_API QExtPinyin : public QObject
{
    Q_OBJECT
public:
    explicit QExtPinyin(QObject *parent = 0);
    ~QExtPinyin();

public slots:
    //Open the input method core
    bool open(const QString &strDBPath);
    //Close the input method core
    void close();
    //Cancel the input
    void cancel();
    //Clear the cache
    void flush();
    //Reset the search
    void reset();

    //Find the Chinese characters corresponding to pinyin, return the number
    int select(const QString &strPinyin);
    //Gets the character for the specified index
    QString getChinese(const int &iIndex);

    //Delete the Chinese characters
    int deleteSelect(const int &iPos);
    //Current lookup position
    int getPosition();

protected:
    QExtPinyinPrivate *dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtPinyin)
    Q_DISABLE_COPY(QExtPinyin)
};

#endif // _QEXTPINYIN_H
