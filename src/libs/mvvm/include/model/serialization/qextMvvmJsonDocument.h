#ifndef _QEXTMVVMSERIALIZATIONJSONDOCUMENT_H
#define _QEXTMVVMSERIALIZATIONJSONDOCUMENT_H

#include <qextMvvmModelDocumentInterface.h>

#include <vector>
#include <memory>

namespace ModelView
{

class QEXTMvvmSessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.
//! Single JsonDocument corresponds to a single file on disk.

class QEXT_MVVM_API QEXTMvvmJsonDocument : public QEXTMVVMModelDocumentInterface
{
public:
    QEXTMvvmJsonDocument(const std::vector<QEXTMvvmSessionModel*>& models);
    ~QEXTMvvmJsonDocument() override;

    void save(const std::string& file_name) const override;
    void load(const std::string& file_name) override;

private:
    struct JsonDocumentImpl;
    std::unique_ptr<JsonDocumentImpl> p_impl;
};

} // namespace ModelView

#endif // _QEXTMVVMSERIALIZATIONJSONDOCUMENT_H
