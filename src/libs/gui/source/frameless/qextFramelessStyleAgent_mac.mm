/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2023-2024 Stdware Collections
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextFramelessStyleAgent_p.h>

#include <Cocoa/Cocoa.h>

#include <QVariant>


static QExtFramelessStyleAgent::SystemTheme getSystemTheme()
{
    NSString *osxMode = [[NSUserDefaults standardUserDefaults] stringForKey:@"AppleInterfaceStyle"];
    bool isDark = [osxMode isEqualToString:@"Dark"];
    return isDark ? QExtFramelessStyleAgent::Dark : QExtFramelessStyleAgent::Light;
}

static void notifyAllQExtFramelessStyleAgents();


// Objective C++ Begin

@interface QExtFramelessSystemThemeObserver : NSObject
{
}
@end

@implementation QExtFramelessSystemThemeObserver

- (id)init
{
    self = [super init];
    if (self)
    {
        [[NSDistributedNotificationCenter defaultCenter]
            addObserver:self
               selector:@selector(interfaceModeChanged:)
                   name:@"AppleInterfaceThemeChangedNotification"
                 object:nil];
    }
    return self;
}

- (void)dealloc
{
    [[NSDistributedNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

- (void)interfaceModeChanged:(NSNotification *)notification
{
    notifyAllQExtFramelessStyleAgents();
}

@end

// Objective C++ End



using QExtFramelessStyleAgentSet = QSet<QExtFramelessStyleAgentPrivate *>;
Q_GLOBAL_STATIC(QExtFramelessStyleAgentSet, g_styleAgentSet)

static QExtFramelessSystemThemeObserver *g_systemThemeObserver = QEXT_NULLPTR;

void notifyAllQExtFramelessStyleAgents()
{
    auto theme = getSystemTheme();

    QSet<QExtFramelessStyleAgentPrivate *>::Iterator iter;
    for (iter = g_styleAgentSet()->begin(); iter != g_styleAgentSet()->end(); ++iter)
    {
        (*iter)->notifyThemeChanged(theme);
    }
}

void QExtFramelessStyleAgentPrivate::setupSystemThemeHook()
{
    systemTheme = getSystemTheme();

    // Alloc
    if (g_styleAgentSet->isEmpty())
    {
        g_systemThemeObserver = [[QExtFramelessSystemThemeObserver alloc] init];
    }

    g_styleAgentSet->insert(this);
}

void QExtFramelessStyleAgentPrivate::removeSystemThemeHook()
{
    if (!g_styleAgentSet->remove(this))
    {
        return;
    }

    if (g_styleAgentSet->isEmpty())
    {
        // Delete
        [g_systemThemeObserver release];
        g_systemThemeObserver = nil;
    }
}
