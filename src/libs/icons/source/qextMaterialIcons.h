#ifndef _QEXTMATERIALICONS_H
#define _QEXTMATERIALICONS_H

#include <QObject>

class QEXTMaterialIcons : public QObject
{
    Q_OBJECT
public:
    enum StyleEnum
    {
        Style_Default = 0,
        Style_Outlined,
        Style_Round,
        Style_Sharp,
        Style_TwoTone,
    };
    Q_ENUM(StyleEnum);

    enum CategoryEnum
    {
        Category_Action = 0,
        Category_Editing,
        Category_Alert,
        Category_Av,
        Category_Communication,
        Category_Content,
        Category_Device,
    };
    Q_ENUM(CategoryEnum);

    enum IconEnum
    {
        Icon_ActionHome = Category_Action * 1000,
        Icon_Action3dRotation,
        Icon_ActionAccessibility,
        Icon_ActionAccessibility_new,
        Icon_ActionAccessible,
        Icon_ActionAccessibleForward,
        Icon_ActionAccountBalance,
        Icon_ActionAccountBalanceWallet,
        Icon_ActionAccountBox,
        Icon_Editing3D = Category_Editing * 1000,
        Icon_Editing3DObject,
    };
    Q_ENUM(IconEnum);

    explicit QEXTMaterialIcons(QObject *parent = 0);

    static QString fileUrl(IconEnum icon, StyleEnum style = Style_Default);
    static QString filePath(IconEnum icon, StyleEnum style = Style_Default);
};

#endif // _QEXTMATERIALICONS_H
