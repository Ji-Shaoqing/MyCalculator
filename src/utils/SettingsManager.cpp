#include "../../inc/utils/SettingsManager.h"

namespace Calculator {

SettingsManager& SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager(QObject *parent)
    : QObject(parent)
    , m_settings("QtCalculator", "Calculator")
{
    // 初始化默认设置
    if (!m_settings.contains("style/preference")) {
        m_settings.setValue("style/preference", ":/styles/default.qss");
    }
    if (!m_settings.contains("window/geometry")) {
        // 不设置默认值，第一次运行时为空
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
    return m_settings.value("style/preference", ":/styles/default.qss").toString();
}

void SettingsManager::setStylePreference(const QString &style)
{
    if (getStylePreference() != style) {
        m_settings.setValue("style/preference", style);
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
    }
}

}
