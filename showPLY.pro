HEADERS += \
    myglwidget.h \
    form.h

SOURCES += \
    myglwidget.cpp \
    main.cpp \
    form.cpp

QT += opengl

LIBS += -lglut -lGLU

FORMS += \
    form.ui

RESOURCES += \
    image.qrc
