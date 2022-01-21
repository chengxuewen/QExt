#include <qextStyleThemeManager.h>
#include <qextStyleThemeDefault.h>

#include <QDebug>
#include <QPointer>

class QEXTStyleThemeManagerPrivate
{
public:
    explicit QEXTStyleThemeManagerPrivate(QEXTStyleThemeManager *q);
    virtual ~QEXTStyleThemeManagerPrivate();

    QEXTStyleThemeManager * const q_ptr;

    QPointer<QWidget> m_targetWidget;
    QPointer<QApplication> m_application;
    QEXTStyleThemeManager::StyleType m_styleType;
    QSharedPointer<QEXTStyleTheme> m_styleTheme;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeManagerPrivate)
    QEXT_DECL_PUBLIC(QEXTStyleThemeManager)
};

QEXTStyleThemeManagerPrivate::QEXTStyleThemeManagerPrivate(QEXTStyleThemeManager *q)
    : q_ptr(q)
    , m_styleType(QEXTStyleThemeManager::Style_Default)
{

}

QEXTStyleThemeManagerPrivate::~QEXTStyleThemeManagerPrivate()
{

}



QEXTStyleThemeManager::QEXTStyleThemeManager(QWidget *parent)
    : QObject(parent)
    , dd_ptr(new QEXTStyleThemeManagerPrivate(this))
{
    Q_D(QEXTStyleThemeManager);
    d->m_styleTheme.reset(this->styleTheme(d->m_styleType));
}

QEXTStyleThemeManager::QEXTStyleThemeManager(QApplication *parent)
    : QObject(parent)
    , dd_ptr(new QEXTStyleThemeManagerPrivate(this))
{
    Q_D(QEXTStyleThemeManager);
    d->m_styleTheme.reset(this->styleTheme(d->m_styleType));
}

QEXTStyleThemeManager::~QEXTStyleThemeManager()
{

}

QEXTStyleTheme *QEXTStyleThemeManager::styleTheme(StyleType type) const
{
    switch (type)
    {
    case Style_Default: return new QEXTStyleThemeDefault;
    default: break;
    }
    return QEXT_DECL_NULLPTR;
}

QSharedPointer<QEXTStyleTheme> QEXTStyleThemeManager::currentStyleTheme() const
{
    Q_D(const QEXTStyleThemeManager);
    return d->m_styleTheme;
}

QEXTStyleThemeManager::StyleType QEXTStyleThemeManager::currentStyle() const
{
    Q_D(const QEXTStyleThemeManager);
    return d->m_styleType;
}

void QEXTStyleThemeManager::setCurrentStyle(StyleType type)
{
    Q_D(QEXTStyleThemeManager);
    if (type != d->m_styleType)
    {
        d->m_styleType = type;
        d->m_styleTheme.reset(this->styleTheme(type));
    }
}

QString QEXTStyleThemeManager::styleTypeString(int type)
{
    switch (type)
    {
    case Style_Default: return "Default";
    case Style_Material: return "Material";
    case Style_Universal: return "Universal";
    default: break;
    }
    return "";
}
