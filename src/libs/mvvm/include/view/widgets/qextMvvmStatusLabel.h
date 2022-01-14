#ifndef _QEXTMVVMWIDGETSSTATUSLABEL_H
#define _QEXTMVVMWIDGETSSTATUSLABEL_H

#include <qextMvvmGlobal.h>

#include <QFrame>

class QPaintEvent;

namespace ModelView
{

//! Shows a single line of text on a white background.
//! Opposite to QLabel, doesn't trigger layout resize, being happy with place it has. If text string
//! is too long for current size, it will be clipped.

class QEXT_MVVM_API QEXTMvvmStatusLabel : public QFrame
{
    Q_OBJECT

public:
    explicit QEXTMvvmStatusLabel(QWidget* parent = nullptr);

    void setText(const QString& text);
    void setFont(const QFont& font);
    void setPointSize(int pointSize);
    void setAlignment(Qt::Alignment);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QString m_text;
    Qt::Alignment m_alignment;
    QFont m_font;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSSTATUSLABEL_H
