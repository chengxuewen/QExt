#ifndef _QEXTMVVMPROPERTYFLATVIEW_P_H
#define _QEXTMVVMPROPERTYFLATVIEW_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmDefaultEditorFactory.h>
#include <qextMvvmStandardViewItems.h>
#include <qextMvvmViewModelDelegate.h>
#include <qextMvvmViewModelFactory.h>
#include <qextMvvmCustomEditor.h>
#include <qextMvvmLayoutUtils.h>
#include <qextMvvmGroupItem.h>
#include <qextMvvmViewModel.h>
#include <qextMvvmItem.h>

#include <QDataWidgetMapper>
#include <QScopedPointer>
#include <QLabel>

class QEXTMvvmPropertyFlatView;
class QEXT_MVVM_API QEXTMvvmPropertyFlatViewPrivate
{
public:
    explicit QEXTMvvmPropertyFlatViewPrivate(QEXTMvvmPropertyFlatView *q);
    virtual ~QEXTMvvmPropertyFlatViewPrivate();

    QLabel *createLabel(QEXTMvvmViewItem* viewItem);
    QEXTMvvmCustomEditor *createEditor(const QModelIndex &index);

    void updateMappers();
    void updateGridLayout();
    void connectModel();
    QWidget *createWidget(const QModelIndex &index);

    QEXTMvvmPropertyFlatView * const q_ptr;

    QScopedPointer<QEXTMvvmDefaultEditorFactory> m_editorFactory;
    QVector<QSharedPointer<QDataWidgetMapper> > m_widgetMappers;
    QScopedPointer<QEXTMvvmViewModelDelegate> m_delegate;
    QMap<QEXTMvvmViewItem *, QWidget *> m_itemToWidget;
    QScopedPointer<QEXTMvvmViewModel> m_viewModel;
    QGridLayout *m_gridLayout;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmPropertyFlatViewPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmPropertyFlatView)
};

#endif // _QEXTMVVMPROPERTYFLATVIEW_P_H
