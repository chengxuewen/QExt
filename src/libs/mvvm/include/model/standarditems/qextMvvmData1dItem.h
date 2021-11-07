#ifndef _QEXTMVVMDATA1DITEM_H
#define _QEXTMVVMDATA1DITEM_H

#include <qextMvvmCompoundItem.h>
#include <qextMvvmModel.h>

#include <QVector>

class QEXTMvvmBinnedAxisItem;

//! Represents one-dimensional data (axis and values).
//! Values are stored in QEXTMvvmData1DItem itself, axis is attached as a child. Corresponding plot
//! properties will be served by QEXTMvvmGraphItem.

class QEXT_MVVM_API QEXTMvvmData1DItem : public QEXTMvvmCompoundItem
{
public:
    static inline const QString P_VALUES = "P_VALUES";
    static inline const QString P_ERRORS = "P_ERRORS";
    static inline const QString T_AXIS = "T_AXIS";

    QEXTMvvmData1DItem();

    void setAxis(QEXTMvvmBinnedAxisItem *axis);

    QVector<double> binCenters() const;

    void setValues(const QVector<double>& data);
    QVector<double> binValues() const;

    void setErrors(const QVector<double>& errors);
    QVector<double> binErrors() const;

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
    if (item(T_AXIS, 0))
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
    setValues(QVector<double>(result->size(), 0.0));
    return result;
}

#endif // _QEXTMVVMDATA1DITEM_H
