/**
 * @file main.cpp
 * @brief 计算器应用程序入口
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#include "../inc/ui/MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

/**
 * @brief 设置应用程序属性
 * @param app QApplication实例
 */
void setupApplication(QApplication &app)
{
    // 设置应用程序信息
    app.setApplicationName("Calculator");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("QtCalculator");
    app.setOrganizationDomain("qtcalculator.example.com");
}

int main(int argc, char *argv[])
{
    // 在创建 QApplication 之前设置高DPI属性
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // 创建应用程序实例
    QApplication app(argc, argv);
    
    // 设置应用程序
    setupApplication(app);
    
    try {
        // 创建并显示主窗口
        Calculator::MainWindow window;
        window.show();
        
        // 执行应用程序主循环
        return app.exec();
        
    } catch (const std::exception &e) {
        qCritical() << "应用程序异常:" << e.what();
        return -1;
    } catch (...) {
        qCritical() << "未知应用程序异常";
        return -1;
    }
}
