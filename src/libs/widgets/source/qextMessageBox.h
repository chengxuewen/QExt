#ifndef _QEXTMESSAGEBOX_H
#define _QEXTMESSAGEBOX_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QMessageBox>

class QEXT_WIDGETS_API QExtMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit QExtMessageBox(QWidget *parent = QEXT_NULLPTR);
    QExtMessageBox(Icon icon, const QString &title, const QString &text,
                   StandardButtons buttons = NoButton, QWidget *parent = nullptr,
                   Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    static QSize customIconSize();
    static void setCustomIconSize(const QSize &size);

    static const QIcon &customIcon(Icon type);
    static void setCustomIcon(Icon type, const QIcon &icon);

    static StandardButton information(QWidget *parent, const QString &title, const QString &text,
                                      StandardButtons buttons = Ok,
                                      StandardButton defaultButton = NoButton);
    static StandardButton question(QWidget *parent, const QString &title, const QString &text,
                                   StandardButtons buttons = StandardButtons(Yes | No),
                                   StandardButton defaultButton = NoButton);
    static StandardButton warning(QWidget *parent, const QString &title, const QString &text,
                                  StandardButtons buttons = Ok,
                                  StandardButton defaultButton = NoButton);
    static StandardButton critical(QWidget *parent, const QString &title, const QString &text,
                                   StandardButtons buttons = Ok,
                                   StandardButton defaultButton = NoButton);
    // static void about(QWidget *parent, const QString &title, const QString &text);
    // static void aboutQt(QWidget *parent, const QString &title = QString());
};

#endif // _QEXTMESSAGEBOX_H
