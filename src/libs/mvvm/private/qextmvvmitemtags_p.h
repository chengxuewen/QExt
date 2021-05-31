#ifndef QEXTMVVMITEMTAGS_P_H
#define QEXTMVVMITEMTAGS_P_H

#include <qextmvvmglobal.h>

#include <qextobject_p.h>



class QEXTMvvmItemContainer;
class QEXTMvvmItemTags;
class QEXT_MVVM_API QEXTMvvmItemTagsPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTMvvmItemTagsPrivate(QEXTMvvmItemTags *qq);
    ~QEXTMvvmItemTagsPrivate();

    QEXTMvvmItemContainer *container(const QString &tagName) const;
    QEXTMvvmItemContainer *findContainer(const QString &tagName) const;

    QVector<QEXTMvvmItemContainer *> m_containers;
    QString m_defaultTag;

private:
    QEXT_DECLARE_PUBLIC(QEXTMvvmItemTags)
    QEXT_DISABLE_COPY_MOVE(QEXTMvvmItemTagsPrivate)
};



#endif // QEXTMVVMITEMTAGS_P_H
