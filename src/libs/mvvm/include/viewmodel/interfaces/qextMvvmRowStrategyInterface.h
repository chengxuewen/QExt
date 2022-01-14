#ifndef _QEXTMVVMINTERFACESROWSTRATEGYINTERFACE_H
#define _QEXTMVVMINTERFACESROWSTRATEGYINTERFACE_H

#include <qextMvvmGlobal.h>

#include <QStringList>

#include <memory>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;
class QEXTMvvmViewItem;

//! Base class to construct row of ViewItem's from given QEXTMvvmSessionItem.
//! Used in context of AbstractViewModel while exposing SessionModel to Qt.

class QEXT_MVVM_API QEXTMvvmRowStrategyInterface
{
public:
    virtual ~QEXTMvvmRowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<std::unique_ptr<QEXTMvvmViewItem>> constructRow(QEXTMvvmSessionItem*) = 0;
};

} // namespace ModelView

#endif // _QEXTMVVMINTERFACESROWSTRATEGYINTERFACE_H
