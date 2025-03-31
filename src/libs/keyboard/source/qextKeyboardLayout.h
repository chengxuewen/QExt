#ifndef _QEXTKEYBOARDLAYOUT_H
#define _QEXTKEYBOARDLAYOUT_H

#include <qextKeyboardGlobal.h>

#include <QObject>
#include <QVector>
#include <QJsonValue>
#include <QJsonArray>

class QEXT_KEYBOARD_API  QExtKeyboardLayout : public QObject
{
    Q_OBJECT
public:
    explicit QExtKeyboardLayout(QObject *parent = QEXT_NULLPTR);

    bool LoadLayout(const QString & strJsonPath);

private:
    QVector<QJsonValue> keyboardRows;
    QEXT_DISABLE_COPY_MOVE(QExtKeyboardLayout)
};

#endif // _QEXTKEYBOARDLAYOUT_H
