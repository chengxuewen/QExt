// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_STATUSLABEL_H
#define MVVM_WIDGETS_STATUSLABEL_H

#include <qextMvvmGlobal.h>
#include <QFrame>

class QPaintEvent;

namespace ModelView {

//! Shows a single line of text on a white background.
//! Opposite to QLabel, doesn't trigger layout resize, being happy with place it has. If text string
//! is too long for current size, it will be clipped.

class QEXT_MVVM_API QExtMvvmStatusLabel : public QFrame {
    Q_OBJECT

public:
    explicit QExtMvvmStatusLabel(QWidget* parent = nullptr);

    void setText(const QString& text);
    void setFont(const QFont& font);
    void setPointSize(int pointSize);
    void setAlignment(Qt::Alignment);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString m_text;
    Qt::Alignment m_alignment;
    QFont m_font;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_STATUSLABEL_H
