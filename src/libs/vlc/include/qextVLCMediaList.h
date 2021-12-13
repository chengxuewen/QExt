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

#ifndef _QEXTVLCMEDIALIST_H
#define _QEXTVLCMEDIALIST_H

#include <qextVLC.h>
#include <qextVLCGlobal.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

class QEXTVLCInstance;
class QEXTVLCMedia;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;
struct libvlc_media_list_t;

/*!
    \class QEXTVLCMediaList qextVLCMediaList.h
    \ingroup QEXTVLC
    \brief Media list item

    QEXTVLCMediaList holds multiple QEXTVLCMedia items to play in sequence.
*/
class QEXT_VLC_API QEXTVLCMediaList : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief QEXTVLCMediaList constructor.

        This constructor creates a new media list instance.

        \param instance main libvlc instance
    */
    explicit QEXTVLCMediaList(QEXTVLCInstance *instance);

    /*!
        \brief QEXTVLCMediaList destructor
    */
    ~QEXTVLCMediaList();

    /*!
        \brief libvlc media list item
        \return libvlc media list item (libvlc_media_list_t *)
    */
    libvlc_media_list_t *core();

    /*!
        \brief Add media item to the list
        \param media media item
    */
    void addMedia(QEXTVLCMedia *media);

    /*!
        \brief Get media item at selected index
        \param index item position
        \return media item (QEXTVLCMedia)
    */
    QEXTVLCMedia *at(int index);

    /*!
        \brief libvlc media list item
        \return items count (int)
    */
    int count();

    /*!
        \brief Index of media item
        \param media media item
        \return media item index (int)
    */
    int indexOf(QEXTVLCMedia *media);

    /*!
        \brief Index of media item (core)
        \param media media item
        \return media item index (int)
    */
    int indexOf(libvlc_media_t *media);

    /*!
        \brief Insert media item at the specific position of the list.
        \param media media item
        \param index item position
    */
    void insertMedia(QEXTVLCMedia *media, int index);

    /*!
        \brief Remove media item from the specific position of the list.
        \param index item position
    */
    void removeMedia(int index);

signals:
    /*!
        \brief Signal sent on item added
        \param item item that was added
        \param index index of item
    */
    void itemAdded(libvlc_media_t *item, int index);

    /*!
        \brief Signal sent when item will be added
        \param item item that will be added
        \param index index of item
    */
    void willAddItem(libvlc_media_t *item, int index);

    /*!
        \brief Signal sent on item deleted
        \param item item that was added
        \param index index of item
    */
    void itemDeleted(libvlc_media_t *item, int index);

    /*!
        \brief Signal sent when item will be deleted
        \param item item that will be deleted
        \param index index of item
    */
    void willDeleteItem(libvlc_media_t *item, int index);

private:
    void lock();
    void unlock();

    static void libvlc_callback(const libvlc_event_t *event, void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_list_t *m_vlcMediaList;
    libvlc_event_manager_t *m_vlcEvents;
    QList<QEXTVLCMedia *> m_list;
};

#endif // _QEXTVLCMEDIALIST_H
