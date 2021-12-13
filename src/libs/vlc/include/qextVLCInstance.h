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

#ifndef _QEXTVLCVLCINSTANCE_H
#define _QEXTVLCVLCINSTANCE_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QObject>

struct libvlc_instance_t;

class QEXTVLCModuleDescription;

/*!
    \class QEXTVLCInstance qextVLCInstance.h
    \ingroup QEXTVLC
    \brief Main instance

    A basic Instance manager for VLC-Qt library.
    It provides main instance controls.
*/
class QEXTVLCInstancePrivate;
class QEXT_VLC_API QEXTVLCInstance : public QObject
{
    Q_OBJECT
public:
    /*!
            \brief QEXTVLCInstance constructor.

            This is mandatory for using VLC-Qt and all its other classes.

            \param args libvlc arguments (QStringList)
            \param parent Instance's parent object (QObject *)
        */
    explicit QEXTVLCInstance(const QStringList &args, QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTVLCInstance();

    /*!
        \brief Returns libvlc instance object.
        \return libvlc instance (libvlc_instance_t *)
    */
    libvlc_instance_t *core();

    /*!
        \brief Returns libvlc initialisation status.
        \return libvlc status (bool)
    */
    bool status() const;

    /*!
        \brief Returns current log level (default QEXTVLC::ErrorLevel)
        \return log level
        \since QEXT 0.11.1
    */
    QEXTVLC::LogLevelType logLevel() const;

    /*!
        \brief Set current log level
        \param level desired log level
        \see QEXTVLC::LogLevel
        \since QEXT 0.11.1
    */
    void setLogLevel(QEXTVLC::LogLevelType level);


    /*!
        \brief libvlc version info
        \return a string containing the libvlc version (QString)
    */
    static QString version();

    /*!
        \brief libvlc compiler info
        \return a string containing the compiler version (QString)
    */
    static QString compiler();

    /*!
        \brief libvlc changeset info
        \return a string containing the changeset (QString)
    */
    static QString changeset();

    /*!
        \brief Sets the application name.

        libvlc passes this as the user agent string when a protocol requires it.

        \param application Application name (QString)
        \param version Application version (QString)

        \see setAppId
    */
    void setUserAgent(const QString &application, const QString &version);

    /*!
        \brief Sets the application some meta-information.

        \param id Java-style application identifier, e.g. "com.acme.foobar"
        \param version application version numbers, e.g. "1.2.3"
        \param icon application icon name, e.g. "foobar"

        \see setUserAgent
        \brief QEXT 0.11.1
    */
    void setAppId(const QString &id, const QString &version, const QString &icon);

    /*!
        \brief List audio filter modules
        \briefn audio filter module description list
    */
    QList<QEXTVLCModuleDescription *> audioFilterList() const;

    /*!
        \brief List video filter modules
        \return video filter module description list
    */
    QList<QEXTVLCModuleDescription *> videoFilterList() const;

protected:
    QScopedPointer<QEXTVLCInstancePrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTVLCInstance)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTVLCInstance)
};

#endif // _QEXTVLCVLCINSTANCE_H
