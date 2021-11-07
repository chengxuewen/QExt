#ifndef _QEXTMVVMUTILS_H
#define _QEXTMVVMUTILS_H

#include <qextFunction.h>
#include <qextMvvmGlobal.h>
#include <qextMvvmFactory.h>
#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmModel.h>
#include <qextMvvmRealLimits.h>
#include <qextMvvmFunctionTypes.h>

#include <QVector>
#include <QMetaType>

#include <memory>
#include <functional>
#include <algorithm>
#include <optional>
#include <string>
#include <string_view>
#include <complex>
#include <iterator>
#include <memory>
#include <unordered_set>
#include <type_traits>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <cmath>

class QEXTMvvmItem;
struct QEXT_MVVM_API QEXTMvvmUtils
{

    //! Iterates through item and all its children.
    static void iterate(QEXTMvvmItem *item, const QEXTMvvmItemFunction &fun);

    //! Iterates through all model indices and calls user function.
    //! If function returns false for given index, iteration will not go down to children.
    static void iterateIf(const QEXTMvvmItem *item, const QEXTFunction<bool, const QEXTMvvmItem *> &fun);

    //! Returns copy number of given item in it's parent hierarchy. Takes into account only items with
    //! same modelType.
    static int copyNumber(const QEXTMvvmItem *item);

    //! Returns child at given index of parent. No tags are involved, index is considered
    //! as global index in the combined array of all children.
    static QEXTMvvmItem *childAt(const QEXTMvvmItem *parent, int index);

    //! Returns vector of children representing top level items.

    static QVector<QEXTMvvmItem *> topLevelItems(const QEXTMvvmItem &item);

    //! Returns vector of children representing property items.

    static QVector<QEXTMvvmItem *> singlePropertyItems(const QEXTMvvmItem &item);



    //! Returns true if 'candidate' is one of ancestor of given item.
    static bool isItemAncestor(const QEXTMvvmItem *item, const QEXTMvvmItem *candidate);

    //! Returns vector with duplicates and 'nullptr' filtered out.
//    static QVector<QEXTMvvmItem *> UniqueItems(const QVector<QEXTMvvmItem *> &items);


    //! Returns true if file is binary
    static bool isBinary(const QString &filename);

    //! Returns true if file is text/ascii
    static bool isText(const QString &filename);




    //! Returns true if file exists.
    static bool exists(const QString &fileName);

    //! Joins two path elements into the path.
    static QString join(const QString &part1, const QString &part2);

    //! Create directory, parent directory must exist. If path resolves to existing directory,
    //! no error reported.
    static bool createDirectory(const QString &path);

    //! Removes file or empty directory.
    static bool remove(const QString &path);

    //! Removes directory with all its content.
    static void removeAll(const QString &path);

    //! Provide the filename of a file path.
    static QString baseName(const QString &path);

    //! Returns list of files with given extention found in given directory.
    static QVector<QString> FindFiles(const QString &dirname, const QString &ext);

    //! Returns the path to the parent directory.
    static QString parentPath(const QString &path);

    //! Returns true if the file indicated by 'path' refers to empty file or directory.
    static bool isEmpty(const QString &path);





    //! Returns true if two doubles agree within epsilon*tolerance.
    static bool AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

    //! Produces random integer values uniformly distributed on the closed interval [low, high].
    static int RandInt(int low, int high);

    //! Produces random FLOAT values uniformly distributed on the  interval [low, high).
    static double RandDouble(double low, double high);




    //! Returns string representation of double with given precision.
    //! Provides additional formatting on top of iomanip, so "double x{0}" becomes "0.0".
    static QString DoubleToString(double input, int precision = 12);

    //! Returns string representation of scientific double.
    //! Provides additional formatting on top of iomanip, so "double x{1}" becomes "1.0e+00".
    static QString ScientificDoubleToString(double input, int precision = 6);





    //! Returns name of variant.
    static QString VariantName(const QVariant &variant);

    //! Returns type of variant (additionally checks for user type).
    static int VariantType(const QVariant &variant);

    //! Returns true if variants has compatible types.
    static bool CompatibleVariantTypes(const QVariant &oldValue, const QVariant &newValue);

    //! Returns true if given variants have same type and value.
    static bool IsTheSame(const QVariant &var1, const QVariant &var2);

    //! Converts custom variant to standard variant which Qt views will understand.
    static QVariant toQtVariant(const QVariant &custom);

    //! Converts Qt variant to custom variant on board of QEXTMvvmItem.
    static QVariant toCustomVariant(const QVariant &standard);

    //! Returns true in the case of double value based variant.
    static bool IsBoolVariant(const QVariant &variant);

    //! Returns true in the case of double value based variant.
    static bool IsIntVariant(const QVariant &variant);

    //! Returns true in the case of double value based variant.
    static bool IsDoubleVariant(const QVariant &variant);

    //! Returns true in the case of double value based variant.
    static bool IsComboVariant(const QVariant &variant);

    //! Returns true in the case of double value based variant.
    static bool IsStdStringVariant(const QVariant &variant);

    //! Returns true in the case of variant based on QVector<double>.
    static bool IsDoubleVectorVariant(const QVariant &variant);

    //! Returns true in the case of QColor based variant.
    static bool IsColorVariant(const QVariant &variant);

    //! Returns true in the case of QEXTMvvmExternalProperty based variant.
    static bool IsExtPropertyVariant(const QVariant &variant);

    //! Returns true in the case of QEXTMvvmRealLimits based variant.
    static bool IsRealLimitsVariant(const QVariant &variant);


    template <typename T> static T *createItem()
    {
        return new T;
    }

    //! Returns vector containing results of elemntwise unary function application.

    template <typename It, typename UnaryFunction>
    static QVector<double> Apply(It begin, It end, UnaryFunction func)
    {
        QVector<double> result;
        std::transform(begin, end, std::back_inserter(result), func);
        return result;
    }

    //! Returns copy of container with all duplicated elements filtered our. The order is preserved.

//    template <typename C> static C UniqueWithOrder(const C &container)
//    {
//        C result;

//        using valueType = typename C::value_type;
//        std::unordered_set<valueType> unique;

//        std::copy_if(container.begin(), container.end(), std::back_inserter(result),
//                     [&unique](auto x)
//        {
//            return unique.insert(x).second;
//        });

//        return result;
//    }

//    //! Returns true if container contains a given element.

//    template <typename A, typename B> static bool Contains(const A &container, const B &element)
//    {
//        return std::find(container.begin(), container.end(), element) != container.end();
//    }






    //! Returns all top level items of given type.

    template <typename T = QEXTMvvmItem> static QVector<T *> TopItems(const QEXTMvvmModel *model)
    {
        QVector<T *> result;
        for (auto child : model->rootItem()->children())
        {
            if (auto item = dynamic_cast<T *>(child); item)
            {
                result.push_back(item);
            }
        }

        return result;
    }

    //! Returns top level item of given type.

    template <typename T = QEXTMvvmItem> static T * TopItem(const QEXTMvvmModel *model)
    {
        auto items = TopItems<T>(model);
        return items.empty() ? nullptr : items.front();
    }

    //! Returns all items in a tree of given type.

    template <typename T = QEXTMvvmItem> static QVector<T *> FindItems(const QEXTMvvmModel *model)
    {
        QVector<T *> result;

        auto func = [&result](QEXTMvvmItem * item)
        {
            if (auto concrete = dynamic_cast<T *>(item); concrete)
            {
                result.push_back(concrete);
            }
        };

        iterate(model->rootItem(), func);

        return result;
    }


    //! Removes and deletes item from its model.
    static void DeleteItemFromModel(QEXTMvvmItem *item);

    //! Moves item up (decrements row of the item). Works on children belonging to single tag.
    static void MoveUp(QEXTMvvmItem *item);

    //! Moves item down (increments row of the item). Works on children belonging to single tag.
    static void MoveDown(QEXTMvvmItem *item);

    //! Undo last model operation. If not undo/redo enabled, will do nothing.
    static void Undo(QEXTMvvmModel &model);

    //! Redo model operation which was undone just before. If not undo/redo enabled, will do nothing.
    static void Redo(QEXTMvvmModel &model);

    //! Begin undo/redo macros with given name. Works only if item belongs to the model, and model has
    //! undo/redo enabled. Otherwise, do nothing.
    static void BeginMacros(const QEXTMvvmItem *item, const QString &macro_name);

    //! Finishes undo/redo macros. Works only if item belongs to the model, and model has undo/redo
    //! enabled. Otherwise, do nothing.
    static void EndMacros(const QEXTMvvmItem *item);

};


#endif // _QEXTMVVMUTILS_H
