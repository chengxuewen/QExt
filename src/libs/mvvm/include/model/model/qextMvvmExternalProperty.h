#ifndef _QEXTMVVMMODELEXTERNALPROPERTY_H
#define _QEXTMVVMMODELEXTERNALPROPERTY_H

#include <qextMvvmGlobal.h>

#include <QColor>

#include <string>

namespace ModelView
{

//! Property to carry text, color and identifier.
//! Can be used to link items with each other.

class QEXT_MVVM_API QEXTMvvmExternalProperty
{
public:
    QEXTMvvmExternalProperty();
    QEXTMvvmExternalProperty(std::string text, QColor color, std::string id = {});

    static QEXTMvvmExternalProperty undefined();

    std::string text() const;

    QColor color() const;

    std::string identifier() const;

    bool isValid() const;

    bool operator==(const QEXTMvvmExternalProperty& other) const;
    bool operator!=(const QEXTMvvmExternalProperty& other) const;
    bool operator<(const QEXTMvvmExternalProperty& other) const;

private:
    std::string m_text;
    QColor m_color;
    std::string m_identifier;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::QEXTMvvmExternalProperty)

#endif // _QEXTMVVMMODELEXTERNALPROPERTY_H
