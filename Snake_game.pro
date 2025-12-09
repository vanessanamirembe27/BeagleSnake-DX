QT += core gui widgets

# Set the name of the final executable file.
TARGET = BeagleSnake-DX

# Specify that this is an application project.
TEMPLATE = app

# Add all your source files (.cpp).
SOURCES += \
    src/main.cpp \
    src/snakegame.cpp \
    src/gameview.cpp \
    src/gamewindow.cpp \
        src/tonebuzzer.cpp   

# Add all your header files (.h).
HEADERS += \
    src/snakegame.h \
    src/gameview.h \
    src/config.h \
    src/gamewindow.h \
    src/tonebuzzer.h

#resource files
RESOURCES += \
    resources.qrc

