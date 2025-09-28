/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#include <qextQmlThemePalette.h>

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

#define QEXT_QUICK_PALETTE_COLOR_RANDOM(a, b) (rand() % (b - a + 1) + a)

class QExtQmlThemePalettePrivate
{
    Q_DISABLE_COPY(QExtQmlThemePalettePrivate)
    Q_DECLARE_PUBLIC(QExtQmlThemePalette)
public:
    explicit QExtQmlThemePalettePrivate(QExtQmlThemePalette *q);
    virtual ~QExtQmlThemePalettePrivate();

    QExtQmlThemePalette * const q_ptr;

    QVector<QVector<QColor>> mMaterialColorVector;
    QVector<QColor> mBorderColors;
    QVector<QColor> mBrandColors;
    QVector<QColor> mTextColors;
};

QExtQmlThemePalettePrivate::QExtQmlThemePalettePrivate(QExtQmlThemePalette *q)
    : q_ptr(q)
{
    mMaterialColorVector.resize(QExtQmlThemePalette::ColorEnumCount);
    for (int i = 0; i < QExtQmlThemePalette::ColorEnumCount; ++i)
    {
        mMaterialColorVector[i].resize(QExtQmlThemePalette::DepthEnumCount);
    }
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth50] = QColor(255, 235, 238, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth100] = QColor(255, 205, 210, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth200] = QColor(239, 154, 154, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth300] = QColor(229, 115, 115, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth400] = QColor(239, 83, 80, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth500] = QColor(244, 67, 54, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth600] = QColor(229, 57, 53, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth700] = QColor(211, 47, 47, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth800] = QColor(198, 40, 40, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::Depth900] = QColor(183, 28, 28, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::DepthA100] = QColor(255, 138, 128, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::DepthA200] = QColor(255, 82, 82, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::DepthA400] = QColor(255, 23, 68, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorRed][QExtQmlThemePalette::DepthA700] = QColor(213, 0, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth50] = QColor(252, 228, 236, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth100] = QColor(248, 187, 208, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth200] = QColor(244, 143, 177, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth300] = QColor(240, 98, 146, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth400] = QColor(236, 64, 122, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth500] = QColor(233, 30, 99, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth600] = QColor(216, 27, 96, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth700] = QColor(194, 24, 91, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth800] = QColor(173, 20, 87, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::Depth900] = QColor(136, 14, 79, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::DepthA100] = QColor(255, 128, 171, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::DepthA200] = QColor(255, 64, 129, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::DepthA400] = QColor(245, 0, 87, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPink][QExtQmlThemePalette::DepthA700] = QColor(197, 17, 98, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth50] = QColor(243, 229, 245, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth100] = QColor(225, 190, 231, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth200] = QColor(206, 147, 216, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth300] = QColor(186, 104, 200, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth400] = QColor(171, 71, 188, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth500] = QColor(156, 39, 176, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth600] = QColor(142, 36, 170, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth700] = QColor(123, 31, 162, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth800] = QColor(106, 27, 154, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::Depth900] = QColor(74, 20, 140, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::DepthA100] = QColor(234, 128, 252, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::DepthA200] = QColor(224, 64, 251, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::DepthA400] = QColor(213, 0, 249, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorPurple][QExtQmlThemePalette::DepthA700] = QColor(170, 0, 255, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth50] = QColor(237, 231, 246, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth100] = QColor(209, 196, 233, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth200] = QColor(179, 157, 219, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth300] = QColor(149, 117, 205, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth400] = QColor(126, 87, 194, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth500] = QColor(103, 58, 183, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth600] = QColor(94, 53, 177, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth700] = QColor(81, 45, 168, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth800] = QColor(69, 39, 160, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::Depth900] = QColor(49, 27, 146, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::DepthA100] = QColor(179, 136, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::DepthA200] = QColor(124, 77, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::DepthA400] = QColor(101, 31, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepPurple][QExtQmlThemePalette::DepthA700] = QColor(98, 0, 234, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth50] = QColor(232, 234, 246, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth100] = QColor(197, 202, 233, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth200] = QColor(159, 168, 218, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth300] = QColor(121, 134, 203, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth400] = QColor(92, 107, 192, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth500] = QColor(63, 81, 181, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth600] = QColor(57, 73, 171, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth700] = QColor(48, 63, 159, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth800] = QColor(40, 53, 147, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::Depth900] = QColor(26, 35, 126, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::DepthA100] = QColor(140, 158, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::DepthA200] = QColor(83, 109, 254, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::DepthA400] = QColor(61, 90, 254, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorIndigo][QExtQmlThemePalette::DepthA700] = QColor(48, 79, 254, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth50] = QColor(227, 242, 253, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth100] = QColor(187, 222, 251, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth200] = QColor(144, 202, 249, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth300] = QColor(100, 181, 246, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth400] = QColor(66, 165, 245, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth500] = QColor(33, 150, 243, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth600] = QColor(30, 136, 229, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth700] = QColor(25, 118, 210, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth800] = QColor(21, 101, 192, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::Depth900] = QColor(13, 71, 161, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::DepthA100] = QColor(130, 177, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::DepthA200] = QColor(68, 138, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::DepthA400] = QColor(41, 121, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlue][QExtQmlThemePalette::DepthA700] = QColor(41, 98, 255, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth50] = QColor(225, 245, 254, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth100] = QColor(179, 229, 252, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth200] = QColor(129, 212, 250, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth300] = QColor(79, 195, 247, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth400] = QColor(41, 182, 246, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth500] = QColor(3, 169, 244, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth600] = QColor(3, 155, 229, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth700] = QColor(2, 136, 209, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth800] = QColor(2, 119, 189, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::Depth900] = QColor(1, 87, 155, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::DepthA100] = QColor(128, 216, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::DepthA200] = QColor(64, 196, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::DepthA400] = QColor(0, 176, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightBlue][QExtQmlThemePalette::DepthA700] = QColor(0, 145, 234, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth50] = QColor(224, 247, 250, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth100] = QColor(178, 235, 242, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth200] = QColor(128, 222, 234, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth300] = QColor(77, 208, 225, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth400] = QColor(38, 198, 218, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth500] = QColor(0, 188, 212, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth600] = QColor(0, 172, 193, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth700] = QColor(0, 151, 167, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth800] = QColor(0, 131, 143, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::Depth900] = QColor(0, 96, 100, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::DepthA100] = QColor(132, 255, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::DepthA200] = QColor(24, 255, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::DepthA400] = QColor(0, 229, 255, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorCyan][QExtQmlThemePalette::DepthA700] = QColor(0, 184, 212, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth50] = QColor(224, 242, 241, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth100] = QColor(178, 223, 219, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth200] = QColor(128, 203, 196, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth300] = QColor(77, 182, 172, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth400] = QColor(38, 166, 154, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth500] = QColor(0, 150, 136, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth600] = QColor(0, 137, 123, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth700] = QColor(0, 121, 107, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth800] = QColor(0, 105, 92, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::Depth900] = QColor(0, 77, 64, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::DepthA100] = QColor(167, 255, 235, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::DepthA200] = QColor(100, 255, 218, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::DepthA400] = QColor(29, 233, 182, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorTeal][QExtQmlThemePalette::DepthA700] = QColor(0, 191, 165, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth50] = QColor(232, 245, 233, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth100] = QColor(200, 230, 201, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth200] = QColor(165, 214, 167, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth300] = QColor(129, 199, 132, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth400] = QColor(102, 187, 106, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth500] = QColor(76, 175, 80, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth600] = QColor(67, 160, 71, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth700] = QColor(56, 142, 60, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth800] = QColor(46, 125, 50, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::Depth900] = QColor(27, 94, 32, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::DepthA100] = QColor(185, 246, 202, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::DepthA200] = QColor(105, 240, 174, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::DepthA400] = QColor(0, 230, 118, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGreen][QExtQmlThemePalette::DepthA700] = QColor(0, 200, 83, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth50] = QColor(241, 248, 233, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth100] = QColor(220, 237, 200, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth200] = QColor(197, 225, 165, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth300] = QColor(174, 213, 129, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth400] = QColor(156, 204, 101, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth500] = QColor(139, 195, 74, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth600] = QColor(124, 179, 66, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth700] = QColor(104, 159, 56, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth800] = QColor(85, 139, 47, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::Depth900] = QColor(51, 105, 30, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::DepthA100] = QColor(204, 255, 144, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::DepthA200] = QColor(178, 255, 89, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::DepthA400] = QColor(118, 255, 3, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLightGreen][QExtQmlThemePalette::DepthA700] = QColor(100, 221, 23, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth50] = QColor(249, 251, 231, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth100] = QColor(240, 244, 195, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth200] = QColor(230, 238, 156, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth300] = QColor(220, 231, 117, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth400] = QColor(212, 225, 87, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth500] = QColor(205, 220, 57, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth600] = QColor(192, 202, 51, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth700] = QColor(175, 180, 43, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth800] = QColor(158, 157, 36, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::Depth900] = QColor(130, 119, 23, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::DepthA100] = QColor(244, 255, 129, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::DepthA200] = QColor(238, 255, 65, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::DepthA400] = QColor(198, 255, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorLime][QExtQmlThemePalette::DepthA700] = QColor(174, 234, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth50] = QColor(255, 253, 231, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth100] = QColor(255, 249, 196, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth200] = QColor(255, 245, 157, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth300] = QColor(255, 241, 118, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth400] = QColor(255, 238, 88, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth500] = QColor(255, 235, 59, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth600] = QColor(253, 216, 53, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth700] = QColor(251, 192, 45, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth800] = QColor(249, 168, 37, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::Depth900] = QColor(245, 127, 23, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::DepthA100] = QColor(255, 255, 141, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::DepthA200] = QColor(255, 255, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::DepthA400] = QColor(255, 234, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorYellow][QExtQmlThemePalette::DepthA700] = QColor(255, 214, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth50] = QColor(255, 248, 225, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth100] = QColor(255, 236, 179, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth200] = QColor(255, 224, 130, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth300] = QColor(255, 213, 79, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth400] = QColor(255, 202, 40, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth500] = QColor(255, 193, 7, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth600] = QColor(255, 179, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth700] = QColor(255, 160, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth800] = QColor(255, 143, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::Depth900] = QColor(255, 111, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::DepthA100] = QColor(255, 229, 127, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::DepthA200] = QColor(255, 215, 64, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::DepthA400] = QColor(255, 196, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorAmber][QExtQmlThemePalette::DepthA700] = QColor(255, 171, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth50] = QColor(255, 243, 224, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth100] = QColor(255, 224, 178, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth200] = QColor(255, 204, 128, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth300] = QColor(255, 183, 77, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth400] = QColor(255, 167, 38, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth500] = QColor(255, 152, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth600] = QColor(251, 140, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth700] = QColor(245, 124, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth800] = QColor(239, 108, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::Depth900] = QColor(230, 81, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::DepthA100] = QColor(255, 209, 128, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::DepthA200] = QColor(255, 171, 64, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::DepthA400] = QColor(255, 145, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorOrange][QExtQmlThemePalette::DepthA700] = QColor(255, 109, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth50] = QColor(251, 233, 231, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth100] = QColor(255, 204, 188, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth200] = QColor(255, 171, 145, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth300] = QColor(255, 138, 101, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth400] = QColor(255, 112, 67, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth500] = QColor(255, 87, 34, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth600] = QColor(244, 81, 30, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth700] = QColor(230, 74, 25, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth800] = QColor(216, 67, 21, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::Depth900] = QColor(191, 54, 12, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::DepthA100] = QColor(255, 158, 128, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::DepthA200] = QColor(255, 110, 64, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::DepthA400] = QColor(255, 61, 0, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorDeepOrange][QExtQmlThemePalette::DepthA700] = QColor(221, 44, 0, 100);

    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth50] = QColor(239, 235, 233, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth100] = QColor(215, 204, 200, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth200] = QColor(188, 170, 164, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth300] = QColor(161, 136, 127, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth400] = QColor(141, 110, 99, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth500] = QColor(121, 85, 72, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth600] = QColor(109, 76, 65, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth700] = QColor(93, 64, 55, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth800] = QColor(78, 52, 46, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::Depth900] = QColor(62, 39, 35, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::DepthA100] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::DepthA200] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::DepthA400] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBrown][QExtQmlThemePalette::DepthA700] = QColor();

    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth50] = QColor(250, 250, 250, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth100] = QColor(245, 245, 245, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth200] = QColor(238, 238, 238, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth300] = QColor(224, 224, 224, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth400] = QColor(189, 189, 189, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth500] = QColor(158, 158, 158, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth600] = QColor(117, 117, 117, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth700] = QColor(97, 97, 97, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth800] = QColor(66, 66, 66, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::Depth900] = QColor(33, 33, 33, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::DepthA100] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::DepthA200] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::DepthA400] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorGrey][QExtQmlThemePalette::DepthA700] = QColor();

    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth50] = QColor(236, 239, 241, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth100] = QColor(207, 216, 220, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth200] = QColor(176, 190, 197, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth300] = QColor(144, 164, 174, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth400] = QColor(120, 144, 156, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth500] = QColor(96, 125, 139, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth600] = QColor(84, 110, 122, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth700] = QColor(69, 90, 100, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth800] = QColor(55, 71, 79, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::Depth900] = QColor(38, 50, 56, 100);
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::DepthA100] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::DepthA200] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::DepthA400] = QColor();
    mMaterialColorVector[QExtQmlThemePalette::ColorBlueGrey][QExtQmlThemePalette::DepthA700] = QColor();

    mBrandColors.resize(QExtQmlThemePalette::BrandEnumCount);
    mBrandColors[QExtQmlThemePalette::BrandPrimary] = QColor(2, 123, 227, 100);
    mBrandColors[QExtQmlThemePalette::BrandSecondary] = QColor(38, 166, 154, 100);
    mBrandColors[QExtQmlThemePalette::BrandAccent] = QColor(156, 39, 176, 100);
    mBrandColors[QExtQmlThemePalette::BrandDark] = QColor(29, 29, 29, 100);
    mBrandColors[QExtQmlThemePalette::BrandPositive] = QColor(33, 186, 69, 100);
    mBrandColors[QExtQmlThemePalette::BrandNegative] = QColor(193, 0, 21, 100);
    mBrandColors[QExtQmlThemePalette::BrandInfo] = QColor(144, 147, 153, 100);
    mBrandColors[QExtQmlThemePalette::BrandSuccess] = QColor(103, 194, 58, 100);
    mBrandColors[QExtQmlThemePalette::BrandWarning] = QColor(230, 162, 60, 100);
    mBrandColors[QExtQmlThemePalette::BrandDanger] = QColor(245, 108, 108, 100);

    mTextColors.resize(QExtQmlThemePalette::TextEnumCount);
    mTextColors[QExtQmlThemePalette::TextPrimary] = QColor(48, 49, 51, 100);
    mTextColors[QExtQmlThemePalette::TextNormal] = QColor(96, 98, 102, 100);
    mTextColors[QExtQmlThemePalette::TextSecondary] = QColor(144, 147, 153, 100);
    mTextColors[QExtQmlThemePalette::TextPlaceholder] = QColor(192, 196, 204, 100);

    mBorderColors.resize(QExtQmlThemePalette::BorderLevelEnumCount);
    mBorderColors[QExtQmlThemePalette::BorderLevel1] = QColor(220, 223, 230, 100);
    mBorderColors[QExtQmlThemePalette::BorderLevel2] = QColor(228, 231, 237, 100);
    mBorderColors[QExtQmlThemePalette::BorderLevel3] = QColor(235, 238, 245, 100);
    mBorderColors[QExtQmlThemePalette::BorderLevel4] = QColor(242, 246, 252, 100);
}

QExtQmlThemePalettePrivate::~QExtQmlThemePalettePrivate()
{
}

QExtQmlThemePalette::QExtQmlThemePalette(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlThemePalettePrivate(this))
{
    qRegisterMetaType<BrandEnum>("BrandEnum");
    qRegisterMetaType<TextEnum>("TextEnum");
    qRegisterMetaType<BorderLevelEnum>("BorderLevelEnum");
    qRegisterMetaType<ColorEnum>("ColorEnum");
    qRegisterMetaType<DepthEnum>("DepthEnum");
}

QExtQmlThemePalette::~QExtQmlThemePalette()
{
}

QColor QExtQmlThemePalette::randomColor() const
{
    return QColor(QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255)).name();
}

QColor QExtQmlThemePalette::brandColor(int brand) const
{
    if (brand < 0 || brand >= QExtQmlThemePalette::BrandEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::brandColor():unknown brand type";
        return "";
    }
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(brand).name();
}

QString QExtQmlThemePalette::brandPrimaryColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandPrimary).name();
}

QString QExtQmlThemePalette::brandSecondaryColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandSecondary).name();
}

QString QExtQmlThemePalette::brandAccentColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandAccent).name();
}

QString QExtQmlThemePalette::brandDarkColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandDark).name();
}

QString QExtQmlThemePalette::brandPositiveColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandPositive).name();
}

QString QExtQmlThemePalette::brandNegativeColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandNegative).name();
}

QString QExtQmlThemePalette::brandInfoColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandInfo).name();
}

QString QExtQmlThemePalette::brandSuccessColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandSuccess).name();
}

QString QExtQmlThemePalette::brandWarningColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandWarning).name();
}

QString QExtQmlThemePalette::brandDangerColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBrandColors.at(QExtQmlThemePalette::BrandDanger).name();
}

QColor QExtQmlThemePalette::textColor(int text) const
{
    if (text < 0 || text >= QExtQmlThemePalette::TextEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::textColor():unknown textType";
        return "";
    }
    Q_D(const QExtQmlThemePalette);
    return d->mTextColors.at(text).name();
}

QString QExtQmlThemePalette::textPrimaryColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mTextColors.at(QExtQmlThemePalette::TextPrimary).name();
}

QString QExtQmlThemePalette::textNormalColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mTextColors.at(QExtQmlThemePalette::TextNormal).name();
}

QString QExtQmlThemePalette::textSecondaryColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mTextColors.at(QExtQmlThemePalette::TextSecondary).name();
}

QString QExtQmlThemePalette::textPlaceholderColor() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mTextColors.at(QExtQmlThemePalette::TextPlaceholder).name();
}

QColor QExtQmlThemePalette::borderColor(int level) const
{
    if (level < 0 || level >= QExtQmlThemePalette::BorderLevelEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::textColor():unknown borderLevel";
        return "";
    }
    Q_D(const QExtQmlThemePalette);
    return d->mBorderColors.at(level).name();
}

QString QExtQmlThemePalette::borderLevel1Color() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBorderColors.at(QExtQmlThemePalette::BorderLevel1).name();
}

QString QExtQmlThemePalette::borderLevel2Color() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBorderColors.at(QExtQmlThemePalette::BorderLevel2).name();
}

QString QExtQmlThemePalette::borderLevel3Color() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBorderColors.at(QExtQmlThemePalette::BorderLevel3).name();
}

QString QExtQmlThemePalette::borderLevel4Color() const
{
    Q_D(const QExtQmlThemePalette);
    return d->mBorderColors.at(QExtQmlThemePalette::BorderLevel4).name();
}

QColor QExtQmlThemePalette::materialColor(int color, int depth) const
{
    if (color < 0 || color >= QExtQmlThemePalette::ColorEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::color():unknown color type";
        return "";
    }
    if (depth < 0 || depth >= QExtQmlThemePalette::DepthEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::color():unknown depth type";
        return "";
    }
    Q_D(const QExtQmlThemePalette);
    return d->mMaterialColorVector.at(color).at(depth).name();
}

QString QExtQmlThemePalette::materialColorTypeName(int color)
{
    switch (color)
    {
    case ColorRed: return "Red";
    case ColorPink: return "Pink";
    case ColorPurple: return "Purple";
    case ColorDeepPurple: return "DeepPurple";
    case ColorIndigo: return "Indigo";
    case ColorBlue: return "Blue";
    case ColorLightBlue: return "LightBlue";
    case ColorCyan: return "Cyan";
    case ColorTeal: return "Teal";
    case ColorGreen: return "Green";
    case ColorLightGreen: return "LightGreen";
    case ColorLime: return "Lime";
    case ColorYellow: return "Yellow";
    case ColorAmber: return "Amber";
    case ColorOrange: return "Orange";
    case ColorDeepOrange: return "DeepOrange";
    case ColorBrown: return "Brown";
    case ColorGrey: return "Grey";
    case ColorBlueGrey: return "BlueGrey";
    default: break;
    }
    return QString("");
}

QString QExtQmlThemePalette::materialDepthTypeName(int depth)
{
    switch (depth)
    {
    case Depth50: return "50";
    case Depth100: return "100";
    case Depth200: return "200";
    case Depth300: return "300";
    case Depth400: return "400";
    case Depth500: return "500";
    case Depth600: return "600";
    case Depth700: return "700";
    case Depth800: return "800";
    case Depth900: return "900";
    case DepthA100: return "A100";
    case DepthA200: return "A200";
    case DepthA400: return "A400";
    case DepthA700: return "A700";
    default: break;
    }
    return QString("");
}

void QExtQmlThemePalette::setBorderColor(int level, const QColor &color)
{
    Q_D(QExtQmlThemePalette);
    if (level < 0 || level >= QExtQmlThemePalette::BorderLevelEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::setBorderColor():unknown level type";
        return;
    }
    if (color != d->mBorderColors[level])
    {
        d->mBorderColors[level] = color;
        emit this->borderColorChanged(level, color);
        switch (level)
        {
        case BorderLevel1:
            emit this->borderLevel1ColorChanged(color);
            break;
        case BorderLevel2:
            emit this->borderLevel2ColorChanged(color);
            break;
        case BorderLevel3:
            emit this->borderLevel3ColorChanged(color);
            break;
        case BorderLevel4:
            emit this->borderLevel4ColorChanged(color);
            break;
        default:
            break;
        }
    }
}

void QExtQmlThemePalette::setBrandColor(int brand, const QColor &color)
{
    Q_D(QExtQmlThemePalette);
    if (brand < 0 || brand >= QExtQmlThemePalette::BrandEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::setBrandColor():unknown brand type";
        return;
    }
    if (color != d->mBrandColors[brand])
    {
        d->mBrandColors[brand] = color;
        emit this->brandColorChanged(brand, color);
        switch (brand)
        {
        case BrandPrimary:
            emit this->brandPrimaryColorChanged(color);
            break;
        case BrandSecondary:
            emit this->brandSecondaryColorChanged(color);
            break;
        case BrandAccent:
            emit this->brandAccentColorChanged(color);
            break;
        case BrandDark:
            emit this->brandDarkColorChanged(color);
            break;
        case BrandPositive:
            emit this->brandPositiveColorChanged(color);
            break;
        case BrandNegative:
            emit this->brandNegativeColorChanged(color);
            break;
        case BrandInfo:
            emit this->brandInfoColorChanged(color);
            break;
        case BrandSuccess:
            emit this->brandSuccessColorChanged(color);
            break;
        case BrandWarning:
            emit this->brandWarningColorChanged(color);
            break;
        case BrandDanger:
            emit this->brandDangerColorChanged(color);
            break;
        default:
            break;
        }
    }
}

void QExtQmlThemePalette::setTextColor(int text, const QColor &color)
{
    Q_D(QExtQmlThemePalette);
    if (text < 0 || text >= QExtQmlThemePalette::TextEnumCount)
    {
        qCritical() << "QExtQmlThemePalette::setTextColor():unknown text type";
        return;
    }
    if (color != d->mTextColors[text])
    {
        d->mTextColors[text] = color;
        emit this->textColorChanged(text, color);
        switch (text)
        {
        case TextPrimary:
            emit this->textPrimaryColorChanged(color);
            break;
        case TextNormal:
            emit this->textNormalColorChanged(color);
            break;
        case TextSecondary:
            emit this->textSecondaryColorChanged(color);
            break;
        case TextPlaceholder:
            emit this->textPlaceholderColorChanged(color);
            break;
        default:
            break;
        }
    }
}
