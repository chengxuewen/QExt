#ifndef _QEXTMESSAGEDIALOG_H
#define _QEXTMESSAGEDIALOG_H

#include <qextWidgetGlobal.h>
#include <qextFramelessDialog.h>

#include <QDialog>
#include <qpixmap.h>

class QCheckBox;
class QAbstractButton;

class QEXTMessageDialogPrivate;
class QEXT_WIDGET_API QEXTMessageDialog : public QEXTFramelessDialog
{
    Q_OBJECT
public:
    enum IconType {
        Icon_None = 0,
        Icon_Information,
        Icon_Warning,
        Icon_Critical,
        Icon_Question
    };
    Q_ENUMS(IconType)
    static const int IconNum; // = 5

    enum ButtonRoleType {
        ButtonRole_None = 0,
        ButtonRole_Invalid,
        ButtonRole_Accept,
        ButtonRole_Reject,
        ButtonRole_Destructive,
        ButtonRole_Action,
        ButtonRole_Help,
        ButtonRole_Yes,
        ButtonRole_No,
        ButtonRole_Reset,
        ButtonRole_Apply
    };
    static const int ButtonRoleNum; // = 11

    enum ButtonType {
        Button_None               = 0x00000000,
        Button_Ok                 = 0x00000400,
        Button_Save               = 0x00000800,
        Button_SaveAll            = 0x00001000,
        Button_Open               = 0x00002000,
        Button_Yes                = 0x00004000,
        Button_YesToAll           = 0x00008000,
        Button_No                 = 0x00010000,
        Button_NoToAll            = 0x00020000,
        Button_Abort              = 0x00040000,
        Button_Retry              = 0x00080000,
        Button_Ignore             = 0x00100000,
        Button_Close              = 0x00200000,
        Button_Cancel             = 0x00400000,
        Button_Discard            = 0x00800000,
        Button_Help               = 0x01000000,
        Button_Apply              = 0x02000000,
        Button_Reset              = 0x04000000,
        Button_RestoreDefaults    = 0x08000000,

        Button_FirstButton        = Button_Ok,                // internal
        Button_LastButton         = Button_RestoreDefaults,   // internal

        Button_YesAll             = Button_YesToAll,          // obsolete
        Button_NoAll              = Button_NoToAll,           // obsolete

        Button_Default            = 0x00000100,        // obsolete
        Button_Escape             = 0x00000200,        // obsolete
        Button_FlagMask           = 0x00000300,        // obsolete
        Button_ButtonMask         = ~Button_FlagMask          // obsolete
    };
    Q_DECLARE_FLAGS(ButtonTypes, ButtonType)
    static const int ButtonNum; // = 27

    explicit QEXTMessageDialog(QWidget *parent = QEXT_DECL_NULLPTR);
    QEXTMessageDialog(IconType icon, const QString &title, const QString &text,
                      ButtonTypes buttons = Button_None, QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTMessageDialog();

    void addButton(QAbstractButton *button, ButtonRoleType role);
    QAbstractButton *addButton(const QString &text, ButtonRoleType role);
    QAbstractButton *addButton(ButtonType button);
    void removeButton(QAbstractButton *button);

    QList<QAbstractButton *> buttons() const;
    ButtonRoleType buttonRole(QAbstractButton *button) const;

    void setButtonTypes(ButtonTypes buttons);
    QEXTMessageDialog::ButtonTypes buttonTypes() const;
    ButtonType buttonType(QAbstractButton *button) const;
    QAbstractButton *button(ButtonType type) const;

    QAbstractButton *defaultButton() const;
    void setDefaultButton(QAbstractButton *button);
    void setDefaultButton(ButtonType button);

    QAbstractButton *escapeButton() const;
    void setEscapeButton(QAbstractButton *button);
    void setEscapeButton(ButtonType button);

    QAbstractButton *clickedButton() const;

    QString messageText() const;
    void setMessageText(const QString &text);

    QSize iconSize() const;
    void setIconSize(QSize size);

    IconType iconType() const;
    void setIconType(IconType icon);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QIcon titleIcon() const;
    void setTitleIcon(const QIcon &icon);

    QString titleText() const;
    void setTitleText(const QString &text);

    Qt::TextFormat textFormat() const;
    void setTextFormat(Qt::TextFormat format);

    void setTextInteractionFlags(Qt::TextInteractionFlags flags);
    Qt::TextInteractionFlags textInteractionFlags() const;

    void setCheckBox(QCheckBox *cb);
    QCheckBox* checkBox() const;

    QWidget *titleBarWidget();
    QWidget *contentWidget();

    static QIcon buttonIcon(ButtonType type);
    static void setButtonIcon(const QIcon &icon, ButtonType type);

    static QIcon contentIcon(IconType type);
    static void setContentIcon(const QIcon &icon, IconType type);

    static ButtonType showMessageDialog(QWidget *parent,
                                        IconType icon,
                                        const QString &title,
                                        const QString &text,
                                        ButtonTypes buttons = Button_Ok,
                                        ButtonType defaultButton = Button_None);
    static ButtonType information(QWidget *parent, const QString &title,
                                  const QString &text,
                                  ButtonTypes buttons = Button_Ok,
                                  ButtonType defaultButton = Button_None);
    static ButtonType question(QWidget *parent, const QString &title,
                               const QString &text,
                               ButtonTypes buttons = ButtonTypes(Button_Yes | Button_No),
                               ButtonType defaultButton = Button_None);
    static ButtonType warning(QWidget *parent, const QString &title,
                              const QString &text,
                              ButtonTypes buttons = Button_Ok,
                              ButtonType defaultButton = Button_None);
    static ButtonType critical(QWidget *parent, const QString &title,
                               const QString &text,
                               ButtonTypes buttons = Button_Ok,
                               ButtonType defaultButton = Button_None);

    static QString buttonTypeText(int type);
    static ButtonRoleType buttonTypeRole(int type);

Q_SIGNALS:
    void clicked(QAbstractButton *);
    void helpRequested();

protected Q_SLOTS:
    void onCloseButtonClicked();
    void onHandleButtonClicked();
    void onHandleButtonDestroyed();

protected:
    bool event(QEvent *event) QEXT_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) QEXT_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) QEXT_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) QEXT_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) QEXT_DECL_OVERRIDE;
    void changeEvent(QEvent *event) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTMessageDialogPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTMessageDialog)
    Q_DECLARE_PRIVATE(QEXTMessageDialog)
};

#endif // _QEXTMESSAGEDIALOG_H
