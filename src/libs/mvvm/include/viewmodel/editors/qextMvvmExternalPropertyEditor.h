#ifndef _QEXTMVVMEXTERNALPROPERTYEDITOR_H
#define _QEXTMVVMEXTERNALPROPERTYEDITOR_H

#include <qextMvvmGlobal.h>
#include <qextMvvmCustomEditor.h>
#include <qextMvvmCustomEventFilters.h>

#include <cfSlot.h>

#include <QLabel>

CF_USE_NAMESPACE

class QEXT_MVVM_API QEXTMvvmExternalPropertyEditor : public QEXTMvvmCustomEditor
{
    Q_OBJECT
public:
    typedef CFSlot<void, const QVariant &> Callback;

    explicit QEXTMvvmExternalPropertyEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmExternalPropertyEditor();

    void setCallback(Callback callback);

private slots:
    void buttonClicked();

private:
    void updateComponents() QEXT_DECL_OVERRIDE;

    QLabel *m_textLabel;
    QLabel *m_pixmapLabel;
    Callback m_callback; //! actions to take on clicked button
    QEXTMvvmLostFocusFilter *m_focusFilter;
};

#endif // _QEXTMVVMEXTERNALPROPERTYEDITOR_H
