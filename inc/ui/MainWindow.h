/**
 * @file MainWindow.h
 * @brief 计算器主窗口
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../core/CalculatorEngine.h"
#include "DisplayPanel.h"
#include "NumPadButton.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMap>

namespace Calculator {

/**
 * @class MainWindow
 * @brief 计算器主窗口类
 * 
 * 负责界面布局、用户交互和与计算引擎的通信。
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /**
     * @brief 重写键盘事件处理
     * @param event 键盘事件
     */
    void keyPressEvent(QKeyEvent *event) override;
    
    /**
     * @brief 重写窗口显示事件
     * @param event 显示事件
     */
    void showEvent(QShowEvent *event) override;

private slots:
    /**
     * @brief 处理数字按钮点击
     */
    void onDigitClicked();
    
    /**
     * @brief 处理运算符按钮点击
     */
    void onOperatorClicked();
    
    /**
     * @brief 处理功能按钮点击
     */
    void onFunctionClicked();
    
    /**
     * @brief 处理等号按钮点击
     */
    void onEqualsClicked();
    
    /**
     * @brief 处理小数点按钮点击
     */
    void onDecimalClicked();
    
    /**
     * @brief 更新显示内容
     * @param text 显示文本
     */
    void onDisplayChanged(const QString &text);
    
    /**
     * @brief 处理计算错误
     * @param errorType 错误类型
     */
    void onErrorOccurred(ErrorType errorType);

private:
    /**
     * @brief 初始化用户界面
     */
    void setupUI();
    
    /**
     * @brief 初始化信号槽连接
     */
    void setupConnections();
    
    /**
     * @brief 创建数字按钮
     * @param digit 数字 (0-9)
     * @return 创建的按钮指针
     */
    NumPadButton* createDigitButton(int digit);
    
    /**
     * @brief 创建运算符按钮
     * @param op 运算符
     * @param text 显示文本
     * @return 创建的按钮指针
     */
    NumPadButton* createOperatorButton(Operator op, const QString &text);
    
    /**
     * @brief 创建功能按钮
     * @param function 功能标识
     * @param text 显示文本
     * @return 创建的按钮指针
     */
    NumPadButton* createFunctionButton(const QString &function, const QString &text);
    
    /**
     * @brief 处理键盘输入映射
     * @param event 键盘事件
     */
    void handleKeyboardInput(QKeyEvent *event);
    
    /**
     * @brief 加载应用程序样式
     */
    void loadStyleSheet();

private:
    // UI 组件
    QWidget *m_centralWidget;          ///< 中央部件
    DisplayPanel *m_displayPanel;      ///< 显示面板
    QGridLayout *m_buttonLayout;       ///< 按钮布局
    
    // 核心组件
    CalculatorEngine *m_engine;        ///< 计算引擎
    
    // 按钮映射
    QMap<QString, NumPadButton*> m_buttons;        ///< 按钮映射表
    QMap<int, NumPadButton*> m_keyboardShortcuts;  ///< 键盘快捷键映射
};

} // namespace Calculator

#endif // MAINWINDOW_H