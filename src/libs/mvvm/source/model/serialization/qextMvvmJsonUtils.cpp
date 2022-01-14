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
#include <qextMvvmModelConverterFactory.h>
#include <qextMvvmSessionModel.h>
#include <serialization/qextMvvmJsonUtils.h>
#include <qextMvvmRealLimits.h>
#include <stdexcept>

namespace
{
const std::string text_limitless = "limitless";
const std::string text_positive = "positive";
const std::string text_nonnegative = "nonnegative";
const std::string text_lowerlimited = "lowerlimited";
const std::string text_upperlimited = "upperlimited";
const std::string text_limited = "limited";
const std::string separator = " ";
} // namespace
using namespace ModelView;

std::string QEXTMvvmJsonUtils::ModelToJsonString(const ModelView::QEXTMvvmSessionModel& model)
{
    auto converter = CreateModelCopyConverter();
    QJsonObject json_source = converter->to_json(model);
    QJsonDocument document(json_source);
    return QString(document.toJson(QJsonDocument::Indented)).toStdString();
}

std::string QEXTMvvmJsonUtils::ToString(const ModelView::QEXTMvvmRealLimits& limits)
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

QEXTMvvmRealLimits QEXTMvvmJsonUtils::CreateLimits(const std::string& text, double min, double max)
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
