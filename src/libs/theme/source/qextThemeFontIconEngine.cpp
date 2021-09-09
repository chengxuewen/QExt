#include <qextThemeFontIconEngine.h>
#include <qextThemeHelper.h>

#include <qextObject_p.h>

#include <QtGui/private/qiconloader_p.h>

class QEXTThemeFontIconEnginePrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTThemeFontIconEnginePrivate(QEXTThemeFontIconEngine *qq);
    ~QEXTThemeFontIconEnginePrivate() {}

    QEXTThemePalette::ColorGroup m_colorGroup;
    QEXTThemePalette::ColorType m_colorType;

    QThemeIconInfo m_info;
    QString m_iconName;
    uint m_key;

private:
    QEXT_DECL_PUBLIC(QEXTThemeFontIconEngine)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeFontIconEnginePrivate)
};

QEXTThemeFontIconEnginePrivate::QEXTThemeFontIconEnginePrivate(QEXTThemeFontIconEngine *qq)
    : QEXTObjectPrivate(qq)
{
    m_colorGroup = QEXTThemePalette::Active;
    m_colorType = QEXTThemePalette::Color_NColorTypes;
}

QEXTThemeFontIconEngine::QEXTThemeFontIconEngine()
    : QIconEngine(), QEXTObject(*(new QEXTThemeFontIconEnginePrivate(this)))
{

}

QEXTThemeFontIconEngine::QEXTThemeFontIconEngine(QPalette::ColorGroup cg, QEXTThemePalette::ColorType ct)
    : QIconEngine(), QEXTObject(*(new QEXTThemeFontIconEnginePrivate(this)))
{
    QEXT_DECL_D(QEXTThemeFontIconEngine);
    d->m_colorGroup = cg;
    d->m_colorType = ct;
}

QEXTThemeFontIconEngine::QEXTThemeFontIconEngine(const QEXTThemeFontIconEngine &other)
    : QIconEngine(other), QEXTObject(*(new QEXTThemeFontIconEnginePrivate(this)))
{

}

QEXTThemeFontIconEngine::~QEXTThemeFontIconEngine()
{

}

void QEXTThemeFontIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{

}

QSize QEXTThemeFontIconEngine::actualSize(const QSize &size, QIcon::Mode mode, QIcon::State state)
{

}

QPixmap QEXTThemeFontIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{

}

QString QEXTThemeFontIconEngine::key() const
{
    return QLatin1String("QEXTThemeFontIconEngine");
}

QIconEngine *QEXTThemeFontIconEngine::clone() const
{
    return new QEXTThemeFontIconEngine(*this);
}

bool QEXTThemeFontIconEngine::read(QDataStream &in)
{
    QEXT_DECL_D(QEXTThemeFontIconEngine);
    in >> d->m_iconName;
    return true;
}

bool QEXTThemeFontIconEngine::write(QDataStream &out) const
{
    QEXT_DECL_DC(QEXTThemeFontIconEngine);
    out << d->m_iconName;
    return true;
}

QString QEXTThemeFontIconEngine::iconName() const
{
    QEXT_DECL_DC(QEXTThemeFontIconEngine);
    return d->m_iconName;
}

QEXTThemeFontIconEngine &QEXTThemeFontIconEngine::operator=(const QEXTThemeFontIconEngine &other)
{
    Q_UNUSED(other);
}
