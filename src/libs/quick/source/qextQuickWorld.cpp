#include <qextQuickWorld.h>
#include <qextQuickWorld_p.h>
#include <qextQuick.h>

QEXTQuickWorldPrivate::QEXTQuickWorldPrivate(QEXTQuickWorld *q)
    : q_ptr(q)
{

}

QEXTQuickWorldPrivate::~QEXTQuickWorldPrivate()
{

}



QEXTQuickWorld::QEXTQuickWorld(QQuickItem *parent)
    : QQuickItem(parent), dd_ptr(new QEXTQuickWorldPrivate(this))
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
//    QEXTQuickThemeManager::instance()->setStartupTheme(themeName);
}

QString QEXTQuickWorld::startupTheme() const
{
    qWarning() << "Please call: QEXTThemeManager.appTheme";
    return QString();
}

void QEXTQuickWorld::setThemeDirs(const QStringList &themeDirs)
{
    foreach (QString themeDir, themeDirs) {
//        QEXTQuickThemeManager::instance()->addThemeDir(themeDir);
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
//    return QEXTQuickThemeManager::instance()->isGenerateThemeTemplateEnable();
    return false;
}

void QEXTQuickWorld::setGenerateThemeTemplateEnable(const bool &enable)
{
//    QEXTQuickThemeManager::instance()->setGenerateThemeTemplateEnable(enable);
}

void QEXTQuickWorld::onParentChanged(QQuickItem *parent)
{
    Q_UNUSED(parent);
    QEXTQuick::instance()->initQuickRoot(dynamic_cast<QQuickWindow *>(this->parent()));
    QEXTQuick::instance()->initWorld(this);
    disconnect(this, SIGNAL(parentChanged(QQuickItem*)), this, SLOT(onParentChanged(QQuickItem*)));
}
