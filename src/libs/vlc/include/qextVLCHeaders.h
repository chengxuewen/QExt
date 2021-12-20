#ifndef _QEXTVLCHEADERS_H
#define _QEXTVLCHEADERS_H

#include <qextVLCConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#if QEXT_LIBVLC_VERSION >= 3
#include <vlc/libvlc.h>
#include <vlc/libvlc.h>
#include <vlc/libvlc_renderer_discoverer.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>
#include <vlc/libvlc_media_list.h>
#include <vlc/libvlc_media_list_player.h>
#include <vlc/libvlc_media_library.h>
#include <vlc/libvlc_media_discoverer.h>
#include <vlc/libvlc_events.h>
#include <vlc/libvlc_dialog.h>
#include <vlc/libvlc_vlm.h>
#include <deprecated.h>
#else
#include <vlc.h>
#include <libvlc.h>
#include <libvlc_structures.h>
#include <libvlc_media.h>
#include <libvlc_media_player.h>
#include <libvlc_media_list.h>
#include <libvlc_media_list_player.h>
#include <libvlc_media_library.h>
#include <libvlc_media_discoverer.h>
#include <libvlc_events.h>
#include <libvlc_vlm.h>
#include <deprecated.h>
#endif

#ifdef __cplusplus
}
#endif

#include <QDateTime>
#pragma execution_character_set("utf-8")


#define TIMEMS          qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME            qPrintable(QTime::currentTime().toString("HH:mm:ss"))
#define QDATE           qPrintable(QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME           qPrintable(QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME        qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME     qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS   qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))

#endif // _QEXTVLCHEADERS_H
