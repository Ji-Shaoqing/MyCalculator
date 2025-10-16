/**
 * @file MainWindow.h
 * @brief 计算器窗口功能
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../inc/core/CalculatorEngine.h"
#include "../../inc/utils/SettingsManager.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>

namespace Calculator {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onFunctionClicked();
    void onEqualsClicked();
    void onDecimalClicked();
    void onDisplayChanged(const QString &text);
    void onErrorOccurred(ErrorType errorType);

private:
    void setupUI();
    void setupConnections();
    void loadStyleSheet();
    void saveWindowState();
    void restoreWindowState();
    void setupButtonStyles();

private:
    QWidget *m_centralWidget;
    QLineEdit *m_displayPanel;
    CalculatorEngine *m_engine;
    QMap<QString, QPushButton*> m_buttons;
};

}

#endif
