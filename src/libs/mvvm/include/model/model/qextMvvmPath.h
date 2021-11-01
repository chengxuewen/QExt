#ifndef _QEXTMVVMPATH_H
#define _QEXTMVVMPATH_H

#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView
{

//! Supports navigation through QEXTMvvmSessionModel. It contains a chain of row indexes that have to
//! be used to reach the desired QEXTMvvmSessionItem starting from the root item.

class QEXT_MVVM_API QEXTMvvmPath
{
public:
    using PathElement = int;
    using container_t = std::vector<PathElement>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    QEXTMvvmPath() = default;

    static QEXTMvvmPath fromString(const std::string& str);

    static QEXTMvvmPath fromVector(const std::vector<int>& data);

    std::string str() const;

    void append(PathElement element);
    void prepend(PathElement element);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    container_t m_data;
};

} // namespace ModelView

#endif // _QEXTMVVMPATH_H
