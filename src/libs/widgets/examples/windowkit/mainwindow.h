// Copyright (C) 2023-2024 Stdware Collections
// SPDX-License-Identifier: Apache-2.0

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class WidgetWindowAgent;
class QExtFramelessStyleAgent;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum Theme
    {
        Dark,
        Light,
    };
    Q_ENUM(Theme)

Q_SIGNALS:
    void themeChanged();

protected:
    bool event(QEvent *event);

private:
    void installWindowAgent();
    void loadStyleSheet(Theme theme);

    Theme currentTheme{};

    WidgetWindowAgent *windowAgent;
};

#endif // MAINWINDOW_H
