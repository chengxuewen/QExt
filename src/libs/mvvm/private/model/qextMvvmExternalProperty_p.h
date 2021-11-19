#ifndef _QEXTMVVMEXTERNALPROPERTY_P_H
#define _QEXTMVVMEXTERNALPROPERTY_P_H

#include <qextMvvmGlobal.h>

#include <QColor>
#include <QString>

class QEXTMvvmExternalProperty;
class QEXT_MVVM_API QEXTMvvmExternalPropertyPrivate
{
public:
    explicit QEXTMvvmExternalPropertyPrivate(QEXTMvvmExternalProperty *q);
    virtual ~QEXTMvvmExternalPropertyPrivate();

    QEXTMvvmExternalProperty * const q_ptr;

    QColor m_color;
    QString m_text;
    QString m_identifier;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmExternalPropertyPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmExternalProperty)
};

#endif // _QEXTMVVMEXTERNALPROPERTY_P_H
