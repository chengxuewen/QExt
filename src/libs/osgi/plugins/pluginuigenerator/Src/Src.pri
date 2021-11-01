INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

FORMS += \
    $$PWD/qtkplugingeneratormainextension.ui \
    $$PWD/qtkplugingeneratormanifestextension.ui

HEADERS += \
    $$PWD/qtkplugingeneratorabstractuiextension.h \
    $$PWD/qtkplugingeneratormainextension.h \
    $$PWD/qtkplugingeneratorui_global.h \
    $$PWD/qtkplugingeneratoruiplugin_p.h

SOURCES += \
    $$PWD/qtkplugingeneratorabstractuiextension.cpp \
    $$PWD/qtkplugingeneratormainextension.cpp \
    $$PWD/qtkplugingeneratoruiplugin.cpp

RESOURCES += \
    $$PWD/QTKPluginGeneratorUI.qrc
