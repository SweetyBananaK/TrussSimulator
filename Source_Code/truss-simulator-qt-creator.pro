QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    displacement_arrow.cpp \
    edge.cpp \
    force.cpp \
    joint.cpp \
    main.cpp \
    mainwindow.cpp \
    myscene.cpp \
    parser.cpp \
    truss.cpp \
    trusswidget.cpp


HEADERS += \
    displacement_arrow.hpp \
    edge.hpp \
    exprtk.hpp \
    force.hpp \
    joint.hpp \
    mainwindow.hpp \
    myscene.hpp \
    parser.hpp \
    truss.hpp \
    trusswidget.hpp \
    utils.hpp



FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    $(HOME)/Software/Eigen/ \
    $(HOME)/Software/dco/include
LIBS += \
    -L$(HOME)/Software/dco/lib -dcoc #hier -L


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    E-modul_test.truss \
    hausvomnikolaus.truss \
    icon/zoomIn.png \
    icon/zoomOut.png \
    test_save_file.truss \
    zoomIn.png

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Software/dco/lib/release/ -ldcoc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Software/dco/lib/debug/ -ldcoc
else:unix:!macx: LIBS += -L$$PWD/../../Software/dco/lib/ -ldcoc

INCLUDEPATH += $(HOME)/Software/dco/include
DEPENDPATH += $(HOME)/Software/dco/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(HOME)/Software/dco/lib/release/libdcoc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(HOME)/Software/dco/lib/debug/libdcoc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $(HOME)/Software/dco/lib/release/dcoc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $(HOME)/Software/dco/lib/debug/dcoc.lib
else:unix:!macx: PRE_TARGETDEPS += $(HOME)/Software/dco/lib/libdcoc.a

NAG_KUSARI_FILE=$(HOME)/Software/dco/nag_key.txt

RESOURCES +=
    icon.qrc
