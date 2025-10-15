// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPIMAGEPARAMETER_H
#define _QEXTMAPIMAGEPARAMETER_H

#include <qextMapStyleParameter.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace QExtMapLibre {

class QEXT_MAP_API ImageParameter : public StyleParameter {
    Q_OBJECT
public:
    explicit ImageParameter(QObject *parent = nullptr);
    ~ImageParameter() override;

    [[nodiscard]] QString source() const;
    void setSource(const QString &source);

Q_SIGNALS:
    void sourceUpdated();

protected:
    QString m_source;

    Q_DISABLE_COPY(ImageParameter)
};

} // namespace QMapLibre

#endif // _QEXTMAPIMAGEPARAMETER_H
