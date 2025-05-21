#ifndef _QEXTINPUTDIALOG_H
#define _QEXTINPUTDIALOG_H

#include <qextWidgetGlobal.h>

#include <QInputDialog>
#include <QObject>

class QEXT_WIDGETS_API QExtInputDialog : public QInputDialog
{
    Q_OBJECT
public:
    QExtInputDialog(QWidget *parent = QEXT_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    ~QExtInputDialog() QEXT_OVERRIDE;

    static QString getItem(QWidget *parent, const QString &title, const QString &label,
                           const QStringList &items, int current = 0, bool editable = true,
                           bool *ok = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags(),
                           Qt::InputMethodHints inputMethodHints = Qt::ImhNone);
};

#endif // _QEXTINPUTDIALOG_H
