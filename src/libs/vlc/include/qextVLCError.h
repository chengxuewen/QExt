/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCERROR_H
#define _QEXTVLCERROR_H

#include <qextVLCGlobal.h>

/*!
    \class QEXTVLCError qextVLCError.h
    \ingroup QEXTVLC
	\brief Error handler

	A basic error handler for VLC-Qt library.
*/
class QEXT_VLC_API QEXTVLCError
{
public:
    /*!
        \brief A human-readable error message for the last libvlc error in the calling thread.

        The resulting string is valid until another error occurs.
        \return error message (QString)
        \warning There may be no output, if there is no error.
    */
    static QString errmsg();

    /*!
        \brief A human-readable error message displayed into standard output for the last libvlc error in the calling thread.

        The resulting string is valid until another error occurs.
        \warning There may be no output, if there is no error.
    */
    static void showErrMsg();

    /*!
        \brief Clears the libvlc error status for the current thread.

        This does nothing.

        @deprecated Deprecated since QEXT 0.11.1, will be removed in 2.0
    */
    Q_DECL_DEPRECATED static void clearerr();
};

#endif // _QEXTVLCERROR_H
