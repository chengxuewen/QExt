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

#ifndef _QEXTVLCMETAMANAGER_H
#define _QEXTVLCMETAMANAGER_H

#include <QtCore/QDate>
#include <QtCore/QString>

#include <qextVLCGlobal.h>

class QEXTVLCMedia;

/*!
    \class QEXTVLCMetaManager qextVLCMetaManager.h
    \ingroup QEXTVLC
    \brief Media meta information manager

    A manager and editor of media's meta information.
*/
class QEXT_VLC_API QEXTVLCMetaManager
{
public:
    /*!
        \brief QEXTVLCMetaManager constructor.

        This constructor creates a new media instance from a media location.

        \param media selected media for meta information (QEXTVLCMedia *)
    */
    explicit QEXTVLCMetaManager(QEXTVLCMedia *media);

    /*!
        \brief QEXTVLCMetaManager destructor
    */
    ~QEXTVLCMetaManager();

    /*!
        \brief Get current track title.
        \return current track title (const QString)
    */
    QString title() const;

    /*!
        \brief Set track title.
        \param title new track title (QString)
    */
    void setTitle(const QString &title);

    /*!
        \brief Get current track artist.
        \return current track artist (const QString)
    */
    QString artist() const;

    /*!
        \brief Set track artist.
        \param artist new track artist (QString)
    */
    void setArtist(const QString &artist);

    /*!
        \brief Get current track genre.
        \return current track genre (const QString)
    */
    QString genre() const;

    /*!
        \brief Set track genre.
        \param genre new track genre (QString)
    */
    void setGenre(const QString &genre);

    /*!
        \brief Get current track copyright.
        \return current track copyright (const QString)
    */
    QString copyright() const;

    /*!
        \brief Set track copyright.
        \param copyright new track copyright (QString)
    */
    void setCopyright(const QString &copyright);

    /*!
        \brief Get current track album.
        \return current track album (const QString)
    */
    QString album() const;

    /*!
        \brief Set track album.
        \param album new track album (QString)
    */
    void setAlbum(const QString &album);

    /*!
        \brief Get current track number.
        \return current track number (const int)
    */
    int number() const;

    /*!
        \brief Set track number.
        \param number new track number (int)
    */
    void setNumber(int number);

    /*!
        \brief Get current track description.
        \return current track description (const QString)
    */
    QString description() const;

    /*!
        \brief Set track description.
        \param description new track description (QString)
    */
    void setDescription(const QString &description);

    /*!
        \brief Get current track rating.
        \return current track rating (const QString)
    */
    QString rating() const;

    /*!
        \brief Get current track year.
        \return current track year (const int)
    */
    int year() const;

    /*!
        \brief Set track year.
        \param year new track year (int)
    */
    void setYear(int year);

    /*!
        \brief Get current track setting.
        \return current track setting (const QString)
    */
    QString setting() const;

    /*!
        \brief Get current track URL.
        \return current track URL (const QString)
    */
    QString url() const;

    /*!
        \brief Get current track language.
        \return current track language (const QString)
    */
    QString language() const;

    /*!
        \brief Set track language.
        \param language new track language (QString)
    */
    void setLanguage(const QString &language);

    /*!
        \brief Get current track publisher.
        \return current track publisher (const QString)
    */
    QString publisher() const;

    /*!
        \brief Set track publisher.
        \param publisher new track publisher (QString)
    */
    void setPublisher(const QString &publisher);

    /*!
        \brief Get current track encoder.
        \return current track encoder (const QString)
    */
    QString encoder() const;

    /*!
        \brief Set track encoder.
        \param encoder new track encoder (QString)
    */
    void setEncoder(const QString &encoder);

    /*!
        \brief Get current track artwork URL.
        \return current track artwork URL (const QString)
    */
    QString artwork() const;

    /*!
        \brief Get current track ID.
        \return current track ID (const QString)
    */
    QString id() const;

    /*!
        \brief Save the meta previously set.
        \return true if the write operation was successfull (const bool)
    */
    bool saveMeta() const;

private:
    QEXTVLCMedia *m_media;
};

#endif // _QEXTVLCMETAMANAGER_H
