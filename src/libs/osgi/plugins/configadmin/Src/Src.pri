INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtkcmeventdispatcher_p.h \
    $$PWD/qtkcmlogtracker_p.h \
    $$PWD/qtkcmpluginmanager_p.h \
    $$PWD/qtkcmserializedtaskqueue_p.h \
    $$PWD/qtkconfigurationadminactivator_p.h \
    $$PWD/qtkconfigurationadminfactory_p.h \
    $$PWD/qtkconfigurationadminimpl_p.h \
    $$PWD/qtkconfigurationeventadapter_p.h \
    $$PWD/qtkconfigurationimpl_p.h \
    $$PWD/qtkconfigurationstore_p.h \
    $$PWD/qtkmanagedservicefactorytracker_p.h \
    $$PWD/qtkmanagedservicetracker_p.h

SOURCES += \
    $$PWD/qtkcmeventdispatcher.cpp \
    $$PWD/qtkcmlogtracker.cpp \
    $$PWD/qtkcmpluginmanager.cpp \
    $$PWD/qtkcmserializedtaskqueue.cpp \
    $$PWD/qtkconfigurationadminactivator.cpp \
    $$PWD/qtkconfigurationadminfactory.cpp \
    $$PWD/qtkconfigurationadminimpl.cpp \
    $$PWD/qtkconfigurationeventadapter.cpp \
    $$PWD/qtkconfigurationimpl.cpp \
    $$PWD/qtkconfigurationstore.cpp \
    $$PWD/qtkmanagedservicefactorytracker.cpp \
    $$PWD/qtkmanagedservicetracker.cpp

RESOURCES += \
    $$PWD/QTKConfigAdmin.qrc
