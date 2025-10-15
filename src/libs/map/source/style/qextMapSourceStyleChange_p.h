// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPSOURCESTYLECHANGE_P_H
#define _QEXTMAPSOURCESTYLECHANGE_P_H

#include <private/qextMapStyleChange_p.h>
#include <qextMapSourceParameter.h>
#include <qextMapTypes.h>

#include <QtCore/QString>
#include <QtCore/QVariantMap>

namespace QExtMapLibre {

class Map;

class QEXT_MAP_API StyleAddSource : public StyleChange {
public:
    explicit StyleAddSource(const Feature &feature);
    explicit StyleAddSource(const SourceParameter *parameter);

    void apply(Map *map) override;

private:
    QString m_id;
    QVariantMap m_params;
};

class QEXT_MAP_API StyleRemoveSource : public StyleChange {
public:
    explicit StyleRemoveSource(QString id);
    explicit StyleRemoveSource(const Feature &feature);
    explicit StyleRemoveSource(const SourceParameter *parameter);

    void apply(Map *map) override;

private:
    QString m_id;
};

} // namespace QMapLibre

#endif // _QEXTMAPSOURCESTYLECHANGE_P_H
