#include <qextMvvmUtils.h>

#include <cfMvvmItem.h>

#include <QDataStream>
#include <QBitArray>
#include <QByteArray>
#include <QString>
#include <QLatin1String>
#include <QStringList>
#include <QChar>
#include <QDateTime>
#include <QList>
#include <QMap>
#include <QHash>
#include <QSize>
#include <QSizeF>
#include <QPoint>
#include <QPointF>
#include <QLine>
#include <QLineF>
#include <QRect>
#include <QRectF>
#include <QUrl>
#include <QLocale>
#include <QRegExp>
#include <QEasingCurve>
#include <QVariant>

#include <string>
#include <sstream>

QEXTMvvmUtils::QEXTMvvmUtils()
{

}

QVariant QEXTMvvmUtils::anyToQVariant(const CFAny &any)
{
    if (any.canConvert<int>())
    {
        return QVariant(*(any.toPtr<int>()));
    }
    else if (any.canConvert<uint>())
    {
        return QVariant(*(any.toPtr<uint>()));
    }
    else if (any.canConvert<qlonglong>())
    {
        return QVariant(*(any.toPtr<qlonglong>()));
    }
    else if (any.canConvert<qulonglong>())
    {
        return QVariant(*(any.toPtr<qulonglong>()));
    }
    else if (any.canConvert<bool>())
    {
        return QVariant(*(any.toPtr<bool>()));
    }
    else if (any.canConvert<double>())
    {
        return QVariant(*(any.toPtr<double>()));
    }
    else if (any.canConvert<float>())
    {
        return QVariant(*(any.toPtr<float>()));
    }
    else if (any.canConvert<QByteArray>())
    {
        return QVariant(*(any.toPtr<QByteArray>()));
    }
    else if (any.canConvert<QBitArray>())
    {
        return QVariant(*(any.toPtr<QBitArray>()));
    }
    else if (any.canConvert<QString>())
    {
        return QVariant(*(any.toPtr<QString>()));
    }
    else if (any.canConvert<QLatin1String>())
    {
        return QVariant(QString(*(any.toPtr<QLatin1String>())));
    }
    else if (any.canConvert<QStringList>())
    {
        return QVariant(*(any.toPtr<QStringList>()));
    }
    else if (any.canConvert<QChar>())
    {
        return QVariant(*(any.toPtr<QChar>()));
    }
    else if (any.canConvert<QDate>())
    {
        return QVariant(*(any.toPtr<QDate>()));
    }
    else if (any.canConvert<QTime>())
    {
        return QVariant(*(any.toPtr<QTime>()));
    }
    else if (any.canConvert<QDateTime>())
    {
        return QVariant(*(any.toPtr<QDateTime>()));
    }
    else if (any.canConvert<QList<QVariant> >())
    {
        return QVariant(*(any.toPtr<QList<QVariant> >()));
    }
    else if (any.canConvert<QMap<QString, QVariant> >())
    {
        return QVariant(*(any.toPtr<QMap<QString, QVariant> >()));
    }
    else if (any.canConvert<QHash<QString, QVariant> >())
    {
        return QVariant(*(any.toPtr<QHash<QString, QVariant> >()));
    }
    else if (any.canConvert<QSize>())
    {
        return QVariant(*(any.toPtr<QSize>()));
    }
    else if (any.canConvert<QSizeF>())
    {
        return QVariant(*(any.toPtr<QSizeF>()));
    }
    else if (any.canConvert<QPoint>())
    {
        return QVariant(*(any.toPtr<QPoint>()));
    }
    else if (any.canConvert<QPointF>())
    {
        return QVariant(*(any.toPtr<QPointF>()));
    }
    else if (any.canConvert<QLine>())
    {
        return QVariant(*(any.toPtr<QLine>()));
    }
    else if (any.canConvert<QLineF>())
    {
        return QVariant(*(any.toPtr<QLineF>()));
    }
    else if (any.canConvert<QRect>())
    {
        return QVariant(*(any.toPtr<QRect>()));
    }
    else if (any.canConvert<QRectF>())
    {
        return QVariant(*(any.toPtr<QRectF>()));
    }
    else if (any.canConvert<QUrl>())
    {
        return QVariant(*(any.toPtr<QUrl>()));
    }
    else if (any.canConvert<QLocale>())
    {
        return QVariant(*(any.toPtr<QLocale>()));
    }
    else if (any.canConvert<QRegExp>())
    {
        return QVariant(*(any.toPtr<QRegExp>()));
    }
    else if (any.canConvert<QEasingCurve>())
    {
        return QVariant(*(any.toPtr<QEasingCurve>()));
    }
    else if (any.canConvert<QVariant>())
    {
        return QVariant(*(any.toPtr<QVariant>()));
    }
    else if (any.canConvert<std::string>())
    {
        return QVariant(QString::fromStdString(*(any.toPtr<std::string>())));
    }
    else if (any.canConvert<std::list<std::string> >())
    {
        std::list<std::string> stringList = (*any.toPtr<std::list<std::string> >());
        QStringList qStringList;
        std::list<std::string>::iterator iter;
        for (iter = stringList.begin(); iter != stringList.end(); ++iter)
        {
            qStringList.push_back(QString::fromStdString(*iter));
        }
        return QVariant(qStringList);
    }
    else
    {
        return QVariant();
    }
}

CFAny QEXTMvvmUtils::qVariantToAny(const QVariant &variant)
{
    if (variant.type() == QVariant::Int)
    {
        return CFAny(variant.value<int>());
    }
    else if (variant.type() == QVariant::UInt)
    {
        return CFAny(variant.value<uint>());
    }
    else if (variant.type() == QVariant::LongLong)
    {
        return CFAny(variant.value<qlonglong>());
    }
    else if (variant.type() == QVariant::ULongLong)
    {
        return CFAny(variant.value<qulonglong>());
    }
    else if (variant.type() == QVariant::Bool)
    {
        return CFAny(variant.value<bool>());
    }
    else if (variant.type() == QVariant::Double)
    {
        return CFAny(variant.value<double>());
    }
    else if (variant.type() == QMetaType::Float)
    {
        return CFAny(variant.value<float>());
    }
    else if (variant.type() == QVariant::ByteArray)
    {
        return CFAny(variant.value<QByteArray>());
    }
    else if (variant.type() == QVariant::BitArray)
    {
        return CFAny(variant.value<QBitArray>());
    }
    else if (variant.type() == QVariant::String)
    {
        return CFAny(variant.toString().toStdString());
    }
    else if (variant.type() == QVariant::StringList)
    {
        std::list<std::string> stringList;
        QStringList qStringList = variant.toStringList();
        QStringList::iterator iter;
        for (iter = qStringList.begin(); iter != qStringList.end(); ++iter)
        {
            stringList.push_back(iter->toStdString());
        }
        return CFAny(stringList);
    }
    else if (variant.type() == QVariant::Char)
    {
        return CFAny(variant.toChar().toLatin1());
    }
    else if (variant.canConvert<QVariant>())
    {
        return CFAny(variant.value<QVariant>());
    }
    else
    {
        return CFAny();
    }
}

Qt::ItemFlags QEXTMvvmUtils::viewItemFlagsToQtItemFlags(const CFMvvmViewItem::ItemFlags &viewItemFlags)
{
    Qt::ItemFlags qtItemFlags;
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_Selectable))
    {
        qtItemFlags |= Qt::ItemIsSelectable;
    }
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_Editable))
    {
        qtItemFlags |= Qt::ItemIsEditable;
    }
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_DragEnabled))
    {
        qtItemFlags |= Qt::ItemIsDragEnabled;
    }
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_DropEnabled))
    {
        qtItemFlags |= Qt::ItemIsDropEnabled;
    }
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_UserCheckable))
    {
        qtItemFlags |= Qt::ItemIsUserCheckable;
    }
    if (viewItemFlags.testFlag(CFMvvmViewItem::Item_Enabled))
    {
        qtItemFlags |= Qt::ItemIsEnabled;
    }
    return qtItemFlags;
}

CFMvvmViewItem::ItemFlags QEXTMvvmUtils::qtItemFlagsToViewItemFlags(const Qt::ItemFlags &qtItemFlags)
{
    CFMvvmViewItem::ItemFlags viewItemFlags;
    if (qtItemFlags.testFlag(Qt::ItemIsSelectable))
    {
        viewItemFlags |= CFMvvmViewItem::Item_Selectable;
    }
    if (qtItemFlags.testFlag(Qt::ItemIsEditable))
    {
        viewItemFlags |= CFMvvmViewItem::Item_Editable;
    }
    if (qtItemFlags.testFlag(Qt::ItemIsDragEnabled))
    {
        viewItemFlags |= CFMvvmViewItem::Item_DragEnabled;
    }
    if (qtItemFlags.testFlag(Qt::ItemIsDropEnabled))
    {
        viewItemFlags |= CFMvvmViewItem::Item_DropEnabled;
    }
    if (qtItemFlags.testFlag(Qt::ItemIsUserCheckable))
    {
        viewItemFlags |= CFMvvmViewItem::Item_UserCheckable;
    }
    if (qtItemFlags.testFlag(Qt::ItemIsEnabled))
    {
        viewItemFlags |= CFMvvmViewItem::Item_Enabled;
    }
    return viewItemFlags;
}

int QEXTMvvmUtils::qtItemDataRoleToViewItemRole(int qtItemDataRole)
{
    switch (qtItemDataRole)
    {
        case Qt::DisplayRole:
            return CFMvvmItem::Role_Display;
        case Qt::EditRole:
            return CFMvvmItem::Role_Editor;
        case Qt::ToolTipRole:
            return CFMvvmItem::Role_Tooltip;
        default:
            return CFMvvmItem::Role_None;
    }
}

int QEXTMvvmUtils::viewItemRoleToQtItemDataRole(int viewItemRole)
{
    switch (viewItemRole)
    {
        case CFMvvmItem::Role_Display:
            return Qt::DisplayRole;
        case CFMvvmItem::Role_Editor:
            return Qt::EditRole;
        case CFMvvmItem::Role_Tooltip:
            return Qt::ToolTipRole;
        default:
            return Qt::UserRole;
    }
}

std::list<CFMvvmItem *> QEXTMvvmUtils::singlePropertyItems(const CFMvvmItem *item)
{
    std::list<CFMvvmItem *> result;
    if (item)
    {
        std::list<CFMvvmItem *> children = item->children();
        std::list<CFMvvmItem *>::const_iterator iter;
        for (iter = children.begin(); iter != children.end(); ++iter)
        {
            CFMvvmItem *child = *iter;
            if (!item->isSinglePropertyTag(item->tagOfItem(child)))
            {
                result.push_back(child);
            }
        }
    }
    return result;
}
