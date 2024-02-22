#ifndef _QEXTMVCUPDATEDATA_H
#define _QEXTMVCUPDATEDATA_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

class QEXT_PATTERNS_API QExtMVCUpdateData : public QExtMVCUpdateDataInterface
{
public:
    /*QString getType() const;

    QString setType(const QString &type);*/

    QString getName() const;

protected:
    //QString m_updateDataType;
    QString m_updateDataName;
};

#endif // _QEXTMVCUPDATEDATA_H
