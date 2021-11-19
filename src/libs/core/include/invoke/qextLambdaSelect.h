/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright 2002, The libsigc++ Development Team
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTLAMBDASELECT_H
#define _QEXTLAMBDASELECT_H

#include <qextLambdaBase.h>

namespace qextPrivate
{

    struct QEXTLambdaSelect1 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg1 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1>
        T_arg1 operator ()(T_arg1 arg1) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2>
        T_arg1 operator ()(T_arg1 arg1, T_arg2) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3>
        T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6) const
        {
            return arg1;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg1 operator ()(T_arg1 arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const
        {
            return arg1;
        }
    };

    struct QEXTLambdaSelect2 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg2 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2>
        T_arg2 operator ()(T_arg1, T_arg2 arg2) const
        {
            return arg2;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3>
        T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3) const
        {
            return arg2;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4) const
        {
            return arg2;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5) const
        {
            return arg2;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5, T_arg6) const
        {
            return arg2;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg2 operator ()(T_arg1, T_arg2 arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7) const
        {
            return arg2;
        }
    };

    struct QEXTLambdaSelect3 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg3 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2, typename T_arg3>
        T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3) const
        {
            return arg3;
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4) const
        {
            return arg3;
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5) const
        {
            return arg3;
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5, T_arg6) const
        {
            return arg3;
        }


        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg3 operator ()(T_arg1, T_arg2, T_arg3 arg3, T_arg4, T_arg5, T_arg6, T_arg7) const
        {
            return arg3;
        }
    };

    struct QEXTLambdaSelect4 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg4 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4>
        T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4) const
        {
            return arg4;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5) const
        {
            return arg4;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5, T_arg6) const
        {
            return arg4;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg4 operator ()(T_arg1, T_arg2, T_arg3, T_arg4 arg4, T_arg5, T_arg6, T_arg7) const
        {
            return arg4;
        }
    };

    struct QEXTLambdaSelect5 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg5 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5>
        T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5) const
        {
            return arg5;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5, T_arg6) const
        {
            return arg5;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg5 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5 arg5, T_arg6, T_arg7) const
        {
            return arg5;
        }
    };

    struct QEXTLambdaSelect6 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg6 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6>
        T_arg6 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 arg6) const
        {
            return arg6;
        }

        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg6 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6 arg6, T_arg7) const
        {
            return arg6;
        }
    };

    struct QEXTLambdaSelect7 : public QEXTLambdaBase
    {
        template <typename T_arg1 = void, typename T_arg2 = void, typename T_arg3 = void,
                  typename T_arg4 = void, typename T_arg5 = void, typename T_arg6 = void, typename T_arg7 = void>
        struct ReturnTypeDeduce
        {
            typedef T_arg7 Type;
        };
        typedef void Return; // no operator ()() overload

        void operator ()() const; // not implemented
        template <typename T_arg1, typename T_arg2, typename T_arg3, typename T_arg4, typename T_arg5, typename T_arg6, typename T_arg7>
        T_arg7 operator ()(T_arg1, T_arg2, T_arg3, T_arg4, T_arg5, T_arg6, T_arg7 arg7) const
        {
            return arg7;
        }
    };

} /* namespace qextPrivate */


static const QEXTLambda<qextPrivate::QEXTLambdaSelect1> g_qextLambdaSelector1;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect2> g_qextLambdaSelector2;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect3> g_qextLambdaSelector3;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect4> g_qextLambdaSelector4;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect5> g_qextLambdaSelector5;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect6> g_qextLambdaSelector6;
static const QEXTLambda<qextPrivate::QEXTLambdaSelect7> g_qextLambdaSelector7;

namespace qextLambdaSelectors
{
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect1> _1;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect2> _2;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect3> _3;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect4> _4;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect5> _5;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect6> _6;
    static const QEXTLambda<qextPrivate::QEXTLambdaSelect7> _7;
}



#endif // _QEXTLAMBDASELECT_H
