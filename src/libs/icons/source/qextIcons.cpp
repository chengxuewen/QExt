#include <qextIcons.h>
#include <qextIcons_p.h>

QEXTIconsPrivate::QEXTIconsPrivate(QEXTIcons *q)
    : q_ptr(q)
{

}

QEXTIconsPrivate::~QEXTIconsPrivate()
{

}



QEXTIcons::QEXTIcons(QObject *parent)
    : QObject(parent), d_ptr(new QEXTIconsPrivate(this))
{

}

QEXTIcons::~QEXTIcons()
{

}
