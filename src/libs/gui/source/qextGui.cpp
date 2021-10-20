#include <qextGui.h>
#include <qextGui_p.h>

QEXTGuiPrivate::QEXTGuiPrivate(QEXTGui *q)
    : q_ptr(q)
{

}

QEXTGuiPrivate::~QEXTGuiPrivate()
{

}



QEXTGui::QEXTGui(QObject *parent)
    : QObject(parent), d_ptr(new QEXTGuiPrivate(this))
{

}

QEXTGui::~QEXTGui()
{

}
