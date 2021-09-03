#include <qextThemeHelper.h>
#include <qextThemeHelper_p.h>


class QEXTThemeHelperWraper
{
public:
    QEXTThemeHelperWraper()
        : helper(creator())
    {
        helper->initialize();
    }

    ~QEXTThemeHelperWraper()
    {
        delete helper;
    }

    static QEXTThemeHelper *defaultCreator()
    {
        return new QEXTThemeHelper();
    }

    QEXTThemeHelper *helper;
    static QEXTThemeHelper::HelperCreator creator;
};

QEXTThemeHelper::HelperCreator QEXTThemeHelperWraper::creator = QEXTThemeHelperWraper::defaultCreator;
Q_GLOBAL_STATIC(QEXTThemeHelperWraper, sg_globalHelper)


static QEXTThemeHelper *sg_instance = QEXT_DECL_NULLPTR;



QEXTThemeHelperPrivate::QEXTThemeHelperPrivate(QEXTThemeHelper *qq)
    : QEXTObjectPrivate(qq)
{
    m_themeType = QEXTThemeHelper::Color_Light;
    m_paletteType = QEXTThemeHelper::Color_Light;
}

QEXTThemeHelperPrivate::~QEXTThemeHelperPrivate()
{

}


QEXTThemeHelper::QEXTThemeHelper(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTThemeHelperPrivate(this)))
{

}

void QEXTThemeHelper::initialize()
{

}

void QEXTThemeHelper::registerInstanceCreator(QEXTThemeHelper::HelperCreator creator)
{
    if (creator == QEXTThemeHelperWraper::creator)
    {
        return;
    }

    QEXTThemeHelperWraper::creator = creator;

    if (sg_globalHelper.exists() && sg_globalHelper->helper) {
        delete sg_globalHelper->helper;
        sg_globalHelper->helper = creator();
        sg_globalHelper->helper->initialize();
    }
}

QEXTThemeHelper *QEXTThemeHelper::instance()
{
   return sg_globalHelper->helper;
}

QEXTThemeHelper::~QEXTThemeHelper()
{

}

QEXTThemeHelper::ColorType QEXTThemeHelper::themeType() const
{
    QEXT_DECL_DC(QEXTThemeHelper);
    return d->m_themeType;
}

QEXTThemeHelper::ColorType QEXTThemeHelper::paletteType() const
{
    QEXT_DECL_DC(QEXTThemeHelper);
    return d->m_paletteType;
}
