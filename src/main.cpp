/**
 * @file main.cpp
 * @brief 计算器应用程序入口
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#include "ui/Mainwindow.h"
#include "utils/Settingsmanager.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

/**
 * @brief 加载应用程序翻译
 * @param app QApplication实例
 */
void loadTranslations(QApplication &app)
{
    SettingsManager &settings = SettingsManager::instance();
    QString language = settings.getLanguage();
    
    QTranslator *qtTranslator = new QTranslator(&app);
    QTranslator *appTranslator = new QTranslator(&app);
    
    // 加载Qt标准对话框翻译
    QString qtTranslationsPath = QLibraryInfo::path(QLibraryInfo::TranslationsPath);
    if (qtTranslator->load("qt_" + language, qtTranslationsPath)) {
        app.installTranslator(qtTranslator);
    }
    
    // 加载应用程序翻译
    QString appTranslationsPath = ":/translations";
    if (appTranslator->load("calculator_" + language, appTranslationsPath)) {
        app.installTranslator(appTranslator);
    }
}

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
    
    // 设置应用程序属性
    app.setAttribute(Qt::AA_EnableHighDpiScaling, true);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
}

int main(int argc, char *argv[])
{
    // 创建应用程序实例
    QApplication app(argc, argv);
    
    // 设置应用程序
    setupApplication(app);
    
    // 加载翻译
    loadTranslations(app);
    
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