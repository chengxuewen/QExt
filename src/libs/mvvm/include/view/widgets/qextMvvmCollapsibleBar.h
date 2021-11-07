#ifndef _QEXTMVVMCOLLAPSIBLEBAR_H
#define _QEXTMVVMCOLLAPSIBLEBAR_H

#include <QFrame>
#include <qextMvvmGlobal.h>

class QLabel;
class QString;


//! Horizontal collapsible bar, part of QEXTMvvmCollapsibleListWidget.
//! Intended for placement into the QSplitter, makes client widget visible/invisible on clicks.

class QEXT_MVVM_API QEXTMvvmCollapsibleBar : public QFrame
{
    Q_OBJECT

public:
    QEXTMvvmCollapsibleBar(QWidget* parent = nullptr);

    void setWidget(QWidget* widget, const QString& title);

protected:
    void mousePressEvent(QMouseEvent* event) QEXT_DECL_OVERRIDE;

private:
    bool eventFilter(QObject* obj, QEvent* event) QEXT_DECL_OVERRIDE;
    void updatePixmap();

    QWidget* m_controlledWidget{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QLabel* m_titleLabel{nullptr};
};


#endif // _QEXTMVVMCOLLAPSIBLEBAR_H
