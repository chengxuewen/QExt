/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2025 ChengXueWen.
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

#ifndef _QEXTSVGCOLORIMAGEPROVIDER_H
#define _QEXTSVGCOLORIMAGEPROVIDER_H

#include <qextQuickControlsGlobal.h>

#include <QCache>
#include <QMutex>
#include <QQuickImageProvider>

class QColor;

// image://qextsvg/<wBucket>/<hBucket>/<dpr档 x100>/<AARRGGBB>/<percent-encoded source>
class QExtSvgColorImageProvider : public QQuickImageProvider
{
public:
    static const QString kId;                      // "qextsvg"（QLatin1String 自 Qt 6.4 起弃用）
    enum { kCacheBytes = 8 << 20 };                // QCache 代价按 QImage::sizeInBytes() 计（byteCount() Qt6 已删）

    QExtSvgColorImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) QEXT_OVERRIDE;

    // 供 C++/单测使用；QML 侧当前用 QExtQuickSvgIcon.qml 的等价 JS 拼装（量化表双实现，单测对拍锁定）
    static QString urlFor(const QString &source, const QColor &color,
                          qreal width, qreal height, qreal devicePixelRatio);

    static bool parseId(const QString &id, QString *source, QColor *color,
                        qreal *width, qreal *height, qreal *dpr);

private:
    QCache<QString, QImage> mCache;                // id 即键（已含全部影响成像的参数）
    QMutex mMutex;                                 // 异步路径下 requestImage 可能来自线程池
};

#endif // _QEXTSVGCOLORIMAGEPROVIDER_H
