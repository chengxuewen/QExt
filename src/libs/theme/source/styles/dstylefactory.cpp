#include "dstylefactory.h"
#include "style.h"
#include "chameleonstyle.h"

DStyleFactory::DStyleFactory()
{

}

QStyle *DStyleFactory::create(const QString &key)
{
    if (key == "ddark") {
        return new dstyle::Style(dstyle::StyleDark);
    } else if (key == "dlight") {
        return new dstyle::Style(dstyle::StyleLight);
    } else if (key == "dsemidark") {
        return new dstyle::Style(dstyle::StyleSemiDark);
    } else if (key == "dsemilight") {
        return new dstyle::Style(dstyle::StyleSemiLight);
    } else if (key == "chameleon") {
        return new chameleon::ChameleonStyle();
    }

    return nullptr;
}
