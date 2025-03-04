// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_TAGINFO_H
#define MVVM_MODEL_TAGINFO_H

#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView {

//! Holds info about single tag for QExtMvvmSessionItem.
//! The tag specifies information about children that can be added to a QExtMvvmSessionItem. A tag has a
//! name, min, max allowed number of children, and vector of all modelTypes that children can have.

class QEXT_MVVM_API QExtMvvmTagInfo {
public:
    QExtMvvmTagInfo();

    QExtMvvmTagInfo(std::string name, int min, int max, std::vector<std::string> modelTypes);

    //! Constructs universal tag intended for unlimited amount of various items.
    static QExtMvvmTagInfo universalTag(std::string name, std::vector<std::string> modelTypes = {});

    //! Constructs tag intended for single property.
    static QExtMvvmTagInfo propertyTag(std::string name, std::string QExtMvvmModelType);

    std::string name() const;

    int min() const;

    int max() const;

    std::vector<std::string> modelTypes() const;

    bool maximumReached() const;

    bool isValidChild(const std::string& modelType) const;

    bool isSinglePropertyTag() const;

    bool operator==(const QExtMvvmTagInfo& other) const;
    bool operator!=(const QExtMvvmTagInfo& other) const;

private:
    std::string m_name;
    int m_min;
    int m_max;
    std::vector<std::string> m_modelTypes;
};

} // namespace ModelView

#endif // MVVM_MODEL_TAGINFO_H
