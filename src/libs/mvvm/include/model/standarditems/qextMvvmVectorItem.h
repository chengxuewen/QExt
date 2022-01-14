#ifndef _QEXTMVVMSTANDARDITEMSVECTORITEM_H
#define _QEXTMVVMSTANDARDITEMSVECTORITEM_H

#include <qextMvvmCompoundItem.h>

namespace ModelView
{

//! Vector item with three x,y,z property items.

class QEXT_MVVM_API QEXTMvvmVectorItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_X = "P_X";
    static inline const std::string P_Y = "P_Y";
    static inline const std::string P_Z = "P_Z";

    QEXTMvvmVectorItem();

    void activate() override;

private:
    void update_label();
};

} // namespace ModelView

#endif // _QEXTMVVMSTANDARDITEMSVECTORITEM_H
