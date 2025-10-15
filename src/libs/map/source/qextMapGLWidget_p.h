// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPGLWIDGET_P_H
#define _QEXTMAPGLWIDGET_P_H

#include <qextMapGLWidget.h>

#include <memory>

QT_BEGIN_NAMESPACE

class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

QT_END_NAMESPACE

namespace QExtMapLibre {

class GLWidgetPrivate : public QObject {
    Q_OBJECT

public:
    explicit GLWidgetPrivate(QObject *parent, Settings settings);
    ~GLWidgetPrivate() override;

    void handleMousePressEvent(QMouseEvent *event);
    void handleMouseMoveEvent(QMouseEvent *event);
    void handleWheelEvent(QWheelEvent *event) const;

    std::unique_ptr<Map> m_map{};
    Settings m_settings;

private:
    Q_DISABLE_COPY(GLWidgetPrivate);

    QPointF m_lastPos;
};

} // namespace QMapLibre

#endif // _QEXTMAPGLWIDGET_P_H
