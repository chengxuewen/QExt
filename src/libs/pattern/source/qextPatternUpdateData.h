#ifndef _QEXTPATTERNUPDATEDATA_H
#define _QEXTPATTERNUPDATEDATA_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

class QEXT_PATTERN_API QExtPatternUpdateData : public QExtPatternUpdateDataInterface
{
public:
    /*QString getType() const;

    QString setType(const QString &type);*/

    QString getName() const;

protected:
    //QString m_updateDataType;
    QString m_updateDataName;
};

#endif // _QEXTPATTERNUPDATEDATA_H
