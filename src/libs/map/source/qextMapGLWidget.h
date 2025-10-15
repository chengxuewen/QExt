// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPGLWIDGET_H
#define _QEXTMAPGLWIDGET_H

#include <qextMap.h>
#include <qextMapSettings.h>

#include <QOpenGLWidget>

#include <memory>

QT_BEGIN_NAMESPACE

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

QT_END_NAMESPACE

namespace QExtMapLibre {

class GLWidgetPrivate;

class QEXT_MAP_API GLWidget : public QOpenGLWidget {
    Q_OBJECT

public:
    explicit GLWidget(const Settings &);
    ~GLWidget() override;

    Map *map();

signals:
    void onMouseDoubleClickEvent(QExtMapLibre::Coordinate coordinate);
    void onMousePressEvent(QExtMapLibre::Coordinate coordinate);
    void onMouseReleaseEvent(QExtMapLibre::Coordinate coordinate);
    void onMouseMoveEvent(QExtMapLibre::Coordinate coordinate);

protected:
    // QWidget implementation.
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    // Q{,Open}GLWidget implementation.
    void initializeGL() override;
    void paintGL() override;

private:
    Q_DISABLE_COPY(GLWidget)

    std::unique_ptr<GLWidgetPrivate> d_ptr;
};

} // namespace QMapLibre

#endif // _QEXTMAPGLWIDGET_H
