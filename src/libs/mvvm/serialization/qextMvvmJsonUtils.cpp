// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QJsonDocument>
#include <QJsonObject>
#include <qextMvvmFactory.h>
#include <qextMvvmModel.h>
#include <qextMvvmJsonUtils.h>
#include <qextMvvmRealLimits.h>
#include <stdexcept>

namespace
{
const QString text_limitless = "limitless";
const QString text_positive = "positive";
const QString text_nonnegative = "nonnegative";
const QString text_lowerlimited = "lowerlimited";
const QString text_upperlimited = "upperlimited";
const QString text_limited = "limited";
const QString separator = " ";
} // namespace


QString JsonUtils::ModelToJsonString(const QEXTMvvmModel& model)
{
    auto converter = QEXTMvvmFactory::createModelCopyConverter();
    QJsonObject json_source = converter->toJson(model);
    QJsonDocument document(json_source);
    return QString(document.toJson(QJsonDocument::Indented));
}

QString JsonUtils::ToString(const QEXTMvvmRealLimits& limits)
{
    if (limits.isLimitless())
        return text_limitless;
    else if (limits.isPositive())
        return text_positive;
    else if (limits.isNonnegative())
        return text_nonnegative;
    else if (limits.isLowerLimited())
        return text_lowerlimited;
    else if (limits.isUpperLimited())
        return text_upperlimited;
    else if (limits.isLimited())
        return text_limited;
    else
        throw std::runtime_error("JsonUtils::ToString() -> Unknown type");
}

QEXTMvvmRealLimits JsonUtils::CreateLimits(const QString& text, double min, double max)
{
    if (text == text_limitless)
        return QEXTMvvmRealLimits();
    else if (text == text_positive)
        return QEXTMvvmRealLimits::positive();
    else if (text == text_nonnegative)
        return QEXTMvvmRealLimits::nonnegative();
    else if (text == text_lowerlimited)
        return QEXTMvvmRealLimits::lowerLimited(min);
    else if (text == text_upperlimited)
        return QEXTMvvmRealLimits::upperLimited(max);
    else if (text == text_limited)
        return QEXTMvvmRealLimits::limited(min, max);
    else
        throw std::runtime_error("JsonUtils::CreateLimits -> Unknown type");
}
