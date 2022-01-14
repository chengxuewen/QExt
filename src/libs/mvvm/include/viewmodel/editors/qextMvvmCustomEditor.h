#ifndef _QEXTMVVMEDITORSCUSTOMEDITOR_H
#define _QEXTMVVMEDITORSCUSTOMEDITOR_H

#include <qextMvvmGlobal.h>

#include <QWidget>

namespace ModelView
{

//! Base class for all custom variant editors.

class QEXT_MVVM_API QEXTMvvmCustomEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value MEMBER m_data READ data WRITE setData NOTIFY dataChanged USER true)

public:
    explicit QEXTMvvmCustomEditor(QWidget* parent = nullptr);

    QVariant data() const;

    virtual bool is_persistent() const;

public slots:
    void setData(const QVariant& data);

signals:
    //! Emmits signal when data was changed in an editor.
    void dataChanged(QVariant value);

protected:
    void setDataIntern(const QVariant& data);
    //! Should update widget components from m_data, if necessary.
    virtual void update_components() = 0;
    QVariant m_data;
};

} // namespace ModelView

#endif // _QEXTMVVMEDITORSCUSTOMEDITOR_H
