#include <private/qextFluentIcons_p.h>
#include <qextOnceFlag.h>

#include <QDebug>
#include <QString>
#include <QMetaEnum>

QExtFluentIconsPrivate::QExtFluentIconsPrivate(QExtFluentIcons *q)
    : q_ptr(q)
{

}

QExtFluentIconsPrivate::~QExtFluentIconsPrivate()
{

}

QExtFluentIcons::QExtFluentIcons(QObject *parent)
    : QExtIconsResource(parent)
    , dd_ptr(new QExtFluentIconsPrivate(this))
{

}

QExtFluentIcons::~QExtFluentIcons()
{

}
