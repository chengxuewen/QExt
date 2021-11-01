INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qtkplugingeneratorabstractextension.h \
    $$PWD/qtkplugingeneratorabstracttemplate.h \
    $$PWD/qtkplugingeneratorcmakelists.h \
    $$PWD/qtkplugingeneratorcodemodel.h \
    $$PWD/qtkplugingeneratorconstants.h \
    $$PWD/qtkplugingeneratorcore_global.h \
    $$PWD/qtkplugingeneratorcoreplugin_p.h \
    $$PWD/qtkplugingeneratorcpppluginactivator.h \
    $$PWD/qtkplugingeneratorcpptemplate.h \
    $$PWD/qtkplugingeneratorheadertemplate.h \
    $$PWD/qtkplugingeneratortargetlibraries.h

SOURCES += \
    $$PWD/qtkplugingeneratorabstractextension.cpp \
    $$PWD/qtkplugingeneratorabstracttemplate.cpp \
    $$PWD/qtkplugingeneratorcmakelists.cpp \
    $$PWD/qtkplugingeneratorcodemodel.cpp \
    $$PWD/qtkplugingeneratorconstants.cpp \
    $$PWD/qtkplugingeneratorcoreplugin.cpp \
    $$PWD/qtkplugingeneratorcpppluginactivator.cpp \
    $$PWD/qtkplugingeneratorcpptemplate.cpp \
    $$PWD/qtkplugingeneratorheadertemplate.cpp \
    $$PWD/qtkplugingeneratortargetlibraries.cpp

RESOURCES += \
    $$PWD/QTKPluginGeneratorCore.qrc
