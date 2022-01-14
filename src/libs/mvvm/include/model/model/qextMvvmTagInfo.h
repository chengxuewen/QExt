#ifndef _QEXTMVVMMODELTAGINFO_H
#define _QEXTMVVMMODELTAGINFO_H

#include <qextMvvmGlobal.h>

#include <string>
#include <vector>

namespace ModelView
{

//! Holds info about single tag for QEXTMvvmSessionItem.

class QEXT_MVVM_API QEXTMvvmTagInfo
{
public:
    QEXTMvvmTagInfo();

    QEXTMvvmTagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes);

    //! Constructs universal tag intended for unlimited amount of various items.
    static QEXTMvvmTagInfo universalTag(std::string name, std::vector<std::string> modelTypes = {});

    //! Constructs tag intended for single property.
    static QEXTMvvmTagInfo propertyTag(std::string name, std::string model_type);

    std::string name() const;

    int min() const;

    int max() const;

    std::vector<std::string> modelTypes() const;

    bool maximumReached() const;

    bool isValidChild(const std::string& child) const;

    bool isSinglePropertyTag() const;

    bool operator==(const QEXTMvvmTagInfo& other) const;
    bool operator!=(const QEXTMvvmTagInfo& other) const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    std::vector<std::string> m_modelTypes;
};

} // namespace ModelView

#endif // _QEXTMVVMMODELTAGINFO_H
