INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtkbusevent.h \
    $$PWD/qtkeventadminbus.h \
    $$PWD/qtkeventbus_global.h \
    $$PWD/qtkeventbusimpl.h \
    $$PWD/qtkeventbusmanager.h \
    $$PWD/qtkeventbusplugin.h \
    $$PWD/qtkeventdefinitions.h \
    $$PWD/qtkeventdispatcher.h \
    $$PWD/qtkeventdispatcherlocal.h \
    $$PWD/qtkeventdispatcherremote.h \
    $$PWD/qtkeventhandlerwrapper_p.h \
    $$PWD/qtknetworkconnector.h \
    $$PWD/qtknetworkconnectorqtsoap.h \
    $$PWD/qtktopicregistry.h

SOURCES += \
    $$PWD/qtkbusevent.cpp \
    $$PWD/qtkeventbusimpl.cpp \
    $$PWD/qtkeventbusmanager.cpp \
    $$PWD/qtkeventbusplugin.cpp \
    $$PWD/qtkeventdispatcher.cpp \
    $$PWD/qtkeventdispatcherlocal.cpp \
    $$PWD/qtkeventdispatcherremote.cpp \
    $$PWD/qtknetworkconnector.cpp \
    $$PWD/qtknetworkconnectorqtsoap.cpp \
    $$PWD/qtktopicregistry.cpp

RESOURCES += \
    $$PWD/QTKEventBus.qrc \
