/**
 * @file CalculatorEngine.cpp
 * @brief 计算器核心引擎实现
 */

#include "../../inc/core/CalculatorEngine.h"
#include "../../inc/utils/Constants.h"
#include <cmath>
#include <limits>

namespace Calculator {

CalculatorEngine::CalculatorEngine(QObject *parent)
    : QObject(parent)
    , m_hasDecimal(false)
{
    reset();
}

QString CalculatorEngine::getDisplayText() const
{
    if (m_state.error != ErrorType::NoError) {
        switch (m_state.error) {
        case ErrorType::DivisionByZero:
            return tr("错误: 除零");
        case ErrorType::Overflow:
            return tr("错误: 溢出");
        case ErrorType::InvalidInput:
            return tr("错误: 无效输入");
        case ErrorType::SyntaxError:
            return tr("错误: 语法错误");
        default:
            return tr("错误");
        }
    }
    
    if (m_state.waitingForOperand) {
        return formatNumber(m_state.storedValue);
    }
    
    return m_currentInput.isEmpty() ? "0" : m_currentInput;
}

void CalculatorEngine::inputDigit(int digit)
{
    if (m_state.error != ErrorType::NoError) {
        reset();
    }
    
    if (m_state.waitingForOperand) {
        m_currentInput = QString::number(digit);
        m_state.waitingForOperand = false;
        m_hasDecimal = false;
    } else {
        if (m_currentInput == "0") {
            m_currentInput = QString::number(digit);
        } else {
            m_currentInput += QString::number(digit);
        }
    }
    
    m_state.currentValue = m_currentInput.toDouble();
    emit displayChanged(getDisplayText());
}

void CalculatorEngine::inputOperator(Operator op)
{
    if (m_state.error != ErrorType::NoError) {
        return;
    }
    
    if (!m_state.waitingForOperand) {
        calculate();
    }
    
    if (m_state.error == ErrorType::NoError) {
        m_state.pendingOperator = op;
        m_state.storedValue = m_state.currentValue;
        m_state.waitingForOperand = true;
        m_hasDecimal = false;
        emit stateUpdated(m_state);
    }
}

void CalculatorEngine::inputEquals()
{
    if (m_state.error != ErrorType::NoError || 
        m_state.pendingOperator == Operator::None) {
        return;
    }
    
    if (!m_state.waitingForOperand) {
        calculate();
    }
    
    if (m_state.error == ErrorType::NoError) {
        m_state.pendingOperator = Operator::None;
        m_state.waitingForOperand = true;
        emit stateUpdated(m_state);
    }
}

void CalculatorEngine::inputDecimal()
{
    if (m_state.error != ErrorType::NoError) {
        reset();
    }
    
    if (m_state.waitingForOperand) {
        m_currentInput = "0";
        m_state.waitingForOperand = false;
        m_hasDecimal = false;
    }
    
    if (!m_hasDecimal) {
        m_currentInput += ".";
        m_hasDecimal = true;
        emit displayChanged(getDisplayText());
    }
}

void CalculatorEngine::clearEntry()
{
    m_currentInput.clear();
    m_state.currentValue = 0.0;
    m_hasDecimal = false;
    m_state.waitingForOperand = true;
    emit displayChanged(getDisplayText());
}

void CalculatorEngine::clearAll()
{
    reset();
    emit displayChanged(getDisplayText());
    emit stateUpdated(m_state);
}

void CalculatorEngine::backspace()
{
    if (m_state.waitingForOperand || m_state.error != ErrorType::NoError) {
        return;
    }
    
    if (m_currentInput.length() > 1) {
        if (m_currentInput.endsWith('.')) {
            m_hasDecimal = false;
        }
        m_currentInput.chop(1);
        m_state.currentValue = m_currentInput.toDouble();
    } else {
        m_currentInput.clear();
        m_state.currentValue = 0.0;
        m_state.waitingForOperand = true;
    }
    
    emit displayChanged(getDisplayText());
}

void CalculatorEngine::changeSign()
{
    if (m_state.error != ErrorType::NoError) {
        return;
    }
    
    if (m_state.waitingForOperand) {
        m_state.storedValue = -m_state.storedValue;
        m_state.currentValue = m_state.storedValue;
    } else {
        m_state.currentValue = -m_state.currentValue;
        m_currentInput = formatNumber(m_state.currentValue);
    }
    
    emit displayChanged(getDisplayText());
}

void CalculatorEngine::calculate()
{
    double result = m_state.storedValue;
    double operand = m_state.currentValue;
    
    switch (m_state.pendingOperator) {
    case Operator::Add:
        result += operand;
        break;
    case Operator::Subtract:
        result -= operand;
        break;
    case Operator::Multiply:
        result *= operand;
        break;
    case Operator::Divide:
        if (std::abs(operand) < std::numeric_limits<double>::epsilon()) {
            setError(ErrorType::DivisionByZero);
            return;
        }
        result /= operand;
        break;
    default:
        return;
    }
    
    if (checkOverflow(result)) {
        setError(ErrorType::Overflow);
        return;
    }
    
    m_state.currentValue = result;
    m_state.storedValue = result;
    m_currentInput = formatNumber(result);
    m_state.waitingForOperand = true;
}

void CalculatorEngine::reset()
{
    m_state = CalculatorState();
    m_currentInput.clear();
    m_hasDecimal = false;
}

void CalculatorEngine::setError(ErrorType error)
{
    m_state.error = error;
    emit errorOccurred(error);
    emit displayChanged(getDisplayText());
}

QString CalculatorEngine::formatNumber(double value) const
{
    QString text = QString::number(value, 'g', Constants::MAX_DISPLAY_LENGTH);
    
    // 移除不必要的尾随零和小数点
    if (text.contains('.')) {
        while (text.endsWith('0')) {
            text.chop(1);
        }
        if (text.endsWith('.')) {
            text.chop(1);
        }
    }
    
    return text;
}

bool CalculatorEngine::checkOverflow(double value) const
{
    return std::isinf(value) || std::isnan(value) ||
           std::abs(value) > Constants::MAX_CALCULATION_VALUE;
}

} // namespace Calculator