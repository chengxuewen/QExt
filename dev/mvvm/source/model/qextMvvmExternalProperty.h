// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_EXTERNALPROPERTY_H
#define MVVM_MODEL_EXTERNALPROPERTY_H


#include <qextMvvmGlobal.h>
#include <QColor>
#include <string>

namespace ModelView {

//! Property to carry text, color and identifier.
//! Can be used to link items with each other.

class QEXT_MVVM_API QExtMvvmExternalProperty {
public:
    QExtMvvmExternalProperty();
    QExtMvvmExternalProperty(std::string text, QColor color, std::string id = {});

    static QExtMvvmExternalProperty undefined();

    std::string text() const;

    QColor color() const;

    std::string identifier() const;

    bool isValid() const;

    bool operator==(const QExtMvvmExternalProperty& other) const;
    bool operator!=(const QExtMvvmExternalProperty& other) const;
    bool operator<(const QExtMvvmExternalProperty& other) const;

private:
    std::string m_text;
    QColor m_color;
    std::string m_identifier;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::QExtMvvmExternalProperty)

#endif // MVVM_MODEL_EXTERNALPROPERTY_H
