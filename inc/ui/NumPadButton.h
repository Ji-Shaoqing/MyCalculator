/**
 * @file NumPadButton.h
 * @brief 计算器数字键盘按钮组件
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef NUMPADBUTTON_H
#define NUMPADBUTTON_H

#include "core/CalculationTypes.h"
#include <QPushButton>
#include <QPainter>

namespace Calculator {

/**
 * @class NumPadButton
 * @brief 自定义数字键盘按钮
 * 
 * 支持不同类型的按钮样式和动画效果，提供更好的用户体验。
 */
class NumPadButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(ButtonType buttonType READ buttonType WRITE setButtonType NOTIFY buttonTypeChanged)

public:
    explicit NumPadButton(QWidget *parent = nullptr);
    explicit NumPadButton(const QString &text, QWidget *parent = nullptr);
    
    // 属性访问器
    ButtonType buttonType() const { return m_buttonType; }
    void setButtonType(ButtonType type);
    
    /**
     * @brief 设置按钮对应的键盘快捷键
     * @param key 键盘键值
     */
    void setShortcutKey(int key);

protected:
    /**
     * @brief 重写绘制事件
     * @param event 绘制事件
     */
    void paintEvent(QPaintEvent *event) override;
    
    /**
     * @brief 重写鼠标按下事件
     * @param event 鼠标事件
     */
    void mousePressEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标释放事件
     * @param event 鼠标事件
     */
    void mouseReleaseEvent(QMouseEvent *event) override;
    
    /**
     * @brief 重写鼠标进入事件
     * @param event 进入事件
     */
    void enterEvent(QEvent *event) override;
    
    /**
     * @brief 重写鼠标离开事件
     * @param event 离开事件
     */
    void leaveEvent(QEvent *event) override;

signals:
    /**
     * @brief 按钮类型改变信号
     * @param type 新的按钮类型
     */
    void buttonTypeChanged(ButtonType type);

private:
    ButtonType m_buttonType;   ///< 按钮类型
    bool m_isPressed;          ///< 按下状态
    bool m_isHovered;          ///< 悬停状态
    int m_shortcutKey;         ///< 快捷键
};

} // namespace Calculator

#endif // NUMPADBUTTON_H