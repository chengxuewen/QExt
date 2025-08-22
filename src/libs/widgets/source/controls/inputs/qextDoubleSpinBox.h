#ifndef _QEXTDOUBLESPINBOX_H
#define _QEXTDOUBLESPINBOX_H

#include <qextWidgetGlobal.h>

#include <QObject>
#include <QDoubleSpinBox>
#include <QScopedPointer>

class QExtDoubleSpinBoxPrivate;
class QEXT_WIDGETS_API QExtDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    enum CursorMoveTriggerFlag
    {
        CursorMoveTrigger_RightKey = 0x01,
    };
    Q_DECLARE_FLAGS(CursorMoveTriggerFlags, CursorMoveTriggerFlag)
    Q_FLAGS(CursorMoveTriggerFlags)

    explicit QExtDoubleSpinBox(QWidget *parent = QEXT_NULLPTR);
    QExtDoubleSpinBox(bool valueTextTrimed, QWidget *parent = QEXT_NULLPTR);
    QExtDoubleSpinBox(bool valueTextTrimed, CursorMoveTriggerFlags flags, QWidget *parent = QEXT_NULLPTR);
    ~QExtDoubleSpinBox() QEXT_OVERRIDE;

    bool isValueTextTrimedEnabled() const;
    void setValueTextTrimedEnable(bool enable);

    QExtDoubleSpinBox::CursorMoveTriggerFlags cursorMoveTriggerFlags() const;
    void setCursorMoveTriggerFlags(QExtDoubleSpinBox::CursorMoveTriggerFlags flags);

    double valueFromText(const QString &text) const QEXT_OVERRIDE;
    QString textFromValue(double val) const QEXT_OVERRIDE;

Q_SIGNALS:
    void valueTextTrimedEnableChanged(bool enable);
    void cursorMoveTriggerFlagsChanged(QExtDoubleSpinBox::CursorMoveTriggerFlags flags);

protected:
    void keyPressEvent(QKeyEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtDoubleSpinBoxPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDoubleSpinBox)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDoubleSpinBox)
};

#endif // _QEXTDOUBLESPINBOX_H
