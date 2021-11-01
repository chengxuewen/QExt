#ifndef _QEXTMVVMMODELUTILS_H
#define _QEXTMVVMMODELUTILS_H

#include <memory>
#include <qextMvvmModelConverterFactory.h>
#include <qextMvvmItemUtils.h>
#include <qextMvvmSessionItem.h>
#include <qextMvvmSessionModel.h>
#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView
{

namespace Utils
{

//! Returns all top level items of given type.

template <typename T = QEXTMvvmSessionItem> std::vector<T*> TopItems(const QEXTMvvmSessionModel* model)
{
    std::vector<T*> result;
    for (auto child : model->rootItem()->children()) {
        if (auto item = dynamic_cast<T*>(child); item)
            result.push_back(item);
    }

    return result;
}

//! Returns top level item of given type.

template <typename T = QEXTMvvmSessionItem> T* TopItem(const QEXTMvvmSessionModel* model)
{
    auto items = TopItems<T>(model);
    return items.empty() ? nullptr : items.front();
}

//! Returns all items in a tree of given type.

template <typename T = QEXTMvvmSessionItem> std::vector<T*> FindItems(const QEXTMvvmSessionModel* model)
{
    std::vector<T*> result;

    auto func = [&result](QEXTMvvmSessionItem* item) {
        if (auto concrete = dynamic_cast<T*>(item); concrete)
            result.push_back(concrete);
    };

    iterate(model->rootItem(), func);

    return result;
}

//! Populate empty model with content of target model using provided converter.
//! Serves as auxiliary function for model copying and cloning.
void QEXT_MVVM_API PopulateEmptyModel(const QEXTMvvmJsonModelConverterInterface* converter,
                                          const QEXTMvvmSessionModel& source, QEXTMvvmSessionModel& target);

//! Creates full deep copy of given model. All item's ID will be generated.
template <typename T = QEXTMvvmSessionModel> std::unique_ptr<T> CreateCopy(const T& model)
{
    auto result = std::make_unique<T>();
    auto converter = CreateModelCopyConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Creates exact clone of given model. All item's ID will be preserved.
template <typename T = QEXTMvvmSessionModel> std::unique_ptr<T> CreateClone(const T& model)
{
    auto result = std::make_unique<T>();
    auto converter = CreateModelCloneConverter();
    PopulateEmptyModel(converter.get(), model, *result.get());
    return result;
}

//! Removes and deletes item from its model.
void QEXT_MVVM_API DeleteItemFromModel(QEXTMvvmSessionItem* item);

//! Moves item up (decrements row of the item). Works on children belonging to single tag.
void QEXT_MVVM_API MoveUp(QEXTMvvmSessionItem* item);

//! Moves item down (increments row of the item). Works on children belonging to single tag.
void QEXT_MVVM_API MoveDown(QEXTMvvmSessionItem* item);

//! Undo last model operation. If not undo/redo enabled, will do nothing.
void QEXT_MVVM_API Undo(QEXTMvvmSessionModel& model);

//! Redo model operation which was undone just before. If not undo/redo enabled, will do nothing.
void QEXT_MVVM_API Redo(QEXTMvvmSessionModel& model);

//! Begin undo/redo macros with given name. Works only if item belongs to the model, and model has
//! undo/redo enabled. Otherwise, do nothing.
void QEXT_MVVM_API BeginMacros(const QEXTMvvmSessionItem* item, const std::string& macro_name);

//! Finishes undo/redo macros. Works only if item belongs to the model, and model has undo/redo
//! enabled. Otherwise, do nothing.
void QEXT_MVVM_API EndMacros(const QEXTMvvmSessionItem* item);

} // namespace Utils
} // namespace ModelView

#endif // _QEXTMVVMMODELUTILS_H
