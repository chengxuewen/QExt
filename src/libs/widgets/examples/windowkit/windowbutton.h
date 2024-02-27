// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

#include <QPushButton>

#include <qextGlobal.h>

class WindowButtonPrivate;

class WindowButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WindowButton)
    Q_PROPERTY(QIcon iconNormal READ iconNormal WRITE setIconNormal FINAL)
    Q_PROPERTY(QIcon iconChecked READ iconChecked WRITE setIconChecked FINAL)
    Q_PROPERTY(QIcon iconDisabled READ iconDisabled WRITE setIconDisabled FINAL)
public:
    explicit WindowButton(QWidget *parent = QEXT_NULLPTR);
    ~WindowButton();

public:
    QIcon iconNormal() const;
    void setIconNormal(const QIcon &icon);

    QIcon iconChecked() const;
    void setIconChecked(const QIcon &icon);

    QIcon iconDisabled() const;
    void setIconDisabled(const QIcon &icon);

Q_SIGNALS:
    void doubleClicked();

protected:
    void checkStateSet() QEXT_OVERRIDE;

    void mouseDoubleClickEvent(QMouseEvent *event) QEXT_OVERRIDE;

protected:
    WindowButton(WindowButtonPrivate &d, QWidget *parent = QEXT_NULLPTR);

    QScopedPointer<WindowButtonPrivate> d_ptr;
};

#endif // WINDOWBUTTON_H
