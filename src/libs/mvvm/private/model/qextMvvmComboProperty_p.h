#ifndef _QEXTMVVMCOMBOPROPERTY_P_H
#define _QEXTMVVMCOMBOPROPERTY_P_H

#include <qextMvvmGlobal.h>

class QEXTMvvmComboProperty;
class QEXT_MVVM_API QEXTMvvmComboPropertyPrivate
{
public:
    explicit QEXTMvvmComboPropertyPrivate(QEXTMvvmComboProperty *q);
    virtual ~QEXTMvvmComboPropertyPrivate();

    QEXTMvvmComboProperty * const q_ptr;

    QVector<QString> m_values;
    QVector<QString> m_toolTips;
    QVector<int> m_selectedIndices;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmComboPropertyPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmComboProperty)
};

#endif // _QEXTMVVMCOMBOPROPERTY_P_H
