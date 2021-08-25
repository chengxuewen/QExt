#ifndef QEXTQUICKPALETTETABLEMODEL_H
#define QEXTQUICKPALETTETABLEMODEL_H

#include <QPointer>
#include <QAbstractTableModel>

#include <qextglobal.h>
#include <qextquickpalette.h>



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

#endif // QEXTQUICKPALETTETABLEMODEL_H
