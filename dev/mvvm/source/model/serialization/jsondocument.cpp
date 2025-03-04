// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/serialization/jsondocument.h"
#include "model/factories/modelconverterfactory.h"
#include "model/model/sessionmodel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <sstream>
#include <stdexcept>

using namespace ModelView;

struct QExtMvvmJsonDocument::JsonDocumentImpl {
    std::vector<QExtMvvmSessionModel*> models;
    JsonDocumentImpl(std::vector<QExtMvvmSessionModel*> models) : models(std::move(models)) {}
};

QExtMvvmJsonDocument::QExtMvvmJsonDocument(const std::vector<QExtMvvmSessionModel*>& models)
    : p_impl(qextMakeUnique<JsonDocumentImpl>(models))
{
}

//! Saves models on disk.
void QExtMvvmJsonDocument::save(const std::string& file_name) const
{
    auto converter = ModelView::qextMvvmCreateModelProjectConverter();
    QJsonArray array;

    for (auto model : p_impl->models)
        array.push_back(converter->to_json(*model));

    QJsonDocument document(array);
    QFile file(QString::fromStdString(file_name));

    if (!file.open(QIODevice::WriteOnly))
        throw std::runtime_error("Error in QExtMvvmJsonDocument: can't save the file '" + file_name + "'");

    file.write(document.toJson());

    file.close();
}

//! Loads models from disk. If models have some data already, it will be rewritten.

void QExtMvvmJsonDocument::load(const std::string& file_name)
{
    QFile file(QString::fromStdString(file_name));
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Error in QExtMvvmJsonDocument: can't read the file '" + file_name + "'");

    auto document = QJsonDocument::fromJson(file.readAll());
    auto array = document.array();
    if (array.size() != static_cast<int>(p_impl->models.size())) {
        std::ostringstream ostr;
        ostr << "Error in QExtMvvmJsonDocument: number of application models " << p_impl->models.size()
             << " and number of json models " << array.size() << " doesn't match";
        throw std::runtime_error(ostr.str());
    }

    auto converter = ModelView::qextMvvmCreateModelProjectConverter();
    int index(0);
    for (auto model : p_impl->models) {
        converter->from_json(array.at(index).toObject(), *model);
        ++index;
    }

    file.close();
}

QExtMvvmJsonDocument::~QExtMvvmJsonDocument() = default;
