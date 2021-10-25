#ifndef _QEXTMVVMUTILS_H
#define _QEXTMVVMUTILS_H

#include <qextMvvmGlobal.h>

#include <cfMvvmItem.h>
#include <cfMvvmViewItem.h>

#include <cfAny.h>

#include <QVariant>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmUtils
{
public:
    QEXTMvvmUtils();

    static QVariant anyToQVariant(const CFAny &any);
    static CFAny qVariantToAny(const QVariant &variant);

    static Qt::ItemFlags viewItemFlagsToQtItemFlags(const CFMvvmViewItem::ItemFlags &viewItemFlags);
    static CFMvvmViewItem::ItemFlags qtItemFlagsToViewItemFlags(const Qt::ItemFlags &qtItemFlags);

    static int qtItemDataRoleToViewItemRole(int qtItemDataRole);
    static int viewItemRoleToQtItemDataRole(int viewItemRole);

    static std::list<CFMvvmItem *> singlePropertyItems(const CFMvvmItem *item);

};

#endif // _QEXTMVVMUTILS_H
