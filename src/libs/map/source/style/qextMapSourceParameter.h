// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPSOURCEPARAMETER_H
#define _QEXTMAPSOURCEPARAMETER_H

#include <qextMapStyleParameter.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace QExtMapLibre {

class QEXT_MAP_API SourceParameter : public StyleParameter {
    Q_OBJECT
public:
    explicit SourceParameter(QObject *parent = nullptr);
    ~SourceParameter() override;

    [[nodiscard]] QString type() const;
    void setType(const QString &type);

protected:
    QString m_type;

    Q_DISABLE_COPY(SourceParameter)
};

} // namespace QMapLibre

#endif // _QEXTMAPSOURCEPARAMETER_H
