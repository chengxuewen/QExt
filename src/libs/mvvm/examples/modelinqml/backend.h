// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_BACKEND_H
#define MODELINQMLCORE_BACKEND_H

#include <QObject>
#include <QString>
#include <QScopedPointer>
#include "tablemodel.h"
#include "particleviewmodel.h"

//class TableModel;
//class ParticleViewModel;

class BackEnd : public QObject
{
    Q_OBJECT

public:
    explicit BackEnd(QObject* parent = nullptr);
    ~BackEnd() QEXT_DECL_OVERRIDE;

    Q_INVOKABLE TableModel* tableModel() const;
    Q_INVOKABLE ParticleViewModel* particleViewModel() const;

private:
    struct BackEndImpl;
    QScopedPointer<BackEndImpl> p_impl;
};

#endif // MODELINQMLCORE_BACKEND_H
