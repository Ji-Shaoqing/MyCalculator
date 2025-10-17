/**
 * @file CalculatorEngine.h
 * @brief 计算器核心引擎
 * @author Jisq
 * @version 1.0
 * @date 2025.10.16
 */

#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include "CalculationTypes.h"
#include <QObject>
#include <QString>

namespace Calculator {

/**
 * @class CalculatorEngine
 * @brief 计算器核心逻辑引擎
 * 负责处理所有计算逻辑，包括四则运算、错误处理、状态管理等。
 * 采用MVC模式，与界面层完全分离。
 */
class CalculatorEngine : public QObject {
    Q_OBJECT

public:
    explicit CalculatorEngine(QObject *parent = nullptr);
    ~CalculatorEngine() = default;

    // 状态访问
    CalculatorState getState() const { return m_state; }
    QString getDisplayText() const;
    bool hasError() const { return m_state.error != ErrorType::NoError; }

public slots:
    // 处理数字输入槽函数
    void inputDigit(int digit);
    
    // 处理运算符输入槽函数
    void inputOperator(Operator op);
    
    // 处理等号输入槽函数
    void inputEquals();
    
    // 处理小数点输入槽函数
    void inputDecimal();
    
    // 清除当前输入槽函数
    void clearEntry();
    
    // 全部清除槽函数
    void clearAll();
    
    // 退格操作槽函数
    void backspace();
    
    // 改变正负号槽函数
    void changeSign();

signals:
    // 显示内容改变信号
    void displayChanged(const QString &displayText);
    
    // 错误发生信号
    void errorOccurred(ErrorType errorType);
    
    // 状态更新信号
    void stateUpdated(const CalculatorState &state);

private:
    // 执行计算
    void calculate();
    
    // 重置计算器状态
    void reset();
    
    // 设置错误状态
    void setError(ErrorType error);
    
    // 格式化数字为字符串
    QString formatNumber(double value) const;
    
    // 检查是否溢出
    bool checkOverflow(double value) const;

private:
    CalculatorState m_state;        // 计算器状态
    QString m_currentInput;         // 当前输入字符串
    bool m_hasDecimal;              // 是否已输入小数点
};

} // namespace Calculator

#endif // CALCULATORENGINE_H