// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPSTYLECHANGE_P_H
#define _QEXTMAPSTYLECHANGE_P_H

#include <qextMapStyleParameter.h>
#include <qextMapTypes.h>

#include <QtCore/QString>

#include <memory>
#include <vector>

namespace QExtMapLibre {

class Map;

class QEXT_MAP_API StyleChange {
public:
    StyleChange() = default;
    StyleChange(const StyleChange &s) = delete;
    StyleChange(StyleChange &&s) noexcept = default;
    StyleChange &operator=(const StyleChange &s) = delete;
    StyleChange &operator=(StyleChange &&s) noexcept = default;
    virtual ~StyleChange() = default;

    [[nodiscard]] bool isValid() const { return m_valid; }
    virtual void apply(Map *map) = 0;

    static std::vector<std::unique_ptr<StyleChange>> addFeature(
        const Feature &feature,
        const std::vector<FeatureProperty> &properties = std::vector<FeatureProperty>(),
        const QString &before = QString());
    static std::vector<std::unique_ptr<StyleChange>> removeFeature(const Feature &feature);

    static std::vector<std::unique_ptr<StyleChange>> addParameter(const StyleParameter *parameter,
                                                                  const QString &before = QString());
    static std::vector<std::unique_ptr<StyleChange>> removeParameter(const StyleParameter *parameter);

protected:
    bool m_valid{true};
};

} // namespace QMapLibre

#endif // _QEXTMAPSTYLECHANGE_P_H
