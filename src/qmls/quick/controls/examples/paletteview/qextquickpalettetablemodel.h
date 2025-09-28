#ifndef _QEXTQMLQUICKPALETTETABLEMODEL_H
#define _QEXTQMLQUICKPALETTETABLEMODEL_H

#include <QPointer>
#include <QAbstractTableModel>

#include <qextGlobal.h>

class QExtQuickPaletteTableModel : public QAbstractTableModel
{
public:
    QExtQuickPaletteTableModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QPointer<QExtQuickPalette> m_quickPalette;
};

#endif // _QEXTQMLQUICKPALETTETABLEMODEL_H
