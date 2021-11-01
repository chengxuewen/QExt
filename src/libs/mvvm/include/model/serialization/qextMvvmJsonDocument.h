#ifndef _QEXTMVVMJSONDOCUMENT_H
#define _QEXTMVVMJSONDOCUMENT_H

#include <vector>
#include <memory>
#include <qextMvvmModelDocumentInterface.h>

namespace ModelView
{

    class QEXTMvvmSessionModel;

//! Saves and restores list of QEXTMvvmSessionModel's to/from disk using json format.
//! Single QEXTMvvmJsonDocument corresponds to a single file on disk.

    class QEXT_MVVM_API QEXTMvvmJsonDocument : public QEXTMvvmModelDocumentInterface
    {
    public:
        QEXTMvvmJsonDocument(const std::vector<QEXTMvvmSessionModel *> &models);
        ~QEXTMvvmJsonDocument() override;

        void save(const std::string &file_name) const override;
        void load(const std::string &file_name) override;

    private:
        struct JsonDocumentImpl;
        std::unique_ptr<JsonDocumentImpl> p_impl;
    };

} // namespace ModelView

#endif // _QEXTMVVMJSONDOCUMENT_H
