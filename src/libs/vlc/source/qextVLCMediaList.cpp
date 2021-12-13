/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <vlc/vlc.h>

#include "qextVLCError.h"
#include "qextVLCInstance.h"
#include "qextVLCMedia.h"
#include "qextVLCMediaList.h"

QEXTVLCMediaList::QEXTVLCMediaList(QEXTVLCInstance *instance)
    : QObject(instance)
{
    m_vlcMediaList = libvlc_media_list_new(instance->core());
    m_vlcEvents = libvlc_media_list_event_manager(m_vlcMediaList);

    createCoreConnections();

    QEXTVLCError::showErrMsg();
}

QEXTVLCMediaList::~QEXTVLCMediaList()
{
    qDeleteAll(m_list);
    m_list.clear();

    removeCoreConnections();

    libvlc_media_list_release(m_vlcMediaList);

    QEXTVLCError::showErrMsg();
}

libvlc_media_list_t *QEXTVLCMediaList::core()
{
    return m_vlcMediaList;
}

void QEXTVLCMediaList::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListItemAdded
         << libvlc_MediaListWillAddItem
         << libvlc_MediaListItemDeleted
         << libvlc_MediaListWillDeleteItem;

    foreach (const libvlc_event_e &event, list) {
        libvlc_event_attach(m_vlcEvents, event, libvlc_callback, this);
    }
}

void QEXTVLCMediaList::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListItemAdded
         << libvlc_MediaListWillAddItem
         << libvlc_MediaListItemDeleted
         << libvlc_MediaListWillDeleteItem;

    foreach (const libvlc_event_e &event, list) {
        libvlc_event_detach(m_vlcEvents, event, libvlc_callback, this);
    }
}

void QEXTVLCMediaList::addMedia(QEXTVLCMedia *media)
{
    lock();
    libvlc_media_list_add_media(m_vlcMediaList, media->core());
    m_list.append(media);
    unlock();

    QEXTVLCError::showErrMsg();
}

QEXTVLCMedia *QEXTVLCMediaList::at(int index)
{
    return m_list[index];
}

int QEXTVLCMediaList::count()
{
    lock();
    int count = libvlc_media_list_count(m_vlcMediaList);
    unlock();

    QEXTVLCError::showErrMsg();

    return count;
}

int QEXTVLCMediaList::indexOf(QEXTVLCMedia *media)
{
    return m_list.indexOf(media);
}

int QEXTVLCMediaList::indexOf(libvlc_media_t *media)
{
    int index;
    lock();
    index = libvlc_media_list_index_of_item(m_vlcMediaList, media);
    unlock();

    QEXTVLCError::showErrMsg();

    return index;
}

void QEXTVLCMediaList::insertMedia(QEXTVLCMedia *media,
                               int index)
{
    lock();
    libvlc_media_list_insert_media(m_vlcMediaList, media->core(), index);
    m_list.insert(index, media);
    unlock();

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaList::removeMedia(int index)
{
    lock();
    libvlc_media_list_remove_index(m_vlcMediaList, index);
    delete m_list[index];
    m_list.removeAt(index);
    unlock();

    QEXTVLCError::showErrMsg();
}

void QEXTVLCMediaList::lock()
{
    libvlc_media_list_lock(m_vlcMediaList);
}

void QEXTVLCMediaList::unlock()
{
    libvlc_media_list_unlock(m_vlcMediaList);
}

void QEXTVLCMediaList::libvlc_callback(const libvlc_event_t *event,
                                   void *data)
{
    QEXTVLCMediaList *core = static_cast<QEXTVLCMediaList *>(data);

    switch (event->type) {
    case libvlc_MediaListItemAdded:
        emit core->itemAdded(event->u.media_list_item_added.item, event->u.media_list_item_added.index);
        break;
    case libvlc_MediaListWillAddItem:
        emit core->willAddItem(event->u.media_list_will_add_item.item, event->u.media_list_will_add_item.index);
        break;
    case libvlc_MediaListItemDeleted:
        emit core->itemDeleted(event->u.media_list_item_deleted.item, event->u.media_list_item_deleted.index);
        break;
    case libvlc_MediaListWillDeleteItem:
        emit core->willDeleteItem(event->u.media_list_will_delete_item.item, event->u.media_list_will_delete_item.index);
        break;
    default:
        break; // LCOV_EXCL_LINE
    }
}
