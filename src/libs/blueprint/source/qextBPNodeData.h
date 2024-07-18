#ifndef _QEXTBPNODEDATA_H
#define _QEXTBPNODEDATA_H

#include <qextBlueprintGlobal.h>

#include <QObject>
#include <QString>

#include <memory>

/**
 * `id` represents an internal unique data type for the given port.
 * `name` is a normal text description.
 */
struct QEXT_BLUEPRINT_API QExtBPNodeDataType
{
    QString id;
    QString name;
};

/**
 * Class represents data transferred between nodes.
 * @param type is used for comparing the types
 * The actual data is stored in subtypes
 */
class QEXT_BLUEPRINT_API QExtBPNodeData
{
public:
    virtual ~QExtBPNodeData() = default;

    virtual bool sameType(const QExtBPNodeData &nodeData) const
    {
        return (this->type().id == nodeData.type().id);
    }

    /// Type for inner use
    virtual QExtBPNodeDataType type() const = 0;
};
Q_DECLARE_METATYPE(QExtBPNodeDataType)
Q_DECLARE_METATYPE(QSharedPointer<QExtBPNodeData>)

#endif // _QEXTBPNODEDATA_H
