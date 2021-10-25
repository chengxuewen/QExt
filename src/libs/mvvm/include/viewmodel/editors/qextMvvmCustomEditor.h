#ifndef _QEXTMVVMCUSTOMEDITOR_H
#define _QEXTMVVMCUSTOMEDITOR_H

#include <qextMvvmGlobal.h>

#include <QWidget>
#include <QVariant>

//! Base class for all custom variant editors.
class QEXT_MVVM_API QEXTMvvmCustomEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QEXTMvvmCustomEditor(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMvvmCustomEditor();

    QVariant data() const;

    virtual bool isPersistent() const;

public slots:
    void setData(const QVariant &data);

signals:
    //! Emmits signal when data was changed in an editor.
    void dataChanged(QVariant value);

protected:
    void setDataIntern(const QVariant &data);
    //! Should update widget components from m_data, if necessary.
    virtual void updateComponents() = 0;

    QVariant m_data;
};

#endif // _QEXTMVVMCUSTOMEDITOR_H
