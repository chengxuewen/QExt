#ifndef _QEXTMVVMSESSIONITEMDATA_H
#define _QEXTMVVMSESSIONITEMDATA_H

#include <qextMvvmDataRole.h>
#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView
{

//! Handles data roles for QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmSessionItemData
{
public:
    using container_type = std::vector<QEXTMvvmDataRole>;
    using const_iterator = container_type::const_iterator;

    std::vector<int> roles() const;

    QEXTMvvmVariant data(int role) const;

    bool setData(const QEXTMvvmVariant& value, int role);

    const_iterator begin() const;
    const_iterator end() const;

    bool hasData(int role) const;

private:
    void assure_validity(const QEXTMvvmVariant& variant, int role);
    container_type m_values;
};

} // namespace ModelView

#endif // _QEXTMVVMSESSIONITEMDATA_H
