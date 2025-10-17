/**
 * @file NumPadButton.h
 * @brief 计算器数字键盘按钮组件
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef NUMPADBUTTON_H
#define NUMPADBUTTON_H

#include "../core/CalculationTypes.h"
#include <QPushButton>
#include <QPainter>

namespace Calculator {

/**
 * @class NumPadButton
 * @brief 自定义数字键盘按钮
 * 
 * 支持不同类型的按钮样式和动画效果，提供更好的用户体验。
 */
class NumPadButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(ButtonType buttonType READ buttonType WRITE setButtonType NOTIFY buttonTypeChanged)

public:
    explicit NumPadButton(QWidget *parent = nullptr);
    explicit NumPadButton(const QString &text, QWidget *parent = nullptr);
    
    // 属性访问器
    ButtonType buttonType() const { return m_buttonType; }
    void setButtonType(ButtonType type);
    
    // 设置按钮对应的键盘快捷键
    void setShortcutKey(int key);

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;

    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;

    // 重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 重写鼠标进入事件
    void enterEvent(QEvent *event) override;

    // 重写鼠标离开事件
    void leaveEvent(QEvent *event) override;

signals:
    // 按钮类型改变信号
    void buttonTypeChanged(ButtonType type);

private:
    ButtonType m_buttonType;   // 按钮类型
    bool m_isPressed;          // 按下状态
    bool m_isHovered;          // 悬停状态
    int m_shortcutKey;         // 快捷键
};

} // namespace Calculator

#endif // NUMPADBUTTON_H