#ifndef _QEXTBPNODEDELEGATEMODEL_H
#define _QEXTBPNODEDELEGATEMODEL_H

#include <qextBlueprintGlobal.h>
#include <qextBPSerializable.h>
#include <qextBPNodeStyle.h>
#include <qextBPNodeData.h>
#include <qextBPTypes.h>

#include <QtWidgets/QWidget>

#include <memory>

class QExtBPStyleCollection;

/**
 * The class wraps Node-specific data operations and propagates it to
 * the nesting DataFlowGraphModel which is a subclass of
 * AbstractGraphModel.
 * This class is the same what has been called NodeDataModel before v3.
 */
class QEXT_BLUEPRINT_API QExtBPNodeDelegateModel : public QObject, public QExtBPSerializable
{
    Q_OBJECT

public:
    QExtBPNodeDelegateModel();

    virtual ~QExtBPNodeDelegateModel() = default;

    /// It is possible to hide caption in GUI
    virtual bool captionVisible() const { return true; }

    /// Caption is used in GUI
    virtual QString caption() const = 0;

    /// It is possible to hide port caption in GUI
    virtual bool portCaptionVisible(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const { return false; }

    /// Port caption is used in GUI to label individual ports
    virtual QString portCaption(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const { return QString(); }

    /// Name makes this model unique
    virtual QString name() const = 0;

public:
    QJsonObject save() const override;

    void load(const QJsonObject &) override;

public:
    virtual unsigned int nPorts(QExtBPTypes::PortTypeEnum portType) const = 0;

    virtual QExtBPNodeDataType dataType(QExtBPTypes::PortTypeEnum portType, QExtBPTypes::PortIndex portIndex) const = 0;

public:
    virtual QExtBPTypes::ConnectionPolicyEnum portConnectionPolicy(QExtBPTypes::PortTypeEnum, QExtBPTypes::PortIndex) const;

    const QExtBPNodeStyle &nodeStyle() const;

    void setNodeStyle(const QExtBPNodeStyle &style);

public:
    virtual void setInData(QSharedPointer<QExtBPNodeData> nodeData, const QExtBPTypes::PortIndex portIndex) = 0;

    virtual QSharedPointer<QExtBPNodeData> outData(const QExtBPTypes::PortIndex port) = 0;

    /**
   * It is recommented to preform a lazy initialization for the
   * embedded widget and create it inside this function, not in the
   * constructor of the current model.
   *
   * Our Model Registry is able to shortly instantiate models in order
   * to call the non-static `Model::name()`. If the embedded widget is
   * allocated in the constructor but not actually embedded into some
   * QGraphicsProxyWidget, we'll gonna have a dangling pointer.
   */
    virtual QWidget *embeddedWidget() = 0;

    virtual bool resizable() const { return false; }

public Q_SLOTS:

    virtual void inputConnectionCreated(const QExtBPTypes::ConnectionId &) {}

    virtual void inputConnectionDeleted(const QExtBPTypes::ConnectionId &) {}

    virtual void outputConnectionCreated(const QExtBPTypes::ConnectionId &) {}

    virtual void outputConnectionDeleted(const QExtBPTypes::ConnectionId &) {}

Q_SIGNALS:

    /// Triggers the updates in the nodes downstream.
    void dataUpdated(const QExtBPTypes::PortIndex index);

    /// Triggers the propagation of the empty data downstream.
    void dataInvalidated(const QExtBPTypes::PortIndex index);

    void computingStarted();

    void computingFinished();

    void embeddedWidgetSizeUpdated();

    /// Call this function before deleting the data associated with ports.
    /**
   * The function notifies the Graph Model and makes it remove and recompute the
   * affected connection addresses.
   */
    void portsAboutToBeDeleted(const QExtBPTypes::PortTypeEnum portType,
                               const QExtBPTypes::PortIndex first,
                               const QExtBPTypes::PortIndex last);

    /// Call this function when data and port moditications are finished.
    void portsDeleted();

    /// Call this function before inserting the data associated with ports.
    /**
   * The function notifies the Graph Model and makes it recompute the affected
   * connection addresses.
   */
    void portsAboutToBeInserted(const QExtBPTypes::PortTypeEnum portType,
                                const QExtBPTypes::PortIndex first,
                                const QExtBPTypes::PortIndex last);

    /// Call this function when data and port moditications are finished.
    void portsInserted();

private:
    QExtBPNodeStyle _nodeStyle;
};

#endif // _QEXTBPNODEDELEGATEMODEL_H
