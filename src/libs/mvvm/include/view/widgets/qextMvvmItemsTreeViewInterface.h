#ifndef _QEXTMVVMITEMSTREEVIEWINTERFACE_H
#define _QEXTMVVMITEMSTREEVIEWINTERFACE_H

#include <QWidget>
#include <qextMvvmGlobal.h>

class QTreeView;


class QEXTMvvmModel;

//! Saves and restores list of QEXTMvvmModel's to/from disk using json format.

class QEXT_MVVM_API QEXTMvvmItemsTreeViewInterface : public QWidget
{
    Q_OBJECT

public:
    virtual void setSessionModel(QEXTMvvmModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};


#endif // _QEXTMVVMITEMSTREEVIEWINTERFACE_H
