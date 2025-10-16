/**
 * @file MainWindow.cpp
 * @brief 计算器主窗口实现
 */

#include "../../inc/ui/MainWindow.h"
#include "../../inc/utils/Constants.h"
#include "../../inc/utils/SettingsManager.h"
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QFile>
#include <QDebug>

namespace Calculator {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_displayPanel(nullptr)
    , m_buttonLayout(nullptr)
    , m_engine(new CalculatorEngine(this))
{
    setupUI();
    setupConnections();
    loadStyleSheet();
    
    setWindowTitle(tr("计算器"));
    setFixedSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
}

MainWindow::~MainWindow()
{
    // 自动清理Qt对象
}

void MainWindow::setupUI()
{
    // 创建中央部件
    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName("centralWidget");
    setCentralWidget(m_centralWidget);
    
    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setSpacing(Constants::LAYOUT_SPACING);
    mainLayout->setContentsMargins(
        Constants::LAYOUT_MARGIN,
        Constants::LAYOUT_MARGIN,
        Constants::LAYOUT_MARGIN,
        Constants::LAYOUT_MARGIN
    );
    
    // 创建显示面板
    m_displayPanel = new DisplayPanel();
    mainLayout->addWidget(m_displayPanel);
    
    // 创建按钮网格布局
    m_buttonLayout = new QGridLayout();
    m_buttonLayout->setSpacing(Constants::LAYOUT_SPACING);
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    
    // 第一行：功能按钮
    m_buttonLayout->addWidget(createFunctionButton("clearEntry", "CE"), 0, 0);
    m_buttonLayout->addWidget(createFunctionButton("clearAll", "C"), 0, 1);
    m_buttonLayout->addWidget(createFunctionButton("backspace", "⌫"), 0, 2);
    m_buttonLayout->addWidget(createOperatorButton(Operator::Divide, "÷"), 0, 3);
    
    // 第二行：数字7-9和乘号
    m_buttonLayout->addWidget(createDigitButton(7), 1, 0);
    m_buttonLayout->addWidget(createDigitButton(8), 1, 1);
    m_buttonLayout->addWidget(createDigitButton(9), 1, 2);
    m_buttonLayout->addWidget(createOperatorButton(Operator::Multiply, "×"), 1, 3);
    
    // 第三行：数字4-6和减号
    m_buttonLayout->addWidget(createDigitButton(4), 2, 0);
    m_buttonLayout->addWidget(createDigitButton(5), 2, 1);
    m_buttonLayout->addWidget(createDigitButton(6), 2, 2);
    m_buttonLayout->addWidget(createOperatorButton(Operator::Subtract, "-"), 2, 3);
    
    // 第四行：数字1-3和加号
    m_buttonLayout->addWidget(createDigitButton(1), 3, 0);
    m_buttonLayout->addWidget(createDigitButton(2), 3, 1);
    m_buttonLayout->addWidget(createDigitButton(3), 3, 2);
    m_buttonLayout->addWidget(createOperatorButton(Operator::Add, "+"), 3, 3);
    
    // 第五行：数字0、小数点、等号
    m_buttonLayout->addWidget(createDigitButton(0), 4, 0, 1, 2); // 跨2列
    m_buttonLayout->addWidget(createFunctionButton("decimal", "."), 4, 2);
    
    // 等号按钮（跨2行）
    NumPadButton *equalsButton = new NumPadButton("=");
    equalsButton->setButtonType(ButtonType::Equals);
    connect(equalsButton, &NumPadButton::clicked, this, &MainWindow::onEqualsClicked);
    m_buttonLayout->addWidget(equalsButton, 3, 4, 2, 1); // 从第3行开始，跨2行
    m_buttons["equals"] = equalsButton;
    
    mainLayout->addLayout(m_buttonLayout);
}

void MainWindow::setupConnections()
{
    // 连接计算引擎信号
    connect(m_engine, &CalculatorEngine::displayChanged,
            m_displayPanel, &DisplayPanel::updateDisplay);
    connect(m_engine, &CalculatorEngine::errorOccurred,
            this, &MainWindow::onErrorOccurred);
    
    // 初始显示
    m_displayPanel->updateDisplay(m_engine->getDisplayText());
}

NumPadButton* MainWindow::createDigitButton(int digit)
{
    QString digitStr = QString::number(digit);
    NumPadButton *button = new NumPadButton(digitStr);
    button->setButtonType(ButtonType::Number);
    
    // 设置键盘快捷键
    int key = Qt::Key_0 + digit;
    button->setShortcutKey(key);
    m_keyboardShortcuts[key] = button;
    
    connect(button, &NumPadButton::clicked, this, &MainWindow::onDigitClicked);
    m_buttons[digitStr] = button;
    
    return button;
}

NumPadButton* MainWindow::createOperatorButton(Operator op, const QString &text)
{
    NumPadButton *button = new NumPadButton(text);
    button->setButtonType(ButtonType::Operator);
    button->setProperty("operator", QVariant::fromValue(op));
    
    // 设置键盘快捷键
    int key = 0;
    if (text == "+") key = Qt::Key_Plus;
    else if (text == "-") key = Qt::Key_Minus;
    else if (text == "×") key = Qt::Key_Asterisk;
    else if (text == "÷") key = Qt::Key_Slash;
    
    if (key != 0) {
        button->setShortcutKey(key);
        m_keyboardShortcuts[key] = button;
    }
    
    connect(button, &NumPadButton::clicked, this, &MainWindow::onOperatorClicked);
    m_buttons[text] = button;
    
    return button;
}

NumPadButton* MainWindow::createFunctionButton(const QString &function, const QString &text)
{
    NumPadButton *button = new NumPadButton(text);
    button->setButtonType(ButtonType::Function);
    button->setProperty("function", function);
    
    // 设置键盘快捷键
    int key = 0;
    if (function == "backspace") key = Qt::Key_Backspace;
    else if (function == "clearAll") key = Qt::Key_Escape;
    else if (function == "decimal") key = Qt::Key_Period;
    
    if (key != 0) {
        button->setShortcutKey(key);
        m_keyboardShortcuts[key] = button;
    }
    
    connect(button, &NumPadButton::clicked, this, &MainWindow::onFunctionClicked);
    m_buttons[function] = button;
    
    return button;
}

void MainWindow::onDigitClicked()
{
    NumPadButton *button = qobject_cast<NumPadButton*>(sender());
    if (button) {
        int digit = button->text().toInt();
        m_engine->inputDigit(digit);
    }
}

void MainWindow::onOperatorClicked()
{
    NumPadButton *button = qobject_cast<NumPadButton*>(sender());
    if (button) {
        Operator op = button->property("operator").value<Operator>();
        m_engine->inputOperator(op);
    }
}

void MainWindow::onFunctionClicked()
{
    NumPadButton *button = qobject_cast<NumPadButton*>(sender());
    if (button) {
        QString function = button->property("function").toString();
        
        if (function == "clearEntry") {
            m_engine->clearEntry();
        } else if (function == "clearAll") {
            m_engine->clearAll();
        } else if (function == "backspace") {
            m_engine->backspace();
        }
    }
}

void MainWindow::onEqualsClicked()
{
    m_engine->inputEquals();
}

void MainWindow::onDecimalClicked()
{
    m_engine->inputDecimal();
}

void MainWindow::onDisplayChanged(const QString &text)
{
    // 显示更新由信号槽自动处理
    Q_UNUSED(text);
}

void MainWindow::onErrorOccurred(ErrorType errorType)
{
    Q_UNUSED(errorType);
    m_displayPanel->setErrorState(true);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    handleKeyboardInput(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    m_displayPanel->setFocus();
}

void MainWindow::handleKeyboardInput(QKeyEvent *event)
{
    int key = event->key();
    QString keyText = event->text();
    
    // 检查快捷键映射
    if (m_keyboardShortcuts.contains(key)) {
        m_keyboardShortcuts[key]->click();
        event->accept();
        return;
    }
    
    // 处理其他键盘输入
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Equal:
        m_engine->inputEquals();
        event->accept();
        break;
        
    case Qt::Key_Comma:
        // 将逗号映射为小数点
        m_engine->inputDecimal();
        event->accept();
        break;
        
    default:
        // 处理数字直接输入（非小键盘）
        if (key >= Qt::Key_0 && key <= Qt::Key_9) {
            m_engine->inputDigit(key - Qt::Key_0);
            event->accept();
        } else {
            QMainWindow::keyPressEvent(event);
        }
    }
}

void MainWindow::loadStyleSheet()
{
    SettingsManager &settings = SettingsManager::instance();
    QString stylePath = settings.getStylePreference();
    
    QFile styleFile(stylePath);
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
        qDebug() << "样式表加载成功:" << stylePath;
    } else {
        qWarning() << "无法加载样式表:" << stylePath;
        // 使用内置的默认样式
        QString defaultStyle = R"(
            QMainWindow { background-color: #f0f0f0; }
            #centralWidget { background-color: white; border: 1px solid #ccc; padding: 8px; }
            DisplayPanel { 
                background-color: white; border: 2px solid #c0c0c0; border-radius: 4px;
                font-size: 24px; padding: 8px 12px; 
            }
        )";
        qApp->setStyleSheet(defaultStyle);
    }
}

} // namespace Calculator