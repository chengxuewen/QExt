/*************************************************************************************
*
* Library: QExt
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2014 Tadej Novak <tadej@tano.si>
*
* License: MIT License
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*************************************************************************************/

#ifndef _QEXTVLCVIDEOFRAME_H
#define _QEXTVLCVIDEOFRAME_H

#include <qextVLCGlobal.h>

#include <QtCore/QByteArray>

/*!
    \struct QEXTVLCVideoFrame qextVLCVideoFrame.h
    \ingroup QEXTVLC
    \brief Video frame data container (deprecated)
    \see QEXTVLCAbstractVideoFrame
    @deprecated Deprecated since QExt 0.11.1
*/
struct Q_DECL_DEPRECATED QEXT_VLC_API QEXTVLCVideoFrame
{
    /*!
        \brief QEXTVLCVideoFrame constructor.

        This construction ensures default data is set.
    */
    QEXTVLCVideoFrame();

    bool inited; /*!< initialisation status */

    unsigned int width; /*!< frame width */
    unsigned int height; /*!< frame height */

    unsigned int planeCount; /*!< plane count */

    QByteArray plane[4]; /*!< plane data */

    int pitch[4]; /*!< pitch information */
    int visiblePitch[4]; /*!< visible pitch information */
    int lines[4]; /*!< lines count */
    int visibleLines[4]; /*!< visible lines count */
};

#endif // _QEXTVLCVIDEOFRAME_H
