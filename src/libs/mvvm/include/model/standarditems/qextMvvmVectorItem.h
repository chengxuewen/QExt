#ifndef _QEXTMVVMVECTORITEM_H
#define _QEXTMVVMVECTORITEM_H

#include <qextMvvmCompoundItem.h>


//! Vector item with three x,y,z property items.

class QEXT_MVVM_API QEXTMvvmVectorItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_X = "P_X";
    static inline const QString P_Y = "P_Y";
    static inline const QString P_Z = "P_Z";

    QEXTMvvmVectorItem();

    void activate() QEXT_DECL_OVERRIDE;

protected:
    void onPropertyChanged(QEXTMvvmItem *, QString);

private:
    void updateLabel();
};

#endif // _QEXTMVVMVECTORITEM_H
