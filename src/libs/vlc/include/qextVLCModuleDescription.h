/*************************************************************************************
*
* Library: QEXT
*
* Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#ifndef _QEXTVLCMODULEDESCRIPTION_H
#define _QEXTVLCMODULEDESCRIPTION_H

#include <qextVLCGlobal.h>

#include <QtCore/QString>

/*!
    \class QEXTVLCModuleDescription qextVLCModuleDescription.h
    \ingroup QEXTVLC
    \brief VLC module description
*/
class QEXT_VLC_API QEXTVLCModuleDescription
{
public:
    /*!
        \enum Type
        \brief Module type
    */
    enum Type
    {
        AudioFilter,
        VideoFilter
    };

    /*!
        \brief Basic constructor
        \param type module type
        \param name module name
    */
    explicit QEXTVLCModuleDescription(Type type, const QString &name);

    /*!
        \brief QEXTVLCModuleDescription destructor
    */
    ~QEXTVLCModuleDescription();

    /*!
        \brief Get module type
        \return module type
    */
    inline Type type() const
    {
        return m_type;
    }

    /*!
        \brief Get module name
        \return module name
    */
    inline QString name() const
    {
        return m_name;
    }

    /*!
        \brief Get short module readable name
        \return short module human readable name
    */
    inline QString shortName() const
    {
        return m_shortName;
    }

    /*!
        \brief Set short module readable name
        \param name short module human readable name
    */
    void setShortName(const QString &name);

    /*!
        \brief Get long module readable name
        \return long module human readable name
    */
    inline QString longName() const
    {
        return m_longName;
    }

    /*!
        \brief Set long module readable name
        \param name long module human readable name
    */
    void setLongName(const QString &name);

    /*!
        \brief Get module help
        \return module help
    */
    inline QString help() const
    {
        return m_help;
    }

    /*!
        \brief Set module help
        \param help new module help
    */
    void setHelp(const QString &help);

private:
    Type m_type;
    QString m_name;
    QString m_shortName;
    QString m_longName;
    QString m_help;
};

#endif // _QEXTVLCMODULEDESCRIPTION_H
