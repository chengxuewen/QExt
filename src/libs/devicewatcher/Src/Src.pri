INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtkdevicewatcher.h \
    $$PWD/qtkdevicewatcher_global.h \
    $$PWD/qtkdevicewatcher_p.h

SOURCES += \
    $$PWD/qtkdevicewatcher.cpp \
    $$PWD/qtkdevicewatcher_global.cpp

win32 {
    wince: SOURCES += $$PWD/qtkdevicewatcher_wince.cpp
    else: SOURCES += $$PWD/qtkdevicewatcher_win32.cpp
    LIBS *= -luser32
}

unix {
    macx {
        SOURCES += $$PWD/qtkdevicewatcher_mac.cpp
        LIBS += -framework DiskArbitration -framework Foundation
    } else {
        SOURCES += $$PWD/qtkdevicewatcher_linux.cpp
    }
}
