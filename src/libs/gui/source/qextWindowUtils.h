#ifndef _QEXTWINDOWUTILS_H
#define _QEXTWINDOWUTILS_H

#include <qextGuiGlobal.h>

#include <QWindow>

class QEXT_GUI_API QExtWindowUtils
{
public:
    QExtWindowUtils();

    static WId winIdFromProcessId(qint64 pid);
};

#endif // _QEXTWINDOWUTILS_H
