#ifndef QEXTGROUPBOX_H
#define QEXTGROUPBOX_H

#include <qextWidgetGlobal.h>

#include <qextobject.h>

#include <QGroupBox>

class QEXT_WIDGET_API QEXTGroupBox : public QGroupBox
{
public:
    explicit QEXTGroupBox(QWidget *parent = QEXT_DECL_NULLPTR);
    explicit QEXTGroupBox(const QString &title, QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTGroupBox();

    void setTitle(const QString &title);
    void setAlignment(int alignment);
    void setFlat(bool flat);
    void setCheckable(bool checkable);

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setChecked(bool checked);

};

#endif // QEXTGROUPBOX_H
