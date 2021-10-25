#ifndef _QEXTICONS_H
#define _QEXTICONS_H

#include <qextIconsGlobal.h>

#include <QObject>

class QEXTIconsPrivate;
class QEXT_ICONS_API QEXTIcons : public QObject
{
    Q_OBJECT
public:
    explicit QEXTIcons(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTIcons();


protected:
    QScopedPointer<QEXTIconsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTIcons)
    Q_DECLARE_PRIVATE(QEXTIcons)
};

#endif // _QEXTICONS_H
