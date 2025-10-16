/**
 * @file SettingsManager.cpp
 * @brief 设置管理器实现
 */

#include "../../inc/utils/SettingsManager.h"
#include "../../inc/utils/Constants.h"
#include <QApplication>
#include <QDir>

namespace Calculator {

SettingsManager& SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings(QSettings::UserScope, "QtCalculator", "Calculator")
{
    // 设置默认值
    if (!m_settings.contains("style/preference")) {
        m_settings.setValue("style/preference", Constants::DEFAULT_STYLE);
    }
    if (!m_settings.contains("sound/enabled")) {
        m_settings.setValue("sound/enabled", false);
    }
    if (!m_settings.contains("language/current")) {
        m_settings.setValue("language/current", "zh_CN");
    }
}

QString SettingsManager::getStylePreference() const
{
    return m_settings.value("style/preference", Constants::DEFAULT_STYLE).toString();
}

void SettingsManager::setStylePreference(const QString &style)
{
    if (getStylePreference() != style) {
        m_settings.setValue("style/preference", style);
        emit styleChanged(style);
    }
}

QByteArray SettingsManager::getWindowGeometry() const
{
    return m_settings.value("window/geometry").toByteArray();
}

void SettingsManager::setWindowGeometry(const QByteArray &geometry)
{
    m_settings.setValue("window/geometry", geometry);
}

bool SettingsManager::getSoundEnabled() const
{
    return m_settings.value("sound/enabled", false).toBool();
}

void SettingsManager::setSoundEnabled(bool enabled)
{
    if (getSoundEnabled() != enabled) {
        m_settings.setValue("sound/enabled", enabled);
        emit soundEnabledChanged(enabled);
    }
}

QString SettingsManager::getLanguage() const
{
    return m_settings.value("language/current", "zh_CN").toString();
}

void SettingsManager::setLanguage(const QString &language)
{
    if (getLanguage() != language) {
        m_settings.setValue("language/current", language);
        emit languageChanged(language);
    }
}

} // namespace Calculator