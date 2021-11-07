#include <qextMvvmModel.h>
#include <qextMvvmJsonDocument.h>
#include <qextMvvmFactory.h>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <sstream>
#include <stdexcept>


struct QEXTMvvmJsonDocument::JsonDocumentImpl {
    QVector<QEXTMvvmModel*> models;
    JsonDocumentImpl(const QVector<QEXTMvvmModel*>& models) : models(models) {}
};

QEXTMvvmJsonDocument::QEXTMvvmJsonDocument(const QVector<QEXTMvvmModel *> &models)
    : p_impl(new JsonDocumentImpl(models))
{
}

QEXTMvvmJsonDocument::~QEXTMvvmJsonDocument()
{

}

//! Saves models on disk.
void QEXTMvvmJsonDocument::save(const QString &file_name) const
{
    auto converter = QEXTMvvmFactory::createModelProjectConverter();
    QJsonArray array;

    for (auto model : p_impl->models)
        array.push_back(converter->toJson(*model));

    QJsonDocument document(array);
    QFile file(file_name);

    if (!file.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Error in QEXTMvvmJsonDocument: can't save the file '" + file_name.toStdString() + "'");
    }

    file.write(document.toJson());

    file.close();
}

//! Loads models from disk. If models have some data already, it will be rewritten.

void QEXTMvvmJsonDocument::load(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Error in QEXTMvvmJsonDocument: can't read the file '" + file_name.toStdString() + "'");
    }

    auto document = QJsonDocument::fromJson(file.readAll());
    auto array = document.array();
    if (array.size() != static_cast<int>(p_impl->models.size())) {
        std::ostringstream ostr;
        ostr << "Error in QEXTMvvmJsonDocument: number of application models " << p_impl->models.size()
             << " and number of json models " << array.size() << " doesn't match";
        throw std::runtime_error(ostr.str());
    }

    auto converter = QEXTMvvmFactory::createModelProjectConverter();
    int index(0);
    for (auto model : p_impl->models) {
        converter->fromJson(array.at(index).toObject(), *model);
        ++index;
    }

    file.close();
}
