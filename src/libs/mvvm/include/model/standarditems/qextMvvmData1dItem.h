#ifndef _QEXTMVVMDATA1DITEM_H
#define _QEXTMVVMDATA1DITEM_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmSessionModel.h>
#include <vector>

namespace ModelView
{

class QEXTMvvmBinnedAxisItem;

//! Represents one-dimensional data (axis and values).
//! Values are stored in QEXTMvvmData1DItem itself, axis is attached as a child. Corresponding plot
//! properties will be served by QEXTMvvmGraphItem.

class QEXT_MVVM_API QEXTMvvmData1DItem : public QEXTMvvmCompoundItem
{
public:
    static inline const std::string P_VALUES = "P_VALUES";
    static inline const std::string P_ERRORS = "P_ERRORS";
    static inline const std::string T_AXIS = "T_AXIS";

    QEXTMvvmData1DItem();

//    void setAxis(std::unique_ptr<QEXTMvvmBinnedAxisItem> axis);

    std::vector<double> binCenters() const;

    void setValues(const std::vector<double>& data);
    std::vector<double> binValues() const;

    void setErrors(const std::vector<double>& errors);
    std::vector<double> binErrors() const;

    //! Inserts axis of given type.
    template <typename T, typename... Args> T* setAxis(Args&&... args);
};

// FIXME Consider redesign of the method below. Should the axis exist from the beginning
// or added later? It is not clear how to create axis a) via QEXTMvvmData1DItem::setAxis
// b) via model directly c) in constructor?

template<typename T, typename... Args>
T* QEXTMvvmData1DItem::setAxis(Args&&... args)
{
    // we disable possibility to re-create axis to facilitate undo/redo
    if (getItem(T_AXIS, 0))
        throw std::runtime_error("Axis was already set. Currently we do not support axis change");

    T* result{nullptr};
    if (model()) {
        // acting through the model to enable undo/redo
        result = model()->insertItem<T>(this);
    } else {
        result = new T;
        insertItem(result, {T_AXIS, 0});
    }
    result->setParameters(std::forward<Args>(args)...);
    setValues(std::vector<double>(result->size(), 0.0));
    return result;
}

} // namespace ModelView

#endif // _QEXTMVVMDATA1DITEM_H
