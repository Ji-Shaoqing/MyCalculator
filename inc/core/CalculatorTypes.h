/** 
 * @file CalculationtTypes.h
 * @brief 计算类型定义和枚举
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef CALCULATIONTYPES_H
#define CALCULATIONTYPES_H

#include <QString>
#include <QMetaType>

namespace Calculator {

/**
 * @brief 支持的数学运算符
 */
enum class Operator {
    None,       ///< 无运算符
    Add,        ///< 加法 +
    Subtract,   ///< 减法 -
    Multiply,   ///< 乘法 ×
    Divide,     ///< 除法 ÷
    Equals      ///< 等号 =
};

/**
 * @brief 计算错误类型
 */
enum class ErrorType {
    NoError,        ///< 无错误
    DivisionByZero, ///< 除零错误
    Overflow,       ///< 溢出错误
    InvalidInput,   ///< 无效输入
    SyntaxError     ///< 语法错误
};

/**
 * @brief 计算器状态
 */
struct CalculatorState {
    double currentValue;    ///< 当前值
    double storedValue;     ///< 存储值
    Operator pendingOperator; ///< 待处理运算符
    bool waitingForOperand; ///< 等待操作数输入
    ErrorType error;        ///< 错误状态
    
    CalculatorState() 
        : currentValue(0.0)
        , storedValue(0.0)
        , pendingOperator(Operator::None)
        , waitingForOperand(true)
        , error(ErrorType::NoError) {}
};

/**
 * @brief 按钮类型
 */
enum class ButtonType {
    Number,     ///< 数字按钮 0-9
    Operator,   ///< 运算符按钮 + - × ÷
    Equals,     ///< 等号按钮 =
    Function,   ///< 功能按钮 CE C ⌫
    Decimal     ///< 小数点按钮 .
};

} // namespace Calculator

// 注册元类型以便在信号槽中使用
Q_DECLARE_METATYPE(Calculator::Operator)
Q_DECLARE_METATYPE(Calculator::ErrorType)

#endif // CALCULATIONTYPES_H