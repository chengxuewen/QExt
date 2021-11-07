#ifndef _QEXTMVVMJSONDOCUMENT_H
#define _QEXTMVVMJSONDOCUMENT_H

#include <qextMvvmModelDocumentInterface.h>

#include <QVector>
#include <QScopedPointer>

class QEXTMvvmModel;

//! Saves and restores list of QEXTMvvmModel's to/from disk using json format.
//! Single QEXTMvvmJsonDocument corresponds to a single file on disk.

class QEXT_MVVM_API QEXTMvvmJsonDocument : public QEXTMvvmModelDocumentInterface
{
public:
    QEXTMvvmJsonDocument(const QVector<QEXTMvvmModel *> &models);
    ~QEXTMvvmJsonDocument() QEXT_DECL_OVERRIDE;

    void save(const QString &file_name) const QEXT_DECL_OVERRIDE;
    void load(const QString &file_name) QEXT_DECL_OVERRIDE;

private:
    struct JsonDocumentImpl;
    QScopedPointer<JsonDocumentImpl> p_impl;
};


#endif // _QEXTMVVMJSONDOCUMENT_H
