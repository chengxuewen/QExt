#include <qextStyleThemeMaterial.h>

class QEXTStyleThemeMaterialPrivate
{
public:
    explicit QEXTStyleThemeMaterialPrivate(QEXTStyleThemeMaterial *q);
    virtual ~QEXTStyleThemeMaterialPrivate();

    QEXTStyleThemeMaterial * const q_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTStyleThemeMaterialPrivate)
    QEXT_DECL_PUBLIC(QEXTStyleThemeMaterial)
};

QEXTStyleThemeMaterialPrivate::QEXTStyleThemeMaterialPrivate(QEXTStyleThemeMaterial *q)
    : q_ptr(q)
{

}

QEXTStyleThemeMaterialPrivate::~QEXTStyleThemeMaterialPrivate()
{

}



QEXTStyleThemeMaterial::QEXTStyleThemeMaterial(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTStyleThemeMaterialPrivate(this))
{

}

QEXTStyleThemeMaterial::~QEXTStyleThemeMaterial()
{

}

QString QEXTStyleThemeMaterial::styleName() const
{
    return "Material";
}

QString QEXTStyleThemeMaterial::themeName(int type) const
{

}

int QEXTStyleThemeMaterial::currentTheme() const
{

}

void QEXTStyleThemeMaterial::setCurrentTheme(int type)
{

}

QString QEXTStyleThemeMaterial::styleSheet() const
{

}

QString QEXTStyleThemeMaterial::additionalStyle() const
{

}

void QEXTStyleThemeMaterial::setAdditionalStyle(const QString &style)
{

}

void QEXTStyleThemeMaterial::addAdditionalStyle(const QString &style)
{

}
