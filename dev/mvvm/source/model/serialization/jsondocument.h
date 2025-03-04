// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONDOCUMENT_H
#define MVVM_SERIALIZATION_JSONDOCUMENT_H

#include "model/interfaces/modeldocumentinterface.h"
#include <memory>
#include <vector>

namespace ModelView {

class QExtMvvmSessionModel;

//! Saves and restores list of QExtMvvmSessionModel's to/from disk using json format.
//! Single QExtMvvmJsonDocument corresponds to a single file on disk.

class QEXT_MVVM_API QExtMvvmJsonDocument : public QExtMvvmModelDocumentInterface {
public:
    QExtMvvmJsonDocument(const std::vector<QExtMvvmSessionModel*>& models);
    ~QExtMvvmJsonDocument() override;

    void save(const std::string& file_name) const override;
    void load(const std::string& file_name) override;

private:
    struct JsonDocumentImpl;
    QExtUniquePointer<JsonDocumentImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONDOCUMENT_H
