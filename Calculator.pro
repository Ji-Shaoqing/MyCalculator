# Qt项目配置
QT += core gui widgets

CONFIG += c++11
CONFIG += warn_on
CONFIG += debug_and_release

# 项目信息
TARGET = Calculator
TEMPLATE = app
VERSION = 1.0.0

# 源代码路径
SOURCES += \
    src/main.cpp \
    src/core/CalculatorEngine.cpp \
    src/ui/MainWindow.cpp \
    src/ui/NumPadButton.cpp \
    src/ui/DisplayPanel.cpp \
    src/utils/SettingsManager.cpp

# 头文件路径
HEADERS += \
    inc/core/CalculatorEngine.h \
    inc/core/CalculationTypes.h \
    inc/ui/MainWindow.h \
    inc/ui/NumPadButton.h \
    inc/ui/DisplayPanel.h \
    inc/utils/Constants.h \
    inc/utils/SettingsManager.h

# 资源文件
RESOURCES += calculator.qrc

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
