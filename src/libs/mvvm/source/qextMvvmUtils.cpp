#include <qextMvvmUtils.h>
#include <qextMvvmItem.h>
#include <qextMvvmComboProperty.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmUndoStackInterface.h>

#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QVector>

#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

// length of buffer
#define BYTE_LENGTH 2048

// null character
#define NULL_CHR (0x00)

// control characters
#define NUL 0
#define BS 8
#define CR 13
#define SUB 26


namespace
{
    const QString qstring_name = "QString";

//! Returns buffer size
    int qextMvvmGetBufferSize(const QString &filename);

//! Returns part of file content in a buffer
    void qextMvvmGetBufferData(const QString &filename, int *buffer, int buffer_size);

//! Returns true if the interger is control character as defined above
    bool qextMvvmIsControlChar(int ch);

//! Returns true if there is two null bytes in the buffer
    bool qextMvvmNullCheck(int *buffer, int buffer_size);
} // namespace


void QEXTMvvmUtils::iterate(QEXTMvvmItem *item, const QEXTMvvmItemFunction &fun)
{
    if (item)
    {
        fun(item);
    }
    else
    {
        return;
    }

    for (auto child : item->children())
    {
        iterate(child, fun);
    }
}

void QEXTMvvmUtils::iterateIf(const QEXTMvvmItem *item, const QEXTFunction<bool, const QEXTMvvmItem *> &fun)
{
    bool proceed_with_children(true);

    if (item)
    {
        proceed_with_children = fun(item);
    }

    if (!item || !proceed_with_children)
    {
        return;
    }

    for (auto child : item->children())
    {
        QEXTMvvmUtils::iterateIf(child, fun);
    }
}

int QEXTMvvmUtils::copyNumber(const QEXTMvvmItem *item)
{
    int result(-1);

    if (!item)
    {
        return result;
    }

    int count(0);
    auto QString = item->modelType();
    if (auto parent = item->parent())
    {
        for (auto child : parent->children())
        {
            if (child == item)
            {
                result = count;
            }
            if (child->modelType() == QString)
            {
                ++count;
            }
        }
    }

    return count > 1 ? result : -1;
}

QEXTMvvmItem *QEXTMvvmUtils::childAt(const QEXTMvvmItem *parent, int index)
{
    if (!parent)
    {
        return nullptr;
    }

    auto container = parent->children();
    return index >= 0 && static_cast<size_t>(index) < container.size()
           ? container[static_cast<size_t>(index)]
           : nullptr;
}

QVector<QEXTMvvmItem *> QEXTMvvmUtils::topLevelItems(const QEXTMvvmItem &item)
{
    QVector<QEXTMvvmItem *> result;
    for (auto child : item.children())
        if (!item.isSinglePropertyTag(item.tagOfItem(child)))
        {
            result.push_back(child);
        }
    return result;
}

QVector<QEXTMvvmItem *> QEXTMvvmUtils::singlePropertyItems(const QEXTMvvmItem &item)
{
    QVector<QEXTMvvmItem *> result;
    for (auto child : item.children())
        if (item.isSinglePropertyTag(item.tagOfItem(child)))
        {
            result.push_back(child);
        }
    return result;
}




bool QEXTMvvmUtils::isItemAncestor(const QEXTMvvmItem *item, const QEXTMvvmItem *candidate)
{
    if (!item || !candidate)
    {
        return false;
    }
    const QEXTMvvmItem *parent = item->parent();
    while (parent)
    {
        if (parent == candidate)
        {
            return true;
        }
        else
        {
            parent = parent->parent();
        }
    }
    return false;
}

//QVector<QEXTMvvmItem *> QEXTMvvmUtils::UniqueItems(const QVector<QEXTMvvmItem *> &items)
//{
//    auto filtered = QEXTMvvmUtils::UniqueWithOrder(items);
//    QVector<QEXTMvvmItem *> result;
//    std::copy();
//    std::copy_if(filtered.begin(), filtered.end(), std::back_inserter(result),
//                 [](auto x)
//    {
//        return x != nullptr;
//    });
//    return result;
//}

bool QEXTMvvmUtils::isBinary(const QString &filename)
{
    int buffer[BYTE_LENGTH];

    // get buffer size
    int buffer_size = qextMvvmGetBufferSize(filename);
    if (buffer_size == 0)
    {
        return false;
    }

    // buffer allocation
    qextMvvmGetBufferData(filename, buffer, buffer_size);

    // control character check
    for (int count = 0; count < buffer_size; ++count)
        if (qextMvvmIsControlChar(buffer[count]))
        {
            return true;
        }

    return qextMvvmNullCheck(buffer, buffer_size);
}

bool QEXTMvvmUtils::isText(const QString &filename)
{
    return (!isBinary(filename));
}

bool QEXTMvvmUtils::exists(const QString &fileName)
{
    QFileInfo info(fileName);
    return info.exists();
}

QString QEXTMvvmUtils::join(const QString &part1, const QString &part2)
{
    return part1 + "/" + part2;
}

bool QEXTMvvmUtils::createDirectory(const QString &path)
{
    QDir dir(path);
    return dir.mkpath(".");
}

bool QEXTMvvmUtils::remove(const QString &path)
{
    QFile file(path);
    return file.remove();
}

void QEXTMvvmUtils::removeAll(const QString &path)
{
    QDir dir(path);
    if (dir.exists())
    {
        dir.removeRecursively();
    }
}

QString QEXTMvvmUtils::baseName(const QString &path)
{
    return QFileInfo(path).completeBaseName();
}

QVector<QString> QEXTMvvmUtils::FindFiles(const QString &dirname, const QString &ext)
{
    QVector<QString> result;
    QDir dir(dirname);
    if (dir.exists())
    {
        QStringList filters = {QString("*" + ext)};
        for (auto entry : dir.entryList(filters))
        {
            auto name = dir.filePath(entry);
            result.append(name);
        }
    }
    return result;
}

QString QEXTMvvmUtils::parentPath(const QString &path)
{
    QFileInfo info(path);
    return info.dir().path();
}

bool QEXTMvvmUtils::isEmpty(const QString &path)
{
    QFileInfo info(path);
    if (info.isDir())
    {
        QDir dir(path);
        return dir.isEmpty();
    }
    else
    {
        return info.size() == 0;
    }
    return false;
}

bool QEXTMvvmUtils::AreAlmostEqual(double a, double b, double tolerance_factor)
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    return std::abs(a - b)
           <= eps * std::max(tolerance_factor * eps, std::max(1., tolerance_factor) * std::abs(b));
}

int QEXTMvvmUtils::RandInt(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uniform_int(low, high);
    return uniform_int(gen);
}

double QEXTMvvmUtils::RandDouble(double low, double high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform_real(low, high);
    return uniform_real(gen);
}

QString QEXTMvvmUtils::DoubleToString(double input, int precision)
{
    std::ostringstream inter;
    inter << std::setprecision(precision);
    if (std::abs(input) < std::numeric_limits<double>::epsilon())
    {
        inter << "0.0";
        return QString::fromStdString(inter.str());
    }
    inter << input;
    if (inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
    {
        inter << ".0";
    }
    return QString::fromStdString(inter.str());
}

QString QEXTMvvmUtils::ScientificDoubleToString(double input, int precision)
{
    std::ostringstream inter;
    inter << std::scientific;
    inter << std::setprecision(precision);
    inter << input;

    std::string::size_type pos = inter.str().find('e');
    if (pos == std::string::npos)
    {
        return QString::fromStdString(inter.str());
    }

    std::string part1 = inter.str().substr(0, pos);
    std::string part2 = inter.str().substr(pos, std::string::npos);

    part1.erase(part1.find_last_not_of('0') + 1, std::string::npos);
    if (part1.back() == '.')
    {
        part1 += "0";
    }

    return QString::fromStdString(part1 + part2);
}

QString QEXTMvvmUtils::VariantName(const QVariant &variant)
{
    return variant.isValid() ? variant.typeName() : QEXTMvvmConstants::invalid_type_name;
}

int QEXTMvvmUtils::VariantType(const QVariant &variant)
{
    auto result = static_cast<int>(variant.type());
    if (result == QVariant::UserType)
    {
        result = variant.userType();
    }
    return result;
}

bool QEXTMvvmUtils::CompatibleVariantTypes(const QVariant &oldValue, const QVariant &newValue)
{
    // Invalid variant can be rewritten by any variant.
    // Valid QVariant can be replaced by invalid variant.
    // In other cases types of variants should coincide to be compatible.

    if (!oldValue.isValid() || !newValue.isValid())
    {
        return true;
    }

    return QEXTMvvmUtils::VariantType(oldValue) == QEXTMvvmUtils::VariantType(newValue);
}

bool QEXTMvvmUtils::IsTheSame(const QVariant &var1, const QVariant &var2)
{
    // variants of different type are always reported as not the same
    if (VariantType(var1) != VariantType(var2))
    {
        return false;
    }

    // variants of same type are compared by value
    return var1 == var2;
}

QVariant QEXTMvvmUtils::toQtVariant(const QVariant &custom)
{
    if (!custom.isValid())
    {
        return custom;
    }

    // converts variant based on QString to variant based on QString
    if (custom.typeName() == QEXTMvvmConstants::string_type_name)
    {
        return QVariant(custom.value<QString>());
    }
    else if (IsDoubleVectorVariant(custom))
    {
        QString str =
            QString("vector of %1 elements").arg(custom.value<QVector<double>>().size());
        return QVariant(str);
    }

    // in other cases returns unchanged variant
    return custom;
}

QVariant QEXTMvvmUtils::toCustomVariant(const QVariant &standard)
{
    if (!standard.isValid())
    {
        return standard;
    }

    // converts variant based on QString to variant based on QString
    if (standard.typeName() == qstring_name)
    {
        return QVariant::fromValue(standard.toString());
    }

    // in other cases returns unchanged variant
    return standard;
}

bool QEXTMvvmUtils::IsBoolVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Bool;
}

bool QEXTMvvmUtils::IsIntVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Int;
}

bool QEXTMvvmUtils::IsDoubleVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Double;
}

bool QEXTMvvmUtils::IsComboVariant(const QVariant &variant)
{
    return variant.canConvert<QEXTMvvmComboProperty>();
}

bool QEXTMvvmUtils::IsStdStringVariant(const QVariant &variant)
{
    return variant.canConvert<QString>();
}

bool QEXTMvvmUtils::IsDoubleVectorVariant(const QVariant &variant)
{
    return variant.typeName() == QEXTMvvmConstants::vector_double_type_name;
}

bool QEXTMvvmUtils::IsColorVariant(const QVariant &variant)
{
    return variant.type() == QVariant::Color;
}

bool QEXTMvvmUtils::IsExtPropertyVariant(const QVariant &variant)
{
    return variant.canConvert<QEXTMvvmExternalProperty>();
}

bool QEXTMvvmUtils::IsRealLimitsVariant(const QVariant &variant)
{
    return variant.canConvert<QEXTMvvmRealLimits>();
}


void QEXTMvvmUtils::DeleteItemFromModel(QEXTMvvmItem *item)
{
    auto model = item->model();
    if (!model)
    {
        return;
    }

    model->removeItem(item->parent(), item->tagRow());
}

void QEXTMvvmUtils::MoveUp(QEXTMvvmItem *item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == 0)
    {
        return;    // item already at the top
    }
    item->model()->moveItem(item, item->parent(), tagrow.prev());
}

void QEXTMvvmUtils::MoveDown(QEXTMvvmItem *item)
{
    auto tagrow = item->tagRow();
    if (tagrow.row == item->parent()->itemCount(tagrow.tag) - 1)
    {
        return;    // item already at the buttom
    }
    item->model()->moveItem(item, item->parent(), tagrow.next());
}

void QEXTMvvmUtils::Undo(QEXTMvvmModel &model)
{
    if (auto stack = model.undoStack(); stack)
    {
        stack->undo();
    }
}

void QEXTMvvmUtils::Redo(QEXTMvvmModel &model)
{
    if (auto stack = model.undoStack(); stack)
    {
        stack->redo();
    }
}

void QEXTMvvmUtils::BeginMacros(const QEXTMvvmItem *item, const QString &macro_name)
{
    if (!item->model())
    {
        return;
    }

    if (auto stack = item->model()->undoStack(); stack)
    {
        stack->beginMacro(macro_name);
    }
}

void QEXTMvvmUtils::EndMacros(const QEXTMvvmItem *item)
{
    if (!item->model())
    {
        return;
    }

    if (auto stack = item->model()->undoStack(); stack)
    {
        stack->endMacro();
    }
}



namespace
{

    int qextMvvmGetBufferSize(const QString &filename)
    {
        std::ifstream mySource;
        mySource.open(filename.toStdString(), std::ios_base::binary);
        mySource.seekg(0, std::ios_base::end);
        int size = mySource.tellg();
        mySource.close();
        return (size > BYTE_LENGTH) ? BYTE_LENGTH : size;
    }

    void qextMvvmGetBufferData(const QString &filename, int *buffer, int byte_length)
    {
        std::ifstream fstr(filename.toStdString(), std::ios::in | std::ios::binary);
        for (int i = 0; i < byte_length; i++)
        {
            buffer[i] = fstr.get();
        }
    }

    bool qextMvvmIsControlChar(int ch)
    {
        return ((ch > NUL && ch < BS) || (ch > CR && ch < SUB));
    }

    bool qextMvvmNullCheck(int *buffer, int buffer_size)
    {
        for (int i = 1; i < buffer_size; ++i)
            if (buffer[i] == NULL_CHR && buffer[i - 1] == NULL_CHR)
            {
                return true;
            }
        return false;
    }
} // namespace
