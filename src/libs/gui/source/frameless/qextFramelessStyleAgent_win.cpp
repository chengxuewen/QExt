// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#include "styleagent_p.h"

#include <QtCore/QSet>
#include <QtCore/QVariant>
#include <QtGui/QColor>

#include <QWKCore/private/qwkwindowsextra_p.h>
#include <QWKCore/private/nativeeventfilter_p.h>

// namespace QWK
// {

using QExtFramelessStyleAgentSet = QSet<QExtFramelessStyleAgentPrivate *>;
Q_GLOBAL_STATIC(QExtFramelessStyleAgentSet, g_styleAgentSet)

static QExtFramelessStyleAgent::SystemTheme getSystemTheme()
{
    if (isHighContrastModeEnabled())
    {
        return QExtFramelessStyleAgent::HighContrast;
    }
    else if (isDarkThemeActive())
    {
        return QExtFramelessStyleAgent::Dark;
    }
    else
    {
        return QExtFramelessStyleAgent::Light;
    }
}

static void notifyAllQExtFramelessStyleAgents()
{
    auto theme = getSystemTheme();
    for (auto &&ap: std::as_const(*g_styleAgentSet()))
    {
        ap->notifyThemeChanged(theme);
    }
}

class SystemSettingEventFilter : public QExtFramelessAppNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message,
                           QT_NATIVE_EVENT_RESULT_TYPE *result) QEXT_OVERRIDE
    {
        Q_UNUSED(eventType)
        if (!result)
        {
            return false;
        }

        const auto msg = static_cast<const MSG *>(message);
        switch (msg->message)
        {
            case WM_THEMECHANGED:
            case WM_SYSCOLORCHANGE:
            case WM_DWMCOLORIZATIONCOLORCHANGED:
            {
                notifyAllQExtFramelessStyleAgents();
                break;
            }

            case WM_SETTINGCHANGE:
            {
                if (isImmersiveColorSetChange(msg->wParam, msg->lParam))
                {
                    notifyAllQExtFramelessStyleAgents();
                }
                break;
            }

            default:
                break;
        }
        return false;
    }

    static SystemSettingEventFilter *instance;

    static inline void install()
    {
        if (instance)
        {
            return;
        }
        instance = new SystemSettingEventFilter();
    }

    static inline void uninstall()
    {
        if (!instance)
        {
            return;
        }
        delete instance;
        instance = QEXT_NULLPTR;
    }
};

SystemSettingEventFilter *SystemSettingEventFilter::instance = QEXT_NULLPTR;

void QExtFramelessStyleAgentPrivate::setupSystemThemeHook()
{
    systemTheme = getSystemTheme();

    g_styleAgentSet->insert(this);
    SystemSettingEventFilter::install();
}

void QExtFramelessStyleAgentPrivate::removeSystemThemeHook()
{
    if (!g_styleAgentSet->remove(this))
    {
        return;
    }

    if (g_styleAgentSet->isEmpty())
    {
        SystemSettingEventFilter::uninstall();
    }
}
// }