// Copyright (C) 2023 MapLibre contributors
// Copyright (C) 2019 Mapbox, Inc.

// SPDX-License-Identifier: BSD-2-Clause


#ifndef _QEXTMAPGEOJSON_P_H
#define _QEXTMAPGEOJSON_P_H

#include <qextMapTypes.h>

#include <mapbox/geojson.hpp>
#include <mbgl/util/feature.hpp>
#include <mbgl/util/geometry.hpp>

#include <QtCore/QVariant>

#include <string>

namespace QExtMapLibre::GeoJSON {

mbgl::Point<double> asPoint(const Coordinate &coordinate);
mbgl::MultiPoint<double> asMultiPoint(const Coordinates &multiPoint);
mbgl::LineString<double> asLineString(const Coordinates &lineString);
mbgl::MultiLineString<double> asMultiLineString(const CoordinatesCollection &multiLineString);
mbgl::Polygon<double> asPolygon(const CoordinatesCollection &polygon);
mbgl::MultiPolygon<double> asMultiPolygon(const CoordinatesCollections &multiPolygon);
mbgl::Value asPropertyValue(const QVariant &value);
mbgl::FeatureIdentifier asFeatureIdentifier(const QVariant &id);
mbgl::GeoJSONFeature asFeature(const Feature &feature);

} // namespace QMapLibre::GeoJSON

#endif // _QEXTMAPGEOJSON_P_H
