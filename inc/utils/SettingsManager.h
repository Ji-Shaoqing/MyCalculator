/**
 * @file SettingsManager.h
 * @brief 应用程序设置管理
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

/**
 * @class SettingsManager
 * @brief 应用程序设置管理单例类
 * 
 * 负责管理应用程序的配置设置，包括样式偏好、窗口状态等。
 */
class SettingsManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 获取单例实例
     * @return SettingsManager实例
     */
    static SettingsManager& instance();
    
    // 禁止拷贝和赋值
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;
    
    // 样式设置
    QString getStylePreference() const;
    void setStylePreference(const QString &style);
    
    // 窗口设置
    QByteArray getWindowGeometry() const;
    void setWindowGeometry(const QByteArray &geometry);
    
    // 计算器设置
    bool getSoundEnabled() const;
    void setSoundEnabled(bool enabled);
    
    // 语言设置
    QString getLanguage() const;
    void setLanguage(const QString &language);

private:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager() = default;
    
    QSettings m_settings;   ///< QSettings实例
};

} // namespace Calculator

#endif // SETTINGSMANAGER_H