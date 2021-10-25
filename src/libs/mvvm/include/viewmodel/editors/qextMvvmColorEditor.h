#ifndef _QEXTMVVMCOLOREDITOR_H
#define _QEXTMVVMCOLOREDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>
#include <qextMvvmCustomEventFilters.h>

#include <QLabel>
#include <QMouseEvent>

class QEXT_MVVM_API QEXTMvvmColorEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    explicit QEXTMvvmColorEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmColorEditor();

protected:
    void mousePressEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QColor currentColor() const;

    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    QEXTMvvmLostFocusFilter *m_focusFilter;
};

#endif // _QEXTMVVMCOLOREDITOR_H
