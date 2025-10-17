/**
 * @file NumPadButton.cpp
 * @brief 计算器数字键盘按钮组件实现
 */

#include "../../inc/ui/NumPadButton.h"
#include "../../inc/utils/Constants.h"
#include <QMouseEvent>
#include <QPainter>

namespace Calculator {

NumPadButton::NumPadButton(QWidget *parent)
    : QPushButton(parent)
    , m_buttonType(ButtonType::Number)
    , m_isPressed(false)
    , m_isHovered(false)
    , m_shortcutKey(0)
{
    setObjectName("numPadButton");
    setFocusPolicy(Qt::NoFocus);
    
    // 设置字体
    QFont font = this->font();
    font.setPointSize(Constants::BUTTON_FONT_SIZE);
    font.setWeight(QFont::Medium);
    setFont(font);
    
    // 设置固定尺寸
    setMinimumSize(Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT);
}

NumPadButton::NumPadButton(const QString &text, QWidget *parent)
    : NumPadButton(parent)
{
    setText(text);
}

void NumPadButton::setButtonType(ButtonType type) {
    if (m_buttonType != type) {
        m_buttonType = type;
        update();
        emit buttonTypeChanged(type);
    }
}

void NumPadButton::setShortcutKey(int key) {
    m_shortcutKey = key;
}

void NumPadButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QRect rect = this->rect();
    
    // 根据按钮状态设置颜色
    QColor backgroundColor;
    QColor textColor = palette().color(QPalette::ButtonText);
    
    switch (m_buttonType) {
    case ButtonType::Number:
        backgroundColor = palette().color(QPalette::Button);
        if (m_isPressed) backgroundColor = palette().color(QPalette::Dark);
        else if (m_isHovered) backgroundColor = palette().color(QPalette::Midlight);
        break;
        
    case ButtonType::Operator:
        backgroundColor = palette().color(QPalette::Highlight);
        textColor = palette().color(QPalette::HighlightedText);
        if (m_isPressed) backgroundColor = palette().color(QPalette::Dark);
        else if (m_isHovered) backgroundColor = palette().color(QPalette::Light);
        break;
        
    case ButtonType::Equals:
        backgroundColor = QColor("#0078d7");
        textColor = Qt::white;
        if (m_isPressed) backgroundColor = QColor("#005a9e");
        else if (m_isHovered) backgroundColor = QColor("#106ebe");
        break;
        
    case ButtonType::Function:
        backgroundColor = palette().color(QPalette::AlternateBase);
        if (m_isPressed) backgroundColor = palette().color(QPalette::Dark);
        else if (m_isHovered) backgroundColor = palette().color(QPalette::Midlight);
        break;
        
    case ButtonType::Decimal:
        backgroundColor = palette().color(QPalette::Button);
        if (m_isPressed) backgroundColor = palette().color(QPalette::Dark);
        else if (m_isHovered) backgroundColor = palette().color(QPalette::Midlight);
        break;
    }
    
    // 绘制按钮背景
    painter.setBrush(backgroundColor);
    painter.setPen(QPen(palette().color(QPalette::Mid), 1));
    painter.drawRoundedRect(rect.adjusted(1, 1, -1, -1), 4, 4);
    
    // 绘制按钮文本
    painter.setPen(textColor);
    painter.drawText(rect, Qt::AlignCenter, text());
}

void NumPadButton::mousePressEvent(QMouseEvent *event) {
    m_isPressed = true;
    update();
    QPushButton::mousePressEvent(event);
}

void NumPadButton::mouseReleaseEvent(QMouseEvent *event) {
    m_isPressed = false;
    update();
    QPushButton::mouseReleaseEvent(event);
}

void NumPadButton::enterEvent(QEvent *event) {
    m_isHovered = true;
    update();
    QPushButton::enterEvent(event);
}

void NumPadButton::leaveEvent(QEvent *event) {
    m_isHovered = false;
    update();
    QPushButton::leaveEvent(event);
}

} // namespace Calculator