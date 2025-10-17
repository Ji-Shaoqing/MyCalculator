/**
 * @file DisplayPanel.cpp
 * @brief 计算器显示面板组件实现
 */

#include "../../inc/ui/DisplayPanel.h"
#include "../../inc/utils/Constants.h"
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>

namespace Calculator {

DisplayPanel::DisplayPanel(QWidget *parent)
    : QLineEdit(parent)
    , m_errorState(false)
{
    setObjectName("displayPanel");
    setReadOnly(true);
    setAlignment(Qt::AlignRight);
    setMaxLength(Constants::MAX_DISPLAY_LENGTH);
    
    // 设置字体
    QFont font = this->font();
    font.setPointSize(Constants::DISPLAY_FONT_SIZE);
    font.setWeight(QFont::Medium);
    setFont(font);
    
    // 设置样式
    setStyleSheet("border: none; background: transparent;");
}

void DisplayPanel::setErrorState(bool error) {
    if (m_errorState != error) {
        m_errorState = error;

        QPalette palette = this->palette();
        if (error) {
            palette.setColor(QPalette::Text, QColor("#e74c3c"));  // 红色文本
        } else {
            palette.setColor(QPalette::Text, QApplication::palette().color(QPalette::Text));  // 默认文本
        }
        setPalette(palette);

        update();
        emit errorStateChanged(error);
    }
}

void DisplayPanel::updateDisplay(const QString &text) {
    setText(text);
    setErrorState(false);
}

void DisplayPanel::clearDisplay() {
    clear();
    setErrorState(false);
}

void DisplayPanel::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制自定义边框
    QRect rect = this->rect();
    QPen pen;
    
    if (m_errorState) {
        pen.setColor(QColor("#e74c3c"));
        pen.setWidth(2);
    } else if (hasFocus()) {
        pen.setColor(palette().color(QPalette::Highlight));
        pen.setWidth(2);
    } else {
        pen.setColor(palette().color(QPalette::Mid));
        pen.setWidth(1);
    }
    
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(rect.adjusted(1, 1, -1, -1), 6, 6);
}

void DisplayPanel::keyPressEvent(QKeyEvent *event) {
    // 禁止直接编辑，但允许复制操作
    if (event->key() == Qt::Key_C && event->modifiers() == Qt::ControlModifier) {
        QLineEdit::keyPressEvent(event);
    } else {
        event->ignore();
    }
}

} // namespace Calculator