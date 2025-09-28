#ifndef _PALETTETABLEMODEL_H
#define _PALETTETABLEMODEL_H

#include <QPointer>
#include <QAbstractTableModel>

#include <qextQmlThemePalette.h>

class PaletteTableModel : public QAbstractTableModel
{
public:
    PaletteTableModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QPointer<QExtQmlThemePalette> mPalette;
};

#endif // _PALETTETABLEMODEL_H
