#ifndef _QEXTMVVMWIDGETSCOLLAPSIBLEBAR_H
#define _QEXTMVVMWIDGETSCOLLAPSIBLEBAR_H

#include <qextMvvmGlobal.h>

#include <QFrame>

class QLabel;
class QString;

namespace ModelView
{

//! Horizontal collapsible bar, part of CollapsibleListWidget.
//! Intended for placement into the QSplitter, makes client widget visible/invisible on clicks.

class QEXT_MVVM_API QEXTMvvmCollapsibleBar : public QFrame
{
    Q_OBJECT

public:
    QEXTMvvmCollapsibleBar(QWidget* parent = nullptr);

    void setWidget(QWidget* widget, const QString& title);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    bool eventFilter(QObject* obj, QEvent* event) override;
    void updatePixmap();

    QWidget* m_controlledWidget{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    QLabel* m_titleLabel{nullptr};
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSCOLLAPSIBLEBAR_H
