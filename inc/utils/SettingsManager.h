/**
 * @file SettingsManager.h
 * @brief 计算器设置
 * @author Jisq
 * @version 1.0
 * @date 2025
 */

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>

namespace Calculator {

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    // 获取单例实例
    static SettingsManager& instance();

    // 禁用拷贝构造和赋值操作
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    // 样式设置
    QString getStylePreference() const;
    void setStylePreference(const QString &style);

    // 窗口设置
    QByteArray getWindowGeometry() const;
    void setWindowGeometry(const QByteArray &geometry);

    // 其他设置
    bool getSoundEnabled() const;
    void setSoundEnabled(bool enabled);

    QString getLanguage() const;
    void setLanguage(const QString &language);

private:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager() = default;

    QSettings m_settings;
};

}

#endif
