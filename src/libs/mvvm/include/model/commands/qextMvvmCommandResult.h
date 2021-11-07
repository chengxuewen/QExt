#ifndef _QEXTMVVMCOMMANDRESULT_H
#define _QEXTMVVMCOMMANDRESULT_H

#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QEXTMvvmItem;
class QEXT_MVVM_API QEXTMvvmCommandResult
{
public:
    QEXTMvvmCommandResult();
    QEXTMvvmCommandResult(bool value);
    QEXTMvvmCommandResult(QEXTMvvmItem *item);
    QEXTMvvmCommandResult(const QEXTMvvmCommandResult &other);
    virtual ~QEXTMvvmCommandResult();

    QEXTMvvmCommandResult &operator=(const QEXTMvvmCommandResult &other);
    bool operator ==(const QEXTMvvmCommandResult &other) const;
    bool operator !=(const QEXTMvvmCommandResult &other) const;

    QEXTMvvmItem *resultItem() const;
    void setResultItem(QEXTMvvmItem *item);

    bool resultValue() const;
    void setResultValue(bool value);

protected:
    bool m_resultValue;
    QSharedPointer<QEXTMvvmItem> m_resultItem;
};

#endif // _QEXTMVVMCOMMANDRESULT_H
