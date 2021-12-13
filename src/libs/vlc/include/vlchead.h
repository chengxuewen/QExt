#ifndef VLCHEAD_H
#define VLCHEAD_H 1

# ifdef __cplusplus
extern "C" {
# endif

#define vlc3

#ifdef vlc3
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
#include <vlc/deprecated.h>
#else
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

# ifdef __cplusplus
}
# endif

#include "qdatetime.h"
#pragma execution_character_set("utf-8")


#define TIMEMS          qPrintable(QTime::currentTime().toString("HH:mm:ss zzz"))
#define TIME            qPrintable(QTime::currentTime().toString("HH:mm:ss"))
#define QDATE           qPrintable(QDate::currentDate().toString("yyyy-MM-dd"))
#define QTIME           qPrintable(QTime::currentTime().toString("HH-mm-ss"))
#define DATETIME        qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
#define STRDATETIME     qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))
#define STRDATETIMEMS   qPrintable(QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz"))

#endif // VLCHEAD_H
