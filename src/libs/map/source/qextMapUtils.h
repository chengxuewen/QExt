// Copyright (C) 2023 MapLibre contributors
// Copyright (C) 2019 Mapbox, Inc.

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPUTILS_H
#define _QEXTMAPUTILS_H

#include <qextMapTypes.h>

namespace QExtMapLibre {

enum NetworkMode {
    Online, // Default
    Offline,
};

QEXT_MAP_API NetworkMode networkMode();
QEXT_MAP_API void setNetworkMode(NetworkMode mode);

QEXT_MAP_API double metersPerPixelAtLatitude(double latitude, double zoom);
QEXT_MAP_API ProjectedMeters projectedMetersForCoordinate(const Coordinate &coordinate);
QEXT_MAP_API Coordinate coordinateForProjectedMeters(const ProjectedMeters &projectedMeters);

} // namespace QMapLibre

#endif // _QEXTMAPUTILS_H
