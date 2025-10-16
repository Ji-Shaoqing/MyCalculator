/**
 * @file CalculatorEngine.h
 * @brief 计算器核心引擎
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef CALCULATORENGINE_H
#define CALCULATORENGINE_H

#include "calculationtypes.h"
#include <QObject>
#include <QString>

namespace Calculator {

/**
 * @class CalculatorEngine
 * @brief 计算器核心逻辑引擎
 * 
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
    /**
     * @brief 处理数字输入
     * @param digit 输入的数字 (0-9)
     */
    void inputDigit(int digit);
    
    /**
     * @brief 处理运算符输入
     * @param op 运算符类型
     */
    void inputOperator(Operator op);
    
    /**
     * @brief 处理等号输入
     */
    void inputEquals();
    
    /**
     * @brief 处理小数点输入
     */
    void inputDecimal();
    
    /**
     * @brief 清除当前输入
     */
    void clearEntry();
    
    /**
     * @brief 全部清除
     */
    void clearAll();
    
    /**
     * @brief 退格操作
     */
    void backspace();
    
    /**
     * @brief 改变正负号
     */
    void changeSign();

signals:
    /**
     * @brief 显示内容改变信号
     * @param displayText 显示文本
     */
    void displayChanged(const QString &displayText);
    
    /**
     * @brief 错误状态改变信号
     * @param errorType 错误类型
     */
    void errorOccurred(ErrorType errorType);
    
    /**
     * @brief 状态更新信号
     * @param state 当前计算器状态
     */
    void stateUpdated(const CalculatorState &state);

private:
    /**
     * @brief 执行计算
     */
    void calculate();
    
    /**
     * @brief 重置计算器状态
     */
    void reset();
    
    /**
     * @brief 设置错误状态
     * @param error 错误类型
     */
    void setError(ErrorType error);
    
    /**
     * @brief 格式化数字显示
     * @param value 数值
     * @return 格式化后的字符串
     */
    QString formatNumber(double value) const;
    
    /**
     * @brief 检查数值是否溢出
     * @param value 待检查的数值
     * @return 是否溢出
     */
    bool checkOverflow(double value) const;

private:
    CalculatorState m_state;        ///< 计算器状态
    QString m_currentInput;         ///< 当前输入字符串
    bool m_hasDecimal;              ///< 是否已输入小数点
};

} // namespace Calculator

#endif // CALCULATORENGINE_H