#include <QUuid>
#include <qextMvvmUniqueIdGenerator.h>



QString QEXTMvvmUniqueIdGenerator::generate()
{
    return QUuid::createUuid().toString();
}
