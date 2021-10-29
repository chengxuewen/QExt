#ifndef _QEXTGUI_H
#define _QEXTGUI_H

#include <qextGlobal.h>
#include <qextGuiGlobal.h>

#include <QObject>

class QEXTGuiPrivate;
class QEXT_GUI_API QEXTGui : public QObject
{
    Q_OBJECT
public:
    explicit QEXTGui(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTGui();


protected:
    QScopedPointer<QEXTGuiPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGui)
    Q_DECLARE_PRIVATE(QEXTGui)
};

#endif // _QEXTGUI_H
