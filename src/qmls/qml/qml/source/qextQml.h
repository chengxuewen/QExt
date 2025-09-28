/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024 ChengXueWen.
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

#ifndef _QEXTQML_H
#define _QEXTQML_H

#include <qextQmlGlobal.h>
#include <qextQmlSingleton.h>

#include <QObject>
#include <QQmlEngine>
#include <QQuickWindow>
#include <QScopedPointer>

class QExtQmlFontIconInfo : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString family READ family WRITE setFamily NOTIFY familyChanged)
public:
    QExtQmlFontIconInfo() {}
    QExtQmlFontIconInfo(const QString &family, const QString &text) : mText(text), mFamily(family) {}
    QExtQmlFontIconInfo(const QExtQmlFontIconInfo &other) : mText(other.mText), mFamily(other.mFamily) {}

    QExtQmlFontIconInfo &operator =(const QExtQmlFontIconInfo &other)
    {
        if (this != &other)
        {
            mText = other.mText;
            mFamily = other.mFamily;
        }
        return *this;
    }

    bool operator==(const QExtQmlFontIconInfo &other) const
    {
        if (this != &other)
        {
            return mText == other.mText && mFamily == other.mFamily;
        }
        return true;
    }
    bool operator!=(const QExtQmlFontIconInfo &other) const
    {
        return !(*this == other);
    }

    QString text() const { return mText; }
    void setText(const QString &text)
    {
        if (text != mText)
        {
            mText = text;
            emit this->textChanged(text);
        }
    }

    QString family() const { return mFamily; }
    void setFamily(const QString &family)
    {
        if (family != mFamily)
        {
            mFamily = family;
            emit this->familyChanged(family);
        }
    }

Q_SIGNALS:
    void textChanged(const QString &text);
    void familyChanged(const QString &family);

private:
    QString mText;
    QString mFamily;
};

class QExtQmlWorld;
class QExtQmlPrivate;
class QEXT_QML_API QExtQml : public QExtQmlSingleton<QExtQml>
{
    Q_OBJECT
    QEXT_DECLARE_QML_SINGLETON(QExtQml)
public:
    enum StateType
    {
        State_None = 0,
        State_Normal,
        State_Hovered,
        State_Pressed,
        State_Checked,
        State_Unchecked,
        State_PartiallyChecked,
    };
    Q_ENUM(StateType)

    enum PositionType
    {
        Position_Left = 0,
        Position_Right,
        Position_Top,
        Position_Bottom,
        Position_Center
    };
    Q_ENUM(PositionType)

    enum IconDisplayType
    {
        IconDisplay_TextOnly = 0,
        IconDisplay_IconOnly,
        IconDisplay_Left,
        IconDisplay_Right,
        IconDisplay_Top,
        IconDisplay_Bottom,
    };
    Q_ENUM(IconDisplayType)

    enum IconType
    {
        Icon_Awesome = 0,
        Icon_SVG
    };
    Q_ENUM(IconType)

    //h1=32px h2=24px h3=19px h4=16px h5=14px h6=12px
    enum class PixelSizeType
    {
        PH1 = 32,
        PH2 = 24,
        PH3 = 19,
        PH4 = 16,
        PH5 = 14,
        PH6 = 12,
        PH7 = 10,
        PH8 = 8
    };
    Q_ENUM(PixelSizeType)

    enum DragDirectionType
    {
        DragDirection_Left = 0,
        DragDirection_LeftTop,
        DragDirection_LeftBottom,
        DragDirection_Right,
        DragDirection_RightTop,
        DragDirection_RightBottom,
        DragDirection_Top,
        DragDirection_Bottom,
        DragDirection_Center
    };
    Q_ENUM(DragDirectionType)

    Q_INVOKABLE QString stateToString(int state) const;
    Q_INVOKABLE int stateToEnum(const QString &state) const;

    Q_INVOKABLE bool isFontIconUrl(const QString &url);
    Q_INVOKABLE QExtQmlFontIconInfo fontIconInfoFromUrl(const QString &url);
    Q_INVOKABLE bool parseFontIconInfoFromUrl(const QString &url, QExtQmlFontIconInfo *fontIconInfo);
    Q_INVOKABLE QString fontIconUrl(const QString &family, const QString &key);

    Q_INVOKABLE QString version() const override;
    void registerTypes(const char *url = nullptr) override;
    void initializeEngine(QQmlEngine *engine, const char *uri) override;

protected:
    QExtQml();
    ~QExtQml() override;

    QScopedPointer<QExtQmlPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQml)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQml)
};

#endif // _QEXTQML_H
