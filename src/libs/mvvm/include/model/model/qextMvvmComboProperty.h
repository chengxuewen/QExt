#ifndef _QEXTMVVMMODELCOMBOPROPERTY_H
#define _QEXTMVVMMODELCOMBOPROPERTY_H

#include <qextMvvmGlobal.h>

#include <string>
#include <vector>

namespace ModelView
{

//! Custom property to define list of string values with multiple selections.

class QEXT_MVVM_API QEXTMvvmComboProperty
{
public:
    QEXTMvvmComboProperty();

    static QEXTMvvmComboProperty createFrom(const std::vector<std::string>& values,
                                    const std::string& current_value = {});

    std::string value() const;
    void setValue(const std::string& name);

    std::vector<std::string> values() const;
    void setValues(const std::vector<std::string>& values);

    std::vector<std::string> toolTips() const;
    void setToolTips(const std::vector<std::string>& tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    QEXTMvvmComboProperty& operator<<(const std::string& str);
    QEXTMvvmComboProperty& operator<<(const std::vector<std::string>& str);
    bool operator==(const QEXTMvvmComboProperty& other) const;
    bool operator!=(const QEXTMvvmComboProperty& other) const;
    bool operator<(const QEXTMvvmComboProperty& other) const;

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
    QEXTMvvmComboProperty(std::vector<std::string> values);

    std::vector<std::string> m_values;
    std::vector<std::string> m_tooltips;
    std::vector<int> m_selected_indices;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::QEXTMvvmComboProperty)

#endif // _QEXTMVVMMODELCOMBOPROPERTY_H
