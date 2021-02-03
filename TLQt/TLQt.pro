#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T14:26:39
#
#-------------------------------------------------

QT       += core gui gui-private widgets

TEMPLATE = lib
TARGET = TLQt

SOURCES += $$PWD/src/TerraLens/QTextureViewport.cpp \
    $$PWD/src/TerraLens/QTextureViewport2D.cpp \
	$$PWD/src/TerraLens/QTextureViewport3D.cpp \
	$$PWD/src/TerraLens/QWidgetViewport.cpp \
	$$PWD/src/TerraLens/QWidgetViewport2D.cpp \
	$$PWD/src/TerraLens/QWidgetViewport3D.cpp

HEADERS  += $$PWD/include/TerraLens/QTextureViewport.h \
    $$PWD/include/TerraLens/QTextureViewport2D.h \
	$$PWD/include/TerraLens/QTextureViewport3D.h \
	$$PWD/include/TerraLens/QWidgetViewport.h \
	$$PWD/include/TerraLens/QWidgetViewport2D.h \
	$$PWD/include/TerraLens/QWidgetViewport3D.h

DEFINES += ICL_EXPORTS

!exists($$(TLCOREDIR)){
    error(TLCOREDIR environment variable undefined or target does not exist: $$(TLCOREDIR))
}
!exists($$(TLINPUTDIR)){
    error(TLINPUTDIR environment variable undefined or target does not exist: $$(TLINPUTDIR))
}

win32 {

    INCLUDEPATH += ./src \
		./include

    INCLUDEPATH += $$(TLCOREDIR)/include
    INCLUDEPATH += $$(TLINPUTDIR)/include



    CONFIG(debug, debug|release) {

        CONFIGURATION = Debug

        DLLS += \
            $$(QTDIR)/bin/Qt5Cored.dll \
            $$(QTDIR)/bin/Qt5Guid.dll \
            $$(QTDIR)/bin/Qt5Widgetsd.dll \

        LIBS += -L$$(TLINPUTDIR)/lib/Debug

        PLATFORM_DLLS += \
            $$(QTDIR)/plugins/platforms/qminimald.dll \
            $$(QTDIR)/plugins/platforms/qwindowsd.dll
    } else {

        CONFIGURATION = Release

        DLLS += \
            $$(QTDIR)/bin/Qt5Core.dll \
            $$(QTDIR)/bin/Qt5Gui.dll \
            $$(QTDIR)/bin/Qt5Widgets.dll

        LIBS += -L$$(TLINPUTDIR)/lib/Release

        PLATFORM_DLLS += \
            $$(QTDIR)/plugins/platforms/qminimal.dll \
            $$(QTDIR)/plugins/platforms/qwindows.dll
    }

    LIBS += \
        -lMapping -L$$(TLCOREDIR)/lib \ 
        -lIVC -L$$(TLCOREDIR)/lib \
        -lIAC -L$$(TLCOREDIR)/lib \
        -lglu32 -lTLInput \
        -lopengl32

    DLLS += \
        $$(TLCOREDIR)/lib/IVC.dll \
        $$(TLCOREDIR)/3rdParty/lti_dsdk.dll \
        $$(TLCOREDIR)/3rdParty/rlm1131.dll
}

unix {

    INCLUDEPATH += ./src $$(TLCOREDIR)/include
    INCLUDEPATH += $$(TLINPUTDIR)/include

    CONFIG(debug, debug|release) {

        CONFIGURATION = debug

        DLLS += \
            $$(QTDIR)/bin/Qt5Cored.so \
            $$(QTDIR)/bin/Qt5Guid.so \
            $$(QTDIR)/bin/Qt5Widgetsd.so \

        PLATFORM_DLLS += \
            $$(QTDIR)/plugins/platforms/libqminimald.so

    } else {

        CONFIGURATION = release

        DLLS += \
            $$(QTDIR)/bin/Qt5Core.so \
            $$(QTDIR)/bin/Qt5Gui.so \
            $$(QTDIR)/bin/Qt5Widgets.so \

        PLATFORM_DLLS += \
            $$/../plugins/platforms/libqminimal.so
    }

    LIBS += -lIVC -L$$(TLCOREDIR)/lib -L$$(TLINPUTDIR)/lib \
            -lltidsdk
-
    DLLS += \
        $$(TLCOREDIR)/lib/libIVC.so \
        $$(TLCOREDIR)/lib/libltidsdk.so
}

DESTDIR = $$CONFIGURATION/bin
OBJECTS_DIR = $$CONFIGURATION/obj
UI_DIR = $$CONFIGURATION/ui
MOC_DIR = $$CONFIGURATION/moc
RCC_DIR = $$CONFIGURATION/rcc

DLLS_TO_INSTALL.files = $$DLLS
DLLS_TO_INSTALL.path = $$DESTDIR
INSTALLS += DLLS_TO_INSTALL
PLATFORM_DLLS_TO_INSTALL.files = $$PLATFORM_DLLS
PLATFORM_DLLS_TO_INSTALL.path = $$DESTDIR/platforms
INSTALLS += PLATFORM_DLLS_TO_INSTALL

debug{
PDBS_TO_INSTALL.files = $$(TLCOREDIR)/lib/IVC.pdb
PDBS_TO_INSTALL.path = $$DESTDIR
INSTALLS += PDBS_TO_INSTALL
}
