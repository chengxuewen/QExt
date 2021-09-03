#include <qextThemePalette.h>


struct QEXTThemePaletteData : public QSharedData
{
    QBrush m_brush[QEXTThemePalette::NColorGroups][QEXTThemePalette::Color_NColorTypes];
};

class QEXTThemePalettePrivate
{
public:
    QEXTThemePalettePrivate(const QSharedDataPointer<QEXTThemePaletteData> &d)
        : data(d)
    {
    }

    QSharedDataPointer<QEXTThemePaletteData> data;
};

/*!
 * \~chinese \class QEXTThemePalette
 * \~chinese \brief QEXTThemePalette提供了修改的 QPalette 类
 * \~chinese \li QEXTThemePalette添加了新的颜色类型
 */

/*!
 * \~chinese \enum QEXTThemePalette::ColorType
 * \~chinese QEXTThemePalette::ColorType 定义了 QEXTThemePalette 颜色类型
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::NoType
 * \~chinese 无类型
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::ItemBackground
 * \~chinese 列表项的背景色
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::TextTitle
 * \~chinese 标题型文本的颜色
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::TextTips
 * \~chinese 提示性文本的颜色
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::TextWarning
 * \~chinese 警告类型的文本颜色
* \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::TextLively
 * \~chinese 活跃式文本颜色（不受活动色影响）
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::LightLively
 * \~chinese 活跃式按钮（recommend button）背景色中的亮色（不受活跃色影响）
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::DarkLively
 * \~chinese 活跃式按钮（recommend button）背景色中的暗色，会从亮色渐变到暗色（不受活跃色影响）
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::FrameBorder
 * \~chinese 控件边框颜色
 * \~chinese \var QEXTThemePalette::ColorType QEXTThemePalette::Color_NoColorTypes
 * \~chinese 无颜色类型
 */

/*!
 * \~chinese \brief QEXTThemePalette::QEXTThemePalette构造函数
 */
QEXTThemePalette::QEXTThemePalette()
    : d(new QEXTThemePalettePrivate(QSharedDataPointer<QEXTThemePaletteData>(new QEXTThemePaletteData())))
{

}

/*!
 * \~chinese \brief QEXTThemePalette::QEXTThemePalette构造函数
 * \~chinese \param palette参数被发送到 QPalette 构造函数
 */
QEXTThemePalette::QEXTThemePalette(const QPalette &palette)
    : QPalette(palette)
    , d(new QEXTThemePalettePrivate(QSharedDataPointer<QEXTThemePaletteData>(new QEXTThemePaletteData())))
{

}

/*!
 * \~chinese \brief QEXTThemePalette::QEXTThemePalette构造函数
 * \~chinese \param palette参数被发送到 QPalette 构造函数
 */
QEXTThemePalette::QEXTThemePalette(const QEXTThemePalette &palette)
    : QPalette(palette)
    , d(new QEXTThemePalettePrivate(palette.d->data))
{

}

QEXTThemePalette::~QEXTThemePalette()
{

}

QEXTThemePalette &QEXTThemePalette::operator=(const QEXTThemePalette &palette)
{
    QPalette::operator =(palette);
    d->data = palette.d->data;
    return *this;
}

/*!
 * \~chinese \brief QEXTThemePalette::brush
 * \~chinese \param \sa QPalette::brush()
 */
const QBrush &QEXTThemePalette::brush(QPalette::ColorGroup cg, QEXTThemePalette::ColorType cr) const
{
    if (cr >= Color_NColorTypes)
    {
        return QPalette::brush(cg, QPalette::NoRole);
    }

    if (cg == Current)
    {
        cg = this->currentColorGroup();
    }
    else if (cg >= NColorGroups)
    {
        cg = Active;
    }

    return d->data->m_brush[cg][cr];
}

/*!
 * \~chinese \brief QEXTThemePalette::setBrush设置画刷
 * \~chinese \param \sa cg QPalette::setBrush()
 */
void QEXTThemePalette::setBrush(QPalette::ColorGroup cg, QEXTThemePalette::ColorType cr, const QBrush &brush)
{
    if (cg == All)
    {
        for (uint i = 0; i < NColorGroups; i++)
        {
            this->setBrush(ColorGroup(i), cr, brush);
        }
        return;
    }

    if (cr >= Color_NColorTypes)
    {
        return QPalette::setBrush(cg, QPalette::NoRole, brush);
    }

    if (cg == Current)
    {
        cg = currentColorGroup();
    }
    else if (cg >= NColorGroups)
    {
        cg = Active;
    }

    d->data->m_brush[cg][cr] = brush;
}


QT_BEGIN_NAMESPACE
QDataStream &operator<<(QDataStream &ds, const QEXTThemePalette &p)
{
    ds << static_cast<const QPalette &>(p);

    for (int i = 0; i < QEXTThemePalette::NColorGroups; ++i)
    {
        for (int j = 0; j < QEXTThemePalette::Color_NColorTypes; ++j)
        {
            ds << p.brush(QEXTThemePalette::ColorGroup(i), QEXTThemePalette::ColorType(j));
        }
    }

    return ds;
}

QDataStream &operator>>(QDataStream &ds, QEXTThemePalette &p)
{
    ds >> static_cast<QPalette &>(p);

    for (int i = 0; i < QEXTThemePalette::NColorGroups; ++i)
    {
        for (int j = 0; j < QEXTThemePalette::Color_NColorTypes; ++j)
        {
            QBrush brush;
            ds >> brush;

            p.setBrush(QEXTThemePalette::ColorGroup(i), QEXTThemePalette::ColorType(j), brush);
        }
    }

    return ds;
}
QT_END_NAMESPACE
