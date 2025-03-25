// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_MODELUTILS_H
#define MVVM_MODEL_MODELUTILS_H

#include <qextMvvmModelConverterFactory.h>
#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmGlobal.h>
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmPath;

namespace Utils {

//! Returns all top level items of given type.

template <typename T = QExtMvvmSessionItem> std::vector<T*> TopItems(const QExtMvvmSessionModel* model)
{
    std::vector<T*> result;
    for (auto child : model->rootItem()->children())
    {
        auto item = dynamic_cast<T*>(child);
        if (item) result.push_back(item);
    }

    return result;
}

//! Returns top level item of given type.

template <typename T = QExtMvvmSessionItem> T* TopItem(const QExtMvvmSessionModel* model)
{
    auto items = TopItems<T>(model);
    return items.empty() ? nullptr : items.front();
}

//! Returns all items in a tree of given type.

template <typename T = QExtMvvmSessionItem> std::vector<T*> FindItems(const QExtMvvmSessionModel* model)
{
    std::vector<T*> result;

    auto func = [&result](QExtMvvmSessionItem* item)
    {
        auto concrete = dynamic_cast<T*>(item);
        if (concrete) result.push_back(concrete);
    };

    iterate(model->rootItem(), func);

    return result;
}

//! Constructs path to find given item. Item must belong to a model.
QEXT_MVVM_API QExtMvvmPath PathFromItem(const QExtMvvmSessionItem* item);

//! Returns item found in the model following given QExtMvvmPath.
QEXT_MVVM_API QExtMvvmSessionItem* ItemFromPath(const QExtMvvmSessionModel& moodel, const QExtMvvmPath& path);

//! Populate empty model with content of target model using provided converter.
//! Serves as auxiliary function for model copying and cloning.
QEXT_MVVM_API void PopulateEmptyModel(const QExtMvvmJsonModelConverterInterface* converter,
                                          const QExtMvvmSessionModel& source, QExtMvvmSessionModel& target);

//! Creates full deep copy of given model. All item's ID will be generated.
template <typename T = QExtMvvmSessionModel> QExtUniquePointer<T> CreateCopy(const T& model)
{
    auto result = qextMakeUnique<T>();
    auto converter = qextMvvmCreateModelCopyConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Creates exact clone of given model. All item's ID will be preserved.
template <typename T = QExtMvvmSessionModel> QExtUniquePointer<T> CreateClone(const T& model)
{
    auto result = qextMakeUnique<T>();
    auto converter = qextMvvmCreateModelCloneConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Removes and deletes item from its model.
QEXT_MVVM_API void DeleteItemFromModel(QExtMvvmSessionItem* item);

//! Moves item up (decrements row of the item). Works on children belonging to single tag.
QEXT_MVVM_API void MoveUp(QExtMvvmSessionItem* item);

//! Moves item down (increments row of the item). Works on children belonging to single tag.
QEXT_MVVM_API void MoveDown(QExtMvvmSessionItem* item);

//! Undo last model operation. If not undo/redo enabled, will do nothing.
QEXT_MVVM_API void Undo(QExtMvvmSessionModel& model);

//! Redo model operation which was undone just before. If not undo/redo enabled, will do nothing.
QEXT_MVVM_API void Redo(QExtMvvmSessionModel& model);

//! Begin undo/redo macros with given name. Works only if item belongs to the model, and model has
//! undo/redo enabled. Otherwise, do nothing.
QEXT_MVVM_API void BeginMacros(const QExtMvvmSessionItem* item, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if item belongs to the model, and model has undo/redo
//! enabled. Otherwise, do nothing.
QEXT_MVVM_API void EndMacros(const QExtMvvmSessionItem* item);

//! Begin undo/redo macros with given name. Works only if the model has undo/redo enabled.
//! Otherwise, do nothing.
QEXT_MVVM_API void BeginMacros(const QExtMvvmSessionModel* model, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if the model has undo/redo enabled. Otherwise, do nothing.
QEXT_MVVM_API void EndMacros(const QExtMvvmSessionModel* model);

} // namespace Utils
} // namespace ModelView

#endif // MVVM_MODEL_MODELUTILS_H
