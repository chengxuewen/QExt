#ifndef _QEXTMVVMWIDGETSITEMSTREEVIEWINTERFACE_H
#define _QEXTMVVMWIDGETSITEMSTREEVIEWINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QWidget>

class QTreeView;

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.

class QEXT_MVVM_API QEXTMvvmItemsTreeViewInterface : public QWidget
{
    Q_OBJECT

public:
    virtual void setSessionModel(QEXTMvvmSessionModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSITEMSTREEVIEWINTERFACE_H
