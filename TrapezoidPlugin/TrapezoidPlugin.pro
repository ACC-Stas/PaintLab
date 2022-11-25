QT += widgets

TEMPLATE = lib
DEFINES += TRAPEZOIDPLUGIN_LIBRARY

CONFIG += c++11
CONFIG += plugin


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    trapezoid.cpp \
    trapezoidplugin.cpp

HEADERS += \
    TrapezoidPlugin_global.h \
    trapezoid.h \
    trapezoidplugin.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
