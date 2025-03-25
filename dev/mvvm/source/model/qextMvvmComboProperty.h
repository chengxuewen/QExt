// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_COMBOPROPERTY_H
#define MVVM_MODEL_COMBOPROPERTY_H


#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView {

//! Custom property to define list of string values with multiple selections.

class QEXT_MVVM_API QExtMvvmComboProperty {
public:
    QExtMvvmComboProperty();

    static QExtMvvmComboProperty createFrom(const std::vector<std::string>& values,
                                    const std::string& current_value = {});

    std::string value() const;
    void setValue(const std::string& name);

    std::vector<std::string> values() const;
    void setValues(const std::vector<std::string>& values);

    std::vector<std::string> toolTips() const;
    void setToolTips(const std::vector<std::string>& tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QExtMvvmComboProperty& operator<<(const std::string& str);
    QExtMvvmComboProperty& operator<<(const std::vector<std::string>& str);
    bool operator==(const QExtMvvmComboProperty& other) const;
    bool operator!=(const QExtMvvmComboProperty& other) const;
    bool operator<(const QExtMvvmComboProperty& other) const;

    std::string stringOfValues() const;
    void setStringOfValues(const std::string& values);

    std::vector<int> selectedIndices() const;
    std::vector<std::string> selectedValues() const;

    void setSelected(int index, bool value = true);
    void setSelected(const std::string& name, bool value = true);

    std::string stringOfSelections() const;
    void setStringOfSelections(const std::string& values);

    std::string label() const;

private:
    QExtMvvmComboProperty(std::vector<std::string> values);

    std::vector<std::string> m_values;
    std::vector<std::string> m_tooltips;
    std::vector<int> m_selected_indices;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::QExtMvvmComboProperty)

#endif // MVVM_MODEL_COMBOPROPERTY_H
