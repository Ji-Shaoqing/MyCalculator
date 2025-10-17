/**
 * @file DisplayPanel.h
 * @brief 计算器显示面板组件
 * @author Jisq
 * @version 1.0
 * @date 2025.10.16
 */

#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

#include <QLineEdit>
#include <QPainter>

namespace Calculator {

/**
 * @class DisplayPanel
 * @brief 自定义显示面板组件
 * 负责显示计算器的输入和结果，支持错误状态显示和自定义绘制。
 */
class DisplayPanel : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(bool errorState READ errorState WRITE setErrorState NOTIFY errorStateChanged)

public:
    explicit DisplayPanel(QWidget *parent = nullptr);
    
    // 属性访问器
    bool errorState() const { return m_errorState; }
    void setErrorState(bool error);
    
public slots:
    // 更新显示内容槽函数
    void updateDisplay(const QString &text);
    
    // 清除显示内容槽函数
    void clearDisplay();

signals:
    // 错误状态改变信号
    void errorStateChanged(bool errorState);

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;
    
    // 重写键盘事件
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool m_errorState;   // 错误状态标志
};

} // namespace Calculator

#endif // DISPLAYPANEL_H