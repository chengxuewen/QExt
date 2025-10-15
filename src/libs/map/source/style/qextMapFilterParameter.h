// Copyright (C) 2023 MapLibre contributors

// SPDX-License-Identifier: BSD-2-Clause

#ifndef _QEXTMAPFILTERPARAMETER_H
#define _QEXTMAPFILTERPARAMETER_H

#include <qextMapStyleParameter.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantList>

namespace QExtMapLibre {

class QEXT_MAP_API FilterParameter : public StyleParameter {
    Q_OBJECT
public:
    explicit FilterParameter(QObject *parent = nullptr);
    ~FilterParameter() override;

    [[nodiscard]] QVariantList expression() const;
    void setExpression(const QVariantList &expression);

Q_SIGNALS:
    void expressionUpdated();

protected:
    QVariantList m_expression;

    Q_DISABLE_COPY(FilterParameter)
};

} // namespace QMapLibre

#endif // _QEXTMAPFILTERPARAMETER_H
