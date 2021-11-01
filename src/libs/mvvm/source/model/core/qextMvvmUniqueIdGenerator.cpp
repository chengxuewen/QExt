#include <QUuid>
#include <qextMvvmUniqueIdGenerator.h>

using namespace ModelView;

QEXTMvvmIdentifierType QEXTMvvmUniqueIdGenerator::generate()
{
    return QUuid::createUuid().toString().toStdString();
}
