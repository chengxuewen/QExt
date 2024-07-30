#include <private/qextBPBasicGraphicsScene_p.h>
#include <qextBPDataFlowGraphicsScene.h>
#include <qextBPNodeDelegateModelRegistry.h>
#include <qextBPConnectionGraphicsObject.h>
#include <qextBPNodeGraphicsObject.h>
#include <qextBPGraphicsView.h>
#include <qextBPUndoCommands.h>

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidgetAction>
#include <QtWidgets/QGraphicsSceneMoveEvent>

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QBuffer>
#include <QtCore/QtGlobal>
#include <QtCore/QByteArray>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>

#include <utility>


class QExtBPDataFlowGraphicsScenePrivate : public QExtBPBasicGraphicsScenePrivate
{
public:
    QExtBPDataFlowGraphicsScenePrivate(QExtBPDataFlowGraphicsScene *q, QExtBPDataFlowGraphModel &graphModel);
    ~QExtBPDataFlowGraphicsScenePrivate() QEXT_OVERRIDE;

    QExtBPDataFlowGraphModel &m_dataFlowGraphModel;

private:
    QEXT_DECL_PUBLIC(QExtBPDataFlowGraphicsScene)
    QEXT_DISABLE_COPY_MOVE(QExtBPDataFlowGraphicsScenePrivate)

};

QExtBPDataFlowGraphicsScenePrivate::QExtBPDataFlowGraphicsScenePrivate(QExtBPDataFlowGraphicsScene *q,
                                                                       QExtBPDataFlowGraphModel &graphModel)
    : QExtBPBasicGraphicsScenePrivate(q, graphModel)
    , m_dataFlowGraphModel(graphModel)
{
}

QExtBPDataFlowGraphicsScenePrivate::~QExtBPDataFlowGraphicsScenePrivate()
{
}

QExtBPDataFlowGraphicsScene::QExtBPDataFlowGraphicsScene(QExtBPDataFlowGraphModel &graphModel, QObject *parent)
    : QExtBPBasicGraphicsScene(new QExtBPDataFlowGraphicsScenePrivate(this, graphModel), parent)
{
    connect(&graphModel, SIGNAL(inPortDataWasSet(QExtBPTypes::NodeId,QExtBPTypes::PortTypeEnum,QExtBPTypes::PortIndex)),
            this, SLOT(onInPortDataWasSeted(QExtBPTypes::NodeId,QExtBPTypes::PortTypeEnum,QExtBPTypes::PortIndex)));
}

std::vector<QExtBPTypes::NodeId> QExtBPDataFlowGraphicsScene::selectedNodes() const
{
    QList<QGraphicsItem *> graphicsItems = selectedItems();

    std::vector<QExtBPTypes::NodeId> result;
    result.reserve(graphicsItems.size());

    for (QGraphicsItem *item : graphicsItems)
    {
        auto ngo = qgraphicsitem_cast<QExtBPNodeGraphicsObject *>(item);
        if (ngo != QEXT_NULLPTR)
        {
            result.push_back(ngo->nodeId());
        }
    }

    return result;
}

QMenu *QExtBPDataFlowGraphicsScene::createSceneMenu(const QPointF scenePos)
{
    Q_D(QExtBPDataFlowGraphicsScene);
    QMenu *modelMenu = new QMenu();

    // Add filterbox to the context menu
    auto *txtBox = new QLineEdit(modelMenu);
    txtBox->setPlaceholderText(QStringLiteral("Filter"));
    txtBox->setClearButtonEnabled(true);

    auto *txtBoxAction = new QWidgetAction(modelMenu);
    txtBoxAction->setDefaultWidget(txtBox);

    // 1.
    modelMenu->addAction(txtBoxAction);

    // Add result treeview to the context menu
    QTreeWidget *treeView = new QTreeWidget(modelMenu);
    treeView->header()->close();

    auto *treeViewAction = new QWidgetAction(modelMenu);
    treeViewAction->setDefaultWidget(treeView);

    // 2.
    modelMenu->addAction(treeViewAction);

    auto registry = d->m_dataFlowGraphModel.dataModelRegistry();

    for (const auto &cat : registry->categories())
    {
        auto item = new QTreeWidgetItem(treeView);
        item->setText(0, cat);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    }

    for (const auto &assoc : registry->registeredModelsCategoryAssociation())
    {
        QList<QTreeWidgetItem *> parent = treeView->findItems(assoc.second, Qt::MatchExactly);

        if (parent.count() <= 0)
        {
            continue;
        }

        auto item = new QTreeWidgetItem(parent.first());
        item->setText(0, assoc.first);
    }

    treeView->expandAll();

    connect(treeView,
            &QTreeWidget::itemClicked, this,
            [this, modelMenu, scenePos](QTreeWidgetItem *item, int)
            {
                if (!(item->flags() & (Qt::ItemIsSelectable)))
                {
                    return;
                }

                this->undoStack().push(new QExtBPCreateCommand(this, item->text(0), scenePos));

                modelMenu->close();
            });

    //Setup filtering
    connect(txtBox, &QLineEdit::textChanged, this, [treeView](const QString &text)
            {
                QTreeWidgetItemIterator categoryIt(treeView, QTreeWidgetItemIterator::HasChildren);
                while (*categoryIt)
                {
                    (*categoryIt++)->setHidden(true);
                }
                QTreeWidgetItemIterator it(treeView, QTreeWidgetItemIterator::NoChildren);
                while (*it)
                {
                    auto modelName = (*it)->text(0);
                    const bool match = (modelName.contains(text, Qt::CaseInsensitive));
                    (*it)->setHidden(!match);
                    if (match)
                    {
                        QTreeWidgetItem *parent = (*it)->parent();
                        while (parent)
                        {
                            parent->setHidden(false);
                            parent = parent->parent();
                        }
                    }
                    ++it;
                }
            });

    // make sure the text box gets focus so the user doesn't have to click on it
    txtBox->setFocus();

    // QMenu's instance auto-destruction
    modelMenu->setAttribute(Qt::WA_DeleteOnClose);

    return modelMenu;
}

void QExtBPDataFlowGraphicsScene::save() const
{
    Q_D(const QExtBPDataFlowGraphicsScene);
    QString fileName = QFileDialog::getSaveFileName(QEXT_NULLPTR,
                                                    tr("Open Flow Scene"),
                                                    QDir::homePath(),
                                                    tr("Flow Scene Files (*.flow)"));

    if (!fileName.isEmpty())
    {
        if (!fileName.endsWith("flow", Qt::CaseInsensitive))
        {
            fileName += ".flow";
        }

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(QJsonDocument(d->m_dataFlowGraphModel.save()).toJson());
        }
    }
}

void QExtBPDataFlowGraphicsScene::load()
{
    Q_D(QExtBPDataFlowGraphicsScene);
    QString fileName = QFileDialog::getOpenFileName(QEXT_NULLPTR,
                                                    tr("Open Flow Scene"),
                                                    QDir::homePath(),
                                                    tr("Flow Scene Files (*.flow)"));

    if (!QFileInfo::exists(fileName))
    {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    this->clearScene();

    QByteArray const wholeFile = file.readAll();

    d->m_dataFlowGraphModel.load(QJsonDocument::fromJson(wholeFile).object());

    Q_EMIT this->sceneLoaded();
}

void QExtBPDataFlowGraphicsScene::onInPortDataWasSeted(const QExtBPTypes::NodeId nodeId,
                                                       const QExtBPTypes::PortTypeEnum,
                                                       const QExtBPTypes::PortIndex)
{
    this->onNodeUpdated(nodeId);
}
