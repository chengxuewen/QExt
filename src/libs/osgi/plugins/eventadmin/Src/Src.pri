INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/adapter/qtkeaabstractadapter_p.h \
    $$PWD/adapter/qtkeaframeworkeventadapter_p.h \
    $$PWD/adapter/qtkealogeventadapter_p.h \
    $$PWD/adapter/qtkeaplugineventadapter_p.h \
    $$PWD/adapter/qtkeaserviceeventadapter_p.h \
    $$PWD/dispatch/qtkeachannel_p.h \
    $$PWD/dispatch/qtkeadefaultthreadpool_p.h \
    $$PWD/dispatch/qtkeainterruptedexception_p.h \
    $$PWD/dispatch/qtkeainterruptiblethread_p.h \
    $$PWD/dispatch/qtkealinkedqueue_p.h \
    $$PWD/dispatch/qtkeapooledexecutor_p.h \
    $$PWD/dispatch/qtkeasignalpublisher_p.h \
    $$PWD/dispatch/qtkeasyncmasterthread_p.h \
    $$PWD/dispatch/qtkeathreadfactory_p.h \
    $$PWD/dispatch/qtkeathreadfactoryuser_p.h \
    $$PWD/handler/qtkeablacklist_p.h \
    $$PWD/handler/qtkeablacklistinghandlertasks_p.h \
    $$PWD/handler/qtkeacachefilters_p.h \
    $$PWD/handler/qtkeacachetopichandlerfilters_p.h \
    $$PWD/handler/qtkeacleanblacklist_p.h \
    $$PWD/handler/qtkeafilters_p.h \
    $$PWD/handler/qtkeahandlertasks_p.h \
    $$PWD/handler/qtkeaslothandler_p.h \
    $$PWD/handler/qtkeatopichandlerfilters_p.h \
    $$PWD/qtkeaconfiguration_p.h \
    $$PWD/qtkeametatypeprovider_p.h \
    $$PWD/qtkeventadminactivator_p.h \
    $$PWD/qtkeventadminimpl_p.h \
    $$PWD/qtkeventadminservice_p.h \
    $$PWD/tasks/qtkeaasyncdelivertasks_p.h \
    $$PWD/tasks/qtkeadelivertask_p.h \
    $$PWD/tasks/qtkeahandlertask_p.h \
    $$PWD/tasks/qtkeasyncdelivertasks_p.h \
    $$PWD/tasks/qtkeasyncthread_p.h \
    $$PWD/util/qtkeabrokenbarrierexception_p.h \
    $$PWD/util/qtkeacachemap_p.h \
    $$PWD/util/qtkeacyclicbarrier_p.h \
    $$PWD/util/qtkealeastrecentlyusedcachemap_p.h \
    $$PWD/util/qtkealogtracker_p.h \
    $$PWD/util/qtkearendezvous_p.h \
    $$PWD/util/qtkeatimeoutexception_p.h

SOURCES += \
    $$PWD/adapter/qtkeaabstractadapter.cpp \
    $$PWD/adapter/qtkeaframeworkeventadapter.cpp \
    $$PWD/adapter/qtkealogeventadapter.cpp \
    $$PWD/adapter/qtkeaplugineventadapter.cpp \
    $$PWD/adapter/qtkeaserviceeventadapter.cpp \
    $$PWD/dispatch/qtkeadefaultthreadpool.cpp \
    $$PWD/dispatch/qtkeainterruptedexception.cpp \
    $$PWD/dispatch/qtkeainterruptiblethread.cpp \
    $$PWD/dispatch/qtkealinkedqueue.cpp \
    $$PWD/dispatch/qtkeapooledexecutor.cpp \
    $$PWD/dispatch/qtkeasignalpublisher.cpp \
    $$PWD/dispatch/qtkeasyncmasterthread.cpp \
    $$PWD/dispatch/qtkeathreadfactoryuser.cpp \
    $$PWD/handler/qtkeacleanblacklist.cpp \
    $$PWD/handler/qtkeaslothandler.cpp \
    $$PWD/qtkeaconfiguration.cpp \
    $$PWD/qtkeametatypeprovider.cpp \
    $$PWD/qtkeventadminactivator.cpp \
    $$PWD/qtkeventadminservice.cpp \
    $$PWD/tasks/qtkeasyncthread.cpp \
    $$PWD/util/qtkeabrokenbarrierexception.cpp \
    $$PWD/util/qtkeacyclicbarrier.cpp \
    $$PWD/util/qtkealogtracker.cpp \
    $$PWD/util/qtkearendezvous.cpp \
    $$PWD/util/qtkeatimeoutexception.cpp

RESOURCES += \
    $$PWD/QTKEventAdmin.qrc

