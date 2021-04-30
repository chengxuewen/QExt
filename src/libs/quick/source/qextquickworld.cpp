/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#include <qextquickworld.h>
#include <qextquickworld_p.h>
#include <qextquick.h>
#include <qextquickthememanager.h>

QEXTQuickWorldPrivate::QEXTQuickWorldPrivate(QEXTQuickWorld *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTQuickWorldPrivate::~QEXTQuickWorldPrivate()
{

}



QEXTQuickWorld::QEXTQuickWorld(QQuickItem *parent)
    : QQuickItem(parent), QEXTObject(*(new QEXTQuickWorldPrivate(this)))
{
    static bool inited = false;
    if(inited){
        qErrnoWarning("Error:There is only one world :)");
        throw;
    } else {
        inited = true;
        this->setVisible(false);
        this->setEnabled(false);
        connect(this, SIGNAL(parentChanged(QQuickItem*)), this, SLOT(onParentChanged(QQuickItem*)));
    }
}

QEXTQuickWorld::~QEXTQuickWorld()
{

}

QStringList QEXTQuickWorld::themeDirs() const
{
    qWarning() << "Please call: QEXTThemeManager.themeList";
    return QStringList();
}

void QEXTQuickWorld::setStartupTheme(const QString &themeName)
{
    QEXTQuickThemeManager::instance()->setStartupTheme(themeName);
}

QString QEXTQuickWorld::startupTheme() const
{
    qWarning() << "Please call: QEXTThemeManager.appTheme";
    return QString();
}

void QEXTQuickWorld::setThemeDirs(const QStringList &themeDirs)
{
    foreach (QString themeDir, themeDirs) {
        QEXTQuickThemeManager::instance()->addThemeDir(themeDir);
    }
}

int QEXTQuickWorld::mouseAreaCursorShape() const
{
    return QEXTQuick::instance()->mouseAreaCursorShape();
}

void QEXTQuickWorld::setMouseAreaCursorShape(const int &iShape)
{
    QEXTQuick::instance()->setMouseAreaCursorShape((Qt::CursorShape)iShape);
}

bool QEXTQuickWorld::isGenerateThemeTemplateEnable() const
{
    return QEXTQuickThemeManager::instance()->isGenerateThemeTemplateEnable();
}

void QEXTQuickWorld::setGenerateThemeTemplateEnable(const bool &enable)
{
    QEXTQuickThemeManager::instance()->setGenerateThemeTemplateEnable(enable);
}

void QEXTQuickWorld::onParentChanged(QQuickItem *parent)
{
    Q_UNUSED(parent);
    QEXTQuick::instance()->initQuickRoot(dynamic_cast<QQuickWindow *>(this->parent()));
    QEXTQuick::instance()->initWorld(this);
    disconnect(this, SIGNAL(parentChanged(QQuickItem*)), this, SLOT(onParentChanged(QQuickItem*)));
}
