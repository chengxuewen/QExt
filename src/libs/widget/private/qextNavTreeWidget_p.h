#ifndef QEXTNAVLISTVIEW_P_H
#define QEXTNAVLISTVIEW_P_H

#include <qextWidgetGlobal.h>
#include <qextobject_p.h>

#include <QIcon>
#include <QString>
#include <QPointer>

class QEXTNavTreeItem;
class QEXT_WIDGET_API QEXTNavTreeItemPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTNavTreeItemPrivate(QEXTNavTreeItem *qq);
    ~QEXTNavTreeItemPrivate();

    void updateLevel();

    int m_level;
    QIcon m_icon;
    QChar m_fontIcon;
    QString m_text;
    QString m_tip;
    bool m_expand;
    QPointer<QEXTNavTreeItem> m_parent;
    QList<QEXTNavTreeItem *> m_childItems;

private:
    QEXT_DECL_PUBLIC(QEXTNavTreeItem)
    QEXT_DISABLE_COPY_MOVE(QEXTNavTreeItemPrivate)
};

#endif // QEXTNAVLISTVIEW_P_H
