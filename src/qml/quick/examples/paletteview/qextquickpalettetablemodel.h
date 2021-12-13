#ifndef _QEXTQUICKPALETTETABLEMODEL_H
#define _QEXTQUICKPALETTETABLEMODEL_H

#include <QPointer>
#include <QAbstractTableModel>

#include <qextGlobal.h>
#include <qextQuickPalette.h>

class QEXTQuickPaletteTableModel : public QAbstractTableModel
{
public:
    QEXTQuickPaletteTableModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QPointer<QEXTQuickPalette> m_quickPalette;
};

#endif // _QEXTQUICKPALETTETABLEMODEL_H
