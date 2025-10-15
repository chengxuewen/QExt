// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPIMAGESTYLECHANGE_P_H
#define _QEXTMAPIMAGESTYLECHANGE_P_H

#include <private/qextMapStyleChange_p.h>
#include <qextMapImageParameter.h>

#include <QtGui/QImage>

namespace QExtMapLibre {

class Map;

class QEXT_MAP_API StyleAddImage : public StyleChange {
public:
    explicit StyleAddImage(QString id, const QString &spriteUrl);
    explicit StyleAddImage(QString id, QImage sprite);
    explicit StyleAddImage(const ImageParameter *parameter);

    void apply(Map *map) override;

private:
    QString m_id;
    QImage m_sprite;
};

class QEXT_MAP_API StyleRemoveImage : public StyleChange {
public:
    explicit StyleRemoveImage(QString id);
    explicit StyleRemoveImage(const ImageParameter *parameter);

    void apply(Map *map) override;

private:
    QString m_id;
};

} // namespace QMapLibre

#endif // _QEXTMAPIMAGESTYLECHANGE_P_H
