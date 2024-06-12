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

#include <qextQuickPalette.h>

#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

#define QEXT_QUICK_PALETTE_COLOR_RANDOM(a, b) (rand() % (b - a + 1) + a)

class QExtQuickPalettePrivate
{
    Q_DISABLE_COPY(QExtQuickPalettePrivate)
    Q_DECLARE_PUBLIC(QExtQuickPalette)
public:
    explicit QExtQuickPalettePrivate(QExtQuickPalette *q);
    virtual ~QExtQuickPalettePrivate();

    QExtQuickPalette * const q_ptr;

    QVector<QVector<QColor>> m_materialColorVector;
    QVector<QColor> m_brandColorVector;
    QVector<QColor> m_textColorVector;
    QVector<QColor> m_borderColorVector;
};

QExtQuickPalettePrivate::QExtQuickPalettePrivate(QExtQuickPalette *q)
    : q_ptr(q)
{
    m_materialColorVector.resize(QExtQuickPalette::ColorTypeNum);
    for (int i = 0; i < QExtQuickPalette::ColorTypeNum; ++i) {
        m_materialColorVector[i].resize(QExtQuickPalette::DepthTypeNum);
    }
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_50] = QColor(255, 235, 238, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_100] = QColor(255, 205, 210, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_200] = QColor(239, 154, 154, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_300] = QColor(229, 115, 115, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_400] = QColor(239, 83, 80, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_500] = QColor(244, 67, 54, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_600] = QColor(229, 57, 53, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_700] = QColor(211, 47, 47, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_800] = QColor(198, 40, 40, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_900] = QColor(183, 28, 28, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_A100] = QColor(255, 138, 128, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_A200] = QColor(255, 82, 82, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_A400] = QColor(255, 23, 68, 100);
    m_materialColorVector[QExtQuickPalette::Color_Red][QExtQuickPalette::Depth_A700] = QColor(213, 0, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_50] = QColor(252, 228, 236, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_100] = QColor(248, 187, 208, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_200] = QColor(244, 143, 177, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_300] = QColor(240, 98, 146, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_400] = QColor(236, 64, 122, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_500] = QColor(233, 30, 99, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_600] = QColor(216, 27, 96, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_700] = QColor(194, 24, 91, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_800] = QColor(173, 20, 87, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_900] = QColor(136, 14, 79, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_A100] = QColor(255, 128, 171, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_A200] = QColor(255, 64, 129, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_A400] = QColor(245, 0, 87, 100);
    m_materialColorVector[QExtQuickPalette::Color_Pink][QExtQuickPalette::Depth_A700] = QColor(197, 17, 98, 100);

    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_50] = QColor(243, 229, 245, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_100] = QColor(225, 190, 231, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_200] = QColor(206, 147, 216, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_300] = QColor(186, 104, 200, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_400] = QColor(171, 71, 188, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_500] = QColor(156, 39, 176, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_600] = QColor(142, 36, 170, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_700] = QColor(123, 31, 162, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_800] = QColor(106, 27, 154, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_900] = QColor(74, 20, 140, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_A100] = QColor(234, 128, 252, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_A200] = QColor(224, 64, 251, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_A400] = QColor(213, 0, 249, 100);
    m_materialColorVector[QExtQuickPalette::Color_Purple][QExtQuickPalette::Depth_A700] = QColor(170, 0, 255, 100);

    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_50] = QColor(237, 231, 246, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_100] = QColor(209, 196, 233, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_200] = QColor(179, 157, 219, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_300] = QColor(149, 117, 205, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_400] = QColor(126, 87, 194, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_500] = QColor(103, 58, 183, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_600] = QColor(94, 53, 177, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_700] = QColor(81, 45, 168, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_800] = QColor(69, 39, 160, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_900] = QColor(49, 27, 146, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_A100] = QColor(179, 136, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_A200] = QColor(124, 77, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_A400] = QColor(101, 31, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepPurple][QExtQuickPalette::Depth_A700] = QColor(98, 0, 234, 100);

    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_50] = QColor(232, 234, 246, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_100] = QColor(197, 202, 233, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_200] = QColor(159, 168, 218, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_300] = QColor(121, 134, 203, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_400] = QColor(92, 107, 192, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_500] = QColor(63, 81, 181, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_600] = QColor(57, 73, 171, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_700] = QColor(48, 63, 159, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_800] = QColor(40, 53, 147, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_900] = QColor(26, 35, 126, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_A100] = QColor(140, 158, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_A200] = QColor(83, 109, 254, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_A400] = QColor(61, 90, 254, 100);
    m_materialColorVector[QExtQuickPalette::Color_Indigo][QExtQuickPalette::Depth_A700] = QColor(48, 79, 254, 100);

    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_50] = QColor(227, 242, 253, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_100] = QColor(187, 222, 251, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_200] = QColor(144, 202, 249, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_300] = QColor(100, 181, 246, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_400] = QColor(66, 165, 245, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_500] = QColor(33, 150, 243, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_600] = QColor(30, 136, 229, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_700] = QColor(25, 118, 210, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_800] = QColor(21, 101, 192, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_900] = QColor(13, 71, 161, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_A100] = QColor(130, 177, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_A200] = QColor(68, 138, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_A400] = QColor(41, 121, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Blue][QExtQuickPalette::Depth_A700] = QColor(41, 98, 255, 100);

    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_50] = QColor(225, 245, 254, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_100] = QColor(179, 229, 252, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_200] = QColor(129, 212, 250, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_300] = QColor(79, 195, 247, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_400] = QColor(41, 182, 246, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_500] = QColor(3, 169, 244, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_600] = QColor(3, 155, 229, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_700] = QColor(2, 136, 209, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_800] = QColor(2, 119, 189, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_900] = QColor(1, 87, 155, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_A100] = QColor(128, 216, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_A200] = QColor(64, 196, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_A400] = QColor(0, 176, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightBlue][QExtQuickPalette::Depth_A700] = QColor(0, 145, 234, 100);

    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_50] = QColor(224, 247, 250, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_100] = QColor(178, 235, 242, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_200] = QColor(128, 222, 234, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_300] = QColor(77, 208, 225, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_400] = QColor(38, 198, 218, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_500] = QColor(0, 188, 212, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_600] = QColor(0, 172, 193, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_700] = QColor(0, 151, 167, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_800] = QColor(0, 131, 143, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_900] = QColor(0, 96, 100, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_A100] = QColor(132, 255, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_A200] = QColor(24, 255, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_A400] = QColor(0, 229, 255, 100);
    m_materialColorVector[QExtQuickPalette::Color_Cyan][QExtQuickPalette::Depth_A700] = QColor(0, 184, 212, 100);

    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_50] = QColor(224, 242, 241, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_100] = QColor(178, 223, 219, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_200] = QColor(128, 203, 196, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_300] = QColor(77, 182, 172, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_400] = QColor(38, 166, 154, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_500] = QColor(0, 150, 136, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_600] = QColor(0, 137, 123, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_700] = QColor(0, 121, 107, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_800] = QColor(0, 105, 92, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_900] = QColor(0, 77, 64, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_A100] = QColor(167, 255, 235, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_A200] = QColor(100, 255, 218, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_A400] = QColor(29, 233, 182, 100);
    m_materialColorVector[QExtQuickPalette::Color_Teal][QExtQuickPalette::Depth_A700] = QColor(0, 191, 165, 100);

    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_50] = QColor(232, 245, 233, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_100] = QColor(200, 230, 201, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_200] = QColor(165, 214, 167, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_300] = QColor(129, 199, 132, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_400] = QColor(102, 187, 106, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_500] = QColor(76, 175, 80, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_600] = QColor(67, 160, 71, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_700] = QColor(56, 142, 60, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_800] = QColor(46, 125, 50, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_900] = QColor(27, 94, 32, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_A100] = QColor(185, 246, 202, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_A200] = QColor(105, 240, 174, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_A400] = QColor(0, 230, 118, 100);
    m_materialColorVector[QExtQuickPalette::Color_Green][QExtQuickPalette::Depth_A700] = QColor(0, 200, 83, 100);

    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_50] = QColor(241, 248, 233, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_100] = QColor(220, 237, 200, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_200] = QColor(197, 225, 165, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_300] = QColor(174, 213, 129, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_400] = QColor(156, 204, 101, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_500] = QColor(139, 195, 74, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_600] = QColor(124, 179, 66, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_700] = QColor(104, 159, 56, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_800] = QColor(85, 139, 47, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_900] = QColor(51, 105, 30, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_A100] = QColor(204, 255, 144, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_A200] = QColor(178, 255, 89, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_A400] = QColor(118, 255, 3, 100);
    m_materialColorVector[QExtQuickPalette::Color_LightGreen][QExtQuickPalette::Depth_A700] = QColor(100, 221, 23, 100);

    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_50] = QColor(249, 251, 231, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_100] = QColor(240, 244, 195, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_200] = QColor(230, 238, 156, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_300] = QColor(220, 231, 117, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_400] = QColor(212, 225, 87, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_500] = QColor(205, 220, 57, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_600] = QColor(192, 202, 51, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_700] = QColor(175, 180, 43, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_800] = QColor(158, 157, 36, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_900] = QColor(130, 119, 23, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_A100] = QColor(244, 255, 129, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_A200] = QColor(238, 255, 65, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_A400] = QColor(198, 255, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Lime][QExtQuickPalette::Depth_A700] = QColor(174, 234, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_50] = QColor(255, 253, 231, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_100] = QColor(255, 249, 196, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_200] = QColor(255, 245, 157, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_300] = QColor(255, 241, 118, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_400] = QColor(255, 238, 88, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_500] = QColor(255, 235, 59, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_600] = QColor(253, 216, 53, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_700] = QColor(251, 192, 45, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_800] = QColor(249, 168, 37, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_900] = QColor(245, 127, 23, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_A100] = QColor(255, 255, 141, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_A200] = QColor(255, 255, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_A400] = QColor(255, 234, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Yellow][QExtQuickPalette::Depth_A700] = QColor(255, 214, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_50] = QColor(255, 248, 225, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_100] = QColor(255, 236, 179, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_200] = QColor(255, 224, 130, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_300] = QColor(255, 213, 79, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_400] = QColor(255, 202, 40, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_500] = QColor(255, 193, 7, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_600] = QColor(255, 179, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_700] = QColor(255, 160, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_800] = QColor(255, 143, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_900] = QColor(255, 111, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_A100] = QColor(255, 229, 127, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_A200] = QColor(255, 215, 64, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_A400] = QColor(255, 196, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Amber][QExtQuickPalette::Depth_A700] = QColor(255, 171, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_50] = QColor(255, 243, 224, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_100] = QColor(255, 224, 178, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_200] = QColor(255, 204, 128, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_300] = QColor(255, 183, 77, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_400] = QColor(255, 167, 38, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_500] = QColor(255, 152, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_600] = QColor(251, 140, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_700] = QColor(245, 124, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_800] = QColor(239, 108, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_900] = QColor(230, 81, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_A100] = QColor(255, 209, 128, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_A200] = QColor(255, 171, 64, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_A400] = QColor(255, 145, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_Orange][QExtQuickPalette::Depth_A700] = QColor(255, 109, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_50] = QColor(251, 233, 231, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_100] = QColor(255, 204, 188, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_200] = QColor(255, 171, 145, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_300] = QColor(255, 138, 101, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_400] = QColor(255, 112, 67, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_500] = QColor(255, 87, 34, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_600] = QColor(244, 81, 30, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_700] = QColor(230, 74, 25, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_800] = QColor(216, 67, 21, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_900] = QColor(191, 54, 12, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_A100] = QColor(255, 158, 128, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_A200] = QColor(255, 110, 64, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_A400] = QColor(255, 61, 0, 100);
    m_materialColorVector[QExtQuickPalette::Color_DeepOrange][QExtQuickPalette::Depth_A700] = QColor(221, 44, 0, 100);

    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_50] = QColor(239, 235, 233, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_100] = QColor(215, 204, 200, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_200] = QColor(188, 170, 164, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_300] = QColor(161, 136, 127, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_400] = QColor(141, 110, 99, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_500] = QColor(121, 85, 72, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_600] = QColor(109, 76, 65, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_700] = QColor(93, 64, 55, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_800] = QColor(78, 52, 46, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_900] = QColor(62, 39, 35, 100);
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_A100] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_A200] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_A400] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Brown][QExtQuickPalette::Depth_A700] = QColor();

    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_50] = QColor(250, 250, 250, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_100] = QColor(245, 245, 245, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_200] = QColor(238, 238, 238, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_300] = QColor(224, 224, 224, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_400] = QColor(189, 189, 189, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_500] = QColor(158, 158, 158, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_600] = QColor(117, 117, 117, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_700] = QColor(97, 97, 97, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_800] = QColor(66, 66, 66, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_900] = QColor(33, 33, 33, 100);
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_A100] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_A200] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_A400] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_Grey][QExtQuickPalette::Depth_A700] = QColor();

    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_50] = QColor(236, 239, 241, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_100] = QColor(207, 216, 220, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_200] = QColor(176, 190, 197, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_300] = QColor(144, 164, 174, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_400] = QColor(120, 144, 156, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_500] = QColor(96, 125, 139, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_600] = QColor(84, 110, 122, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_700] = QColor(69, 90, 100, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_800] = QColor(55, 71, 79, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_900] = QColor(38, 50, 56, 100);
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_A100] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_A200] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_A400] = QColor();
    m_materialColorVector[QExtQuickPalette::Color_BlueGrey][QExtQuickPalette::Depth_A700] = QColor();

    m_brandColorVector.resize(QExtQuickPalette::BrandTypeNum);
    m_brandColorVector[QExtQuickPalette::Brand_Primary] = QColor(2, 123, 227, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Secondary] = QColor(38, 166, 154, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Accent] = QColor(156, 39, 176, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Dark] = QColor(29, 29, 29, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Positive] = QColor(33, 186, 69, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Negative] = QColor(193, 0, 21, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Info] = QColor(144, 147, 153, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Success] = QColor(103, 194, 58, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Warning] = QColor(230, 162, 60, 100);
    m_brandColorVector[QExtQuickPalette::Brand_Danger] = QColor(245, 108, 108, 100);

    m_textColorVector.resize(QExtQuickPalette::TextTypeNum);
    m_textColorVector[QExtQuickPalette::Text_Primary] = QColor(48, 49, 51, 100);
    m_textColorVector[QExtQuickPalette::Text_Normal] = QColor(96, 98, 102, 100);
    m_textColorVector[QExtQuickPalette::Text_Secondary] = QColor(144, 147, 153, 100);
    m_textColorVector[QExtQuickPalette::Text_Placeholder] = QColor(192, 196, 204, 100);

    m_borderColorVector.resize(QExtQuickPalette::BorderTypeNum);
    m_borderColorVector[QExtQuickPalette::Border_Level1] = QColor(220, 223, 230, 100);
    m_borderColorVector[QExtQuickPalette::Border_Level2] = QColor(228, 231, 237, 100);
    m_borderColorVector[QExtQuickPalette::Border_Level3] = QColor(235, 238, 245, 100);
    m_borderColorVector[QExtQuickPalette::Border_Level4] = QColor(242, 246, 252, 100);
}

QExtQuickPalettePrivate::~QExtQuickPalettePrivate()
{

}



static QExtQuickPalette *sg_insrance = nullptr;
const int QExtQuickPalette::BrandTypeNum = 10;
const int QExtQuickPalette::TextTypeNum = 4;
const int QExtQuickPalette::BorderTypeNum = 4;
const int QExtQuickPalette::ColorTypeNum = 19;
const int QExtQuickPalette::DepthTypeNum = 14;

QExtQuickPalette::QExtQuickPalette(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQuickPalettePrivate(this))
{

}

QExtQuickPalette::~QExtQuickPalette()
{

}

QObject *QExtQuickPalette::qmlSingletonTypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return QExtQuickPalette::instance();
}

QExtQuickPalette *QExtQuickPalette::instance()
{
    static QMutex mutex;
    QMutexLocker mutexLocker(&mutex);
    if (nullptr == sg_insrance) {
        sg_insrance = new QExtQuickPalette;
    }
    return sg_insrance;
}

QString QExtQuickPalette::randomColor() const
{
    return QColor(QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255),
                  QEXT_QUICK_PALETTE_COLOR_RANDOM(1, 255)).name();
}

QString QExtQuickPalette::brandColor(int brand) const
{
    if (brand < 0 || brand >= QExtQuickPalette::BrandTypeNum) {
        qCritical() << "QExtQuickPalette::brandColor():unknown brand type";
        return "";
    }
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(brand).name();
}

QString QExtQuickPalette::brandPrimaryColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Primary).name();
}

QString QExtQuickPalette::brandSecondaryColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Secondary).name();
}

QString QExtQuickPalette::brandAccentColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Accent).name();
}

QString QExtQuickPalette::brandDarkColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Dark).name();
}

QString QExtQuickPalette::brandPositiveColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Positive).name();
}

QString QExtQuickPalette::brandNegativeColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Negative).name();
}

QString QExtQuickPalette::brandInfoColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Info).name();
}

QString QExtQuickPalette::brandSuccessColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Success).name();
}

QString QExtQuickPalette::brandWarningColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Warning).name();
}

QString QExtQuickPalette::brandDangerColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_brandColorVector.at(QExtQuickPalette::Brand_Danger).name();
}

QString QExtQuickPalette::textColor(int textType) const
{
    if (textType < 0 || textType >= QExtQuickPalette::TextTypeNum) {
        qCritical() << "QExtQuickPalette::textColor():unknown textType";
        return "";
    }
    Q_D(const QExtQuickPalette);
    return d->m_textColorVector.at(textType).name();
}

QString QExtQuickPalette::textPrimaryColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_textColorVector.at(QExtQuickPalette::Text_Primary).name();
}

QString QExtQuickPalette::textNormalColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_textColorVector.at(QExtQuickPalette::Text_Normal).name();
}

QString QExtQuickPalette::textSecondaryColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_textColorVector.at(QExtQuickPalette::Text_Secondary).name();
}

QString QExtQuickPalette::textPlaceholderColor() const
{
    Q_D(const QExtQuickPalette);
    return d->m_textColorVector.at(QExtQuickPalette::Text_Placeholder).name();
}

QString QExtQuickPalette::borderColor(int borderLevel) const
{
    if (borderLevel < 0 || borderLevel >= QExtQuickPalette::BorderTypeNum) {
        qCritical() << "QExtQuickPalette::textColor():unknown borderLevel";
        return "";
    }
    Q_D(const QExtQuickPalette);
    return d->m_borderColorVector.at(borderLevel).name();
}

QString QExtQuickPalette::borderLevel1Color() const
{
    Q_D(const QExtQuickPalette);
    return d->m_borderColorVector.at(QExtQuickPalette::Border_Level1).name();
}

QString QExtQuickPalette::borderLevel2Color() const
{
    Q_D(const QExtQuickPalette);
    return d->m_borderColorVector.at(QExtQuickPalette::Border_Level2).name();
}

QString QExtQuickPalette::borderLevel3Color() const
{
    Q_D(const QExtQuickPalette);
    return d->m_borderColorVector.at(QExtQuickPalette::Border_Level3).name();
}

QString QExtQuickPalette::borderLevel4Color() const
{
    Q_D(const QExtQuickPalette);
    return d->m_borderColorVector.at(QExtQuickPalette::Border_Level4).name();
}

QString QExtQuickPalette::materialColor(int color, int depth) const
{
    if (color < 0 || color >= QExtQuickPalette::ColorTypeNum) {
        qCritical() << "QExtQuickPalette::color():unknown color type";
        return "";
    }
    if (depth < 0 || depth >= QExtQuickPalette::DepthTypeNum) {
        qCritical() << "QExtQuickPalette::color():unknown depth type";
        return "";
    }
    Q_D(const QExtQuickPalette);
    return d->m_materialColorVector.at(color).at(depth).name();
}

QString QExtQuickPalette::materialColorTypeName(int color)
{
    switch (color) {
    case Color_Red: return "Red";
    case Color_Pink: return "Pink";
    case Color_Purple: return "Purple";
    case Color_DeepPurple: return "DeepPurple";
    case Color_Indigo: return "Indigo";
    case Color_Blue: return "Blue";
    case Color_LightBlue: return "LightBlue";
    case Color_Cyan: return "Cyan";
    case Color_Teal: return "Teal";
    case Color_Green: return "Green";
    case Color_LightGreen: return "LightGreen";
    case Color_Lime: return "Lime";
    case Color_Yellow: return "Yellow";
    case Color_Amber: return "Amber";
    case Color_Orange: return "Orange";
    case Color_DeepOrange: return "DeepOrange";
    case Color_Brown: return "Brown";
    case Color_Grey: return "Grey";
    case Color_BlueGrey: return "BlueGrey";
    default: break;
    }
    return QString("");
}

QString QExtQuickPalette::materialDepthTypeName(int depth)
{
    switch (depth) {
    case Depth_50: return "50";
    case Depth_100: return "100";
    case Depth_200: return "200";
    case Depth_300: return "300";
    case Depth_400: return "400";
    case Depth_500: return "500";
    case Depth_600: return "600";
    case Depth_700: return "700";
    case Depth_800: return "800";
    case Depth_900: return "900";
    case Depth_A100: return "A100";
    case Depth_A200: return "A200";
    case Depth_A400: return "A400";
    case Depth_A700: return "A700";
    default: break;
    }
    return QString("");
}
