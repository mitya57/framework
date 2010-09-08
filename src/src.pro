include(../mconfig.pri)

VERSION = 0.1.0
TEMPLATE = lib
TARGET = meegoimframework

# Input
HEADERSINSTALL = \
        minputmethodplugin.h \
        minputmethodbase.h \
        mimpluginmanager.h \
        minputcontextconnection.h \
        mplainwindow.h \
        mpreeditface.h \
        mimhandlerstate.h \
        mimdirection.h \
        mtoolbaritem.h \
        mtoolbardata.h \
        minputmethodnamespace.h \
        minputmethodsettingsbase.h \

HEADERS += $$HEADERSINSTALL \
        mimpluginmanager_p.h \
        mimapplication.h \
        mtoolbardata_p.h \
        mtoolbaritem_p.h \
        mtoolbarmanager.h \
        mtoolbarid.h \
        mimsettingsdialog.h \

SOURCES += mimpluginmanager.cpp \
        minputmethodbase.cpp \
        minputcontextconnection.cpp \
        mplainwindow.cpp \
        mimapplication.cpp \
        mtoolbaritem.cpp \
        mtoolbardata.cpp \
        mtoolbarmanager.cpp \
        mtoolbarid.cpp \
        mimsettingsdialog.cpp \

CONFIG += debug meegotouchcore qdbus
QT = core gui xml

contains(DEFINES, QT_DBUS) {
    SOURCES += minputcontextdbusconnection.cpp
    HEADERS += minputcontextdbusconnection.h minputcontextdbusconnection_p.h
} else {
    CONFIG += link_pkgconfig
    PKGCONFIG += dbus-glib-1 dbus-1
    SOURCES += minputcontextglibdbusconnection.cpp
    HEADERS += minputcontextglibdbusconnection.h
}

# coverage flags are off per default, but can be turned on via qmake COV_OPTION=on
for(OPTION,$$list($$lower($$COV_OPTION))){
    isEqual(OPTION, on){
        QMAKE_CXXFLAGS += -ftest-coverage -fprofile-arcs -fno-elide-constructors
        LIBS += -lgcov
    }
}

QMAKE_CLEAN += *.gcno *.gcda

target.path += $$M_INSTALL_LIBS

OBJECTS_DIR = .obj
MOC_DIR = .moc

headers.path += $$M_INSTALL_HEADERS/meegoimframework
headers.files += $$HEADERSINSTALL

install_pkgconfig.path = $$[QT_INSTALL_LIBS]/pkgconfig
install_pkgconfig.files = MeegoImFramework.pc

install_prf.path = $$[QT_INSTALL_DATA]/mkspecs/features
install_prf.files = meegoimframework.prf

install_xml.path = /usr/share/meegotouch/imtoolbars/imframework
install_xml.files = standard.xml

INSTALLS += target \
    headers \
    install_prf \
    install_pkgconfig \
    install_xml \

QMAKE_EXTRA_TARGETS += check-xml
check-xml.target = check-xml
check-xml.depends += lib$${TARGET}.so.$${VERSION}

QMAKE_EXTRA_TARGETS += check
check.target = check
check.depends += lib$${TARGET}.so.$${VERSION}

contains(DEFINES, M_IM_DISABLE_TRANSLUCENCY) {
    M_IM_FRAMEWORK_FEATURE += M_IM_DISABLE_TRANSLUCENCY
} else {
    M_IM_FRAMEWORK_FEATURE -= M_IM_DISABLE_TRANSLUCENCY
}

PRF_FILE = meegoimframework.prf.in

prffilegenerator.output = meegoimframework.prf
prffilegenerator.input = PRF_FILE
prffilegenerator.commands += sed -e \"s:M_IM_FRAMEWORK_FEATURE:$$M_IM_FRAMEWORK_FEATURE:g\" ${QMAKE_FILE_NAME} > ${QMAKE_FILE_OUT}
prffilegenerator.CONFIG = target_predeps no_link
prffilegenerator.depends += Makefile
QMAKE_EXTRA_COMPILERS += prffilegenerator

