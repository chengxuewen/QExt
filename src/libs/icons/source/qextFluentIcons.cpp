#include <private/qextFluentIcons_p.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QString>
#include <QMetaEnum>

QEXTFluentIconsPrivate::QEXTFluentIconsPrivate(QEXTFluentIcons *q)
    : q_ptr(q)
{

}

QEXTFluentIconsPrivate::~QEXTFluentIconsPrivate()
{

}

QEXTFluentIcons::QEXTFluentIcons(QObject *parent)
    : QExtIconsResource(parent)
    , dd_ptr(new QEXTFluentIconsPrivate(this))
{

}

QEXTFluentIcons::~QEXTFluentIcons()
{

}
