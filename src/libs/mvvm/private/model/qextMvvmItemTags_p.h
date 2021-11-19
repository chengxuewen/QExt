#ifndef _QEXTMVVMITEMTAGS_P_H
#define _QEXTMVVMITEMTAGS_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItemTags.h>

class QEXTMvvmItemTags;
class QEXT_MVVM_API QEXTMvvmItemTagsPrivate
{
public:
    explicit QEXTMvvmItemTagsPrivate(QEXTMvvmItemTags *q);
    virtual ~QEXTMvvmItemTagsPrivate();

    QEXTMvvmItemTags * const q_ptr;

    QEXTMvvmItemTags::ItemContainerVector m_containerVector;
    QString m_defaultTag;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmItemTagsPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmItemTags)
};

#endif // _QEXTMVVMITEMTAGS_P_H
