// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_COLLAPSIBLEBAR_H
#define MVVM_WIDGETS_COLLAPSIBLEBAR_H

#include <qextMvvmGlobal.h>
#include <QFrame>

class QLabel;
class QString;

namespace ModelView {

//! Horizontal collapsible bar, part of QExtMvvmCollapsibleListWidget.
//! Intended for placement into the QSplitter, makes client widget visible/invisible on clicks.

class QEXT_MVVM_API QExtMvvmCollapsibleBar : public QFrame {
    Q_OBJECT

public:
    QExtMvvmCollapsibleBar(QWidget* parent = nullptr);

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

#endif // MVVM_WIDGETS_COLLAPSIBLEBAR_H
