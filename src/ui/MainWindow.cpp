/**
 * @file MainWindow.cpp
 * @brief 窗口功能实现
 */


#include "../../inc/ui/MainWindow.h"
#include "../../inc/utils/SettingsManager.h"
#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QFile>
#include <QDebug>
#include <QCloseEvent>

namespace Calculator {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_displayPanel(nullptr)
    , m_engine(new CalculatorEngine(this))
{
    setupUI();
    setupConnections();
    loadStyleSheet();
    restoreWindowState();

    setWindowTitle("计算器");
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    m_centralWidget->setObjectName("centralWidget");
    setCentralWidget(m_centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    // 显示面板
    m_displayPanel = new QLineEdit();
    m_displayPanel->setObjectName("displayPanel");
    m_displayPanel->setReadOnly(true);
    m_displayPanel->setAlignment(Qt::AlignRight);
    m_displayPanel->setText("0");
    m_displayPanel->setMaxLength(15);

    QFont font = m_displayPanel->font();
    font.setPointSize(24);
    font.setWeight(QFont::Medium);
    m_displayPanel->setFont(font);

    mainLayout->addWidget(m_displayPanel);

    // 按钮网格
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(4);

    // 第一行：功能按钮
    m_buttons["CE"] = new QPushButton("CE");
    m_buttons["C"] = new QPushButton("C");
    m_buttons["backspace"] = new QPushButton("⌫");
    m_buttons["divide"] = new QPushButton("÷");
    gridLayout->addWidget(m_buttons["CE"], 0, 0);
    gridLayout->addWidget(m_buttons["C"], 0, 1);
    gridLayout->addWidget(m_buttons["backspace"], 0, 2);
    gridLayout->addWidget(m_buttons["divide"], 0, 3);

    // 第二行：数字7-9和乘号
    m_buttons["7"] = new QPushButton("7");
    m_buttons["8"] = new QPushButton("8");
    m_buttons["9"] = new QPushButton("9");
    m_buttons["multiply"] = new QPushButton("×");
    gridLayout->addWidget(m_buttons["7"], 1, 0);
    gridLayout->addWidget(m_buttons["8"], 1, 1);
    gridLayout->addWidget(m_buttons["9"], 1, 2);
    gridLayout->addWidget(m_buttons["multiply"], 1, 3);

    // 第三行：数字4-6和减号
    m_buttons["4"] = new QPushButton("4");
    m_buttons["5"] = new QPushButton("5");
    m_buttons["6"] = new QPushButton("6");
    m_buttons["subtract"] = new QPushButton("-");
    gridLayout->addWidget(m_buttons["4"], 2, 0);
    gridLayout->addWidget(m_buttons["5"], 2, 1);
    gridLayout->addWidget(m_buttons["6"], 2, 2);
    gridLayout->addWidget(m_buttons["subtract"], 2, 3);

    // 第四行：数字1-3和加号
    m_buttons["1"] = new QPushButton("1");
    m_buttons["2"] = new QPushButton("2");
    m_buttons["3"] = new QPushButton("3");
    m_buttons["add"] = new QPushButton("+");
    gridLayout->addWidget(m_buttons["1"], 3, 0);
    gridLayout->addWidget(m_buttons["2"], 3, 1);
    gridLayout->addWidget(m_buttons["3"], 3, 2);
    gridLayout->addWidget(m_buttons["add"], 3, 3);

    // 第五行：数字0、小数点、等号
    m_buttons["0"] = new QPushButton("0");
    m_buttons["decimal"] = new QPushButton(".");
    m_buttons["equals"] = new QPushButton("=");
    gridLayout->addWidget(m_buttons["0"], 4, 0, 1, 2); // 跨2列
    gridLayout->addWidget(m_buttons["decimal"], 4, 2);
    gridLayout->addWidget(m_buttons["equals"], 4, 3);

    mainLayout->addLayout(gridLayout);

    // 设置按钮样式
    setupButtonStyles();
}

void MainWindow::setupButtonStyles()
{
    // 为不同类型的按钮设置不同的样式
    for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it) {
        QPushButton *button = it.value();
        QString key = it.key();

        if (key >= "0" && key <= "9") {
            // 数字按钮
            button->setStyleSheet(
                "QPushButton {"
                "    background-color: #f8f9fa;"
                "    border: 1px solid #dee2e6;"
                "    border-radius: 4px;"
                "    font-size: 16px;"
                "    font-weight: 500;"
                "}"
                "QPushButton:hover {"
                "    background-color: #e9ecef;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #dee2e6;"
                "}"
            );
        } else if (key == "add" || key == "subtract" || key == "multiply" || key == "divide") {
            // 运算符按钮
            button->setStyleSheet(
                "QPushButton {"
                "    background-color: #007bff;"
                "    border: 1px solid #007bff;"
                "    border-radius: 4px;"
                "    color: white;"
                "    font-size: 16px;"
                "    font-weight: 600;"
                "}"
                "QPushButton:hover {"
                "    background-color: #0056b3;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #004085;"
                "}"
            );
        } else if (key == "equals") {
            // 等号按钮
            button->setStyleSheet(
                "QPushButton {"
                "    background-color: #28a745;"
                "    border: 1px solid #28a745;"
                "    border-radius: 4px;"
                "    color: white;"
                "    font-size: 16px;"
                "    font-weight: 600;"
                "}"
                "QPushButton:hover {"
                "    background-color: #218838;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #1e7e34;"
                "}"
            );
        } else {
            // 功能按钮
            button->setStyleSheet(
                "QPushButton {"
                "    background-color: #6c757d;"
                "    border: 1px solid #6c757d;"
                "    border-radius: 4px;"
                "    color: white;"
                "    font-size: 14px;"
                "    font-weight: 500;"
                "}"
                "QPushButton:hover {"
                "    background-color: #5a6268;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #545b62;"
                "}"
            );
        }

        // 设置按钮大小
        button->setMinimumSize(60, 48);
    }
}

void MainWindow::setupConnections()
{
    // 连接计算引擎
    connect(m_engine, &CalculatorEngine::displayChanged,
            m_displayPanel, &QLineEdit::setText);
    connect(m_engine, &CalculatorEngine::errorOccurred,
            this, &MainWindow::onErrorOccurred);

    // 连接数字按钮
    for (int i = 0; i <= 9; ++i) {
        QString digit = QString::number(i);
        if (m_buttons.contains(digit)) {
            connect(m_buttons[digit], &QPushButton::clicked, this, &MainWindow::onDigitClicked);
        }
    }

    // 连接运算符按钮
    connect(m_buttons["add"], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(m_buttons["subtract"], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(m_buttons["multiply"], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(m_buttons["divide"], &QPushButton::clicked, this, &MainWindow::onOperatorClicked);

    // 连接功能按钮
    connect(m_buttons["equals"], &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(m_buttons["decimal"], &QPushButton::clicked, this, &MainWindow::onDecimalClicked);
    connect(m_buttons["C"], &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(m_buttons["CE"], &QPushButton::clicked, this, &MainWindow::onFunctionClicked);
    connect(m_buttons["backspace"], &QPushButton::clicked, this, &MainWindow::onFunctionClicked);

    // 初始显示
    m_displayPanel->setText(m_engine->getDisplayText());
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
        qDebug() << "无法加载样式表，使用内置样式";
        // 使用内置的基本样式
        qApp->setStyleSheet(R"(
            QMainWindow { background-color: #f0f0f0; }
            #centralWidget {
                background-color: white;
                border: 1px solid #cccccc;
                border-radius: 8px;
                padding: 12px;
            }
            #displayPanel {
                background-color: white;
                border: 2px solid #cccccc;
                border-radius: 6px;
                font-size: 24px;
                padding: 12px 16px;
            }
            QPushButton {
                background-color: #f8f9fa;
                border: 1px solid #dee2e6;
                border-radius: 4px;
                font-size: 16px;
                min-width: 60px;
                min-height: 48px;
            }
            QPushButton:hover { background-color: #e9ecef; }
            QPushButton:pressed { background-color: #dee2e6; }
        )");
    }
}

void MainWindow::restoreWindowState()
{
    SettingsManager &settings = SettingsManager::instance();
    QByteArray geometry = settings.getWindowGeometry();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
        qDebug() << "窗口状态恢复成功";
    } else {
        // 默认大小
        setFixedSize(300, 400);
        qDebug() << "使用默认窗口大小";
    }
}

void MainWindow::saveWindowState()
{
    SettingsManager &settings = SettingsManager::instance();
    settings.setWindowGeometry(saveGeometry());
    qDebug() << "窗口状态保存成功";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowState();
    QMainWindow::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();
    int key = event->key();

    // 数字键
    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        m_engine->inputDigit(key - Qt::Key_0);
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
        return;
    }

    // 运算符
    if (keyText == "+") {
        m_engine->inputOperator(Operator::Add);
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    } else if (keyText == "-") {
        m_engine->inputOperator(Operator::Subtract);
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    } else if (key == Qt::Key_Asterisk) {
        m_engine->inputOperator(Operator::Multiply);
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    } else if (key == Qt::Key_Slash) {
        m_engine->inputOperator(Operator::Divide);
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    }
    // 等号
    else if (key == Qt::Key_Equal || key == Qt::Key_Enter || key == Qt::Key_Return) {
        m_engine->inputEquals();
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    }
    // 小数点
    else if (key == Qt::Key_Period || key == Qt::Key_Comma) {
        m_engine->inputDecimal();
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    }
    // 退格
    else if (key == Qt::Key_Backspace) {
        m_engine->backspace();
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    }
    // 清除
    else if (key == Qt::Key_Escape) {
        m_engine->clearAll();
        m_displayPanel->setText(m_engine->getDisplayText());
        event->accept();
    }
    else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::onDigitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int digit = button->text().toInt();
        m_engine->inputDigit(digit);
        m_displayPanel->setText(m_engine->getDisplayText());
    }
}

void MainWindow::onOperatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString text = button->text();
        Operator op = Operator::None;

        if (text == "+") op = Operator::Add;
        else if (text == "-") op = Operator::Subtract;
        else if (text == "×") op = Operator::Multiply;
        else if (text == "÷") op = Operator::Divide;

        if (op != Operator::None) {
            m_engine->inputOperator(op);
            m_displayPanel->setText(m_engine->getDisplayText());
        }
    }
}

void MainWindow::onFunctionClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString text = button->text();

        if (text == "C") {
            m_engine->clearAll();
        } else if (text == "CE") {
            m_engine->clearEntry();
        } else if (text == "⌫") {
            m_engine->backspace();
        }
        m_displayPanel->setText(m_engine->getDisplayText());
    }
}

void MainWindow::onEqualsClicked()
{
    m_engine->inputEquals();
    m_displayPanel->setText(m_engine->getDisplayText());
}

void MainWindow::onDecimalClicked()
{
    m_engine->inputDecimal();
    m_displayPanel->setText(m_engine->getDisplayText());
}

void MainWindow::onDisplayChanged(const QString &text)
{
    Q_UNUSED(text);
}

void MainWindow::onErrorOccurred(ErrorType errorType)
{
    Q_UNUSED(errorType);
    // 可以在这里添加错误状态显示
    m_displayPanel->setStyleSheet("color: red;");
}

} // namespace Calculator
