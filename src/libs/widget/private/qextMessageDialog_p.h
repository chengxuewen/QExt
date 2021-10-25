#ifndef _QEXTMESSAGEDIALOG_P_H
#define _QEXTMESSAGEDIALOG_P_H

#include <qextWidgetGlobal.h>
#include <qextMessageDialog.h>

#include <QIcon>
#include <QLabel>
#include <QList>
#include <QPointer>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QAbstractButton>

class QEXTMessageDialog;
class QEXT_WIDGET_API QEXTMessageDialogPrivate
{
public:
    explicit QEXTMessageDialogPrivate(QEXTMessageDialog *q);
    virtual ~QEXTMessageDialogPrivate();

    static void initIcons();

    void initDialog();
    QAbstractButton *createButton(QEXTMessageDialog::ButtonType type);
    void createButtons(QEXTMessageDialog::ButtonTypes buttons);
    void addButton(QAbstractButton *button, QEXTMessageDialog::ButtonRoleType role);
    void removeButton(QAbstractButton *button);

    void updateSize();
    void layoutButtons();
    void addButtonsToLayout(const QList<QAbstractButton *> &buttonList, bool reverse);

    QEXTMessageDialog * const q_ptr;

    QIcon m_currentIcon;
    static QVector<QIcon> sm_contentIconVector;
    static QMap<int, QIcon> sm_buttonIconMap;
    QEXTMessageDialog::IconType m_iconType;

    QIcon m_titleIcon;
    QWidget *m_titleBarWidget;
    QLabel *m_titlebarIconLabel;
    QLabel *m_titlebarTextLabel;
    QAbstractButton *m_titleBarCloseButton;

    QWidget *m_contentWidget;
    QLabel *m_contentIconLabel;
    QLabel *m_contentTextLabel;

    QWidget *m_buttonBoxWidget;
    QHBoxLayout *m_buttonBoxLayout;
    QEXTMessageDialog::ButtonTypes m_buttons;
    QVector<QList<QAbstractButton *> > m_buttonsVector;
    QHash<QAbstractButton *, QEXTMessageDialog::ButtonType> m_buttonHash;
    QList<QAbstractButton *> m_customButtonList;
    QPointer<QCheckBox> m_checkBox;

    QPointer<QAbstractButton> m_escapeButton;
    QPointer<QAbstractButton> m_defaultButton;
    QPointer<QAbstractButton> m_clickedButton;
    QList<QAbstractButton *> customButtonList;

private:
    Q_DISABLE_COPY(QEXTMessageDialogPrivate)
    Q_DECLARE_PUBLIC(QEXTMessageDialog)
};

#endif // QEXTMESSAGEBOX_P_H
