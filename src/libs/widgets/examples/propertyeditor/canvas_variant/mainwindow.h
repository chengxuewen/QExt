// Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
// SPDX-License-Identifier: BSD-3-Clause

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "qtcanvas.h"

class QExtPEVariantProperty;
class QExtPEProperty;

class QtBrowserIndex;

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
    void valueChanged(QExtPEProperty *property, const QVariant &value);
private:

    QtCanvasItem *addRectangle();
    QtCanvasItem *addEllipse();
    QtCanvasItem *addLine();
    QtCanvasItem *addText();
    void addProperty(QExtPEVariantProperty *property, const QString &id);
    void updateExpandState();

    QAction *deleteAction;

    class QExtPEVariantPropertyManager *variantManager;

    class QExtPEPropertyTreeEditor *propertyEditor;
    CanvasView *canvasView;
    QtCanvas *canvas;
    QtCanvasItem *currentItem;
    QMap<QExtPEProperty *, QString> propertyToId;
    QMap<QString, QExtPEVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;
};

#endif
