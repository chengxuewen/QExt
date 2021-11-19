#ifndef _QEXTMVVMINSERTNEWITEMCOMMAND_P_H
#define _QEXTMVVMINSERTNEWITEMCOMMAND_P_H

#include <qextMvvmAbstractItemCommand_p.h>
#include <qextMvvmTypes.h>
#include <qextMvvmTagRow.h>
#include <qextMvvmPath.h>

class QEXTMvvmInsertNewItemCommand;
class QEXT_MVVM_API QEXTMvvmInsertNewItemCommandPrivate : public QEXTMvvmAbstractItemCommandPrivate
{
public:
    explicit QEXTMvvmInsertNewItemCommandPrivate(QEXTMvvmInsertNewItemCommand *q);
    ~QEXTMvvmInsertNewItemCommandPrivate() QEXT_DECL_OVERRIDE;

    QEXTMvvmItemFactoryFunction m_factoryFunc;
    QEXTMvvmTagRow m_tagrow;
    QEXTMvvmPath m_itemPath;
    QString m_initialIdentifier;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmInsertNewItemCommandPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmInsertNewItemCommand)
};

#endif // _QEXTMVVMINSERTNEWITEMCOMMAND_P_H
