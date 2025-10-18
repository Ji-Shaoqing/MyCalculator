/**
 * @file MainWindow.h
 * @brief 计算器窗口功能
 * @author Jisq
 * @version 1.0
 * @date 2025.10.16
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../inc/core/CalculatorEngine.h"
#include "../../inc/utils/SettingsManager.h"
#include "DisplayPanel.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>

namespace Calculator {

/**
 * @class MainWindow
 * @brief 计算器主窗口类
 * 负责管理计算器的UI组件和用户交互逻辑。
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 重写键盘按键事件
    void keyPressEvent(QKeyEvent *event) override;
    
    // 重写窗口关闭事件
    void closeEvent(QCloseEvent *event) override;

private slots:
    // 计算器按钮点击槽函数
    void onDigitClicked();

    // 其他按钮点击槽函数
    void onOperatorClicked();
    
    // 其他按钮点击槽函数
    void onFunctionClicked();
    
    // 等号按钮点击槽函数
    void onEqualsClicked();
    
    // 小数点按钮点击槽函数
    void onDecimalClicked();
    
    // 显示内容改变槽函数
    void onDisplayChanged(const QString &text);
    
    // 处理计算错误槽函数
    void onErrorOccurred(ErrorType errorType);

    // 处理计算器状态更新槽函数
    void onEngineStateUpdated(const CalculatorState& state);

private:
    // 初始化UI组件
    void setupUI();
    
    // 连接信号和槽
    void setupConnections();
    
    // 加载和保存设置
    void loadStyleSheet();
    
    // 保存和恢复窗口状态
    void saveWindowState();
    void restoreWindowState();
    
    // 设置按钮样式
    void setupButtonStyles();

private:
    QWidget *m_centralWidget;              // 中央窗口部件
    DisplayPanel *m_displayPanel;             // 计算结果显示面板
    CalculatorEngine *m_engine;            // 计算器引擎
    QMap<QString, QPushButton*> m_buttons; // 按钮映射表
};

}

#endif
