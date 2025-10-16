# Qt项目配置
QT += core gui widgets

CONFIG += c++17
CONFIG += warn_on
CONFIG += debug_and_release

# 项目信息
TARGET = Calculator
TEMPLATE = app
VERSION = 1.0.0

# 源代码路径
SOURCES += \
    src/main.cpp \
    src/core/calculatorengine.cpp \
    src/ui/mainwindow.cpp \
    src/ui/numpadbutton.cpp \
    src/ui/displaypanel.cpp \
    src/utils/settingsmanager.cpp

# 头文件路径
HEADERS += \
    include/core/calculatorengine.h \
    include/core/calculationtypes.h \
    include/ui/mainwindow.h \
    include/ui/numpadbutton.h \
    include/ui/displaypanel.h \
    include/utils/settingsmanager.h \
    include/utils/constants.h

# 资源文件
RESOURCES += resources/calculator.qrc

# 编译目录设置
win32:CONFIG(release, debug|release) {
    DESTDIR = build/release
    OBJECTS_DIR = build/release/obj
    MOC_DIR = build/release/moc
    RCC_DIR = build/release/rcc
    UI_DIR = build/release/ui
} else:win32:CONFIG(debug, debug|release) {
    DESTDIR = build/debug
    OBJECTS_DIR = build/debug/obj
    MOC_DIR = build/debug/moc
    RCC_DIR = build/debug/rcc
    UI_DIR = build/debug/ui
}

unix {
    DESTDIR = build
    OBJECTS_DIR = build/obj
    MOC_DIR = build/moc
    RCC_DIR = build/rcc
    UI_DIR = build/ui
}

# 编译选项
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

# 安装配置
target.path = $$[QT_INSTALL_EXAMPLES]/calculator
INSTALLS += target