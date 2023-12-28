// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "qtcanvas.h"

class QExtProperty;

class CanvasView : public QtCanvasView
{
    Q_OBJECT
public:
    CanvasView(QWidget *parent = 0)
        : QtCanvasView(parent), moving(0) { }
    CanvasView(QtCanvas *canvas, QWidget *parent = 0)
        : QtCanvasView(canvas, parent), moving(0) { }
signals:
    void itemClicked(QtCanvasItem *item);
    void itemMoved(QtCanvasItem *item);
protected:
    void contentsMousePressEvent(QMouseEvent *event);
    void contentsMouseDoubleClickEvent(QMouseEvent *event);
    void contentsMouseMoveEvent(QMouseEvent* event);
private:
    void handleMouseClickEvent(QMouseEvent *event);
    QPoint moving_start;
    QtCanvasItem *moving;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void newRectangle();
    void newEllipse();
    void newLine();
    void newText();
    void deleteObject();
    void clearAll();
    void fillView();

    void itemClicked(QtCanvasItem *item);
    void itemMoved(QtCanvasItem *item);
    void valueChanged(QExtProperty *property, double value);
    void valueChanged(QExtProperty *property, const QString &value);
    void valueChanged(QExtProperty *property, const QColor &value);
    void valueChanged(QExtProperty *property, const QFont &value);
    void valueChanged(QExtProperty *property, const QPoint &value);
    void valueChanged(QExtProperty *property, const QSize &value);
private:

    QtCanvasItem *addRectangle();
    QtCanvasItem *addEllipse();
    QtCanvasItem *addLine();
    QtCanvasItem *addText();
    void addProperty(QExtProperty *property, const QString &id);
    void updateExpandState();

    QAction *deleteAction;

    class QExtDoublePropertyManager *doubleManager;
    class QExtStringPropertyManager *stringManager;
    class QExtColorPropertyManager *colorManager;
    class QExtFontPropertyManager *fontManager;
    class QExtPointPropertyManager *pointManager;
    class QExtSizePropertyManager *sizeManager;

    class QExtTreePropertyBrowser *propertyEditor;
    CanvasView *canvasView;
    QtCanvas *canvas;
    QtCanvasItem *currentItem;
    QMap<QExtProperty *, QString> propertyToId;
    QMap<QString, QExtProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;
};

#endif
